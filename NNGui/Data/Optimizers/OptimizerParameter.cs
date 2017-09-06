using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NNGui.Data.Optimizers
{
    public class OptimizerParameter<K, V> : INotifyPropertyChanged
    {
        public OptimizerParameter() { }
        public OptimizerParameter(K key, V value)
        {
            Key = key;
            Value = value;
        }

        public K Key { get; set; }
        private V _value;
        public V Value
        {
            get
            {
                return _value;
            }
            set
            {
                _value = value;
                OnPropertyChanged("Value");
            }
        }
        public event PropertyChangedEventHandler PropertyChanged;
        protected virtual void OnPropertyChanged(string propertyName)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }
    }
}
