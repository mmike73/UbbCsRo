package org.example.Entities;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

public class User extends Entity<String> {
    private String username, password;
    List<User> friends;

    public User(String username, String password) {
        this.username = username;
        this.password = password;
        friends = new ArrayList<User>();
    }

    public String getId() {
        return username;
    }

    public String getUsername() {
        return username;
    }

    public String getPassword() {
        return password;
    }
    // maybe exclude
    public void setUsername(String username) {
        this.username = username;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public List<User> getFriends() {
        return friends;
    }

    public boolean equals(User user) {
        return Objects.equals(this.username, user.getUsername());
    }

    public boolean isFriend(User otUser) {
        return friends.contains(otUser);
    }

    public void addFriend(User friend) {
        if (!friends.contains(friend)) {
            friends.add(friend);
        }
    }

    public void removeFriend(String friend) {
        User frToDelete = null;
        for (User fr : friends) {
            if (fr.getUsername().equals(friend)) {
                frToDelete = fr;
            }
        }
        if (frToDelete != null) {
            friends.remove(frToDelete);
        }
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        User user = (User) o;
        return Objects.equals(username, user.username);
    }

    @Override
    public int hashCode() {
        return Objects.hash(username,password);
    }

    @Override
    public String toString() {
        return username;
    }
}
