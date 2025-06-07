using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Networking.DTO;

namespace Networking.JSONProtocol
{
    public class Request
    {
        public RequestType Type { get; set; }
        public EmployeeDTO EmployeeDTO { get; set; }
        public AgencyDTO AgencyDTO { get; set; }
        public ReservationDTO ReservationDTO { get; set; }
        public ExcursionDTO ExcursionDTO { get; set; }
        public string attraction { get; set; }
        public string fromDate { get; set; }
        public string toDate { get; set; }

  
    }
}
