#pragma once
#include <vector>
#include <iostream>
#include <cmath>
#include <map>
#include "vod.h"
#include "stub.h"
#include "potrosac.h"

class Konekcija {
public:
    Stub stub1, stub2;
    float struja;
    float rastojanje;
    float otpor;

    Konekcija(Stub stub1, Stub stub2,float rastojanje, float otpor) 
        : stub1(stub1), stub2(stub2), rastojanje(rastojanje), otpor(otpor) {}

    
};