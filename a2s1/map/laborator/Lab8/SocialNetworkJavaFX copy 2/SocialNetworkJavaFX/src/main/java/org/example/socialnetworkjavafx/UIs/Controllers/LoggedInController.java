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
    private ListView<String> friendRequestsListView;

    @FXML
    private ListView<String> sentRequestsListView;

    //pagination related
    @FXML
    private TableView<Friendship> friendshipsTable;

    @FXML
    private TableColumn<Friendship, String> username1Column;

    @FXML
    private Pagination pagination;

    @FXML
    private Button nextButton;

    @FXML
    private Button prevButton;

    //

    public void setUser(User user, CliController cliController) {
        this.loggedUser = user;
        this.cliController = cliController;

        welcomeMessage.setText("Welcome " + loggedUser.getUsername() + "!");

        updateView();
        initialize();
        loadPage(0);
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

        loadPage(currentPageIndex);
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

    public void initialize() {
        username1Column.setCellValueFactory(data -> {
            String user1 = data.getValue().getUser1();
            String user2 = data.getValue().getUser2();
            return new javafx.beans.property.SimpleStringProperty(user1.equals(loggedUser.getUsername()) ? user2 : user1);
        });

        friendshipsTable.setItems(model);

        pagination.currentPageIndexProperty().addListener((obs, oldIndex, newIndex) -> {
            loadPage(newIndex.intValue());
        });

        nextButton.setOnAction(event -> onNext());
        prevButton.setOnAction(event -> onPrev());
        //seteza numarul de elemente
        // pentru ca sa pot muta printre alea
    }

    public void setController(CliController controller) {
        this.cliController = controller;
        loadPage(0);
    }

    private final ObservableList<Friendship> model = FXCollections.observableArrayList();
    private int currentPageIndex = 0;
    private final int rowsPerPage = 10;
    private int totalElements = 0;

    private void loadPage(int pageIndex) {
        Pageable pageable = new Pageable(pageIndex, rowsPerPage);

        FriendshipFilterDTO filter = new FriendshipFilterDTO(Optional.of(loggedUser.getUsername()), Optional.empty(), Optional.empty());
        Page<Friendship> page = cliController.findAllOnPage(pageable, filter);

        totalElements = cliController.countFriendships(loggedUser.getUsername());

        int totalPages = (int) Math.ceil((double) totalElements / rowsPerPage);
        pagination.setPageCount(totalPages);

        List<Friendship> friendships = StreamSupport.stream(page.getElementsOnPage().spliterator(), false).collect(Collectors.toList());
        model.setAll(friendships);

        prevButton.setDisable(pageIndex == 0);
        nextButton.setDisable(pageIndex + 1 >= totalPages);
        //pageNUmber.setText((pageIndex + 1) + " / " + totalPages);
    }

    private void onNext() {
        int currentIndex = pagination.getCurrentPageIndex();
        int totalPages = pagination.getPageCount();

        if (currentIndex < totalPages - 1) {
            pagination.setCurrentPageIndex(currentIndex + 1);
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
        } else {
            Alert alert = new Alert(Alert.AlertType.INFORMATION);
            alert.setTitle("End of List");
            alert.setHeaderText(null);
            alert.setContentText("You are already on the first page!");
            alert.showAndWait();
        }
    }
}
