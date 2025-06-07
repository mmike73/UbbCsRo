 package org.example.Validators;

public interface Validator<T> {
    void validate(T entity); //throws ValidationException;
}
