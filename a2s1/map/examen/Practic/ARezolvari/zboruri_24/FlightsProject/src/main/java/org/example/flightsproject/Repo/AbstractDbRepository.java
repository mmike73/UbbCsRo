package org.example.flightsproject.Repo;

import org.example.flightsproject.Domain.Entity;
import org.example.flightsproject.Infrastructure.DbConnection;

public abstract class AbstractDbRepository<ID, E extends Entity<ID>> implements Repository<ID, E> {
    protected DbConnection connection;

    public AbstractDbRepository(DbConnection dbConnection) {
        this.connection = dbConnection;
    }
}
