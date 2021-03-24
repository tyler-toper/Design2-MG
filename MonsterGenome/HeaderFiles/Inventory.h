#ifndef INVENTORY_H
#define INVENTORY_H

#include "Items.h"
#include <string>
#include <fstream>

using namespace std;

class Inventory {
private:

    Items** invArray;
    unsigned numItems;
    unsigned maxCap;

    void invInit();
    void makeNull(unsigned start = 0);
    void freeMem();

public:

    Inventory(unsigned maxCap);
    ~Inventory();
    const unsigned& getSize() const;
    const unsigned& getCap() const;
    void clear();

    const bool empty() const;
    const bool add(Items* item);
    const bool remove(const unsigned index);
    const bool saveFile(const string fileName);

};


#endif //INVENTORY_H
