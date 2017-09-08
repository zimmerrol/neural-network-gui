using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using NNGui.Data.Parameters;
using NNGui.ViewModels.Links;

namespace NNGui.ViewModels.Parameters
{
    class ActivationFunctionParameterViewModel : ParameterBaseViewModel
    {
        public ActivationFunctionParameter ActivationFunctionParameterData { get; }
        public ActivationFunctionParameterViewModel(ActivationFunctionParameter activationFunctionParameter, LinkBaseViewModel parent) : base(activationFunctionParameter, parent)
        {
            ActivationFunctionParameterData = activationFunctionParameter;
        }

        public ActivationFunction Value
        {
            get { return ActivationFunctionParameterData.Value; }
            set
            {
                ActivationFunctionParameterData.Value = value;
                NotifyOfPropertyChange(() => Value);
                Parent.NotifyOfPropertyChange(() => Parent.IsInputCompatible);
            }
        }
    }
}
