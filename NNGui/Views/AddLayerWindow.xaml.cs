using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using NNGui.Data.Links;
using NNGui.Data.Parameters;

namespace NNGui.Views
{
    /// <summary>
    /// Interaktionslogik für AddLayerWindow.xaml
    /// </summary>
    public partial class AddLayerWindow : Window
    {
        public AddLayerWindow()
        {
            InitializeComponent();
            DataContext = this;
        }

        public LinkType Result { get; set; }

        private void OkButton_Click(object sender, RoutedEventArgs e)
        {
            this.DialogResult = true;
        }

        private void CancelButton_Click(object sender, RoutedEventArgs e)
        {
            this.DialogResult = false;
        }

        public static LinkType? ShowAddLayerDialog()
        {
            var window = new AddLayerWindow();
            if (window.ShowDialog() ?? true)
            {
                return window.Result;
            }
            return null;
        }
    }
}
