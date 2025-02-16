#pragma once
#include <tuple>

class Stub {
public:
    Stub() : id(0), ulaznaStruja(0) {}

    int id;
    double ulaznaStruja;

    bool operator<(const Stub& other) const {
        return std::tie(id, ulaznaStruja) < std::tie(other.id, other.ulaznaStruja);
    }

    bool operator==(const Stub& other) const {
        return id == other.id;
    }
};
