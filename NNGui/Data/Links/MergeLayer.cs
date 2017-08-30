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
    public class MergeLayer : LinkBase
    {
        private MergeLayer() : base() { }
        public MergeLayer(Chain parent) : base(parent) { }

        public MergeLayer(Chain parent, string name) : base(parent, name)
        {
            Parameters.Add(new LinkConnectionListParameter("Links", this));
        }

        public override string TypeName { get { return "Merge Layer"; } }
    }
}
