package org.example.socialnetworkjavafx.Repositories;

import org.example.socialnetworkjavafx.Entities.Entity;
import org.example.socialnetworkjavafx.Utils.Dtos.FilterDTO;
import org.example.socialnetworkjavafx.Utils.Paging.Page;
import org.example.socialnetworkjavafx.Utils.Paging.Pageable;

import java.sql.Connection;
import java.util.Optional;

public abstract class AbstractPagingDbRepository<ID, E extends Entity<ID>, Filter extends FilterDTO<E>> implements PagingRepository<ID, E, Filter> {
    protected Connection connection;

    public AbstractPagingDbRepository(Connection connection) {
        this.connection = connection;
    };

    @Override
    public int count(Filter filters) {
        return 0;
    }

    @Override
    public int countAll() {
        return 0;
    }

    @Override
    public abstract Page<E> findAllOnPage(Pageable pageable, Filter filter);

    @Override
    public abstract Page<E> findAllOnPage(Pageable pageable);

    @Override
    public abstract Optional<E> findOne(ID id);

    @Override
    public abstract Iterable<E> findAll();

    @Override
    public Optional<E> save(E friendship) {
        return Optional.empty();
    }

    @Override
    public Optional<E> delete(ID id) {
        return Optional.empty();
    }

    @Override
    public Optional<E> update(E friendship) {
        return Optional.empty();
    }
}
