using log4net;
using Model;
using Npgsql;
using Persistance.Interfaces;
using System;
using System.Collections.Generic;
using System.Data;
using System.Data.Common;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Persistance.Implementations
{
    public class ExcursionRepository : IExcursionRepository
    {
        IDictionary<String, string> props;
        private static readonly ILog log = LogManager.GetLogger(typeof(AgencyRepository));

        public ExcursionRepository(IDictionary<String, string> props)
        {
            this.props = props;
        }

        public Excursion? FindById(int id)
        {
            log.Info($"Finding excursie {id}");
            const string query = "SELECT * FROM \"Excursii\" WHERE \"excursieId\" = @id";

            try
            {
                using var connection = DbConnection.GetConnection(props);
                connection.Open();
                using var command = new NpgsqlCommand(query, connection);
                command.Parameters.AddWithValue("@id", id);

                using var reader = command.ExecuteReader();
                if (!reader.Read()) return null;

                return new Excursion(
                    reader.GetInt32("excursieId"),
                    reader.GetString("obiectiv"),
                    reader.GetString("firmaTransport"),
                    reader.GetInt32("nrLocuri"),
                    reader.GetInt32("pret"),
                    reader.GetDateTime("dataOraPlecare")
                );
            }
            catch (Exception e)
            {
                log.Error(e.Message);
            }
            return null;
        }

        public List<Excursion> FindAll()
        {
            log.Info("Fetching all excursii");
            const string query = "SELECT * FROM \"Excursii\"";
            var excursii = new List<Excursion>();

            try
            {
                using var connection = DbConnection.GetConnection(props);
                connection.Open();
                using var command = new NpgsqlCommand(query, connection);
                using var reader = command.ExecuteReader();

                while (reader.Read())
                {
                    excursii.Add(new Excursion(
                        reader.GetInt32("excursieId"),
                        reader.GetString("obiectiv"),
                        reader.GetString("firmaTransport"),
                        reader.GetInt32("nrLocuri"),
                        reader.GetInt32("pret"),
                        reader.GetDateTime("dataOraPlecare")
                    ));
                }
            }
            catch (Exception ex)
            {
                log.Error(ex);
            }

            return excursii;
        }

        public Excursion? Save(Excursion entity)
        {
            log.Info($"Saving excursie: {entity.Attraction}");
            const string query = "INSERT INTO \"Excursii\" (obiectiv, \"firmaTransport\", \"nrLocuri\", \"pret\", \"dataOraPlecare\") " +
                                 "VALUES (@obiectiv, @firmaTransport, @nrLocuri, @pret, @dataOraPlecare) RETURNING \"excursieId\"";

            try
            {
                using var connection = DbConnection.GetConnection(props);
                connection.Open();
                using var command = new NpgsqlCommand(query, connection);
                command.Parameters.AddWithValue("@obiectiv", entity.Attraction);
                command.Parameters.AddWithValue("@firmaTransport", entity.TransportFirm);
                command.Parameters.AddWithValue("@nrLocuri", entity.NoSeats);
                command.Parameters.AddWithValue("@pret", entity.Price);
                command.Parameters.AddWithValue("@dataOraPlecare", entity.BoardingDateTime);

                var newId = command.ExecuteScalar();
                if (newId == null) return null;

                entity.Id = Convert.ToInt32(newId);
                return entity;
            }
            catch (Exception ex)
            {
                log.Error(ex);
                Console.WriteLine(ex.Message);
            }

            return null;
        }

        public Excursion? Delete(int id)
        {
            log.Info($"Deleting excursie with id {id}");
            var excursie = FindById(id);
            if (excursie == null) return null;

            const string query = "DELETE FROM \"Excursii\" WHERE \"excursieId\" = @id";

            using var connection = DbConnection.GetConnection(props);
            connection.Open();
            using var command = new NpgsqlCommand(query, connection);
            command.Parameters.AddWithValue("@id", id);
            command.ExecuteNonQuery();

            return excursie;
        }

        public Excursion? Update(Excursion entity)
        {
            log.Info($"Updating excursie: {entity.Attraction}");
            const string query = "UPDATE \"Excursii\" SET obiectiv = @obiectiv, \"firmaTransport\" = @firmaTransport, " +
                                 "\"nrLocuri\" = @nrLocuri, \"pret\" = @pret, \"dataOraPlecare\" = @dataOraPlecare " +
                                 "WHERE \"excursieId\" = @id";

            using var connection = DbConnection.GetConnection(props);
            connection.Open();
            using var command = new NpgsqlCommand(query, connection);
            command.Parameters.AddWithValue("@obiectiv", entity.Attraction);
            command.Parameters.AddWithValue("@firmaTransport", entity.TransportFirm);
            command.Parameters.AddWithValue("@nrLocuri", entity.NoSeats);
            command.Parameters.AddWithValue("@pret", entity.Price);
            command.Parameters.AddWithValue("@dataOraPlecare", entity.BoardingDateTime);
            command.Parameters.AddWithValue("@id", entity.Id);

            int rowsAffected = command.ExecuteNonQuery();
            return rowsAffected > 0 ? entity : null;
        }

        public int? GetNoOccupiedSeats(Excursion excursion)
        {
            log.Info($"Gettig number of remaining seats");
            const string query = "SELECT SUM(\"nrLocuriRezervate\") AS locuri_ramase FROM \"Rezervari\" WHERE \"excursieId\" = @id";

            using var connection = DbConnection.GetConnection(props);
            connection.Open();
            using var command = new NpgsqlCommand(query, connection);
            command.Parameters.AddWithValue("@id", excursion.Id);

            var reader = command.ExecuteReader();

            if (reader.Read())
            {
                return reader.GetInt32("locuri_ramase");
            }

            throw new Exception("COuld not get No Occupied Seats!");
        }
    }
}
