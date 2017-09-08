using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NNGui
{
    public static class Extensions
    {
        public static int CountListType<T>(this IEnumerable<T> list, Type type)
        {
            return list.Where(x => x.GetType() == type).Count();
        }
    }
}
