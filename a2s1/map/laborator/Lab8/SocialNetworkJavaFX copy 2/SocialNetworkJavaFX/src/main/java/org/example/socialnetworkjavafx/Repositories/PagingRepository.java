package org.example.socialnetworkjavafx.Repositories;

import org.example.socialnetworkjavafx.Entities.Entity;
import org.example.socialnetworkjavafx.Utils.Dtos.FilterDTO;
import org.example.socialnetworkjavafx.Utils.Paging.Page;
import org.example.socialnetworkjavafx.Utils.Paging.Pageable;

import java.util.Optional;

public interface PagingRepository<ID, E extends Entity<ID>, Filter extends FilterDTO<E>> extends Repository<ID, E> {
    Page<E> findAllOnPage(Pageable pageable);
    Page<E> findAllOnPage(Pageable pageable, Filter filters);

    int count(Filter filters);
    int countAll();

    Optional<E> save(E friendship);

    Optional<E> delete(ID id);

    Optional<E> update(E friendship);
}
