# neural-network-gui
A lightweight GUI to create neural network architectures.

# Structure
This project consits out of two important parts

  * The GUI written in C# with WPF (**NNGui**)
  * The network parser written in C++ (**NNCreator**)
  
## NNGui
This WPF application, written in C#, offers a easy to understand user interface allowing (unexperienced) users to create network architectures easily. Nevertheless, there are almost no restrictions regarding the network architecture, so that is just as well possible to generate more complex models with NNGui.
After the network architecture has been defined in NNGui one can export it as an human-readable .xml file. This .xml file can then later on be parsed by the NNCreator to create a real network model.

## NNCreator
This program/library, written in pure C++, is meant to import the previously .xml files describing a network's architecture. Afterwards it will create a graph to represent this architecture in one of the popular deep learning frameworks. At the beginning only Microsoft's CNTK is supported, but it is planned to support different frameworks like Caffe/Caffe2 and tensorflow later, too.
