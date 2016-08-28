using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Djondb
{
    public class DjondbException : Exception
    {
        private int ResultCode;
        private string ResultMessage;

        public DjondbException(int ResultCode, string ResultMessage)
        {
            this.ResultCode = ResultCode;
            this.ResultMessage = ResultMessage;
        }

        public override string ToString()
        {
            return string.Format("Code: {0}. Error: {1}", ResultCode, ResultMessage);
        }
    }
}
