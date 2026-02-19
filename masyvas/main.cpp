#include <algorithm>
#include <cstdint>
#include <iomanip>
#include <iostream>
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
    Studentas* studentai = nullptr;
    size_t studentuKiekis = 0;
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

    std::cout << std::left
              << std::setw(14) << "Vardas"
              << std::setw(17) << "Pavarde"
              << std::setw(17) << "Galutinis(Vid.)"
              << std::setw(17) << "Galutinis(Med.)"
              << "\n";

    std::cout << std::string(65, '-') << "\n";
    std::cout << std::fixed << std::setprecision(2);

    for (size_t idx = 0; idx < studentuKiekis; idx++) {
        const Studentas& i = studentai[idx];

        double galutinisVid =
            i.namuDarbaiVid100 * 0.004 + i.egzaminas * 0.6;
        double galutinisMed =
            i.namuDarbaiMed100 * 0.004 + i.egzaminas * 0.6;

        std::cout << std::left
                  << std::setw(14) << i.vardas
                  << std::setw(17) << i.pavarde
                  << std::setw(17) << galutinisVid
                  << std::setw(17) << galutinisMed
                  << "\n";
    }

    delete[] studentai;
    return 0;
}
