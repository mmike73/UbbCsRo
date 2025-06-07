import java.util.ArrayList;
import java.util.List;

public class QueueContainer implements Container {
    private List<Task> tasks = new ArrayList<>();

    @Override
    public Task remove() {
        if(tasks.isEmpty()) {
            return null;
        }
        return tasks.remove(0);
    }

    @Override
    public void add(Task task) {
        tasks.add(task);
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
