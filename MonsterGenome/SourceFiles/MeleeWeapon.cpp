#include "../HeaderFiles/MeleeWeapon.h"


MeleeWeapon::MeleeWeapon(unsigned level, string textureFile) : Weapons(level, textureFile) {

    this->itemType = ItemTypes::ITEM_MELEE;
}

MeleeWeapon::~MeleeWeapon() {

}