package org.example.flightsproject.UI;

import javafx.application.Application;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.GridPane;
import javafx.stage.Stage;
import org.example.flightsproject.Domain.Client;
import org.example.flightsproject.Domain.Flight;
import org.example.flightsproject.Domain.Ticket;
import org.example.flightsproject.Service.Service;
import org.example.flightsproject.Utils.Event.EntityChangeEvent;
import org.example.flightsproject.Utils.Observer.Observer;

import java.sql.Timestamp;
import java.time.LocalDate;
import java.time.LocalDateTime;

public class ClientDashboard extends Application implements Observer<EntityChangeEvent> {
    Client loggedClient;
    static Service service;
    GridPane gridpane;

    ObservableList<Ticket> tickets;
    TableView<Ticket> boughtTicketsTable;

    ObservableList<Ticket> soldTicketsDate;
    TableView<Ticket> soldTicketsDateTable;

    ObservableList<Flight> flights;
    TableView<Flight> flightsTable;

    ObservableList<String> allFroms;
    ObservableList<String> allTos;

    // get all locations - from repo
    // get all to locations - from repo
    ComboBox<String> fromLocation;
    ComboBox<String> toLocation;
    Button searchButton;
    DatePicker datePicker;

    Button buyButton;

    public void setLoggedClient(Client loggedClient) {
        this.loggedClient = loggedClient;
    }

    public static void setService(Service service) {
        ClientDashboard.service = service;
    }

    public void initialize() {
        service.addObserver(this);
        allFroms = FXCollections.observableArrayList();
        allTos = FXCollections.observableArrayList();
        tickets = FXCollections.observableArrayList();
        soldTicketsDate = FXCollections.observableArrayList();
        flights = FXCollections.observableArrayList();

        boughtTicketsTable = new TableView<>();
        soldTicketsDateTable = new TableView<>();
        boughtTicketsTable.setItems(tickets);
        TableColumn flightIdCol = new TableColumn("Flight");
        flightIdCol.setCellValueFactory(
                new PropertyValueFactory<Long, Ticket>("flightId")
        );

        TableColumn putchaseTimeCol = new TableColumn("PurchasedOn");
        putchaseTimeCol.setCellValueFactory(
                new PropertyValueFactory<LocalDateTime, Ticket>("purchaseTime")
        );
        boughtTicketsTable.getColumns().addAll(flightIdCol, putchaseTimeCol);

        TableColumn flightIdCol2 = new TableColumn("Flight");
        flightIdCol2.setCellValueFactory(
                new PropertyValueFactory<Long, Ticket>("flightId")
        );

        TableColumn putchaseTimeCol2 = new TableColumn("PurchasedOn");
        putchaseTimeCol2.setCellValueFactory(
                new PropertyValueFactory<LocalDateTime, Ticket>("purchaseTime")
        );
        soldTicketsDateTable.getColumns().addAll(flightIdCol2, putchaseTimeCol2);
        soldTicketsDateTable.setItems(soldTicketsDate);

        flightsTable = new TableView<>();
        TableColumn fromPlaceCol = new TableColumn("From");
        fromPlaceCol.setCellValueFactory(
                new PropertyValueFactory<LocalDateTime, Ticket>("fromPlace")
        );
        TableColumn toPlaceCol = new TableColumn("To");
        toPlaceCol.setCellValueFactory(
                new PropertyValueFactory<LocalDateTime, Ticket>("toPlace")
        );
        TableColumn departureCol = new TableColumn("Depature");
        departureCol.setCellValueFactory(
                new PropertyValueFactory<LocalDateTime, Ticket>("departureTime")
        );
        TableColumn landingCol = new TableColumn("Landing");
        landingCol.setCellValueFactory(
                new PropertyValueFactory<LocalDateTime, Ticket>("landingTime")
        );
        TableColumn seatsCol = new TableColumn("Landing");
        seatsCol.setCellValueFactory(
                new PropertyValueFactory<LocalDateTime, Ticket>("seats")
        );
        flightsTable.getColumns().setAll(fromPlaceCol, toPlaceCol, departureCol, landingCol, seatsCol);
        flightsTable.setItems(flights);
        flights.setAll(service.flightRepo.findAll());

        fromLocation = new ComboBox<>();
        fromLocation.setItems(allFroms);
        toLocation = new ComboBox<>();
        toLocation.setItems(allTos);

        datePicker = new DatePicker();
        searchButton = new Button("Search");
        searchButton.setOnAction(e -> {
            String from = fromLocation.getSelectionModel().getSelectedItem();
            String to = toLocation.getSelectionModel().getSelectedItem();
            LocalDateTime date = datePicker.getValue().atStartOfDay();

            if (from != null && to != null) {
                flights.setAll(service.flightRepo.findAll()
                        .stream()
                        .filter(flight -> {
                            return flight.getFromPlace().equals(from) &&
                                    flight.getToPlace().equals(to) &&
                                    flight.getDepartureTime().getDayOfYear() == date.getDayOfYear();
                        })
                        .toList()
                );
                flightsTable.refresh();
            } else {
                flights.setAll(service.flightRepo.findAll());
            }
        });

        buyButton = new Button("Buy");
        buyButton.setOnAction(e -> {
            Flight slected = this.flightsTable.getSelectionModel().getSelectedItem();
            if (slected != null) {
                service.buyTicket(loggedClient.getUsername(), slected);
            }
        });

        gridpane = new GridPane();
        gridpane.add(fromLocation, 0, 0);
        gridpane.add(toLocation, 1, 0);
        gridpane.add(datePicker, 2, 0);
        gridpane.add(searchButton, 3, 0);
        gridpane.add(buyButton, 3, 4);
        gridpane.add(flightsTable, 0, 1, 3, 1);

        gridpane.add(new Label("Sold on January 24th:"), 0, 2);
        gridpane.add(soldTicketsDateTable, 0, 3, 3, 1);

        gridpane.add(new Label("My tickets:"), 0, 4);
        gridpane.add(boughtTicketsTable, 0, 5, 3, 1);

        update(null);
    }

    @Override
    public void start(Stage stage) throws Exception {
        initialize();

        Scene scene = new Scene(gridpane, 600, 400);
        stage.setTitle(loggedClient.getUsername() + "'s Dashboard");
        stage.setScene(scene);
        stage.show();
    }

    @Override
    public void update(EntityChangeEvent event) {

        allFroms.setAll(service.flightRepo.findAllFromLocations());
        allTos.setAll(service.flightRepo.findAllToLocations());

        tickets.setAll(service.ticketsRepo.findById(loggedClient.getUsername()));
        boughtTicketsTable.refresh();
        flightsTable.refresh();

        soldTicketsDate.setAll(service.ticketsRepo.findByDate(LocalDateTime.of(2024, 1,24, 0, 0, 0, 0)));
        soldTicketsDateTable.refresh();

    }
}
