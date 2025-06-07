package org.example.infrastructure;

import org.example.domain.Angajat;
import org.example.repo.AbstractDbRepository;

import java.util.Optional;

public class AngajatRepository extends AbstractDbRepository<Integer, Angajat> {
    public AngajatRepository(DbConnection dbConnection) {
        super(dbConnection);
    }

    @Override
    public Optional<Angajat> delete(Angajat entity) {
        return Optional.empty();
    }

    @Override
    public Optional<Angajat> findById(Integer integer) {
        return Optional.empty();
    }

    @Override
    public Iterable<Angajat> findAll() {
        return null;
    }

    @Override
    public Optional<Angajat> save(Angajat entity) {
        return Optional.empty();
    }

    @Override
    public Optional<Angajat> update(Angajat entity) {
        return Optional.empty();
    }
}
