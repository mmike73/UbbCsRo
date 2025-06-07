package org.example.flightsproject.Service;

import org.example.flightsproject.Domain.Client;
import org.example.flightsproject.Domain.Flight;
import org.example.flightsproject.Domain.Ticket;
import org.example.flightsproject.Infrastructure.ClientDbRepo;
import org.example.flightsproject.Infrastructure.FlightDbRepo;
import org.example.flightsproject.Infrastructure.TicketDbRepo;
import org.example.flightsproject.Utils.Event.ChangeType;
import org.example.flightsproject.Utils.Event.EntityChangeEvent;
import org.example.flightsproject.Utils.Observer.Observable;
import org.example.flightsproject.Utils.Observer.Observer;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class Service implements Observable<EntityChangeEvent> {
    public ClientDbRepo clientRepo;
    public FlightDbRepo flightRepo;
    public TicketDbRepo ticketsRepo;

    private List<Observer> observers;

    public Service(ClientDbRepo clientRepo, FlightDbRepo flightRepo, TicketDbRepo ticketsRepo) {
        observers = new ArrayList<>();
        this.clientRepo = clientRepo;
        this.flightRepo = flightRepo;
        this.ticketsRepo = ticketsRepo;
    }

    public Client logClient(String username) throws Exception {
        Optional<Client> toLog = clientRepo.findByUsername(username);
        if (toLog.isPresent()) {
            return toLog.get();
        }
        throw new Exception("Client not found");
    }

    public void buyTicket(String username, Flight slected) {
        long noSeatsRemaining = slected.getSeats() - ticketsRepo.findAll()
                .stream()
                .filter(e -> e.getFlightId() == slected.getId())
                .count();

        if (noSeatsRemaining > 0) {
            ticketsRepo.save(new Ticket(slected.getId(), username, LocalDateTime.now()));
            notifyObservers(new EntityChangeEvent(ChangeType.ADD, null));
        }
    }

    @Override
    public void addObserver(Observer<EntityChangeEvent> observer) {
        observers.add(observer);
    }

    @Override
    public void removeObserver(Observer<EntityChangeEvent> observer) {
        if (observers.contains(observer))
            observers.remove(observer);
    }

    @Override
    public void notifyObservers(EntityChangeEvent event) {
        observers.forEach(observer -> observer.update(event));
    }
}
