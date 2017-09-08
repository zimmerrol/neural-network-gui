using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using NNGui.Data.Parameters;
using NNGui.ViewModels.Links;

namespace NNGui.ViewModels.Parameters
{
    class DoubleParameterViewModel : ParameterBaseViewModel
    {
        public DoubleParameter DoubleParameterData { get; }
        public DoubleParameterViewModel(DoubleParameter doubleParameter, LinkBaseViewModel parent) : base(doubleParameter, parent)
        {
            DoubleParameterData = doubleParameter;
        }
        public double Value
        {
            get { return DoubleParameterData.Value; }
            set
            {
                DoubleParameterData.Value = value;
                NotifyOfPropertyChange(() => Value);
            }
        }
    }
}
