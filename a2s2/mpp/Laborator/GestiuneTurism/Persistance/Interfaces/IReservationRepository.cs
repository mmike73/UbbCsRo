﻿using Model;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Persistance.Interfaces
{
    public interface IReservationRepository : IRepository<int, Reservation>
    {
        public List<Reservation> FindAllReservationsWithAgencyId(int id);
    }
}
