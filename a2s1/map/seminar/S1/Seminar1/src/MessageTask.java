import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class MessageTask extends Task {
    private String message, from, to;
    private LocalDateTime date;

    private static final DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyy-MM-dd HH:mm");

    public String getMessage() {
        return message;
    }

    public void setMessage(String message) {
        this.message = message;
    }

    public String getTo() {
        return to;
    }

    public void setTo(String to) {
        this.to = to;
    }

    public String getFrom() {
        return from;
    }

    public void setFrom(String from) {
        this.from = from;
    }

    public LocalDateTime getDate() {
        return date;
    }

    public void setDate(LocalDateTime date) {
        this.date = date;
    }

    public MessageTask(String description, String id, String message, String from, String to, LocalDateTime date) {
        super(description, id);
        this.message = message;
        this.from = from;
        this.to = to;
        this.date = date;
    }

    @Override
    public void execute() {
        System.out.println(date.format(formatter) + ": " + message);
    }

    @Override
    public String toString() {
        return "id=" + this.getTaskID() + " | description=" + this.getDescriere() + " | message= " + this.getMessage() + " | date and time=" + this.getDate() + " | from=" + this.getFrom() + " | to=" + this.getTo() +  " | from=" + this.getFrom() + " | to=" + this.getTo();
    }
}
