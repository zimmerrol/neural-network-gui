using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Runtime.Serialization;
using System.Security.Cryptography;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Xml.Serialization;
using NNGui.Data.Parameters;

namespace NNGui.Data.Links
{
    [XmlInclude(typeof(InputLayer))]
    [XmlInclude(typeof(ActivationLayer))]
    [XmlInclude(typeof(Convolution1DLayer))]
    [XmlInclude(typeof(Convolution2DLayer))]
    [XmlInclude(typeof(Convolution3DLayer))]
    [XmlInclude(typeof(DenseLayer))]
    [XmlInclude(typeof(DropoutLayer))]
    [XmlInclude(typeof(FlattenLayer))]
    [XmlInclude(typeof(ReshapeLayer))]
    [XmlInclude(typeof(MergeLayer))]
    [Serializable]
    public abstract class LinkBase : IDeserializationCallback, INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;
        protected virtual void OnPropertyChanged(string propertyName)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }

        public abstract void ValidateInputCompatibility();

        private bool _isInputCompatible;
        [XmlIgnore]
        public bool IsInputCompatible
        {
            get
            {
                return _isInputCompatible;
            }
            set
            {
                _isInputCompatible = value;
                OnPropertyChanged("IsInputCompatible");
            }
        }

        protected LinkBase()
        {
            Parameters = new ObservableCollection<ParameterBase>();

            initializeID();
        }
        public LinkBase(Chain parent) : this()
        {
            ParentChain = parent;
        }

        public LinkBase(Chain parent, string name) : this(parent)
        {
            Name = name;
        }

        private void initializeID()
        {
            //generate a 8 character long ID for this link
            //TODO: remove this and replace it with something more robust
            ID = Utility.GetHashString(DateTime.Now.ToFileTimeUtc().ToString() + Regex.Replace(TypeName, @"\s+", "")).Substring(0, 8);
        }

        private Chain _parentChain;
        [XmlIgnore]
        public Chain ParentChain
        {
            get
            {
                return _parentChain;
            }
            internal set
            {
                _parentChain = value;
                OnPropertyChanged("ParentChain");
            }
        }

        public ObservableCollection<ParameterBase> Parameters { get; }

        private string _name;
        [XmlAttribute]
        public string Name
        {
            get
            {
                return _name;
            }
            set
            {
                _name = value;
                OnPropertyChanged("Name");
            }
        }

        [XmlAttribute]
        public virtual string TypeName { get; }

        public abstract int? GetTensorRank();


        private string _id;
        [XmlAttribute]
        public string ID
        {
            get
            {
                return _id;
            }
            set
            {
                _id = value;
                OnPropertyChanged("ID");
            }
        }

        public void OnDeserialization(object sender)
        {
            foreach (var item in Parameters)
            {
                item.Parent = this;
            }
        }

        public LinkBase GetPreviousLink()
        {
            int index = ParentChain.ChainLinks.IndexOf(this);
            if (index == 0)
                return null;
            return ParentChain.ChainLinks[index - 1];
        }
    }

    public enum LinkType
    {
        [Description("Input Layer")]
        InputLayer,
        [Description("Activation Layer")]
        ActivationLayer,
        [Description("1D Convolution Layer")]
        Convolution1DLayer,
        [Description("2D Convolution Layer")]
        Convolution2DLayer,
        [Description("3D Convolution Layer")]
        Convolution3DLayer,
        [Description("Dense Layer")]
        DenseLayer,
        [Description("Dropout Layer")]
        DropoutLayer,
        [Description("Flatten Layer")]
        FlattenLayer,
        [Description("Reshape Layer")]
        ReshapeLayer,
        [Description("Merge Layer")]
        MergeLayer,
    }
}
