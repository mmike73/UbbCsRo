package Lab2.Containers;

import Lab2.Tasks.Task;
import java.util.ArrayList;
import java.util.List;

public abstract class AbstractContainer implements Container {
    protected List<Task> tasks;

    public AbstractContainer() {
        tasks = new ArrayList<>();
    }

    @Override
    public void add(Task task) {
        if (!tasks.contains(task)) {
            tasks.add(task);
        }
    }

    @Override
    public int size() {
        return tasks.size();
    }

    @Override
    public boolean isEmpty() {
        return tasks.isEmpty();
    }

}
