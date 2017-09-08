using Caliburn.Micro;
using NNGui.Data.Links;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NNGui.ViewModels.Windows
{
    class AddLinkWindowViewModel : Screen
    {
        public void Accept()
        {
            TryClose();
        }

        public void Cancel()
        {
            Result = null;
            TryClose();
        }

        public LinkType? Result { get; set; } = LinkType.DenseLayer;
    }
}
