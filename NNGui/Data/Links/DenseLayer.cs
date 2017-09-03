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
    public class DenseLayer : LinkBase
    {
        private DenseLayer() : base() { }
        public DenseLayer(Chain parent) : base(parent) { }

        public DenseLayer(Chain parent, string name) : base(parent, name)
        {
            Parameters.Add(new IntParameter("Units", this));
            Parameters.Add(new ActivationFunctionParameter("Activation", this));
        }

        public override string TypeName { get { return "Dense Layer"; } }

        public override void ValidateInputCompatibility()
        {
            LinkBase previousLink = GetPreviousLink();
            if (previousLink == null)
            {
                IsInputCompatible = false;
                return;
            }

            IsInputCompatible = (previousLink.GetTensorRank() == 1);
        }

        public override int? GetTensorRank()
        {
            return 1;
        }
    }
}
