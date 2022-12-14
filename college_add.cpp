#include <iostream>
#include <fstream>
#include <cstring>
#include <conio.h>
#include <iomanip>
#include <ctime>
#include <vector>
using namespace std;

void design()
{
    cout << "\n\t  \xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd";
    cout << "\n\t      |-- COLLEGE ADDMISSION --|";
    cout << "\n\t  \xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\n\n";
}

void print_details(int rank, vector<string> &row, bool flag)
{
    system("cls");
    design();
    if (!flag)
    {
        cout << "\t    Seat already booked\n";
    }
    else
    {
        cout << "\t\t---------------------\n";
        cout << "\t\t|    Seat booked    |\n";
        cout << "\t\t---------------------\n";
        cout << "\t\t   Booking details\n";
        cout << "\t  ___________________________________\n";
        cout << "\t\t  Name: " << row[3] << endl;
        cout << "\t\t  Admit No.: " << row[4] << endl;
        cout << "\t\t  Rank: " << rank << endl;
        cout << "\t\t  College Name: " << row[1] << endl;
        cout << "\t\t  Department: " << row[2] << endl;
        cout << "\t\t  Booking time: " << row[6] << endl;
    }
    getch();
}

void create_student_details(int rank, string college_name, string dept, string choosen_college)
{
    fstream file;
    file.open("student_details.csv", ios::app);
    string studen_name, roll_no;
    cout << "\t  Enter your Full Name\n";
    getline(cin >> ws, studen_name);
    cout << "\t  Enter your Admit No.\n";
    cin >> roll_no;

    time_t now = time(0);
    char *date_time = ctime(&now);
    file << rank << ',' << college_name << ',' << dept << ',' << studen_name << ',' << roll_no << ',' << choosen_college << ',' << date_time << "";
    file.close();
}

bool search_rank(int rank, bool flag)
{
    ifstream fin;
    fin.open("student_details.csv", ios::in);
    string line, word;
    vector<string> row;
    while (fin)
    {
        row.clear();
        getline(fin, line);
        stringstream s(line);
        while (getline(s, word, ','))
            row.push_back(word);
        if (!s && word.empty())
        {
            row.push_back("");
            break;
        }
        if (stoi(row[0]) == rank)
        {
            print_details(rank, row, flag);
            return true;
        }
    }
    fin.close();
    return false;
}

void check_status()
{
    design();
    int rank;
    cout << "\t\t  Enter your rank\n";
    cin >> rank;
    if (!search_rank(rank, true))
    {
        cout << "\t\t  Not done yet\n";
        cout << "\t\t  Book your seat first\n";
        getch();
    }
}

string update(string choosen_college, int choosen_dept, int x)
{
    design();
    fstream fin, fout;
    fin.open("college_dept_details.csv", ios::in);
    fout.open("college_dept_details_new.csv", ios::out);
    string line, word, dept;
    vector<string> row;

    while (fin)
    {
        row.clear();
        getline(fin, line);
        stringstream s(line);

        while (getline(s, word, ','))
        {
            row.push_back(word);
        }
        if (!s && word.empty())
        {
            row.push_back("");
            break;
        }
        int row_size = row.size();
        if (row[0] == choosen_college && stoi(row[1]) == (choosen_dept + x))
        {
            dept = row[2];
            int convert = stoi(row[3]) - 1;
            row[3] = to_string(convert);
            if (fin)
            {
                for (int i = 0; i < row_size - 1; i++)
                {
                    fout << row[i] << ',';
                }
                fout << row[row_size - 1] << "\n";
            }
        }
        else
        {
            if (fin)
            {
                for (int i = 0; i < row_size - 1; i++)
                {
                    fout << row[i] << ',';
                }
                fout << row[row_size - 1] << "\n";
            }
        }
    }
    fin.close();
    fout.close();
    remove("college_dept_details.csv");
    rename("college_dept_details_new.csv", "college_dept_details.csv");
    return dept;
}
void show_dept(string choosen_college, int rank, string college_name)
{
    design();
    cout << "\t    Available departments in " << college_name << endl;
    ifstream fin;
    fin.open("college_dept_details.csv", ios::in);
    string line, word;
    vector<string> row;
    int i = 1, x = 0;
    while (fin)
    {
        row.clear();
        getline(fin, line);
        stringstream s(line);
        while (getline(s, word, ','))
        {
            row.push_back(word);
        }
        if (!s && word.empty())
        {
            row.push_back("");
            break;
        }
        if (row[0] == choosen_college)
        {
            if (stoi(row[4]) >= rank && stoi(row[3]))
            {
                cout << "\t\t\t" << i << ". " << row[2] << '\n';
                i++;
            }
            else
                x++;
        }
    }
    fin.close();
    cout << "\n\t  \xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\n\n";
    cout << "\t      Choose your department\n";
    int choosen_dept;
    cin >> choosen_dept;
    string dept = update(choosen_college, choosen_dept, x);
    system("cls");
    design();
    create_student_details(rank, college_name, dept, choosen_college);
    cout << "\t    Booking done successfully\n";
    cout << "\t\t    Thank You!\n";
    getch();
}

int read_record(int rank)
{
    design();
    cout << "\t  Best colleges for you based on your rank\n";
    ifstream fin;
    fin.open("college_detail.csv", ios::in);
    vector<string> row;
    string line, word;
    int i = 1, x = 0;

    while (fin)
    {
        row.clear();
        getline(fin, line);
        stringstream s(line);
        while (getline(s, word, ','))
        {
            row.push_back(word);
        }
        if (!s && word.empty())
        {
            row.push_back("");
            break;
        }
        if (stoi(row[4]) >= rank && stoi(row[3]))
        {
            cout << "\t\t\t" << i << ". " << row[1] << '\n';
            i++;
        }
        else
            x++;
    }
    fin.close();
    return x;
}
void show_colleges()
{
    design();

    int rank, college_idx;
    cout << "\t\t  Enter your rank\n";
    cin >> rank;
    if (search_rank(rank, false))
        return;
    system("cls");
    int x = read_record(rank);
    cout << "\n\t  \xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\n\n";

    cout << "\t    Choose your favorite college\n";
    cin >> college_idx;
    fstream fin, fout;
    fin.open("college_detail.csv", ios::in);
    fout.open("college_detail_new.csv", ios::out);
    vector<string> row;
    string line, word, choosen_college, college_name;

    while (fin)
    {
        row.clear();
        getline(fin, line);
        stringstream s(line);
        while (getline(s, word, ','))
            row.push_back(word);
        if (!s && word.empty())
        {
            row.push_back("");
            break;
        }

        int row_size = row.size();
        int college_id = stoi(row[0]);
        if (college_id == college_idx + x)
        {
            choosen_college = row[2];
            college_name = row[1];
            int decrease_seats = stoi(row[3]) - 1;
            row[3] = to_string(decrease_seats);
            if (fin)
            {
                for (int i = 0; i < row_size - 1; i++)
                {
                    fout << row[i] << ',';
                }
                fout << row[row_size - 1] << "\n";
            }
        }
        else
        {
            if (fin)
            {
                for (int i = 0; i < row_size - 1; i++)
                {
                    fout << row[i] << ',';
                }
                fout << row[row_size - 1] << "\n";
            }
        }
    }
    fin.close();
    fout.close();
    remove("college_detail.csv");
    rename("college_detail_new.csv", "college_detail.csv");
    system("cls");

    show_dept(choosen_college, rank, college_name);
}

void update_after_withdraw(string college_id, string dept)
{
    fstream fin, fout;
    fin.open("college_dept_details.csv", ios::in);
    fout.open("college_dept_details_new.csv", ios::out);
    string line, word;
    vector<string> row;

    while (fin)
    {
        row.clear();
        getline(fin, line);
        stringstream s(line);

        while (getline(s, word, ','))
        {
            row.push_back(word);
        }
        if (!s && word.empty())
        {
            row.push_back("");
            break;
        }
        int row_size = row.size();
        if (row[0] == college_id && row[2] == dept)
        {
            int convert = stoi(row[3]) + 1;
            row[3] = to_string(convert);
            if (fin)
            {
                for (int i = 0; i < row_size - 1; i++)
                {
                    fout << row[i] << ',';
                }
                fout << row[row_size - 1] << "\n";
            }
        }
        else
        {
            if (fin)
            {
                for (int i = 0; i < row_size - 1; i++)
                {
                    fout << row[i] << ',';
                }
                fout << row[row_size - 1] << "\n";
            }
        }
    }
    fin.close();
    fout.close();
    remove("college_dept_details.csv");
    rename("college_dept_details_new.csv", "college_dept_details.csv");
    fin.open("college_detail.csv", ios::in);
    fout.open("college_detail_new.csv", ios::out);
    while (fin)
    {
        row.clear();
        getline(fin, line);
        stringstream s(line);

        while (getline(s, word, ','))
        {
            row.push_back(word);
        }
        if (!s && word.empty())
        {
            row.push_back("");
            break;
        }
        int row_size = row.size();
        if (row[2] == college_id)
        {
            int convert = stoi(row[3]) + 1;
            row[3] = to_string(convert);
            if (fin)
            {
                for (int i = 0; i < row_size - 1; i++)
                {
                    fout << row[i] << ',';
                }
                fout << row[row_size - 1] << "\n";
            }
        }
        else
        {
            if (fin)
            {
                for (int i = 0; i < row_size - 1; i++)
                {
                    fout << row[i] << ',';
                }
                fout << row[row_size - 1] << "\n";
            }
        }
    }
    fin.close();
    fout.close();
    remove("college_detail.csv");
    rename("college_detail_new.csv", "college_detail.csv");
}
void withdraw()
{
    design();
    int rank;
    cout << "\t\t  Enter your rank\n";
    cin >> rank;
    ifstream fin;
    fin.open("student_details.csv");
    ofstream fout;
    fout.open("temp.csv", ios::out);
    string line, word, college_id, dept;
    bool flag = true;
    vector<string> row;
    while (fin)
    {
        row.clear();
        getline(fin, line);
        stringstream s(line);
        while (getline(s, word, ','))
            row.push_back(word);
        if (!s && word.empty())
        {
            row.push_back("");
            break;
        }
        if (stoi(row[0]) == rank)
        {
            flag = false;
            dept = row[2];
            college_id = row[5];
            continue;
        }
        else
        {
            for (int it = 0; it < row.size() - 1; it++)
                fout << row[it] << ',';
            fout << row[row.size() - 1] << "\n";
        }
    }
    fout.close();
    fin.close();
    remove("student_details.csv");
    rename("temp.csv", "student_details.csv");
    if (flag)
    {
        cout << "\t\t  Rank not found\n";
        getch();
    }
    else
    {
        cout << "\t\t  Seat withdraw successful\n";
        getch();
        update_after_withdraw(college_id, dept);
    }
}

void menu()
{
    system("cls");
    design();
    cout << "\t\t  ------------\n";
    cout << "\t\t  |   MENU   |\n";
    cout << "\t\t  ------------\n";
    cout << "\t\t  1: Book seat\n";
    cout << "\t\t  2: Current status\n";
    cout << "\t\t  3: Withdraw seat\n";
    cout << "\t\t  4: Exit\n";

    int input;
    cin >> input;
    system("cls");
    switch (input)
    {
    case 1:
        show_colleges();
        menu();
        break;
    case 2:
        check_status();
        menu();
        break;
    case 3:
        withdraw();
        menu();
        break;
    case 4:
        cout << "\t\tThank You!\n";
        exit(0);
    default:
        cout << "\t\tInvalid option\n";
        cout << "\t\tChoose valid option....\n";
        getch();
        menu();
        break;
    }
}

bool search_mob(string mob_no, string dob)
{

    ifstream fin;
    fin.open("register.csv", ios::in);
    string line, word;
    vector<string> row;
    while (fin)
    {
        row.clear();
        getline(fin, line);
        stringstream s(line);
        while (getline(s, word, ','))
            row.push_back(word);
        if (!s && word.empty())
        {
            row.push_back("");
            break;
        }
        if (row[0] == mob_no && dob == "")
        {
            return true;
        }
        else if (row[0] == mob_no && row[1] == dob)
            return true;
    }
    fin.close();
    return false;
}

bool check_mob(string s)
{
    if (s.size() != 10)
        return false;
    for (auto it : s)
    {
        if (it < '0' or it > '9')
            return false;
    }
    return true;
}
bool check_dob(string s)
{
    if (s.size() != 8)
        return false;
    for (auto it : s)
    {
        if (it < '0' or it > '9')
            return false;
    }
    return true;
}
void Register()
{
    system("cls");
    design();
    fstream file;
    file.open("register.csv", ios::app);
    string mob_no, dob;
    string user_name;
    cout << "\t\tEnter your Mobile No.\n";
    cin >> mob_no;
    if (mob_no == "-1")
    {
        exit(0);
        return;
    }
    if (!check_mob(mob_no))
    {
        cout << "\t\t Invalid mobile no.\n";
        cout << "\t\t Please reenter\n";
        cout << "\t\t Enter -1 for exit\n";
        getch();
        Register();
    }
    cout << "\t  Enter your Date of birth(DDMMYYYY)\n";
    cin >> dob;
    if (!check_dob(dob))
    {
        cout << "\t\t Invalid date of birth\n";
        cout << "\t\t Please reenter\n";
        cout << "\t\t Enter -1 for exit\n";
        getch();
        Register();
    }
    cout << "\t\tEnter your full name\n";
    getline(cin >> ws, user_name);

    system("cls");
    design();
    if (search_mob(mob_no, ""))
    {
        cout << "\t\tMobile no. already exist\n";
        getch();
        return;
    }
    else
    {
        file << mob_no << ',' << dob << ',' << user_name << "\n";
        file.close();
        cout << "\t\t Registration successful\n";
        getch();
        menu();
    }
}
void login()
{
    system("cls");
    design();
    string mob_no, dob;
    cout << "\t\tEnter your Mobile No.\n";
    cin >> mob_no;
    if (mob_no == "-1")
    {
        exit(0);
        return;
    }
    if (!check_mob(mob_no))
    {
        cout << "\t\t Invalid mobile no.\n";
        cout << "\t\t Please reenter\n";
        cout << "\t\t Enter -1 for exit\n";
        getch();
        login();
    }
    cout << "\t  Enter your Date of birth(DDMMYYYY)\n";
    cin >> dob;
    if (!check_dob(dob))
    {
        cout << "\t\t Invalid date of birth\n";
        cout << "\t\t Please reenter\n";
        cout << "\t\t Enter -1 for exit\n";
        getch();
        login();
    }
    system("cls");
    design();
    if (search_mob(mob_no, dob))
    {
        cout << "\t\t\tWelcome!\n";
        getch();
        menu();
    }
    else
    {
        cout << "\t Mobile no./Date of birth not matched\n";
        getch();
        return;
    }
}

int main()
{
    system("cls");
    design();
    cout << "\t\t1. Register\n";
    cout << "\t\t2. Login\n";
    cout << "\t\t3. Exit\n";
    int entry_key;
    cin >> entry_key;
    if (entry_key == 1)
    {
        Register();
        main();
    }
    else if (entry_key == 2)
    {
        login();
        main();
    }
    else
    {
        exit(0);
    }

    return 0;
}