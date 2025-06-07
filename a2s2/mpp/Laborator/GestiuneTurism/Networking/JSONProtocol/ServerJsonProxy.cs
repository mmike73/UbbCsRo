using log4net;
using Model;
using Networking.DTO;
using Services;
using Services.Services;
using System.Net.Sockets;
using System.Text;
using System.Text.Json;

namespace Networking.JSONProtocol
{
    public class ServerJsonProxy : IController
    {
        private string host;
        private int port;

        private IObserver client;
        private NetworkStream stream;
        private TcpClient connection;
        private Queue<Response> responses;
        private volatile bool finished;
        private EventWaitHandle _waitHandle;
        private static readonly ILog log = LogManager.GetLogger(typeof(ServerJsonProxy));

        public ServerJsonProxy(string host, int port)
        {
            this.host = host;
            this.port = port;
            responses = new Queue<Response>();
        }

        private void closeConnection()
        {
            finished = true;
            try
            {
                stream.Close();
                connection.Close();
                _waitHandle.Close();
                client = null;
            }
            catch (Exception e)
            {
                Console.WriteLine(e.StackTrace);
            }
        }

        private void sendRequest(Request request)
        {
            try
            {
                lock (stream)
                {

                    string jsonRequest = JsonSerializer.Serialize(request);
                    log.DebugFormat("Sending request {0}", jsonRequest);
                    byte[] data = Encoding.UTF8.GetBytes(jsonRequest + "\n"); // Append newline 
                    stream.Write(data, 0, data.Length);
                    stream.Flush();

                }
            }
            catch (Exception e)
            {
                throw new Exception("Error sending object " + e);
            }

        }

        private Response readResponse()
        {
            Response response = null;
            try
            {
                _waitHandle.WaitOne();
                lock (responses)
                {
                    response = responses.Dequeue();

                }
            }
            catch (Exception e)
            {
                Console.WriteLine(e.StackTrace);
            }
            return response;
        }
        private void initializeConnection()
        {
            try
            {
                connection = new TcpClient(host, port);
                stream = connection.GetStream();
                finished = false;
                _waitHandle = new AutoResetEvent(false);
                startReader();
            }
            catch (Exception e)
            {
                Console.WriteLine(e.StackTrace);
            }
        }
        private void startReader()
        {
            Thread tw = new Thread(run);
            tw.Start();
        }

        private void handleUpdate(Response response)
        {
            if (response.Type == ResponseType.BROADCAST_UPDATE)
            {
                Reservation addedReservation = DTOUtils.GetFromDTO(response.ReservationDTO);
                client.AddedReservation(addedReservation);
            }
        }

        private bool isUpdate(Response response)
        {
            return response.Type == ResponseType.BROADCAST_UPDATE;
        }

        public virtual void run()
        {
            using StreamReader reader = new StreamReader(stream, Encoding.UTF8);
            while (!finished)
            {
                try
                {
                    string responseJson = reader.ReadLine();
                    if (string.IsNullOrEmpty(responseJson))
                        continue; //nu s-a citit un raspuns valid
                    Response response = JsonSerializer.Deserialize<Response>(responseJson);
                    log.Debug("response received " + response);
                    if (isUpdate(response))
                    {
                        handleUpdate(response);
                    }
                    else
                    {
                        lock (responses)
                        {
                            responses.Enqueue(response);
                        }
                        _waitHandle.Set();
                    }
                }
                catch (Exception e)
                {
                    log.Error("Reading error " + e);
                }

            }
        }

        public List<Excursion> FindAllExcursions()
        {
            log.Info("FindAllExcursions");

            sendRequest(ProtocolUtils.CreateFindAllExcursionsRequest());

            Response response = readResponse();

            if (response.Type == ResponseType.ERROR)
            {
                throw new TourismException(response.ErrorMessage);
            }

            List<Excursion> excursionList = DTOUtils.GetFromDTO(response.ExcursionDTOs);

            return excursionList;
        }

        public Employee? Login(string username, string password, IObserver client)
        {
            log.Info($"Login {username}");
            initializeConnection();
            sendRequest(ProtocolUtils.CreateLoginRequest(DTOUtils.ToDTO(new Employee(username, password, new Agency(1,"")))));
            Response response = readResponse();

            if (response.Type == ResponseType.OK)
            {
                this.client = client;
                return DTOUtils.GetFromDTO(response.EmployeeDTO);
            }
            if (response.Type == ResponseType.ERROR)
            {
                String err = response.ErrorMessage;
                closeConnection();
                throw new TourismException(err);
            }

            return null;
        }

        public void Logout(string username)
        {
            log.Info($"Logout {username}");
            sendRequest(ProtocolUtils.CreateLogoutRequest(DTOUtils.ToDTO(new Employee(username, "", new Agency(1, "")))));
            Response resp = readResponse();
            if (resp.Type == ResponseType.OK)
            {
                this.client = null;
                closeConnection();
                return;
            }

            if (resp.Type == ResponseType.ERROR)
            {
                throw new TourismException(resp.ErrorMessage);
            }
        }

        public List<Excursion> FindAllExcursionWithDestinationBetween(string destination, DateTime date1, DateTime date2)
        {
            log.Info($"FindAllExcursionWithDestinationBetween {destination} {date1} {date2}");
            return new List<Excursion>();
        }

        public void AddReservation(Reservation reservation)
        {
            log.Info($"AddReservation {reservation.ClientName} {reservation.PhoneNumber}");
            sendRequest(ProtocolUtils.CreateAddReservationRequest(reservation));
            Response response = readResponse();

            if (response.Type == ResponseType.OK)
            {
                log.Info("Response added successfully!");
            }
            if (response.Type == ResponseType.ERROR)
            {
                throw new TourismException(response.ErrorMessage);
            }
        }

        public List<Reservation> FindAllReservaionsWithAgency(Agency agency)
        {
            log.Info($"FindAllReservationsWithAgency {agency.Name}");
            sendRequest(ProtocolUtils.CreateFindAllReservationsOfAgencyRequest(DTOUtils.ToDTO(agency)));
            Response resp = readResponse();
            if (resp.Type == ResponseType.OK)
            {
                List<Reservation> reservationList = DTOUtils.GetFromDTO(resp.ReservationDTOs);
                return reservationList;
            }
            if (resp.Type == ResponseType.ERROR)
            {
                throw new TourismException(resp.ErrorMessage);
            }
            return new List<Reservation>();
        }

        public int GetNoRemainingSeats(Excursion excursion)
        {
            log.Info("Getting no remaining seats for " + excursion.Attraction);
            sendRequest(ProtocolUtils.CreateGetNoRemainingSeatsRequest(DTOUtils.ToDTO(excursion)));
            Response response = readResponse();
            if (response.Type == ResponseType.OK)
            {
                int noRemainingSeats = response.NoRemainingSeats;
                return noRemainingSeats;
            }
            if (response.Type == ResponseType.ERROR)
            {
                throw new TourismException(response.ErrorMessage);
            }
            return -1;
        }


    }
}
