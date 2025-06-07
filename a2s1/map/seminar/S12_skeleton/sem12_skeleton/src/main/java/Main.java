public class Main {

    /*
    CREATE EXTENSION IF NOT EXISTS pgcrypto;

    CREATE TABLE tasks (
        id UUID PRIMARY KEY DEFAULT gen_random_uuid(),
        name VARCHAR(30) NOT NULL,
        difficulty VARCHAR(30) NOT NULL,
        estimated_hours INT NOT NULL
    );

    CREATE TABLE employees (
        id UUID PRIMARY KEY DEFAULT gen_random_uuid(),
        name VARCHAR(30) NOT NULL,
        salary_per_hour FLOAT NOT NULL,
        knowledge_level VARCHAR(30) NOT NULL
    );

    CREATE TABLE task_assignments (
        id UUID PRIMARY KEY DEFAULT gen_random_uuid(),
        employee_id UUID NOT NULL,
        task_id UUID NOT NULL,
        date TIMESTAMP NOT NULL,
        CONSTRAINT fk_employee FOREIGN KEY (employee_id) REFERENCES employees (id) ON DELETE CASCADE,
        CONSTRAINT fk_task FOREIGN KEY (task_id) REFERENCES tasks (id) ON DELETE CASCADE
    );
     */

    public static void main(String[] args) {
        Sem12.main(args);
    }
}
