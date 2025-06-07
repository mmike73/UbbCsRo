package Lab2.Factories;
import Lab2.Containers.*;

public class TaskContainerFactory implements Factory {

    static final Factory SINGLE_INSTANCE = new TaskContainerFactory();

    private TaskContainerFactory() {}

    public static Factory getInstance() {
        return SINGLE_INSTANCE;
    }

    public Container createContainer(ContainerStrategy strategy) {
        return switch (strategy) {
            case FIFO -> new QueueContainer();
            case LIFO -> new StackContainer();
            default -> null;
        };
    }
}
