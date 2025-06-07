import java.util.Objects;

public class Student implements Comparable<Student> {
    private String nume;
    private float media;

    public Student(String nume, float media) {
        this.nume = nume;
        this.media = media;
    }

    public float getMedia() {
        return media;
    }

    public void setMedia(float media) {
        this.media = media;
    }

    public String getNume() {
        return nume;
    }

    public void setNume(String nume) {
        this.nume = nume;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Student student = (Student) o;
        return Float.compare(media, student.media) == 0 && Objects.equals(nume, student.nume);
    }

    @Override
    public int hashCode() {
        return Objects.hash(nume, media);
    }

    @Override
    public int compareTo(Student oth) {
        return nume.compareTo(oth.nume);
    }

    @Override
    public String toString() {
        return "Student{" +
                "nume='" + nume + '\'' +
                ", media=" + media +
                '}';
    }
}
