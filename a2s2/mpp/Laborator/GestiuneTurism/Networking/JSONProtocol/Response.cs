using Networking.DTO;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Networking.JSONProtocol
{
    public class Response
    {
        public ResponseType Type { get; set; }
        public EmployeeDTO EmployeeDTO { get; set; }
        public string ErrorMessage { get; set; }
        public ExcursionDTO[] ExcursionDTOs { get; set; }
        public ReservationDTO[] ReservationDTOs { get; set; }
        public int NoRemainingSeats { get; set; }
        public ReservationDTO ReservationDTO { get; set; }
    }
}
