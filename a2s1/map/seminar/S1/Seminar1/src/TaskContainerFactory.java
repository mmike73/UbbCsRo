public class TaskContainerFactory implements Factory {
    //private costructor

    @Override
    public Container createContainer(Strategy strategy) {
        switch(strategy) {
            case FIFO:
                return new QueueContainer();
            case LIFO:
                return new StackContainer();
            default:
                return null;
        }
    }
}
