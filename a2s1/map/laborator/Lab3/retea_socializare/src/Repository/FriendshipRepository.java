package Repository;

import Entities.Entity;
import Entities.Friendship;
import Entities.User;
import Factories.FriendshipFactory;
import Validators.FriendshipValidator;
import Validators.Validator;

import java.io.*;
import java.util.ArrayList;
import java.util.List;

public class FriendshipRepository extends AbstractFileRepository<Integer, Friendship> {

    FriendshipFactory friendshipFactory;
    UserRepository userRepository;

    public FriendshipRepository(UserRepository userRepo, String filePath, Validator validator) {
        super(filePath, validator);
        friendshipFactory = FriendshipFactory.getInstance();
        userRepository = userRepo;
        readFromFile();
    }

    @Override
    protected void readFromFile() {
        String line;
        String delimiter = ",";

        try (BufferedReader br = new BufferedReader(new FileReader(filePath))) {
            while ((line = br.readLine()) != null) {
                String[] values = line.split(delimiter);

                String uname1 = values[0];
                String uname2 = values[1];

                Friendship fship = friendshipFactory.createFriendship(uname1, uname2);
                userRepository.findOne(uname1).addFriend(userRepository.findOne(uname2));
                userRepository.findOne(uname2).addFriend(userRepository.findOne(uname1));

                super.save(fship);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Override
    protected void writeToFile() {
        try (FileWriter fw = new FileWriter(filePath)) {
            Iterable<Friendship> friendships = findAll();
            friendships.forEach(friendship -> {
                try {
                    fw.write(friendship.getUser1() + ',' +friendship.getUser2() + '\n');
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }
            });
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    @Override
    public Friendship update(Friendship entity) {
        super.update(entity);
        writeToFile();
        return entity;
    }

    @Override
    public Friendship delete(Integer o) {
        Friendship df = super.delete(o);
        writeToFile();
        return df;
    }

    @Override
    public Friendship save(Friendship entity) {
        super.save(entity);
        writeToFile();
        return entity;
    }

    @Override
    public Iterable findAll() {
        return super.findAll();
    }

    @Override
    public Friendship findOne(Integer o) {
        return super.findOne(o);
    }
}
