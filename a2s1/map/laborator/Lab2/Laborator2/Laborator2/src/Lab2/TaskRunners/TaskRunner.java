package Lab2.TaskRunners;
import Lab2.Tasks.*;

public interface TaskRunner {
    void executeOneTask();
    void executeAll();
    void addTask(Task t);
    boolean hasTask();
}
