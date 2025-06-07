package service;


import domain.Employee;
import domain.Pair;
import domain.Task;
import repository.EmployeeRepository;
import repository.TaskAssignmentRepository;
import repository.TaskRepository;

import java.time.YearMonth;
import java.util.List;
import java.util.Map;

public class Service {

    private TaskRepository taskRepository;
    private EmployeeRepository employeeRepository;
    private TaskAssignmentRepository taskAssignmentRepository;

    public Service(TaskRepository taskRepository, EmployeeRepository employeeRepository, TaskAssignmentRepository taskAssignmentRepository) {
        this.taskRepository = taskRepository;
        this.employeeRepository = employeeRepository;
        this.taskAssignmentRepository = taskAssignmentRepository;
    }

    public List<Employee> getEmployeesOrderedByLevelAndRatePerHour() {
        return employeeRepository.getOrderedByLevelAndRatePerHour();
    }

    public Map<Task.Difficulty, Double> getAverageTaskTime() {
        return taskRepository.getAverageTime();
    }

    public List<Pair<Employee, Double>> getTopBestPaidEmployees(int limit, int year) {
        return taskAssignmentRepository.getTopBestPaidEmployees(limit, year);
    }

    public List<Pair<Employee, Double>> getEmployeeSalaries(YearMonth yearMonth) {
        return taskAssignmentRepository.getEmployeeSalaries(yearMonth);
    }
}
