module org.example.socialnetworkjavafx {
    requires javafx.controls;
    requires javafx.fxml;
    requires java.sql;


    opens org.example.socialnetworkjavafx to javafx.fxml;
    exports org.example.socialnetworkjavafx;
}