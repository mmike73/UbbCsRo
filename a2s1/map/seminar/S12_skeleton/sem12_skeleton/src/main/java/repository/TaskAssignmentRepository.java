package repository;

import domain.Employee;
import domain.Pair;
import domain.TaskAssignment;
import repository.Repository;

import java.time.YearMonth;
import java.util.List;

public interface TaskAssignmentRepository extends Repository<Pair<String, String>, TaskAssignment> {

    List<Pair<Employee, Double>> getTopBestPaidEmployees(int limit, int year);

    List<Pair<Employee, Double>> getEmployeeSalaries(YearMonth yearMonth);
}
