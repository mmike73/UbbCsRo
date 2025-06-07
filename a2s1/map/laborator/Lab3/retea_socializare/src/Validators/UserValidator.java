package Validators;

import Entities.User;

public class UserValidator implements Validator<User> {

    @Override
    public void validate(User entity) throws ValidationException {
        if ("".equals(entity.getUsername()))
            throw new ValidationException("Username cannot be empty");
    }
}
