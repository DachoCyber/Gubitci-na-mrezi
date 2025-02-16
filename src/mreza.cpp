#include <string>
#include <set>
#include <iostream>
#include <sstream>
#include <fstream>

#include "stub.h"
#include "mreza.h"


void Mreza :: izvuciPotrosaceIzFajla(std::string imeFajla) {

    std::ifstream mrezaFajl(imeFajla);
    if(!mrezaFajl) {
        std::cerr << "Greska pri otvaranju fajla!" << std::endl;
        return;
    }

    std::string linijaFajla;
    brPotrosaca = 0;
    

    int stariId = -1;

    while (getline(mrezaFajl, linijaFajla)) {
        std::istringstream iss(linijaFajla);
        Potrosac noviPotrosac;
        iss >> noviPotrosac.vod.id >> noviPotrosac.stub.id >> noviPotrosac.ime >> noviPotrosac.struja >> noviPotrosac.geogSirina >> noviPotrosac.geogDuzina;

        strujeStubova[noviPotrosac.stub.id] += noviPotrosac.struja;



        potrosaci.push_back(noviPotrosac);
        

        if (noviPotrosac.vod.id != stariId) {
            Vod noviVod;
            noviVod.id = noviPotrosac.vod.id;
            vodovi.push_back(noviVod);
        }

        stubovi.insert(noviPotrosac.stub);
        stariId = noviPotrosac.vod.id;
        brPotrosaca++;
    }
}


void Mreza :: napraviKonekcijeIMrezu() {
    for (int i = 0; i < vodovi.size(); i++) {
        for (int j = vodovi[i].stubovi.size() - 1; j > 0; j--) {
            // Proveri da li konekcija već postoji
            bool postoji = false;
            for (const auto& k : skupKonekcija) {
                if ((k.stub1.id == vodovi[i].stubovi[j].id && k.stub2.id == vodovi[i].stubovi[j - 1].id) ||
                    (k.stub1.id == vodovi[i].stubovi[j - 1].id && k.stub2.id == vodovi[i].stubovi[j].id)) {
                    postoji = true;
                    break;
                }
            }

            if (!postoji) {
                // Pronađi potrošače za stubove
                Potrosac p1, p2;
                bool pronadjenP1 = false, pronadjenP2 = false;

                for (const auto& potrosac : potrosaci) {
                    if (potrosac.stub.id == vodovi[i].stubovi[j].id) {
                        p1 = potrosac;
                        pronadjenP1 = true;
                    }
                    if (potrosac.stub.id == vodovi[i].stubovi[j - 1].id) {
                        p2 = potrosac;
                        pronadjenP2 = true;
                    }
                    if (pronadjenP1 && pronadjenP2) break;
                }

                if (!pronadjenP1 || !pronadjenP2) {
                    std::cerr << "Greska: Nije pronadjen potrosac za stubove " << vodovi[i].stubovi[j].id << " i " << vodovi[i].stubovi[j - 1].id << std::endl;
                    continue;
                }

                // Izračunaj rastojanje i otpor
                float rastojanje = sqrt(pow((p1.geogDuzina - p2.geogDuzina) * 109000 * cos(p2.geogSirina * 3.14159 / 180), 2.0) +
                   pow((p1.geogSirina - p2.geogSirina) * 109000, 2.0));
                float otpor = rastojanje / (70 * 32); // Pretpostavljena specifična otpornost i presek


                // Dodaj konekciju
                if (vodovi[i].stubovi[j].id != vodovi[i].stubovi[j - 1].id) {
                    Konekcija knkcija = {vodovi[i].stubovi[j], vodovi[i].stubovi[j - 1], rastojanje, otpor};
                    skupKonekcija.push_back(knkcija);
                    graf[vodovi[i].stubovi[j].id].push_back(vodovi[i].stubovi[j - 1].id);
                }
            }
        }
    }
}

float Mreza :: racunajStruju(int stub, int prethodni) {
    float ukupnaStruja = strujeStubova[stub];

    for (int sused : graf[stub]) {
        if (sused == prethodni) continue; // Izbegavamo povratak

        float strujaSuseda = racunajStruju(sused, stub);
        ukupnaStruja += strujaSuseda;

        // Ažuriranje struje u konekciji
        for (auto& konekcija : skupKonekcija) {
            if ((konekcija.stub1.id == stub && konekcija.stub2.id == sused) ||
                (konekcija.stub1.id == sused && konekcija.stub2.id == stub)) {
                konekcija.struja = strujaSuseda; // Ažuriraj struju samo jednom
                break;
            }
        }
    }

    return ukupnaStruja;
}

float Mreza :: izracunajUkupneGubitke() {
    float sum = 0;

    for (const auto& konekcija : skupKonekcija) {
        sum += konekcija.struja * konekcija.struja * konekcija.otpor * 3;
    }

    return sum;
}

void Mreza :: dodajUVod() {
    int trBrPotrosaca = brPotrosaca;
    while(trBrPotrosaca >= 0) {

    
        int idVod = potrosaci[trBrPotrosaca].vod.id;
        Stub stub = potrosaci[trBrPotrosaca].stub;
        
        for (auto& vod : vodovi) {
            if (vod.id == idVod) {
                vod.stubovi.push_back(stub);
                break;
            }
        }

        trBrPotrosaca--;
    }
}
