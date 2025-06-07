package org.example.flightsproject.Domain;

import java.time.LocalDate;
import java.time.LocalDateTime;

public class Flight extends Entity<Long> {
    String fromPlace, toPlace;
    LocalDateTime departureTime, landingTime;
    int seats;

    public Flight(String fromPlace, String toPlace, LocalDateTime landingTime, LocalDateTime departureTime, int seats) {
        this.departureTime = departureTime;
        this.fromPlace = fromPlace;
        this.landingTime = landingTime;
        this.seats = seats;
        this.toPlace = toPlace;
    }

    public Flight(Long flightId, String fromPlace, String toPlace, LocalDateTime landingTime, LocalDateTime departureTime, int seats) {
        this.setId(flightId);
        this.departureTime = departureTime;
        this.fromPlace = fromPlace;
        this.landingTime = landingTime;
        this.seats = seats;
        this.toPlace = toPlace;
    }

    public LocalDateTime getDepartureTime() {
        return departureTime;
    }

    public void setDepartureTime(LocalDateTime departureTime) {
        this.departureTime = departureTime;
    }

    public String getFromPlace() {
        return fromPlace;
    }

    public void setFromPlace(String fromPlace) {
        this.fromPlace = fromPlace;
    }

    public LocalDateTime getLandingTime() {
        return landingTime;
    }

    public void setLandingTime(LocalDateTime landingTime) {
        this.landingTime = landingTime;
    }

    public int getSeats() {
        return seats;
    }

    public void setSeats(int seats) {
        this.seats = seats;
    }

    public String getToPlace() {
        return toPlace;
    }

    public void setToPlace(String toPlace) {
        this.toPlace = toPlace;
    }
}
