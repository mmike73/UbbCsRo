package repository.memory;

import domain.Employee;
import domain.Pair;
import domain.TaskAssignment;
import repository.TaskAssignmentRepository;

import java.time.LocalDateTime;
import java.time.YearMonth;
import java.util.Comparator;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class TaskAssignmentInMemoryRepository extends InMemoryRepository<Pair<String, String>, TaskAssignment> implements TaskAssignmentRepository {

    public List<Pair<Employee, Double>> getTopBestPaidEmployees(int limit, int year) {
        return StreamSupport.stream(findAll().spliterator(), false)
                .filter(a -> a.getDate().getYear() == year)
                .collect(Collectors.groupingBy(
                        TaskAssignment::getEmployee,
                        Collectors.summingDouble(a -> a.getTask().getEstimatedHours() * a.getEmployee().getSalaryPerHour())
                ))
                .entrySet().stream()
                /* .map(entry -> new Pair<>(entry.getKey(), entry.getValue()))
                .sorted((p1, p2) -> Double.compare(p2.getRight(), p1.getRight())) */
                .sorted((e1, e2) -> Double.compare(e2.getValue(), e1.getValue())) // .sorted(Map.Entry.comparingByValue().reversed())
                .map(entry -> new Pair<>(entry.getKey(), entry.getValue()))
                .limit(limit)
                .collect(Collectors.toList());
    }

    public List<Pair<Employee, Double>> getEmployeeSalaries(YearMonth yearMonth) {
        return StreamSupport.stream(findAll().spliterator(), false)
                .filter(a -> {
                    LocalDateTime data = a.getDate();
                    return data.getYear() == yearMonth.getYear() && data.getMonth() == yearMonth.getMonth();
                })
                .collect(Collectors.groupingBy(
                        TaskAssignment::getEmployee,
                        Collectors.summingDouble(a ->
                                a.getTask().getEstimatedHours() * a.getEmployee().getSalaryPerHour()
                        )
                ))
                .entrySet().stream()
                .map(entry -> new Pair<>(entry.getKey(), entry.getValue()))
                .sorted(Comparator.comparing((Pair<Employee, Double> pair) -> pair.getLeft().getKnowledgeLevel())
                        .thenComparing(Pair::getRight))
                .collect(Collectors.toList());
    }
}
