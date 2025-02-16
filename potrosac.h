#pragma once
#include "stub.h"
#include "vod.h"
#include <string>

class Potrosac {
public:
    Stub stub;
    Vod vod;
    std::string ime;
    float struja;
    float geogSirina, geogDuzina;

    Potrosac() : struja(0), geogSirina(0), geogDuzina(0), ime("") {}

    Potrosac(Stub stub, Vod vod, std::string ime, float struja, float geogSirina, float geogDuzina)
        : stub(stub), vod(vod), ime(ime), struja(struja), geogSirina(geogSirina), geogDuzina(geogDuzina) {}
};