using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;
using System.Threading.Tasks;

namespace NNGui.Data
{
    public class NetworkArchitecture : INotifyPropertyChanged, IDeserializationCallback
    {
        public NetworkArchitecture()
        {
            Chains = new ObservableCollection<Chain>();
        }

        public event PropertyChangedEventHandler PropertyChanged;
        protected virtual void OnPropertyChanged(string propertyName)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }

        public ObservableCollection<Chain> Chains { get; }
   
        public void OnDeserialization(object sender)
        {
            foreach (var chain in Chains)
            {
                chain.NetworkArchitecture = this;
            }
        }
    }
}
