using System;

using System.Configuration;
using System.Net.Sockets;
using System.Threading;
using chat.persistence.repository.mock;
using chat.persistence;
using chat.services;
using chat.network.client;
using ServerTemplate;
using protobuf;
namespace chat
{
    using server;
    class StartServer
    {
        private static int DEFAULT_PORT=55556;
        private static String DEFAULT_IP="127.0.0.1";

        static void Main(string[] args)
        {
            
            // IUserRepository userRepo = new UserRepositoryMock();
            Console.WriteLine("Reading properties from app.config ...");
            int port = DEFAULT_PORT;
            String ip = DEFAULT_IP;
            String portS= ConfigurationManager.AppSettings["port"];
            if (portS == null)
            {
                Console.WriteLine("Port property not set. Using default value "+DEFAULT_PORT);
            }
            else
            {
                bool result = Int32.TryParse(portS, out port);
                if (!result)
                {
                    Console.WriteLine("Port property not a number. Using default value "+DEFAULT_PORT);
                    port = DEFAULT_PORT;
                    Console.WriteLine("Portul "+port);
                }
            }
            String ipS=ConfigurationManager.AppSettings["ip"];
           
            if (ipS == null)
            {
                Console.WriteLine("Port property not set. Using default value "+DEFAULT_IP);
            }

            IUserRepository userRepo = new UserRepositoryMock();
            IMessageRepository messageRepository = new MessageRepositoryMock();
            IChatServices services = new ChatServicesImpl(userRepo, messageRepository);

            Console.WriteLine("Starting server on IP {0} and port {1}", ip, port);

            ProtoV3ChatServer scs = new ProtoV3ChatServer(ip, port, services);
            scs.Start();
            Console.WriteLine("Server started ...");
            //Console.WriteLine("Press <enter> to exit...");
            Console.ReadLine();
            
        }
    }

    public class SerialChatServer: ConcurrentServer 
    {
        private IChatServices services;
        private ChatClientWorker worker;
        public SerialChatServer(string host, int port, IChatServices services) : base(host, port)
            {
                this.services = services;
                Console.WriteLine("SerialChatServer...");
        }
        protected override Thread createWorker(TcpClient client)
        {
            worker = new ChatClientWorker(services, client);
            return new Thread(new ThreadStart(worker.run));
        }
    }
    public class ProtoChatServer : ConcurrentServer
    {
        private IChatServices services;
        private ProtoChatWorker worker;
        public ProtoChatServer(string host, int port, IChatServices services)
            : base(host, port)
        {
            this.services = services;
            Console.WriteLine("ProtoChatServer...");
        }
        protected override Thread createWorker(TcpClient client)
        {
            worker = new ProtoChatWorker(services, client);
            return new Thread(new ThreadStart(worker.run));
        }
    }
    
    public class ProtoV3ChatServer : ConcurrentServer
    {
        private IChatServices services;
        private ProtoV3ChatWorker worker;
        public ProtoV3ChatServer(string host, int port, IChatServices services)
            : base(host, port)
        {
            this.services = services;
            Console.WriteLine("ProtoChatServer...");
        }
        protected override Thread createWorker(TcpClient client)
        {
            worker = new ProtoV3ChatWorker(services, client);
            return new Thread(new ThreadStart(worker.run));
        }
    }
}
