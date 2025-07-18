﻿using Model;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Persistance.Interfaces
{
    public interface IExcursionRepository : IRepository<int, Excursion>
    {
        public int? GetNoOccupiedSeats(Excursion excursion);
    }
}
