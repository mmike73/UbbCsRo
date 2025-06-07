package Lab2.Factories;

import Lab2.Containers.Container;
import Lab2.Containers.ContainerStrategy;


public interface Factory {
    Container createContainer(ContainerStrategy strategy);
}
