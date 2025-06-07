package repository.db;

import domain.Employee;
import domain.Pair;
import domain.Task;
import domain.TaskAssignment;
import repository.TaskAssignmentRepository;

import java.sql.*;
import java.time.LocalDateTime;
import java.time.YearMonth;
import java.util.ArrayList;
import java.util.List;
import java.util.UUID;

import static repository.db.EmployeeDBRepository.toEmployee;

public class TaskAssignmentDBRepository implements TaskAssignmentRepository {

    private String url;
    private String username;
    private String password;


    private static final String GET_TOP_BEST_PAID_EMPLOYEES = "select e.*, sum(e.salary_per_hour*t.estimated_hours) as total_salary" +
            " from task_assignments a " +
            "left join employees e on a.employee_id=e.id " +
            "left join tasks t on t.id=a.task_id " +
            "where extract(year from a.date)=? " +
            "group by e.id, e.name, e.salary_per_hour, e.knowledge_level " +
            "order by total_salary desc " +
            "limit ?";
    private static final String GET_EMPLOYEE_SALARY = "select e.*, sum(e.salary_per_hour*t.estimated_hours) as total_salary" +
            " from task_assignments a " +
            "left join employees e on a.employee_id=e.id " +
            "left join tasks t on t.id=a.task_id " +
            "where extract(year from a.date)=? and " +
            "extract(month from a.date)=? " +
            "group by e.id, e.name, e.salary_per_hour, e.knowledge_level " +
            "order by knowledge_level, total_salary";

    private static final String GET_WITH_SUBENTITIES_SQL = "select a.*, " +
            "e.name as employee_name, e.salary_per_hour as employee_salary_per_hour, e.knowledge_level as employee_knowledge_level, " +
            "t.name as task_name, t.difficulty as task_difficulty, t.estimated_hours as task_estimated_hours " +
            "from task_assignments a " +
            "left join employees e on a.employee_id = e.id " +
            "left join tasks t on a.task_id = t.id";
    private static final String GET_BY_ID_WITH_SUBENTITIES_SQL = GET_WITH_SUBENTITIES_SQL + " where a.employee_id = ? and a.task_id = ?";
    private static final String INSERT_SQL = "insert into task_assignments (employee_id, task_id, date) values (?, ?, ?)";
    private static final String DELETE_SQL = "delete from task_assignments where employee_id = ? and task_id = ?";
    private static final String UPDATE_SQL = "update task_assignments set date = ? where employee_id = ? and task_id = ?";

    public TaskAssignmentDBRepository(String url, String username, String password) {
        this.url = url;
        this.username = username;
        this.password = password;
    }

    @Override
    public TaskAssignment findOne(Pair<String, String> id) {
        try (Connection connection = DriverManager.getConnection(url, username, password)) {
            return findOne(connection, id);
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public Iterable<TaskAssignment> findAll() {
        List<TaskAssignment> entities = new ArrayList<>();
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement(GET_WITH_SUBENTITIES_SQL);
             ResultSet resultSet = statement.executeQuery()) {
            while (resultSet.next()) {
                entities.add(toTaskAssignment(resultSet));
            }
            return entities;
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public TaskAssignment save(TaskAssignment entity) {
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement(INSERT_SQL)) {
            statement.setObject(1, UUID.fromString(entity.getId().getLeft()));
            statement.setObject(2, UUID.fromString(entity.getId().getRight()));
            statement.setTimestamp(3, Timestamp.valueOf(entity.getDate()));
            int response = statement.executeUpdate();
            return response == 0 ? null : entity;
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public TaskAssignment delete(Pair<String, String> id) {
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement(DELETE_SQL)) {
            statement.setObject(1, UUID.fromString(id.getLeft()));
            statement.setObject(1, UUID.fromString(id.getRight()));
            TaskAssignment existingEntity = findOne(connection, id);
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
    public TaskAssignment update(TaskAssignment entity) {
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement(UPDATE_SQL)) {
            statement.setTimestamp(1, Timestamp.valueOf(entity.getDate()));
            statement.setObject(2, UUID.fromString(entity.getId().getLeft()));
            statement.setObject(3, UUID.fromString(entity.getId().getRight()));
            int response = statement.executeUpdate();
            return response == 0 ? null : entity;
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public List<Pair<Employee, Double>> getTopBestPaidEmployees(int limit, int year) {
        List<Pair<Employee, Double>> entities = new ArrayList<>();
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement(GET_TOP_BEST_PAID_EMPLOYEES);
            ) {
            statement.setInt(1, year);
            statement.setInt(2, limit);
            try(ResultSet resultSet = statement.executeQuery()) {
                while (resultSet.next()) {
                    Employee employee = toEmployee(resultSet);
                    double total_salary=resultSet.getDouble("total_salary");
                    entities.add(new Pair<>(employee, total_salary));
                }
            }return entities;
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public List<Pair<Employee, Double>> getEmployeeSalaries(YearMonth yearMonth) {
        List<Pair<Employee, Double>> entities = new ArrayList<>();
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement(GET_EMPLOYEE_SALARY);
        ) {
            statement.setInt(1, yearMonth.getYear());
            statement.setInt(2, yearMonth.getMonthValue());
            try(ResultSet resultSet = statement.executeQuery()) {
                while (resultSet.next()) {
                    Employee employee = toEmployee(resultSet);
                    double total_salary=resultSet.getDouble("total_salary");
                    entities.add(new Pair<>(employee, total_salary));
                }
            }return entities;
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    private TaskAssignment toTaskAssignment(ResultSet resultSet) throws SQLException {
        String employeeId = resultSet.getString("employee_id");
        String employeeName = resultSet.getString("employee_name");
        float employeeSalaryPerHour = resultSet.getFloat("employee_salary_per_hour");
        Employee.KnowledgeLevel employeeKnowledgeLevel = Employee.KnowledgeLevel.valueOf(resultSet.getString("employee_knowledge_level"));
        Employee employee = new Employee(employeeId, employeeName, employeeSalaryPerHour, employeeKnowledgeLevel);

        String taskId = resultSet.getString("task_id");
        String taskName = resultSet.getString("task_name");
        Task.Difficulty taskDifficulty = Task.Difficulty.valueOf(resultSet.getString("task_difficulty"));
        int taskEstimatedHours = resultSet.getInt("task_estimated_hours");
        Task task = new Task(taskId, taskName, taskDifficulty, taskEstimatedHours);

        Timestamp dateTs = resultSet.getTimestamp("date");
        LocalDateTime date = dateTs != null ? dateTs.toLocalDateTime() : null;
        return new TaskAssignment(employee, task, date);
    }

    private TaskAssignment findOne(Connection connection, Pair<String, String> id) throws SQLException {
        try (PreparedStatement statement = connection.prepareStatement(GET_BY_ID_WITH_SUBENTITIES_SQL)) {
            statement.setObject(1, UUID.fromString(id.getLeft()));
            statement.setObject(2, UUID.fromString(id.getRight()));
            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                return toTaskAssignment(resultSet);
            }
            return null;
        }
    }
}
