package org.example;

import java.io.FileReader;
import java.io.IOException;
import java.util.Properties;

public class Main {
    public static void main(String[] args) {

        Properties props=new Properties();
        try {
            props.load(new FileReader("/Volumes/D/Faculta/A2S2/MPP/Laborator/lab1/GestiuneTurism/untitled/src/main/java/org/example/bd.config"));
        } catch (IOException e) {
            System.out.println("Cannot find bd.config "+e);
        }

        CarsDBRepository carRepo = new CarsDBRepository(props);

//        carRepo.add(new Car("VW", "Polo", 2006));
//        carRepo.add(new Car("Rolls Royce", "Phantom", 1972));
//        carRepo.add(new Car("VW", "Passat", 1995));



        System.out.println("Toate masinile din db");
        for(Car car:carRepo.findAll())
            System.out.println(car);
        String manufacturer="VW";
        System.out.println("Masinile produse de "+manufacturer);
        for(Car car:carRepo.findByManufacturer(manufacturer))
            System.out.println(car);

    }
}
