#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum class PositionPost {
    DIRECTOR,
    STUDENT,
    INTERN,
    WORKER,
};

class Worker
{
public:
    string firstname;
    string rang;
    double money;
    PositionPost post;

    virtual void setName(string firstnameInput) {
        firstname = firstnameInput;
    }

    virtual void setRang(string rangInput) {
        rang = rangInput;
    }

    virtual void setMoney(double moneyInput) {
        money = moneyInput;
    }

    virtual void setPost(char reduction) {
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
            post = PositionPost::INTERN;
            break;
        }
    }

    virtual string getName() {
        return firstname;
    }

    virtual string getRang() {
        return rang;
    }

    virtual double getMoney() {
        return money;
    }

    virtual PositionPost getPost() {
        return post;
    }

    virtual void upMoneyOnePeople(Worker people) {
        people.money = people.money * 1.15;
    }

    virtual void reversRangOnePeople(Worker people) {
        if (people.getName()[0] == 'I' && people.getName()[1] == 'v' && people.getName()[2] == 'a' && people.getName()[3] == 'n') {
            people.rang = "injener";
        }
    }

    vector<string> diskIn(ifstream &fin) {
        string N;
        vector<string> check;
        while (getline(fin, N)) {
            check.push_back(N);
        }

        return check;
    }

    void diskOut(ofstream& fout, Worker people) {
        fout << people.getName() << endl;
        fout << people.getRang() << endl;
        fout << people.getMoney() << endl;
        fout.close();
    }
};


void upMoney(vector<Worker> list) {
    for (int i = 0; i < list.size(); i++)
    {
        Worker.upMoneyOnePeople(list[i]);
    }
}

void reversRang(vector<Worker> list) {
    for (int i = 0; i < list.size(); i++)
    {
        Worker.reversRangOnePeople(list[i]);
    }
}

vector<Worker> inputDataConsole(int Count) {
    vector<Worker> list;

    for (int i = 0; i < Count; i++)
    {
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

vector<Worker> inputDataFList(vector<string> check) {
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
        cout << "how much people?" << endl;
        int Count;
        cin >> Count;

        vector<Worker> listConsole = inputDataConsole(Count);

        cout << "------" << endl;

        for (int i = 0; i < Count; i++)
        {
            cout << listConsole[i].getMoney() << endl;
        }

        cout << "------" << endl;

        upMoney(listConsole);

        for (int i = 0; i < Count; i++)
        {
            cout << listConsole[i].getMoney() << endl;
        }

        cout << "------" << endl;

        reversRang(listConsole);

        for (int i = 0; i < Count; i++)
        {
            cout << listConsole[i].getRang() << endl;
        }

        // part 2
        vector<Worker> listFile;
        ifstream fin("test.txt");
        try
        {
            vector<string> check = Worker.diskIn(fin);
            listFile = inputDataFList(check);

            fin.Close();
        }
        catch (char* name)
        {
            cout << "The file could not be opened: " << name << endl;
        }

        cout << "------" << endl;

        for (int i = 0; i < listFile.size(); i++) {
            cout << listFile[i].getName() << endl;
        }

        try
        {
            using (ofstream fout = new StreamWriter("res.txt")) {
                for (int i = 0; i < listFile.size(); i++) {
                    Worker.diskOut(fout, listFile[i]);
                }

                fout.Close();
            }

        }
        catch (char* name)
        {
            cout << "The file could not be opened: " << name << endl;
        }

        //Part 3 enum
        char search;
        cin >> search;

        for (int i = 0; i < listConsole.size(); i++) {
            if (search == listConsole[i].getPost()) {
                cout << listConsole[i].getName() << endl;
            }
            
        }

        cout << "------" << endl;

        for (int i = 0; i < listConsole.size(); i++) {
            int now = listConsole[i].getNow();
            cout << now << endl;
        }
    }
}
