package org.example.Infrastructure;

import org.example.Entities.Friendship;
import org.example.Entities.User;
import org.example.Repository.AbstractDbRepository;

import java.sql.*;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class FriendshipDbRepository extends AbstractDbRepository<Integer, Friendship> {
    public FriendshipDbRepository(Connection connection) {
        super(connection);
    }

    @Override
    public Optional<Friendship> findOne(Integer integer) {
        return findAll()
                .stream()
                .filter(friendship -> friendship.getId().equals(integer))
                .findFirst();
    }

    @Override
    public List<Friendship> findAll() {
        String query = "SELECT * FROM friendships";
        try {

            PreparedStatement statement = connection.prepareStatement(query);
            ResultSet resultSet = statement.executeQuery();

            List<Friendship> friendships = new ArrayList<>();
            while (resultSet.next()) {
                //System.out.println(resultSet.getString("since"));
                LocalDateTime since = resultSet.getTimestamp("since").toLocalDateTime();
                //nu e string
                boolean pending = resultSet.getBoolean("pending");
                //nu e string
                friendships.add(new Friendship(resultSet.getString("username1"), resultSet.getString("username2"), resultSet.getString("initiator"), since, pending));
            }
            return friendships;

        } catch (SQLException e) {
            e.printStackTrace();
        }

        return new ArrayList<Friendship>();
    }

    @Override
    public Optional<Friendship> save(Friendship entity) {
        String query = "INSERT INTO friendships (username1, username2, since, pending, initiator) VALUES (?, ?, ?, ?, ?)";
        try {

            PreparedStatement statement = connection.prepareStatement(query);

            int res = entity.getUser1().compareToIgnoreCase(entity.getUser2());

            if (res < 0) {
                statement.setString(1, entity.getUser1());
                statement.setString(2, entity.getUser2());
            } else {
                statement.setString(1, entity.getUser2());
                statement.setString(2, entity.getUser1());
            }

            statement.setString(3, Timestamp.valueOf(entity.getDateTime()).toString());

            String pending = (entity.isPending()) ? "True" : "False";

            statement.setString(4, pending);

            statement.setString(5, entity.getInitiator());

            statement.execute();

            return Optional.of(entity);
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return Optional.empty();
    }

    @Override
    public Optional<Friendship> delete(Integer integer) {
        Optional<Friendship> friendship = findOne(integer);
        if (friendship.isPresent()) {
            String query = "DELETE FROM friendships WHERE username1 = ? AND username2 = ?";
             try {
                 PreparedStatement statement = connection.prepareStatement(query);
                 statement.setString(1, friendship.get().getUser1());
                 statement.setString(2, friendship.get().getUser2());
                 statement.execute();
                 return friendship;
             } catch (Exception e) {
                 e.printStackTrace();
             }
        }
        return Optional.empty();
    }

    @Override
    public Optional<Friendship> update(Friendship entity) {
        String query = "UPDATE friendships SET since = ?, pending = ? WHERE username1 = ? AND username2 = ?";

        try {
            PreparedStatement statement = connection.prepareStatement(query);

            statement.setTimestamp(1, Timestamp.valueOf(entity.getDateTime()));
            statement.setBoolean(2, entity.isPending());

            int res = entity.getUser1().compareToIgnoreCase(entity.getUser2());
            if (res < 0) {
                statement.setString(3, entity.getUser1());
                statement.setString(4, entity.getUser2());
            } else {
                statement.setString(3, entity.getUser2());
                statement.setString(4, entity.getUser1());
            }

            int rowsUpdated = statement.executeUpdate();

            if (rowsUpdated > 0) {
                return Optional.of(entity);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return Optional.empty();
    }

}
