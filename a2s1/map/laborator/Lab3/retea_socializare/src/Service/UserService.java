package Service;

import Entities.Friendship;
import Entities.User;
import Exceptions.UserNotFoundException;
import Repository.UserRepository;

import java.util.ArrayList;
import java.util.List;

public class UserService {
    UserRepository userRepository;

    public UserService(UserRepository userRepository) {
        this.userRepository = userRepository;
    }

    public void addUser(User user) {
        if (userRepository.findOne(user.getUsername()) == null) {
            userRepository.save(user);
        } else {
            throw new RuntimeException("Username already exists");
        }
    }

    public void addFriend(String userName1, String userName2) throws UserNotFoundException {
        User user1 = userRepository.findOne(userName1);
        User user2 = userRepository.findOne(userName2);
        if (user1 != null && user2 != null) {
            user1.addFriend(user2);
            user2.addFriend(user1);
        } else {
            throw new RuntimeException("Username not exists");
        }
    }

    public void removeFriend(String userName1, String userName2) throws RuntimeException {
        User user = userRepository.findOne(userName1);
        try {
            user.removeFriend(userName2);
        } catch (RuntimeException e) {
            e.printStackTrace();
        }
    }

    public void removeUser(String username) {
        userRepository.delete(username);

        List<User> allUsers = getAllUsers();

        for (User user : allUsers) {
            user.removeFriend(username);
        }
    }

    public User getUser(String username) throws UserNotFoundException {
        User searched = null;
        try {
            searched = userRepository.findOne(username);
        } catch (RuntimeException e) {
            throw new UserNotFoundException(username);
        }
        return searched;
    }

    public List<User> getAllUsers() {
        Iterable allUsers = userRepository.findAll();
        List<User> users = new ArrayList<>();

        allUsers.forEach(user -> users.add((User) user));

        return users;
    }


}
