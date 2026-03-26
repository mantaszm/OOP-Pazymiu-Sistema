#include "funkcijos.h"

int main() {
    std::vector<Studentas> studentai;

    std::cout << "Pasirinkite:\n";
    std::cout << "1 - mokiniu ivestis terminale\n";
    std::cout << "2 - mokiniu ivestis is failo\n";
    std::cout << "3 - generuoti faila\n";
    std::cout << "4 - padalinti mokinius i grupes is failo\n";
    std::cout << "5 - testuoti strategijas su vector\n";
    std::cout << "6 - testuoti strategijas su list\n";
    std::cout << "7 - testuoti strategijas su deque\n";
    std::cout << "8 - senas bendras laiko testas\n";

    char pasirinkimas;
    std::cin >> pasirinkimas;
    std::cin.ignore();

    if (pasirinkimas == '1') {
        studentai = readTerminal();
    }
    else if (pasirinkimas == '2') {
        std::string failas;
        std::cout << "Iveskite failo pavadinima: ";
        std::getline(std::cin, failas);

        studentai = readFile(failas);
    }
    else if (pasirinkimas == '3') {
        int kiekStud, kiekND;
        std::string fileName;

        std::cout << "Failo pavadinimas:\n";
        std::cin >> fileName;

        std::cout << "Kiek studentu faile:\n";
        std::cin >> kiekStud;

        std::cout << "Kiek namu darbu pazymiu:\n";
        std::cin >> kiekND;

        generateFile(kiekStud, kiekND, fileName);
        return 0;
    }
    else if (pasirinkimas == '4') {
        std::string dataFileName, newFileName;

        std::cout << "Mokiniu duomenu failo pavadinimas:\n";
        std::cin >> dataFileName;

        std::cout << "Padalintu mokiniu failo pavadinimas:\n";
        std::cin >> newFileName;

        splitStudents(dataFileName, newFileName);
        return 0;
    }
    else if (pasirinkimas == '5') {
        std::string failas;
        std::cout << "Iveskite failo pavadinima: ";
        std::getline(std::cin, failas);

        std::vector<Studentas> studentaiTest = readFile(failas);

        if (studentaiTest.empty()) {
            std::cout << "Nepavyko nuskaityti studentu.\n";
            return 0;
        }

        std::cout << "\nPasirinkite strategija:\n";
        std::cout << "1 - kurti du naujus konteinerius\n";
        std::cout << "2 - kurti tik vargsiukus ir trinti is bendro\n";
        std::cout << "3 - naudoti partition\n";

        char strategija;
        std::cin >> strategija;

        auto start = std::chrono::high_resolution_clock::now();

        if (strategija == '1') {
            std::vector<Studentas> vargsiukai;
            std::vector<Studentas> kietiakai;
            splitVector1(studentaiTest, vargsiukai, kietiakai);

            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = end - start;

            std::cout << "\nVECTOR 1 strategija baigta\n";
            std::cout << "Vargsiukai: " << vargsiukai.size() << "\n";
            std::cout << "Kietiakai: " << kietiakai.size() << "\n";
            std::cout << "Laikas: " << elapsed.count() << " s\n";
        }
        else if (strategija == '2') {
            std::vector<Studentas> vargsiukai;
            splitVector2(studentaiTest, vargsiukai);

            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = end - start;

            std::cout << "\nVECTOR 2 strategija baigta\n";
            std::cout << "Vargsiukai: " << vargsiukai.size() << "\n";
            std::cout << "Kietiakai: " << studentaiTest.size() << "\n";
            std::cout << "Laikas: " << elapsed.count() << " s\n";
        }
        else if (strategija == '3') {
            std::vector<Studentas> vargsiukai;
            splitVector3(studentaiTest, vargsiukai);

            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = end - start;

            std::cout << "\nVECTOR 3 strategija baigta\n";
            std::cout << "Vargsiukai: " << vargsiukai.size() << "\n";
            std::cout << "Kietiakai: " << studentaiTest.size() << "\n";
            std::cout << "Laikas: " << elapsed.count() << " s\n";
        }
        else {
            std::cout << "Netinkama strategija.\n";
        }

        return 0;
    }
    else if (pasirinkimas == '6') {
        std::string failas;
        std::cout << "Iveskite failo pavadinima: ";
        std::getline(std::cin, failas);

        std::vector<Studentas> temp = readFile(failas);
        if (temp.empty()) {
            std::cout << "Nepavyko nuskaityti studentu.\n";
            return 0;
        }

        std::list<Studentas> studentaiList;
        for (const auto& s : temp) {
            studentaiList.push_back(s);
        }

        std::cout << "\nPasirinkite strategija:\n";
        std::cout << "1 - kurti du naujus konteinerius\n";
        std::cout << "2 - kurti tik vargsiukus ir trinti is bendro\n";
        std::cout << "3 - naudoti splice\n";

        char strategija;
        std::cin >> strategija;

        auto start = std::chrono::high_resolution_clock::now();

        if (strategija == '1') {
            std::list<Studentas> vargsiukai;
            std::list<Studentas> kietiakai;
            splitList1(studentaiList, vargsiukai, kietiakai);

            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = end - start;

            std::cout << "\nLIST 1 strategija baigta\n";
            std::cout << "Vargsiukai: " << vargsiukai.size() << "\n";
            std::cout << "Kietiakai: " << kietiakai.size() << "\n";
            std::cout << "Laikas: " << elapsed.count() << " s\n";
        }
        else if (strategija == '2') {
            std::list<Studentas> vargsiukai;
            splitList2(studentaiList, vargsiukai);

            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = end - start;

            std::cout << "\nLIST 2 strategija baigta\n";
            std::cout << "Vargsiukai: " << vargsiukai.size() << "\n";
            std::cout << "Kietiakai: " << studentaiList.size() << "\n";
            std::cout << "Laikas: " << elapsed.count() << " s\n";
        }
        else if (strategija == '3') {
            std::list<Studentas> vargsiukai;
            splitList3(studentaiList, vargsiukai);

            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = end - start;

            std::cout << "\nLIST 3 strategija baigta\n";
            std::cout << "Vargsiukai: " << vargsiukai.size() << "\n";
            std::cout << "Kietiakai: " << studentaiList.size() << "\n";
            std::cout << "Laikas: " << elapsed.count() << " s\n";
        }
        else {
            std::cout << "Netinkama strategija.\n";
        }

        return 0;
    }
    else if (pasirinkimas == '7') {
        std::string failas;
        std::cout << "Iveskite failo pavadinima: ";
        std::getline(std::cin, failas);

        std::vector<Studentas> temp = readFile(failas);
        if (temp.empty()) {
            std::cout << "Nepavyko nuskaityti studentu.\n";
            return 0;
        }

        std::deque<Studentas> studentaiDeque;
        for (const auto& s : temp) {
            studentaiDeque.push_back(s);
        }

        std::cout << "\nPasirinkite strategija:\n";
        std::cout << "1 - kurti du naujus konteinerius\n";
        std::cout << "2 - kurti tik vargsiukus ir trinti is bendro\n";
        std::cout << "3 - naudoti partition\n";

        char strategija;
        std::cin >> strategija;

        auto start = std::chrono::high_resolution_clock::now();

        if (strategija == '1') {
            std::deque<Studentas> vargsiukai;
            std::deque<Studentas> kietiakai;
            splitDeque1(studentaiDeque, vargsiukai, kietiakai);

            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = end - start;

            std::cout << "\nDEQUE 1 strategija baigta\n";
            std::cout << "Vargsiukai: " << vargsiukai.size() << "\n";
            std::cout << "Kietiakai: " << kietiakai.size() << "\n";
            std::cout << "Laikas: " << elapsed.count() << " s\n";
        }
        else if (strategija == '2') {
            std::deque<Studentas> vargsiukai;
            splitDeque2(studentaiDeque, vargsiukai);

            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = end - start;

            std::cout << "\nDEQUE 2 strategija baigta\n";
            std::cout << "Vargsiukai: " << vargsiukai.size() << "\n";
            std::cout << "Kietiakai: " << studentaiDeque.size() << "\n";
            std::cout << "Laikas: " << elapsed.count() << " s\n";
        }
        else if (strategija == '3') {
            std::deque<Studentas> vargsiukai;
            splitDeque3(studentaiDeque, vargsiukai);

            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = end - start;

            std::cout << "\nDEQUE 3 strategija baigta\n";
            std::cout << "Vargsiukai: " << vargsiukai.size() << "\n";
            std::cout << "Kietiakai: " << studentaiDeque.size() << "\n";
            std::cout << "Laikas: " << elapsed.count() << " s\n";
        }
        else {
            std::cout << "Netinkama strategija.\n";
        }

        return 0;
    }
    else if (pasirinkimas == '8') {
        int testSize, ndSize;
        std::cout << "Iveskite studentu kieki: ";
        std::cin >> testSize;
        std::cout << "Iveskite ND kieki: ";
        std::cin >> ndSize;

        testTime(testSize, ndSize);
        return 0;
    }
    else {
        std::cout << "Netinkamas pasirinkimas\n";
        return 0;
    }

    std::cout << "\nRikiavimas:\n";
    std::cout << "1 - Vardas\n";
    std::cout << "2 - Pavarde\n";
    std::cout << "3 - Galutinis (Vid.)\n";
    std::cout << "4 - Galutinis (Med.)\n";

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
                    return galutinisVid(a) < galutinisVid(b);
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
        double vid = galutinisVid(i);
        double med = i.namuDarbaiMed100 * 0.004 + i.egzaminas * 0.6;

        *out << std::setw(14) << i.vardas
             << std::setw(17) << i.pavarde
             << std::setw(17) << vid
             << std::setw(17) << med << "\n";
    }

    if (!studentai.empty()) {
        double total = elapsed.count();
        double avg = total / static_cast<double>(studentai.size());

        std::cout << "\n--- Laiko matavimas ---\n";
        std::cout << "Bendras laikas: " << total << " s\n";
        std::cout << "Studentu kiekis: " << studentai.size() << "\n";
        std::cout << "Vidutinis laikas/studentui: " << avg << " s\n";
    }

    return 0;
}
