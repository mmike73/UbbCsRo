import Entities.Network;
import Entities.User;
import Factories.ValidatorFactory;
import Repository.FriendshipRepository;
import Repository.UserRepository;
import Service.NetworkService;
import Service.UserService;
import UserInterface.Controller;
import UserInterface.UI;
import Validators.FriendshipValidator;
import Validators.UserValidator;
import Validators.ValidStrategy;

public class Main {
    public static void main(String[] args) {

        Network network = new Network();

        ValidatorFactory vf = ValidatorFactory.getInstance();
        UserValidator userValidator = (UserValidator) vf.createValidator(ValidStrategy.USER);
        FriendshipValidator friendshipValidator = (FriendshipValidator) vf.createValidator(ValidStrategy.FRIENDSHIP);

        UserRepository userRepo = new UserRepository("/Volumes/D/Faculta/A2S1/MAP/Lab/Lab4/retea_socializare/data_storage/users.txt", userValidator);
        FriendshipRepository friendshipRepo = new FriendshipRepository(userRepo, "/Volumes/D/Faculta/A2S1/MAP/Lab/Lab4/retea_socializare/data_storage/friendships.txt", friendshipValidator);

        UserService userService = new UserService(userRepo);
        NetworkService networkService = new NetworkService(friendshipRepo, userRepo, network);

        Controller controller = new Controller(userService, networkService);

        UI ui = new UI(controller);

        ui.run();
    }
}