#include "../HeaderFiles/Items.h"

void Items::initValues() {

}

Items::Items(unsigned level){
    this->initValues();
    this->level = level;
    this->itemType = ItemTypes::ITEM_DEFAULT;

}

Items::~Items() {

}

const unsigned& Items::getLevel() const {
    return this->level;
}

const unsigned& Items::getType() const {
    return this->itemType;
}