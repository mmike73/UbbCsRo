package org.example.flightsproject.Infrastructure;

import org.example.flightsproject.Domain.Entity;
import org.example.flightsproject.Domain.Ticket;
import org.example.flightsproject.Repo.AbstractDbRepository;

import java.sql.*;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class TicketDbRepo extends AbstractDbRepository<Long, Ticket> {
    public TicketDbRepo(DbConnection dbConnection) {
        super(dbConnection);
    }

    @Override
    public Optional<Ticket> delete(Ticket entity) {
        return Optional.empty();
    }

    @Override
    public Optional<Ticket> update(Ticket entity) {
        return Optional.empty();
    }

    @Override
    public Optional<Ticket> findById(Long id) {
        String query = "SELECT * FROM Tickets WHERE ticketId = ?";

        try (PreparedStatement preparedStatement = connection.getConn().prepareStatement(query)) {
            preparedStatement.setLong(1, id);
            try (ResultSet resultSet = preparedStatement.executeQuery()) {
                if (resultSet.next()) {
                    return Optional.of (
                            new Ticket(
                                    resultSet.getLong("flightId"),
                                    resultSet.getString("username"),
                                    resultSet.getTimestamp("purchaseTime").toLocalDateTime()
                            )
                    );
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return Optional.empty();
    }

    public List<Ticket> findById(String username) {
        String query = "SELECT * FROM Ticket WHERE username = ?";
        List<Ticket> tickets = new ArrayList<>();

        try (PreparedStatement preparedStatement = connection.getConn().prepareStatement(query)) {
            preparedStatement.setString(1, username);
            try (ResultSet resultSet = preparedStatement.executeQuery()) {
                while (resultSet.next()) {
                    tickets.add(
                            new Ticket(
                                    resultSet.getLong("flightId"),
                                    resultSet.getString("username"),
                                    resultSet.getTimestamp("purchaseTime").toLocalDateTime()
                            )
                    );
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return tickets;
    }

    public List<Ticket> findByDate(LocalDateTime dateTime) {
        String query = "SELECT * FROM Ticket WHERE purchaseTime = ?";
        List<Ticket> tickets = new ArrayList<>();

        try (PreparedStatement preparedStatement = connection.getConn().prepareStatement(query)) {
            preparedStatement.setTimestamp(1, Timestamp.valueOf(dateTime));
            try (ResultSet resultSet = preparedStatement.executeQuery()) {
                if (resultSet.next()) {
                    tickets.add(
                            new Ticket(
                                    resultSet.getLong("flightId"),
                                    resultSet.getString("username"),
                                    resultSet.getTimestamp("purchaseTime").toLocalDateTime()
                            )
                    );
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return tickets;
    }

    @Override
    public List<Ticket> findAll() {
        List<Ticket> tickets = new ArrayList<>();
        String query = "SELECT * FROM Ticket";

        try (PreparedStatement preparedStatement = connection.getConn().prepareStatement(query)) {
            try (ResultSet resultSet = preparedStatement.executeQuery()) {
                while (resultSet.next()) {
                    tickets.add(
                            new Ticket(
                                    resultSet.getLong("flightId"),
                                    resultSet.getString("username"),
                                    resultSet.getTimestamp("purchaseTime").toLocalDateTime()
                            )
                    );
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return tickets;
    }

    @Override
    public Optional save(Ticket ticket) {
        String query = "INSERT INTO Ticket (username, flightId, purchaseTime) VALUES (?, ?, ?)";

        try {
            PreparedStatement preparedStatement = connection.getConn().prepareStatement(query, Statement.RETURN_GENERATED_KEYS);
            preparedStatement.setString(1, ticket.getUsername());
            preparedStatement.setLong(2, ticket.getFlightId());
            preparedStatement.setTimestamp(3, Timestamp.valueOf(ticket.getPurchaseTime()));

            preparedStatement.executeUpdate();

            ResultSet generatedKeys = preparedStatement.getGeneratedKeys();
            if (generatedKeys.next()) {
                ticket.setId(generatedKeys.getLong(1));
            } else {
                throw new SQLException("Creating order failed, no ID obtained.");
            }


            return Optional.of(ticket);
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }
}
