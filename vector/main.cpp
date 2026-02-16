#include <algorithm>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <vector>
#include <string>

struct Studentas{
    uint16_t namuDarbaiVid100{}; // vidurkis * 100
    uint16_t namuDarbaiMed100{};
    uint8_t egzaminas{};
    char vardas[14]{};
    char pavarde[17]{};
};

int main() {
    std::vector<Studentas> studentai;
    Studentas temp;

    while (true) {
        std::string stringTemp;
        
        std::cout << "Norint baigti parasykite 'baigti'\nVardas: ";
        std::cin.getline(temp.vardas, 14);
        if (std::string(temp.vardas) == "baigti") break;

        std::cout << "Pavarde: ";
        std::cin.getline(temp.pavarde, 17);

        int suma = 0;
        int kiek = 0;
        std::vector<int> nd_pazymiai;

        std::cout << "Iveskite namu darbu pazymius (rasykite 'baigti' kai baigsite):\n";

        while (true) {
            std::cout << "Pazymys: ";
            std::getline(std::cin, stringTemp);
            if (stringTemp == "baigti") break;

            try {
                int paz = std::stoi(stringTemp);

                if (paz < 0 || paz > 10) {
                    std::cout << "Netinkamas pazymys (0-10), baigiame ivedima.\n";
                    break;
                }

                suma += paz;
                nd_pazymiai.push_back(paz);
                kiek++;
            }
            catch (...) {
                std::cout << "Netinkama ivestis, baigiame ivedima.\n";
                break;
            }
        }

        if (kiek > 0)
            temp.namuDarbaiVid100 =
                static_cast<uint16_t>((static_cast<double>(suma) / kiek) * 100);
        else
            temp.namuDarbaiVid100 = 0;

        std::cout << "Egzamino pazymys: ";
        std::getline(std::cin, stringTemp);
        temp.egzaminas = static_cast<uint8_t>(std::stoi(stringTemp));

        studentai.emplace_back(temp);
    }

    std::cout << std::left
              << std::setw(14) << "Vardas"
              << std::setw(17) << "Pavarde"
              << std::setw(17) << "Galutinis(Vid.)"
              << "\n";

    std::cout << std::string(48, '-') << "\n";
    std::cout << std::fixed << std::setprecision(2);

    for (const auto& i : studentai) {
        const double galutinisVid =
            i.namuDarbaiVid100 * 0.004 + i.egzaminas * 0.6;

        std::cout << std::left
                  << std::setw(14) << i.vardas
                  << std::setw(17) << i.pavarde
                  << std::setw(17) << galutinisVid
                  << "\n";
    }

    return 0;
}
