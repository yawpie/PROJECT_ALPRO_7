#include <iostream>
using namespace std;

void buy(int buyID)
{
    switch (buyID)
    {
    case 1:
        if (BALANCE_AMOUNT >= 5000)
        {
            string getNewPlantName;
            system("cls");
            cout << "\n\nPembelian tanaman berhasil\n";
            cout << "\nsilahkan beri Nama: ";
            // getline(cin >> ws, getNewPlantName);
            addPlant(&head, "");
            // cout << "onlinePlant name: " << onlinePlant->plantName;
            onlinePlant->rename();
        }
        else
        {
            system("cls");
            cout << "Uang anda tidak mencukupi\n";
            system("pause");
        }

        break;
    case 2:
    {
        if (BALANCE_AMOUNT >= 600)
        {
            // TODO bikin codingan beli pupuk
        }

        break;
    }
    default:
        break;
    }
}

void buyToolsMenu()
{
    char userInput;
    while (true)
    {
        system("cls");
        cout << "1. tanaman \t5000\n";
        cout << "2. pupuk\t600\n";
        cout << "3. atur suhu 1 kali\t1200\n";
        cout << "4. ganti tanah\t200\n";
        cout << "\n0. kembali";
        switch (userInput)
        {
        case '1':
            // ! debug dulu function buy();
            buy(1);
            break;
        case '0':
        {
            return;
        }
        default:
            break;
        }
        userInput = getch();
    }
}

void shopMainMenu()
{
    char shopMenuChoice;
    while (true)
    {
        system("cls");
        switch (shopMenuChoice)
        {
        case '1':
            buyToolsMenu();
            break;
        case '2':
            // TODO buat menu jual tanaman
            break;
        case '0':
            return;
            break;
        default:

            break;
        }
        system("cls");

        cout << "==== Toko Perlengkapan Kebun ====\n";
        cout << "1. beli perlengkapan\n";
        cout << "2. jual tanaman\n";
        cout << "0. kembali\n";

        shopMenuChoice = getch();
    }
}
