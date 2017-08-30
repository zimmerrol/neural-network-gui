using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace NNGui
{
    public static class Commands
    {
        public static readonly RoutedUICommand AddChainCommand = new RoutedUICommand("Add a new chain to the architecture", "AddChainCommand", typeof(MainWindow));
        public static readonly RoutedUICommand AddChainLinkCommand = new RoutedUICommand("Add a new link to the chain", "AddChainLinkCommand", typeof(MainWindow));
        public static readonly RoutedUICommand RemoveChainCommand = new RoutedUICommand("Removes a chain from the architecture", "RemoveChainCommand", typeof(MainWindow));
        public static readonly RoutedUICommand RemoveChainLinkCommand = new RoutedUICommand("Removes a link from the chain", "RemoveChainLinkCommand", typeof(MainWindow));
        public static readonly RoutedUICommand RemoveLinkConnectionCommand = new RoutedUICommand("Removes a connection to another link.", "RemoveLinkConnectionCommand", typeof(MainWindow));
    }
}
