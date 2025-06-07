package org.example.flightsproject.Domain;

import java.time.LocalDateTime;

public class Ticket extends Entity<Long> {
    String username;
    Long flightId;
    LocalDateTime purchaseTime;

    public Ticket(Long flightId, String username, LocalDateTime purchaseTime) {
        this.flightId = flightId;
        this.purchaseTime = purchaseTime;
        this.username = username;
    }

    public Ticket(Long ticketId, Long flightId, String username, LocalDateTime purchaseTime) {
        this.setId(ticketId);
        this.flightId = flightId;
        this.purchaseTime = purchaseTime;
        this.username = username;
    }

    public Long getFlightId() {
        return flightId;
    }

    public void setFlightId(Long flightId) {
        this.flightId = flightId;
    }

    public LocalDateTime getPurchaseTime() {
        return purchaseTime;
    }

    public void setPurchaseTime(LocalDateTime purchaseTime) {
        this.purchaseTime = purchaseTime;
    }

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }
}
