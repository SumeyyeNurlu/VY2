#ifndef HEXAGONNODE_HPP
#define HEXAGONNODE_HPP

#include "Hexagon.hpp"
using namespace std;

class HexagonNode {
public:
    Hexagon* data;       // Bu düğüm bir tane Altıgen taşır
    HexagonNode* next;   // Bir sonraki Altıgen düğümüne işaret eder

    HexagonNode(Hexagon* hexa) {
        data = hexa;
        next = nullptr;
    }
    
    // Yıkıcıda Altıgeni de silmeliyiz (Sahiplik Listede olacak)
    ~HexagonNode() {
        delete data;
    }
};

#endif