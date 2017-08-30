using System;
using System.Collections.Generic;
using System.Collections;
using System.Windows;
using System.Windows.Input;
using NNGui.Data;
using NNGui.Data.Links;
using NNGui.ViewModels;
using System.Linq;
using System.Data;
using NNGui.Data.Parameters;
using System.Windows.Controls;

namespace NNGui
{
    /// <summary>
    /// Interaktionslogik für MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void AddChainCommand_Executed(object sender, ExecutedRoutedEventArgs e)
        {
            var nac = e.Parameter as NetworkArchitecture;
            var cn = new Data.Chain(nac, String.Format("Chain {0}", nac.Chains.Count));
            cn.ChainLinks.Add(new InputLayer(cn, "Input Layer"));
            nac.Chains.Add(cn);
            e.Handled = true;
        }

        private int CountListType<T>(Type type, IEnumerable<T> list)
        {
            return list.Where(x => x.GetType() == type).Count();
        }

        private void RemoveLinkConnectionCommand_Executed(object sender, ExecutedRoutedEventArgs e)
        {
            var lclp = e.Parameter as LinkConnectionListParameter;
            if (lclp == null)
                return;
            lclp.RawValue.Remove(((Control)e.OriginalSource).DataContext as LinkBase);
        }

        private void AddChainLinkCommand_Executed(object sender, ExecutedRoutedEventArgs e)
        {
            var type = Views.AddLayerWindow.ShowAddLayerDialog();
            if (type.HasValue)
            {
                var cn = e.Parameter as Chain;
                int insertIndex = cn.ChainLinks.Count;
                LinkBase link;
                switch (type.Value)
                {
                    case LinkType.InputLayer:
                        if (cn.ChainLinks.Count > 0)
                        {
                            if (CountListType(typeof(InputLayer), cn.ChainLinks) > 0)
                            {
                                MessageBox.Show("Only one Input Layer is allowed (or usefull) per chain.");
                                return;
                            }
                        }
                        insertIndex = 0;
                        link = new Data.Links.InputLayer(cn, String.Format("Input Layer"));
                        ((InputDataParameter)((InputLayer)link).Parameters[0]).Value = ((MainWindowViewModel)DataContext).InputData[0];
                        break;
                    case LinkType.ActivationLayer:
                        link = new Data.Links.ActivationLayer(cn, String.Format("Activation Layer"));
                        break;
                    case LinkType.Convolution1DLayer:
                        link = new Data.Links.Convolution1DLayer(cn, String.Format("1D Convolution Layer"));
                        break;
                    case LinkType.Convolution2DLayer:
                        link = new Data.Links.Convolution2DLayer(cn, String.Format("2D Convolution Layer"));
                        break;
                    case LinkType.Convolution3DLayer:
                        link = new Data.Links.Convolution3DLayer(cn, String.Format("3D Convolution Layer"));
                        break;
                    default:
                    case LinkType.DenseLayer:
                        link = new Data.Links.DenseLayer(cn, String.Format("Dense Layer"));
                        break;
                    case LinkType.DropoutLayer:
                        link = new Data.Links.DropoutLayer(cn, String.Format("Dropout Layer"));
                        break;
                    case LinkType.FlattenLayer:
                        link = new Data.Links.FlattenLayer(cn, String.Format("Flatten Layer"));
                        break;
                    case LinkType.ReshapeLayer:
                        link = new Data.Links.ReshapeLayer(cn, String.Format("Reshape Layer"));
                        break;
                    case LinkType.MergeLayer:
                        link = new Data.Links.MergeLayer(cn, String.Format("Merge Layer"));
                        break;

                }

                cn.ChainLinks.Insert(insertIndex, link);
            }

            e.Handled = true;
        }

        private void RemoveChainCommand_Executed(object sender, ExecutedRoutedEventArgs e)
        {
            var cn = e.Parameter as Chain;
            cn.NetworkArchitecture.Chains.Remove(cn);
            e.Handled = true;
        }

        private void RemoveChainLinkCommand_Executed(object sender, ExecutedRoutedEventArgs e)
        {
            var lk = e.Parameter as LinkBase;
            lk.Chain.ChainLinks.Remove(lk);

            e.Handled = true;
        }

        private void CommandBinding_DefaultCanExecute(object sender, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = true;
        }

        private void ExportButton_Click(object sender, RoutedEventArgs e)
        {
            ((MainWindowViewModel)DataContext).Export();
        }

        private void ImportButton_Click(object sender, RoutedEventArgs e)
        {
            ((MainWindowViewModel)DataContext).Import();
        }

    
    }
}
