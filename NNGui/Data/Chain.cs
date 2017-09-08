using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;
using NNGui.Data.Links;

namespace NNGui.Data
{
    public class Chain : IDeserializationCallback
    {
        private Chain()
        {
            ChainLinks = new List<LinkBase>();
        }
        public Chain(NetworkArchitecture parent) : this()
        {
            NetworkArchitecture = parent;
        }

        public Chain(NetworkArchitecture parent, string name) : this(parent)
        {
            Name = name;
        }

        [XmlIgnore]
        public NetworkArchitecture NetworkArchitecture { get; internal set; }

        public List<LinkBase> ChainLinks { get; }

        public void OnDeserialization(object sender)
        {
            foreach (var link in ChainLinks)
            {
                link.ParentChain = this;
            }
        }

        [XmlAttribute]
        public string Name { get; set; }
    }
}
