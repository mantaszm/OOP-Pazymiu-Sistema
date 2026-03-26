#ifndef OOP_PAZYMIU_SISTEMA_FUNKCIJOS_H
#define OOP_PAZYMIU_SISTEMA_FUNKCIJOS_H

#include <algorithm>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <deque>
#include <chrono>
#include <string>
#include <random>
#include <cstring>
#include <sstream>

struct Studentas {
    uint16_t namuDarbaiVid100{};
    uint16_t namuDarbaiMed100{};
    uint8_t egzaminas{};
    char vardas[14]{};
    char pavarde[17]{};
    std::vector<short int> ND{};
};

double galutinisVid(const Studentas& s);

std::vector<Studentas> readFile(const std::string& filename, bool saveND = false);
std::vector<Studentas> readTerminal();
void generateFile(int kiekStud, int kiekND, std::string fileName);
void splitStudents(std::string dataFileName, std::string newFileName);
void testFileCreation(int kiekStud, int kiekND, const std::string& fileName);
void testDataProcessing(const std::string& fileName);
void testTime(int testSize, int ndSize);

// VECTOR strategijos
void splitVector1(const std::vector<Studentas>& studentai, std::vector<Studentas>& vargsiukai, std::vector<Studentas>& kietiakai);
void splitVector2(std::vector<Studentas>& studentai, std::vector<Studentas>& vargsiukai);
void splitVector3(std::vector<Studentas>& studentai, std::vector<Studentas>& vargsiukai);

// LIST strategijos
void splitList1(const std::list<Studentas>& studentai, std::list<Studentas>& vargsiukai, std::list<Studentas>& kietiakai);
void splitList2(std::list<Studentas>& studentai, std::list<Studentas>& vargsiukai);
void splitList3(std::list<Studentas>& studentai, std::list<Studentas>& vargsiukai);

// DEQUE strategijos
void splitDeque1(const std::deque<Studentas>& studentai, std::deque<Studentas>& vargsiukai, std::deque<Studentas>& kietiakai);
void splitDeque2(std::deque<Studentas>& studentai, std::deque<Studentas>& vargsiukai);
void splitDeque3(std::deque<Studentas>& studentai, std::deque<Studentas>& vargsiukai);

#endif
