package repository.memory;

import domain.Entity;
import repository.Repository;

import java.util.HashMap;
import java.util.Map;

public class InMemoryRepository<ID, E extends Entity<ID>> implements Repository<ID,E> {

    protected Map<ID,E> entities;

    public InMemoryRepository() {
        entities = new HashMap<>();
    }

    @Override
    public E findOne(ID id) {
        if (id == null)
            throw new IllegalArgumentException("id must be not null");
        return entities.get(id);
    }

    @Override
    public Iterable<E> findAll() {
        return entities.values();
    }

    @Override
    public E save(E entity) {
        if (entity == null)
            throw new IllegalArgumentException("entity must be not null");
        E oldEntity = entities.get(entity.getId());
        if (oldEntity != null) {
            return oldEntity;
        } else {
            entities.put(entity.getId(), entity);
            return null;
        }
    }

    @Override
    public E delete(ID id) {
        if (id == null)
            throw new IllegalArgumentException("id must be not null");
        return entities.remove(id);
    }

    @Override
    public E update(E entity) {
        if (entity == null)
            throw new IllegalArgumentException("entity must be not null!");
        if (entities.get(entity.getId()) != null) {
            entities.put(entity.getId(), entity);
            return null;
        }
        return entity;
    }
}
