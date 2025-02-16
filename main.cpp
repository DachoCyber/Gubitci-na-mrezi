#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include "potrosac.h"
#include "stub.h"
#include "konekcija.h"
#include "mreza.h"

int main() {

    Mreza elektricnaMreza;

    std::string imeFajla = "stubovi.txt";
    
    elektricnaMreza.izvuciPotrosaceIzFajla(imeFajla);
    elektricnaMreza.dodajUVod();
    elektricnaMreza.napraviKonekcijeIMrezu();

    int idTrafoStub = elektricnaMreza.trafoStanicaId();

    elektricnaMreza.racunajStruju(idTrafoStub, -1);

    float ukupniGubici = elektricnaMreza.izracunajUkupneGubitke();


    std::cout << "Ukupni gubitci na mrezi su: ";
    std::cout << ukupniGubici << "W." << std::endl;

    // Ovde dodaj kod za učitavanje podataka iz fajla

    return 0;
}
