package org.example.domain;

import java.time.LocalDateTime;

public class Excursie extends Entity<Integer> {
    public int nrLocuri, pret;
    public LocalDateTime dataOraPlcare;
    public String obiectiv, firmaTransport;
}
