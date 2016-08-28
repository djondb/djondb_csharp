using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Djondb
{
    enum CommandType
    {
        INSERT = 0,
        UPDATE = 1,
        FIND = 2,
        CLOSECONNECTION = 3,
        DROPNAMESPACE = 4,
        SHUTDOWN = 5,
        SHOWDBS = 6,
        SHOWNAMESPACES = 7,
        REMOVE = 8,
        COMMIT = 9,
        ROLLBACK = 10,
        FETCHCURSOR = 11,
        FLUSHBUFFER = 12,
        CREATEINDEX = 13,
        BACKUP = 14,
        RCURSOR = 15,
        PERSISTINDEXES = 16,
        EXECUTEQUERY = 17,
        EXECUTEUPDATE = 18
    };

    class Command
    {
        private Network _network;
        private int ResultCode;
        private string ResultMessage;
        private string _activeTransaction;

        public Command(System.Net.Sockets.TcpClient client)
        {
            // TODO: Complete member initialization
            this._network = new Network(client);
            _activeTransaction = null;
        }

        private void WriteOptions()
        {
            BSONObj o = new BSONObj();
            if (_activeTransaction != null)
            {
                o.add("_transactionId", _activeTransaction);
            }
            this._network.WriteBSON(o);
        }

        private string[] ReadResultShowDbs()
        {
            int results = this._network.ReadInt32();
            string[] dbs = new string[results];
            for (int x = 0; x < results; x++)
            {
                string db = this._network.ReadString();
                dbs[x] = db;
            }

            readErrorInformation();

            return dbs;
        }

        public string[] ShowDbs()
        {
            this._network.Reset();
            this._network.WriteHeader();
            this._network.WriteInt32((int)CommandType.SHOWDBS);
            WriteOptions();
            this._network.Flush();

            return ReadResultShowDbs();
        }

        private string[] ReadResultShowNameSpaces()
        {
            int results = this._network.ReadInt32();
            string[] nss = new string[results];
            for (int x = 0; x < results; x++)
            {
                string ns = this._network.ReadString();
                nss[x] = ns;
            }

            readErrorInformation();

            return nss;
        }

        public string[] ShowNamespaces(string db)
        {
            this._network.Reset();
            this._network.WriteHeader();
            this._network.WriteInt32((int)CommandType.SHOWNAMESPACES);
            WriteOptions();
            this._network.WriteString(db);
            this._network.Flush();

            return ReadResultShowNameSpaces();
        }

        private void ReadResultInsert()
        {
            int result = this._network.ReadInt32();

            readErrorInformation();
        }

        public void Insert(string db, string ns, BSONObj obj)
        {
            this._network.Reset();
            this._network.WriteHeader();
            this._network.WriteInt32((int)CommandType.INSERT);
            WriteOptions();
            this._network.WriteString(db);
            this._network.WriteString(ns);
            this._network.WriteBSON(obj);
            this._network.Flush();

            ReadResultInsert();
        }

        private bool ReadResultUpdate()
        {
            bool b = this._network.ReadBoolean();

            readErrorInformation();
            return b;
        }

        public void Update(string db, string ns, BSONObj obj)
        {
            this._network.Reset();
            this._network.WriteHeader();
            this._network.WriteInt32((int)CommandType.UPDATE);
            WriteOptions();
            this._network.WriteString(db);
            this._network.WriteString(ns);
            this._network.WriteBSON(obj);
            this._network.Flush();

            ReadResultUpdate();
        }

        private DjondbCursor ReadResultFind()
        {
            string cursorId = this._network.ReadString();
            int flag = this._network.ReadInt32();

            DjondbCursor cursor = null;
            BSONArrayObj arr = null;
            if (flag == 1)
            {
                arr = _network.ReadBSONArray();
            }
            cursor = new DjondbCursor(this, cursorId, arr);
            readErrorInformation();
            return cursor;
        }

        public DjondbCursor Find(string db, string ns, string select, string filter)
        {
            this._network.Reset();
            this._network.WriteHeader();
            this._network.WriteInt32((int)CommandType.FIND);
            WriteOptions();
            this._network.WriteString(db);
            this._network.WriteString(ns);
            this._network.WriteString(filter);
            this._network.WriteString(select);
            this._network.Flush();

            return ReadResultFind();
        }

        private void readErrorInformation()
        {
            this.ResultCode = this._network.ReadInt32();
            if (this.ResultCode > 0) {
                this.ResultMessage = this._network.ReadString();
                throw new DjondbException(ResultCode, ResultMessage);
            }
        }

        private bool ReadResultDropNamespace()
        {
            int result = this._network.ReadInt32();
            readErrorInformation();

            return true;
        }

        public bool DropNamespace(string db, string ns)
        {
            this._network.Reset();
            this._network.WriteHeader();
            this._network.WriteInt32((int)CommandType.DROPNAMESPACE);
            WriteOptions();
            this._network.WriteString(db);
            this._network.WriteString(ns);
            this._network.Flush();

            return ReadResultDropNamespace();
        }

        private bool ReadResultRemove()
        {
            readErrorInformation();

            return true;

        }

        public bool Remove(string db, string ns, string id, string revision = null)
        {
            this._network.Reset();
            this._network.WriteHeader();
            this._network.WriteInt32((int)CommandType.REMOVE);
            WriteOptions();
            this._network.WriteString(db);
            this._network.WriteString(ns);
            this._network.WriteString(id);
            if (revision != null)
            {
                this._network.WriteString(revision);
            }
            else
            {
                this._network.WriteString("");
            }
            this._network.Flush();

            return ReadResultRemove();
        }

        public void BeginTransaction()
        {
            _activeTransaction = Guid.NewGuid().ToString();
        }

        private void ReadResultCommit()
        {
            readErrorInformation();
            _activeTransaction = null;
        }

        public void CommitTransaction()
        {
            if (_activeTransaction != null)
            {
                this._network.Reset();
                this._network.WriteHeader();
                this._network.WriteInt32((int)CommandType.COMMIT);
                WriteOptions();
                this._network.WriteString(_activeTransaction);
                this._network.Flush();

                ReadResultCommit();
            }
            else
            {
                throw new ApplicationException("Before commiting or rolling back you will need to call BeginTransaction");
            }
        }

        private void ReadResultRollbackTransaction()
        {
            readErrorInformation();
            _activeTransaction = null;
        }

        public void RollbackTransaction()
        {
            if (_activeTransaction != null)
            {
                this._network.Reset();
                this._network.WriteHeader();
                this._network.WriteInt32((int)CommandType.ROLLBACK);
                WriteOptions();
                this._network.WriteString(_activeTransaction);
                this._network.Flush();

                ReadResultRollbackTransaction();
            }
            else
            {
                throw new ApplicationException("Before commiting or rolling back you will need to call BeginTransaction");
            }
        }

        private BSONArrayObj ReadResultFetchRecords()
        {
            int flag = this._network.ReadInt32();
            BSONArrayObj result = null;
            if (flag == 1)
            {
                result = this._network.ReadBSONArray();
            }

            readErrorInformation();
            return result;
        }

        public BSONArrayObj FetchRecords(string cursorId)
        {
            this._network.Reset();
            this._network.WriteHeader();
            this._network.WriteInt32((int)CommandType.FETCHCURSOR);
            WriteOptions();
            this._network.WriteString(cursorId);
            this._network.Flush();

            return ReadResultFetchRecords();
        }

        private void ReadResultCreateIndex()
        {
            readErrorInformation();
        }

        public void CreateIndex(BSONObj indexDescription)
        {
            this._network.Reset();
            this._network.WriteHeader();
            this._network.WriteInt32((int)CommandType.CREATEINDEX);
            WriteOptions();
            this._network.WriteBSON(indexDescription);
            this._network.Flush();

            ReadResultCreateIndex();
        }

        private int ReadResultBackup()
        {
            int result = this._network.ReadInt32();
            readErrorInformation();
            return result;
        }

        public int Backup(string db, string location)
        {
            this._network.Reset();
            this._network.WriteHeader();
            this._network.WriteInt32((int)CommandType.BACKUP);
            WriteOptions();
            this._network.WriteString(db);
            this._network.WriteString(location);
            this._network.Flush();

            return ReadResultBackup();
        }

        public void ExecuteUpdate(string query)
        {
            this._network.Reset();
            this._network.WriteHeader();
            this._network.WriteInt32((int)CommandType.EXECUTEUPDATE);
            WriteOptions();
            this._network.WriteString(query);
            this._network.Flush();

            int flag = this._network.ReadInt32();
            if (flag == 1)
            {
                CommandType commandType = (CommandType) this._network.ReadInt32();
                switch (commandType)
                {
                    case CommandType.INSERT:
                        ReadResultInsert();
                        break;
                    case CommandType.BACKUP:
                        ReadResultBackup();
                        break;
                    case CommandType.COMMIT:
                        ReadResultCommit();
                        break;
                    case CommandType.CREATEINDEX:
                        ReadResultCreateIndex();
                        break;
                    case CommandType.DROPNAMESPACE:
                        ReadResultDropNamespace();
                        break;
                    case CommandType.REMOVE:
                        ReadResultRemove();
                        break;
                    case CommandType.ROLLBACK:
                        ReadResultRollbackTransaction();
                        break;
                    case CommandType.UPDATE:
                        ReadResultUpdate();
                        break;
                }
            }
            readErrorInformation();
        }

        public DjondbCursor ExecuteQuery(string query)
        {
            this._network.Reset();
            this._network.WriteHeader();
            this._network.WriteInt32((int)CommandType.EXECUTEQUERY);
            WriteOptions();
            this._network.WriteString(query);
            this._network.Flush();

            int flag = this._network.ReadInt32();
            DjondbCursor cursor = null;
            if (flag == 1)
            {
                CommandType commandType = (CommandType)this._network.ReadInt32();
                switch (commandType)
                {
                    case CommandType.INSERT:
                        ReadResultInsert();
                        break;
                    case CommandType.BACKUP:
                        ReadResultBackup();
                        break;
                    case CommandType.COMMIT:
                        ReadResultCommit();
                        break;
                    case CommandType.CREATEINDEX:
                        ReadResultCreateIndex();
                        break;
                    case CommandType.DROPNAMESPACE:
                        ReadResultDropNamespace();
                        break;
                    case CommandType.FIND:
                        cursor = ReadResultFind();
                        break;
                    case CommandType.REMOVE:
                        ReadResultRemove();
                        break;
                    case CommandType.ROLLBACK:
                        ReadResultRollbackTransaction();
                        break;
                    case CommandType.SHOWDBS:
                        string[] dbs = ReadResultShowDbs();
                        BSONArrayObj arrDbs = new BSONArrayObj();
                        foreach (string db in dbs)
                        {
                            BSONObj o = new BSONObj();
                            o.add("db", db);
                            arrDbs.Add(o);
                        }
                        cursor = new DjondbCursor(this, null, arrDbs);
                        break;
                    case CommandType.SHOWNAMESPACES:
                        string[] nss = ReadResultShowNameSpaces();
                        BSONArrayObj arrNs = new BSONArrayObj();
                        foreach (string ns in nss)
                        {
                            BSONObj o = new BSONObj();
                            o.add("ns", ns);
                            arrNs.Add(o);
                        }
                        cursor = new DjondbCursor(this, null, arrNs);
                        break;
                    case CommandType.UPDATE:
                        ReadResultUpdate();
                        break;
                }
            }
            if (cursor == null)
            {
                BSONArrayObj arr = new BSONArrayObj();
                BSONObj result = new BSONObj();
                result.add("date", DateTime.Now.ToString("yyyy/MM/dd hh:mm:ss:nn"));
                result.add("success", true);
                arr.Add(result);
                cursor = new DjondbCursor(this, null, arr);
            }
            readErrorInformation();
            return cursor;
        }


        internal void ReleaseCursor(string cursorId)
        {
            this._network.Reset();
            this._network.WriteHeader();
            this._network.WriteInt32((int)CommandType.RCURSOR);
            WriteOptions();
            this._network.WriteString(cursorId);
            this._network.Flush();

            ReadResultReleaseCursor();
        }

        private void ReadResultReleaseCursor()
        {
            readErrorInformation();
        }
    }
}
