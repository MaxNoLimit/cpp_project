#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <string>
using namespace std;

//Richie Angjaya 2502030536
//Roger Gibson 2502015453

string item;
int price, bill, money, change, confirm = 0;
fstream toFile;
char confirmation;

void paymentContinue()
{
    cout << "The total of your purchase: " << bill << "\n";
    cout << "Please input the nominal of the payment: ";
    cin >> money;
    change = money - bill;
    cout << "\nYour change is: " << change <<"\n\n\n";
}

void addingItems()
{
    toFile.open("ItemRecords.dat", std::ofstream::in | std::ofstream::out | std::ofstream::app);

    cout << "Enter the item name: ";
    cin.ignore();
    getline(cin, item);

    for (int i = 0; i < item.length(); i++)
    {
        item[i] = tolower(item[i]);
    }

    toFile << item << "\t";

    do
    {
        cout << "Enter the price of the item (in Rupiah): ";
        cin >> price;

        if (price > 0)
        {
            continue;
        }
        else
        {
            cout << "Please enter a valid price\n";
        }
    } while (price < 1);

    toFile << price << "\n";
    cout << "Would you like to add another item? (y/n) \n";
    cin >> confirmation;
    toFile.close();
    while (confirmation == 'y')
    {
        return addingItems();
    }
}

void priceCheck()
{
    string findPrice;
    string priceArray[1000][2];

    toFile.open("ItemRecords.dat", std::ofstream::in | std::ofstream::out | std::ofstream::app);

    for (int i = 0; i < 1000; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            toFile >> priceArray[i][j];
        }
    }

    cout << "Enter the item you are looking for: ";
    cin.ignore();
    getline(cin, findPrice);

    for (int i = 0; i < findPrice.length(); i++)
    {
        findPrice[i] = tolower(findPrice[i]);
    }

    for (int z = 0; z < 1000; z++)
    {
        if (findPrice == priceArray[z][0])
        {
            cout << "The item has been found!\n"
                 << priceArray[z][0] << " is Rp" << priceArray[z][1] << "\n";
            break;
        }
    }
    cout << "Would you like to check another item? (y/n) \n";
    cin >> confirmation;
    toFile.close();
    while (confirmation == 'y')
    {
        return priceCheck();
    }
}

void payment()
{
    int quantity=0;
    string findPrice;
    string priceArray[1000][2];

    toFile.open("ItemRecords.dat", std::ofstream::in | std::ofstream::out | std::ofstream::app);

    for (int i = 0; i < 1000; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            toFile >> priceArray[i][j];
        }
    }

    cout << "Enter the item you are looking for: ";
    cin.ignore();
    getline(cin, findPrice);
    cout << "How many? \n";
    cin >> quantity;

    for (int i = 0; i < findPrice.length(); i++)
    {
        findPrice[i] = tolower(findPrice[i]);
    }

    for (int z = 0; z < 1000; z++)
    {
        if (findPrice == priceArray[z][0])
        {
            bill = bill + quantity*(stoi(priceArray[z][1]));
            cout << "Do you to add more items? (y/n) \n";
            cin >> confirmation;
            while (confirmation == 'y')
            {
                toFile.close();
                return payment();
            }
            paymentContinue();
            confirm = 1;
        }
    }
    if (confirm != 1)
    {
        cout << "The item is not available :( \n";
        cout << "Do you want to try again? (y/n) \n";
        cin >> confirmation;
        while (confirmation == 'y')
        {
            return payment();
        }
    }
}

int main()
{
    int inputNumber;
    do
    {
        cout << "\nHello, what do you want to do?\n";
        cout << "Please type the number from the following activities:\n";
        cout << "1 Adding items\n2 Check the price of an item\n3 Calculating payment\n4 Exit\n\n";
        cin >> inputNumber;

        if (inputNumber == 1)
        {
            cout << "You've just called the addingItems function!\n";
            addingItems();
        }
        else if (inputNumber == 2)
        {
            cout << "You've just called the priceCheck function!\n";
            priceCheck();
        }
        else if (inputNumber == 3)
        {
            cout << "You've just called the payment function!\n";
            payment();
        }
        else if (inputNumber == 4)
        {
            return 0;
        }
        else
        {
            cout << "Please input a valid number\n";
        }
    } while (inputNumber != 1 || inputNumber != 2 || inputNumber != 3);

    return 0;
}