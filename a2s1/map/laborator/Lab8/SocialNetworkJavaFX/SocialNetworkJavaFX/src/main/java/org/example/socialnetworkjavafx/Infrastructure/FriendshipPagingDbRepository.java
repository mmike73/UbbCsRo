package org.example.socialnetworkjavafx.Infrastructure;

import javafx.util.Pair;
import org.example.socialnetworkjavafx.Entities.Entity;
import org.example.socialnetworkjavafx.Entities.Friendship;
import org.example.socialnetworkjavafx.Repositories.AbstractPagingDbRepository;
import org.example.socialnetworkjavafx.Utils.Dtos.FilterDTO;
import org.example.socialnetworkjavafx.Utils.Dtos.FriendshipFilterDTO;
import org.example.socialnetworkjavafx.Utils.Paging.Page;
import org.example.socialnetworkjavafx.Utils.Paging.Pageable;

import java.sql.*;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Optional;

public class FriendshipPagingDbRepository extends AbstractPagingDbRepository<Integer, Friendship, FriendshipFilterDTO> {
    public FriendshipPagingDbRepository(Connection connection) {
        super(connection);
    }

    @Override
    public Page<Friendship> findAllOnPage(Pageable pageable, FriendshipFilterDTO filter) {
        List<Friendship> friendships = new ArrayList<>();
        String query = "SELECT * FROM friendships";
        Pair<String, List<Object>> sqlFilter = friendshipFilterToSql(filter);

        if (!sqlFilter.getKey().isEmpty()) {
            query += " WHERE " + sqlFilter.getKey();
        }
        query += "ORDER BY [username1] OFFSET ? ROWS FETCH NEXT ? ROWS ONLY";

        try {
            PreparedStatement statement = connection.prepareStatement(query);

            int paramIndex = 0;
            for (Object param : sqlFilter.getValue()) {
                statement.setObject(++paramIndex, param);
            }
            System.out.println(pageable.getPageSize() + " " + pageable.getPageNumber() + " * " + pageable.getPageSize());
            statement.setInt(++paramIndex, pageable.getPageSize() * pageable.getPageNumber());
            statement.setInt(++paramIndex, pageable.getPageSize());

            ResultSet resultSet = statement.executeQuery();
            while (resultSet.next()) {
                //System.out.println(resultSet.getString("since"));
                LocalDateTime since = resultSet.getTimestamp("since").toLocalDateTime();
                //nu e string
                boolean pending = resultSet.getBoolean("pending");
                //nu e string
                friendships.add(new Friendship(resultSet.getString("username1"), resultSet.getString("username2"), resultSet.getString("initiator"), since, pending));
            }

            //int totalSize = count(filter);
            return new Page<>(friendships, friendships.size());
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public int count(FriendshipFilterDTO filter) {
        String query = "SELECT COUNT(*) as count FROM friendships";
        Pair<String, List<Object>> sqlFilter = friendshipFilterToSql(filter);

        if (!sqlFilter.getKey().isEmpty()) {
            query += " WHERE " + sqlFilter.getKey();
        }

        try (PreparedStatement statement = connection.prepareStatement(query)) {
            int paramIndex = 0;
            for (Object param : sqlFilter.getValue()) {
                statement.setObject(++paramIndex, param);
            }

            try (ResultSet result = statement.executeQuery()) {
                if (result.next()) {
                    return result.getInt("count");
                }
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        return 0;
    }

    @Override
    public int countAll() {
        String query = "SELECT COUNT(*) as count FROM friendships";

        try (PreparedStatement statement = connection.prepareStatement(query)) {
            try (ResultSet result = statement.executeQuery()) {
                if (result.next()) {
                    return result.getInt("count");
                }
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        return 0; // Default to 0 if no results
    }

    private Pair<String, List<Object>> friendshipFilterToSql(FriendshipFilterDTO filter) {
        if (filter == null) {
            return new Pair<>("", Collections.emptyList());
        }

        List<String> conditions = new ArrayList<>();
        List<Object> params = new ArrayList<>();

        filter.getUsername().ifPresent(username -> {
            conditions.add("(username1 = ? OR username2 = ?)");
            params.add(username);
            params.add(username);
        });

        filter.getInitiator().ifPresent(initiator -> {
            conditions.add("initiator = ?");
            params.add(initiator);
        });

        filter.getPending().ifPresent(pending -> {
            conditions.add("pending = ?");
            params.add(pending);
        });

        String sql = String.join(" AND ", conditions);
        return new Pair<>(sql, params);
    }



    @Override
    public Page<Friendship> findAllOnPage(Pageable pageable) {
        return findAllOnPage(pageable, (FriendshipFilterDTO) null);
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
