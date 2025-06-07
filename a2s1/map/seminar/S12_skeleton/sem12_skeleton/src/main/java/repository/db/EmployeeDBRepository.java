package repository.db;

import domain.Employee;
import repository.EmployeeRepository;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class EmployeeDBRepository implements EmployeeRepository {

    private String url;
    private String username;
    private String password;

    private static final String ORDER_BY_LEVEL_AND_SALARY = "select * from employees order by knowledge_level, salary_per_hour desc";
    private static final String GET_BY_ID_SQL = "select * from employees where id = ?";
    private static final String GET_ALL_SQL = "select * from employees";
    private static final String INSERT_SQL = "insert into employees (name, salary_per_hour, knowledge_level) values (?, ?, ?) returning id";
    private static final String DELETE_SQL = "delete from employees where id = ?";
    private static final String UPDATE_SQL = "update employees set name = ?, salary_per_hour = ?, knowledge_level = ? where id = ?";

    public EmployeeDBRepository(String url, String username, String password) {
        this.url = url;
        this.username = username;
        this.password = password;
    }

    @Override
    public Employee findOne(String id) {
        try (Connection connection = DriverManager.getConnection(url, username, password)) {
             return findOne(connection, id);
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public Iterable<Employee> findAll() {
        List<Employee> entities = new ArrayList<>();
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement(GET_ALL_SQL);
             ResultSet resultSet = statement.executeQuery()) {
            while (resultSet.next()) {
                entities.add(toEmployee(resultSet));
            }
            return entities;
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public Employee save(Employee entity) {
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement(INSERT_SQL)) {
            statement.setString(1, entity.getName());
            statement.setFloat(2, entity.getSalaryPerHour());
            statement.setString(3, entity.getKnowledgeLevel().name());
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
    public Employee delete(String id) {
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement(DELETE_SQL)) {
            statement.setString(1, id);
            Employee existingEntity = findOne(connection, id);
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
    public Employee update(Employee entity) {
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement(UPDATE_SQL)) {
            statement.setString(1, entity.getName());
            statement.setFloat(2, entity.getSalaryPerHour());
            statement.setString(3, entity.getKnowledgeLevel().name());
            statement.setString(4, entity.getId());
            int response = statement.executeUpdate();
            return response == 0 ? null : entity;
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public List<Employee> getOrderedByLevelAndRatePerHour() {
        List<Employee> entities = new ArrayList<>();
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement(ORDER_BY_LEVEL_AND_SALARY);
             ResultSet resultSet = statement.executeQuery()) {
            while (resultSet.next()) {
                entities.add(toEmployee(resultSet));
            }
            return entities;
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    public static Employee toEmployee(ResultSet resultSet) throws SQLException {
        String id = resultSet.getString("id");
        String name = resultSet.getString("name");
        float salaryPerHour = resultSet.getFloat("salary_per_hour");
        Employee.KnowledgeLevel knowledgeLevel = Employee.KnowledgeLevel.valueOf(resultSet.getString("knowledge_level"));
        return new Employee(id, name, salaryPerHour, knowledgeLevel);
    }

    private Employee findOne(Connection connection, String id) throws SQLException {
        try (PreparedStatement statement = connection.prepareStatement(GET_BY_ID_SQL)) {
            statement.setString(1, id);
            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                return toEmployee(resultSet);
            }
            return null;
        }
    }
}
