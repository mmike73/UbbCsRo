using Model;
using Networking.DTO;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Networking.JSONProtocol
{
    public class ProtocolUtils
    {
        public static Request CreateLogoutRequest(EmployeeDTO employeeDTO)
        {
            Request request = new Request();
            request.Type = RequestType.LOGOUT;
            request.EmployeeDTO = employeeDTO;
            return request;
        }
        public static Response CreateLogoutResponse()
        {
            Response response = new Response();
            response.Type = ResponseType.OK;
            return response;
        }
        public static Request CreateLoginRequest(EmployeeDTO employee)
        {
            Request request = new Request();
            request.Type = RequestType.LOGIN;
            request.EmployeeDTO = employee;
            return request;
        }

        public static Response CreateLoginResponse(EmployeeDTO employee)
        {
            Response response = new Response();
            response.Type = ResponseType.OK;
            response.EmployeeDTO = employee;
            return response;
        }
        public static Request CreateFindAllExcursionsRequest()
        {
            Request request = new Request();
            request.Type = RequestType.GET_ALL_EXCURSIONS;
            return request;
        }
        public static Response CreateFindAllExcursionsResponse(ExcursionDTO[] excursions)
        {
            Response response = new Response();
            response.Type = ResponseType.OK;
            response.ExcursionDTOs = excursions;
            return response;
        }
        public static Request CreateFindAllReservationsOfAgencyRequest(AgencyDTO agency)
        {
            Request request = new Request();
            request.Type = RequestType.GET_ALL_RESERVATIONS_OF_AGENCY;
            request.AgencyDTO = agency;
            return request;
        }
        public static Response CreateFindAllReservationsOfAgencyResponse(ReservationDTO[] reservations)
        {
            Response response = new Response();
            response.Type = ResponseType.OK;
            response.ReservationDTOs = reservations;
            return response;
        }
        public static Response CreateErrorResponse(string error)
        {
            Response response = new Response();
            response.Type= ResponseType.ERROR;
            response.ErrorMessage = error;
            return response;
        }

        public static Request CreateAddReservationRequest(Reservation reservation)
        {
            Request request = new Request();
            request.Type = RequestType.ADD_RESERVATION;
            request.ReservationDTO = DTOUtils.ToDTO(reservation);
            return request;
        }

        public static Response CreateAddReservationResponse()
        {
            Response response = new Response();
            response.Type = ResponseType.OK;
            return response;
        }

        internal static Response CreateGetNoRemainingSeatsResponse(int noRemainingSeats)
        {
            Response response = new Response();
            response.Type = ResponseType.OK;
            response.NoRemainingSeats = noRemainingSeats;
            return response;
        }

        internal static Request CreateGetNoRemainingSeatsRequest(ExcursionDTO excursionDTO)
        {
            Request request = new Request();
            request.Type = RequestType.GET_NO_REMAINING_SEATS;
            request.ExcursionDTO = excursionDTO;
            return request;
        }

        internal static Response CreateBroadcastReservationResponse(ReservationDTO reservation)
        {
            Response response = new Response();
            response.Type = ResponseType.BROADCAST_UPDATE;
            response.ReservationDTO = reservation;
            return response;
        }
    }
}
