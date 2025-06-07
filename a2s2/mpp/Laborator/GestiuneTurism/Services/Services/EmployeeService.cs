using Model;
using Persistance.Interfaces;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Services.Services
{
    public class EmployeeService
    {
        private IEmployeeRepository employeeRepository;

        public EmployeeService(IEmployeeRepository employeeRepository)
        {
            this.employeeRepository = employeeRepository;
        }

        public Employee? Login(string username, string password)
        {
            Employee? employee = employeeRepository.FindByUsername(username);
            if (employee == null)
            {
                return null;
            }
            if (password != null)
            {
                if (employee.Password == password) return employee;
            }
            return null;
        }
    }
}
