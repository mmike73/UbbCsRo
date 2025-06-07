import config.Config;
import controller.Controller;
import domain.Employee;
import domain.Task;
import domain.TaskAssignment;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;
import repository.EmployeeRepository;
import repository.TaskAssignmentRepository;
import repository.TaskRepository;
import repository.db.*;
import service.Service;

import java.time.LocalDateTime;
import java.util.Arrays;
import java.util.List;

import static domain.Employee.KnowledgeLevel.JUNIOR;
import static domain.Employee.KnowledgeLevel.SENIOR;
import static domain.Task.Difficulty.EASY;
import static domain.Task.Difficulty.MEDIUM;


public class Sem12 extends Application {

    @Override
    public void start(Stage primaryStage) throws Exception{
        FXMLLoader loader=new FXMLLoader();
        loader.setLocation(getClass().getResource("/view/taskAssignments.fxml"));
        AnchorPane root=loader.load();

        Controller ctrl=loader.getController();

        String dbUrl = Config.getProperties().getProperty("db.url");
        String dbUsername = Config.getProperties().getProperty("db.username");
        String dbPassword = Config.getProperties().getProperty("db.password");
        List<Task> tasks = generateTasks(false); // generateTasks(true);
        List<Employee> employees = generateEmployees(false);  // generateTasks(true);
        TaskRepository taskRepository = new TaskDBRepository(dbUrl, dbUsername, dbPassword); // new InMemoryRepository<>();
//        for (Task task : tasks) {
//            System.out.println(taskRepository.save(task));
//        }
        EmployeeRepository employeeRepository = new EmployeeDBRepository(dbUrl, dbUsername, dbPassword); // new InMemoryRepository<>();
//        for (Employee employee : employees) {
//            System.out.println(employeeRepository.save(employee));
//        }
        TaskAssignmentRepository taskAssignmentRepository = new TaskAssignmentDBRepository(dbUrl, dbUsername, dbPassword); // new InMemoryRepository<>();
//        for (TaskAssignment taskAssignment : generateTaskAssignments(employees, tasks)) {
//            System.out.println(taskAssignmentRepository.save(taskAssignment));
//        }
        ctrl.setService(new Service(taskRepository, employeeRepository, taskAssignmentRepository));

        primaryStage.setScene(new Scene(root));
        primaryStage.setTitle("Hello World");
        primaryStage.show();
    }

    public List<Task> generateTasks(boolean withId) {
        return Arrays.asList(
                new Task(withId ? "1" : null, "T1", EASY, 1),
                new Task(withId ? "2" : null, "T2", MEDIUM, 2),
                new Task(withId ? "3" : null, "T3", EASY, 1));
    }

    public List<Employee> generateEmployees(boolean withId) {
        return Arrays.asList(
                new Employee(withId ? "1" : null, "E1", 100, SENIOR),
                new Employee(withId ? "2" : null, "E2", 50, JUNIOR),
                new Employee(withId ? "3": null, "E3", 50, JUNIOR));
    }

    public List<TaskAssignment> generateTaskAssignments(List<Employee> employees, List<Task> tasks) {
        return Arrays.asList(
                new TaskAssignment(employees.get(0), tasks.get(0), LocalDateTime.of(2025, 1, 1, 0, 0, 0)),
                new TaskAssignment(employees.get(0), tasks.get(1), LocalDateTime.of(2025, 1, 2, 0, 0, 0)),
                new TaskAssignment(employees.get(1), tasks.get(2), LocalDateTime.of(2025, 1, 1, 0, 0, 0)));
    }

    public static void main(String[] args) {
        launch(args);
    }

}
