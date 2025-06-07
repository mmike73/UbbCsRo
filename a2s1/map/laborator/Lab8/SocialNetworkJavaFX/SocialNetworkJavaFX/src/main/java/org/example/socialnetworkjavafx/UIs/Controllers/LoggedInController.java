package org.example.socialnetworkjavafx.UIs.Controllers;

import javafx.application.Platform;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.layout.Pane;
import javafx.stage.Modality;
import javafx.stage.Stage;
import org.example.socialnetworkjavafx.Entities.Friendship;
import org.example.socialnetworkjavafx.Entities.User;
import org.example.socialnetworkjavafx.Utils.Dtos.FriendshipFilterDTO;
import org.example.socialnetworkjavafx.Utils.Paging.Page;
import org.example.socialnetworkjavafx.Utils.Paging.Pageable;

import java.io.IOException;
import java.util.List;
import java.util.Optional;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class LoggedInController {

    private CliController cliController;
    private User loggedUser;

    @FXML
    private Label welcomeMessage;

    @FXML
    private ListView<String> friendsListView;

    @FXML
    private ListView<String> pgFriendsListView;

    @FXML
    private ListView<String> friendRequestsListView;

    @FXML
    private ListView<String> sentRequestsListView;

    @FXML
    private Pagination pagination;

    @FXML
    private Button nextButton;

    @FXML
    private Button prevButton;

    private final ObservableList<String> friendsModel = FXCollections.observableArrayList();
    private int currentPageIndex = 0;
    private final int rowsPerPage = 10;
    private int totalElements = 0;


    public void setUser(User user, CliController cliController) {
        this.loggedUser = user;
        this.cliController = cliController;

        welcomeMessage.setText("Welcome " + loggedUser.getUsername() + "!");
        updateView();
        initialize();
        loadPage(0);
    }

    private void updateView() {
        List<String> friends = getFriends();
        if (friends != null && !friends.isEmpty()) {
            friendsModel.setAll(friends);
            pgFriendsListView.setItems(friendsModel);
        } else {
            pgFriendsListView.setPlaceholder(new Label("No friends to display"));
        }
        friendsListView.setItems(FXCollections.observableArrayList(getFriends()));
        friendRequestsListView.setItems(FXCollections.observableArrayList(getFriendRequests()));
        sentRequestsListView.setItems(FXCollections.observableArrayList(getSentRequests()));
    }

    private List<String> getFriends() {
        return cliController.getAllFriendships().stream()
                .filter(friendship -> !friendship.isPending() &&
                        (friendship.getUser1().equals(loggedUser.getUsername()) ||
                                friendship.getUser2().equals(loggedUser.getUsername())))
                .map(friendship -> friendship.getUser1().equals(loggedUser.getUsername())
                        ? friendship.getUser2()
                        : friendship.getUser1())
                .collect(Collectors.toList());
    }

    private List<String> getFriendRequests() {
        return cliController.getAllFriendships().stream()
                .filter(friendship -> friendship.isPending() &&
                        !friendship.getInitiator().equals(loggedUser.getUsername()) &&
                        (friendship.getUser1().equals(loggedUser.getUsername()) ||
                                friendship.getUser2().equals(loggedUser.getUsername())))
                .map(friendship -> friendship.getUser1().equals(loggedUser.getUsername())
                        ? friendship.getUser2()
                        : friendship.getUser1())
                .collect(Collectors.toList());
    }

    private List<String> getSentRequests() {
        return cliController.getAllFriendships().stream()
                .filter(friendship -> friendship.isPending() &&
                        friendship.getInitiator().equals(loggedUser.getUsername()))
                .map(friendship -> friendship.getUser1().equals(loggedUser.getUsername())
                        ? friendship.getUser2()
                        : friendship.getUser1())
                .collect(Collectors.toList());
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
                FXMLLoader loader = new FXMLLoader(getClass().getResource("/org/example/socialnetworkjavafx/Views/Message.fxml"));

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

    private void initialize() {
        pgFriendsListView = new ListView<>();
        pagination.currentPageIndexProperty().addListener((obs, oldIndex, newIndex) -> loadPage(newIndex.intValue()));
        nextButton.setOnAction(event -> onNext());
        prevButton.setOnAction(event -> onPrev());
    }

    private void loadPage(int pageIndex) {

        Pageable pageable = new Pageable(pageIndex, rowsPerPage);
        FriendshipFilterDTO filter = new FriendshipFilterDTO(Optional.of(loggedUser.getUsername()), Optional.empty(), Optional.empty());
        Page<Friendship> page = cliController.findAllOnPage(pageable, filter);

        List<String> friends = StreamSupport.stream(page.getElementsOnPage().spliterator(), false)
                .map(friendship -> friendship.getUser1().equals(loggedUser.getUsername())
                        ? friendship.getUser2()
                        : friendship.getUser1())
                .collect(Collectors.toList());

        friendsModel.setAll(friends);
        pgFriendsListView.setItems(friendsModel);

        totalElements = friends.size();

        int totalPages = (int) Math.ceil((double) totalElements / rowsPerPage);
        pagination.setPageCount(totalPages);

        prevButton.setDisable(pageIndex == 0);
        nextButton.setDisable(pageIndex + 1 >= totalPages);
    }

    private void onNext() {
        int currentIndex = pagination.getCurrentPageIndex();
        if (currentIndex < pagination.getPageCount() - 1) {
            pagination.setCurrentPageIndex(currentIndex + 1);
        } else {
            showAlert("End of List", "You are already on the last page!");
        }
    }

    private void onPrev() {
        int currentIndex = pagination.getCurrentPageIndex();
        if (currentIndex > 0) {
            pagination.setCurrentPageIndex(currentIndex - 1);
        } else {
            showAlert("End of List", "You are already on the first page!");
        }
    }

    private void showAlert(String title, String content) {
        Alert alert = new Alert(Alert.AlertType.INFORMATION);
        alert.setTitle(title);
        alert.setHeaderText(null);
        alert.setContentText(content);
        alert.showAndWait();
    }
}
