using log4net;
using Npgsql;
using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Reflection;
using System.Reflection.Metadata.Ecma335;
using System.Text;
using System.Threading.Tasks;

namespace Persistance
{
    public static class DbConnection
    {
        //private static NpgsqlConnection? instance = null;
        //private static NpgsqlConnection GetConnection(IDictionary<String, string> props)
        //{
        //    if (instance == null || instance.State == System.Data.ConnectionState.Closed)
        //    {
        //        instance = GetNewConnection(props);
        //        instance.Open();
        //    }
        //    return instance;
        //}


        //old name: GetNewConnection
        public static NpgsqlConnection GetConnection(IDictionary<String, string> props)
        {
            return ConnectionFactory.GetInstance().CreateConnection(props);
        }
    }

    public abstract class ConnectionFactory
    {
        protected ConnectionFactory()
        {
        }

        private static ConnectionFactory instance;

        public static ConnectionFactory GetInstance()
        {
            if (instance == null)
            {
                Assembly assem = Assembly.GetExecutingAssembly();
                Type[] types = assem.GetTypes();
                foreach (Type type in types)
                {
                    if (type.IsSubclassOf(typeof(ConnectionFactory)))
                        instance = (ConnectionFactory)Activator.CreateInstance(type);
                }
            }
            return instance;
        }

        public abstract NpgsqlConnection CreateConnection(IDictionary<String, string> props);
    }

    public class PostgreSqlConnectionFactory : ConnectionFactory
    {
        private static readonly ILog log = LogManager.GetLogger(typeof(PostgreSqlConnectionFactory));
        public override NpgsqlConnection CreateConnection(IDictionary<String, string> props)
        {
            string connectionString = props["ConnectionString"];
            log.DebugFormat("Creating PostgreSQL connection for {0}", connectionString);
            return new NpgsqlConnection(connectionString);
        }
    }
}

