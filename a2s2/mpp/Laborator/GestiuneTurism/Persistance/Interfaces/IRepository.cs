using Model;
using System;
using System.Collections.Generic;
using System.Data.Common;
using System.Linq;
using System.Reflection.Metadata;
using System.Text;
using System.Threading.Tasks;

namespace Persistance.Interfaces
{
    public interface IRepository<Identifier, E> where E : Entity<Identifier>
    {
        E? FindById(Identifier id);
        
        List<E> FindAll();

        E? Save(E entity);

        E? Delete(Identifier id);

        E? Update(E entity);
    }
}
