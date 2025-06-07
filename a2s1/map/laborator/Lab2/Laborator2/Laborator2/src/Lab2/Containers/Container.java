package Lab2.Containers;
import Lab2.Tasks.Task;


public interface Container {
    Task remove();
    void add(Task task);
    int size();
    boolean isEmpty();
}
