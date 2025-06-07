package org.example.flightsproject.Domain;

public class Client extends Entity<Long> {

    String username, name;

    public Client(String name, String username) {
        this.name = name;
        this.username = username;
    }

    public Client(Long clientId, String name, String username) {
        this.setId(clientId);
        this.name = name;
        this.username = username;
    }

    public boolean authenticate() {
        return true;
    }

    public boolean authenticate(String password) {
        return true;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }
}
