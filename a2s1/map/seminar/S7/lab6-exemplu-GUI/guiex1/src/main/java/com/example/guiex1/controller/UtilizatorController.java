package com.example.guiex1.controller;

import com.example.guiex1.HelloApplication;
import com.example.guiex1.domain.Utilizator;
import com.example.guiex1.domain.ValidationException;
import com.example.guiex1.services.UtilizatorService;
import com.example.guiex1.utils.events.UtilizatorEntityChangeEvent;
import com.example.guiex1.utils.observer.Observer;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Modality;
import javafx.stage.Stage;


import java.io.IOException;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class UtilizatorController implements Observer<UtilizatorEntityChangeEvent> {
    public TextField fieldNume;
    public TextField fieldPrenume;
    public TextField fieldEmail;
    UtilizatorService service;
    ObservableList<Utilizator> model = FXCollections.observableArrayList();

    @FXML
    TableView<Utilizator> tableView;
    @FXML
    TableColumn<Utilizator,String> tableColumnFirstName;
    @FXML
    TableColumn<Utilizator,String> tableColumnLastName;
    @FXML
    TableColumn<Utilizator,String> tableColumnEmail;

    public void setUtilizatorService(UtilizatorService service) {
        this.service = service;
        initModel();
        this.service.addObserver(this);
    }

    @FXML
    public void initialize() {
        tableColumnFirstName.setCellValueFactory(new PropertyValueFactory<>("firstName"));
        tableColumnLastName.setCellValueFactory(new PropertyValueFactory<>("lastName"));
        tableColumnEmail.setCellValueFactory(new PropertyValueFactory<>("email"));
        tableView.setItems(model);

        tableView.getSelectionModel().selectedItemProperty().addListener((observable, oldValue, newValue) -> {
            if (newValue != null) {
                fieldNume.setText(newValue.getLastName());
                fieldPrenume.setText(newValue.getFirstName());
                fieldEmail.setText(newValue.getEmail());
            }
            else{
                fieldNume.setText("");
                fieldPrenume.setText("");
                fieldEmail.setText("");
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
            Utilizator updatedUser=new Utilizator(fieldPrenume.getText(),fieldNume.getText(),fieldEmail.getText());
            updatedUser.setId(user.getId());
            try{
                service.updateUtilizator(updatedUser);
                //initModel();
            }catch(ValidationException e){
                MessageAlert.showErrorMessage(null, e.getMessage());
            }
        }
    }

    public void showUserEditDialog(Utilizator user) {
        try {
            // create a new stage for the popup dialog.
            FXMLLoader loader = new FXMLLoader(HelloApplication.class.getResource("views/edit-user-view.fxml"));
//            loader.setLocation(getClass().getResource("../views/edit-user-view.fxml"));

            AnchorPane root = (AnchorPane) loader.load();

            // Create the dialog Stage.
            Stage dialogStage = new Stage();
            dialogStage.setTitle("Edit Message");
            dialogStage.initModality(Modality.WINDOW_MODAL);
            //dialogStage.initOwner(primaryStage);
            Scene scene = new Scene(root);
            dialogStage.setScene(scene);

            EditUserController editUserController = loader.getController();
            editUserController.setService(service, dialogStage, user);

            dialogStage.show();

        } catch ( IOException e) {
            e.printStackTrace();
        }
    }

    public void handleAddUtilizator(ActionEvent actionEvent) {
        showUserEditDialog(null);

    }

    public void handleUpdateInNewWindow(ActionEvent actionEvent) {
        Utilizator selected = tableView.getSelectionModel().getSelectedItem();
        if (selected != null) {
            showUserEditDialog(selected);
        } else
            MessageAlert.showErrorMessage(null, "NU ati selectat nici un user!");

    }
}
