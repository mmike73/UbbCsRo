using Persistance.Interfaces;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Services.Services
{
    public class AgencyService
    {
        private IAgencyRepository agencyRepository;

        public AgencyService(IAgencyRepository agencyRepository)
        {
            this.agencyRepository = agencyRepository;
        }
    }
}
