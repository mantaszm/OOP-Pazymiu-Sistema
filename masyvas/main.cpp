#include "funkcijos.h"
#include <chrono>
#include <iomanip>

int main() {
    size_t studentuKiekis = 0;
    Studentas* studentai = nullptr;

    std::cout << "Pasirinkite ivesti:\n1 - terminalas\n2 - failas\n";
    char pasirinkimas;
    std::cin >> pasirinkimas;
    std::cin.ignore();

    if (pasirinkimas == '1') {
        studentai = readTerminal(studentuKiekis);
    } else if (pasirinkimas == '2') {
        std::string failas;
        std::cout << "Iveskite failo pavadinima: ";
        std::getline(std::cin, failas);
        studentai = readFile(failas, studentuKiekis);
    } else {
        std::cout << "Blogas pasirinkimas\n";
        return 0;
    }

    std::cout << "\nRikiavimas:\n1 - Vardas\n2 - Pavarde\n3 - Galutinis (Vid.)\n4 - Galutinis (Med.)\n";
    char rikiavimas;
    std::cin >> rikiavimas;

    auto start = std::chrono::high_resolution_clock::now();

    switch (rikiavimas) {
        case '1':
            std::sort(studentai, studentai + studentuKiekis,
                [](const Studentas& a, const Studentas& b) {
                    return std::strcmp(a.vardas, b.vardas) < 0;
                });
            break;

        case '2':
            std::sort(studentai, studentai + studentuKiekis,
                [](const Studentas& a, const Studentas& b) {
                    return std::strcmp(a.pavarde, b.pavarde) < 0;
                });
            break;

        case '3':
            std::sort(studentai, studentai + studentuKiekis,
                [](const Studentas& a, const Studentas& b) {
                    double vidA = a.namuDarbaiVid100 * 0.004 + a.egzaminas * 0.6;
                    double vidB = b.namuDarbaiVid100 * 0.004 + b.egzaminas * 0.6;
                    return vidA < vidB;
                });
            break;

        case '4':
            std::sort(studentai, studentai + studentuKiekis,
                [](const Studentas& a, const Studentas& b) {
                    double medA = a.namuDarbaiMed100 * 0.004 + a.egzaminas * 0.6;
                    double medB = b.namuDarbaiMed100 * 0.004 + b.egzaminas * 0.6;
                    return medA < medB;
                });
            break;

        default:
            std::cout << "Neteisingas pasirinkimas, nerikiuojama.\n";
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    char pasirinkimasOutput;
    std::cout << "Kur rodyti rezultatus? (1 - ekranas, 2 - failas): ";
    std::cin >> pasirinkimasOutput;
    std::cin.ignore();

    std::ostream* out = &std::cout;
    std::ofstream outFile;
    if (pasirinkimasOutput == '2') {
        std::string outputFileName;
        std::cout << "Iveskite failo pavadinima: ";
        std::getline(std::cin, outputFileName);

        outFile.open(outputFileName);
        if (!outFile) {
            std::cout << "Nepavyko sukurti failo.\n";
            delete[] studentai;
            return 1;
        }
        out = &outFile;
    }

    *out << std::left
         << std::setw(14) << "Vardas"
         << std::setw(17) << "Pavarde"
         << std::setw(17) << "Galutinis(Vid.)"
         << std::setw(17) << "Galutinis(Med.)"
         << "\n";

    *out << std::string(65, '-') << "\n";
    *out << std::fixed << std::setprecision(2);

    for (size_t i = 0; i < studentuKiekis; i++) {
        double vid = studentai[i].namuDarbaiVid100 * 0.004 + studentai[i].egzaminas * 0.6;
        double med = studentai[i].namuDarbaiMed100 * 0.004 + studentai[i].egzaminas * 0.6;

        *out << std::setw(14) << studentai[i].vardas
             << std::setw(17) << studentai[i].pavarde
             << std::setw(17) << vid
             << std::setw(17) << med << "\n";
    }

    if (studentuKiekis!=0) {
        double total = elapsed.count();
        double avg = total / studentuKiekis;

        std::cout << "\n--- Laiko matavimas ---\n";
        std::cout << "Bendras laikas: " << total << " s\n";
        std::cout << "Studentu kiekis: " << studentuKiekis << "\n";
        std::cout << "Vidutinis laikas/studentui: " << avg << " s\n";
    }

    delete[] studentai;
}
