package org.example.flightsproject.Utils.Event;

public class EntityChangeEvent<E> implements Event {
    private ChangeType changeType;
    private E data;
    private E oldData;

    public EntityChangeEvent(ChangeType changeType, E data) {
        this.data = data;
        this.changeType = changeType;
    }

    public EntityChangeEvent(ChangeType changeType, E data, E oldData) {
        this.data = data;
        this.changeType = changeType;
        this.oldData = oldData;
    }

    public ChangeType getChangeType() {
        return changeType;
    }

    public E getData() {
        return data;
    }

    public E getOldData() {
        return oldData;
    }

}
