package org.example.Exceptions;

public class UserNotFoundException extends RuntimeException {
    public UserNotFoundException(String user) {

        super("User " + user + " not found");
    }
}
