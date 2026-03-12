#ifndef OOP_PAZYMIU_SISTEMA_FUNKCIJOS_H
#define OOP_PAZYMIU_SISTEMA_FUNKCIJOS_H

#include <algorithm>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <string>
#include <random>
#include <cstring>


struct Studentas{
    uint16_t namuDarbaiVid100{};
    uint16_t namuDarbaiMed100{};
    uint8_t egzaminas{};
    char vardas[14]{};
    char pavarde[17]{};
    std::vector<short int> ND{}; 
};

std::vector<Studentas> readFile(const std::string& filename, bool saveND=false);
std::vector<Studentas> readTerminal();
void generateFile(int kiekStud, int kiekND, std::string fileName);
void splitStudents(std::string dataFileName, std::string newFileName);

#endif
