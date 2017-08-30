using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;
using NNGui.Data.Parameters;

namespace NNGui.Data.Links
{
    [Serializable]
    public class Convolution1DLayer : LinkBase
    {
        private Convolution1DLayer() : base() { }
        public Convolution1DLayer(Chain parent) : base(parent) { }

        public Convolution1DLayer(Chain parent, string name) : base(parent, name)
        {
            Parameters.Add(new IntParameter("Filters", this));
            Parameters.Add(new IntParameter("Kernel Size", this));
            Parameters.Add(new IntParameter("Stride", this));
            Parameters.Add(new ActivationFunctionParameter("Activation", this));
        }

        public override string TypeName { get { return "1D Convolution Layer"; } }
    }
}
