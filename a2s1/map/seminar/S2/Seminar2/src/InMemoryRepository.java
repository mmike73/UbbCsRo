import java.util.HashMap;
import java.util.Map;

public class InMemoryRepository<ID, E extends Entity<ID>> implements Repository<ID, E> {
    private Map<ID, E> entities;

    public InMemoryRepository() {
        entities = new HashMap<>();
    }

    @Override
    public E findOne(ID id) {
        if(id == null) {
            throw new IllegalArgumentException("id cannot be null");
        }
        return entities.get(id);
    }

    @Override
    public Iterable<E> findAll() {
        return entities.values();
    }

    @Override
    public E save(E entity) {
        if(entity == null) {
            throw new IllegalArgumentException("entity cannot be null");
        }
        return ;
    }

    @Override
    public E delete(ID id) {
        return null;
    }

    @Override
    public E update(E entity) {
        return null;
    }
}
