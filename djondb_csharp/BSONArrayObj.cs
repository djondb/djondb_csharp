using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Djondb
{
    public class BSONArrayObj: IEnumerable<BSONObj>
    {
        List<BSONObj> _array = new List<BSONObj>();

        public BSONObj this[int index]
        {
            get
            {
                return _array[index];
            }
        }

        public void Add(BSONObj o)
        {
            _array.Add(o);
        }

        public void Remove(BSONObj o)
        {
            _array.Remove(o);
        }

        public int Count
        {
            get
            {
                return _array.Count;
            }
        }

        public IEnumerator<BSONObj> GetEnumerator()
        {
            return _array.GetEnumerator();
        }

        System.Collections.IEnumerator System.Collections.IEnumerable.GetEnumerator()
        {
            return _array.GetEnumerator();
        }

        public void Add(BSONArrayObj arr)
        {
            _array.AddRange(arr);
        }
    }
}
