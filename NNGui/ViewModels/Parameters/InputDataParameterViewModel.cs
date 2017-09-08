using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using NNGui.Data.Parameters;
using NNGui.Data;
using NNGui.ViewModels.Links;

namespace NNGui.ViewModels.Parameters
{
    class InputDataParameterViewModel : ParameterBaseViewModel
    {
        public InputDataParameter InputDataParameterData { get; }
        public InputDataParameterViewModel(InputDataParameter inputDataParameter, LinkBaseViewModel parent) : base(inputDataParameter, parent)
        {
            InputDataParameterData = inputDataParameter;
        }

        public InputDataViewModel Value
        {
            get { return new InputDataViewModel(InputDataParameterData.InputDataValue); }
            set
            {
                InputDataParameterData.InputDataValue = value.InputData;
                NotifyOfPropertyChange(() => Value);
                Parent.NotifyOfPropertyChange(() => Parent.IsInputCompatible);
            }
        }

    }
}
