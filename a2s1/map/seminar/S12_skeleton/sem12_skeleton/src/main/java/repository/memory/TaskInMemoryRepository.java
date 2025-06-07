package repository.memory;

import domain.Task;
import repository.TaskRepository;

import java.util.Map;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class TaskInMemoryRepository extends InMemoryRepository<String, Task> implements TaskRepository {

    public Map<Task.Difficulty, Double> getAverageTime() {
        return StreamSupport.stream(findAll().spliterator(), false)
                .collect(Collectors.groupingBy(
                        Task::getDifficulty,
                        Collectors.averagingDouble(Task::getEstimatedHours)
                ));
    }
}
