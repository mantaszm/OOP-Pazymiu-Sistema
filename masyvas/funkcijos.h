#ifndef OOP_PAZYMIU_SISTEMA_FUNKCIJOS_H
#define OOP_PAZYMIU_SISTEMA_FUNKCIJOS_H

#include <cstdint>
#include <string>
#include <algorithm>
#include <cstring>
#include <sstream>
#include <iostream>
#include <fstream>
#include <random>

struct Studentas{
    uint16_t namuDarbaiVid100{};
    uint16_t namuDarbaiMed100{};
    uint8_t egzaminas{};
    char vardas[14]{};
    char pavarde[17]{};
};

Studentas* readTerminal(size_t& studentuKiekis);
Studentas* readFile(const std::string& filename, size_t& studentuKiekis);

#endif
