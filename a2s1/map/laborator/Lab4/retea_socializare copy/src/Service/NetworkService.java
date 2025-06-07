package Service;

import Entities.Entity;
import Entities.Friendship;
import Entities.Network;
import Entities.User;
import Exceptions.FriendshipAlreadyExistingException;
import Exceptions.FriendshipNotFoundException;
import Factories.FriendshipFactory;
import Repository.FriendshipRepository;
import Repository.UserRepository;

import java.util.*;

public class NetworkService {
    FriendshipFactory friendshipFactory;
    FriendshipRepository friendshipRepository;
    UserRepository userRepository;
    Network network;

    public NetworkService(FriendshipRepository friendshipRepository, UserRepository userRepository, Network network) {
        this.friendshipRepository = friendshipRepository;
        this.userRepository = userRepository;
        this.network = network;
        friendshipFactory = FriendshipFactory.getInstance();
    }

    public void addFriendship(Friendship friendship) throws Exception {
        if (!friendshipRepository.findOne(friendship.hashCode()).isPresent()) {
            friendshipRepository.save(friendship);
        } else {
            throw new FriendshipAlreadyExistingException(friendship);
        }
    }

    public void removeFriendship(String username1, String username2) throws FriendshipNotFoundException {
        Optional<Friendship> toDelete1 = friendshipRepository.findOne(friendshipFactory.createFriendship(username1, username2).hashCode());
        Optional<Friendship> toDelete2 = friendshipRepository.findOne(friendshipFactory.createFriendship(username2, username1).hashCode());
        if (toDelete1.isPresent()) {
            friendshipRepository.delete(toDelete1.get().hashCode());
        } else if (toDelete1.isPresent()) {
            friendshipRepository.delete(toDelete2.get().hashCode());
        } else{
            throw new FriendshipNotFoundException(username1, username2);
        }
    }

    public List<Friendship> getAllFriendships() {
        Iterable<Friendship> allFriendships = friendshipRepository.findAll();
        List<Friendship> friendships = new ArrayList<>();

        allFriendships.forEach(f -> friendships.add(f));

        return friendships;
    }

    public void removeFriendshipsOfDeleted(String username) {
        Iterable<Friendship> allFriendships = friendshipRepository.findAll();
        List<Friendship> toDetlete = new ArrayList<>();

        allFriendships.forEach(f -> {
            if (Objects.equals(f.getUser1(), username)) {
                toDetlete.add(f);
            }
            if (Objects.equals(f.getUser2(), username)) {
                toDetlete.add(f);
            }
        });

        toDetlete.forEach(f -> friendshipRepository.delete(f.hashCode()));
    }

    public int numberOfCommunities() {
        Iterable users = userRepository.findAll();
        List<User> userList = new ArrayList<>();
        List<Friendship> friendships = getAllFriendships();

        Map<String, List<String>> adjacencyList = new HashMap<>();

        users.forEach(user -> {
            User us = (User) user;
            adjacencyList.put(us.getUsername(), new ArrayList<>());
            userList.add(us);
        });

        for (Friendship friendship : friendships) {
            adjacencyList.get(friendship.getUser1()).add(friendship.getUser2());
            adjacencyList.get(friendship.getUser2()).add(friendship.getUser1());
        }

        Set<String> visited = new HashSet<>();
        int cnt = 0;

        for (User user : userList) {
            if (!visited.contains(user.getUsername())) {
                cnt++;
                dfs(user.getUsername(), adjacencyList, visited);
            }
        }
        return cnt;
    }

    private void dfs(String username, Map<String, List<String>> adjacencyList, Set<String> visited) {
        visited.add(username);
        for (String neighbor : adjacencyList.get(username)) {
            if (!visited.contains(neighbor)) {
                dfs(neighbor, adjacencyList, visited);
            }
        }
    }

    public List<String> theMostSociableComunity() {
        Iterable users = userRepository.findAll();
        List<User> userList = new ArrayList<>();
        List<Friendship> friendships = getAllFriendships();


        Map<String, List<String>> adjacencyList = new HashMap<>();

        users.forEach(user -> {
            User us = (User) user;
            adjacencyList.put(us.getUsername(), new ArrayList<>());
            userList.add(us);
        });

        for (Friendship friendship : friendships) {
            adjacencyList.get(friendship.getUser1()).add(friendship.getUser2());
            adjacencyList.get(friendship.getUser2()).add(friendship.getUser1());
        }
        List<String> largestCom = new ArrayList<>();

        users = friendshipRepository.findAll();
        for (User user : userList) {
            Set<String> visited = new HashSet<>();
            dfs(user.getUsername(), adjacencyList, visited);
            if (visited.size() > largestCom.size()) {
                largestCom.clear();
                largestCom.addAll(visited);
            }
        }
        return largestCom;
    }
}
