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

