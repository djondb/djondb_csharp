using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Djondb
{
    public class BSONObj: IEnumerable<KeyValuePair<string, object>>
    {
        private Dictionary<string, object> _data = new Dictionary<string, object>();

        public void add(string name, object data)
        {
            if (_data.ContainsKey(name))
            {
                _data.Remove(name);
            }
            _data.Add(name, data);
        }

        public object this[string name]
        {
            get
            {
                if (_data.ContainsKey(name))
                {
                    return _data[name];
                }
                else
                {
                    return null;
                }
            }
            set
            {
                add(name, value);
            }
        }

        public int Count
        {
            get { return _data.Count; }
        }

        public IEnumerator<KeyValuePair<string, object>> GetEnumerator()
        {
            return new BSONEnumerator(this);
        }

        System.Collections.IEnumerator System.Collections.IEnumerable.GetEnumerator()
        {
            return new BSONEnumerator(this);
        }

        public class BSONEnumerator : IEnumerator<KeyValuePair<string, object>>
        {
            private IEnumerator<string> _internalE;
            private BSONObj _object;

            public BSONEnumerator(BSONObj obj)
            {
                this._object = obj;
                this._internalE = obj._data.Keys.GetEnumerator();
            }

            public KeyValuePair<string, object> Current
            {
                get { 
                    return new KeyValuePair<string, object>(this._internalE.Current, this._object[this._internalE.Current]); 
                }
            }

            public void Dispose()
            {
            }

            object System.Collections.IEnumerator.Current
            {
                get
                {
                    return new KeyValuePair<string, object>(this._internalE.Current, this._object[this._internalE.Current]);
                }
            }

            public bool MoveNext()
            {
                return this._internalE.MoveNext();
            }

            public void Reset()
            {
                this._internalE.Reset();
            }
        }
    }
}
