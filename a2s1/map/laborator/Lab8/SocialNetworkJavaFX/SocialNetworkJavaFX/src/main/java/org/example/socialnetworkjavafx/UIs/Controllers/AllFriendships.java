package org.example.socialnetworkjavafx.UIs.Controllers;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.layout.VBox;
import org.example.socialnetworkjavafx.Entities.Friendship;
import org.example.socialnetworkjavafx.Utils.Paging.Page;
import org.example.socialnetworkjavafx.Utils.Paging.Pageable;

import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class AllFriendships {
    @FXML CliController controller;

    @FXML
    private VBox rootVBox;

    @FXML
    private TableView<Friendship> friendshipsTable;

    @FXML
    private TableColumn<Friendship, String> username1Column;

    @FXML
    private TableColumn<Friendship, String> username2Column;

    @FXML
    private TableColumn<Friendship, String> dateTimeColumn;

    @FXML
    private TableColumn<Friendship, String> pendingColumn;

    @FXML
    private Pagination pagination;

    @FXML
    private Button nextButton;

    @FXML
    private Button prevButton;

    private List<Friendship> allFriendships;

    private final ObservableList<Friendship> model = FXCollections.observableArrayList();
    private int currentPageIndex = 0;
    private final int rowsPerPage = 10;
    private int totalElements = 0;

    public void initialize() {
        username1Column.setCellValueFactory(data -> new javafx.beans.property.SimpleStringProperty(data.getValue().getUser1()));
        username2Column.setCellValueFactory(data -> new javafx.beans.property.SimpleStringProperty(data.getValue().getUser2()));
        dateTimeColumn.setCellValueFactory(data -> new javafx.beans.property.SimpleStringProperty(data.getValue().getDateTime().toString()));
        pendingColumn.setCellValueFactory(data -> new javafx.beans.property.SimpleStringProperty(data.getValue().isPending() ? "true" : "false"));

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
        this.controller = controller;

        loadPage(0);
    }

    private void loadPage(int pageIndex) {
        Pageable pageable = new Pageable(pageIndex, rowsPerPage);
        Page<Friendship> page = controller.findAllOnPage(pageable);

        totalElements = controller.countAllFriendships();
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
