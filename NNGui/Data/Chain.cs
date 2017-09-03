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
    public class Chain : INotifyPropertyChanged, IDeserializationCallback
    {
        private Chain()
        {
            ChainLinks = new ObservableCollection<LinkBase>();
        }
        public Chain(NetworkArchitecture parent) : this()
        {
            NetworkArchitecture = parent;
        }

        public Chain(NetworkArchitecture parent, string name) : this(parent)
        {
            _name = name;
        }

        [XmlIgnore]
        public NetworkArchitecture NetworkArchitecture { get; internal set; }

        public ObservableCollection<LinkBase> ChainLinks { get; }

        private string _name;

        public event PropertyChangedEventHandler PropertyChanged;
        protected virtual void OnPropertyChanged(string propertyName)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }

        public void ValidateInputCompatibility()
        {
            foreach (var item in ChainLinks)
                item.ValidateInputCompatibility();
        }

        public void OnDeserialization(object sender)
        {
            foreach (var link in ChainLinks)
            {
                link.ParentChain = this;
            }
        }

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
    }
}
