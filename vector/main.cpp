#include "funkcijos.h"

int main() {
    std::vector<Studentas> studentai;

    std::cout << "Pasirinkite:\n1 - mokiniu ivestis terminale\n2 - mokiniu ivestis is failo\n3 - generuoti faila\n4 - padalinti mokinius i grupes is failo\n";
    char pasirinkimas;
    std::cin >> pasirinkimas;
    std::cin.ignore();

    if (pasirinkimas == '1') {
        studentai = readTerminal();
    } else if (pasirinkimas == '2') {
        std::string failas;
        std::cout << "Iveskite failo pavadinima: ";
        std::getline(std::cin, failas);

        studentai = readFile(failas);
    } else if(pasirinkimas == '3'){
        int kiekStud, kiekND; 
        std::string fileName;

        std::cout <<"Failo pavadinimas:\n";
        std::cin >>fileName;

        std::cout <<"Kiek studentu faile:\n";
        std::cin >> kiekStud;

        std::cout <<"Kiek namu darbu pazymiu:\n";
        std::cin >> kiekND;

        generateFile(kiekStud, kiekND, fileName);
        return 0;
        
    } else if(pasirinkimas == '4'){
        std::string dataFileName, newFileName;

        std::cout << "Mokiniu duomenu failo pavadinimas:\n";
        std::cin >> dataFileName;

        std::cout << "Padalintu mokiniu failo pavadinimas:\n";
        std::cin >> newFileName;

        splitStudents(dataFileName, newFileName);
        return 0;
        
    } else {
        std::cout << "Netinkamas pasirinkimas\n";
        return 0;
    }


    std::cout << "\nRikiavimas:\n1 - Vardas\n2 - Pavarde\n3 - Galutinis (Vid.)\n4 - Galutinis (Med.)\n";
    char rikiavimas;
    std::cin >> rikiavimas;

    auto start = std::chrono::high_resolution_clock::now();
    switch (rikiavimas) {
        case '1':
            std::sort(studentai.begin(), studentai.end(),
                [](const Studentas& a, const Studentas& b) {
                    return std::strcmp(a.vardas, b.vardas) < 0;
                });
            break;
        case '2':
            std::sort(studentai.begin(), studentai.end(),
                [](const Studentas& a, const Studentas& b) {
                    return std::strcmp(a.pavarde, b.pavarde) < 0;
                });
            break;
        case '3':
            std::sort(studentai.begin(), studentai.end(),
                [](const Studentas& a, const Studentas& b) {
                    double vidA = a.namuDarbaiVid100 * 0.004 + a.egzaminas * 0.6;
                    double vidB = b.namuDarbaiVid100 * 0.004 + b.egzaminas * 0.6;
                    return vidA < vidB;
                });
            break;
        case '4':
            std::sort(studentai.begin(), studentai.end(),
                [](const Studentas& a, const Studentas& b) {
                    double medA = a.namuDarbaiMed100 * 0.004 + a.egzaminas * 0.6;
                    double medB = b.namuDarbaiMed100 * 0.004 + b.egzaminas * 0.6;
                    return medA < medB;
                });
            break;
        default:
            std::cout << "Neteisingas pasirinkimas, nerikiuojama.\n";
            break;
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    // Pasirinkimas output
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

    for (const auto& i : studentai) {
        double vid = i.namuDarbaiVid100 * 0.004 + i.egzaminas * 0.6;
        double med = i.namuDarbaiMed100 * 0.004 + i.egzaminas * 0.6;

        *out << std::setw(14) << i.vardas
             << std::setw(17) << i.pavarde
             << std::setw(17) << vid
             << std::setw(17) << med << "\n";
    }

    if (!studentai.empty()) {
        double total = elapsed.count();
        double avg = total / studentai.size();

        std::cout << "\n--- Laiko matavimas ---\n";
        std::cout << "Bendras laikas: " << total << " s\n";
        std::cout << "Studentu kiekis: " << studentai.size() << "\n";
        std::cout << "Vidutinis laikas/studentui: " << avg << " s\n";
    }

    return 0;
}
