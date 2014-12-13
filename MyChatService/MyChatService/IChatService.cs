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
    #region IChatService interface
    /// <summary>
    /// This interface provides 4 methods that may be used in order to clients
    /// to carry out specific actions in the chat room. This interface
    /// expects the clients that implement this interface to be able also support
    /// a callback of type <see cref="IChatCallback">IChatCallback</see>
    /// 
    /// There are methods for
    /// 
    /// Say : send a globally broadcasted message
    /// Whisper : send a personal message
    /// Join : join the chat room
    /// Leave : leave the chat room
    /// </summary>
    [ServiceContract(SessionMode = SessionMode.Required, CallbackContract = typeof(IChatCallback))]
    interface IChatService
    {
        [OperationContract(IsOneWay = true, IsInitiating = false, IsTerminating = false)]
        void Say(string msg);

        [OperationContract(IsOneWay = true, IsInitiating = false, IsTerminating = false)]
        void Whisper(string to, string msg);

        [OperationContract(IsOneWay = false, IsInitiating = true, IsTerminating = false)]
        Person[] Join(Person name);

        [OperationContract(IsOneWay = true, IsInitiating = false, IsTerminating = true)]
        void Leave();

        [OperationContract]
        string ReverseString(string value);

        [OperationContract]
        Stream GetStream(string data);

        [OperationContract]
        bool UploadStream(Stream stream);
    }
    #endregion
    #region IChatCallback interface
    /// <summary>
    /// This interface provides 4 methods that may be used in order to carry 
    /// out a callback to the client. The methods are 1 way (back to the client).
    /// 
    /// There are methods for 
    /// 
    /// Receive : receive a globally broadcasted message
    /// ReceiveWhisper : receive a personal message
    /// UserEnter : recieve notification a new user has entered the chat room
    /// UserLeave : recieve notification a existing user has left the chat room
    /// </summary>
    interface IChatCallback
    {
        [OperationContract(IsOneWay = true)]
        void MyCallbackFunction(string callbackValue);

        [OperationContract(IsOneWay = true)]
        void Receive(Person sender, string message);

        [OperationContract(IsOneWay = true)]
        void ReceiveWhisper(Person sender, string message);

        [OperationContract(IsOneWay = true)]
        void UserEnter(Person person);

        [OperationContract(IsOneWay = true)]
        void UserLeave(Person person);
    }
    #endregion
    #region Public enums/event args
    /// <summary>
    /// A simple enumeration for dealing with the chat message types
    /// </summary>
    public enum MessageType { Receive, UserEnter, UserLeave, ReceiveWhisper };

    /// <summary>
    /// This class is used when carrying out any of the 4 chat callback actions
    /// such as Receive, ReceiveWhisper, UserEnter, UserLeave <see cref="IChatCallback">
    /// IChatCallback</see> for more details
    /// </summary>
    public class ChatEventArgs : EventArgs
    {
        public MessageType msgType;
        public Person person;
        public string message;
    }
    #endregion
}
