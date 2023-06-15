#include <iostream>

using namespace std;

struct plant
{
    int plantID;
    string plantName;
    int plantXP = 0;
    int plantLevel = 0;
    int soilRichness = 0;
    int soilWetness = 0;
    struct fertilizer
    {
        int nitrogen;
        int phosporus;
        int kalium;
    } fertilizerPercentage = {0, 0, 0}; // initial value for fertilizer amount in the soil
    plant *next;
    void waterPlant()
    {
        // jumlah xp yang didapat ketika memberi air bergantung pada jumlah pupuk dan cahaya yang ada di tanaman
        // soilRichness sebaiknya nilainya dilimit 1000, nanti nilai ini dibagi dengan sekian untuk dimasukin ke if else nya

        // TODO buat if else untuk mengatur dan memeriksa kandungan pupuk di tanahnya

        int temp_soilRichness = soilRichness;
        if (temp_soilRichness <= 18)
        {
            // plantXP += ;
        }
    }
    void fertilize(int _fertilizerLeft)
    {
        // user harus mempunyai dulu pupuk sebelum bisa memberi pupuk
    }
    void rename() // jika sudah pernah rename sekali, user harus membayar untuk rename lagi
    {
        cout << "\nNama baru: ";
        getline(cin >> ws, plantName);
        cout << "\nBerhasil Menamai tanaman anda menjadi: " << plantName << endl;
        system("pause");
    }
} *head, *onlinePlant;

void addPlant(plant **reference, string name)
{
    PLANTS_OWNED++;
    plant *newPlant = new plant();
    plant *lastPlantNode = *reference;
    newPlant->plantName = name;
    newPlant->plantID = PLANTS_OWNED;
    newPlant->next = nullptr;

    if (*reference == nullptr)
    {
        *reference = newPlant;
        onlinePlant = *reference;
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

int findPlantID(plant **reference, int plantID)
{

    plant *currentPlant = *reference;
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