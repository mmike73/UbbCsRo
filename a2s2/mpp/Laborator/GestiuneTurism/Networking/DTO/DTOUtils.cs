using Model;
using System;
using System.Collections.Generic;
using System.Text;
using System.Threading.Tasks;
using System.Globalization;

namespace Networking.DTO
{
    public class DTOUtils
    {
        public static EmployeeDTO ToDTO(Employee employee)
        {
            EmployeeDTO dto = new EmployeeDTO();
            dto.Id = employee.Id;
            if (employee.Agency != null)
            {
                dto.AgencyId = employee.Agency.Id;
                dto.AgencyName = employee.Agency.Name;
            }
            dto.Username = employee.Username;
            dto.Password = employee.Password;
            return dto;
        }
        public static Employee GetFromDTO(EmployeeDTO employeeDTO)
        {
            Employee employee = new Employee(
                employeeDTO.Id,
                employeeDTO.Username,
                employeeDTO.Password,
                new Agency(
                    employeeDTO.AgencyId,
                    employeeDTO.AgencyName
                )
            );
            return employee;
        }
        public static AgencyDTO ToDTO(Agency agency)
        {
            AgencyDTO agencyDTO = new AgencyDTO();
            agencyDTO.Id = agency.Id;
            agencyDTO.Name = agency.Name;
            return agencyDTO;
        }
        public static Agency GetFromDTO(AgencyDTO agencyDTO)
        {
            Agency agency = new Agency(
                agencyDTO.Id,
                agencyDTO.Name
            );
            return agency;
        }
        public static ExcursionDTO ToDTO(Excursion excursion) 
        {
            ExcursionDTO dto = new ExcursionDTO();
            dto.Id = excursion.Id;
            dto.Attraction = excursion.Attraction;
            dto.TransportFirm = excursion.TransportFirm;
            dto.NoSeats = excursion.NoSeats;
            dto.Price = excursion.Price;
            dto.BoardingDateTime = excursion.BoardingDateTime.ToString("yyy-MM-dd HH:mm:ss", CultureInfo.InvariantCulture);

            return dto;
        }

        public static Excursion GetFromDTO(ExcursionDTO excursionDTO)
        {
            Excursion excursion = new Excursion(
                excursionDTO.Id,
                excursionDTO.Attraction,
                excursionDTO.TransportFirm,
                excursionDTO.NoSeats,
                excursionDTO.Price,
                DateTime.ParseExact(excursionDTO.BoardingDateTime, "yyyy-MM-dd HH:mm:ss", CultureInfo.InvariantCulture)
            );
            return excursion;
        }
        public static ReservationDTO ToDTO(Reservation reservation)
        {
            ReservationDTO reservationDTO = new ReservationDTO();
            reservationDTO.Id = reservation.Id;
            reservationDTO.ClientName = reservation.ClientName;
            reservationDTO.PhoneNumber = reservation.PhoneNumber;
            reservationDTO.AgencyId = reservation.Agency.Id;
            reservationDTO.AgencyName = reservation.Agency.Name;
            reservationDTO.ExcursionId = reservation.Excursion.Id;
            reservationDTO.Attraction = reservation.Excursion.Attraction;
            reservationDTO.TransportFirm = reservation.Excursion.TransportFirm;
            reservationDTO.NoSeats = reservation.Excursion.NoSeats;
            reservationDTO.Price = reservation.Excursion.Price;
            reservationDTO.BoardingDateTime = reservation.Excursion.BoardingDateTime.ToString("yyyy-MM-dd HH:mm:ss");

            return reservationDTO;
        }
        public static Reservation GetFromDTO(ReservationDTO reservationDTO)
        {
            Reservation reservation = new Reservation(
                reservationDTO.Id,
                reservationDTO.ClientName,
                reservationDTO.PhoneNumber,
                new Agency(
                    reservationDTO.AgencyId,
                    reservationDTO.AgencyName
                ),
                new Excursion(
                    reservationDTO.ExcursionId,
                    reservationDTO.Attraction,
                    reservationDTO.TransportFirm,
                    reservationDTO.NoSeats,
                    reservationDTO.Price,
                    DateTime.ParseExact(reservationDTO.BoardingDateTime, "yyyy-MM-dd HH:mm:ss", CultureInfo.InvariantCulture)
                ),
                reservationDTO.NoBookedSeats
            );
            return reservation;
        }
        public static ExcursionDTO[] ToDTO(List<Excursion> excursionsList)
        {
            ExcursionDTO[] excursions = new ExcursionDTO[excursionsList.Count];

            for (int i = 0; i < excursionsList.Count; i++)
            {
                excursions[i] = ToDTO(excursionsList[i]);
            }
            
            return excursions;
        }
        
        public static List<Excursion> GetFromDTO(ExcursionDTO[] excursionDTOs)
        {
            List<Excursion> excursionList = new List<Excursion>();

            for (int i = 0; i < excursionDTOs.Length; i++)
            {
                excursionList.Add(GetFromDTO(excursionDTOs[i]));
            }

            return excursionList;
        }
        public static ReservationDTO[] ToDTO(List<Reservation> reservationList)
        {
            ReservationDTO[] reservationDTOs = new ReservationDTO[reservationList.Count];

            for (int i = 0; i < reservationList.Count; ++i)
            {
                reservationDTOs[i] = DTOUtils.ToDTO(reservationList[i]);
            }

            return reservationDTOs;
        }
        public static List<Reservation> GetFromDTO(ReservationDTO[] reservationDTOs)
        {
            List<Reservation> reservationList = new List<Reservation>();

            for (int i = 0; i < reservationDTOs.Length; ++i)
            {
                reservationList.Add(GetFromDTO(reservationDTOs[i]));
            }

            return reservationList;
        }
    }
}
