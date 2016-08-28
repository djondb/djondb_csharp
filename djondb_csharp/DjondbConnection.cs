using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace Djondb
{
    public class DjondbConnection
    {
        private string _host;
        private int _port;
        private Command _command;
        private TcpClient _client;

        public DjondbConnection(string host, int port = 1243)
        {
            this._host = host;
            this._port = port;
        }

        public bool Open()
        {
            _client = new TcpClient();
            _client.NoDelay = true;
            _client.Connect(this._host, this._port);

            _command = new Command(_client);
            return true;
        }

        public bool IsOpen()
        {
            return this._client.Connected;
        }

        public string[] ShowDbs()
        {
            return _command.ShowDbs();
        }

        public string[] ShowNamespaces(string db)
        {
            return _command.ShowNamespaces(db);
        }

        public void Insert(string db, string ns, BSONObj o)
        {
            _command.Insert(db, ns, o);
        }

        public void Update(string db, string ns, BSONObj o)
        {
            _command.Update(db, ns, o);
        }

        public DjondbCursor Find(string db, string ns, string select, string filter)
        {
            return _command.Find(db, ns, select, filter);
        }

        public void BeginTransaction()
        {
            _command.BeginTransaction();
        }

        public void CommitTransaction()
        {
            _command.CommitTransaction();
        }

        public DjondbCursor ExecuteQuery(string query)
        {
            return _command.ExecuteQuery(query);
        }

        public void ExecuteUpdate(string query)
        {
            _command.ExecuteUpdate(query);
        }

        public bool Remove(string db, string ns, string id, string revision = null)
        {
            return _command.Remove(db, ns, id, revision);
        }

        public int Backup(string db, string location)
        {
            return _command.Backup(db, location);
        }

        public void CreateIndex(BSONObj indexDef)
        {
            _command.CreateIndex(indexDef);
        }

        public bool DropNamespace(string db, string ns)
        {
            return _command.DropNamespace(db, ns);
        }

        public void RollbackTransaction()
        {
            _command.RollbackTransaction();
        }

    }
}
