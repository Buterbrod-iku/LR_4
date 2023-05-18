#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

enum class PositionPost {
    DIRECTOR = 'D',
    STUDENT = 'S',
    INTERN = 'I',
    WORKER = 'W',
    NULLRES = 'n',
};

class Worker
{
private:
    string firstname;
    string rang;
    double money;
    PositionPost post;
public:
    void setName(string firstnameInput) {
        firstname = firstnameInput;
    }

    void setRang(string rangInput) {
        rang = rangInput;
    }

    void setMoney(double moneyInput) {
        money = moneyInput;
    }

    void setPost(char reduction) {
        switch (reduction)
        {
        case 'D':
            post = PositionPost::DIRECTOR;
            break;
        case 'I':
            post = PositionPost::INTERN;
            break;
        case 'S':
            post = PositionPost::STUDENT;
            break;
        case 'W':
            post = PositionPost::WORKER;
            break;
        default:
            post = PositionPost::NULLRES;
            break;
        }
    }

    string getName() {
        return firstname;
    }

    string getRang() {
        return rang;
    }

    double getMoney() {
        return money;
    }

    PositionPost getPost() {
        return post;
    }

    void upMoneyOnePeople(Worker people) {
        double countMoney = people.getMoney() * 1.15;
        people.money = countMoney;
    }

    void reversRangOnePeople(Worker people) {
        if (people.getName()[0] == 'I' && people.getName()[1] == 'v' && people.getName()[2] == 'a' && people.getName()[3] == 'n') {
            people.rang = "injener";
        }
    }
};

void reversRang(vector<Worker> list) {
    for (int i = 0; i < list.size(); i++)
    {
        list[i].reversRangOnePeople(list[i]);
    }
}

vector<Worker> inputDataConsole(int Count) {
    vector<Worker> list;

    for (int i = 0; i < Count; i++)
    {
        while ((getchar()) != '\n');
        Worker people;
        cout << "Input firstname: ";
        string firstnameInput;
        getline(cin, firstnameInput);
        people.setName(firstnameInput);

        cout << "Input rang: ";
        string  rangInput;
        getline(cin, rangInput);
        people.setRang(rangInput);

        cout << "Input money: ";
        double moneyInput;
        cin >> moneyInput;
        people.setMoney(moneyInput);

        cout << "Input post (D, I, S, W): ";
        char post;
        cin >> post;
        people.setPost(post);

        list.push_back(people);
    }

    return list;
}

void diskOut(ofstream& fout, vector<Worker> list) {
    for (int i = 0; i < list.size(); i++)
    {
        fout << list[i].getName() << endl;
        fout << list[i].getRang() << endl;
        fout << list[i].getMoney() * 1.15 << endl;
        fout << static_cast<char>(list[i].getPost()) << endl;
    }
    fout.close();
}

vector<string> diskIn(ifstream& fin) {
    string N;
    vector<string> check;
    while (getline(fin, N)) {
        check.push_back(N);
    }
    fin.close();

    return check;
}

vector<Worker> inputDataFList(ifstream& fin) {
    vector<string> check = diskIn(fin);
    vector<Worker> list;

    for (int i = 0; i < check.size(); i += 4)
    {
        Worker people;

        people.setName(check[i]);
        people.setRang(check[i + 1]);
        people.setMoney(stod(check[i + 2]));

        list.push_back(people);
    }

    return list;
}

int main() {
    setlocale(LC_ALL, "");

    Worker man;
    cout << "how much people?" << endl;
    int Count;
    cin >> Count;

    vector<Worker> listConsole = inputDataConsole(Count);

    ofstream fout("C:/Users/mvideo/Desktop/LR_4/last_C++/res.txt");
    ifstream fin("C:/Users/mvideo/Desktop/LR_4/last_C++/test.txt");
    vector<Worker> listFile;

    while (true) {
        cout << "1. Вывести деньги" << endl
            << "2. Изменить ранг если имя Ivan" << endl
            << "3. Поместить данные в файл" << endl
            << "4. Считать с файла" << endl
            << "5. Поиск по направлению работы" << endl
            << "6. Завершить работу" << endl;
        char task;
        try {
            cin >> task;
            switch (task)
            {
            case '1':
                cout << "------" << endl;
                cout << "First money" << endl;

                for (int i = 0; i < Count; i++)
                {
                    cout << listConsole[i].getMoney() << endl;
                }

                cout << "------" << endl;
                cout << "Second money" << endl;

                for (int i = 0; i < Count; i++)
                {
                    cout << listConsole[i].getMoney() * 1.15 << endl;
                }
                break;
            case '2':
                cout << "------" << endl;
                cout << "Revers Rang" << endl;

                reversRang(listConsole);

                for (int i = 0; i < Count; i++)
                {
                    cout << listConsole[i].getRang() << endl;
                }
                break;
            case '3':

                try
                {
                    fout.exceptions(ios::badbit);
                    if (!fout.is_open())
                    {
                        cout << "ERROR" << endl;
                    }
                    diskOut(fout, listConsole);

                    fout.close();
                }
                catch (char* name)
                {
                    cout << "The file could not be opened: " << name << endl;
                }
                break;
            case '4':


                try
                {
                    fin.exceptions(ios::badbit);
                    listFile = inputDataFList(fin);
                }
                catch (char* name)
                {
                    cout << "The file could not be opened: " << name << endl;
                }

                cout << "------" << endl;
                cout << "Print NAME with file" << endl;
                for (int i = 0; i < listFile.size(); i++) {
                    cout << listFile[i].getName() << endl;
                }
                break;
            case '5':
                cout << "If post this (enum): ";
                char search;
                cin >> search;
                while ((getchar()) != '\n');

                for (int i = 0; i < listConsole.size(); i++) {
                    string name = listConsole[i].getName();
                    if (search == static_cast<char>(listConsole[i].getPost())) {
                        cout << name << endl;
                    }
                }
                break;
            case '6':
                exit(3);
                break;
            default:
                cout << "ERROR" << endl;
                break;
            }
        }
        catch(...){
            cout << "type error" << endl;
        }
    }
}
