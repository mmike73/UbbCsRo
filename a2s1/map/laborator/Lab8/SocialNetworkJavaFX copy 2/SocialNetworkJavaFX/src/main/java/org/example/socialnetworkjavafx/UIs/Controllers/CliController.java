package org.example.socialnetworkjavafx.UIs.Controllers;

import org.example.socialnetworkjavafx.Entities.Friendship;
import org.example.socialnetworkjavafx.Entities.Message;
import org.example.socialnetworkjavafx.Entities.User;
import org.example.socialnetworkjavafx.Exceptions.FriendshipNotFoundException;
import org.example.socialnetworkjavafx.Exceptions.UserNotFoundException;
import org.example.socialnetworkjavafx.Factories.FriendshipFactory;
import org.example.socialnetworkjavafx.Factories.MessageFactory;
import org.example.socialnetworkjavafx.Factories.UserFactory;
import org.example.socialnetworkjavafx.Services.MessageService;
import org.example.socialnetworkjavafx.Services.NetworkService;
import org.example.socialnetworkjavafx.Services.UserService;
import org.example.socialnetworkjavafx.Utils.Paging.Page;
import org.example.socialnetworkjavafx.Utils.Paging.Pageable;
import org.example.socialnetworkjavafx.Validators.MessageValidator;
import org.example.socialnetworkjavafx.Utils.Dtos.FriendshipFilterDTO;


import java.util.ArrayList;
import java.util.List;
import java.util.Optional;
import java.util.function.Consumer;
import java.util.function.Predicate;
import java.util.function.Supplier;

public class CliController {
    private NetworkService ntwService;
    private UserService userService;
    private MessageService messageService;
    private UserFactory userFactory;
    private FriendshipFactory friendshipFactory;
    private MessageFactory messageFactory;

    private MessageValidator messageValidator;

    public CliController(UserService userService, NetworkService ntwService, MessageService messageService) {
        this.ntwService = ntwService;
        this.userService = userService;
        userFactory = UserFactory.getInstance();
        friendshipFactory = FriendshipFactory.getInstance();
        messageFactory = MessageFactory.getInstance();
        this.messageService = messageService;

        messageValidator = new MessageValidator();
    }

    public User logIn(String username, String password) {
        return Optional.ofNullable(userService.getUser(username))
                .filter(user -> user.hashCode() == userFactory.createUser(username, password).hashCode())
                .orElse(null);
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
    }

    public void  addFriend(String username1, String username2) throws UserNotFoundException, Exception {
        Predicate<String> valisUsername = name -> !name.trim().isEmpty();

        if (valisUsername.test(username1) && valisUsername.test(username2)) {
            // userService.addFriend(username1, username2);
            Friendship friendship = friendshipFactory.createFriendship(username1, username2);
            ntwService.addFriendship(friendship);
        }
    }

    public void acceptFriendship(String loggedUser, String username) throws Exception {
        ntwService.acceptFriendship(loggedUser, username);
    }

    public void declineFriendship(String loggedUser, String username) {
        ntwService.removeFriendship(loggedUser, username);
    }

    public void removeFriend(String username1, String username2) throws FriendshipNotFoundException {
        Predicate<String> validUsername = name -> !name.trim().isEmpty();

        if (validUsername.test(username1) && validUsername.test(username2)) {
            ntwService.removeFriendship(username1, username2);
        }
    }

    public User getUser(String username) {
        return userService.getUser(username);
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

    public void sendMessage(String sender, String receiver, String message) {
        try {
            Message msg = messageFactory.createMessage(sender, receiver, message);
            System.out.println(msg);
            messageValidator.validate(msg);

            messageService.addMessage(msg);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void sendMessageToMultipleUsers(String sender, List<String> receiver, String message) {
        receiver.forEach(user -> sendMessage(sender, user, message));
    }

    public void replyToMessage(Integer messageId, String sender, String receiver, String message) {
        try {
            Message msg = messageFactory.createMessage(sender, receiver, message, messageId);
            messageValidator.validate(msg);
            messageService.addMessage(msg);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public List<Message> getAllMessagesOf(String sender, String receiver) {
        try {
            return messageService.getAllMessagesOf(sender, receiver);
        } catch (Exception e) {
            e.printStackTrace();
        }
        return new ArrayList<>();
    }


    public Page<Friendship> findAllOnPage(Pageable pageable) {
        return ntwService.findAllOnPage(pageable);
    }

    public Page<Friendship> findAllOnPage(Pageable pageable, FriendshipFilterDTO movieFilterDTO) {
        return ntwService.findAllOnPage(pageable, movieFilterDTO);
    }

    public int countFriendships(String username) {
        FriendshipFilterDTO filter = new FriendshipFilterDTO(Optional.of(username), Optional.empty(), Optional.empty());
        return ntwService.countFriendshipsFiltered(filter);
    }

    public int countAllFriendships() {
        return ntwService.countFAllriendships();
    }
}
