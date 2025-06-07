using Model;
using Persistance.Interfaces;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Services.Services
{
    public class ReservationService
    {
        private IReservationRepository reservationRepository;

        public ReservationService(IReservationRepository reservationRepository)
        {
            this.reservationRepository = reservationRepository;
        }

        public void AddReservation(Reservation reservation)
        {
            if (reservation != null)
            {
                Reservation? addedReservation = reservationRepository.Save(reservation);
                if (addedReservation == null)
                {
                    throw new Exception("Reservation could not be added!");
                }
            }
        }

        public List<Reservation> FindAllReservaionsWithAgency(Agency agency)
        {
            if (agency == null)
            {
                throw new Exception("Agency is null!");
            }
            return reservationRepository.FindAllReservationsWithAgencyId(agency.Id);
        }
    }
}
