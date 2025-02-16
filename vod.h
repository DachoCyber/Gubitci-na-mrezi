#pragma once
#include <vector>
#include "stub.h"

// Forward declaration of Potrosac to avoid circular dependency
class Potrosac;

class Vod {
public:
    int id;
    std::vector<Stub> stubovi;

    Vod() : id(0) {}

    static void dodajUVod(int trBrPotrosaca, std::vector<Potrosac>& potrosaci);
};