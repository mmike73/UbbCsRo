using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Networking.JSONProtocol
{
    public enum ResponseType
    {
        LOGIN,
        LOGOUT,
        OK,
        ERROR,
        BROADCAST_UPDATE,
        ADD_RESERVATION
    }
}
