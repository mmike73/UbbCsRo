package org.example.flightsproject.Utils.Observer;


import org.example.flightsproject.Utils.Event.Event;

public interface Observer <E extends Event> {
    void update(E event);
}