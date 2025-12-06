#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "new_main.h"

// Studento Copy Constructor testas
TEST_CASE("Studento Copy Constructor") {
    Studentas<vector<int>> originalas("Jonas", "Jonaitis", {8, 9, 10}, 9);
    originalas.setRez(9.0f);
    originalas.setMediana(9.0f);

    Studentas<vector<int>> kopija = originalas;

    // Tikrinam pirmine kopija
    CHECK(kopija.getVard() == originalas.getVard());
    CHECK(kopija.getPav() == originalas.getPav());
    CHECK(kopija.getRez() == originalas.getRez());
    CHECK(kopija.getMediana() == originalas.getMediana());
    CHECK(kopija.getPaz() == originalas.getPaz());

    // Pakeiciam originala ir tikrinam, kad kopija nesikeicia
    originalas.setVard("Petras");

    CHECK(originalas.getVard() == "Petras");
    CHECK(kopija.getVard() == "Jonas");

    // Pakeiciam kopija ir tikrinam, kad originalas nesikeicia
    kopija.setPav("Kazlauskas");

    CHECK(kopija.getPav() == "Kazlauskas");
    CHECK(originalas.getPav() == "Jonaitis");
}

// Studento Copy Assignment Operator testas
TEST_CASE("Studento Copy Assignment Operator") {
    Studentas<vector<int>> originalas("Jonas", "Jonaitis", {8, 9, 10}, 9);
    originalas.setRez(9.0f);
    originalas.setMediana(9.0f);

    Studentas<vector<int>> priskyrimas;
    priskyrimas = originalas;

    // Tikrinam pirmine kopija
    CHECK(priskyrimas.getVard() == originalas.getVard());
    CHECK(priskyrimas.getPav() == originalas.getPav());
    CHECK(priskyrimas.getPaz() == originalas.getPaz());
    CHECK(priskyrimas.getRez() == originalas.getRez());
    CHECK(priskyrimas.getMediana() == originalas.getMediana());

    // Pakeiciam originala ir tikrinam, kad priskyrimas nesikeicia
    originalas.setVard("Petras");

    CHECK(originalas.getVard() == "Petras");
    CHECK(priskyrimas.getVard() == "Jonas");

    // Pakeiciam priskyrima ir tikrinam, kad originalas nesikeicia
    priskyrimas.setPav("Kazlauskas");
    
    CHECK(priskyrimas.getPav() == "Kazlauskas");
    CHECK(originalas.getPav() == "Jonaitis");

    // Testuojam savikopija
    priskyrimas = priskyrimas;
    CHECK(priskyrimas.getVard() == "Jonas");
    CHECK(priskyrimas.getPav() == "Kazlauskas");
}

// Studento operatoriu testas
TEST_CASE("Operatorius << isveda studento duomenis") {
    Studentas<vector<int>> s("Jonas", "Jonaitis", {8, 9, 10}, 9);
    s.setRez(9.0f);
    s.setMediana(9.0f);

    ostringstream out;
    out << s;

    string rezultatas = out.str();

    // Tikrinam, ar išvestyje yra esminiai duomenys
    CHECK(rezultatas.find("Jonas") != string::npos);
    CHECK(rezultatas.find("Jonaitis") != string::npos);
    CHECK(rezultatas.find("9") != string::npos);
}

TEST_CASE("Operatorius >> nuskaitydamas studento duomenis sukuria teisinga objekta") {
    istringstream in("Jonas Jonaitis 8 9 10 9");
    
    Studentas<vector<int>> s;
    in >> s;

    CHECK(s.getVard() == "Jonas");
    CHECK(s.getPav() == "Jonaitis");

    auto paz = s.getPaz();
    CHECK(paz.size() == 3);
    CHECK(paz[0] == 8);
    CHECK(paz[1] == 9);
    CHECK(paz[2] == 10);

    CHECK(s.getEgzas() == 9);
}