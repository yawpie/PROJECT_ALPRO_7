#include <iostream>
// #include <thread>
#include <conio.h>

using namespace std;

//! user harus diberikan dana awal 8k-10k untuk beli apa apa
unsigned int BALANCE_AMOUNT = 8000;
int FERTILIZER_AMOUNT = 0;
short int PLANTS_OWNED = 0;
short int GLOBAL_TEMPERATURE = 26;
short int CURRENT_DAY = 0;
string CURRENT_DAY_NAME[7] = {"senin", "selasa", "rabu", "kamis", "jumat", "sabtu", "minggu"};
// todo bikin sistem untuk skip hari atau setelah menyiram tanaman beberapa kali bisa skip hari
struct plant
{
    int plantID;
    string plantName;
    int plantXP = 0;
    int plantLevelUpThreshold = 1;
    int plantLevel = 1;
    int soilRichness = 10;
    int soilWetness = 30;
    int plantHealth = 100;
    plant *next;
    void levelUp()
    {
        plantLevel++;
        plantLevelUpThreshold * 2;
    }
    void waterPlant()
    {
        // jumlah xp yang didapat ketika memberi air bergantung pada jumlah pupuk dan cahaya yang ada di tanaman
        // soilRichness sebaiknya nilainya dilimit 1000, nanti nilai ini dibagi dengan sekian untuk dimasukin ke if else nya
        plantXP += 2 + 0.35 * soilRichness;
        if (soilRichness > 0)
        {
            soilRichness -= 20;
        }
        else
        {
            soilRichness = 0;
        }
        soilWetness += 10;
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
            plantHealth -= 45;
        }
    }
    void fertilize() //! belum slesai
    {
        if (soilRichness >= 100)
        {
            system("pause");
            cout << "pupuk terlalu banyak, tidak dapat memberi lebih banyak\n";
            return;
        }
        soilRichness += 34;
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
            cout << "Jumlah pupuk anda sekarang: " << FERTILIZER_AMOUNT << endl;
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

void sellPlant(int plantID)
{
    plant *currentPlant = head;
    plant *prevPlant = nullptr;

    if (PLANTS_OWNED <= 1)
    {
        cout << "Tidak dapat menjual tanaman. Setidaknya harus ada 1 tanaman tersisa di kebun.\n";
        return;
    }
    while (currentPlant != nullptr)
    {
        if (currentPlant->plantID == plantID)
        {

            if (prevPlant == nullptr)
            {
                head = currentPlant->next;
            }
            else
            {
                prevPlant->next = currentPlant->next;
            }
            BALANCE_AMOUNT += 2500;
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
        cout << "\nPilih Tanaman yang ingin dijual (Tekan Enter): ";
        cin >> userInput;
        if (userInput == 0)
        {
            return;
        }
    } while (findPlantID(userInput) == 0);

    sellPlant(userInput);
    system("pause");
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
        cout << "1. beli perlengkapan\n";
        cout << "2. jual tanaman\n";
        cout << "0. kembali\n";
        shopMenuChoice = getch();
    }
}

void plantsMenu(int &health)
{
    char commandNum;
    while (true)
    {
        system("cls");
        cout << "==== tanaman: " << onlinePlant->plantName << " ====" << endl;
        if (health >= 0)
        {
            cout << "Persentase Kesehatan Tanaman: " << onlinePlant->plantHealth << endl;
            cout << "Persentase Kebasahan Tanaman: " << onlinePlant->soilWetness << endl;
            cout << "Persentase Kandungan Pupuk: " << onlinePlant->soilRichness << endl;
            cout << "\nPerintah: \n";
            cout << "1. Siram Tanaman\n";
            cout << "2. Lewati Hari\n";
            cout << "3. Ubah Nama Tanaman\n\n";
            switch (commandNum)
            {
            case '1':
            {
                onlinePlant->waterPlant();
                cout << "Anda telah menyiram\n";
                break;
            }
            case '2':
            {
                cout << "\nAnda telah melewati satu hari\n";
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
        }
        else
        {
            cout << "\nTanaman mati\n";
            if (commandNum == '0')
            {
                return;
            }
        }
        cout << "0. Kembali\n";

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

    plantsMenu(onlinePlant->plantHealth);
}

int main()
{
    char mainMenuChoice;
    char exitMenuChoice;
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
