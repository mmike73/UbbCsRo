using log4net;
using Model;
using Networking.DTO;
using Services;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Text.Json;
using System.Threading.Tasks;

namespace Networking.JSONProtocol
{
    public class ClientJsonWorker : IObserver
    {
        private IController server;
        private TcpClient connection;

        private NetworkStream stream;
        private volatile bool connected;
        private static readonly ILog log = LogManager.GetLogger(typeof(ClientJsonWorker));

        public ClientJsonWorker(IController server, TcpClient connection)
        {
            this.server = server;
            this.connection = connection;

            try
            {
                stream = connection.GetStream();
                connected = true;
            }
            catch (Exception e)
            {
                log.Error(e.StackTrace);
            }
        }

        public virtual void run()
        {
            using StreamReader reader = new StreamReader(stream, Encoding.UTF8);
            while (connected)
            {
                try
                {
                    string requestJson = reader.ReadLine(); // Read JSON line-by-line
                    if (string.IsNullOrEmpty(requestJson)) continue;
                    log.DebugFormat("Received json request {0}", requestJson);
                    Request request = JsonSerializer.Deserialize<Request>(requestJson);
                    log.DebugFormat("Deserializaed Request {0} ", request);
                    Response response = handleRequest(request);
                    if (response != null)
                    {
                        sendResponse(response);
                    }
                }
                catch (Exception e)
                {
                    log.ErrorFormat("run eroare {0}", e.Message);
                    if (e.InnerException != null)
                        log.ErrorFormat("run inner error {0}", e.InnerException.Message);
                    log.Error(e.StackTrace);
                }

                try
                {
                    Thread.Sleep(1000);
                }
                catch (Exception e)
                {
                    log.Error(e.StackTrace);
                }
            }
            try
            {
                stream.Close();
                connection.Close();
            }
            catch (Exception e)
            {
                log.Error("Error " + e);
            }
        }

        private Response handleRequest(Request request)
        {
            Response response = null;
            if (request.Type == RequestType.LOGIN)
            {
                log.Debug("Login request ...");
                if (request.EmployeeDTO != null)
                {
                    Employee user = DTOUtils.GetFromDTO(request.EmployeeDTO);
                    try
                    {
                        Employee loggedUser = null;
                        lock (server)
                        {
                            loggedUser = server.Login(user.Username, user.Password, this);
                        }

                        if (loggedUser != null)
                        {
                            return ProtocolUtils.CreateLoginResponse(DTOUtils.ToDTO(loggedUser));
                        }

                        return ProtocolUtils.CreateErrorResponse("Login error!");
                    }
                    catch (TourismException ex)
                    {
                        connected = false;
                        return ProtocolUtils.CreateErrorResponse(ex.Message);
                    }
                    catch (Exception ex)
                    {
                        connected = false;
                        return ProtocolUtils.CreateErrorResponse(ex.Message);
                    }
                }
            }
                if (request.Type == RequestType.LOGOUT)
                {
                    Employee user = DTOUtils.GetFromDTO(request.EmployeeDTO);
                    try
                    {
                        if (user != null && user.Username != null)
                        {
                            server.Logout(user.Username);
                            return ProtocolUtils.CreateLogoutResponse();
                        }
                        else
                        {
                            return ProtocolUtils.CreateErrorResponse("User couldn't be logged out - username missing!");
                        }
                    }
                    catch (TourismException ex)
                    {
                        connected = false;
                        return ProtocolUtils.CreateErrorResponse(ex.Message);
                    }
                }
                if (request.Type == RequestType.GET_ALL_EXCURSIONS)
                {
                    try
                    {
                        List<Excursion> excursions = server.FindAllExcursions();
                        return ProtocolUtils.CreateFindAllExcursionsResponse(DTOUtils.ToDTO(excursions));
                    }
                    catch(Exception ex)
                    {
                        return ProtocolUtils.CreateErrorResponse(ex.Message);
                    }
                }
            if (request.Type == RequestType.GET_ALL_RESERVATIONS_OF_AGENCY)
            {
                log.Info("Received getReservation request");
                Agency? agency = DTOUtils.GetFromDTO(request.AgencyDTO);
                try
                {
                    if (agency != null)
                    {
                        List<Reservation> reservationList = server.FindAllReservaionsWithAgency(agency);
                        return ProtocolUtils.CreateFindAllReservationsOfAgencyResponse(DTOUtils.ToDTO(reservationList));
                    }
                }
                catch (Exception ex)
                {
                    return ProtocolUtils.CreateErrorResponse(ex.Message);
                }
            }
            if (request.Type == RequestType.ADD_RESERVATION)
            {
                Reservation? reservation = DTOUtils.GetFromDTO(request.ReservationDTO);
                try
                {
                    if (reservation != null)
                    {
                        server.AddReservation(reservation);
                        return ProtocolUtils.CreateAddReservationResponse();
                    }
                } catch (Exception ex)
                {
                    return ProtocolUtils.CreateErrorResponse(ex.Message);
                }
            }
            if (request.Type == RequestType.GET_NO_REMAINING_SEATS)
            {
                Excursion? excursion = DTOUtils.GetFromDTO(request.ExcursionDTO);
                try
                {
                    if (excursion == null) throw new Exception("Excursion is null in worker!");
                    int noRemainingSeats = server.GetNoRemainingSeats(excursion);
                    return ProtocolUtils.CreateGetNoRemainingSeatsResponse(noRemainingSeats);
                }
                catch (Exception ex)
                {
                    return ProtocolUtils.CreateErrorResponse(ex.Message);
                }

            }
            return response;
        }

        private void sendResponse(Response response)
        {
            //de modificat pentru json
            String jsonString = JsonSerializer.Serialize(response);
            log.DebugFormat("sending response {0}", jsonString);
            lock (stream)
            {
                byte[] data = Encoding.UTF8.GetBytes(jsonString + "\n"); // Append newline 
                stream.Write(data, 0, data.Length);
                stream.Flush();
            }

        }

        public void AddedReservation(Reservation reservation)
        {
            log.Info("BRoadcasting update");
            try
            {
                sendResponse(ProtocolUtils.CreateBroadcastReservationResponse(DTOUtils.ToDTO(reservation)));
            }
            catch (Exception ex)
            {
                log.Error(ex.Message);
            }
        }

        public void EmplyeeLoggedIn(Employee employee)
        {
            throw new NotImplementedException();
        }

        public void EmplyeeLoggedOut(Employee employee)
        {
            throw new NotImplementedException();
        }
    }
}
