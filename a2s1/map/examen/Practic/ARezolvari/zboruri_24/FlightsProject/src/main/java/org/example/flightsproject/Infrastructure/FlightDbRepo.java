package org.example.flightsproject.Infrastructure;

import org.example.flightsproject.Domain.Entity;
import org.example.flightsproject.Domain.Flight;
import org.example.flightsproject.Domain.Ticket;
import org.example.flightsproject.Repo.AbstractDbRepository;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class FlightDbRepo extends AbstractDbRepository<Long, Flight> {
    public FlightDbRepo(DbConnection dbConnection) {
        super(dbConnection);
    }

    public List<String> findAllFromLocations() {
        String query = "SELECT DISTINCT fromPlace FROM Flights";
        List<String> locations = new ArrayList<>();
        try {
            PreparedStatement ps = connection.getConn().prepareStatement(query);

            ResultSet rs = ps.executeQuery();

            while (rs.next()) {
                locations.add(rs.getString("fromPlace"));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return locations;
    }

    public List<String> findAllToLocations() {
        String query = "SELECT DISTINCT toPlace FROM Flights";
        List<String> locations = new ArrayList<>();
        try {
            PreparedStatement ps = connection.getConn().prepareStatement(query);

            ResultSet rs = ps.executeQuery();

            while (rs.next()) {
                locations.add(rs.getString("toPlace"));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return locations;
    }

    @Override
    public Optional<Flight> delete(Flight entity) {
        return Optional.empty();
    }

    @Override
    public Optional<Flight> findById(Long aLong) {
        return Optional.empty();
    }

    @Override
    public List<Flight> findAll() {
        String query = "SELECT * FROM Flights";
        List<Flight> flights = new ArrayList<>();

        try {
            PreparedStatement ps = connection.getConn().prepareStatement(query);
            ResultSet rs = ps.executeQuery();

            while (rs.next()) {
                flights.add(
                        new Flight(
                                rs.getLong("flightId"),
                                rs.getString("fromPlace"),
                                rs.getString("toPlace"),
                                rs.getTimestamp("departureTime").toLocalDateTime(),
                                rs.getTimestamp("landingTIme").toLocalDateTime(),
                                rs.getInt("seats")
                        )
                );
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        return flights;
    }

    @Override
    public Optional<Flight> save(Flight entity) {
        return Optional.empty();
    }

    @Override
    public Optional<Flight> update(Flight entity) {
        return Optional.empty();
    }
}
