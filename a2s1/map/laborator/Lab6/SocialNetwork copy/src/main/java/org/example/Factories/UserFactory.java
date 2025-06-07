package org.example.Factories;

import org.example.Entities.User;

public class UserFactory {
    static final UserFactory SINGLE_INSTANCE = new UserFactory();

    private UserFactory() {}

    public static UserFactory getInstance() {
        return SINGLE_INSTANCE;
    }

    public User createUser(String name, String password) {
        return new User(name, password);
    }
}
