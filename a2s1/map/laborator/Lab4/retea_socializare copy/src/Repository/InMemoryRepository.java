package Repository;

import Entities.Entity;
import Validators.Validator;

import java.util.HashMap;
import java.util.Map;
import java.util.Optional;

//import static jdk.internal.classfile.AnnotationValue.of;

public class InMemoryRepository<ID, E extends Entity<ID>> implements Repository<ID, E> {
    private Validator<E> validator;
    protected Map<ID, E> entities;

    public InMemoryRepository(Validator<E> validator) {
        this.validator = validator;
        this.entities = new HashMap<>();
    }

    @Override
    public Optional<E> findOne(ID id) {
        E found = entities.get(id);
        if (found != null) {
            return Optional.of((E) found);
        }
        return Optional.empty();
    }

    @Override
    public Iterable<E> findAll() {
        return entities.values();
    }

    @Override
    public Optional<E> save(E entity) {
        validator.validate(entity);
        entities.put(entity.getId(), entity);
        return Optional.of((E) entity);
    }

    @Override
    public Optional<E> delete(ID id) {
        Entity<ID> entity = entities.remove(id);;
        if (entity == null) return Optional.empty();
        return Optional.of((E) entity);
    }

    @Override
    public Optional<E> update(E entity) {
        entities.put(entity.getId(), entity);
        return Optional.of((E) entity);
    }
}
