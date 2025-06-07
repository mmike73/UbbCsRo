package com.example.guiex1.controller;

import com.example.guiex1.domain.Utilizator;
import com.example.guiex1.domain.ValidationException;
import com.example.guiex1.services.UtilizatorService;
import com.example.guiex1.utils.events.UtilizatorEntityChangeEvent;
import com.example.guiex1.utils.observer.Observer;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;




import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class UtilizatorController implements Observer<UtilizatorEntityChangeEvent> {
    public TextField fieldNume;
    public TextField fieldPrenume;
    UtilizatorService service;
    ObservableList<Utilizator> model = FXCollections.observableArrayList();

    @FXML
    TableView<Utilizator> tableView;
    @FXML
    TableColumn<Utilizator,String> tableColumnFirstName;
    @FXML
    TableColumn<Utilizator,String> tableColumnLastName;

    public void setUtilizatorService(UtilizatorService service) {
        this.service = service;
        initModel();
        this.service.addObserver(this);
    }

    @FXML
    public void initialize() {
        tableColumnFirstName.setCellValueFactory(new PropertyValueFactory<>("firstName"));
        tableColumnLastName.setCellValueFactory(new PropertyValueFactory<>("lastName"));
        tableView.setItems(model);

        tableView.getSelectionModel().selectedItemProperty().addListener((observable, oldValue, newValue) -> {
            if (newValue != null) {
                fieldNume.setText(newValue.getLastName());
                fieldPrenume.setText(newValue.getFirstName());
            }
            else{
                fieldNume.setText("");
                fieldPrenume.setText("");
            }
        });
    }

    private void initModel() {
        List<Utilizator> all_users=StreamSupport.stream(service.getAll().spliterator(), false).collect(Collectors.toList());
        model.setAll(all_users);
    }

    @Override
    public void update(UtilizatorEntityChangeEvent utilizatorEntityChangeEvent) {
        initModel();
    }

    public void handleDeleteUtilizator(ActionEvent actionEvent) {
        Utilizator user=(Utilizator) tableView.getSelectionModel().getSelectedItem();
        if (user!=null) {
            Utilizator deleted= service.deleteUtilizator(user.getId());
            //initModel();
        }
    }

    public void handleUpdateUtilizator(ActionEvent actionEvent) {
        Utilizator user=tableView.getSelectionModel().getSelectedItem();
        if(user!=null){
            Utilizator updatedUser=new Utilizator(fieldPrenume.getText(),fieldNume.getText());
            updatedUser.setId(user.getId());
            try{
                service.updateUtilizator(updatedUser);
                //initModel();
            }catch(ValidationException e){
                MessageAlert.showErrorMessage(null, e.getMessage());
            }
        }
    }

    public void handleAddUtilizator(ActionEvent actionEvent) {
    }
}
