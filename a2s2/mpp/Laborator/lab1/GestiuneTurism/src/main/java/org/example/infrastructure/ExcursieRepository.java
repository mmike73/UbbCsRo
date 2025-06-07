package org.example.infrastructure;

import org.example.domain.Excursie;
import org.example.repo.AbstractDbRepository;

import java.util.Optional;

public class ExcursieRepository extends AbstractDbRepository<Integer, Excursie> {
    public ExcursieRepository(DbConnection dbConnection) {
        super(dbConnection);
    }

    @Override
    public Optional<Excursie> delete(Excursie entity) {
        return Optional.empty();
    }

    @Override
    public Optional<Excursie> findById(Integer integer) {
        return Optional.empty();
    }

    @Override
    public Iterable<Excursie> findAll() {
        return null;
    }

    @Override
    public Optional<Excursie> save(Excursie entity) {
        return Optional.empty();
    }

    @Override
    public Optional<Excursie> update(Excursie entity) {
        return Optional.empty();
    }
}
