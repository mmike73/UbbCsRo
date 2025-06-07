package repository.db;

import domain.Task;
import repository.TaskRepository;

import java.sql.*;
import java.util.*;

public class TaskDBRepository implements TaskRepository {

    private String url;
    private String username;
    private String password;

    private static final String GET_AVG_BY_DIFFICULTY = "select difficulty, avg(estimated_hours) as average from tasks group by difficulty ";
    private static final String GET_BY_ID_SQL = "select * from tasks where id = ?";
    private static final String GET_ALL_SQL = "select * from tasks";
    private static final String INSERT_SQL = "insert into tasks (name, difficulty, estimated_hours) values (?, ?, ?) returning id";
    private static final String DELETE_SQL = "delete from tasks where id = ?";
    private static final String UPDATE_SQL = "update tasks set name = ?, difficulty = ?, estimated_hours = ? where id = ?";

    public TaskDBRepository(String url, String username, String password) {
        this.url = url;
        this.username = username;
        this.password = password;
    }

    @Override
    public Task findOne(String id) {
        try (Connection connection = DriverManager.getConnection(url, username, password)) {
             return findOne(connection, id);
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public Iterable<Task> findAll() {
        List<Task> entities = new ArrayList<>();
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement(GET_ALL_SQL);
             ResultSet resultSet = statement.executeQuery()) {
            while (resultSet.next()) {
                entities.add(toTask(resultSet));
            }
            return entities;
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public Task save(Task entity) {
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement(INSERT_SQL)) {
            statement.setString(1, entity.getName());
            statement.setString(2, entity.getDifficulty().name());
            statement.setInt(3, entity.getEstimatedHours());
            ResultSet resultSet = statement.executeQuery();
            // retrieve the generated id
            if (resultSet.next()) {
                String generatedId = resultSet.getString("id");
                entity.setId(generatedId);
                return entity;
            }
            return null;
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public Task delete(String id) {
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement(DELETE_SQL)) {
            statement.setString(1, id);
            Task existingEntity = findOne(connection, id);
            int response = 0;
            if (existingEntity != null) {
                response = statement.executeUpdate();
            }
            return response == 0 ? null : existingEntity;
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public Task update(Task entity) {
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement(UPDATE_SQL)) {
            statement.setString(1, entity.getName());
            statement.setString(2, entity.getDifficulty().name());
            statement.setInt(3, entity.getEstimatedHours());
            statement.setString(4, entity.getId());
            int response = statement.executeUpdate();
            return response == 0 ? null : entity;
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public Map<Task.Difficulty, Double> getAverageTime() {
        Map<Task.Difficulty, Double> entities = new HashMap<>();
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement(GET_AVG_BY_DIFFICULTY);
             ResultSet resultSet = statement.executeQuery()) {
            while (resultSet.next()) {
                Task.Difficulty difficulty = Task.Difficulty.valueOf(resultSet.getString("difficulty"));
                double average = resultSet.getDouble("average");
                entities.put(difficulty, average);
            }
            return entities;
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    private Task toTask(ResultSet resultSet) throws SQLException {
        String id = resultSet.getString("id");
        String name = resultSet.getString("name");
        Task.Difficulty difficulty = Task.Difficulty.valueOf(resultSet.getString("difficulty"));
        int estimatedHours = resultSet.getInt("estimated_hours");
        return new Task(id, name, difficulty, estimatedHours);
    }

    private Task findOne(Connection connection, String id) throws SQLException {
        try (PreparedStatement statement = connection.prepareStatement(GET_BY_ID_SQL)) {
            statement.setString(1, id);
            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                return toTask(resultSet);
            }
            return null;
        }
    }
}
