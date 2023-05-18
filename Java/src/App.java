import java.util.*;
import java.io.*;
import java.text.ParseException;
import java.text.SimpleDateFormat;

class Worker
{
public enum PositionPost{
    DIRECTOR,
    STUDENT,
    INTERN,
    WORKER,
    NULLRES,
}
private
    String firstname;
    String rang;
    double money;
    PositionPost post; 
    Calendar now;

public
    void setName(String firstnameInput) {
        firstname = firstnameInput;
    }

    void setRang(String rangInput) {
        rang = rangInput;
    }

    void setMoney(double moneyInput) {
        money = moneyInput;
    }

    void setPost(String reduction){
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

    void setNow(Calendar calendar) {
        now = calendar;
    }

    String getName() {
        return firstname;
    }

    String getRang() {
        return rang;
    }

    double getMoney() {
        return money;
    }

    PositionPost getPost() {
        return post;
    }

    Calendar getNow(){
        return now;
    }

    public static void upMoneyOnePeople(Worker people) {
        people.money = people.money * 1.15;
    }

    public static void reversRangOnePeople(Worker people) {
        if (people.getName().charAt(0) == 'I' && people.getName().charAt(1) == 'v' && people.getName().charAt(2) == 'a' && people.getName().charAt(3) == 'n') {
            people.rang = "injener";
        }
    }

    public static ArrayList<String> diskIn(FileReader fin) throws FileNotFoundException {
        Scanner Reader = new Scanner(fin);
        ArrayList<String> check = new ArrayList<String>();
        while (Reader.hasNextLine()) {
            String data = Reader.nextLine();
            check.add(data);
        }

        return check;
    }

    public static void diskOut(FileWriter fout, Worker people) throws IOException {
        fout.write(people.getName() + "\n");
        fout.write(people.getRang() + "\n");
        fout.write(String.valueOf(people.getMoney()) + "\n");
        fout.write(people.getPost() + "\n");
        fout.write(people.getNow().getTime() + "\n");
        fout.append("\n");
    }
};

public class App {
    public static void upMoney(ArrayList<Worker> list) {
        for (int i = 0; i < list.size(); i++)
        {
            Worker.upMoneyOnePeople(list.get(i));
        }
    }

    public static void reversRang(ArrayList<Worker> list) {
        for (int i = 0; i < list.size(); i++)
        {
            Worker.reversRangOnePeople(list.get(i));
        }
    }

    public static ArrayList<Worker> inputDataConsole(int count) {
        Scanner input = new Scanner(System.in);
        Scanner inputString = new Scanner(System.in);

        ArrayList<Worker> list = new ArrayList<Worker>();

        for (int i = 0; i < count; i++)
        {
            Worker people = new Worker();
            System.out.print("Input firstname: ");
            String firstnameInput = inputString.nextLine();
            people.setName(firstnameInput);

            System.out.print("Input rang: ");
            String  rangInput = inputString.nextLine();
            people.setRang(rangInput);

            System.out.print("Input money: ");
            double moneyInput = input.nextDouble();
            people.setMoney(moneyInput);

            System.out.print("Input post (D, I, S, W): ");
            String  post = inputString.nextLine();
            people.setPost(post);

            System.out.print("Input data (day): ");
            int day = input.nextInt();
            System.out.print("Input data (mounth): ");
            int mounth = input.nextInt();
            System.out.print("Input data (year): ");
            int year = input.nextInt();
            Calendar calendar = new GregorianCalendar(year, mounth+1 , day);
            people.setNow(calendar);

            list.add(people);
        }

        return list;
    }

    public static ArrayList<Worker> inputDataFList(ArrayList<String> check) throws ParseException {
        ArrayList<Worker> list = new ArrayList<Worker>();

        for (int i = 0; i < check.size(); i += 6)
        {
            Worker people = new Worker();
            
            people.setName(check.get(i));
            people.setRang(check.get(i+1));
            people.setMoney(Integer.parseInt(check.get(i+2)));
            people.setPost(check.get(i+3));
            Calendar mydate = new GregorianCalendar();
            Date thedate = new SimpleDateFormat("yyyy.MM.dd", Locale.ENGLISH).parse(check.get(i+4));
            mydate.setTime(thedate);
            people.setNow(mydate);

            list.add(people);
        }

        return list;
    }
    public static void main(String[] args) throws Exception {
        Scanner input = new Scanner(System.in);
        System.out.println("how much people?");
        int count = input.nextInt();
        ArrayList<Worker> listConsole = inputDataConsole(count);

        ArrayList<Worker> listFile = null;

        while(true){
            System.out.println( "1. Вывести деньги\n" +
            "2. Изменить ранг если имя Ivan\n" +
            "3. Поместить данные в файл\n" +
            "4. Считать с файла\n" +
            "5. Поиск по направлению работы\n" +
            "6. Работа с датами\n" +
            "7. Завершить работу");
            Scanner taskInput = new Scanner(System.in);
            String task = taskInput.nextLine();
            switch(task){
                case("1"):
                    System.out.println("------");
                    System.out.println("First money");
            
                    for (int i = 0; i < count; i++)
                    {
                        System.out.println(listConsole.get(i).getMoney());
                    }
            
                    System.out.println("------");
                    System.out.println("Second money");
            
                    upMoney(listConsole);
            
                    for (int i = 0; i < count; i++)
                    {
                        System.out.println(listConsole.get(i).getMoney());
                    }
                    break;
                case("2"):
                    System.out.println("------");
                    System.out.println("Revers rang");
            
                    reversRang(listConsole);
            
                    for (int i = 0; i < count; i++)
                    {
                        System.out.println(listConsole.get(i).getRang());
                    }
                    break;
                case("3"):
                    try(FileWriter fout = new FileWriter("res.txt", false))
                    {
                        for(int i = 0; i < listConsole.size(); i++){
                            Worker.diskOut(fout, listConsole.get(i));
                        }
                        
                        fout.flush();
                        fout.close();
                    }
                    catch(IOException ex){
                        
                        System.out.println(ex.getMessage());
                    }
                    break;
                case("4"):
                    try(FileReader fin = new FileReader("test.txt"))
                    {
                        ArrayList<String> check = Worker.diskIn(fin);
                        listFile = inputDataFList(check);
                        
                        fin.close();
                    }
                    catch(IOException ex){
                        
                        System.out.println(ex.getMessage());
                    } 
                    System.out.println("------");
                    System.out.println("Print name with file");

                    for(int i = 0; i < listFile.size(); i++){
                        System.out.println(listFile.get(i).getName());
                    }
                    break;
                case("5"):
                    System.out.println("Check Post (print full name): ");
                    Scanner searchScanner = new Scanner(System.in);
                    String search = searchScanner.nextLine();
            
                    for(int i = 0; i < listConsole.size(); i++){
                        if(listConsole.get(i).getPost().name().equalsIgnoreCase(search)){
                            System.out.println(listConsole.get(i).getName());
                        }
                    }
                    break;
                case("6"):
                    System.out.println("------");
                    System.out.println("Sort data");
            
                    Collections.sort(listConsole, Comparator.comparing(Worker::getNow));
            
                    for(int i = 0; i < listConsole.size(); i++){
                        System.out.println(listConsole.get(i).getNow().getTime());
                    }
                    break;
                case("7"):
                    System.exit(0);
                    break;
                default:
                    System.out.println("ERROR");
                    break;
            }
        }
    }
}