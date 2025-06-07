package org.example.infrastructure;

import org.example.domain.AgentieTurism;
import org.example.repo.AbstractDbRepository;

import java.util.Optional;

public class RezervareRepository extends AbstractDbRepository<Integer, AgentieTurism> {
    public RezervareRepository(DbConnection dbConnection) {
        super(dbConnection);
    }

    @Override
    public Optional<AgentieTurism> delete(AgentieTurism entity) {
        return Optional.empty();
    }

    @Override
    public Optional<AgentieTurism> findById(Integer integer) {
        return Optional.empty();
    }

    @Override
    public Iterable<AgentieTurism> findAll() {
        return null;
    }

    @Override
    public Optional<AgentieTurism> save(AgentieTurism entity) {
        return Optional.empty();
    }

    @Override
    public Optional<AgentieTurism> update(AgentieTurism entity) {
        return Optional.empty();
    }
}
