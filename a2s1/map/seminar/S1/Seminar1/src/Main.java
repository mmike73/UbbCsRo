import java.time.LocalDateTime;

//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {
    public static void main(String[] args) {
        StratrgyTaskRunner s = new StratrgyTaskRunner(Strategy.FIFO);

        s.addTask(new MessageTask("Introducere", "1", "Ce inseamna pentru dumneavoastra 1 Mai?","Mihai", "Alex", LocalDateTime.now()));
        s.addTask(new MessageTask("Introducere", "1", "Așa de bine e... faaaai de mine","Alex", "Mihai", LocalDateTime.now()));
        s.addTask(new MessageTask("Intriga", "1", "Incat a trebuit sa ma bat cu un urs","Alex", "Mihai", LocalDateTime.now()));
        s.addTask(new MessageTask("Intriga", "1", "Da ce treaba are ursul cu 1 Mai?","Mihai", "Alex", LocalDateTime.now()));
        s.addTask(new MessageTask("Desfasurerea actiunii", "1", "Am vennit sa mananc, sa beau si sa am si eu un banut in buzunar","Alex", "Mihai", LocalDateTime.now()));
        s.addTask(new MessageTask("Deznodamant", "1", "Asa de bine e... ahahahaaaaaa :DDDDDDDD","Alex", "Mihai", LocalDateTime.now()));

        PrinterTaskRunner p = new PrinterTaskRunner(s);
        //p.executeAll();

        DelayTaskRunner d = new DelayTaskRunner(s);
        d.executeAll();
    }
}