package org.example.socialnetworkjavafx.Entities;

public class Entity<ID>  {

    private ID id;

    public ID getId() {
        System.out.println(id);
        return id;
    }

    public void setId(ID id) {
        this.id = id;
    }
}