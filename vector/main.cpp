#include <algorithm>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <vector>
#include <string>
#include <random>

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
    bool demo = false;

    std::cout <<"Ar cia yra demo? (y/n) default: n ";
    char isDemo[2];
    std::cin.getline(isDemo, 2);
    if (isDemo[0] == 'y' || isDemo[0] == 'Y') {
        demo = true;
    }

    while (true) {
        std::string stringTemp;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, 10);

        std::cout << "Norint baigti parasykite 'baigti'\nVardas: ";
        std::cin.getline(temp.vardas, 14);
        if (std::string(temp.vardas) == "baigti") break;

        std::cout << "Pavarde: ";
        std::cin.getline(temp.pavarde, 17);

        int suma = 0;
        int kiek = 0;
        std::vector<int> nd_pazymiai;

        if (!demo) {
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
            std::cout <<"Namu darbu pazymiu skaicius: ";
            std::string kiekNd;
            std::getline(std::cin, kiekNd);

            try {
                int kiekND = std::stoi(kiekNd);

                for (int i = 0; i < kiekND; i++) {
                    int paz = distrib(gen);
                    suma += paz;
                    nd_pazymiai.push_back(paz);
                    kiek++;
                }

                temp.egzaminas = static_cast<uint8_t>(distrib(gen));
            }
            catch (...) {
                std::cout <<"Ne skaicius!\n";
                continue;
            }
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
        
        if (!demo) {
            std::cout << "Egzamino pazymys: ";
            std::getline(std::cin, stringTemp);
            temp.egzaminas = static_cast<uint8_t>(std::stoi(stringTemp));
        }

        studentai.emplace_back(temp);
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
