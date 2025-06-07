public class StratrgyTaskRunner implements TaskRunner {
    private Container taskContainer;

    public StratrgyTaskRunner(Strategy strategy) {
        taskContainer = new TaskContainerFactory().createContainer(strategy);
    }

    @Override
    public void executeOneTask() {
        Task t = taskContainer.remove();
        t.execute();
    }

    @Override
    public void executeAll() {
        while(!taskContainer.isEmpty()) {
            Task t = taskContainer.remove();
            t.execute();
        }
    }

    @Override
    public void addTask(Task task) {
        taskContainer.add(task);
    }

    @Override
    public boolean hasTask() {
        return !taskContainer.isEmpty();
    }

}
