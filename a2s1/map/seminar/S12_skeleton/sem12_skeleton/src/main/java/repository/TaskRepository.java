package repository;

import domain.Task;
import repository.Repository;

import java.util.Map;

public interface TaskRepository extends Repository<String, Task> {

    Map<Task.Difficulty, Double> getAverageTime();
}
