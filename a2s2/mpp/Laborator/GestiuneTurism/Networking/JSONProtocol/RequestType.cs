using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Networking.JSONProtocol
{
    public enum RequestType
    {
        LOGIN,
        LOGOUT,
        GET_ALL_ECURSIONS,
        GET_ALL_EXCURSIONS_WITH_DESTINATION_BETWEEN,
        GET_ALL_RESERVATIONS_OF_AGENCY,
        ADD_RESERVATION,
        GET_ALL_EXCURSIONS,
        GET_NO_REMAINING_SEATS
    }
}
