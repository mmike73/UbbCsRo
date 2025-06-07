using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Networking.DTO
{
    public class EmployeeDTO
    {
        public int Id { get; set; }
        public string Username { get; set; }
        public string Password { get; set; }

        public int AgencyId { get; set; }
        public string AgencyName { get; set; }

    }
}
