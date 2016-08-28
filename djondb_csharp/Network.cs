using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace Djondb
{
    class Network
    {
        private System.Net.Sockets.TcpClient _client;
        private MemoryStream _stream = new MemoryStream();
        private int BufferLen;
        private int BufferPos;

        public Network(System.Net.Sockets.TcpClient client)
        {
            // TODO: Complete member initialization
            this._client = client;
            BufferLen = 0;
            BufferPos = 0;
        }

        public void WriteHeader()
        {
            string version = "3.5.60827";
            WriteString(version);
        }

        public void WriteString(string version)
        {
            WriteInt32(version.Length);
            byte[] data = System.Text.UTF8Encoding.UTF8.GetBytes(version);
            _stream.Write(data, 0, data.Length);
            BufferPos += data.Length;
            BufferLen += data.Length;
        }

        public void WriteInt32(int p)
        {
            byte[] b = new byte[4];
            b[0] = (byte)p;
            b[1] = (byte)(((uint)p >> 8) & 0xFF);
            b[2] = (byte)(((uint)p >> 16) & 0xFF);
            b[3] = (byte)(((uint)p >> 24) & 0xFF);
            _stream.Write(b, 0, 4);
            BufferLen += 4;
            BufferPos += 4;
        }

        private void WriteLong(Int64 p)
        {
            byte[] b = BitConverter.GetBytes(p);
            _stream.Write(b, 0, 8);
            BufferLen += 8;
            BufferPos += 8;
        }

        internal void WriteBSON(BSONObj bSONObj)
        {
            WriteLong(bSONObj.Count);

            foreach (KeyValuePair<string, object> kv in bSONObj)
            {
                WriteString(kv.Key);
                object val = kv.Value;
                Int32? i = val as Int32?;
                if (i != null)
                {
                    WriteLong(0);
                    WriteInt32((int)i);
                }
                else
                {
                    long? l = val as long?;
                    if (l != null)
                    {
                        WriteLong(2);
                        WriteLong((long)l);
                    }
                    else
                    {
                        float? f = val as float?;
                        if (f != null)
                        {
                            WriteLong(1);
                            WriteDouble(Convert.ToDouble(f));
                        }
                        else
                        {
                            string s = val as string;
                            if (s != null)
                            {
                                WriteLong(4);
                                WriteString(s);
                            }
                            else
                            {
                                BSONObj bObj = val as BSONObj;
                                if (bObj != null)
                                {
                                    WriteLong(5);
                                    WriteBSON(bObj);
                                }
                                else
                                {
                                    bool? b = val as bool?;
                                    if (b != null)
                                    {
                                        WriteLong(10);
                                        WriteBoolean((bool)b);
                                    }
                                    else
                                    {
                                        BSONArrayObj ar = val as BSONArrayObj;
                                        if (ar != null)
                                        {
                                            WriteLong(6);
                                            WriteBSONArray(ar);
                                        }
                                        else
                                        {
                                            double? d = val as double?;
                                            if (d != null)
                                            {
                                                WriteLong(1);
                                                WriteDouble((double)d);
                                            }
                                            else
                                            {
                                                throw new ApplicationException("Unknown data type");
                                            }
                                        }
                                    }

                                }
                            }
                        }
                    }
                }
            }
        }

        private void WriteBSONArray(BSONArrayObj ar)
        {
            long elements = ar.Count;
            WriteLong(elements);
            foreach (BSONObj o in ar)
            {
                WriteBSON(o);
            }
        }

        private void WriteBoolean(bool p)
        {
            byte[] b = new byte[1];
            b[0] = p ? (byte)1 : (byte)0;
            _stream.Write(b, 0, 1);
        }

        void WriteDouble(double p)
        {
            byte[] data = BitConverter.GetBytes(p);

            _stream.Write(data, 0, data.Length);
        }

        internal void Flush()
        {
            byte[] data = _stream.ToArray();
            _client.GetStream().Write(data, 0, data.Length);
            Reset();
        }

        public void Reset()
        {
            _stream = new MemoryStream();
            BufferLen = 0;
            BufferPos = 0;
        }

        public BSONArrayObj ReadBSONArray()
        {
            long elements = ReadLong();

            BSONArrayObj res = new BSONArrayObj();
            for (long x = 0; x < elements; x++)
            {
                BSONObj o = ReadBSON();
                res.Add(o);
            }
            return res;
        }

        public BSONObj ReadBSON()
        {
            BSONObj o = new BSONObj();
            long elements = ReadLong();

            for (long x = 0; x < elements; x++)
            {
                string key = ReadString();
                long type = ReadLong();
                switch (type)
                {
                    case 0:
                        o.add(key, ReadInt32());
                        break;
                    case 1:
                        o.add(key, ReadDouble());
                        break;
                    case 2:
                        o.add(key, ReadLong());
                        break;
                    case 4:
                        o.add(key, ReadString());
                        break;
                    case 5:
                        o.add(key, ReadBSON());
                        break;
                    case 6:
                        o.add(key, ReadBSONArray());
                        break;
                    case 10:
                        o.add(key, ReadBoolean());
                        break;
                    default:
                        throw new ApplicationException("Type not supported");
                }
            }
            return o;
        }

        public bool ReadBoolean()
        {
            CheckAvailable(1);
            byte[] data = new byte[1];
            this._stream.Read(data, 0, 1);

            return data[0] == 1 ? true : false;
        }

        private double ReadDouble()
        {
            CheckAvailable(8);
            byte[] data = new byte[8];
            this._stream.Read(data, 0, 8);

            return BitConverter.ToDouble(data, 0);
        }

        private long ReadLong()
        {
            CheckAvailable(8);
            byte[] data = new byte[8];

            this._stream.Read(data, 0, 8);
            long res = BitConverter.ToInt64(data, 0);

            return res;
        }

        internal int ReadInt32()
        {
            CheckAvailable(4);
            byte[] data = new byte[4];
            _stream.Read(data, 0, 4);

            int result = (data[3] << 24)
                         | (data[2] << 16)
                         | (data[1] << 8)
                         | data[0];

            return result;
        }

        private void CheckAvailable(int p)
        {
            if ((BufferLen - BufferPos) < p)
            {
                byte[] buffer = new byte[1024*100];
                int readed = _client.GetStream().Read(buffer, 0, 1024*100);
                long pos = _stream.Position;
                _stream.Seek(0, SeekOrigin.End);
                _stream.Write(buffer, 0, readed);
                _stream.Seek(pos, SeekOrigin.Begin);
                BufferLen += readed;
            }
        }

        internal string ReadString()
        {
            int len = ReadInt32();
            byte[] data = new byte[len];
            _stream.Read(data, 0, len);
            string result = System.Text.UTF8Encoding.UTF8.GetString(data);
            BufferPos += len;
            return result;
        }

    }
}