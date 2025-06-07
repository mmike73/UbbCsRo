package org.example.socialnetworkjavafx;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;
import org.example.socialnetworkjavafx.Entities.Network;
import org.example.socialnetworkjavafx.Factories.ValidatorFactory;
import org.example.socialnetworkjavafx.Infrastructure.*;
import org.example.socialnetworkjavafx.Services.MessageService;
import org.example.socialnetworkjavafx.Services.NetworkService;
import org.example.socialnetworkjavafx.Services.UserService;
import org.example.socialnetworkjavafx.UIs.Controllers.CliController;
import org.example.socialnetworkjavafx.UIs.Controllers.LandingController;
import org.example.socialnetworkjavafx.Validators.FriendshipValidator;
import org.example.socialnetworkjavafx.Validators.UserValidator;
import org.example.socialnetworkjavafx.Validators.ValidStrategy;

import java.io.IOException;
import java.sql.SQLException;

public class HelloApplication extends Application {
    LandingController controller;

    private void initView(Stage primaryStage, CliController cli_controller) throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(HelloApplication.class.getResource("Views/Landing.fxml"));

        AnchorPane userLayout = fxmlLoader.load();
        primaryStage.setScene(new Scene(userLayout));

        LandingController controller = fxmlLoader.getController();
        controller.setController(cli_controller);
    }

    @Override
    public void start(Stage stage) throws IOException {
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
        FriendshipPagingDbRepository friendshipRepo = new FriendshipPagingDbRepository(dbCon.getConnection());

        UserService userService = new UserService(userRepo);
        NetworkService networkService = new NetworkService(friendshipRepo, userRepo, network);

        MessageDbRepository messageRepo = new MessageDbRepository(dbCon.getConnection());
        MessageService messageService = new MessageService(messageRepo);

        CliController controller = new CliController(userService, networkService, messageService);

        initView(stage, controller);
        stage.setWidth(800);
        stage.show();
    }

    public static void main(String[] args) {
        launch();
    }
}