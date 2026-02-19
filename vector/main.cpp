#include <algorithm>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <cstring>

struct Studentas{
    uint16_t namuDarbaiVid100{};
    uint16_t namuDarbaiMed100{};
    uint8_t egzaminas{};
    char vardas[14]{};
    char pavarde[17]{};
};

int main() {
    std::vector<Studentas> studentai;
    Studentas temp;

    int mode = 0;
    int kiekND = 0;
    int mokiniai = 0;

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
                return 0;
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
                std::cin.ignore();
            }
            catch (...) {
                std::cout <<"Ne skaicius!";
                return 0;
            }
            break;
        }

        default:
            std::cout <<"Netinkamas";
            return 0;
    }

    while (!(mode == 3 && mokiniai == 0)) {
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
                "Jonas","Mantas","Lukas","Tomas","Dovydas",
                "Karolis","Rokas","Paulius","Andrius","Gabrielius","Dominykas"
            };
            std::string pavarde[11] = {
                "Kazlauskas","Jankauskas","Petrauskas","Balciunas","Zukauskas",
                "Vasiliauskas","Butkus","Navickas","Urbonas","Kavaliauskas","Stankevicius"
            };
            std::strcpy(temp.vardas, vardas[distrib(gen)].c_str());
            std::strcpy(temp.pavarde, pavarde[distrib(gen)].c_str());
        }

        int suma = 0;
        int kiek = 0;
        std::vector<int> nd_pazymiai;

        if (mode == 1) {
            std::cout << "Iveskite namu darbu pazymius (atskirtus tarpais): ";
            std::getline(std::cin, stringTemp);

            size_t pos = 0;

            while (pos < stringTemp.size()) {
                while (pos < stringTemp.size() && stringTemp[pos] == ' ')
                    pos++;

                if (pos >= stringTemp.size()) break;

                size_t next = stringTemp.find(' ', pos);
                std::string token;

                if (next == std::string::npos) {
                    token = stringTemp.substr(pos);
                    pos = stringTemp.size();
                } else {
                    token = stringTemp.substr(pos, next - pos);
                    pos = next + 1;
                }

                try {
                    int paz = std::stoi(token);

                    if (paz < 0 || paz > 10) {
                        std::cout << "Netinkamas pazymys (0-10). Ignoruojamas.\n";
                        continue;
                    }

                    suma += paz;
                    nd_pazymiai.push_back(paz);
                    kiek++;
                }
                catch (...) {
                    std::cout << "Netinkama ivestis: " << token << " (ignoruojama)\n";
                }
            }
        }
        else {
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

        if (kiek == 0) {
            nd_med = 0.0;
        }
        else if (kiek % 2 == 0) {
            nd_med = (nd_pazymiai[kiek/2 - 1] + nd_pazymiai[kiek/2]) / 2.0;
        }
        else {
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

        studentai.emplace_back(temp);
        mokiniai--;
    }

    std::cout << std::left
              << std::setw(14) << "Vardas"
              << std::setw(17) << "Pavarde"
              << std::setw(17) << "Galutinis(Vid.)"
              << std::setw(17) << "Galutinis(Med.)"
              << "\n";

    std::cout << std::string(65, '-') << "\n";
    std::cout << std::fixed << std::setprecision(2);

    for (const auto& i : studentai) {
        const double galutinisVid =
            i.namuDarbaiVid100 * 0.004 + i.egzaminas * 0.6;
        const double galutinisMed =
            i.namuDarbaiMed100 * 0.004 + i.egzaminas * 0.6;

        std::cout << std::left
                  << std::setw(14) << i.vardas
                  << std::setw(17) << i.pavarde
                  << std::setw(17) << galutinisVid
                  << std::setw(17) << galutinisMed
                  << "\n";
    }

    return 0;
}
