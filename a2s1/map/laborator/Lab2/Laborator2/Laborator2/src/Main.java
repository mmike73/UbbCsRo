import java.time.LocalDateTime;

import Lab2.Sorters.SortingStrategies;
import Lab2.TaskRunners.*;
import Lab2.Containers.*;
import Lab2.Tasks.*;

public class Main {
    private static void run(StrategyTaskRunner s) {

        s.addTask(new MessageTask("Introducere", "1", "Cum o fost azi?","Anonim", "Burci", LocalDateTime.now()));
        s.addTask(new MessageTask("Introducere", "2", "Așa de bine e... faaaai de mine, incat trebuia sa ma lupt cu un urs si sa omor un urs din-ala, da asa de puternic ii, faaai, ca nu imi mai aduc aminte unde dracu eram, si trebuia sa dau cu mana de copac, ASA DE BINEEE EEEE","Anonim", "Mihai", LocalDateTime.now()));
        s.addTask(new MessageTask("Intriga", "3", "Da ce treaba are ursul cu 1 Mai?","Anonim", "Burci", LocalDateTime.now()));
        s.addTask(new MessageTask("Desfasurerea actiunii", "4", "Fooooooioioioioi, aici e distractie, eu trebuie sa ma duc la distractie, sa dansez, sa mananc, sa beau, si sa am la mine in buzunar un banutas, draga, ca maine, no, maine mai e si un dolar, un euro","Burci", "Anonim", LocalDateTime.now()));
        s.addTask(new MessageTask("Deznodamant", "5", "Da zi, ai primit ceva de mancare?","Anonim", "Burci", LocalDateTime.now()));
        s.addTask(new MessageTask("Deznodamant", "6", "Am mancat niste gratara de n-am mai mancat de cand ...?","Burci", "Anonim", LocalDateTime.now()));
        s.addTask(new SortingTask("Sorteaza MergeSort", "7", new int[] {4,6,1,10,0,2,9,7,3,5,8}, SortingStrategies.MERGESORT));
        s.addTask(new SortingTask("Sorteaza BubbleSort", "8", new int[] {4,6,1,10,0,2,9,7,3,5,8}, SortingStrategies.BUBBLESORT));

        PrinterTaskRunner p = new PrinterTaskRunner(s);
        //p.executeAll();

        DelayTaskRunner d = new DelayTaskRunner(s);
        //
        d.executeAll();
    }

    public static void main(String[] args) {
        StrategyTaskRunner s;
        switch (args[0]) {
            case "FIFO" -> s = new StrategyTaskRunner(ContainerStrategy.LIFO);
            case "LIFO" -> s = new StrategyTaskRunner(ContainerStrategy.FIFO);
            default -> s = null;
        }
        run(s);
    }
}