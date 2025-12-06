// #define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "new_main.h"

// Medianos skaiciavimo testai
TEST_CASE("Medianos skaiciavimas") {
    // Konteinerio tipas: vector
    SECTION("Nelyginis pazymiu skaicius") {
        vector<int> pazymiai = {4, 2, 9, 6, 5};
        float mediana = skaiciuotiMediana(pazymiai);
        REQUIRE(mediana == 5.0f);
    }

    SECTION("Lyginis pazymiu skaicius") {
        vector<int> pazymiai = {4, 2, 9, 6};
        float mediana = skaiciuotiMediana(pazymiai);
        REQUIRE(mediana == 5.0f);
    } 
    // Konteinerio tipas: list
        SECTION("Nelyginis pazymiu skaicius") {
        list<int> pazymiai = {4, 2, 9, 6, 5};
        float mediana = skaiciuotiMediana(pazymiai);
        REQUIRE(mediana == 5.0f);
    }

    SECTION("Lyginis pazymiu skaicius") {
        list<int> pazymiai = {2, 4, 3, 5};
        float mediana = skaiciuotiMediana(pazymiai);
        REQUIRE(mediana == 3.5f);
    } 
}

// Rikiavimo ir grupavimo testai
TEST_CASE("Rikiavimas ir grupavimas") {
    SECTION("Vector konteineris") {
        vector<Studentas<vector<int>>> visiStudentai;
        {
            Studentas<vector<int>> s("Vardas1", "Pavarde1", {8,9,10}, 9);
            s.setRez(8.2f);
            visiStudentai.push_back(s);
        }
        {
            Studentas<vector<int>> s("Vardas2", "Pavarde2", {5,3,4}, 3);
            s.setRez(3.2f);
            visiStudentai.push_back(s);
        }
        {
            Studentas<vector<int>> s("Vardas3", "Pavarde3", {9,9,10}, 9);
            s.setRez(9.0f);
            visiStudentai.push_back(s);
        }
        {
            Studentas<vector<int>> s("Vardas4", "Pavarde4", {8,7,8}, 7);
            s.setRez(7.4f);
            visiStudentai.push_back(s);
        }
        {
            Studentas<vector<int>> s("Vardas5", "Pavarde5", {2,2,2}, 3);
            s.setRez(2.2f);
            visiStudentai.push_back(s);
        }

        vector<Studentas<vector<int>>> vargsiukai;
        vector<Studentas<vector<int>>> galvociai;

        rikiuotiIrSukurtGrupe(visiStudentai, vargsiukai, galvociai, "vidurkis");

        CHECK(vargsiukai.size() == 2);
        CHECK(galvociai.size() == 3);

        CHECK(vargsiukai[0].getVard() == "Vardas5");
        CHECK(vargsiukai[1].getVard() == "Vardas2");

        CHECK(galvociai[0].getVard() == "Vardas4");
        CHECK(galvociai[1].getVard() == "Vardas1");
        CHECK(galvociai[2].getVard() == "Vardas3");
    };
    SECTION("List konteineris") {
        list<Studentas<list<int>>> visiStudentai;
        {
            Studentas<list<int>> s("Vardas1", "Pavarde1", {8,9,10}, 9);
            s.setRez(8.2f);
            visiStudentai.push_back(s);
        }
        {
            Studentas<list<int>> s("Vardas2", "Pavarde2", {5,3,4}, 3);
            s.setRez(3.2f);
            visiStudentai.push_back(s);
        }
        {
            Studentas<list<int>> s("Vardas3", "Pavarde3", {9,9,10}, 9);
            s.setRez(9.0f);
            visiStudentai.push_back(s);
        }
        {
            Studentas<list<int>> s("Vardas4", "Pavarde4", {8,7,8}, 7);
            s.setRez(7.4f);
            visiStudentai.push_back(s);
        }
        {
            Studentas<list<int>> s("Vardas5", "Pavarde5", {2,2,2}, 3);
            s.setRez(2.2f);
            visiStudentai.push_back(s);
        }

        list<Studentas<list<int>>> vargsiukai;
        list<Studentas<list<int>>> galvociai;

        rikiuotiIrSukurtGrupe(visiStudentai, vargsiukai, galvociai, "vidurkis");

        CHECK(vargsiukai.size() == 2);
        CHECK(galvociai.size() == 3);


        // Konversija i vector, kad galetume indeksuoti
        vector<Studentas<list<int>>> v_vargs(vargsiukai.begin(), vargsiukai.end());
        vector<Studentas<list<int>>> v_galv(galvociai.begin(), galvociai.end());

        CHECK(v_vargs[0].getVard() == "Vardas5");
        CHECK(v_vargs[1].getVard() == "Vardas2");

        CHECK(v_galv[0].getVard() == "Vardas4");
        CHECK(v_galv[1].getVard() == "Vardas1");
        CHECK(v_galv[2].getVard() == "Vardas3");
    }
}