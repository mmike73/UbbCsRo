namespace ConsoleApp1.Repository;

public delegate E StringToEntity<E>(string input);
public delegate string EntityToString<E>(E entity);

public class FileRepository<E,ID>: InMemoryRepository<E,ID> where E : Entity<ID>
{
    private string FilePath;
    private StringToEntity<E> StringToEntity;
    private EntityToString<E> EntityToString;

    public FileRepository(string filePath, StringToEntity<E> stringToEntity, EntityToString<E> entityToString)
    {
        FilePath = filePath;
        StringToEntity = stringToEntity;
        EntityToString = entityToString;
        ReadFromFile();
    }
    
    public void ReadFromFile(){
        List<E> enitities = ReadFromFile(FilePath, StringToEntity);
        foreach (var enitity in enitities){
            base.Save(enitity);
        }
    }

    public List<T> ReadFromFile<T>(string filePath, StringToEntity<T> stringToEntity)
    {
        List<T> entities = new List<T>();
        using (StreamReader sr = new StreamReader(filePath)){
            string line;
            while ((line = sr.ReadLine()) != null){
                entities.Add(stringToEntity(line));
                ///base.Save(stringToEntity(line));
            }
        }
        return entities;
    }

    public void WriteToFile()
    {
        using (StreamWriter sw = new StreamWriter(FilePath))
            foreach (E entity in base.FindAll())
                sw.WriteLine(EntityToString(entity));
    }

    public override E? Save(E entity)
    {
        E? e= base.Save(entity);
        if(e != null)
            WriteToFile();
        return e;
    }

    public override E? Update(E entity)
    {
        E? e = base.Update(entity);
        if(e != null)
                WriteToFile();
        return e;
    }

    public override E? Delete(ID id)
    {
        E? e = base.Delete(id);
        if(e!=null)
            WriteToFile();
        return e;
    }
}