package domain;

import java.time.LocalDateTime;

public class TaskAssignment extends Entity<Pair<String, String>> {

    private Employee employee;
    private Task task;
    private LocalDateTime date;

    public TaskAssignment(Employee employee, Task task, LocalDateTime date) {
        setId(new Pair(employee.getId(), task.getId()));
        this.employee = employee;
        this.task = task;
        this.date = date;
    }

    public Employee getEmployee() {
        return employee;
    }

    public void setEmployee(Employee employee) {
        this.employee = employee;
    }

    public Task getTask() {
        return task;
    }

    public void setTask(Task task) {
        this.task = task;
    }

    public LocalDateTime getDate() {
        return date;
    }

    public void setDate(LocalDateTime date) {
        this.date = date;
    }

    @Override
    public String toString() {
        return "TaskAssignment{" +
                "employee=" + employee +
                ", task=" + task +
                ", date=" + date +
                '}';
    }
}
