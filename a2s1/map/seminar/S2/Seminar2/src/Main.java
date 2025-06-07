import java.util.*;

//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {
    public static List<Student> getList(){
        List<Student> l=new ArrayList<Student>();
        l.add(new Student("1",9.7f));
        l.add(new Student("2",7.3f));
        l.add(new Student("3",6f));
        l.add(new Student("4",6.9f));
        l.add(new Student("5",9.5f));
        l.add(new Student("6",9.9f));
        return l;
    }

    public static void main(String[] args) {

        Student s1 = new Student("Dan", 4.5f);
        Student s2 = new Student("Ana", 8.5f);
        Student s3 = new Student("Dan", 4.5f);

        HashSet<Student> students = new HashSet<>();
        students.add(s1);
        students.add(s2);
        students.add(s3);


        for(Student student : students) {
            System.out.println(student);
        }

        Set<Student> students_treeset = new TreeSet<>(new Comparator<Student>() {
            @Override
            public int compare(Student o1, Student o2) {
                return o1.getNume().compareTo(o2.getNume());
            }
        });
        students_treeset.add(s1);
        students_treeset.add(s2);
        students_treeset.add(s3);

        for(Student student : students_treeset) {
            System.out.println(student);
        }

        Set<Student> sortedStudents = new TreeSet<>(new Comparator<Student>() {
            @Override
            public int compare(Student o1, Student o2) {
                return o2.getNume().compareTo(o1.getNume());
            }
        });

        sortedStudents.add(s1);
        sortedStudents.add(s2);
        sortedStudents.add(s3);

        for(Student student : sortedStudents) {
            System.out.println(student);
        }


        Map<String, Student> student_map = new TreeMap<>(); //HashMap
        student_map.put(s1.getNume(), s1);
        student_map.put(s2.getNume(), s2);
        student_map.put(s3.getNume(), s3);

        for(Student student : student_map.values()) {
            System.out.println(student);
        }

        for(String student : student_map.keySet()) {
            System.out.println(student_map.get(student));
        }

        for(Map.Entry<String, Student> student : student_map.entrySet()) {
            System.out.println(student);
        }

        MyMap studentMap = new MyMap();
        List<Student> students_10 = getList();
        for(Student student : students_10) {
            studentMap.addStudent(student);
        }

        for(Map.Entry<Integer, List<Student>> student_list : studentMap.getEntries()) {
            System.out.println(student_list);
            List<Student> sorted_list = student_list.getValue();
            Collections.sort(sorted_list);
            for(Student student : sorted_list) {
                System.out.println(student);
            }
        }



    }

}