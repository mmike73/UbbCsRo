package UserInterface;

import Entities.Friendship;
import Entities.User;
import Exceptions.FriendshipNotFoundException;
import Service.NetworkService;
import Service.UserService;

import java.util.InputMismatchException;
import java.util.List;

import java.util.Scanner;

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


    Scanner scanner = new Scanner(System.in);
    Controller controller;
    User loggedUser;
    int input = -1;

    public UI(Controller controller) {
        this.controller  = controller;
        loggedUser = null;
    }

    private void MenuPrint() {
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

    private void MenuSelection1() {
        if (loggedUser != null) {
            System.out.println("Username of the friend: ");
            String username = scanner.next();
            try {
                controller.addFriend(loggedUser.getUsername(), username);
            } catch (Exception e) {
                System.err.println(e.getMessage());
            }
        } else {
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
    }

    private void MenuSelection2() {
        if (loggedUser != null) {
            System.out.println("Username of the friend: ");
            String username = scanner.next();
            try {
                controller.removeFriend(loggedUser.getUsername(), username);
            } catch (FriendshipNotFoundException e) {
                System.err.println(e.getMessage());
            }
        } else {
            System.out.println("Set your username: ");
            String username = scanner.next();
            System.out.println("Set your password: ");
            String password = scanner.next();
            loggedUser = controller.registerUser(username, password);
        }
    }

    private void MenuSelection3() {
        if (loggedUser != null) {
            loggedUser = null;
        } else {
            List<User> usrs = controller.getAllUsers();
            for (User user : usrs)
                System.out.println(user.toString());
        }
    }

    private void MenuSelectionLogged4() {}

    private void MenuSelectionUnlogged4() {
        List<Friendship> friendships = controller.getAllFriendships();
        for (Friendship friendship : friendships)
            System.out.println(friendship.toString());
    }

    private void MenuSelectionLogged5() {}

    private void MenuSelectionUnlogged5() {
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

    private void MenuSelectionLogged6() {}

    private void MenuSelectionUnlogged6() {
        int communities = controller.getNumberOfCommunities();
        System.out.println("Number of communities: " + communities);
    }

    private void MenuSelectionLogged7() {}

    private void MenuSelectionUnlogged7() {
        List<String> mostSociable = controller.getMostSociableCom();
        for (String username : mostSociable) {
            System.out.println(username);
        }
    }

    private void MenuSelectionLogged8() {
        System.exit(0);

    }

    private void MenuSelectionUnlogged8() {}

    public void run() {
        Scanner scanner = new Scanner(System.in);

        System.out.println("Welcome to Twisted Connections!");

        while (true) {
            MenuPrint();

            System.out.println(">>> ");
            try {
                input = scanner.nextInt();
            } catch (InputMismatchException e) {
                System.out.println("Please enter a valid number");
                scanner.nextLine();
                continue;
            }

            if (input == 1) MenuSelection1();
            else if (input == 2) MenuSelection2();
            else if (input == 3)  MenuSelection3();
            else if (input == 4) {
                if (loggedUser != null) MenuSelectionLogged4();
                else MenuSelectionUnlogged4();
            } else if(input == 5) {
                if (loggedUser != null) MenuSelectionLogged5();
                else MenuSelectionUnlogged5();
            } else if (input == 6) {
                if (loggedUser != null) MenuSelectionLogged6();
                else MenuSelectionUnlogged6();
            } else if (input == 7) {
                if (loggedUser != null) MenuSelectionLogged7();
                else MenuSelectionUnlogged7();
            } else if (input == 8) MenuSelectionLogged8();
            else {
                System.out.print("Invalid input!");
            }
        }
    }
}
