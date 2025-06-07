package org.example.Infrastructure;

import org.example.Entities.User;
import org.example.Repository.AbstractDbRepository;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class UserDbRepository extends AbstractDbRepository<String, User> {
    public UserDbRepository(Connection connection) {
        super(connection);
    }

    @Override
    public Optional<User> findOne(String s) {
        String query = "SELECT * FROM [users] WHERE [username] = ?";
        try {

            PreparedStatement statement = connection.prepareStatement(query);
            statement.setString(1,  s);
            ResultSet resultSet = statement.executeQuery();

            if (resultSet.next())
                return Optional.of(new User(resultSet.getString("username"), resultSet.getString("password")));

        } catch (SQLException e) {
            e.printStackTrace();
        }
        return Optional.empty();
    }

    @Override
    public List<User> findAll() {
        String query = "SELECT * FROM dbo.users";
        try {

            PreparedStatement statement = connection.prepareStatement(query);
            ResultSet resultSet = statement.executeQuery();

            List<User> users = new ArrayList<>();
            while (resultSet.next()) {
                users.add(new User(resultSet.getString("username"), resultSet.getString("password")));
            }
            return users;

        } catch (SQLException e) {
            e.printStackTrace();
        }

        return new ArrayList<User>();
    }

    @Override
    public Optional<User> save(User entity) {
        String query = "INSERT INTO users (username, password) VALUES (?, ?)";
        try {

            PreparedStatement statement = connection.prepareStatement(query);
            statement.setString(1, entity.getUsername());
            statement.setString(2, entity.getPassword());
            statement.execute();

            return Optional.of(entity);
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return Optional.empty();
    }

    @Override
    public Optional<User> delete(String s) {
        String query = "DELETE FROM users WHERE username = ?";

        Optional<User> user = findOne(s);
        if (user.isPresent()) {
            try {

                PreparedStatement statement = connection.prepareStatement(query);
                statement.setString(1, s);
                statement.executeUpdate();
                return user;

            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
        return Optional.empty();
    }

    @Override
    public Optional<User> update(User entity) {
        return super.update(entity);
    }
}