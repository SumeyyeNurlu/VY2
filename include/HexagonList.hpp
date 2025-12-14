#ifndef HEXAGONLIST_HPP
#define HEXAGONLIST_HPP

#include "HexagonNode.hpp"
#include <string>
using namespace std;

class HexagonList {
private:
    HexagonNode* head;
    HexagonNode* tail;
    int size;

public:
    HexagonList();
    ~HexagonList();

    void addHexagon(Hexagon* newHexagon);
    Hexagon* getHexagon(int index);
    int sizeCount();
    void loadFromFile(string filename);

    void mainOperation(int totalTurns);

    void printStatus();

    int calculateTotalHexagons(string filename);
};

#endif