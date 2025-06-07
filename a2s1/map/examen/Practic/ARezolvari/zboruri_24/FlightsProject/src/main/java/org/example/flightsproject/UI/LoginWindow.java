package org.example.flightsproject.UI;

import javafx.application.Application;
import javafx.geometry.Insets;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.HBox;
import javafx.stage.Stage;
import org.example.flightsproject.Domain.Client;
import org.example.flightsproject.Service.Service;

import java.util.Optional;

public class LoginWindow extends Application {
    static Service service;

    TextField usernameField;
    Button loginButton;

    HBox messageBox;
    Label messageLabel;
    Button closeMessageButton;

    GridPane gridPane = new GridPane();

    public static void setService(Service service) {
        LoginWindow.service = service;
    }

    private void initialize() {
        usernameField = new TextField();
        usernameField.setPromptText("Username");

        loginButton = new Button("Login");
        loginButton.setOnAction(event -> handleLogin());

        messageLabel = new Label();

        closeMessageButton = new Button("Close");
        closeMessageButton.setOnAction(e -> messageBox.setVisible(false));

        messageBox = new HBox(10);
        messageBox.getChildren().setAll(messageLabel, closeMessageButton);
        messageBox.setStyle("-fx-border-color: gray; -fx-background-color: lightyellow; -fx-padding: 5;");
        messageBox.setVisible(false);

        gridPane.setPadding(new Insets(10));
        gridPane.setVgap(10);
        gridPane.setHgap(10);

        gridPane.add(usernameField, 0,0);
        gridPane.add(loginButton, 0,1);
        gridPane.add(messageBox, 0,2);

    }

    private void handleLogin() {
        String username = usernameField.getText().trim();
        if (username.isEmpty()) {
            showMessage("Please enter a username.", false);
        } else if (service == null) {
            showMessage("Service not initialized. Contact support.", false);
        } else {
            try {
                Client loggedClient = service.logClient(username);
                if (loggedClient != null && loggedClient.getUsername().equals(username)) {
                    showMessage("Login successful!", true);
                    ClientDashboard cd = new ClientDashboard();
                    cd.setLoggedClient(loggedClient);
                    cd.setService(service);

                    cd.start(new Stage());
                } else {
                    showMessage("Invalid username. Try again.", false);
                }
            } catch (Exception e) {
                e.printStackTrace();
                showMessage("Invalid username. Try again.", false);
            }
        }
    }

    private void showMessage(String message, boolean isSuccess) {
        messageLabel.setText(message);
        messageBox.setStyle(isSuccess
                ? "-fx-border-color: green; -fx-background-color: lightgreen; -fx-padding: 5;"
                : "-fx-border-color: red; -fx-background-color: lightcoral; -fx-padding: 5;");
        messageBox.setVisible(true);
    }

    @Override
    public void start(Stage stage) throws Exception {
        initialize();

        Scene scene = new Scene(gridPane, 600, 400);
        stage.setTitle("Login");
        stage.setScene(scene);
        stage.show();
    }

    public void main(String[] args) {
        launch(args);
    }
}
