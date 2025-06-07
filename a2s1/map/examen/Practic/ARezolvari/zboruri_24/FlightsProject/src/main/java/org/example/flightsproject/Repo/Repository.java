package org.example.flightsproject.Repo;

import org.example.flightsproject.Domain.Entity;

import java.util.Optional;

public interface Repository <ID, E extends Entity<ID>> {
    Optional<E> findById(ID id);

    Iterable<E> findAll();

    Optional<E> save(E entity);

    Optional<E> update(E entity);

    Optional<E> delete(E entity);
}
