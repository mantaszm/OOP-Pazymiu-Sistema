#include "funkcijos.h"

double galutinisVid(const Studentas& s) {
    return s.namuDarbaiVid100 * 0.004 + s.egzaminas * 0.6;
}

std::vector<Studentas> readFile(const std::string& filename, bool saveND) {
    std::ifstream in(filename);
    std::vector<Studentas> studentai;

    if (!in) {
        std::cout << "Nepavyko atidaryti failo\n";
        return studentai;
    }

    std::string line;
    std::getline(in, line);

    while (std::getline(in, line)) {
        std::stringstream ss(line);
        Studentas temp{};

        std::string vardas, pavarde;
        ss >> vardas >> pavarde;

        std::strncpy(temp.vardas, vardas.c_str(), sizeof(temp.vardas) - 1);
        temp.vardas[sizeof(temp.vardas) - 1] = '\0';

        std::strncpy(temp.pavarde, pavarde.c_str(), sizeof(temp.pavarde) - 1);
        temp.pavarde[sizeof(temp.pavarde) - 1] = '\0';

        std::vector<short int> nd;
        int x = 0;

        while (ss >> x) {
            nd.push_back(static_cast<short int>(x));
        }

        if (nd.empty()) continue;

        temp.egzaminas = static_cast<uint8_t>(nd.back());
        nd.pop_back();

        int suma = 0;
        for (short int v : nd) suma += v;

        if (saveND) temp.ND = nd;

        std::sort(nd.begin(), nd.end());

        std::size_t n = nd.size();
        double med = 0.0;

        if (n > 0) {
            if (n % 2 == 0) {
                med = (nd[n / 2 - 1] + nd[n / 2]) / 2.0;
            } else {
                med = nd[n / 2];
            }
        }

        temp.namuDarbaiVid100 = (n > 0)
            ? static_cast<uint16_t>((static_cast<double>(suma) / static_cast<double>(n)) * 100.0)
            : 0;

        temp.namuDarbaiMed100 = static_cast<uint16_t>(med * 100.0);

        studentai.push_back(temp);
    }

    return studentai;
}

std::vector<Studentas> readTerminal() {
    std::vector<Studentas> studentai;
    Studentas temp{};

    int mode = 0;
    int kiekND = 0;
    int mokiniai = 0;

    std::cout << "Rezimas:\n1 - rankinis\n2 - random pazymiai\n3 - random vardai ir pazymiai\n";
    char whatMode[2]{};
    std::cin.getline(whatMode, 2);

    switch (whatMode[0]) {
        case '1':
            mode = 1;
            break;

        case '2': {
            mode = 2;
            std::cout << "Namu darbu pazymiu skaicius: ";
            std::string ndSkaicius;
            std::getline(std::cin, ndSkaicius);
            try {
                kiekND = std::stoi(ndSkaicius);
            } catch (...) {
                std::cout << "Ne skaicius!\n";
                return {};
            }
            break;
        }

        case '3': {
            mode = 3;
            std::cout << "Namu darbu pazymiu skaicius:\n";
            try {
                std::cin >> kiekND;
                std::cout << "Mokiniu kiekis:\n";
                std::cin >> mokiniai;
                std::cin.ignore();
            } catch (...) {
                std::cout << "Ne skaicius!\n";
                return {};
            }
            break;
        }

        default:
            std::cout << "Netinkamas\n";
            return {};
    }

    while (!(mode == 3 && mokiniai == 0)) {
        temp = Studentas{};
        std::string stringTemp;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, 10);

        if (mode != 3) {
            std::cout << "Norint baigti parasykite 'baigti'\nVardas: ";
            std::cin.getline(temp.vardas, 14);
            if (std::string(temp.vardas) == "baigti") break;

            std::cout << "Pavarde: ";
            std::cin.getline(temp.pavarde, 17);
        } else {
            std::string vardai[11] = {
                "Jonas","Mantas","Lukas","Tomas","Dovydas",
                "Karolis","Rokas","Paulius","Andrius","Gabrielius","Dominykas"
            };
            std::string pavardes[11] = {
                "Kazlauskas","Jankauskas","Petrauskas","Balciunas","Zukauskas",
                "Vasiliauskas","Butkus","Navickas","Urbonas","Kavaliauskas","Stankevicius"
            };

            std::strncpy(temp.vardas, vardai[distrib(gen)].c_str(), sizeof(temp.vardas) - 1);
            temp.vardas[sizeof(temp.vardas) - 1] = '\0';

            std::strncpy(temp.pavarde, pavardes[distrib(gen)].c_str(), sizeof(temp.pavarde) - 1);
            temp.pavarde[sizeof(temp.pavarde) - 1] = '\0';
        }

        int suma = 0;
        int kiek = 0;
        std::vector<int> nd_pazymiai;

        if (mode == 1) {
            std::cout << "Iveskite namu darbu pazymius (atskirtus tarpais): ";
            std::getline(std::cin, stringTemp);

            std::stringstream ss(stringTemp);
            int paz = 0;

            while (ss >> paz) {
                if (paz < 0 || paz > 10) {
                    std::cout << "Netinkamas pazymys (0-10). Ignoruojamas.\n";
                    continue;
                }
                suma += paz;
                nd_pazymiai.push_back(paz);
                kiek++;
            }
        } else {
            for (int i = 0; i < kiekND; i++) {
                int paz = distrib(gen);
                suma += paz;
                nd_pazymiai.push_back(paz);
                kiek++;
            }

            temp.egzaminas = static_cast<uint8_t>(distrib(gen));
        }

        std::sort(nd_pazymiai.begin(), nd_pazymiai.end());

        double nd_med = 0.0;

        if (kiek > 0) {
            if (kiek % 2 == 0) {
                nd_med = (nd_pazymiai[kiek / 2 - 1] + nd_pazymiai[kiek / 2]) / 2.0;
            } else {
                nd_med = nd_pazymiai[kiek / 2];
            }
        }

        temp.namuDarbaiMed100 = static_cast<uint16_t>(nd_med * 100.0);

        if (kiek > 0)
            temp.namuDarbaiVid100 =
                static_cast<uint16_t>((static_cast<double>(suma) / static_cast<double>(kiek)) * 100.0);
        else
            temp.namuDarbaiVid100 = 0;

        if (mode == 1) {
            std::cout << "Egzamino pazymys: ";
            std::getline(std::cin, stringTemp);
            temp.egzaminas = static_cast<uint8_t>(std::stoi(stringTemp));
        }

        studentai.push_back(temp);
        mokiniai--;
    }

    return studentai;
}

void generateFile(int kiekStud, int kiekND, std::string fileName) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 10);

    std::ofstream outFile(fileName);
    if (!outFile) {
        std::cout << "Nepavyko sukurti failo.\n";
        return;
    }

    outFile << std::left
            << std::setw(14) << "Vardas"
            << std::setw(17) << "Pavarde";

    for (int i = 1; i <= kiekND; i++) {
        outFile << std::setw(10) << ("ND" + std::to_string(i));
    }
    outFile << std::setw(10) << "Egz." << "\n";

    for (int i = 1; i <= kiekStud; i++) {
        outFile << std::left
                << std::setw(14) << ("Vardas" + std::to_string(i))
                << std::setw(17) << ("Pavarde" + std::to_string(i));

        for (int j = 0; j <= kiekND; j++) {
            outFile << std::setw(10) << distrib(gen);
        }
        outFile << "\n";
    }
}

void splitStudents(std::string dataFileName, std::string newFileName) {
    std::vector<Studentas> mokiniai = readFile(dataFileName, true);

    std::ofstream outGood("good_" + newFileName);
    std::ofstream outBad("bad_" + newFileName);

    if (!outGood || !outBad) {
        std::cout << "Nepavyko sukurti failo.\n";
        return;
    }

    if (mokiniai.empty()) return;

    int kiekND = static_cast<int>(mokiniai[0].ND.size());

    auto printHeader = [&](std::ostream& out) {
        out << std::left
            << std::setw(14) << "Vardas"
            << std::setw(17) << "Pavarde";

        for (int i = 1; i <= kiekND; i++)
            out << std::setw(10) << ("ND" + std::to_string(i));

        out << std::setw(10) << "Egz." << "\n";
    };

    printHeader(outGood);
    printHeader(outBad);

    for (const auto& s : mokiniai) {
        std::ostream& out = (galutinisVid(s) >= 5.0) ? outGood : outBad;

        out << std::left
            << std::setw(14) << s.vardas
            << std::setw(17) << s.pavarde;

        for (short int nd : s.ND)
            out << std::setw(10) << nd;

        out << std::setw(10) << static_cast<int>(s.egzaminas) << "\n";
    }
}

void testFileCreation(int kiekStud, int kiekND, const std::string& fileName) {
    auto start = std::chrono::high_resolution_clock::now();
    generateFile(kiekStud, kiekND, fileName);
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "Failo sukurimo laikas: "
              << std::chrono::duration<double>(end - start).count() << " s\n";
}

void testDataProcessing(const std::string& fileName) {
    auto t0 = std::chrono::high_resolution_clock::now();
    std::vector<Studentas> students = readFile(fileName, true);
    auto t1 = std::chrono::high_resolution_clock::now();

    std::vector<Studentas> good, bad;
    for (const auto& s : students) {
        if (galutinisVid(s) >= 5.0) good.push_back(s);
        else bad.push_back(s);
    }
    auto t2 = std::chrono::high_resolution_clock::now();

    std::cout << "Failo nuskaitymo laikas: "
              << std::chrono::duration<double>(t1 - t0).count() << " s\n";
    std::cout << "Studentu skirstymo laikas: "
              << std::chrono::duration<double>(t2 - t1).count() << " s\n";
    std::cout << "Bendras laikas: "
              << std::chrono::duration<double>(t2 - t0).count() << " s\n";
}

void testTime(int testSize, int ndSize) {
    std::cout << "Dydis: " << testSize << "\n";
    testFileCreation(testSize, ndSize, "students.txt");
    testDataProcessing("students.txt");
}

void splitVector1(const std::vector<Studentas>& studentai, std::vector<Studentas>& vargsiukai, std::vector<Studentas>& kietiakai) {
    for (const auto& s : studentai) {
        if (galutinisVid(s) < 5.0) vargsiukai.push_back(s);
        else kietiakai.push_back(s);
    }
}

void splitVector2(std::vector<Studentas>& studentai, std::vector<Studentas>& vargsiukai) {
    for (auto it = studentai.begin(); it != studentai.end(); ) {
        if (galutinisVid(*it) < 5.0) {
            vargsiukai.push_back(*it);
            it = studentai.erase(it);
        } else {
            ++it;
        }
    }
}

void splitVector3(std::vector<Studentas>& studentai, std::vector<Studentas>& vargsiukai) {
    auto it = std::partition(studentai.begin(), studentai.end(),
        [](const Studentas& s) {
            return galutinisVid(s) >= 5.0;
        });

    for (auto i = it; i != studentai.end(); ++i) {
        vargsiukai.push_back(*i);
    }

    studentai.erase(it, studentai.end());
}

void splitList1(const std::list<Studentas>& studentai, std::list<Studentas>& vargsiukai, std::list<Studentas>& kietiakai) {
    for (const auto& s : studentai) {
        if (galutinisVid(s) < 5.0) vargsiukai.push_back(s);
        else kietiakai.push_back(s);
    }
}

void splitList2(std::list<Studentas>& studentai, std::list<Studentas>& vargsiukai) {
    for (auto it = studentai.begin(); it != studentai.end(); ) {
        if (galutinisVid(*it) < 5.0) {
            vargsiukai.push_back(*it);
            it = studentai.erase(it);
        } else {
            ++it;
        }
    }
}

void splitList3(std::list<Studentas>& studentai, std::list<Studentas>& vargsiukai) {
    for (auto it = studentai.begin(); it != studentai.end(); ) {
        if (galutinisVid(*it) < 5.0) {
            auto temp = it++;
            vargsiukai.splice(vargsiukai.end(), studentai, temp);
        } else {
            ++it;
        }
    }
}

void splitDeque1(const std::deque<Studentas>& studentai, std::deque<Studentas>& vargsiukai, std::deque<Studentas>& kietiakai) {
    for (const auto& s : studentai) {
        if (galutinisVid(s) < 5.0) vargsiukai.push_back(s);
        else kietiakai.push_back(s);
    }
}

void splitDeque2(std::deque<Studentas>& studentai, std::deque<Studentas>& vargsiukai) {
    for (auto it = studentai.begin(); it != studentai.end(); ) {
        if (galutinisVid(*it) < 5.0) {
            vargsiukai.push_back(*it);
            it = studentai.erase(it);
        } else {
            ++it;
        }
    }
}

void splitDeque3(std::deque<Studentas>& studentai, std::deque<Studentas>& vargsiukai) {
    auto it = std::partition(studentai.begin(), studentai.end(),
        [](const Studentas& s) {
            return galutinisVid(s) >= 5.0;
        });

    for (auto i = it; i != studentai.end(); ++i) {
        vargsiukai.push_back(*i);
    }

    studentai.erase(it, studentai.end());
}
