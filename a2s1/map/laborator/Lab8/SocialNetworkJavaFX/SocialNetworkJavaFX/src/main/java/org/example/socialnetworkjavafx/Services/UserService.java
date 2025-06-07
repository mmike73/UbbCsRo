package org.example.socialnetworkjavafx.Services;

import org.example.socialnetworkjavafx.Entities.User;
import org.example.socialnetworkjavafx.Exceptions.UserNotFoundException;
import org.example.socialnetworkjavafx.Repositories.Repository;
import org.example.socialnetworkjavafx.Utils.Event.ChangeType;
import org.example.socialnetworkjavafx.Utils.Event.UserEntityChangeEvent;
import org.example.socialnetworkjavafx.Utils.Observer.Observable;
import org.example.socialnetworkjavafx.Utils.Observer.Observer;


import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class UserService implements Observable<UserEntityChangeEvent> {
    private Repository<String, User> userRepository;
    private List<Observer<UserEntityChangeEvent>> observers = new ArrayList<>();


    public UserService(Repository<String, User> userRepository) {
        this.userRepository = userRepository;
    }

    public void addUser(User user) {
        if (!userRepository.findOne(user.getUsername()).isPresent()) {
            userRepository.save(user);
            UserEntityChangeEvent event = new UserEntityChangeEvent(ChangeType.ADD, user);
            notifyObservers(event);
        } else {
            throw new RuntimeException("Username already exists");
        }
    }

    public void removeUser(String username) {
        Optional<User> deleted = userRepository.delete(username);
        if (deleted.isPresent()) {
            UserEntityChangeEvent event = new UserEntityChangeEvent(ChangeType.DELETE, deleted.get());
            notifyObservers(event);
        }
    }

    /// modify???

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


    @Override
    public void addObserver(Observer<UserEntityChangeEvent> observer) {
        observers.add(observer);
    }

    @Override
    public void removeObserver(Observer<UserEntityChangeEvent> observer) {
        observers.remove(observer);
    }

    @Override
    public void notifyObservers(UserEntityChangeEvent event) {
        observers.forEach(observer -> observer.update(event));
    }

//unused
//    public void addFriend(String userName1, String userName2) throws UserNotFoundException {
//        Optional<User> oUser1 = userRepository.findOne(userName1);
//        Optional<User> oUser2 = userRepository.findOne(userName2);
//        if (!oUser1.isPresent() || !oUser2.isPresent()) {
//            throw new RuntimeException("Username not exists");
//        }
//    }
//
//    public void removeFriend(String userName1, String userName2) throws RuntimeException {
//        Optional<User> user = userRepository.findOne(userName1);
//        try {
//            if (user.isPresent()) {
//                user.get().removeFriend(userName2);
//
//            }
//        } catch (RuntimeException e) {
//            e.printStackTrace();
//        }
//    }
}
