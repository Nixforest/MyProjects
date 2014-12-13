using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;
using System.IO;

namespace Common
{
    public class ImageData
    {
        public string Id { get; set; }
        [XmlElementAttribute(DataType = "base64Binary")]
        public byte[] ImageContent { get; set; }
    }

    public class SerializeHelper
    {
        public static void Serialize<T>(out Stream stream, T item)
        {
            stream = new MemoryStream();
            XmlSerializer x = new XmlSerializer(typeof(T));
            x.Serialize(stream, item);
            stream.Position = 0;
        }

        public static T Deserialize<T>(Stream stream)
        {
            XmlSerializer x = new XmlSerializer(typeof(T));
            T obj = (T)x.Deserialize(stream);
            return obj;
        }
    }
}
