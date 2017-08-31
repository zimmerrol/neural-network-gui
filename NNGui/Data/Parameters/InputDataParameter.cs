using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;
using NNGui.Data.Links;
using NNGui.Data.Tuple;

namespace NNGui.Data.Parameters
{
    public class InputDataParameter : ParameterBase<InputData>
    {
        protected InputDataParameter() { }
        public InputDataParameter(LinkBase link) : base("Input Data", link) { }
        public InputDataParameter(InputData value, LinkBase link) : base("Input Data", value, link) { }
    }

    public class InputData
    {
        private InputData() { }
        public InputData(string id, string name, IntTupleBase shape, string description)
        {
            ID = id;
            Name = name;
            Shape = shape;
            Description = description;
        }

        public string ID { get; set; }
        [XmlIgnore]
        public string Name { get; set; }
        [XmlIgnore]
        public IntTupleBase Shape { get; set; }
        [XmlIgnore]
        public string Description { get; set; }
    }
}
