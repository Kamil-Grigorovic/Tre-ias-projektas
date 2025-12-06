#include "main.h"

// Funkcija studento ivedimui rankiniu budu
template <typename T>
Studentas<T> ivesk() {
    Studentas<T> s;
    string input;
    cout << "Iveskite varda: ";
    getline(cin, input);
    s.setVard(input);
    cout << "Iveskite pavarde: ";
    getline(cin, input);
    s.setPav(input);

    T paz;
    cout << "Iveskite namu darbu pazymius po viena. Kai baigsite, paspauskite ENTER:\n";
    while (true) {
        cout << "Pazymys: ";
        getline(cin, input);
        if (input.empty()) break;
        try {
            int pazymys = stoi(input);
            paz.push_back(pazymys);
        } catch (...) {
            cout << "Klaida: iveskite skaiciu arba ENTER, kad baigti.\n";
        }
    }
    if (paz.empty()) paz.push_back(0);
    s.setPaz(paz);

    while (true) {
        cout << "Iveskite egzamino bala: ";
        getline(cin, input);
        try {
            s.setEgzas(stoi(input));
            break;
        } catch (...) {
            cout << "Klaida: iveskite skaiciu!\n";
        }
    }

    int sum = 0;
    for (int p : paz) sum += p;
    float rez = s.getEgzas() * 0.6f + (float)sum / paz.size() * 0.4f;
    s.setRez(rez);
    s.setMediana(skaiciuotiMediana(paz));

    return s;
}

// Funkcija vienos eilutes skaitymui is failo
template <typename T>
Studentas<T> iveskIsFailo(const string &line) {
    Studentas<T> s;
    istringstream in(line);

    string vard, pav;
    in >> vard >> pav;
    s.setVard(vard);
    s.setPav(pav);

    T visiSkaiciai;
    string temp;
    while (in >> temp) {
        try {
            int skaicius = stoi(temp);
            visiSkaiciai.push_back(skaicius);
        } catch (...) {}
    }

    if (visiSkaiciai.empty()) {
        s.setEgzas(0);
        s.setRez(0);
        s.setMediana(0);
        return s;
    }

    s.setEgzas(visiSkaiciai.back());
    visiSkaiciai.pop_back();
    s.setPaz(visiSkaiciai);

    int sum = 0;
    for (int p : visiSkaiciai) sum += p;
    float vid = (visiSkaiciai.empty()) ? 0 : (float)sum / visiSkaiciai.size();
    s.setRez(s.getEgzas() * 0.6f + vid * 0.4f);
    s.setMediana(skaiciuotiMediana(visiSkaiciai));

    return s;
}

// Funkcija viso failo skaitymui
template <typename T>
T skaitytiIsFailo(const string &failoPavadinimas) {
    T studentai;
    auto start = chrono::high_resolution_clock::now();

    ifstream failas(failoPavadinimas);
    if (!failas) {
        cout << "Nepavyko atidaryti failo: " << failoPavadinimas << endl;
        return studentai;
    }

    string line;
    getline(failas, line); // praleidžiam antraštę

    using PazT = typename T::value_type::paz_type;
    while (getline(failas, line)) {
        if (!line.empty())
            studentai.push_back(iveskIsFailo<PazT>(line));
    }

    failas.close();
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    cout << "Failo skaitymas uztruko " << elapsed.count() << " s.\n";
    return studentai;
}

// medianai skaiciuoti
template <typename Container>
float skaiciuotiMediana(const Container &pazymiai) {
    vector<int> temp(pazymiai.begin(), pazymiai.end());
    sort(temp.begin(), temp.end());
    int n = temp.size();
    if (n == 0) return 0;
    if (n % 2 == 1) return temp[n/2];
    return (temp[n/2 - 1] + temp[n/2]) / 2.0f;
}

// Funkcija, kuri prideda tarpu, kad stringas uzimtu n simboliu
string formatuoti(string s, int plotis) {
    int tarpai = plotis - s.length();
    int kaire = tarpai / 2;
    int desine = tarpai - kaire;
    return string(kaire, ' ') + s + string(desine, ' ');
}

// Funkcija atsitiktinio studento generavimui
template <typename T>
Studentas<T> generuokStudenta() {
    Studentas<T> s;
    string vard, pav;
    cout << "Iveskite varda: ";
    getline(cin, vard);
    cout << "Iveskite pavarde: ";
    getline(cin, pav);
    s.setVard(vard);
    s.setPav(pav);

    int ndKiekis;
    cout << "Kiek namu darbu pazymiu? ";
    cin >> ndKiekis;
    cin.ignore();

    T paz;
    for (int i = 0; i < ndKiekis; i++)
        paz.push_back(rand() % 10 + 1);
    s.setPaz(paz);
    s.setEgzas(rand() % 10 + 1);

    int sum = accumulate(paz.begin(), paz.end(), 0);
    float rez = s.getEgzas() * 0.6f + (float)sum / paz.size() * 0.4f;
    s.setRez(rez);
    s.setMediana(skaiciuotiMediana(paz));

    return s;
}

// Rusiavimo funkcija
template <typename Container, typename Comparator>
void rikiuoti(Container &temp, Comparator comp) {
    if constexpr  (std::is_same_v<Container, std::list<typename Container::value_type>>) {
        temp.sort(comp);
    } else {
        std::sort(temp.begin(), temp.end(), comp);
    }
}
template <typename T>
void rikiuotiIrSukurtGrupe(const T &visiStudentai, T &vargsiukai, T &galvociai, const string &kriterijus) {
    auto start = std::chrono::high_resolution_clock::now();
    auto temp = visiStudentai;

    auto comparator = [&](const auto &a, const auto &b) {
        if (kriterijus == "vardas") 
            return a.getVard() < b.getVard();
        if (kriterijus == "pavarde") 
            return a.getPav() < b.getPav();
        if (kriterijus == "vidurkis") 
            return a.getRez() < b.getRez();
        if (a.getPav() == b.getPav()) 
            return a.getVard() < b.getVard();
        return a.getVard() < b.getVard();
    };

    rikiuoti(temp, comparator);

    vargsiukai.clear();
    galvociai.clear();

    for (const auto &s : temp) {
        if (s.getRez() < 5)
            vargsiukai.push_back(s);
        else
            galvociai.push_back(s);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    cout << "Rikiavimas ir grupavimas (1 strategija) uztruko: " << elapsed.count() << " sekundziu." << endl;
}

// Rusiavimo funkcija su 2 strategija
template <typename T>
void rikiuotiIrSukurtGrupe_2(T &visiStudentai, T &vargsiukai, const string &kriterijus) {
    auto start = std::chrono::high_resolution_clock::now();

    auto comparator = [&](const auto &a, const auto &b) {
        if (kriterijus == "vardas") 
            return a.getVard() < b.getVard();
        if (kriterijus == "pavarde") 
            return a.getPav() < b.getPav();
        if (kriterijus == "vidurkis") 
            return a.getRez() < b.getRez();
        if (a.getPav() == b.getPav()) 
            return a.getVard() < b.getVard();
        return a.getVard() < b.getVard();
    };

    rikiuoti(visiStudentai, comparator);

    vargsiukai.clear();
    for (auto it = visiStudentai.begin(); it != visiStudentai.end(); ) {
        if (it->getRez() < 5) {
            vargsiukai.push_back(*it);
            it = visiStudentai.erase(it);
        } else {
            ++it;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    cout << "Rikiavimas ir grupavimas (2 strategija) uztruko: " 
         << elapsed.count() << " sekundziu." << endl;
}

// Rusiavimas ir grupavimas 3 strategija
template <typename T>
void rikiuotiIrSukurtGrupe_3(T &visiStudentai, T &vargsiukai, const string &kriterijus) {
    auto start = std::chrono::high_resolution_clock::now();

    auto comparator = [&](const auto &a, const auto &b) {
        if (kriterijus == "vardas") 
            return a.getVard() < b.getVard();
        if (kriterijus == "pavarde") 
            return a.getPav() < b.getPav();
        if (kriterijus == "vidurkis") 
            return a.getRez() < b.getRez();
        if (a.getPav() == b.getPav()) 
            return a.getVard() < b.getVard();
        return a.getVard() < b.getVard();
    };

    rikiuoti(visiStudentai, comparator);

    vargsiukai.clear();

    if constexpr (std::is_same_v<T, std::vector<typename T::value_type>>) {
        std::copy_if(visiStudentai.begin(), visiStudentai.end(), std::back_inserter(vargsiukai),
                     [](const auto &s) { return s.getRez() < 5; });

        visiStudentai.erase(
            std::remove_if(visiStudentai.begin(), visiStudentai.end(),
                           [](const auto &s) { return s.getRez() < 5; }),
            visiStudentai.end());

    } else {
        for (auto it = visiStudentai.begin(); it != visiStudentai.end(); ) {
            if (it->getRez() < 5) {
                vargsiukai.push_back(*it);
                it = visiStudentai.erase(it);
            } else {
                ++it;
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    cout << "Rikiavimas ir grupavimas (3 strategija) uztruko: "
         << elapsed.count() << " sekundziu." << endl;
}

// Funkcija studentų rezultatų spausdinimui į failą
template <typename T>
void spausdintiIFaila(const T &grupe, const string &failoVardas) {
    auto start = chrono::high_resolution_clock::now();

    ofstream out(failoVardas);
    if (!out) {
        cout << "Nepavyko sukurti failo: " << failoVardas << endl;
        return;
    }

    out << "|" << formatuoti("Vardas", 14)
        << "|" << formatuoti(" Pavarde", 15)
        << "|" << formatuoti("Vidurkis", 10)
        << "|" << formatuoti("Mediana", 9) << "|\n";
    out << "-----------------------------------------------------\n";

    for (const auto &temp : grupe) {
        out << "|" << formatuoti(temp.getVard(), 14)
            << "|" << formatuoti(temp.getPav(), 15)
            << "|" << formatuoti(SkaiciaiSuKableliu(temp.getRez()), 10)
            << "|" << formatuoti(SkaiciaiSuKableliu(temp.getMediana()), 9)
            << "|\n";
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    cout << "Spausdinimas i faila (" << failoVardas << ") uztruko: "
         << elapsed.count() << " s.\n";
}


// Funkcija skaiciaus formatavimui su kableliu
string SkaiciaiSuKableliu(float value) {
    int sveika = (int)value;
    int desimtys = (int)(value * 100 + 0.5) % 100;
    string rezultatas = std::to_string(sveika) + ".";
    rezultatas += std::to_string(desimtys);
    return rezultatas;
}

// Sablonų deklaracijos
template void rikiuotiIrSukurtGrupe<vector<Studentas<vector<int>>>>(const vector<Studentas<vector<int>>>&, vector<Studentas<vector<int>>>&, 
    vector<Studentas<vector<int>>>&, const string&);
template void rikiuotiIrSukurtGrupe<list<Studentas<list<int>>>>(const list<Studentas<list<int>>>&, list<Studentas<list<int>>>&,
    list<Studentas<list<int>>>&, const string&);
template void spausdintiIFaila<vector<Studentas<vector<int>>>>(const vector<Studentas<vector<int>>>&, const string&);
template void spausdintiIFaila<list<Studentas<list<int>>>>(const list<Studentas<list<int>>>&, const string&);
template Studentas<vector<int>> ivesk();
template Studentas<list<int>> ivesk();
template Studentas<vector<int>> iveskIsFailo(const string &line);
template Studentas<list<int>> iveskIsFailo(const string &line);
template vector<Studentas<vector<int>>> skaitytiIsFailo(const string &failoPavadinimas);
template list<Studentas<list<int>>> skaitytiIsFailo(const string &failoPavadinimas);
template Studentas<vector<int>> generuokStudenta();
template Studentas<list<int>> generuokStudenta();
template void rikiuotiIrSukurtGrupe_2<vector<Studentas<vector<int>>>>(vector<Studentas<vector<int>>>&, vector<Studentas<vector<int>>>&, const string&);
template void rikiuotiIrSukurtGrupe_2<list<Studentas<list<int>>>>(list<Studentas<list<int>>>&, list<Studentas<list<int>>>&, const string&);
template void rikiuotiIrSukurtGrupe_3<vector<Studentas<vector<int>>>>(vector<Studentas<vector<int>>>&, vector<Studentas<vector<int>>>&, const string&);
template void rikiuotiIrSukurtGrupe_3<list<Studentas<list<int>>>>(list<Studentas<list<int>>>&, list<Studentas<list<int>>>&, const string&);
