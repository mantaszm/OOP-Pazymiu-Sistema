#include <algorithm>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <string>
#include <random>
#include <cstring>
#include <fstream>
#include <sstream>

struct Studentas{
    uint16_t namuDarbaiVid100{};
    uint16_t namuDarbaiMed100{};
    uint8_t egzaminas{};
    char vardas[14]{};
    char pavarde[17]{};
};

Studentas* readFile(const std::string& filename, size_t& studentuKiekis) {
    std::ifstream in(filename);
    if (!in) {
        std::cout << "Nepavyko atidaryti failo\n";
        return nullptr;
    }

    Studentas* studentai = nullptr;
    size_t talpaStudentams = 0;   // renamed to avoid shadowing
    studentuKiekis = 0;

    std::string line;
    std::getline(in, line); // skip header

    while (std::getline(in, line)) {
        std::stringstream ss(line);
        Studentas temp;

        std::string vardas, pavarde;
        ss >> vardas >> pavarde;

        std::strcpy(temp.vardas, vardas.c_str());
        std::strcpy(temp.pavarde, pavarde.c_str());

        int* nd = nullptr;
        size_t kiek = 0;
        size_t talpaND = 0;
        int suma = 0;
        int paz;

        // read grades
        while (ss >> paz) {
            if (kiek == talpaND) {
                talpaND = (talpaND == 0) ? 1 : talpaND * 2;
                int* naujas = new int[talpaND];

                for (size_t i = 0; i < kiek; i++)
                    naujas[i] = nd[i];

                delete[] nd;
                nd = naujas;
            }

            nd[kiek++] = paz;
        }

        if (kiek < 1) {
            delete[] nd;
            continue;
        }

        temp.egzaminas = nd[kiek - 1];
        kiek--;

        for (size_t i = 0; i < kiek; i++)
            suma += nd[i];

        std::sort(nd, nd + kiek);

        double med = 0.0;
        if (kiek > 0) {
            if (kiek % 2 == 0)
                med = (nd[kiek/2 - 1] + nd[kiek/2]) / 2.0;
            else
                med = nd[kiek/2];
        }

        temp.namuDarbaiVid100 =
            (kiek > 0) ? (uint16_t)((double)suma / kiek * 100) : 0;

        temp.namuDarbaiMed100 = (uint16_t)(med * 100);

        // resize student array
        if (studentuKiekis == talpaStudentams) {
            talpaStudentams = (talpaStudentams == 0) ? 1 : talpaStudentams * 2;
            Studentas* naujas = new Studentas[talpaStudentams];

            for (size_t i = 0; i < studentuKiekis; i++)
                naujas[i] = studentai[i];

            delete[] studentai;
            studentai = naujas;
        }

        studentai[studentuKiekis++] = temp;

        delete[] nd; // 🔥 IMPORTANT: prevent memory leak
    }

    return studentai;
}

Studentas* readTerminal(size_t& studentuKiekis) {
    Studentas* studentai = nullptr;
    size_t talpa = 0;
    int kiekND = 0;
    int mokiniai = 0;

    Studentas temp;
    int mode = 0;

    std::cout <<"Rezimas:\n1 - rankinis\n2 - random pazymiai\n3 - random vardai ir pazymiai\n";
    char whatMode[2]{};
    std::cin.getline(whatMode, 2);
    switch (whatMode[0]) {
        case '1':
            mode = 1;
            break;

        case '2': {
            mode = 2;
            std::cout <<"Namu darbu pazymiu skaicius: ";
            std::string ndSkaicius;
            std::getline(std::cin, ndSkaicius);
            try {
                kiekND = std::stoi(ndSkaicius);
            }
            catch (...) {
                std::cout <<"Ne skaicius!";
                return nullptr;
            }
            break;
        }

        case '3': {
            mode = 3;
            std::cout <<"Namu darbu pazymiu skaicius:\n";
            try {
                std::cin >> kiekND;
                std::cout <<"Mokiniu kiekis:\n";
                std::cin >> mokiniai;
            }
            catch (...) {
                std::cout <<"Ne skaicius!";
                return nullptr;
            }
            break;
        }

        default:
            std::cout <<"Netinkamas";
            return nullptr;
    }

    while (!(mode == 3 and mokiniai == 0)) {
        std::string stringTemp;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, 10);

        if (mode != 3){
            std::cout << "Norint baigti parasykite 'baigti'\nVardas: ";
            std::cin.getline(temp.vardas, 14);
            if (std::string(temp.vardas) == "baigti") break;

            std::cout << "Pavarde: ";
            std::cin.getline(temp.pavarde, 17);
        }
        else {
            std::string vardas[11] = {
                "Jonas",
                "Mantas",
                "Lukas",
                "Tomas",
                "Dovydas",
                "Karolis",
                "Rokas",
                "Paulius",
                "Andrius",
                "Gabrielius",
                "Dominykas"
            };
            std::string pavarde[11] = {
                "Kazlauskas",
                "Jankauskas",
                "Petrauskas",
                "Balciunas",
                "Zukauskas",
                "Vasiliauskas",
                "Butkus",
                "Navickas",
                "Urbonas",
                "Kavaliauskas",
                "Stankevicius"
            };
            std::strcpy(temp.vardas, vardas[distrib(gen)].c_str());
            std::strcpy(temp.pavarde, pavarde[distrib(gen)].c_str());
        }

        int suma = 0;
        int kiek = 0;

        int* nd_pazymiai = nullptr;
        size_t nd_kiekis = 0;
        size_t nd_talpa = 0;

        if (mode == 1) {
            std::cout << "Iveskite namu darbu pazymius (atskirtus tarpais): ";
            std::getline(std::cin, stringTemp);

            size_t pos = 0;

            while (pos < stringTemp.size()) {

                while (pos < stringTemp.size() && stringTemp[pos] == ' ')
                    pos++;

                if (pos >= stringTemp.size()) break;

                size_t next = stringTemp.find(' ', pos);//tokeno pabaiga
                std::string token;

                if (next == std::string::npos) {//paskutinis nes neranda
                    token = stringTemp.substr(pos);
                    pos = stringTemp.size();
                } else {//rado kita zodi
                    token = stringTemp.substr(pos, next - pos);
                    pos = next + 1;
                }

                try {
                    int paz = std::stoi(token);

                    if (paz < 0 || paz > 10) {
                        std::cout << "Netinkamas pazymys (0-10). Ignoruojamas.\n";
                        continue;
                    }

                    if (nd_kiekis == nd_talpa) {
                        nd_talpa = (nd_talpa == 0) ? 1 : nd_talpa * 2;
                        int* naujas = new int[nd_talpa];
                        for (size_t i = 0; i < nd_kiekis; i++)
                            naujas[i] = nd_pazymiai[i];
                        delete[] nd_pazymiai;
                        nd_pazymiai = naujas;
                    }

                    nd_pazymiai[nd_kiekis++] = paz;
                    suma += paz;
                    kiek++;

                } catch (...) {
                    std::cout << "Netinkama ivestis: " << token << " (ignoruojama)\n";
                }
            }
        }
        else {
            try {
                for (int i = 0; i < kiekND; i++) {
                    int paz = distrib(gen);

                    if (nd_kiekis == nd_talpa) {
                        nd_talpa = (nd_talpa == 0) ? 1 : nd_talpa * 2;
                        int* naujas = new int[nd_talpa];
                        for (size_t j = 0; j < nd_kiekis; j++)
                            naujas[j] = nd_pazymiai[j];
                        delete[] nd_pazymiai;
                        nd_pazymiai = naujas;
                    }

                    nd_pazymiai[nd_kiekis++] = paz;
                    suma += paz;
                    kiek++;
                }

            } catch (...) {
                std::cout << "Netinkamas skaicius.\n";
                delete[] nd_pazymiai;
                continue;
            }
            temp.egzaminas = distrib(gen);
        }

        std::sort(nd_pazymiai, nd_pazymiai + nd_kiekis);

        double nd_med = 0.0;

        if (kiek > 0) {
            if (kiek % 2 == 0)
                nd_med = (nd_pazymiai[kiek/2 - 1] + nd_pazymiai[kiek/2]) / 2.0;
            else
                nd_med = nd_pazymiai[kiek/2];
        }

        temp.namuDarbaiMed100 = static_cast<uint16_t>(nd_med * 100);

        if (kiek > 0)
            temp.namuDarbaiVid100 =
                static_cast<uint16_t>((static_cast<double>(suma) / kiek) * 100);
        else
            temp.namuDarbaiVid100 = 0;

        if (mode == 1) {
            std::cout << "Egzamino pazymys: ";
            std::getline(std::cin, stringTemp);
            temp.egzaminas = static_cast<uint8_t>(std::stoi(stringTemp));
        }

        delete[] nd_pazymiai;

        if (studentuKiekis == talpa) {
            talpa = (talpa == 0) ? 1 : talpa * 2;
            Studentas* naujas = new Studentas[talpa];

            for (size_t i = 0; i < studentuKiekis; i++)
                naujas[i] = studentai[i];

            delete[] studentai;
            studentai = naujas;
        }

        studentai[studentuKiekis++] = temp;
        mokiniai--;
    }

    return studentai;
}

int main() {
    size_t studentuKiekis = 0;
    Studentas* studentai = nullptr;

    std::cout << "Pasirinkite ivesti:\n1 - terminalas\n2 - failas\n";
    char pasirinkimas;
    std::cin >> pasirinkimas;
    std::cin.ignore();

    if (pasirinkimas == '1') {
        studentai = readTerminal(studentuKiekis);
    }
    else if (pasirinkimas == '2') {
        std::string failas;
        std::cout << "Iveskite failo pavadinima: ";
        std::getline(std::cin, failas);

        studentai = readFile(failas, studentuKiekis);
    }
    else {
        std::cout << "Blogas pasirinkimas\n";
        return 0;
    }

    std::cout << "\nRikiavimas:\n";
    std::cout << "1 - Vardas\n";
    std::cout << "2 - Pavarde\n";
    std::cout << "3 - Galutinis (Vid.)\n";
    std::cout << "4 - Galutinis (Med.)\n";

    char rikiavimas;
    std::cin >> rikiavimas;

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

    std::cout << std::left
              << std::setw(14) << "Vardas"
              << std::setw(17) << "Pavarde"
              << std::setw(17) << "Galutinis(Vid.)"
              << std::setw(17) << "Galutinis(Med.)"
              << "\n";

    std::cout << std::string(65, '-') << "\n";
    std::cout << std::fixed << std::setprecision(2);

    for (size_t i = 0; i < studentuKiekis; i++) {
        double vid = studentai[i].namuDarbaiVid100 * 0.004 + studentai[i].egzaminas * 0.6;
        double med = studentai[i].namuDarbaiMed100 * 0.004 + studentai[i].egzaminas * 0.6;

        std::cout << std::setw(14) << studentai[i].vardas
                  << std::setw(17) << studentai[i].pavarde
                  << std::setw(17) << vid
                  << std::setw(17) << med << "\n";
    }

    delete[] studentai;
}
