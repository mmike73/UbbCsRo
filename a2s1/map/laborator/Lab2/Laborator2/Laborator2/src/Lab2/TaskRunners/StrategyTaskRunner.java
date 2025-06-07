package Lab2.TaskRunners;
import Lab2.Containers.*;
import Lab2.Factories.*;
import Lab2.Tasks.*;

public class StrategyTaskRunner implements TaskRunner {
    private Container taskContainer;

    public StrategyTaskRunner(ContainerStrategy strategy) {
        taskContainer = TaskContainerFactory.getInstance().createContainer(strategy);
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
