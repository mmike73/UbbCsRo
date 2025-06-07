package org.example;

import org.example.Entities.Network;
import org.example.Entities.User;
import org.example.Factories.ValidatorFactory;
import org.example.Infrastructure.*;
import org.example.Service.NetworkService;
import org.example.Service.UserService;
import org.example.UserInterface.Controller;
import org.example.UserInterface.UI;
import org.example.Validators.FriendshipValidator;
import org.example.Validators.UserValidator;
import org.example.Validators.ValidStrategy;

import java.sql.SQLException;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class Main {
    public static void main(String[] args) throws SQLException, ClassNotFoundException {

        Network network = new Network();

        ValidatorFactory vf = ValidatorFactory.getInstance();
        UserValidator userValidator = (UserValidator) vf.createValidator(ValidStrategy.USER);
        FriendshipValidator friendshipValidator = (FriendshipValidator) vf.createValidator(ValidStrategy.FRIENDSHIP);

        DataBaseConnection dbCon = null;
        try {
           dbCon = new DataBaseConnection("jdbc:sqlserver://localhost:1433;databaseName=social-network;trustServerCertificate=true;", "sa", "Ffp6xznu4bfX");

        } catch (ClassNotFoundException | SQLException e) {
            e.printStackTrace();
            return;
        }

        UserDbRepository userRepo = new UserDbRepository(dbCon.getConnection());
        FriendshipDbRepository friendshipRepo = new FriendshipDbRepository(dbCon.getConnection());



        UserService userService = new UserService(userRepo);
        NetworkService networkService = new NetworkService(friendshipRepo, userRepo, network);

        Controller controller = new Controller(userService, networkService);

        UI ui = new UI(controller);

        DateTimeFormatter format = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss.SSS");
        System.out.println(LocalDateTime.now().format(format));

        ui.run();
    }
}