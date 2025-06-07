package Service;

import Entities.Friendship;
import Entities.User;
import Exceptions.UserNotFoundException;
import Repository.UserRepository;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class UserService {
    UserRepository userRepository;

    public UserService(UserRepository userRepository) {
        this.userRepository = userRepository;
    }

    public void addUser(User user) {
        if (!userRepository.findOne(user.getUsername()).isPresent()) {
            userRepository.save(user);
        } else {
            throw new RuntimeException("Username already exists");
        }
    }

    public void addFriend(String userName1, String userName2) throws UserNotFoundException {
        Optional<User> oUser1 = userRepository.findOne(userName1);
        Optional<User> oUser2 = userRepository.findOne(userName2);
        if (oUser1.isPresent() && oUser2.isPresent()) {
            oUser1.get().addFriend(oUser2.get());
            oUser2.get().addFriend(oUser1.get());
        } else {
            throw new RuntimeException("Username not exists");
        }
    }

    public void removeFriend(String userName1, String userName2) throws RuntimeException {
        Optional<User> user = userRepository.findOne(userName1);
        try {
           if (user.isPresent()) {
                user.get().removeFriend(userName2);
            }
        } catch (RuntimeException e) {
            e.printStackTrace();
        }
    }

    public void removeUser(String username) {
        userRepository.delete(username);

        List<User> allUsers = getAllUsers();

        allUsers.forEach(user ->
            user.removeFriend(username)
        );
    }

    public User getUser(String username) throws UserNotFoundException {
        Optional<User> searched;
        try {
            searched = userRepository.findOne(username);
            if (searched.isPresent()) {
                return searched.get();
            }
        } catch (RuntimeException e) {
            throw new UserNotFoundException(username);
        }
        return null;
    }

    public List<User> getAllUsers() {
        Iterable<User> allUsers = userRepository.findAll();
        List<User> users = new ArrayList<>();

        allUsers.forEach(user -> users.add((User) user));

        return users;
    }


}
