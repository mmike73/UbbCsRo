import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.Set;

public class MyMapComposition {

    private Map<Integer, List<Student>> map;

    public MyMapComposition(Map<Integer, List<Student>> map) {

    }

    public int compare(Student o1, Student o2) {
        return o1.getNume().compareTo(o2.getNume());
    }

    public void addStudent(Student student) {
        int grade = Math.round(student.getMedia());
        List<Student> list = map.get(grade);
        if (list == null) {
            list = new ArrayList<>();
            map.put(grade, list);
        }
        list.add(student);
    }

    public Set<Map.Entry<Integer, List<Student>>> getEntries() {
        return map.entrySet();
    }


}
