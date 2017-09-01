using NNGui.Data.Links;
using NNGui.Data.Parameters;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;
using System.Xml.Serialization;

namespace NNGui.Data
{
    public class Problem
    {
        public List<InputData> Inputs { get; } = new List<InputData>();
        //TODO: add support for this later
        //public List<OutputData> Outputs { get; set; }
        public NetworkArchitecture NetworkArchitecture { get; set; } = new NetworkArchitecture();

        public void Export()
        {
            var serializer = new XmlSerializer(typeof(NetworkArchitecture), new Type[] {
                    typeof(ActivationLayer), typeof(Convolution1DLayer), typeof(Convolution2DLayer), typeof(Convolution3DLayer), typeof(DenseLayer),
                    typeof(DropoutLayer), typeof(FlattenLayer), typeof(ReshapeLayer), typeof(MergeLayer),
                    typeof(ActivationFunctionParameter), typeof(DoubleParameter), typeof(IntParameter),
                    typeof(IntTuple2DParameter),  typeof(IntTuple3DParameter),  typeof(IntTuple4DParameter)
                });
            using (var sw = new System.IO.StreamWriter("network.xml"))
            {
                using (XmlWriter writer = XmlWriter.Create(sw))
                {
                    serializer.Serialize(writer, this);
                }
            }
        }
        public static Problem Import(List<InputData> inputs)
        {
            var serializer = new XmlSerializer(typeof(NetworkArchitecture), new Type[] {
                    typeof(ActivationLayer), typeof(Convolution1DLayer), typeof(Convolution2DLayer), typeof(Convolution3DLayer), typeof(DenseLayer),
                    typeof(DropoutLayer), typeof(FlattenLayer), typeof(ReshapeLayer), typeof(MergeLayer),
                    typeof(ActivationFunctionParameter), typeof(DoubleParameter), typeof(IntParameter),
                    typeof(IntTuple2DParameter),  typeof(IntTuple3DParameter),  typeof(IntTuple4DParameter)
                });
            using (var sr = new System.IO.StreamReader("network.xml"))
            {
                using (XmlReader reader = XmlReader.Create(sr))
                {
                    Problem result = serializer.Deserialize(reader) as Problem;

                    foreach (var input in result.Inputs)
                    {
                        foreach (var oldInput in inputs)
                        {
                            if (input.ID.Equals(oldInput.ID))
                            {
                                input.Description = oldInput.Description;
                                inputs.Remove(oldInput);
                                break;
                            }
                        }
                    }

                    foreach (var item in inputs)
                        result.Inputs.Add(item);

                    return result;
                }
            }
        }
    }
}
