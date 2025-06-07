package Lab2.TaskRunners;

import java.io.PrintStream;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class PrinterTaskRunner extends AbstractTaskRunner {
    private static final DateTimeFormatter formatter = DateTimeFormatter.ofPattern("HH:mm");

    public PrinterTaskRunner(TaskRunner taskRunner) {
        super(taskRunner);
    }

    @Override
    public void executeOneTask() {
        super.executeOneTask();
        PrintStream var10000 = System.out;
        LocalDateTime var10001 = LocalDateTime.now();
        var10000.println("Executed at " + var10001.format(formatter));
    }
}
