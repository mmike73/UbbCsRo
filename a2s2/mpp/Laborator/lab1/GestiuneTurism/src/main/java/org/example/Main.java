package org.example;

import org.example.infrastructure.*;

public class Main {
    public static void main(String[] args) {

        DbConnection dbConnection = new DbConnection(
                "jdbc:postgresql://localhost:5432/GestiuneTurism/",
                "mihai",
                "mpp"
        );

        AngajatRepository angajatRepository = new AngajatRepository(dbConnection);
        AgentieRepository agentieRepository = new AgentieRepository(dbConnection);
        ExcursieRepository excursieRepository = new ExcursieRepository(dbConnection);
        RezervareRepository rezervareRepository = new RezervareRepository(dbConnection);

        System.out.println("Correct");
    }
}