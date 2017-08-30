using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using NNGui.Data.Links;

namespace NNGui.Data.Parameters
{
    public class DoubleParameter : ParameterBase<Double>
    {
        private DoubleParameter() { }
        public DoubleParameter(string name, LinkBase link) : base(name, link) { }
        public DoubleParameter(string name, Double value, LinkBase link) : base(name, value, link) { }
    }
}
