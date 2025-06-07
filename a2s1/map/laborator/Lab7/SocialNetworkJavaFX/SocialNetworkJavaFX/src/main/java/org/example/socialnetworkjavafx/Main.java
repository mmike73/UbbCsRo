package org.example.socialnetworkjavafx;

import org.example.socialnetworkjavafx.Entities.Network;
import org.example.socialnetworkjavafx.Factories.ValidatorFactory;
import org.example.socialnetworkjavafx.Infrastructure.DataBaseConnection;
import org.example.socialnetworkjavafx.Infrastructure.FriendshipDbRepository;
import org.example.socialnetworkjavafx.Infrastructure.UserDbRepository;
import org.example.socialnetworkjavafx.Services.NetworkService;
import org.example.socialnetworkjavafx.Services.UserService;
import org.example.socialnetworkjavafx.UIs.Controllers.CliController;
import org.example.socialnetworkjavafx.UIs.CliUI;
import org.example.socialnetworkjavafx.Validators.FriendshipValidator;
import org.example.socialnetworkjavafx.Validators.UserValidator;
import org.example.socialnetworkjavafx.Validators.ValidStrategy;

import java.sql.SQLException;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class Main {

    public static void cliMain(String[] args) throws SQLException, ClassNotFoundException {

//        Network network = new Network();
//
//        ValidatorFactory vf = ValidatorFactory.getInstance();
//        UserValidator userValidator = (UserValidator) vf.createValidator(ValidStrategy.USER);
//        FriendshipValidator friendshipValidator = (FriendshipValidator) vf.createValidator(ValidStrategy.FRIENDSHIP);
//
//        DataBaseConnection dbCon = null;
//        try {
//            dbCon = new DataBaseConnection("jdbc:sqlserver://localhost:1433;databaseName=social-network;trustServerCertificate=true;", "sa", "Ffp6xznu4bfX");
//
//        } catch (ClassNotFoundException | SQLException e) {
//            e.printStackTrace();
//            return;
//        }
//
//        UserDbRepository userRepo = new UserDbRepository(dbCon.getConnection());
//        FriendshipDbRepository friendshipRepo = new FriendshipDbRepository(dbCon.getConnection());
//
//
//
//        UserService userService = new UserService(userRepo);
//        NetworkService networkService = new NetworkService(friendshipRepo, userRepo, network);
//
//        //CliController controller = new CliController(userService, networkService, messs);
//
//
//        ///CliUI ui = new CliUI(controller);
//
//        DateTimeFormatter format = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss.SSS");
//        System.out.println(LocalDateTime.now().format(format));
//
//       // ui.run();
    }

    public static void main(String[] args) throws SQLException, ClassNotFoundException {
        HelloApplication.main(args);
    }
}
