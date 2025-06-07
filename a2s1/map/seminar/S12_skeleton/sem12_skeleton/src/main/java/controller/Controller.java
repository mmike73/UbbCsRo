package controller;

import domain.Employee;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.ComboBox;
import javafx.scene.control.ListView;
import javafx.scene.control.TextField;
import service.Service;

import java.time.YearMonth;
import java.util.Arrays;
import java.util.stream.Collectors;

public class Controller {

    @FXML
    private ListView<String> listView;
    @FXML
    private ComboBox<Integer> monthComboBox;
    @FXML
    private TextField yearField;
    private ObservableList<String> items = FXCollections.observableArrayList();
    private Service service;

    @FXML
    public void initialize() {
        listView.setItems(items);
        monthComboBox.getItems().setAll(Arrays.asList(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12));
    }

    public void handleReport1() {
        items.setAll(service.getEmployeesOrderedByLevelAndRatePerHour().stream()
                .map(Employee::toString)
                .collect(Collectors.toList()));
    }

    public void handleReport2() {
        items.setAll(service.getAverageTaskTime().entrySet().stream()
                .map(e -> e.getKey() + " - " + e.getValue())
                .collect(Collectors.toList()));
    }

    public void handleReport3() {
        items.setAll(service.getTopBestPaidEmployees(2, 2025).stream()
                .map(p -> p.getLeft() + " - " + p.getRight())
                .collect(Collectors.toList()));
    }

    public void handleReport4() {
        Integer month = monthComboBox.getValue();
        String yearValue = yearField.getText();
        if (month == null || yearValue == null || yearValue.isEmpty()) {
            return;
        }
       items.setAll(service.getEmployeeSalaries(YearMonth.of(Integer.parseInt(yearValue), month)).stream()
               .map(p -> p.getLeft() + " - " + p.getRight())
               .collect(Collectors.toList()));
    }

    public void setService(Service service) {
        this.service = service;
    }
}
