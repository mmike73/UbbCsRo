using log4net;
using log4net.Config;
using Networking.Utils;
using Networking.JSONProtocol;
using Persistance.Implementations;
using Persistance.Interfaces;
using Services;
using Services.Services;
using System;
using System.Collections.Generic;
using System.Configuration;
using System.Linq;
using System.Net.Sockets;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace Server
{
    internal class StartServer
    {
        private static int DEFAULT_PORT = 55556;
        private static string DEFAULT_IP = "127.0.0.1";
        private static readonly ILog log = LogManager.GetLogger(typeof(StartServer));

        public static void Main(string[] args)
        {
            var logRepository = LogManager.GetRepository(Assembly.GetEntryAssembly());
            XmlConfigurator.Configure(logRepository, new FileInfo("./log4net.config"));

            log.Info("Starting chat server");
            log.Info("Reading properties from app.config ...");
            int port = DEFAULT_PORT;
            String ip = DEFAULT_IP;
            String portS = ConfigurationManager.AppSettings["port"];
            if (portS == null)
            {
                log.Debug("Port property not set. Using default value " + DEFAULT_PORT);
            }
            else
            {
                bool result = Int32.TryParse(portS, out port);
                if (!result)
                {
                    log.Debug("Port property not a number. Using default value " + DEFAULT_PORT);
                    port = DEFAULT_PORT;
                    log.Debug("Portul " + port);
                }
            }
            String ipS = ConfigurationManager.AppSettings["ip"];

            if (ipS == null)
            {
                log.Info("Port property not set. Using default value " + DEFAULT_IP);
            }
            log.InfoFormat("Configuration Settings for database {0}", GetConnectionStringByName("MppDb"));
            IDictionary<String, string> props = new SortedList<String, String>();

            props.Add("ConnectionString", GetConnectionStringByName("MppDb"));

            IAgencyRepository agencyRepository = new AgencyRepository(props);
            IEmployeeRepository employeeRepository = new EmployeeRepository(props);
            IExcursionRepository excursionRepository = new ExcursionRepository(props);
            IReservationRepository reservationRepository = new ReservationRepository(props);

            AgencyService agencyService = new AgencyService(agencyRepository);
            EmployeeService employeeService = new EmployeeService(employeeRepository);
            ExcursionService excursionService = new ExcursionService(excursionRepository);
            ReservationService reservationService = new ReservationService(reservationRepository);

            IController controller = new AppController(agencyService, employeeService, excursionService, reservationService);

            log.DebugFormat("Starting server on IP {0} and port {1}", ip, port);
            //SerialChatServer server = new SerialChatServer(ip,port, serviceImpl);
            JsonChatServer server = new JsonChatServer(ip, port, controller);
            server.Start();
            log.Debug("Server started ...");
            Console.ReadLine();
        }


        static string GetConnectionStringByName(string name)
        {
            // Assume failure.
            string returnValue = null;

            // Look for the name in the connectionStrings section.
            ConnectionStringSettings settings = ConfigurationManager.ConnectionStrings[name];

            // If found, return the connection string.
            if (settings != null)
                returnValue = settings.ConnectionString;

            return returnValue;
        }
    }

    public class JsonChatServer : ConcurrentServer
    {
        private IController server;
        private ClientJsonWorker worker;
        private static readonly ILog log = LogManager.GetLogger(typeof(JsonChatServer));
        public JsonChatServer(string host, int port, IController server) : base(host, port)
        {
            this.server = server;
            log.Debug("Creating JsonChatServer...");
        }
        protected override Thread createWorker(TcpClient client)
        {
            worker = new ClientJsonWorker(server, client);
            return new Thread(worker.run);
        }
    }
}
