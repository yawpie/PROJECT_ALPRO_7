#include <iostream>
#include <string>
#include <conio.h>
using namespace std;

//! user harus diberikan dana awal 8k-10k untuk beli pupuk, atur suhu, dsb
unsigned int MONEY = 8000;
int FERTILIZER_AMOUNT = 0;
short int FERTILIZER_TYPE = 0;

struct plant
{
    string plantName;
    int plantXP = 0;
    void waterPlant()
    {
        // jumlah xp yang didapat ketika memberi air bergantung pada jumlah pupuk dan cahaya yang ada di tanaman

        plantXP++; // TODO buat if else untuk mengatur dan memeriksa kandungan pupuk di tanahnya
    }
    void fertilize(int _fertilizerLeft)
    {
        // user harus mempunyai dulu pupuk sebelum bisa memberi pupuk
    }
    void rename() // jika sudah pernah rename sekali, user harus membayar untuk rename lagi
    {
        cout << "\nNama baru: ";
        getline(cin >> ws, plantName);
    }
} plantObject;

// TODO buat function int untuk memproses intensitas cahaya matahari
// TODO buat function untuk beli kebutuhan berkebun dan tanaman tambahan

/*
    Function ini dipake untuk mengolah data cuaca yang
    ada sekarang, kemudian nanti akan mengubah cuaca di
    kondisi berikutnya
*/
void weatherNextCycle(char seed)
{
    // TODO buat isinya function ini
}

/*
    function ini dipake untuk membaca kode yang didapat
    dari inputan user yang masuk ketika program berjalan
*/
void commandController(char commandGiven)
{
    switch (commandGiven)
    {
    case '1':
    {
        plantObject.waterPlant();
        break;
    }
    case '2':
    {
        plantObject.fertilize(FERTILIZER_AMOUNT);
        break;
    }
    case '3':
    {
        plantObject.rename();
        break;
    }
    default:
        break;
    }
}

int main()
{
    while (true)
    {
        char commandNum;
        cout << commandNum << endl;
        // system("cls");
        cout << "selamat datang!\n";
        cout << "perintah: \n";
        cout << "1. siram\n";
        cout << "2. skip hari\n";
        cout << "3. rename\n";
        cout << "perintah: 1/2/3";
        commandNum = getch();
        cout << "\nAnda memilih " << commandNum << endl;
        commandController(commandNum);
        cout << endl;
    }

    cout << "\n--------------------------------\n";
    system("pause");
    return 0;
}