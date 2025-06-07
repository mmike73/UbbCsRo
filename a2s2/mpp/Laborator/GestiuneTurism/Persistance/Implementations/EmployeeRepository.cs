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
    public class EmployeeRepository : IEmployeeRepository
    {
        IDictionary<String, string> props;
        private static readonly ILog log = LogManager.GetLogger(typeof(AgencyRepository));

        public EmployeeRepository(IDictionary<String, string> props)
        {
            this.props = props;
        }

        public Employee? FindById(int id)
        {
            log.Info($"Finding angajat {id}");

            const string query = "SELECT * FROM \"Angajati\" WHERE \"angajatId\" = @id";
            try
            {
                using var connection = DbConnection.GetConnection(props);
                if (connection.State != System.Data.ConnectionState.Open)
                    connection.Open();
                using var command = connection.CreateCommand();
                command.CommandText = query;
                command.CommandType = CommandType.Text;

                var parameter = command.CreateParameter();
                parameter.ParameterName = "id";
                parameter.Value = id;
                command.Parameters.Add(parameter);

                using var reader = command.ExecuteReader();
                if (reader.Read())
                {

                    var angajat = new Employee(
                        reader.GetInt32(0),
                        reader.GetString(1),
                        reader.GetString(2),
                        null
                    );

                    int agentieId = reader.GetInt32(3);

                    // Fetch associated AgentieTurism
                    var agentieTurism = FindAgency(agentieId);
                    angajat.Agency = agentieTurism;

                    return angajat;
                }
            }
            catch (Exception ex)
            {
                log.Error(ex);
                Console.WriteLine(ex.Message);
            }
            return null;
        }

        public List<Employee> FindAll()
        {
            log.Info("Fetching all employees");

            const string query = "SELECT * FROM \"Angajati\"";
            var angajati = new List<Employee>();

            try
            {
                using (var connection = DbConnection.GetConnection(props))
                {
                    if (connection.State != System.Data.ConnectionState.Open)
                        connection.Open();
                    using (var command = connection.CreateCommand())
                    {
                        command.CommandText = query;
                        command.CommandType = CommandType.Text;
                        using (var reader = command.ExecuteReader())
                        {
                            while (reader.Read())
                            {
                                var angajat = new Employee(
                                    reader.GetInt32(0),
                                    reader.GetString(1),
                                    reader.GetString(2),
                                    null
                                );

                                int agentieId = reader.GetInt32(3);
                                angajat.Agency = FindAgency(agentieId);

                                angajati.Add(angajat);
                            }
                        }
                    }
                }
            }
            catch (Exception ex)
            {
                log.Error(ex);
                Console.WriteLine(ex.Message);
            }

            return angajati;
        }

        public Employee? Save(Employee entity)
        {
            log.Info($"Saving angajat: {entity.Username}");

            const string query = "INSERT INTO \"Angajati\" (username, password, \"agentieId\") VALUES (@username, @password, @agentieId) RETURNING \"angajatId\"";

            using var connection = DbConnection.GetConnection(props);
            if (connection.State != System.Data.ConnectionState.Open)
                connection.Open();
            using var command = connection.CreateCommand();
            command.CommandText = query;
            command.CommandType = CommandType.Text;

            var param1 = command.CreateParameter();
            param1.ParameterName = "@username";
            param1.Value = entity.Username;

            var param2 = command.CreateParameter();
            param2.ParameterName = "@password";
            param2.Value = entity.Password;

            var param3 = command.CreateParameter();
            param3.ParameterName = "@agentieId";
            param3.Value = entity.Agency.Id;

            command.Parameters.Add(param1);
            command.Parameters.Add(param2);
            command.Parameters.Add(param3);

            var newId = command.ExecuteScalar();
            if (newId == null) return null;

            entity.Id = Convert.ToInt32(newId);
            return entity;
        }

        public Employee? Delete(int id)
        {
            log.Info($"Deleting angajat with id {id}");

            var angajat = FindById(id);
            if (angajat == null) return null;

            try
            {
                const string query = "DELETE FROM \"Angajati\" WHERE \"angajatId\" = @id";
                using var connection = DbConnection.GetConnection(props);
                if (connection.State != System.Data.ConnectionState.Open)
                    connection.Open();
                using var command = connection.CreateCommand();
                command.CommandText = query;
                command.CommandType = CommandType.Text;

                var param = command.CreateParameter();
                param.ParameterName = "@id";
                param.Value = angajat.Id;

                command.Parameters.Add(param);

                command.ExecuteNonQuery();
            }
            catch (Exception ex)
            {
                log.Error(ex);
                Console.WriteLine(ex.Message);
            }

            return angajat;
        }

        public Employee? Update(Employee entity)
        {
            log.Info($"Updating angajat: {entity.Username}");

            const string query = "UPDATE \"Angajati\" SET password = @password, \"agentieId\" = @agentieId WHERE \"angajatId\" = @id";
            try
            {
                using var connection = DbConnection.GetConnection(props);
                if (connection.State != System.Data.ConnectionState.Open)
                    connection.Open();
                using var command = connection.CreateCommand();
                command.Parameters.AddWithValue("@password", entity.Password);
                command.Parameters.AddWithValue("@agentieId", entity.Agency?.Id ?? (object)DBNull.Value);
                command.Parameters.AddWithValue("@id", entity.Id);

                int rowsAffected = command.ExecuteNonQuery();
                return entity;
            }
            catch (Exception ex)
            {
                log.Error(ex);
                Console.WriteLine(ex.Message);
            }
            return null;
        }

        public Employee? FindByUsername(string username)
        {
            log.Info($"Finding angajat {username}");

            const string query = "SELECT * FROM \"Angajati\" WHERE \"username\" = @username";
            try
            {
                using var connection = DbConnection.GetConnection(props);
                if (connection.State != System.Data.ConnectionState.Open)
                    connection.Open();
                using var command = connection.CreateCommand();
                
                command.CommandText = query;
                command.Parameters.AddWithValue("@username", username);

                using var reader = command.ExecuteReader();
                if (!reader.Read()) return null;

                var angajat = new Employee(
                    reader.GetInt32("angajatId"),
                    reader.GetString("username"),
                    reader.GetString("password"),
                    null
                );

                int agentieId = reader.GetInt32("agentieId");

                // Fetch associated AgentieTurism
                var agentieTurism = FindAgency(agentieId);
                angajat.Agency = agentieTurism;

                return angajat;
            }
            catch (Exception ex)
            {
                log.Error(ex);
                Console.WriteLine(ex.Message);
            }
            return null;
        }

        private Agency FindAgency(int id)
        {
            log.Info($"FindAgencyById {id}");

            const string query = "SELECT * FROM \"AgentiiTurism\" WHERE \"agentieId\" = @id";

            try
            {
                using var connection = DbConnection.GetConnection(props);
                if (connection.State != System.Data.ConnectionState.Open)
                    connection.Open();
                using var command = connection.CreateCommand();
                command.CommandText = query;
                command.CommandType = CommandType.Text;

                var parameter = command.CreateParameter();
                parameter.ParameterName = "id";
                parameter.Value = id;
                command.Parameters.Add(parameter);

                using var reader = command.ExecuteReader();
                if (reader.Read())
                {
                    return new Agency(reader.GetInt32(0), reader.GetString(1));
                }
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
            }
            return null;
        }
    }
}
