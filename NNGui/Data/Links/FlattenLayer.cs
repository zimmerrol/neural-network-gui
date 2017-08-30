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
    public class FlattenLayer : LinkBase
    {
        private FlattenLayer() : base() { }
        public FlattenLayer(Chain parent) : base(parent) { }

        public FlattenLayer(Chain parent, string name) : base(parent, name) { }

        public override string TypeName { get { return "Flatten Layer"; } }
    }
}
