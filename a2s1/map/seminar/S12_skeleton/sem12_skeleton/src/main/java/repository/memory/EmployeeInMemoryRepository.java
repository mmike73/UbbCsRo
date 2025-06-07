package repository.memory;

import domain.Employee;
import repository.EmployeeRepository;

import java.util.Comparator;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class EmployeeInMemoryRepository extends InMemoryRepository<String, Employee> implements EmployeeRepository {

    public List<Employee> getOrderedByLevelAndRatePerHour() {
        return StreamSupport.stream(findAll().spliterator(), false)
                .sorted(Comparator.comparing(Employee::getKnowledgeLevel)
                        .thenComparing(Comparator.comparing(Employee::getSalaryPerHour).reversed()))
                .collect(Collectors.toList());
    }
}
