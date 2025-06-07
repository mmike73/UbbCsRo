package Lab2.Containers;

import Lab2.Tasks.Task;

public class StackContainer extends AbstractContainer {

    public StackContainer() {
        super();
    }

    public Task remove() {
        return this.tasks.isEmpty() ? null : (Task)this.tasks.remove(this.tasks.size() - 1);
    }
}
