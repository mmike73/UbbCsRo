package Entities;

import java.util.Objects;

public class Friendship extends Entity<Integer> {
    String userName1, userName2;

    public Friendship(String user1, String user2) {
        this.userName1 = user1;
        this.userName2 = user2;
    }

    public Integer getId() {
        return hashCode();
    }

    public String getUser1() {
        return userName1;
    }

    public String getUser2() {
        return userName2;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Friendship that = (Friendship) o;
        return Objects.equals(userName1, that.userName1) && Objects.equals(userName2, that.userName2);
    }

    @Override
    public int hashCode() {
        return Objects.hash(userName1, userName2);
    }

    @Override
    public String toString() {
        return "Friendship{" +
                "userName1='" + userName1 + '\'' +
                ", userName2='" + userName2 + '\'' +
                '}';
    }
}
