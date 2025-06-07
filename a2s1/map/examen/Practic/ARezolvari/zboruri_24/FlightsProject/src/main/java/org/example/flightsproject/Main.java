package org.example.flightsproject;

import javafx.stage.Stage;
import org.example.flightsproject.Domain.Ticket;
import org.example.flightsproject.Infrastructure.ClientDbRepo;
import org.example.flightsproject.Infrastructure.DbConnection;
import org.example.flightsproject.Infrastructure.FlightDbRepo;
import org.example.flightsproject.Infrastructure.TicketDbRepo;
import org.example.flightsproject.Service.Service;
import org.example.flightsproject.UI.LoginWindow;

public class Main {
    public static void main(String[] args) {
        DbConnection db = new DbConnection(
                "jdbc:sqlserver://localhost\\social-network:1433;database=FlightsProject;trustServerCertificate=true",
                "sa",
                "Ffp6xznu4bfX"
        );
        ClientDbRepo clientRepo = new ClientDbRepo(db);
        FlightDbRepo flightRepo = new FlightDbRepo(db);
        TicketDbRepo ticketsRepo= new TicketDbRepo(db);

        Service service = new Service(clientRepo, flightRepo, ticketsRepo);
        LoginWindow lw = new LoginWindow();
        lw.setService(service);
        lw.main(args);
    }
}