package repository;

import domain.Employee;
import repository.Repository;

import java.util.List;

public interface EmployeeRepository extends Repository<String, Employee> {

    List<Employee> getOrderedByLevelAndRatePerHour();

}
