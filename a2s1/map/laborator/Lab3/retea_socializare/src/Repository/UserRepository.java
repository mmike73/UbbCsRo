package Repository;

import Entities.Entity;
import Entities.User;
import Factories.UserFactory;
import Validators.Validator;

import java.io.*;
import java.util.ArrayList;
import java.util.List;

public class UserRepository extends AbstractFileRepository<String, User> {

    UserFactory userFactory;

    public UserRepository(String filePath, Validator validator) {
        super(filePath, validator);
        userFactory = UserFactory.getInstance();
        try {
            readFromFile();
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
    }

    @Override
    protected void readFromFile() throws FileNotFoundException {
        String line;
        String delimiter = ",";

        try (BufferedReader br = new BufferedReader(new FileReader(filePath))) {
            while ((line = br.readLine()) != null) {
                String[] values = line.split(delimiter);

                String uname = values[0];
                String pass = values[1];

                User user = userFactory.createUser(uname, pass);

                super.save(user);

            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Override
    protected void writeToFile() {
        try (FileWriter fw = new FileWriter(filePath)) {
            Iterable<User> users = findAll();
            users.forEach(user -> {

                try {
                    fw.write(user.getUsername() + ',' + user.getPassword() + '\n');
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }

            });
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Override
    public User update(User entity) {
        super.update(entity);
        writeToFile();
        return entity;
    }

    @Override
    public User delete(String o) {
        User du = super.delete(o);
        writeToFile();
        return du;
    }

    @Override
    public User save(User entity) {
        super.save((User) entity);
        writeToFile();
        return entity;
    }

    @Override
    public Iterable findAll() {
        return super.findAll();
    }

    @Override
    public User findOne(String o) {
        return super.findOne(o);
    }

}
