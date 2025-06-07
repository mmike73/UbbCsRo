using Model;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Services
{
    public interface IController
    {
        List<Excursion> FindAllExcursions();
        Employee? Login(string username, string password, IObserver client);
        void Logout(string username);
        List<Excursion> FindAllExcursionWithDestinationBetween(string destination, DateTime date1, DateTime date2);
        int GetNoRemainingSeats(Excursion selectedExcursie);
        void AddReservation(Reservation reservation);
        List<Reservation> FindAllReservaionsWithAgency(Agency agency);
    }
}
