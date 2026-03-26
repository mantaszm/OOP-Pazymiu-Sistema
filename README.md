# Studentų pažymių programa

Programa leidžia:

- Įvesti studentų vardus, pavardes ir namų darbų bei egzamino pažymius.
- Apskaičiuoti galutinius pažymius pagal **vidurkį** arba **medianą**.
- Generuoti atsitiktinius vardus ir/ar pažymius pasirinkus tam tikrą režimą.

# Studentų duomenų tvarkymo programa – spartos analizė

## Tyrimo tikslas
Išmatuoti programos veikimo laiką generuojant failus ir apdorojant studentų duomenis skirtingam studentų kiekiui.

## Testavimo metodika
- 1 tyrimas: failų kūrimas (tik generuojami duomenys į failą)
- 2 tyrimas: duomenų apdorojimas (skaitymas, rūšiavimas į dvi grupes, išvedimas į du failus)
- Kiekvienam testui naudojamas skirtingas studentų skaičius: 10 000, 100 000, 1 000 000, 10 000 000
- ND kiekis: 15
- Laiką matuojame su `std::chrono::high_resolution_clock`

---

# Paleidimas

## Su `make`

```bash
make
./programa
```

---

## 1 Tyrimas – Failo kūrimas

| Studentų skaičius | Failo sukurimo laikas (s) |
| ----------------- | ------------------------- |
| 10 000            | 0.023767                  |
| 100 000           | 0.211366                  |
| 1 000 000         | 2.21408                   |
| 10 000 000        | 31.6162                   |


> Laikas rodo tik failo generavimą ir įrašymą į diską, be jokio vektorių saugojimo.

---

## 2 Tyrimas – Duomenų apdorojimas

| Studentų skaičius | Failo nuskaitymas (s) | Studentų rūšiavimas (s) | Išvedimas į failus (s) | Bendras procesas (s) |
| ----------------- | --------------------- | ----------------------- | ---------------------- | -------------------- |
| 10 000            | 0.045242              | 0.001876                | 0.015258               | 0.062376             |
| 100 000           | 0.346277              | 0.014624                | 0.133467               | 0.494368             |
| 1 000 000         | 3.38057               | 0.137919                | 1.49002                | 5.00851              |
| 10 000 000        | 58.3972               | 1.72662                 | 12.7086                | 72.8324              |


> Laikas rodo failo skaitymą, studentų rūšiavimą į "good" / "bad" grupes, bei išvedimą į failus `good_students.txt` ir `bad_students.txt`.

---

## Pastebėjimai
- Laikas **proporcingai didėja su studentų skaičiumi**, bet rūšiavimo dalis yra labai greita, nes naudojamas paprastas vektorius.
- Generavimas ir išvedimas į failus užima didžiausią dalį laiko.
- Rezultatai gali skirtis priklausomai nuo disko spartos ir kompiuterio specifikacijos.

---

<img width="800" height="500" alt="plot" src="https://github.com/user-attachments/assets/d03636cf-086c-4895-ae7d-e7a18e3fa4f5" />

# Studentų duomenų apdorojimo programa v1.0

## Programos aprašymas

Programa skirta studentų duomenų nuskaitymui, galutinio balo skaičiavimui, rūšiavimui ir skirstymui į dvi kategorijas:
- **vargšiukai**
- **kietiakai**

Versijoje **v1.0** atliktas skirtingų STL konteinerių ir skirstymo strategijų efektyvumo tyrimas.

---

## Naudoti konteineriai

Tyrime analizuoti šie konteineriai:
- `std::vector`
- `std::list`
- `std::deque`

---

## Testavimo sistemos parametrai

- **CPU:** 13th Gen Intel(R) Core(TM) i7-13650HX
- **RAM:** 24 GB (Speed:	4800 MT/s)
- **Diskas:** KBG60ZNT1T02 LS KIOXIA
- **Operacinė sistema:** Windows 11 25H2

---

## Testavimo metodika

Buvo matuojami šie žingsniai:
1. Duomenų nuskaitymas iš failo į konteinerį
2. Studentų rūšiavimas didėjimo tvarka
3. Studentų padalijimas į dvi grupes

Testavimui naudoti failai su šiais įrašų kiekiais:
- 1 000
- 10 000
- 100 000
- 1 000 000
- 10 000 000

Kiekvienas testas buvo vykdomas ... kartus, o lentelėse pateiktas **laikų vidurkis**.

---

# Konteinerių palyginimas

## `std::vector` strategijų palyginimas

| Įrašų kiekis | 1 strategija (s) | 2 strategija (s) | 3 strategija (s) |
|---:|---:|---:|---:|
| 1 000 | 0.000322 | 0.014209 | 0.000121 |
| 10 000 | 0.002185 | 1.481250 | 0.001551 |
| 100 000 | 0.009897 | 146.913000 | 0.012349 |
| 1 000 000 | 0.106548 | netestuota / per lėta | 0.088860 |
| 10 000 000 | 1.589870 | netestuota / per lėta | 1.193900 |

### Pastebėjimai apie `std::vector`

Atlikus testus su `std::vector` konteineriu, nustatyta, kad efektyviausia yra **3 strategija**, kuri remiasi efektyvesniu duomenų skaidymu (pvz., `partition`). Ji nuosekliai veikė greičiausiai visais testuotais duomenų dydžiais.

**1 strategija** taip pat parodė gerus rezultatus ir skalavosi gana stabiliai didėjant duomenų kiekiui, tačiau buvo šiek tiek lėtesnė nei 3 strategija.

**2 strategija** pasirodė esanti labai neefektyvi. Kadangi jos metu studentai yra šalinami iš `vector` konteinerio, kiekvienas šalinimas reikalauja likusių elementų perstūmimo atmintyje. Dėl to vykdymo laikas labai sparčiai auga didėjant duomenų kiekiui:

- 10 000 įrašų: ~1.48 s  
- 100 000 įrašų: ~146.9 s  

Dėl šios priežasties testai su 1 000 000 įrašų nebuvo tęsiami, nes vykdymo laikas tapo itin ilgas.

<img width="2000" height="1200" alt="vector_strategijos" src="https://github.com/user-attachments/assets/7dbc5b6b-f5c6-4e08-bc61-35d099669d6c" />

---

## `std::list` strategijų palyginimas

| Įrašų kiekis | 1 strategija (s) | 2 strategija (s) | 3 strategija (s) |
|---:|---:|---:|---:|
| 1 000 | 0.000229 | 0.000108 | 0.000065 |
| 10 000 | 0.002070 | 0.001231 | 0.000469 |
| 100 000 | 0.014920 | 0.011912 | 0.006024 |
| 1 000 000 | 0.183009 | 0.102061 | 0.054496 |
| 10 000 000 | 3.191050 | 1.089910 | 0.592616 |

### Pastebėjimai apie `std::list`

Atliekant testus su `std::list` konteineriu pastebėta, kad visos trys strategijos veikia efektyviai, tačiau aiškiai išsiskiria **3 strategija**, kuri visais atvejais buvo greičiausia.

Skirtingai nei `std::vector` atveju, **2 strategija su `std::list` pasirodė esanti efektyvi**. Taip yra todėl, kad `std::list` konteineryje elementų šalinimas vyksta pastoviu laiku (O(1)), nes nereikia perstumti kitų elementų atmintyje.

<img width="2000" height="1200" alt="list_strategijos" src="https://github.com/user-attachments/assets/8479f7f0-5cfb-49b8-bd73-8ed8c9a7f9fb" />

---

## `std::deque` strategijų palyginimas

| Įrašų kiekis | 1 strategija (s) | 2 strategija (s) | 3 strategija (s) |
|---:|---:|---:|---:|
| 1 000 | 0.000128 | 0.005950 | 0.000118 |
| 10 000 | 0.001181 | 0.565432 | 0.001218 |
| 100 000 | 0.007524 | 75.829300 | 0.010144 |
| 1 000 000 | 0.084794 | netestuota / per lėta | 0.148590 |
| 10 000 000 | 1.177900 | netestuota / per lėta | 1.276340 |

### Pastebėjimai apie `std::deque`

Atliekant testus su `std::deque` konteineriu pastebėta, kad efektyviausiai veikia **1 ir 3 strategijos**, kurios nenaudoja dažnų elementų šalinimų.

**1 strategija** daugeliu atvejų pasirodė esanti šiek tiek greitesnė nei 3 strategija, ypač didesnių duomenų kiekių atveju:

- 1 000 000 įrašų: 1 strategija – 0.084 s, 3 strategija – 0.148 s  
- 10 000 000 įrašų: 1 strategija – 1.17 s, 3 strategija – 1.27 s  

**2 strategija** pasirodė esanti labai neefektyvi, nes `std::deque` konteineryje elementų šalinimas iš vidurio yra brangi operacija. Dėl to vykdymo laikas sparčiai didėja:

- 100 000 įrašų: ~75.8 s  

Todėl ši strategija nėra tinkama dideliems duomenų kiekiams.

<img width="2000" height="1200" alt="deque_strategijos" src="https://github.com/user-attachments/assets/ffb4f261-d67b-4013-b19a-9dbb6a06d836" />

---

# Galutinės išvados

- **Greičiausias konteineris:**  
  `std::vector` (naudojant 3 strategiją) – parodė geriausius rezultatus didelių duomenų kiekių atveju.

- **Greičiausia strategija:**  
  3 strategija (`partition` / efektyvus skaidymas) – visais konteineriais veikė greičiausiai arba beveik greičiausiai.

- **Lėčiausias scenarijus:**  
  2 strategija su `std::vector` ir `std::deque`, nes dažnas elementų šalinimas sukelia dideles sąnaudas (elementų perstūmimas / brangios operacijos).  
  Pvz.: `vector` su 100 000 įrašų – ~146.9 s, `deque` – ~75.8 s.

- **Efektyviausias pasirinkimas pagal laiką:**  
  `std::vector` + 3 strategija – geriausias bendras našumas ir labai geras skalavimasis iki 10 000 000 įrašų.

- **Efektyviausias pasirinkimas pagal atmintį:**  
  2 strategija (naudojamas tik vienas papildomas konteineris), ypač su `std::list`, nes leidžia efektyviai šalinti elementus be papildomo kopijavimo.

<img width="1232" height="1213" alt="image" src="https://github.com/user-attachments/assets/667b38fc-7b6e-410d-b68f-8955de3f6f96" />
