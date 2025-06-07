package Repository;

import Entities.Entity;
import Validators.Validator;
import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

//!!!!!!! complete
abstract public class AbstractFileRepository<ID, E extends Entity<ID>> extends InMemoryRepository<ID, E> {

    String filePath;

    public AbstractFileRepository(String filePath, Validator<E> validator) {
        super(validator);
        this.filePath = filePath;
    }

    protected abstract void readFromFile() throws FileNotFoundException;
    protected abstract void writeToFile() throws FileNotFoundException;

    @Override
    public E update(E entity) {
        return super.update(entity);
    }

    @Override
    public E delete(ID id) {
        return super.delete(id);
    }

    @Override
    public E save(E entity) {
        return super.save(entity);
    }

    @Override
    public Iterable<E> findAll() {
        return super.findAll();
    }

    @Override
    public E findOne(ID id) {
        return super.findOne(id);
    }

    public AbstractFileRepository(Validator<E> validator) {
        super(validator);
    }
}
