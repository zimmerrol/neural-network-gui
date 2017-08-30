using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using NNGui.Data.Links;

namespace NNGui.Data.Parameters
{
    public class IntTuple2DParameter : ParameterBase<Tuple2D<int>>
    {
        private IntTuple2DParameter() { }
        public IntTuple2DParameter(string name, LinkBase link) : base(name, link) { }
        public IntTuple2DParameter(string name, Tuple2D<int> value, LinkBase link) : base(name, value, link) { }
    }

    public class IntTuple3DParameter : ParameterBase<Tuple3D<int>>
    {
        private IntTuple3DParameter() { }
        public IntTuple3DParameter(string name, LinkBase link) : base(name, link) { }
        public IntTuple3DParameter(string name, Tuple3D<int> value, LinkBase link) : base(name, value, link) { }
    }

    public class IntTuple4DParameter : ParameterBase<Tuple4D<int>>
    {
        private IntTuple4DParameter() { }
        public IntTuple4DParameter(string name, LinkBase link) : base(name, link) { }
        public IntTuple4DParameter(string name, Tuple4D<int> value, LinkBase link) : base(name, value, link) { }
    }

    public class TupleBase<T> { }

    public class Tuple1D<T> : TupleBase<T>
    {
        private Tuple1D() { }
        public Tuple1D(T x1)
        {
            this.x1 = x1;
        }

        public T x1 { get; set; }

        public override string ToString()
        {
            return $"({x1})";
        }
    }

    public class Tuple2D<T> : TupleBase<T>
    {
        private Tuple2D() { }
        public Tuple2D(T x1, T x2)
        {
            this.x1 = x1;
            this.x2 = x2;
        }

        public T x1 { get; set; }
        public T x2 { get; set; }

        public override string ToString()
        {
            return $"({x1}, {x2})";
        }
    }

    public class Tuple3D<T> : TupleBase<T>
    {
        private Tuple3D() { }
        public Tuple3D(T x1, T x2, T x3)
        {
            this.x1 = x1;
            this.x2 = x2;
            this.x3 = x3;
        }

        public T x1 { get; set; }
        public T x2 { get; set; }
        public T x3 { get; set; }

        public override string ToString()
        {
            return $"({x1}, {x2}, {x3})";
        }
    }

    public class Tuple4D<T> : TupleBase<T>
    {
        private Tuple4D() { }
        public Tuple4D(T x1, T x2, T x3, T x4)
        {
            this.x1 = x1;
            this.x2 = x2;
            this.x3 = x3;
            this.x4 = x4;
        }

        public T x1 { get; set; }
        public T x2 { get; set; }
        public T x3 { get; set; }
        public T x4 { get; set; }

        public override string ToString()
        {
            return $"({x1}, {x2}, {x3}, {x4})";
        }
    }
}
