package domain;

public class Employee extends Entity<String> {

    private String name;
    private float salaryPerHour;
    private KnowledgeLevel knowledgeLevel;

    public enum KnowledgeLevel {
        JUNIOR,
        MEDIUM,
        SENIOR
    }

    public Employee(String id, String name, float salaryPerHour, KnowledgeLevel knowledgeLevel) {
        setId(id);
        this.name = name;
        this.salaryPerHour = salaryPerHour;
        this.knowledgeLevel = knowledgeLevel;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public float getSalaryPerHour() {
        return salaryPerHour;
    }

    public void setSalaryPerHour(float salaryPerHour) {
        this.salaryPerHour = salaryPerHour;
    }

    public KnowledgeLevel getKnowledgeLevel() {
        return knowledgeLevel;
    }

    public void setKnowledgeLevel(KnowledgeLevel knowledgeLevel) {
        this.knowledgeLevel = knowledgeLevel;
    }

    @Override
    public String toString() {
        return "Employee{" +
                "id='" + getId() + '\'' +
                ", name='" + name + '\'' +
                ", salaryPerHour=" + salaryPerHour +
                ", knowledgeLevel=" + knowledgeLevel +
                '}';
    }
}
