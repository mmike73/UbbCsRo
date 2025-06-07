using Model;
using Services;
using Services.Services;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Server
{
    internal class AppController : IController
    {
        private AgencyService AgencyService;
        private EmployeeService EmployeeService;
        private ExcursionService ExcursionService;
        private ReservationService ReservationService;
        private IDictionary<String, IObserver> LoggedClients;

        public AppController(AgencyService agencyService, EmployeeService employeeService, ExcursionService excursionService, ReservationService reservationService)
        {
            this.AgencyService = agencyService;
            this.EmployeeService = employeeService;
            this.ExcursionService = excursionService;
            this.ReservationService = reservationService;
            LoggedClients = new Dictionary<String, IObserver>();
        }

        public void NotifyObserversAddedReservation(Reservation reservation)
        {
            IObserver client;
            foreach (String item in LoggedClients.Keys)
            {
            
                if (LoggedClients.TryGetValue(item, out client))
                {
                    client.AddedReservation(reservation);
                }
            }
        }
        public void AddReservation(Reservation reservation)
        {
            ReservationService.AddReservation(reservation);
            NotifyObserversAddedReservation(reservation);
        }

        public List<Excursion> FindAllExcursions()
        {
            return ExcursionService.FindAllExcursions();
        }

        public List<Excursion> FindAllExcursionWithDestinationBetween(string destination, DateTime date1, DateTime date2)
        {
            return new List<Excursion>();
        }

        public List<Reservation> FindAllReservaionsWithAgency(Agency agency)
        {
            return ReservationService.FindAllReservaionsWithAgency(agency);
        }

        public int GetNoRemainingSeats(Excursion selectedExcursie)
        {
            return ExcursionService.GetNoRemainingSeats(selectedExcursie);
        }

        public Employee? Login(string username, string password, IObserver client)
        {
            try
            {
                Employee? employee = EmployeeService.Login(username, password);
                if (employee != null)
                {
                    if (!LoggedClients.Keys.Contains(username))
                    {
                        LoggedClients[username] = client;
                        return employee;
                    }
                    else
                    {
                        throw new Exception("Employee already logged in!");
                    }
                }
            }
            catch (Exception ex)
            {
                throw new Exception("Invalid username or password!: " + ex.Message);
            }

            throw new Exception("Invalid username or password!");
        }

        public void Logout(string username)
        {
            if (LoggedClients.ContainsKey(username))
            {
                LoggedClients.Remove(username);
                return;
            }
            throw new Exception("User is not logged in!");
        }
    }
}
