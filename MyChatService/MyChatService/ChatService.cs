using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Text;
using Common;
using System.IO;

namespace MyChatService
{
    // NOTE: You can use the "Rename" command on the "Refactor" menu to change the class name "ChatService" in both code and config file together.
    #region ChatService
    /// <summary>
    /// This class provides the service that is used by all clients. This class
    /// uses the bindings as specified in the App.Config, to allow a true peer-2-peer
    /// chat to be perfomed.
    /// 
    /// This class also implements the <see cref="IChat">IChat</see> interface in order
    /// to facilitate a common chat interface for all chat clients
    /// </summary>
    [ServiceBehavior(InstanceContextMode = InstanceContextMode.PerSession, ConcurrencyMode = ConcurrencyMode.Multiple)]
    public class ChatService : IChatService
    {
        #region Instance fields
        //thread sync lock object
        private static Object syncObj = new Object();
        //callback interface for clients
        IChatCallback callback = null;
        //delegate used for BroadcastEvent
        public delegate void ChatEventHandler(object sender, ChatEventArgs e);
        public static event ChatEventHandler ChatEvent;
        private ChatEventHandler myEventHandler = null;
        //holds a list of chatters, and a delegate to allow the BroadcastEvent to work
        //out which chatter delegate to invoke
        static Dictionary<Person, ChatEventHandler> chatters = new Dictionary<Person, ChatEventHandler>();
        //current person 
        private Person person;
        #endregion
        #region Helpers
        /// <summary>
        /// Searches the intenal list of chatters for a particular person, and returns
        /// true if the person could be found
        /// </summary>
        /// <param name="name">the name of the <see cref="Common.Person">Person</see> to find</param>
        /// <returns>True if the <see cref="Common.Person">Person</see> was found in the
        /// internal list of chatters</returns>
        private bool checkIfPersonExists(string name)
        {
            foreach (Person p in chatters.Keys)
            {
                if (p.Name.Equals(name, StringComparison.OrdinalIgnoreCase))
                {
                    return true;
                }
            }
            return false;
        }

        /// <summary>
        /// Searches the intenal list of chatters for a particular person, and returns
        /// the individual chatters ChatEventHandler delegate in order that it can be
        /// invoked
        /// </summary>
        /// <param name="name">the name of the <see cref="Common.Person">Person</see> to find</param>
        /// <returns>The True ChatEventHandler delegate for the <see cref="Common.Person">Person</see> who matched
        /// the name input parameter</returns>
        private ChatEventHandler getPersonHandler(string name)
        {
            foreach (Person p in chatters.Keys)
            {
                if (p.Name.Equals(name, StringComparison.OrdinalIgnoreCase))
                {
                    ChatEventHandler chatTo = null;
                    chatters.TryGetValue(p, out chatTo);
                    return chatTo;
                }
            }
            return null;
        }

        /// <summary>
        /// Searches the intenal list of chatters for a particular person, and returns
        /// the actual <see cref="Common.Person">Person</see> whos name matches
        /// the name input parameter
        /// </summary>
        /// <param name="name">the name of the <see cref="Common.Person">Person</see> to find</param>
        /// <returns>The actual <see cref="Common.Person">Person</see> whos name matches
        /// the name input parameter</returns>
        private Person getPerson(string name)
        {
            foreach (Person p in chatters.Keys)
            {
                if (p.Name.Equals(name, StringComparison.OrdinalIgnoreCase))
                {
                    return p;
                }
            }
            return null;
        }
        #endregion
        #region IChatService implementation
        [OperationBehavior]
        public string ReverseString(string value)
        {
            char[] retVal = value.ToCharArray();
            int idx = 0;
            for (int i = value.Length - 1; i >= 0; i--)
            {
                retVal[idx++] = value[i];
            }
            IChatCallback callback = OperationContext.Current.GetCallbackChannel<IChatCallback>();
            callback.MyCallbackFunction(new string(retVal));
            return new string(retVal);
        }

        /// <summary>
        /// Takes a <see cref="Common.Person">Person</see> and allows them
        /// to join the chat room, if there is not already a chatter with
        /// the same name
        /// </summary>
        /// <param name="person"><see cref="Common.Person">Person</see> joining</param>
        /// <returns>An array of <see cref="Common.Person">Person</see> objects</returns>
        public Person[] Join(Person person)
        {
            bool userAdded = false;
            //create a new ChatEventHandler delegate, pointing to the MyEventHandler() method
            myEventHandler = new ChatEventHandler(MyEventHandler);

            //carry out a critical section that checks to see if the new chatter
            //name is already in use, if its not allow the new chatter to be
            //added to the list of chatters, using the person as the key, and the
            //ChatEventHandler delegate as the value, for later invocation
            lock (syncObj)
            {
                if (!checkIfPersonExists(person.Name) && person != null)
                {
                    this.person = person;
                    chatters.Add(person, MyEventHandler);
                    userAdded = true;
                }
            }

            //if the new chatter could be successfully added, get a callback instance
            //create a new message, and broadcast it to all other chatters, and then 
            //return the list of al chatters such that connected clients may show a
            //list of all the chatters
            if (userAdded)
            {
                callback = OperationContext.Current.GetCallbackChannel<IChatCallback>();
                ChatEventArgs e = new ChatEventArgs();
                e.msgType = MessageType.UserEnter;
                e.person = this.person;
                BroadcastMessage(e);
                //add this newly joined chatters ChatEventHandler delegate, to the global
                //multicast delegate for invocation
                ChatEvent += myEventHandler;
                Person[] list = new Person[chatters.Count];
                //carry out a critical section that copy all chatters to a new list
                lock (syncObj)
                {
                    chatters.Keys.CopyTo(list, 0);
                }
                return list;
            }
            else
            {
                return null;
            }
        }

        /// <summary>
        /// Broadcasts the input msg parameter to all connected chatters
        /// by using the BroadcastMessage() method
        /// </summary>
        /// <param name="msg">The message to broadcast to all chatters</param>
        public void Say(string msg)
        {
            ChatEventArgs e = new ChatEventArgs();
            e.msgType = MessageType.Receive;
            e.person = this.person;
            e.message = msg;
            BroadcastMessage(e);
        }

        /// <summary>
        /// Broadcasts the input msg parameter to all the <see cref="Common.Person">
        /// Person</see> whos name matches the to input parameter
        /// by looking up the person from the internal list of chatters
        /// and invoking their ChatEventHandler delegate asynchronously.
        /// Where the MyEventHandler() method is called at the start of the
        /// asynch call, and the EndAsync() method at the end of the asynch call
        /// </summary>
        /// <param name="to">The persons name to send the message to</param>
        /// <param name="msg">The message to broadcast to all chatters</param>
        public void Whisper(string to, string msg)
        {
            ChatEventArgs e = new ChatEventArgs();
            e.msgType = MessageType.ReceiveWhisper;
            e.person = this.person;
            e.message = msg;
            try
            {
                ChatEventHandler chatterTo;
                //carry out a critical section, that attempts to find the 
                //correct Person in the list of chatters.
                //if a person match is found, the matched chatters 
                //ChatEventHandler delegate is invoked asynchronously
                lock (syncObj)
                {
                    chatterTo = getPersonHandler(to);
                    if (chatterTo == null)
                    {
                        throw new KeyNotFoundException("The person whos name is " + to +
                                                        " could not be found");
                    }
                }
                //do a async invoke on the chatter (call the MyEventHandler() method, and the
                //EndAsync() method at the end of the asynch call
                chatterTo.BeginInvoke(this, e, new AsyncCallback(EndAsync), null);
            }
            catch (KeyNotFoundException)
            {
            }
        }

        /// <summary>
        /// A request has been made by a client to leave the chat room,
        /// so remove the <see cref="Common.Person">Person </see>from
        /// the internal list of chatters, and unwire the chatters
        /// delegate from the multicast delegate, so that it no longer
        /// gets invokes by globally broadcasted methods
        /// </summary>
        public void Leave()
        {
            if (this.person == null)
                return;

            //get the chatters ChatEventHandler delegate
            ChatEventHandler chatterToRemove = getPersonHandler(this.person.Name);

            //carry out a critical section, that removes the chatter from the
            //internal list of chatters
            lock (syncObj)
            {
                chatters.Remove(this.person);
            }
            //unwire the chatters delegate from the multicast delegate, so that 
            //it no longer gets invokes by globally broadcasted methods
            ChatEvent -= chatterToRemove;
            ChatEventArgs e = new ChatEventArgs();
            e.msgType = MessageType.UserLeave;
            e.person = this.person;
            this.person = null;
            //broadcast this leave message to all other remaining connected
            //chatters
            BroadcastMessage(e);
        }

        public System.IO.Stream GetStream(string data)
        {
            try
            {
                ImageData item = new ImageData();
                item.Id = "001";
                item.ImageContent = File.ReadAllBytes(@"C:\Temp\001.tif");
                Stream stream = null;
                Common.SerializeHelper.Serialize<ImageData>(out stream, item);
                return stream;
            }
            catch (Exception ex)
            {
                Console.Write(ex.Message);
                return null;
            }
        }

        public bool UploadStream(Stream stream)
        {
            if (stream == null)
            {
                return false;
            }

            try
            {
                ImageData item = Common.SerializeHelper.Deserialize<ImageData>(stream);
                File.WriteAllBytes(@"C:\Temp\001_server.tif", item.ImageContent);
            }
            catch (Exception)
            {
                return false;
            }
            return true;
        }
        #endregion
        #region private methods

        /// <summary>
        /// This method is called when ever one of the chatters
        /// ChatEventHandler delegates is invoked. When this method
        /// is called it will examine the events ChatEventArgs to see
        /// what type of message is being broadcast, and will then
        /// call the correspoding method on the clients callback interface
        /// </summary>
        /// <param name="sender">the sender, which is not used</param>
        /// <param name="e">The ChatEventArgs</param>
        private void MyEventHandler(object sender, ChatEventArgs e)
        {
            try
            {
                switch (e.msgType)
                {
                    case MessageType.Receive:
                        callback.Receive(e.person, e.message);
                        break;
                    case MessageType.ReceiveWhisper:
                        callback.ReceiveWhisper(e.person, e.message);
                        break;
                    case MessageType.UserEnter:
                        callback.UserEnter(e.person);
                        break;
                    case MessageType.UserLeave:
                        callback.UserLeave(e.person);
                        break;
                }
            }
            catch
            {
                Leave();
            }
        }

        /// <summary>
        ///loop through all connected chatters and invoke their 
        ///ChatEventHandler delegate asynchronously, which will firstly call
        ///the MyEventHandler() method and will allow a asynch callback to call
        ///the EndAsync() method on completion of the initial call
        /// </summary>
        /// <param name="e">The ChatEventArgs to use to send to all connected chatters</param>
        private void BroadcastMessage(ChatEventArgs e)
        {

            ChatEventHandler temp = ChatEvent;

            //loop through all connected chatters and invoke their 
            //ChatEventHandler delegate asynchronously, which will firstly call
            //the MyEventHandler() method and will allow a asynch callback to call
            //the EndAsync() method on completion of the initial call
            if (temp != null)
            {
                foreach (ChatEventHandler handler in temp.GetInvocationList())
                {
                    handler.BeginInvoke(this, e, new AsyncCallback(EndAsync), null);
                }
            }
        }


        /// <summary>
        /// Is called as a callback from the asynchronous call, so simply get the
        /// delegate and do an EndInvoke on it, to signal the asynchronous call is
        /// now completed
        /// </summary>
        /// <param name="ar">The asnch result</param>
        private void EndAsync(IAsyncResult ar)
        {
            ChatEventHandler d = null;

            try
            {
                //get the standard System.Runtime.Remoting.Messaging.AsyncResult,and then
                //cast it to the correct delegate type, and do an end invoke
                System.Runtime.Remoting.Messaging.AsyncResult asres = (System.Runtime.Remoting.Messaging.AsyncResult)ar;
                d = ((ChatEventHandler)asres.AsyncDelegate);
                d.EndInvoke(ar);
            }
            catch
            {
                ChatEvent -= d;
            }
        }
        #endregion
    }
    #endregion
}
