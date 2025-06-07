package UserInterface;

import Entities.Friendship;
import Entities.User;
import Exceptions.FriendshipNotFoundException;
import Service.NetworkService;
import Service.UserService;

import java.util.*;
import java.util.function.*;

public class UI {
    private static String[] enntryPointMenu = {
            "1. log in",
            "2. register",
            "3. userlist",
            "4. friendshiplist",
            "5. remove_user",
            "6. number of communities",
            "7. the most sociable community",
            "8. exit"
    };
    private static String[] loggeUserMenu = {
            "1. add friend",
            "2. remove friend",
            "3. log out",
            "4. my group ... comming soon",
            "5. message ... comming soon",
            "6. comming soon",
            "7. comming soon",
            "8. exit"
    };

    private final Scanner scanner = new Scanner(System.in);
    private Controller controller;
    private User loggedUser;
    private int input = -1;

    public UI(Controller controller) {
        this.controller  = controller;
        loggedUser = null;
    }

    public void run() {
        Scanner scanner = new Scanner(System.in);

        System.out.println("Welcome to Twisted Connections!");

        while (true) {
            PrintMenu();
            System.out.print(">>> ");
            try {
                input = scanner.nextInt();
                Runnable toCall = loggedUser == null ?
                        menuOptionsNoUser.get(input) : menuOptionsLoggedUser.get(input);

                Optional.ofNullable(toCall).ifPresentOrElse(Runnable::run,
                        () -> System.out.println("Invalid input!"));
            } catch (InputMismatchException e) {
                System.out.println(e.getMessage());
                scanner.nextLine();
            }
        }
    }


    private void PrintMenu() {
        if (loggedUser == null) {
            for (String menuLine : enntryPointMenu) {
                System.out.println(menuLine);
            }
        } else {
            System.out.println("+++ You are " + loggedUser.toString() + " +++");
            for (String menuLine : loggeUserMenu) {
                System.out.println(menuLine);
            }
        }
    }

    private final Map<Integer, Runnable> menuOptionsNoUser = new HashMap<>() {{
        put(1, UI.this::logIn);
        put(2, UI.this::register);
        put(3, () -> controller.getAllUsers().forEach(System.out::println));
        put(4, () -> controller.getAllFriendships().forEach(System.out::println));
        put(5, UI.this::deleteUser);
        put(6, () -> System.out.println("Number of communities: " + controller.getNumberOfCommunities()));
        put(7, () -> controller.getMostSociableCom().forEach(System.out::println));
        put(8, () -> System.exit(0));
    }};

    private final Map<Integer, Runnable> menuOptionsLoggedUser = new HashMap<>() {{
        put(1, UI.this::addFriend);
        put(2, UI.this::removeFriend);
        put(3, UI.this::logOut);
        put(4, null);
        put(5, null);
        put(6, () -> System.out.println("Number of communities: " + controller.getNumberOfCommunities()));
        put(7, () -> controller.getMostSociableCom().forEach(System.out::println));
        put(8, () -> System.exit(0));
    }};

    private void addFriend() {
        if (loggedUser != null) {
            System.out.println("Username of the friend: ");
            String username = scanner.next();
            try {
                controller.addFriend(loggedUser.getUsername(), username);
            } catch (Exception e) {
                System.err.println(e.getMessage());
            }
        }
    }

    private void logIn() {
        System.out.println("Username: ");
        String username = scanner.next();
        System.out.println("Password: ");
        String password = scanner.next();
        try {
            loggedUser = controller.logIn(username, password);
        } catch (Exception e) {
            System.err.println(e.getMessage());
        }
    }

    private void removeFriend() {
        System.out.println("Username of the friend: ");
        String username = scanner.next();
        try {
            controller.removeFriend(loggedUser.getUsername(), username);
        } catch (FriendshipNotFoundException e) {
            System.err.println(e.getMessage());
        }
    }

    private void register() {
        System.out.println("Set your username: ");
        String username = scanner.next();
        System.out.println("Set your password: ");
        String password = scanner.next();
        loggedUser = controller.registerUser(username, password);
    }

    private void logOut() {
        loggedUser = null;
    }

    private void deleteUser() {
        System.out.println("Username: ");
        String username = scanner.next();
        System.out.println("Password: ");
        String password = scanner.next();
        try {
            controller.removeUser(username, password);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }
}
