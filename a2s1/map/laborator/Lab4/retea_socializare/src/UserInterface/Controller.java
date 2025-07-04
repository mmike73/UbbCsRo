package UserInterface;

import Entities.Friendship;
import Entities.User;
import Exceptions.FriendshipNotFoundException;
import Exceptions.UserNotFoundException;
import Factories.FriendshipFactory;
import Factories.UserFactory;
import Service.NetworkService;
import Service.UserService;

import java.util.List;
import java.util.Optional;
import java.util.function.Consumer;
import java.util.function.Predicate;
import java.util.function.Supplier;

public class Controller {
    private NetworkService ntwService;
    private UserService userService;
    private UserFactory userFactory;
    private FriendshipFactory friendshipFactory;

    public Controller(UserService userService, NetworkService ntwService) {
        this.ntwService = ntwService;
        this.userService = userService;
        userFactory = UserFactory.getInstance();
        friendshipFactory = FriendshipFactory.getInstance();
    }

    public User logIn(String username, String password) {
        return Optional.ofNullable(userService.getUser(username))
                .filter(user -> user.hashCode() == userFactory.createUser(username, password).hashCode())
                .orElse(null);
        /*
        User potential = userService.getUser(username);
        System.out.println(potential.hashCode() + " " + userFactory.createUser(username, password).hashCode());
        if (potential != null && potential.hashCode() == userFactory.createUser(username, password).hashCode())
            return potential;
        return null;
        */
    }

    public User registerUser(String username, String password) {
        User potential = userFactory.createUser(username, password);

        Consumer<User> addUser = user -> {
            try {
                userService.addUser(user);
            } catch (UserNotFoundException e) {
                e.getMessage();
            }
        };

        Optional.ofNullable(potential).ifPresent(addUser);
        return null;
    }

    public void removeUser(String username, String password) {
        Supplier<User> userSupplier = () -> userFactory.createUser(username, password);
        Predicate<User> userMatch = user -> user.hashCode() == userFactory.createUser(username, password).hashCode();

        Optional.ofNullable(userSupplier.get())
                .filter(userMatch)
                .ifPresent(user -> {
                    ntwService.removeFriendshipsOfDeleted(username);
                    userService.removeUser(username);
                });

        /*User potential = userService.getUser(username);
        if (potential != null && potential.hashCode() == userFactory.createUser(username, password).hashCode()) {
            ntwService.removeFriendshipsOfDeleted(username);
            userService.removeUser(username);
        }*/
    }

    public void  addFriend(String username1, String username2) throws UserNotFoundException, Exception {
        Predicate<String> valisUsername = name -> !name.trim().isEmpty();

        if (valisUsername.test(username1) && valisUsername.test(username2)) {
            userService.addFriend(username1, username2);
            Friendship friendship = friendshipFactory.createFriendship(username1, username2);
            ntwService.addFriendship(friendship);
        }
    }

    public void removeFriend(String username1, String username2) throws FriendshipNotFoundException {
        Predicate<String> validUsername = name -> !name.trim().isEmpty();

        if (validUsername.test(username1) && validUsername.test(username2)) {
            ntwService.removeFriendship(username1, username2);
            userService.removeFriend(username1, username2);
            userService.removeFriend(username2, username1);
        }
    }

    public List<User> getAllUsers() {
        List<User> usrs = userService.getAllUsers();
        return usrs;
    }

    public  List<Friendship> getAllFriendships() {
        List<Friendship> frsps = ntwService.getAllFriendships();
        return frsps;
    }

    public int getNumberOfCommunities() {
        return ntwService.numberOfCommunities();
    }

    public List<String> getMostSociableCom() {
        return ntwService.theMostSociableComunity();
    }


}
