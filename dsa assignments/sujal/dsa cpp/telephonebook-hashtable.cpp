/* Consider telephone book database of N clients. Make use of a hash table implementation to quickly look up client‘s telephone number.
Make use of two collision handling techniques and compare them using number of comparisons required to find a set of telephone numbers */

#include <iostream>
#define MAX 10
using namespace std;

struct node
{
    string name;
    long long int telephone_number;
};

class hash_functions
{
private:
    node data[MAX];

public:
    hash_functions()
    {
        for (int i = 0; i < MAX; i++)
        {
            data[i].name = " ";
            data[i].telephone_number = 0;
        }
    }
    void insert();
    int hash(string client_name);
    void search();
    void display();
};

int main()
{
    std::cout << "\n--------------------------------------------------" << std::endl;
    std::cout << "--------------------------------------------------" << std::endl;
    hash_functions obj;
    int choice;
    do
    {
        std::cout << "1.Insert" << std::endl;
        std::cout << "2.Search" << std::endl;
        std::cout << "3.Display" << std::endl;
        std::cout << "4.Exit" << std::endl;
        std::cout << "--------------------------------------------------" << std::endl;
        std::cout << "Enter your choice: ";
        cin >> choice;
        std::cout << "--------------------------------------------------" << std::endl;
        switch (choice)
        {
        case 1:
            obj.insert();
            break;
        case 2:
            obj.search();
            break;
        case 3:
            obj.display();
            break;
        case 4:
            std::cout << "Thank You" << std::endl;
            break;
        default:
            std::cout << "Invalid Choice" << std::endl;
            std::cout << "--------------------------------------------------" << std::endl;
            break;
        }
    } while (choice != 4);

    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << "--------------------------------------------------" << std::endl;

    return 0;
}

void hash_functions::insert()
{
    int pos;
    string client_name;
    long int telephone_number;

    std::cout << "Enter the name of client: ";
    cin >> client_name;
    std::cout << "Enter the client telephone number: ";
    cin >> telephone_number;
    pos = hash(client_name);
    int c = pos;
    bool flag = false;
    
    while (flag != true)
    {
        if (data[pos].name == " " && data[pos].telephone_number == 0)
        {
            data[pos].name = client_name;
            data[pos].telephone_number = telephone_number;
            flag = true;
            cout << "Hash is: " << pos << endl;
            break;
        }

        pos = (pos + 1) % 10;

        if (c == pos)
        {
            std::cout << "Hash Table is Full." << std::endl;
            break;
        }
    }

    std::cout << "--------------------------------------------------" << std::endl;
}

int hash_functions::hash(string client_name)
{
    int sum = 0;
    for (int i = 0; i < client_name.length(); i++)
    {
        sum += (int)client_name[i];
    }

    return (sum / client_name.length()) % 10;
}

void hash_functions::search()
{
    int pos;
    string client_name;
    std::cout << "Enter client name to be searched: ";
    cin >> client_name;
    pos = hash(client_name);
    int c = pos;
    bool flag = false;

    while (flag != true)
    {
        if (data[pos].name == client_name)
        {
            std::cout << "Data Found. Telephone number is: " << data[pos].telephone_number << std::endl;
            flag = true;
            break;
        }

        pos = (pos + 1) % 10;

        if (c == pos)
        {
            std::cout << "Data Not Found" << std::endl;
            break;
        }
    }
    std::cout << "--------------------------------------------------" << std::endl;
}

void hash_functions::display()
{
    for (int i = 0; i < MAX; i++)
    {
        std::cout << i << ". Name: " << data[i].name << "\n   Telephone_number: " << data[i].telephone_number << std::endl;
    }
    std::cout << "--------------------------------------------------" << std::endl;
}