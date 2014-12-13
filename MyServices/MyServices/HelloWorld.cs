using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Text;

namespace MyServices
{
    // NOTE: You can use the "Rename" command on the "Refactor" menu to change the class name "HelloWorld" in both code and config file together.
    public class HelloWorld : IHelloWorld
    {
        #region IHelloWorld Members
        public string SayHello(string inputName)
        {
            return "Hello " + inputName;
        }
        #endregion
    }
}
