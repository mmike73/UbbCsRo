using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Model;

namespace Services
{
    public interface IObserver
    {
        public void AddedReservation(Reservation reservation);
        public void EmplyeeLoggedIn(Employee employee);
        public void EmplyeeLoggedOut(Employee employee); 

    }
}
