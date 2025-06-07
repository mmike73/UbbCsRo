using System;
using System.Collections.Generic;
using System.Configuration;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Networking.DTO
{
    public class ReservationDTO
    {
        public int Id { get; set; }
        public string ClientName { get; set; }
        public string PhoneNumber { get; set; }
        public int NoBookedSeats  { get; set; }

        public int ExcursionId { get; set; }
        public string Attraction {  get; set; }
        public string TransportFirm { get; set; }
        public int NoSeats { get; set; }
        public int Price {  get; set; }
        public string BoardingDateTime { get; set; }
        public int AgencyId { get; set; }
        public string AgencyName { get; set; }

    }
}
