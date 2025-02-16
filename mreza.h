#ifndef _MREZA_H_
#define _MREZA_H_

#include "konekcija.h"
#include "vod.h"
#include "stub.h"
#include "potrosac.h"

#include <string>
#include <map>
#include <vector>
#include <utility>
#include <set>

class Mreza {
private:
    std::map<std::pair<int, int>, float> strujaKrozVod;
    std::vector<Konekcija> skupKonekcija;
    std::map<int, std::vector<int>> graf;
    std::map<int, float> strujeStubova;
    std::vector<Vod> vodovi;
    std::vector<Potrosac> potrosaci;
    std::set<Stub> stubovi;
    int brStubova;
    int brPotrosaca;
public:
    void izvuciPotrosaceIzFajla(std::string imeFajla);
    void napraviKonekcijeIMrezu();

    float racunajStruju(int stub, int prethodni);
    int trafoStanicaId() {
        return stubovi.begin() -> id;
    }
    float izracunajUkupneGubitke();
    void dodajUVod();
};

#endif