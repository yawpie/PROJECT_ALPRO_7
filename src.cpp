#include <iostream>
#include <conio.h>

using namespace std;

unsigned int BALANCE_AMOUNT = 8000;
int FERTILIZER_OWNED = 0;
short unsigned int PLANTS_OWNED = 0;
short int GLOBAL_TEMPERATURE = 26;
short unsigned int CURRENT_DAY = 0;
string CURRENT_DAY_NAME[7] = {"Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu", "Minggu"};
short unsigned int ENERGY = 5;
// todo bikin sistem untuk skip hari atau setelah menyiram tanaman beberapa kali bisa skip hari
struct plant
{
    bool isAlive = true;
    string plantName;
    int plantXP = 0;
    int plantLevelUpThreshold = 10;
    int plantLevel = 1;
    int soilRichness = 20;
    int soilWetness = 60;
    int plantHealth = 100;
    plant *next;
    void levelUp()
    {
        if (plantXP > plantLevelUpThreshold)
        {
            plantLevel++;
            plantLevelUpThreshold *= 2;
            system("cls");
            cout << "Selamat! Tanaman Anda Naik Level!\n";
            cout << "Level " << plantLevel - 1 << " ------> Level " << plantLevel << endl;
            if (plantLevel % 5 == 0)
            {
                BALANCE_AMOUNT += plantLevel * 600;
                cout << "Selamat! Anda mendapat budget tambahan sebesar " << plantLevel * 500 << " sebagai hadiah!" << endl;
                cout << "Tekan Enter untuk melanjutkan\n";
                return;
            }

            cout << "Anda mendapat budget tambahan sebesar " << plantLevel * 100 << " sebagai hadiah!" << endl;
            BALANCE_AMOUNT += plantLevel * 200;
            cout << "Tekan Enter untuk melanjutkan\n";
            return;
        }
    }
    void waterPlant()
    {
        if (soilRichness > 0)
        {
            soilRichness -= 20;
        }
        else
        {
            soilRichness = 0;
        }
        soilWetness += 7;
        if (soilWetness >= 70 && soilWetness < 80)
        {
            plantHealth -= 8;
        }
        else if (soilWetness >= 80 && soilWetness < 95)
        {
            plantHealth -= 15;
        }
        else if (soilWetness >= 95)
        {
            plantHealth -= 30;
        }
        else if (soilWetness >= 100)
        {
            plantHealth -= 40;
        }

        plantXP += 2 + 0.35 * soilRichness;
        cout << "Berhasil menyiram tanaman ini!\n";
        levelUp();
        ENERGY--;
    }
    void fertilize()
    {
        if (FERTILIZER_OWNED > 0)
        {
            if (soilRichness >= 100)
            {
                cout << "Pupuk sudah terlalu banyak, tidak dapat memberi lebih banyak\n";
                return;
            }
            FERTILIZER_OWNED--;
            cout << "Berhasil memberi pupuk kepada tanaman ini!\n";
            soilRichness += 34;
        }
        else
        {
            cout << "\nPupuk anda tidak cukup! Silahkan membeli di toko\n";
            return;
        }
        ENERGY--;
    }
    void rename()
    {
        cout << "\nNama baru: ";
        getline(cin >> ws, plantName);
        BALANCE_AMOUNT -= 750;
        cout << "\nBerhasil Menamai tanaman anda menjadi: " << plantName << endl;
        ENERGY--;
        system("pause");
    }
    void soilReset()
    {
        if (BALANCE_AMOUNT >= 200)
        {
            soilRichness = 20;
            soilWetness = 30;
            cout << "Berhasil Mengganti Tanah!\n";
            ENERGY--;
            return;
        }
        cout << "\nBudget Anda Tidak Cukup!\n";
        return;
    }
    void checkHealth()
    {
        if (plantHealth <= 0)
        {
            isAlive = false;
        }
        if (soilWetness <= 25 && soilWetness > 0)
        {
            plantHealth -= 10;
        }
        else if (soilWetness <= 0)
        {
            soilWetness = 0;
            plantHealth -= 18;
        }
    }
} *head, *onlinePlant;

void addPlant(string name)
{
    PLANTS_OWNED++;
    plant *newPlant = new plant();
    plant *lastPlantNode = head;
    newPlant->plantName = name;
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

bool findPlantName(string plantName)
{

    plant *currentPlant = head;
    while (currentPlant != nullptr)
    {
        if (currentPlant->plantName == plantName)
        {
            onlinePlant = currentPlant;
            return true;
        }
        currentPlant = currentPlant->next;
    }
    cout << "tidak ada tanaman itu!\n";
    return false;
}

void finishDay()
{
    plant *current = head;
    if (ENERGY == 0)
    {
        CURRENT_DAY++;
        while (current != nullptr)
        {
            current->soilWetness -= GLOBAL_TEMPERATURE * 0.25;
            current = current->next;
        }
        if (CURRENT_DAY == 7)
        {
            CURRENT_DAY = 0;
        }
        cout << "Satu hari sudah dilewati.\nSekarang hari: " << CURRENT_DAY_NAME[CURRENT_DAY];
        if (CURRENT_DAY_NAME[CURRENT_DAY] == "Kamis")
        {
            GLOBAL_TEMPERATURE = (CURRENT_DAY_NAME[CURRENT_DAY].length() * GLOBAL_TEMPERATURE) / 5 + 6;
            ENERGY = 5;
            onlinePlant->checkHealth();
            return;
        }
        GLOBAL_TEMPERATURE = (CURRENT_DAY_NAME[CURRENT_DAY].length() * GLOBAL_TEMPERATURE) / 6 + 5;
        onlinePlant->checkHealth();
        cout << endl;
        ENERGY = 5;
    }
}

void buyToolsMenu()
{
    char userInput;
    while (true)
    {
        system("cls");
        cout << "=== Perlengkapan Kebun & Tanaman ===\n";
        cout << "1. Tanaman Baru \t\t5000\n";
        cout << "2. Pupuk\t\t\t100\n";
        cout << "3. Ganti Suhu Rumah Kaca\t1200\n";
        cout << "\nBudget: " << BALANCE_AMOUNT;
        cout << "\n\n0. kembali";

        switch (userInput)
        {
        case '1':
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
                cout << "Uang anda tidak mencukupi\n";
            }
            break;
        case '2':
        {
            if (BALANCE_AMOUNT >= 100)
            {
                FERTILIZER_OWNED++;
                BALANCE_AMOUNT -= 100;
                cout << "\nBerhasil membeli pupuk\n";
                cout << "Jumlah pupuk anda sekarang: " << FERTILIZER_OWNED << endl;
            }
            else
            {
                cout << "Uang anda tidak mencukupi\n";
            }
            break;
        }
        case '3':
        {
            if (BALANCE_AMOUNT >= 1200)
            {
                system("cls");
                cout << "Suhu kebun anda sekarang: " << GLOBAL_TEMPERATURE << endl;
                cout << "\nAtur suhu menjadi: ";
                BALANCE_AMOUNT -= 1200;
                cin >> GLOBAL_TEMPERATURE;
            }
            else
            {
                cout << "Uang anda tidak mencukupi\n";
            }
            break;
        }
        case '0':
            return;
            break;
        default:
            break;
        }
        userInput = getch();
    }
}

void sellPlant(string plantName)
{
    plant *currentPlant = head;
    plant *prevPlant = nullptr;

    if (PLANTS_OWNED <= 1)
    {
        cout << "\nTidak dapat menjual tanaman. Setidaknya harus ada 1 tanaman tersisa di kebun.\n";
        return;
    }
    while (currentPlant != nullptr)
    {
        if (currentPlant->plantName == plantName)
        {

            if (prevPlant == nullptr)
            {
                head = currentPlant->next;
            }
            else
            {
                prevPlant->next = currentPlant->next;
            }
            BALANCE_AMOUNT += currentPlant->plantLevel * 1500 + currentPlant->plantXP * 10;
            // todo ketika ingin jual tanaman, akan melihat variabel plantHealth, semakin rendah health nya, semakin rendah harga jualnya. jika planthealth = 0 maka harga jual adalah 0
            PLANTS_OWNED--;
            delete currentPlant;
            cout << "Tanaman berhasil dijual\n";
            PLANTS_OWNED--;
            cout << "Saldo Anda sebelumnya: " << BALANCE_AMOUNT - 2500 << endl;
            cout << "Saldo Anda saat ini: " << BALANCE_AMOUNT << endl;
            return;
        }
        prevPlant = currentPlant;
        currentPlant = currentPlant->next;
    }

    cout << "Tanaman tidak ditemukan\n";
}

void sellPlantMenu()
{
    system("cls");
    string userInput;
    int i = 0;
    plant *currentPlant = head;

    while (currentPlant != nullptr)
    {
        cout << i + 1 << ". " << currentPlant->plantName << endl;
        currentPlant = currentPlant->next;
        i++;
    }
    do
    {
        cout << "\nTanaman yang ingin dijual (Ketik 0 untuk kembali): ";
        getline(cin >> ws, userInput);
        if (userInput == "0")
        {
            return;
        }

    } while (findPlantName(userInput) == false);

    sellPlant(userInput);
    system("pause");
    return;
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
            sellPlantMenu();
            break;
        case '0':
            return;
            break;
        default:

            break;
        }
        system("cls");

        cout << "==== Toko Perlengkapan Kebun ====\n";
        cout << "1. Perlengkapan Kebun & Tanaman\n";
        cout << "2. Jual Tanaman\n";
        cout << "\n0. Kembali\n";
        shopMenuChoice = getch();
    }
}

void plantsMenu()
{
    char commandNum;
    while (true)
    {
        system("cls");
        cout << "======== Tanaman: " << onlinePlant->plantName << " ========" << endl;
        if (onlinePlant->isAlive)
        {
            cout << "Level: " << onlinePlant->plantLevel << endl;
            cout << "\nXP\t\t\t: " << onlinePlant->plantXP << endl;
            cout << "XP untuk Naik Level\t: " << onlinePlant->plantLevelUpThreshold << endl;
            cout << "Kesehatan\t\t: " << onlinePlant->plantHealth << endl;
            cout << "Kebasahan\t\t: " << onlinePlant->soilWetness << endl;
            cout << "Keelokan Tanah\t\t: " << onlinePlant->soilRichness << endl;
            cout << "\nPupuk\t\t\t: " << FERTILIZER_OWNED << endl;
            cout << "Hari\t\t\t: " << CURRENT_DAY_NAME[CURRENT_DAY] << endl;
            cout << "Suhu\t\t\t: " << GLOBAL_TEMPERATURE << endl;
            cout << "Tenaga\t\t\t: " << ENERGY << endl;

            cout << "\nPerintah: \n";
            cout << "1. Siram Tanaman\n";
            cout << "2. Berikan Pupuk\n";
            cout << "3. Ubah Nama Tanaman (Harga: 750)\n";
            cout << "4. Ganti Tanah Tanaman (Harga: 200)\n";
            cout << "5. Lewati Hari Ini\n";
            cout << "\nBudget: " << BALANCE_AMOUNT << endl;

            switch (commandNum)
            {
            case '1':
            {
                onlinePlant->waterPlant();
                break;
            }
            case '2':
            {
                onlinePlant->fertilize();
                break;
            }
            case '3':
            {
                onlinePlant->rename();
                break;
            }
            case '4':
            {
                onlinePlant->soilReset();
                break;
            }
            case '5':
            {
                ENERGY = 0;
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
        }
        else
        {
            cout << "\nTanaman ini mati\n\n";
            if (commandNum == '0')
            {
                return;
            }
        }
        finishDay();
        cout << "0. Kembali\n";
        commandNum = getch();
        cout << endl;
        onlinePlant->levelUp();
        // onlinePlant->checkHealth();
    }
}

void plantsListMenu()
{
    while (true)
    {
        system("cls");
        string userInput;
        int i = 0;
        plant *currentPlant = head;
        cout << "=== Menu Pilih Tanaman ===\n";
        while (currentPlant != nullptr)
        {
            cout << i + 1 << ". " << currentPlant->plantName << endl;
            currentPlant = currentPlant->next;
            i++;
        }
        do
        {
            cout << "\nPilih Nama Tanaman (Ketik 0 untuk kembali): ";
            getline(cin >> ws, userInput);
            if (userInput == "0")
            {
                return;
            }
        } while (findPlantName(userInput) == 0);

        plantsMenu();
    }
}

int main()
{
    char mainMenuChoice;
    char exitMenuChoice;
    string new_plantName;

    cout << "Selamat Datang di Water Your Plants!\n";
    cout << "Berikan Nama Tanaman Pertamamu!\n";
    cout << "Nama: ";
    getline(cin >> ws, new_plantName);
    addPlant(new_plantName);
    cout << "\nNama tanaman pertama anda adalah: " << onlinePlant->plantName << endl;
    cout << "Selamat Datang dan Selamat Menyiram!\n";
    system("pause");

    while (true)
    {
        system("cls");
        cout << "==== Main Menu ====\n";
        cout << "Pilihan:\n";
        cout << "1. Pengelola Tanaman\n";
        cout << "2. Toko Kebun\n";
        cout << "\n0. Exit\n";
        mainMenuChoice = getch();

        if (mainMenuChoice == '1')
        {
            plantsListMenu();
        }
        else if (mainMenuChoice == '2')
        {
            shopMainMenu();
        }
        else if (mainMenuChoice == '0')
        {
            cout << "\nApakah anda yakin ingin keluar? (Y/N) ";
            cin >> exitMenuChoice;
            if (exitMenuChoice == 'y' || exitMenuChoice == 'Y')
            {
                cout << "\nSee you next time\n\n";
                system("pause");
                return 0;
            }
        }
    }
}
