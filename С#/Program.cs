using System;
using System.IO;


class Worker
{
public enum PositionPost{
    DIRECTOR = 'D',
    STUDENT = 'S',
    INTERN = 'I',
    WORKER = 'W',
    NULLRES = 'n',
}
private
    string firstname;
    string rang;
    double money;
    PositionPost post; 
    DateTime now;

    public void setName(string firstnameInput) {
        firstname = firstnameInput;
    }

    public void setRang(string rangInput) {
        rang = rangInput;
    }

    public void setMoney(double moneyInput) {
        money = moneyInput;
    }

    public void setPost(string reduction){
        switch(reduction){
            case("D"):
                post = PositionPost.DIRECTOR;
                break;
            case("I"):
                post = PositionPost.INTERN;
                break;
            case("S"):
                post = PositionPost.STUDENT;
                break;
            case("W"):
                post = PositionPost.WORKER;
                break;
            default:
                post = PositionPost.NULLRES;
                break;
        }
    }

    public void setNow(DateTime time) {
        now = time;
    }

    public string getName() {
        return firstname;
    }

    public string getRang() {
        return rang;
    }

    public double getMoney() {
        return money;
    }

    public PositionPost getPost() {
        return post;
    }

    public DateTime getNow(){
        return now;
    }

    public static void upMoneyOnePeople(Worker people) {
        people.money = people.money * 1.15;
    }

    public static void reversRangOnePeople(Worker people) {
        if (people.getName()[0] == 'I' && people.getName()[1] == 'v' && people.getName()[2] == 'a' && people.getName()[3] == 'n') {
            people.rang = "injener";
        }
    }

    public static List<string> diskIn(StreamReader fin) {
        string N;
        List<string> check = new List<string>();
        while ((N = fin.ReadLine()) != null) {
            check.Add(N);
        }

        return check;
    }

    public static void diskOut(StreamWriter fout, Worker people) {
        fout.WriteLine(people.getName());
        fout.WriteLine(people.getRang());
        fout.WriteLine(people.getMoney() + "\n");
    }
};

class HelloWorld {
    public static void upMoney(List<Worker> list) {
        for (int i = 0; i < list.Count; i++)
        {
            Worker.upMoneyOnePeople(list[i]);
        }
    }

    public static void reversRang(List<Worker> list) {
        for (int i = 0; i < list.Count; i++)
        {
            Worker.reversRangOnePeople(list[i]);
        }
    }

    public static List<Worker> inputDataConsole(int Count) {
        List<Worker> list = new List<Worker>();

        for (int i = 0; i < Count; i++)
        {
            Worker people = new Worker();
            Console.Write("Input firstname: ");
            string firstnameInput = Console.ReadLine();
            people.setName(firstnameInput);

            Console.Write("Input rang: ");
            string  rangInput = Console.ReadLine();
            people.setRang(rangInput);

            Console.Write("Input money: ");
            double moneyInput = Convert.ToInt32(Console.ReadLine());
            people.setMoney(moneyInput);

            Console.Write("Input post (D, I, S, W): ");
            string  post = Console.ReadLine();
            people.setPost(post);

            Console.Write("Input data (day): ");
            int day = Convert.ToInt32(Console.ReadLine());
            Console.Write("Input post (mounth): ");
            int mounth = Convert.ToInt32(Console.ReadLine());
            Console.Write("Input post (year): ");
            int year = Convert.ToInt32(Console.ReadLine());
            DateTime DateTime = new DateTime(year, mounth, day);
            people.setNow(DateTime);

            list.Add(people);
        }

        return list;
    }

    public static List<Worker> inputDataFList(List<string> check) {
        List<Worker> list = new List<Worker>();

        for (int i = 0; i < check.Count; i += 6)
        {
            Worker people = new Worker();
            
            people.setName(check[i]);
            people.setRang(check[i+1]);
            people.setMoney(Convert.ToDouble(check[i+2]));
            people.setPost(check[i+3]);
            DateTime myDate = DateTime.ParseExact(check[i+4], "yyyy-MM-dd",
                                       System.Globalization.CultureInfo.InvariantCulture);
            people.setNow(myDate);

            list.Add(people);
        }

        return list;
    }
    static void Main() {
        Console.WriteLine("how much people?");
        int Count = Convert.ToInt32(Console.ReadLine());
        List<Worker> listConsole = inputDataConsole(Count);
        List<Worker> listFile = null;

        while(true){
            Console.WriteLine("1. Output money\n" +
            "2. Revers rang if name Ivan\n" +
            "3. In file\n" +
            "4. Read file\n" +
            "5. Search post\n" +
            "6. Print data\n" +
            "7. Close");
            string task = Console.ReadLine();
            switch(task){
                case("1"):
                    Console.WriteLine("------");
                    Console.WriteLine("First money");

                    for (int i = 0; i < Count; i++)
                    {
                        Console.WriteLine(listConsole[i].getMoney());
                    }

                    Console.WriteLine("------");
                    Console.WriteLine("Second money");

                    upMoney(listConsole);

                    for (int i = 0; i < Count; i++)
                    {
                        Console.WriteLine(listConsole[i].getMoney());
                    }
                    break;
                case("2"):
                    Console.WriteLine("------");
                    Console.WriteLine("Revers rang if need");

                    reversRang(listConsole);

                    for (int i = 0; i < Count; i++)
                    {
                        Console.WriteLine(listConsole[i].getRang());
                    }
                    break;
                case("3"):
                    try
                    {
                        using (StreamWriter fout = new StreamWriter("res.txt")){
                            for(int i = 0; i < listConsole.Count; i++){
                                Worker.diskOut(fout, listConsole[i]);
                            }
                            
                            fout.Close();
                        }
                        
                    }
                    catch(IOException e)
                    {
                        Console.WriteLine($"The file could not be opened: '{e}'");
                    }
                    break;
                case("4"):
                    try
                    {
                        using (StreamReader fin = new StreamReader("test.txt"))
                        {
                            List<string> check = Worker.diskIn(fin);
                            listFile = inputDataFList(check);
                            
                            fin.Close();
                        }
                    }
                    catch(IOException e)
                    {
                        Console.WriteLine($"The file could not be opened: '{e}'");
                    }

                    Console.WriteLine("------");

                    for(int i = 0; i < listFile.Count; i++){
                        Console.WriteLine(listFile[i].getName());
                    }
                    break;
                case("5"):
                    Console.WriteLine("Check post");
                    char search = Console.ReadLine()[0];

                    for(int i = 0; i < listConsole.Count; i++){
                        if(search.Equals((char)listConsole[i].getPost())){
                            Console.WriteLine(listConsole[i].getName());
                        }
                    }
                    break;
                case("6"):
                    Console.WriteLine("------");
                    Console.WriteLine("Sort data");

                    var sorted = listConsole.OrderBy(ob => ob.getNow()).ToList();

                    for(int i = 0; i < sorted.Count; i++){
                        Console.WriteLine(sorted[i].getNow());
                    }
                    break;
                case("7"):
                    Environment.Exit(0);
                    break;
                default:
                    Console.WriteLine("ERROR");
                    break;
            }
        }
        

        

        // part 2
        

         

        //Part 3 enum
        

        
    }
}
