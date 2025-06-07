package org.example.Service;

import org.example.Entities.Friendship;
import org.example.Entities.Network;
import org.example.Entities.User;
import org.example.Exceptions.AcceptFriendshipException;
import org.example.Exceptions.FriendshipAlreadyExistingException;
import org.example.Exceptions.FriendshipNotFoundException;
import org.example.Factories.FriendshipFactory;
import org.example.Infrastructure.FriendshipRepository;
import org.example.Infrastructure.UserDbRepository;
import org.example.Infrastructure.UserRepository;
import org.example.Repository.Repository;

import java.time.LocalDateTime;
import java.util.*;
import java.util.function.Predicate;

public class NetworkService {
    FriendshipFactory friendshipFactory;
    Repository<Integer, Friendship>  friendshipRepository;
    Repository<String, User> userRepository;
    Network network;

    public NetworkService(Repository<Integer, Friendship> friendshipRepository, Repository<String, User> userRepository, Network network) {
        this.friendshipRepository = friendshipRepository;
        this.userRepository = userRepository;
        this.network = network;
        friendshipFactory = FriendshipFactory.getInstance();
    }

    public void addFriendship(Friendship friendship) throws Exception {
        Predicate<Friendship> friendshipExists = f -> friendshipRepository.findOne(f.hashCode()).isPresent();

        if (!friendshipExists.test(friendship)) {
            friendshipRepository.save(friendship);
        } else {
            throw new FriendshipAlreadyExistingException(friendship);
        }
    }

    public void acceptFriendship(String loggedUser, String username) throws Exception, AcceptFriendshipException {
        Friendship toAccept = getAFriendship(loggedUser, username);
        if (toAccept.getInitiator().equals(loggedUser)) {
            throw new AcceptFriendshipException();
        }
        toAccept.Accept();
        toAccept.setDateTime(LocalDateTime.now());
        friendshipRepository.update(toAccept);
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

    public Friendship getAFriendship(String username1, String username2) throws FriendshipNotFoundException {
        Friendship to_search = friendshipFactory.createFriendship(username1, username2);
        Optional<Friendship> friendship =  friendshipRepository.findOne(to_search.hashCode());
        if (friendship.isPresent()) {
            return friendship.get();
        }
        to_search = friendshipFactory.createFriendship(username2, username1);
        friendship =  friendshipRepository.findOne(to_search.hashCode());
        if (friendship.isPresent()) {
            return friendship.get();
        }
        throw new FriendshipNotFoundException(username1, username2);
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
