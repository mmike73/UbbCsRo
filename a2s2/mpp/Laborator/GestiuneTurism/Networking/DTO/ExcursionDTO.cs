using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Networking.DTO
{
    public class ExcursionDTO
    {
        public int Id { get; set; }
        public string Attraction { get; set; }
        public string TransportFirm { get; set; }
        public int NoSeats { get; set; }
        public int Price { get; set; }
        public string BoardingDateTime { get; set; }
    }
}
