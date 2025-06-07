package org.example.socialnetworkjavafx.UIs.Controllers;

import javafx.application.Platform;
import javafx.collections.FXCollections;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.scene.control.ListView;
import javafx.scene.control.TextInputDialog;
import javafx.scene.layout.Pane;
import javafx.stage.Modality;
import javafx.stage.Stage;
import org.example.socialnetworkjavafx.Entities.Friendship;
import org.example.socialnetworkjavafx.Entities.User;

import java.io.IOException;
import java.util.List;
import java.util.Optional;

public class LoggedInController {
    private CliController cliController;
    private User loggedUser;

    @FXML
    private Label welcomeMessage;

    @FXML
    private ListView<String> friendsListView;

    @FXML
    private ListView<String> friendRequestsListView;

    @FXML
    private ListView<String> sentRequestsListView;

    public void setUser(User user, CliController cliController) {
        this.loggedUser = user;
        this.cliController = cliController;

        welcomeMessage.setText("Welcome " + loggedUser.getUsername() + "!");

        updateView();
    }

    private void updateView() {
        List<String> friends = cliController.getAllFriendships().stream()
                .filter(friendship -> !friendship.isPending() &&
                        (friendship.getUser1().equals(loggedUser.getUsername()) ||
                                friendship.getUser2().equals(loggedUser.getUsername())))
                .map(friendship -> friendship.getUser1().equals(loggedUser.getUsername())
                        ? friendship.getUser2()
                        : friendship.getUser1())
                .toList();
        friendsListView.setItems(FXCollections.observableArrayList(friends));

        List<String> requests = cliController.getAllFriendships().stream()
                .filter(friendship -> friendship.isPending() &&
                        !friendship.getInitiator().equals(loggedUser.getUsername()) &&
                        (friendship.getUser1().equals(loggedUser.getUsername()) ||
                                friendship.getUser2().equals(loggedUser.getUsername())))
                .map(friendship -> friendship.getUser1().equals(loggedUser.getUsername())
                        ? friendship.getUser2()
                        : friendship.getUser1())
                .toList();
        friendRequestsListView.setItems(FXCollections.observableArrayList(requests));

        List<String> sentRequests = cliController.getAllFriendships().stream()
                .filter(friendship -> friendship.isPending() &&
                        friendship.getInitiator().equals(loggedUser.getUsername()))
                .map(friendship -> friendship.getUser1().equals(loggedUser.getUsername())
                        ? friendship.getUser2()
                        : friendship.getUser1())
                .toList();
        sentRequestsListView.setItems(FXCollections.observableArrayList(sentRequests));
    }

    @FXML
    private void onAddFriend() {
        TextInputDialog dialog = new TextInputDialog();
        dialog.setTitle("Add Friend");
        dialog.setHeaderText("Add a new friend");
        dialog.setContentText("Enter friend's username:");

        Optional<String> result = dialog.showAndWait();
        result.ifPresent(friendUsername -> {
            try {
                cliController.addFriend(loggedUser.getUsername(), friendUsername);
                updateView();
            } catch (Exception e) {
                e.printStackTrace();
            }
        });
    }

    @FXML
    private void onRemoveFriend() {
        String selectedFriend = friendsListView.getSelectionModel().getSelectedItem();
        if (selectedFriend != null) {
            try {
                cliController.removeFriend(loggedUser.getUsername(), selectedFriend);
                updateView();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }

    @FXML
    private void onAcceptRequest() {
        String selectedRequest = friendRequestsListView.getSelectionModel().getSelectedItem();
        if (selectedRequest != null) {
            try {
                cliController.acceptFriendship(loggedUser.getUsername(), selectedRequest);
                updateView();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }

    @FXML
    private void onDeclineRequest() {
        String selectedRequest = friendRequestsListView.getSelectionModel().getSelectedItem();
        if (selectedRequest != null) {
            try {
                cliController.declineFriendship(loggedUser.getUsername(), selectedRequest);
                updateView();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }

    @FXML
    private void onSendMessage() {
        String selectedFriend = friendsListView.getSelectionModel().getSelectedItem();
        if (selectedFriend != null) {
            try {
                FXMLLoader loader = new FXMLLoader(LoggedInController.class.getResource("/org/example/socialnetworkjavafx/Views/Message.fxml"));

                Pane root = loader.load();
                Stage stage = new Stage();
                stage.setScene(new Scene(root));

                stage.initModality(Modality.APPLICATION_MODAL);

                MessageController messageController = loader.getController();
                messageController.setUsers(loggedUser.getUsername(), selectedFriend, cliController);
                stage.show();

            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    @FXML
    private void onLogOut() {
        loggedUser = null;
        Stage stage = (Stage) welcomeMessage.getScene().getWindow();
        stage.close();
    }
}
