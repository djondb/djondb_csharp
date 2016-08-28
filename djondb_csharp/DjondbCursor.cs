using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Djondb
{
    public class DjondbCursor
    {
        private enum CursorStatus
        {
            CS_LOADING = 1,
            CS_RECORDS_LOADED = 2,
            CS_CLOSED = 3
        };

        private Command _command;
        private string _cursorId;
        private BSONArrayObj _rows;
        private int _pos;
        private int _count;
        private BSONObj _current;
        private CursorStatus _status;

        internal DjondbCursor(Command cmd, string cursorId, BSONArrayObj arr)
        {
            // TODO: Complete member initialization
            this._command = cmd;
            this._cursorId = cursorId;
            this._rows = arr;
            if (_rows == null)
            {
                _rows = new BSONArrayObj();
            }
            this._pos = 0;
            this._current = null;
            if (this._rows == null)
            {
                this._count = 0;
            }
            else
            {
                this._count = this._rows.Count;
            }
            if (cursorId != null)
            {
                this._status = CursorStatus.CS_LOADING;
            }
            else
            {
                this._status = CursorStatus.CS_RECORDS_LOADED;
            }
        }

        public bool Next()
        {
            if (_status == CursorStatus.CS_CLOSED)
            {
                throw new ApplicationException("Cursor is Closed");
            }
            bool result = true;
            if (_count > _pos)
            {
                _current = _rows[_pos];
                _pos++;
            }
            else
            {
                if (_status == CursorStatus.CS_LOADING)
                {
                    BSONArrayObj page = _command.FetchRecords(_cursorId);
                    if (page == null)
                    {
                        _status = CursorStatus.CS_RECORDS_LOADED;
                        result = false;
                    }
                    else
                    {
                        _rows.Add(page);
                        _count += page.Count;
                        result = Next();
                    }
                }
                else
                {
                    result = false;
                }
            }
            return result;
        }

        public BSONObj Current
        {
            get
            {
                return _current;
            }
        }

        public void ReleaseCursor()
        {
            _command.ReleaseCursor(this._cursorId);
        }
    }
}
