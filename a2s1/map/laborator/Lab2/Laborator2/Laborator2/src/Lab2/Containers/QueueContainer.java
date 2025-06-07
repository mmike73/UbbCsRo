package Lab2.Containers;

import Lab2.Tasks.Task;

public class QueueContainer extends AbstractContainer {

    public QueueContainer() {
        super();
    }

    @Override
    public Task remove() {
        if(tasks.isEmpty()) {
            return null;
        }
        return tasks.removeFirst();
    }

}
