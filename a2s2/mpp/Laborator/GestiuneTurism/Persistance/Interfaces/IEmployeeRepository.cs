using Model;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Persistance.Interfaces
{
    public interface IEmployeeRepository : IRepository<int, Employee>
    {
        public Employee? FindByUsername(string username);
    }
}
