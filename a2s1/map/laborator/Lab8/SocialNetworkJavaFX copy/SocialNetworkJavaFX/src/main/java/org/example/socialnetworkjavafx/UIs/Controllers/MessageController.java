package org.example.socialnetworkjavafx.UIs.Controllers;

import javafx.application.Platform;
import javafx.beans.property.SimpleListProperty;
import javafx.beans.property.SimpleObjectProperty;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.ListView;
import javafx.scene.control.TextField;
import org.example.socialnetworkjavafx.Entities.Message;

import java.util.List;

public class MessageController {

    private String loggedUser;
    private String otherUser;
    private CliController controller;

    @FXML
    private ListView<String> messageListView;

    @FXML
    private TextField messageInputField;

    private final SimpleListProperty<String> messages = new SimpleListProperty<>(FXCollections.observableArrayList());
    private final SimpleListProperty<Integer> messageIds = new SimpleListProperty<>(FXCollections.observableArrayList());

    private final SimpleObjectProperty<Integer> selectedMessageId = new SimpleObjectProperty<>(null);

    public void setUsers(String loggedUser, String otherUser, CliController cliController) {
        this.loggedUser = loggedUser;
        this.otherUser = otherUser;
        this.controller = cliController;

        messageListView.itemsProperty().bind(messages);

        messageListView.getSelectionModel().selectedIndexProperty().addListener((obs, oldIndex, newIndex) -> {
            if (newIndex.intValue() >= 0 && newIndex.intValue() < messageIds.size()) {
                selectedMessageId.set(messageIds.get(newIndex.intValue()));
            } else {
                selectedMessageId.set(null);
            }
        });

        loadMessages();
    }

    private void loadMessages() {
        Platform.runLater(() -> {
            try {
                List<Message> messageList = controller.getAllMessagesOf(loggedUser, otherUser);

                messages.clear();
                messageIds.clear();

                for (Message message : messageList) {
                    String formattedMessage = formatMessage(message);
                    messages.add(formattedMessage);
                    messageIds.add(message.getId());
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
        });
    }

    private String formatMessage(Message message) {
        if (message.getRepplyFor() != 0) {
            return "reply to: " + message.getRepplyFor() + " - " + message.getFrom() + ": " + message.getContent();
        } else {
            return message.getFrom() + ": " + message.getContent();
        }
    }

    @FXML
    private void onSendMessage() {
        String messageContent = messageInputField.getText().trim();
        if (!messageContent.isEmpty()) {
            Platform.runLater(() -> {
                try {
                    Integer replyToId = selectedMessageId.get();

                    if (replyToId != null) {
                        controller.replyToMessage(replyToId, loggedUser, otherUser, messageContent);
                        messages.add("reply to: " + replyToId + " - " + loggedUser + ": " + messageContent);
                    } else {
                        controller.sendMessage(loggedUser, otherUser, messageContent);
                        messages.add(loggedUser + ": " + messageContent);
                    }

                    messageInputField.clear();
                    messageListView.getSelectionModel().clearSelection();
                } catch (Exception e) {
                    e.printStackTrace();
                }
            });
        }
    }

    public void refreshMessages() {
        loadMessages();
    }
}
