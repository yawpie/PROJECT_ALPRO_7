#include <iostream>
// #include <thread>
#include <conio.h>
#include <string>
using namespace std;

//! user harus diberikan dana awal 8k-10k untuk beli apa apa
unsigned int BALANCE_AMOUNT = 8000;
int FERTILIZER_AMOUNT = 0;
short int PLANTS_OWNED = 0;
short int GLOBAL_TEMPERATURE = 26;
// TODO buat function int untuk memproses intensitas cahaya matahari
// TODO buat array untuk memproses hari spesial untuk xp
struct plant
{
    int plantID;
    string plantName;
    int plantXP = 0;
    int plantLevel = 0;
    int soilRichness = 0;
    int soilWetness = 0;
    // int fertilizer[3] = {0, 0, 0}; // initial value for fertilizer amount in the soil
    plant *next;
    void waterPlant()
    {
        // jumlah xp yang didapat ketika memberi air bergantung pada jumlah pupuk dan cahaya yang ada di tanaman
        // soilRichness sebaiknya nilainya dilimit 1000, nanti nilai ini dibagi dengan sekian untuk dimasukin ke if else nya

        // ! bagian ini belum slesai

        int xpRisingModifier = soilRichness % plantLevel;
        if (xpRisingModifier <= 10)
        {
            plantXP += 1 + plantName[2] * xpRisingModifier;
        }
        else if (xpRisingModifier <= 20 && xpRisingModifier >= 11)
        {
            plantXP += 2 + plantName[2] * xpRisingModifier;
        }
    }
    void fertilize() //! belum slesai
    {
        int fertilizerModifier[5] = {15, 30, 45, 75, 120};
        // user harus mempunyai dulu pupuk sebelum bisa memberi pupuk
        int i = 0;
        // todo bikin untuk array nya
    }
    void rename() // jika sudah pernah rename sekali, user harus membayar untuk rename lagi
    {
        cout << "\nNama baru: ";
        getline(cin >> ws, plantName);
        cout << "\nBerhasil Menamai tanaman anda menjadi: " << plantName << endl;
        system("pause");
    }
} *head, *onlinePlant;

void addPlant(string name)
{
    PLANTS_OWNED++;
    plant *newPlant = new plant();
    plant *lastPlantNode = head;
    newPlant->plantName = name;
    newPlant->plantID = PLANTS_OWNED;
    newPlant->next = nullptr;

    if (head == nullptr)
    {
        head = newPlant;
        onlinePlant = head;
        return;
    }
    while (lastPlantNode->next != nullptr)
    {
        lastPlantNode = lastPlantNode->next;
    }
    lastPlantNode->next = newPlant;
    onlinePlant = lastPlantNode->next;
    return;
}

int findPlantID(int plantID)
{

    plant *currentPlant = head;
    ;
    while (currentPlant != nullptr)
    {
        if (currentPlant->plantID == plantID)
        {
            onlinePlant = currentPlant;
            return 1;
        }
        currentPlant = currentPlant->next;
    }
    cout << "tidak ada tanaman itu!\n";
    return 0;
}

void buy(int buyID)
{
    switch (buyID)
    {
    case 1:
        if (BALANCE_AMOUNT >= 5000)
        {
            string getNewPlantName;
            system("cls");
            cout << "====!!Pembelian tanaman berhasil!!====\n";
            cout << "\nBeri nama baru: ";
            getline(cin >> ws, getNewPlantName);
            addPlant(getNewPlantName);
            cout << "Berhasil menamai tanaman baru dengan nama: " << getNewPlantName << endl;
            BALANCE_AMOUNT -= 5000;
            system("pause");
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
            FERTILIZER_AMOUNT++;
            BALANCE_AMOUNT -= 600;
            system("cls");
            cout << "Berhasil membeli pupuk\n";
            system("pause");
        }
        else
        {
            system("cls");
            cout << "Uang anda tidak mencukupi\n";
            system("pause");
        }
        break;
    }
    case 3:
    {
        if (BALANCE_AMOUNT >= 1200)
        {
            system("cls");
            cout << "Suhu kebun anda sekarang: " << GLOBAL_TEMPERATURE << endl;
            cout << "\nAtur suhu menjadi: ";
            BALANCE_AMOUNT -= 1200;
            cin >> GLOBAL_TEMPERATURE;
        }
        break;
    }
    case 4:
    {
        if (BALANCE_AMOUNT >= 200)
        {
            plant *temp = head;
            int i = 1, userChoice = 0;
            system("cls");
            cout << "Pilih tanaman yang ingin diganti tanah: \n";
            while (temp != nullptr)
            {
                cout << i << ". " << temp->plantName << endl;
                temp = temp->next;
                i++;
            }
            cin >> userChoice;
            BALANCE_AMOUNT -= 200;
            findPlantID(userChoice);
            // onlinePlant->soilRichness = 0; // TODO ganti jadi array
            onlinePlant->soilWetness = 0;
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
        cout << "\nUang: " << BALANCE_AMOUNT;
        cout << "\n\n0. kembali";
        // ! debug dulu function buy();
        switch (userInput)
        {
        case '1':
            buy(1);
            break;
        case '2':
        {
            buy(2);
            break;
        }
        case '3':
        {
            buy(3);
            break;
        }
        case '4':
        {
            buy(4);
            break;
        }
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

void plantsMenu()
{
    char commandNum;
    while (true)
    {
        // cout << commandNum << endl; //debugging
        system("cls");
        cout << "==== tanaman: " << onlinePlant->plantName << " ====" << endl;
        cout << "Perintah: \n";
        cout << "1. Siram Tanaman\n";
        cout << "2. Lewati Hari\n";
        cout << "3. Ubah Nama Tanaman\n\n";
        cout << "0. Kembali\n";

        switch (commandNum)
        {
        case '1':
        {
            onlinePlant->waterPlant();
            break;
        }
        case '2':
        {
            onlinePlant->fertilize(FERTILIZER_AMOUNT);
            break;
        }
        case '3':
        {
            onlinePlant->rename();
            break;
        }
        case '0':
        {
            return;
            break;
        }
        default:
            break;
        }

        switch (commandNum)
        {
        case '1':
        {
            cout << "\nAnda telah menyiram\n";
            break;
        }
        case '2':
        {
            cout << "\nAnda telah melewati satu hari\n";
            break;
        }
        case '3':
        {
            break;
        }
        default:
            break;
        }
        commandNum = getch();
        cout << endl;
    }
}

void plantsListMenu()
{
    system("cls");
    int userInput = 0;
    int i = 0;
    plant *currentPlant = head;
    while (currentPlant != nullptr)
    {
        cout << i + 1 << ". " << currentPlant->plantName << endl;
        currentPlant = currentPlant->next;
        i++;
    }
    cout << "\n0. Kembali\n";

    do
    {
        cout << "\nPilih Tanaman (Tekan Enter): ";
        cin >> userInput;
        if (userInput == 0)
        {
            return;
        }
    } while (findPlantID(userInput) == 0);

    plantsMenu();
}

/*
    Function ini dipake untuk mengolah data cuaca yang
    ada sekarang, kemudian nanti akan mengubah cuaca di
    kondisi berikutnya

    function ini akan berjalan terus menerus selama
    program berjalan dengan menggunakan fitur std::thread
    kemudian ketika dibutuhkan data cuaca, akan berhenti
    sejenak kemudian melanjutkannya
*/
void weatherNextCycle(char seed) // TODO slesaikan fitur cuaca
{
    while (true)
    {
    }
}

int main()
{
    char mainMenuChoice;
    string new_plantName;
    if (PLANTS_OWNED == 0)
    {
        cout << "Selamat Datang di Water Your Plants!\n";
        cout << "Berikan Nama Tanaman Pertamamu!\n";
        cout << "Nama: ";
        getline(cin >> ws, new_plantName);
        addPlant(new_plantName);
        cout << "\nNama tanaman pertama anda adalah: " << onlinePlant->plantName << endl;
        system("pause");
    }

    while (true)
    {
        system("cls");
        cout << "==== Main Menu ====\n";
        cout << "Pilihan:\n";
        cout << "1. Kebun\n";
        cout << "2. Toko\n";
        cout << "3. Pengaturan\n\n";
        cout << "0. Exit\n";
        mainMenuChoice = getch();

        if (mainMenuChoice == '1')
        {
            plantsListMenu();
        }
        else if (mainMenuChoice == '2')
        {
            shopMainMenu();
        }
        else if (mainMenuChoice == '3')
        {
            // TODO bikin fitur settings stelah semua logic jadi
        }
        else if (mainMenuChoice == '0')
        {
            break;
        }
    }

    system("cls");
    cout << "See you next time\n\n";
    system("pause");
    return 0;
}
