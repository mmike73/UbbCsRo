package org.example.flightsproject.Infrastructure;

import org.example.flightsproject.Domain.Client;
import org.example.flightsproject.Domain.Entity;
import org.example.flightsproject.Repo.AbstractDbRepository;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.List;
import java.util.Optional;

public class ClientDbRepo extends AbstractDbRepository<Long, Client> {

    public ClientDbRepo(DbConnection connection) {
        super(connection);
    }

    @Override
    public Optional<Client> delete(Client entity) {
        return Optional.empty();
    }

    @Override
    public Optional<Client> findById(Long id) {
        String query = "SELECT * FROM Clients WHERE clientId = ?";

        try (PreparedStatement preparedStatement = connection.getConn().prepareStatement(query)) {
            preparedStatement.setLong(1, id);
            try (ResultSet resultSet = preparedStatement.executeQuery()) {
                if (resultSet.next()) {
                    return Optional.of(new Client(
                            resultSet.getLong("clientId"),
                            resultSet.getString("clientName"),
                            resultSet.getString("clientUsername")
                    ));
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return Optional.empty();
        //11:30 12:24 13:39
    }

    public Optional<Client> findByUsername(String username) {
        String query = "SELECT * FROM Clients WHERE clientUsername = ?";

        try (PreparedStatement preparedStatement = connection.getConn().prepareStatement(query)) {
            preparedStatement.setString(1, username);
            try (ResultSet resultSet = preparedStatement.executeQuery()) {
                if (resultSet.next()) {
                    return Optional.of(new Client(
                            resultSet.getLong("clientId"),
                            resultSet.getString("clientName"),
                            resultSet.getString("clientUsername")
                    ));
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return Optional.empty();
    }

    @Override
    public Iterable<Client> findAll() {
        return null;
    }

    @Override
    public Optional<Client> save(Client entity) {
        return Optional.empty();
    }

    @Override
    public Optional<Client> update(Client entity) {
        return Optional.empty();
    }
}
