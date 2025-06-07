package org.example.Factories;

import org.example.Validators.*;

public class ValidatorFactory {
    static final ValidatorFactory SINGLE_INSTANCE = new ValidatorFactory();

    private ValidatorFactory() {}

    public static ValidatorFactory getInstance() {
        return SINGLE_INSTANCE;
    }

    public Validator createValidator(ValidStrategy validStrategy) {
        return switch (validStrategy) {
            case USER -> new UserValidator();
            case FRIENDSHIP -> new FriendshipValidator();
            default -> throw new IllegalArgumentException("Invalid Strategy");
        };
    }
}
