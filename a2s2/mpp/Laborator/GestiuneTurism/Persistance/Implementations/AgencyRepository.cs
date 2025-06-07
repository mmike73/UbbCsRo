using log4net;
using Model;
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
    public class AgencyRepository : IAgencyRepository
    {
        IDictionary<String, string> props;
        private static readonly ILog log = LogManager.GetLogger(typeof(AgencyRepository));

        public AgencyRepository(IDictionary<String, string> props) 
        {
            this.props = props;
        }

        public Agency? FindById(int id)
        {
            log.Info($"AgencyRepository: FindById {id}");

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
                
                return new Agency(reader.GetInt32(0), reader.GetString(1));
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
            }
            return null;
        }

        public List<Agency> FindAll()
        {
            log.Info($"FindAll");

            const string query = "SELECT * FROM \"AgentiiTurism\"";
            var agentii = new List<Agency>();

            try
            {
                using var connection = DbConnection.GetConnection(props);
                if (connection.State != System.Data.ConnectionState.Open)
                    connection.Open();
                using var command = connection.CreateCommand();
                command.CommandText = query;
                command.CommandType = CommandType.Text;

                using var reader = command.ExecuteReader();
                while (reader.Read())
                {
                    agentii.Add(new Agency(reader.GetInt32(0), reader.GetString(1)));
                }
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
            }

            return agentii;
        }

        public Agency? Save(Agency entity)
        {
            log.Info($"Save {entity}");

            const string query = "INSERT INTO \"AgentiiTurism\" (\"numeAgentie\") VALUES (@numeAgentie); SELECT SCOPE_IDENTITY();";
            try
            {
                using var connection = DbConnection.GetConnection(props);
                using var command = connection.CreateCommand();
                command.CommandText = query;
                command.CommandType = CommandType.Text;

                var param = command.CreateParameter();
                param.ParameterName = "@numeAgentie";
                param.Value = entity.Name;
                command.Parameters.Add(param);

                var result = command.ExecuteScalar();
                if (result != null)
                {
                    entity.Id = Convert.ToInt32(result);
                    return entity;
                }
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
            }
            finally
            {
                //DbConnection.Close
            }

            return null;
        }

        public Agency? Delete(int id)
        {
            log.Info($"Delete {id}");
            try
            {
                var agentie = FindById(id);
                if (agentie == null) return null;

                const string query = "DELETE FROM \"AgentiiTurism\" WHERE \"agentieId\" = @id";
                using var connection = DbConnection.GetConnection(props);
                using var command = connection.CreateCommand();
                command.CommandText = query;
                command.CommandType = CommandType.Text;

                var parameter = command.CreateParameter();
                parameter.ParameterName = "@id";
                parameter.Value = id;
                command.Parameters.Add(parameter);

                command.ExecuteNonQuery();

                return agentie;
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
            }

            return null;
        }

        public Agency? Update(Agency entity)
        {
            log.Info($"Update {entity}");

            const string query = "UPDATE AgentiiTurism SET \"numeAgentie\" = @numeAgentie WHERE \"agentieId\" = @id";
            try
            {
                using var connection = DbConnection.GetConnection(props);
                connection.Open();
                using var command = connection.CreateCommand();
                command.CommandText = query;
                command.CommandType = CommandType.Text;

                var param1 = command.CreateParameter();
                param1.ParameterName = "@numeAgentie";
                param1.Value = entity.Name;
                command.Parameters.Add(param1);

                var param2 = command.CreateParameter();
                param2.ParameterName = "@id";
                param2.Value = entity.Id;
                command.Parameters.Add(param2);

                var rowsAffected = command.ExecuteNonQuery();
                return entity;
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
            }

            return null;
        }
    }
}
