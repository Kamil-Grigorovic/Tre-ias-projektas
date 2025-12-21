#pragma once
#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <chrono>
#include <type_traits>
#include <numeric>
#include "base.h"

using namespace std;

/**
 * @class Studentas
 * @brief Šabloninė klasė, aprašanti studento duomenis.
 * @tparam T Pažymių konteinerio tipas (pvz., std::vector<int>, std::list<int>).
 *
 * Klasė paveldi iš bazinės klasės Zmogus ir saugo papildomą informaciją:
 * - namų darbų pažymius
 * - egzamino rezultatą
 * - galutinį balą (rezultatą)
 * - medianą
 */
template <typename T>
class Studentas : public Zmogus {
public:
    using paz_type = T; ///< Pažymių konteinerio tipas

private:
    T paz; ///< Namų darbų pažymiai
    int egzas; ///< Egzamino rezultatas
    float rez; ///< Galutinis balas
    float mediana; ///< Namų darbų pažymių mediana

public:
    /**
     * @brief Numatytaisiais parametrais inicializuojantis konstruktorius.
     * 
     * Nustato numatytąsias reikšmes pažymiams, egzaminui, rezultatui ir medianai.
     */
    Studentas() : paz(), egzas(0), rez(0), mediana(0) {}

    /**
     * @brief Konstruktorius su visais studento duomenimis.
     * @param v Vardas.
     * @param p Pavardė.
     * @param paz Namų darbų pažymiai.
     * @param e Egzamino rezultatas.
     * @details
     * Inicijuoja bazinę klasę Zmogus su vardu ir pavarde. 
     * Taip pat nustato pradinius pažymius ir egzamino rezultatą,
     * o galutinio balo ir medianos reikšmės inicializuojamos į 0.
     */
    Studentas(const string& v, const string& p, const T& paz, int e)
        : Zmogus{v, p}, paz(paz), egzas(e), rez(0), mediana(0) {}

    /**
     * @brief Destruktorius.
     */
    ~Studentas() {
        paz.clear();
        egzas = 0;
        rez = 0;
        mediana = 0;
    }

    /**
     * @brief Copy Constructor.
     * @param other Kitas Studentas objektas, iš kurio kopijuojami duomenys.
     * @details
     * Atliekamas gilus kopijavimas:
     * - inicializuojama bazinė klasė Zmogus su tais pačiais vardu ir pavarde,
     * - nukopijuojami namų darbų pažymiai,
     * - egzamino balas,
     * - galutinis balas,
     * - ir mediana.
     *
     * Šis konstruktorius yra dalis *Rule of Three* realizacijos.
     */
    Studentas(const Studentas& other)
        : Zmogus(other.getVard(), other.getPav()),
          paz(other.paz),
          egzas(other.egzas),
          rez(other.rez),
          mediana(other.mediana)
    {}

    /**
     * @brief Copy Assignment Operator.
     * @param other Kitas Studentas objektas, iš kurio kopijuojami duomenys.
     * @return Nuoroda į šį objektą po priskyrimo.
     * @details
     * Atlieka pilną objekto lauko reikšmių kopijavimą, įskaitant:
     * - paveldėtus laukus (vardą ir pavardę),
     * - pažymių konteinerį,
     * - egzamino balą,
     * - galutinį balą,
     * - medianą.
     *
     * Operatorius taip pat turi savikopijos (self-assignment) patikrą:
     * jei `other` yra tas pats objektas, priskyrimas nevykdomas.
     *
     * Šis operatorius yra dalis *Rule of Three* realizacijos.
     */
    Studentas& operator=(const Studentas& other)
    {   if (this == &other) return *this;

        setVard(other.getVard());
        setPav(other.getPav());

        paz = other.paz;
        egzas = other.egzas;
        rez = other.rez;
        mediana = other.mediana;

        return *this;
    }

    /**
     * @brief Išveda studento informaciją.
     * 
     * Perrašo bazinės klasės virtualią funkciją.
     */
    void info() const override {
        cout << getVard() << " " << getPav() << " ";

        for (int x : getPaz())
            cout << x << " ";

        cout << endl;
    }

    /**
     * @brief Gražina pažymių konteinerį.
     * @return Pažymių konteineris.
     */
    const T& getPaz() const { return paz; }
    /**
     * @brief Gražina egzamino balą.
     * @return Egzamino balas kaip int.
     */
    int getEgzas() const { return egzas; }
    /**
     * @brief Gražina galutinį balą.
     * @return Galutinis balas kaip float.
     */
    float getRez() const { return rez; }
    /**
     * @brief Gražina namų darbų pažymių medianą.
     * @return Mediana kaip float.
     */
    float getMediana() const { return mediana; }
    
    /**
     * @brief Nustato pažumių konteinerį.
     * @param p Naujas pažymių konteineris.
     */
    void setPaz(const T& p) { paz = p; }
    /**
     * @brief Nustato egzamino balą.
     * @param e Naujas egzamino balas.
     */
    void setEgzas(int e) { egzas = e; }
    /**
     * @brief Nustato galutinį balą.
     * @param r Naujas galutinis balas.
     */
    void setRez(float r) { rez = r; }
    /**
     * @brief Nustato namų darbų pažymių medianą.
     * @param m Nauja mediana.
     */
    void setMediana(float m) { mediana = m; }

    /**
     * @brief operator<< perkrovimas.
     * @param os Išvesties srautas (ostream), į kurį rašomi duomenys.
     * @param s Studentas objektas, kurio informacija išvedama.
     * @return Tas pats išvesties srautas po duomenų įrašymo
     * 
     * Formatas:
     * @code
     * Vardas Pavardė Rezultatas Mediana
     * @endcode
     */
    friend ostream& operator<<(ostream& os, const Studentas<T>& s) {
        os << s.getVard() << " " << s.getPav() << " | ";
        for (const auto& pazymys : s.getPaz()) {
            os << " " << pazymys;
        }
        os << " | " << s.getEgzas() << " | " << s.getRez() << " " << s.getMediana();
        return os;
    }

    /**
     * @brief operator>> perkrovimas.
     * @param is Įvesties srautas (istream), iš kurio skaitomi duomenys.
     * @param s Studentas objektas, į kurį įrašomi nuskaityti duomenys.
     * @return Tas pats įvesties srautas po duomenų nuskaitymo
     * 
     * Jeigu įvesties eilutėje nėra jokių pažymių, studentui priskiriami
     * numatytieji 0 reikšmės (paz, egzas, rez, mediana).
     * 
     * Formatas:
     * @code
     * Vardas Pavardė Paz1 Paz2 Paz3... Egzaminas
     * @endcode
     * 
     * @note
     * Funkcija išvalo įvesties srauto klaidos būseną (`is.clear()`),
     * kad būtų galima toliau naudoti srautą.
     */
    friend istream& operator>>(istream& is, Studentas<T>& s)
    {
        string vard, pav;
        if (!(is >> vard >> pav)) return is;

        s.setVard(vard);
        s.setPav(pav);

        T pazymiai;
        int x;

        while (is >> x) {
            pazymiai.push_back(x);
    }

        is.clear();
    if (pazymiai.empty()) {
            s.setPaz(T{});
            s.setEgzas(0);
            return is;
        }
        auto it = std::prev(pazymiai.end());
        int egzas = *it;
        pazymiai.erase(it);

        s.setPaz(pazymiai);
        s.setEgzas(egzas);

        return is;
    }
};

/** 
 * @brief Priklauso studento įvedimui. 
 * Šabloninės funkcijos deklaracijos.
 * @param T Pažymių konteinerio tipas (pvz., std::vector<int>, std::list<int>).
*/
template <typename T>
Studentas<T> ivesk();
template <typename T>
Studentas<T> iveskIsFailo(const string &line);
template <typename T>
float skaiciuotiMediana(const T &pazymiai);
template <typename T>
T skaitytiIsFailo(const string &failoPavadinimas);
template <typename T>
Studentas<T> generuokStudenta();
template <typename T>
void rikiuotiIrSukurtGrupe(const T &visiStudentai, T &vargsiukai, T &galvociai, const string &kriterijus);
template <typename T>
void rikiuotiIrSukurtGrupe_2(T &visiStudentai, T &vargsiukai, const string &kriterijus);
template <typename T>
void rikiuotiIrSukurtGrupe_3(T &visiStudentai, T &vargsiukai, const string &kriterijus);
template <typename T>
void spausdintiIFaila(const T &grupe, const string &failoVardas);
template <typename Container, typename Comparator>
void rikiuoti(Container &temp, Comparator comp);

/**
 * @brief Funkcija, kuri prideda tarpu, kad stringas uzimtu n simboliu
 */
string formatuoti(string s, int plotis);
string SkaiciaiSuKableliu(float value);
