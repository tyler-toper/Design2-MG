#ifndef ITEMS_H
#define ITEMS_H

enum ItemTypes {ITEM_DEFAULT = 0, ITEM_MELEE, ITEM_RANGE};

class Items {
private:
    void initValues();

protected:
    unsigned int itemType;
    unsigned level;

public:
    Items(unsigned level);
    virtual ~Items();

    virtual Items* clone() = 0;
    const unsigned& getLevel() const;
    const unsigned& getType() const;
};


#endif //ITEMS_H
