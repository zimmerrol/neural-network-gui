using GongSolutions.Wpf.DragDrop;
using System;
using System.Collections;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Xml;
using System.Xml.Serialization;
using NNGui.Data;
using NNGui.Data.Links;
using NNGui.Data.Parameters;
using Xml.Serialization;

namespace NNGui.ViewModels
{
    public class MainWindowViewModel : INotifyPropertyChanged
    {
        public MainWindowViewModel()
        {
            _architecture = new NetworkArchitecture();

            Architecture.Chains.Add(new Chain(Architecture, "123"));
            Architecture.Chains.Add(new Chain(Architecture, "456"));
            Architecture.Chains[0].ChainLinks.Add(new DenseLayer(Architecture.Chains[0], "dense1"));

            InputData = new ObservableCollection<Data.Parameters.InputData>();

            InputData.Add(new Data.Parameters.InputData("State Images", new Tuple3D<int>(84, 84, 4), "The state conisting out of the last 4 images."));
            InputData.Add(new Data.Parameters.InputData("State RAM", new Tuple1D<int>(1024 * 1024), "The state conisting out of the current RAM."));
        }

        public event PropertyChangedEventHandler PropertyChanged;
        protected virtual void OnPropertyChanged(string propertyName)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }

        private NetworkArchitecture _architecture;
        public NetworkArchitecture Architecture
        {
            private set
            {
                _architecture = value;
                OnPropertyChanged("Architecture");
            }
            get
            {
                return _architecture;
            }
        }

        public ObservableCollection<InputData> InputData { get; }

        public void Export()
        {
            var serializer = new XmlSerializer(typeof(NetworkArchitecture),
                new Type[] { typeof(ActivationLayer), typeof(Convolution1DLayer), typeof(Convolution2DLayer), typeof(Convolution3DLayer), typeof(DenseLayer),
                            typeof(DropoutLayer), typeof(FlattenLayer), typeof(ReshapeLayer), typeof(MergeLayer),
                           typeof(ActivationFunctionParameter), typeof(DoubleParameter), typeof(IntParameter),
                        typeof(IntTuple2DParameter),  typeof(IntTuple3DParameter),  typeof(IntTuple4DParameter)
                    });
            using (var sw = new System.IO.StreamWriter("network.xml"))
            {
                using (XmlWriter writer = XmlWriter.Create(sw))
                {
                    serializer.Serialize(writer, Architecture);
                }
            }
        }

        public void Import()
        {
            var serializer = new XmlCallbackSerializer(typeof(NetworkArchitecture),
               new Type[] { typeof(ActivationLayer), typeof(Convolution1DLayer), typeof(Convolution2DLayer), typeof(Convolution3DLayer), typeof(DenseLayer),
                            typeof(DropoutLayer), typeof(FlattenLayer), typeof(ReshapeLayer), typeof(MergeLayer),
                           typeof(ActivationFunctionParameter), typeof(DoubleParameter), typeof(IntParameter),
                        typeof(IntTuple2DParameter),  typeof(IntTuple3DParameter),  typeof(IntTuple4DParameter)
                   });
            using (var sr = new System.IO.StreamReader("network.xml"))
            {
                using (XmlReader reader = XmlReader.Create(sr))
                {
                    Architecture = serializer.Deserialize(reader) as NetworkArchitecture;
                }
            }
        }


        public DragDropHandler DDHandler { get; set; } = new DragDropHandler();

        public class DragDropHandler : IDropTarget
        {
            private DefaultDropHandler _defaultDropHandler = new DefaultDropHandler();
            public void DragOver(IDropInfo dropInfo)
            {
                _defaultDropHandler.DragOver(dropInfo);
            }

            public void Drop(IDropInfo dropInfo)
            {
                var targetChain = ((ItemsControl)dropInfo.VisualTarget).DataContext as Chain;
                var item = dropInfo.Data as LinkBase;

                if (targetChain is null)
                {
                    ((ObservableCollection<LinkBase>)((ItemsControl)dropInfo.VisualTarget).ItemsSource).Add(item);
                }
                else
                {
                    item.Chain.ChainLinks.Remove(item);
                    item.Chain = targetChain;
                    item.Chain.ChainLinks.Insert(dropInfo.InsertIndex, item);
                }
            }
        }
    }
}
