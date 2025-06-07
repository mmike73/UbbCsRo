package domain;

public class Task extends Entity<String> {

    private String name;
    private Difficulty difficulty;
    private int estimatedHours;

    public enum Difficulty {
        EASY,
        MEDIUM,
        HARD
    }

    public Task(String id, String name, Difficulty difficulty, int estimatedHours) {
        setId(id);
        this.name = name;
        this.difficulty = difficulty;
        this.estimatedHours = estimatedHours;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public Difficulty getDifficulty() {
        return difficulty;
    }

    public void setDifficulty(Difficulty difficulty) {
        this.difficulty = difficulty;
    }

    public int getEstimatedHours() {
        return estimatedHours;
    }

    public void setEstimatedHours(int estimatedHours) {
        this.estimatedHours = estimatedHours;
    }

    @Override
    public String toString() {
        return "Task{" +
                "id='" + getId() + '\'' +
                ", name='" + name + '\'' +
                ", difficulty=" + difficulty +
                ", estimatedHours=" + estimatedHours +
                '}';
    }
}
