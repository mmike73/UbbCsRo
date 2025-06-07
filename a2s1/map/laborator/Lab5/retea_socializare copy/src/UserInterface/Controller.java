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
        User potential = userService.getUser(username);
        System.out.println(potential.hashCode() + " " + userFactory.createUser(username, password).hashCode());
        if (potential != null && potential.hashCode() == userFactory.createUser(username, password).hashCode())
            return potential;
        return null;
    }

    public User registerUser(String username, String password) {
        User potential = userFactory.createUser(username, password);
        try {
            userService.addUser(potential);
            return potential;
        } catch (Exception e) {
            /// trateaza calumea
            e.printStackTrace();
        }
        return null;
    }

    public void removeUser(String username, String password) {
        User potential = userService.getUser(username);
        if (potential != null && potential.hashCode() == userFactory.createUser(username, password).hashCode()) {
            ntwService.removeFriendshipsOfDeleted(username);
            userService.removeUser(username);
        }
    }

    public void  addFriend(String username1, String username2) throws UserNotFoundException, Exception {
        if (!"".equals(username1) || "".equals(username2)) {
            userService.addFriend(username1, username2);
            Friendship friendship = friendshipFactory.createFriendship(username1, username2);
            ntwService.addFriendship(friendship);
        }
    }

    public void removeFriend(String username1, String username2) throws FriendshipNotFoundException {
        if (!"".equals(username2)) {
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
