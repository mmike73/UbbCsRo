package Repository;

import Entities.Friendship;
import Entities.User;
import Factories.FriendshipFactory;
import Validators.Validator;

import java.io.*;
import java.util.Optional;

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
                Optional<User> oUser2 = userRepository.findOne(uname2);
                Optional<User> oUser1 = userRepository.findOne(uname1);
                if (oUser2.isPresent() && oUser1.isPresent()) {
                    oUser1.get().addFriend(oUser2.get());
                    oUser2.get().addFriend(oUser1.get());
                }

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
    public Optional<Friendship> update(Friendship entity) {
        super.update(entity);
        writeToFile();
        return Optional.of(entity);
    }

    @Override
    public Optional<Friendship> delete(Integer o) {
        Optional<Friendship> oDf = super.delete(o);
        if (oDf.isPresent()) {
            writeToFile();
            return oDf;
        }
        return Optional.empty();
    }

    @Override
    public Optional<Friendship> save(Friendship entity) {
        super.save(entity);
        writeToFile();
        return Optional.of(entity);
    }

    @Override
    public Iterable findAll() {
        return super.findAll();
    }

    @Override
    public Optional<Friendship> findOne(Integer o) {
        return super.findOne(o);
    }
}
