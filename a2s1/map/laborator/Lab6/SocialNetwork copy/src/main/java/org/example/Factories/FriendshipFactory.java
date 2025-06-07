package org.example.Factories;

import org.example.Entities.Friendship;
import org.example.Entities.User;

public class FriendshipFactory {
    static final FriendshipFactory SINGLE_INSTANCE = new FriendshipFactory();

    private FriendshipFactory() {}

    public static FriendshipFactory getInstance() {
        return SINGLE_INSTANCE;
    }

    public Friendship createFriendship(String userName1, String userName2) {
        return new Friendship(userName1, userName2);
    }
}
