using log4net;
using Model;
using Npgsql;
using Persistance.Interfaces;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Persistance.Implementations
{
    public class ReservationRepository : IReservationRepository
    {
        IDictionary<String, string> props;
        private static readonly ILog log = LogManager.GetLogger(typeof(AgencyRepository));

        public ReservationRepository(IDictionary<String, string> props)
        {
            this.props = props;
        }

        public Reservation? FindById(int id)
        {
            log.Info($"Rezervare {id}");

            const string query = "SELECT * FROM \"Rezervari\" WHERE \"rezervareId\" = @id";
            try
            {
                using var connection = DbConnection.GetConnection(props);
                connection.Open();
                using var command = new NpgsqlCommand(query, connection);
                command.Parameters.AddWithValue("@id", id);
                using var reader = command.ExecuteReader();

                if (reader.Read())
                {
                    var rezervare = new Reservation(
                        reader.GetInt32(reader.GetOrdinal("rezervareId")),
                        reader.GetString(reader.GetOrdinal("numeClient")),
                        reader.GetString(reader.GetOrdinal("telefon")),
                        null,
                        null,
                        reader.GetInt32(reader.GetOrdinal("nrLocuriRezervate"))

                    );

                    int agentieId = reader.GetInt32(reader.GetOrdinal("agentieId"));

                    const string queryAgentie = "SELECT * FROM \"AgentiiTurism\" WHERE \"agentieId\" = @id";
                    using var connectionAgentie = DbConnection.GetConnection(props);
                    using var commandAgentie = new NpgsqlCommand(queryAgentie, connectionAgentie);
                    command.Parameters.AddWithValue("@id", agentieId);
                    using var readerAgentie = commandAgentie.ExecuteReader();

                    Agency? agentie = null;

                    if (readerAgentie.Read())
                    {
                        agentie = new Agency(
                            agentieId,
                            readerAgentie.GetString(readerAgentie.GetOrdinal("numeAgentie"))
                        );
                        rezervare.Agency = agentie;
                    }

                    int excursieId = reader.GetInt32(reader.GetOrdinal("excursieId"));

                    const string queryExcursie = "SELECT * FROM \"Excursii\" WHERE \"excursieId\" = @id";
                    using var connectionExcursie = DbConnection.GetConnection(props);
                    using var commandExcursie = new NpgsqlCommand(queryExcursie, connectionExcursie);
                    command.Parameters.AddWithValue("@id", excursieId);
                    using var readerExcursie = commandExcursie.ExecuteReader();

                    Excursion? excursie = null;

                    if (readerExcursie.Read())
                    {
                        excursie = new Excursion(
                            readerExcursie.GetInt32(readerExcursie.GetOrdinal("excursieId")),
                            readerExcursie.GetString(readerExcursie.GetOrdinal("obiectiv")),
                            readerExcursie.GetString(readerExcursie.GetOrdinal("firmaTransport")),
                            readerExcursie.GetInt32(readerExcursie.GetOrdinal("nrLocuri")),
                            readerExcursie.GetInt32(readerExcursie.GetOrdinal("pret")),
                            readerExcursie.GetDateTime(readerExcursie.GetOrdinal("dataOraPlecare"))
                        );
                        rezervare.Excursion = excursie;
                    }

                    return rezervare;
                }
            }
            catch (Exception ex)
            {
                log.Error(ex);
                Console.WriteLine(ex);
            }

            return null;
        }

        public List<Reservation> FindAll()
        {
            log.Info($"RezervareRepository");

            const string queryRezervari = "SELECT * FROM \"Rezervari\"";
            var rezervari = new List<Reservation>();

            try
            {
                using var connection = DbConnection.GetConnection(props);
                connection.Open();
                using var commandRezervari = new NpgsqlCommand(queryRezervari, connection);
                using var readerRezervari = commandRezervari.ExecuteReader();

                while (readerRezervari.Read())
                {
                    var rezervare = new Reservation(
                        readerRezervari.GetInt32(readerRezervari.GetOrdinal("rezervareId")),
                        readerRezervari.GetString(readerRezervari.GetOrdinal("numeClient")),
                        readerRezervari.GetString(readerRezervari.GetOrdinal("telefon")),
                        null,
                        null,
                        readerRezervari.GetInt32(readerRezervari.GetOrdinal("nrLocuriRezervate"))
                    );

                    // Retrieve associated AgentieTurism
                    int agentieId = readerRezervari.GetInt32(readerRezervari.GetOrdinal("agentieId"));
                    const string queryAgentie = "SELECT * FROM \"AgentiiTurism\" WHERE \"agentieId\" = @id";
                    using (var connectionAgentie = DbConnection.GetConnection(props))
                    {
                        connectionAgentie.Open();
                        using (var commandAgentie = new NpgsqlCommand(queryAgentie, connectionAgentie))
                        {
                            commandAgentie.Parameters.AddWithValue("@id", agentieId);
                            using (var readerAgentie = commandAgentie.ExecuteReader())
                            {
                                if (readerAgentie.Read())
                                {
                                    var agentie = new Agency(
                                        agentieId,
                                        readerAgentie.GetString(readerAgentie.GetOrdinal("numeAgentie"))
                                    );
                                    rezervare.Agency = agentie;
                                }
                            }
                        }
                    }

                    // Retrieve associated Excursie
                    int excursieId = readerRezervari.GetInt32(readerRezervari.GetOrdinal("excursieId"));
                    const string queryExcursie = "SELECT * FROM \"Excursii\" WHERE \"excursieId\" = @id";
                    using (var connectionExcursie = DbConnection.GetConnection(props))
                    {
                        connectionExcursie.Open();
                        using (var commandExcursie = new NpgsqlCommand(queryExcursie, connectionExcursie))
                        {
                            commandExcursie.Parameters.AddWithValue("@id", excursieId);
                            using (var readerExcursie = commandExcursie.ExecuteReader())
                            {
                                if (readerExcursie.Read())
                                {
                                    var excursie = new Excursion(
                                        readerExcursie.GetInt32(readerExcursie.GetOrdinal("excursieId")),
                                        readerExcursie.GetString(readerExcursie.GetOrdinal("obiectiv")), 
                                        readerExcursie.GetString(readerExcursie.GetOrdinal("firmaTransport")),
                                        readerExcursie.GetInt32(readerExcursie.GetOrdinal("nrLocuri")),
                                        readerExcursie.GetInt32(readerExcursie.GetOrdinal("pret")),
                                        readerExcursie.GetDateTime(readerExcursie.GetOrdinal("dataOraPlecare"))
                                    );
                                    rezervare.Excursion = excursie;
                                }
                            }
                        }
                    }

                    rezervari.Add(rezervare);
                }

                return rezervari;
            }
            catch (Exception e)
            {
                log.Error(e.Message);
                Console.WriteLine(e);
            }
            return null;
        }

        public Reservation? Save(Reservation entity)
        {
            log.Info("Added rezervation for " + entity.ClientName);
            const string query = "INSERT INTO \"Rezervari\" (\"numeClient\", \"agentieId\", \"excursieId\", telefon, \"nrLocuriRezervate\") VALUES (@numeClient, @agentieId, @excursieId, @telefon, @nrLocuriRezervate) RETURNING \"rezervareId\"";
            try
            {
                using var connection = DbConnection.GetConnection(props);
                connection.Open();
                using var command = new NpgsqlCommand(query, connection);
                command.Parameters.AddWithValue("@numeClient", entity.ClientName);
                command.Parameters.AddWithValue("@agentieId", entity.Agency.Id);
                command.Parameters.AddWithValue("@excursieId", entity.Excursion.Id);
                command.Parameters.AddWithValue("@telefon", entity.PhoneNumber);
                command.Parameters.AddWithValue("@nrLocuriRezervate", entity.NoBookedSeats);
                var id = command.ExecuteScalar();
                if (id != null)
                {
                    entity.Id = Convert.ToInt32(id);
                    return entity;
                }

                return null;
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
            }

            return null;
        }

        public Reservation? Delete(int id)
        {
            log.Info($"Deleting Reservation {id}");
            var rezervare = FindById(id);
            if (rezervare == null) return null;

            const string query = "DELETE FROM \"Rezervari\" WHERE \"rezervareId\" = @id";
            try
            {
                using var connection = DbConnection.GetConnection(props);
                using var command = new NpgsqlCommand(query, connection);
                command.Parameters.AddWithValue("@id", id);
                command.ExecuteNonQuery();
                return rezervare;
            }
            catch (Exception e)
            {
                log.Error(e.Message);
            }
            return null;
        }

        public Reservation? Update(Reservation entity)
        {
            log.Info("Updated rezervation with id " + entity.Id);

            const string query = "UPDATE \"Rezervari\" SET \"numeClient\" = @numeClient, \"agentieId\" = @agentieId, \"excursieId\" = @excursieId, telefon = @telefon, \"nrLocuriRezervate\" = @nrLocuriRezervate WHERE \"rezervareId\" = @id";
            try
            {
                using var connection = DbConnection.GetConnection(props);
                connection.Open();
                using var command = new NpgsqlCommand(query, connection);
                command.Parameters.AddWithValue("@id", entity.Id);
                command.Parameters.AddWithValue("@numeClient", entity.ClientName);
                command.Parameters.AddWithValue("@agentieId", entity.Agency.Id);
                command.Parameters.AddWithValue("@excursieId", entity.Excursion.Id);
                command.Parameters.AddWithValue("@telefon", entity.PhoneNumber);
                command.Parameters.AddWithValue("@nrLocuriRezervate", entity.NoBookedSeats);
                int rowsAffected = command.ExecuteNonQuery();
                return entity;
            }
            catch (Exception e)
            {
                log.Error(e.Message);
            }
            return null;
        }

        public List<Reservation> FindAllReservationsWithAgencyId(int id)
        {
            log.Info($"Rezervare {id}");

            List<Reservation> rezervareList = new List<Reservation>();

            const string query = "SELECT * FROM \"Rezervari\" WHERE \"agentieId\" = @id";
            try
            {
                using var connection = DbConnection.GetConnection(props);
                connection.Open();
                using var command = new NpgsqlCommand(query, connection);
                command.Parameters.AddWithValue("@id", id);
                using var reader = command.ExecuteReader();

                while (reader.Read())
                {
                    var rezervare = new Reservation(
                        reader.GetInt32(reader.GetOrdinal("rezervareId")),
                        reader.GetString(reader.GetOrdinal("numeClient")),
                        reader.GetString(reader.GetOrdinal("telefon")),
                        null,
                        null,
                        reader.GetInt32(reader.GetOrdinal("nrLocuriRezervate"))

                    );

                    int agentieId = reader.GetInt32(reader.GetOrdinal("agentieId"));

                    const string queryAgentie = "SELECT * FROM \"AgentiiTurism\" WHERE \"agentieId\" = @id";
                    using var connectionAgentie = DbConnection.GetConnection(props);
                    connectionAgentie.Open();
                    using var commandAgentie = new NpgsqlCommand(queryAgentie, connectionAgentie);
                    commandAgentie.Parameters.AddWithValue("@id", agentieId);
                    using var readerAgentie = commandAgentie.ExecuteReader();

                    Agency? agentie = null;

                    if (readerAgentie.Read())
                    {
                        agentie = new Agency(
                            agentieId,
                            readerAgentie.GetString(readerAgentie.GetOrdinal("numeAgentie"))
                        );
                        rezervare.Agency = agentie;
                    }

                    int excursieId = reader.GetInt32(reader.GetOrdinal("excursieId"));

                    const string queryExcursie = "SELECT * FROM \"Excursii\" WHERE \"excursieId\" = @id";
                    using var connectionExcursie = DbConnection.GetConnection(props);
                    connectionExcursie.Open();
                    using var commandExcursie = new NpgsqlCommand(queryExcursie, connectionExcursie);
                    commandExcursie.Parameters.AddWithValue("@id", excursieId);
                    using var readerExcursie = commandExcursie.ExecuteReader();

                    Excursion? excursie = null;

                    if (readerExcursie.Read())
                    {
                        excursie = new Excursion(
                            readerExcursie.GetInt32(readerExcursie.GetOrdinal("excursieId")),
                            readerExcursie.GetString(readerExcursie.GetOrdinal("obiectiv")),
                            readerExcursie.GetString(readerExcursie.GetOrdinal("firmaTransport")),
                            readerExcursie.GetInt32(readerExcursie.GetOrdinal("nrLocuri")),
                            readerExcursie.GetInt32(readerExcursie.GetOrdinal("pret")),
                            readerExcursie.GetDateTime(readerExcursie.GetOrdinal("dataOraPlecare"))
                        );
                        rezervare.Excursion = excursie;
                    }

                    rezervareList.Add(rezervare);
                }
            }
            catch (Exception ex)
            {
                log.Error(ex);
                Console.WriteLine(ex);
            }

            return rezervareList;
        }
    }
}
