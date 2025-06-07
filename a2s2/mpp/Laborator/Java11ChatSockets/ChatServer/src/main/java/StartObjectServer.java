import chat.network.utils.AbstractServer;
import chat.network.utils.ChatObjectConcurrentServer;
import chat.network.utils.ServerException;
import chat.persistence.MessageRepository;
import chat.persistence.UserRepository;
import chat.persistence.repository.jdbc.MessageRepositoryJdbc;
import chat.persistence.repository.jdbc.UserRepositoryJdbc;
import chat.server.ChatServicesImpl;
import chat.services.IChatServices;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.io.File;
import java.io.IOException;
import java.util.Properties;


public class StartObjectServer {
    private static int defaultPort=55555;
    private static Logger logger = LogManager.getLogger(StartObjectServer.class);
    public static void main(String[] args) {
       // UserRepository userRepo=new UserRepositoryMock();
       Properties serverProps=new Properties();
        try {
            serverProps.load(StartObjectServer.class.getResourceAsStream("/chatserver.properties"));
            logger.info ("Server properties set. {} ", serverProps);
            //serverProps.list(System.out);
        } catch (IOException e) {
            logger.error("Cannot find chatserver.properties "+e);
            logger.debug ("Looking into directory {} ", (new File(".")).getAbsolutePath());
            return;
        }
        UserRepository userRepo=new UserRepositoryJdbc(serverProps);
        MessageRepository messRepo=new MessageRepositoryJdbc(serverProps);
        IChatServices chatServerImpl=new ChatServicesImpl(userRepo, messRepo);
        int chatServerPort=defaultPort;
        try {
            chatServerPort = Integer.parseInt(serverProps.getProperty("chat.server.port"));
        }catch (NumberFormatException nef){
            logger.error("Wrong  Port Number"+nef.getMessage());
            logger.debug("Using default port "+defaultPort);
        }
        logger.debug("Starting server on port: "+chatServerPort);
        AbstractServer server = new ChatObjectConcurrentServer(chatServerPort, chatServerImpl);
        try {
                server.start();
        } catch (ServerException e) {
                logger.error("Error starting the server" + e.getMessage());
        }
    }
}
