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
import java.util.ArrayList;
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
    private ListView<String> friendRequestsListView;

    @FXML
    private ListView<String> sentRequestsListView;

    @FXML
    private Pagination pagination;

//    @FXML
//    private Button nextButton;
//
//    @FXML
//    private Button prevButton;

    private final ObservableList<Friendship> model = FXCollections.observableArrayList();

    private int currentPageIndex = 0;

    private final int rowsPerPage = 4;

    private int totalElements = 0;

    public void init() {
        //totalElements = cliController.countFriendships(loggedUser.getUsername());
        pagination.currentPageIndexProperty().addListener((obs, oldIndex, newIndex) -> {
            loadPage(newIndex.intValue());
        });

//        nextButton.setOnAction(event -> onNext());
//        prevButton.setOnAction(event -> onPrev());

        loadPage(0);
        updateView();
    }

    private void loadPage(int pageIndex) {
        Pageable pageable = new Pageable(pageIndex, rowsPerPage);

        FriendshipFilterDTO filter = new FriendshipFilterDTO(Optional.of(loggedUser.getUsername()), Optional.empty(), Optional.empty());
        Page<Friendship> page = cliController.findAllOnPage(pageable, filter);
        totalElements = cliController.countFriendships(loggedUser.getUsername());

        int totalPages = (int) Math.ceil((double) totalElements / rowsPerPage);
        pagination.setPageCount(totalPages);

        List<Friendship> friendships = StreamSupport.stream(page.getElementsOnPage().spliterator(), false).collect(Collectors.toList());

        List<String> friends_names = new ArrayList<>();
        friendships.forEach(u -> {
            if (u.isPending() == false) {
                if (u.getUser1().equals(loggedUser.getUsername())) {
                    friends_names.add(u.getUser2());
                } else {
                    friends_names.add(u.getUser1());
                }
            }
        });

        pagination.currentPageIndexProperty().addListener((obs, oldIndex, newIndex) -> {
            loadPage(newIndex.intValue());
        });

        friendsListView.setItems(FXCollections.observableArrayList(friends_names));
    }

    private void updateView() {
        loadPage(currentPageIndex);

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

        loadPage(currentPageIndex);
    }

    public void setUser(User user) {
        this.loggedUser = user;
        welcomeMessage.setText("Welcome " + loggedUser.getUsername() + "!");
    }

    public void setController(CliController controller) {
        this.cliController = controller;
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

    private void onNext() {
        int currentIndex = pagination.getCurrentPageIndex();
        int totalPages = pagination.getPageCount();

        if (currentIndex < totalPages - 1) {
            pagination.setCurrentPageIndex(currentIndex + 1);
            updateView();
        } else {
            Alert alert = new Alert(Alert.AlertType.INFORMATION);
            alert.setTitle("End of List");
            alert.setHeaderText(null);
            alert.setContentText("You are already on the last page!");
            alert.showAndWait();
        }
    }

    private void onPrev() {
        int currentIndex = pagination.getCurrentPageIndex();
        int totalPages = pagination.getPageCount();

        if (currentIndex > 0) {
            pagination.setCurrentPageIndex(currentIndex - 1);
            updateView();
        } else {
            Alert alert = new Alert(Alert.AlertType.INFORMATION);
            alert.setTitle("End of List");
            alert.setHeaderText(null);
            alert.setContentText("You are already on the first page!");
            alert.showAndWait();
        }
    }
}
