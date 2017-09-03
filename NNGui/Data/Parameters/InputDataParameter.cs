using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;
using NNGui.Data.Links;
using NNGui.Data.Tuple;
using System.Runtime.Serialization;

namespace NNGui.Data.Parameters
{
    public class InputDataParameter : ParameterBase<String>
    {
        protected InputDataParameter() { }
        public InputDataParameter(LinkBase link) : base("Input Data", link) { }
        public InputDataParameter(InputData value, LinkBase link) : base("Input Data", value.ID, link) { }
        public InputDataParameter(String value, LinkBase link) : base("Input Data", value, link) { }

        [XmlIgnore]
        public InputData InputDataValue
        {
            get
            {
                foreach (var item in Parent.ParentChain.NetworkArchitecture.Problem.Inputs)
                {
                    if (item.ID.Equals(Value))
                    {
                        return item;
                    }
                }

                return null;
            }
            set
            {
                Value = value.ID;
            }
        }
    }

    public class InputData : IDeserializationCallback
    {
        private InputData() { }
        public InputData(string id, string name, IntTupleBase shape, string description)
        {
            ID = id;
            Name = name;
            Shape = shape;
            Description = description;
        }

        [XmlAttribute]
        public string ID { get; set; }
        [XmlAttribute]
        public string Name { get; set; }

        public IntTupleBase Shape { get; set; }
        [XmlIgnore]
        public string Description { get; set; }

        public void OnDeserialization(object sender)
        {
            //throw new NotImplementedException();
        }
    }
}
