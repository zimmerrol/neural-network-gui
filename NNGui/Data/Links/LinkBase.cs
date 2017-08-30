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
    public abstract class LinkBase : IDeserializationCallback
    {
        protected LinkBase()
        {
            Parameters = new ObservableCollection<ParameterBase>();

            initializeID();
        }
        public LinkBase(Chain parent) : this()
        {
            Chain = parent;
        }

        public LinkBase(Chain parent, string name) : this(parent)
        {
            Name = name;
        }

        private void initializeID()
        {
            //generate a 8 character long ID for this link
            //TODO: remove this and replace it with something more robust
            ID = GetHashString(DateTime.Now.ToFileTimeUtc().ToString() + Regex.Replace(TypeName, @"\s+", "")).Substring(0, 8);
        }

        [XmlIgnore]
        public Chain Chain { get; internal set; }

        public ObservableCollection<ParameterBase> Parameters { get; }
        public string Name { get; set; }
        public virtual string TypeName { get; }

        public string ID { get; set; }

        public static byte[] GetHash(string inputString)
        {
            HashAlgorithm algorithm = MD5.Create();  //or use SHA256.Create();
            return algorithm.ComputeHash(Encoding.UTF8.GetBytes(inputString));
        }

        public static string GetHashString(string inputString)
        {
            StringBuilder sb = new StringBuilder();
            foreach (byte b in GetHash(inputString))
                sb.Append(b.ToString("X2"));

            return sb.ToString();
        }

        public void OnDeserialization(object sender)
        {
            foreach (var item in Parameters)
            {
                item.Parent = this;
            }
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
