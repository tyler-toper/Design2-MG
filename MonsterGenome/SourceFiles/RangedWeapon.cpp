#include "../HeaderFiles/RangedWeapon.h"


RangedWeapon::RangedWeapon(unsigned level, string textureFile) : Weapons(level, textureFile) {

    this->itemType = ItemTypes::ITEM_RANGE;
}

RangedWeapon::~RangedWeapon() {

}