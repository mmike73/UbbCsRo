package Exceptions;

import Entities.Friendship;

public class FriendshipAlreadyExistingException extends RuntimeException {
    public FriendshipAlreadyExistingException(Friendship f) {

        super("Friendship between " + f.getUser1() + " and " + f.getUser2()  + " already exists!");
    }
}
