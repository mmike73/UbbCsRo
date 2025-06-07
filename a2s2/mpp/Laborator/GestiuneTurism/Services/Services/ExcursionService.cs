using Model;
using Persistance.Interfaces;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Services.Services
{
    public class ExcursionService
    {
        private IExcursionRepository excursionRepository;

        public ExcursionService(IExcursionRepository excursionRepository)
        {
            this.excursionRepository = excursionRepository;
        }

        public List<Excursion> FindAllExcursions()
        {
            return excursionRepository.FindAll();
        }

        public int GetNoRemainingSeats(Excursion excursion)
        {
            Excursion notModified = excursionRepository.FindById(excursion.Id);
            int? noOccupiedSeats = excursionRepository.GetNoOccupiedSeats(excursion);
            if (noOccupiedSeats == null)
            {
                throw new Exception("Could not get No Ocupied seats in service");
            }
            int noS = (int)noOccupiedSeats;
            return notModified.NoSeats - noS;
        }
    }
}
