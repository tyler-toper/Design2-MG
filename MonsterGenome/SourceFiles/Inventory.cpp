#include "../HeaderFiles/Inventory.h"


void Inventory::invInit() {
    this->numItems = 0;
    this->invArray = new Items*[this->maxCap];
}

Inventory::Inventory(unsigned int maxCap) {
    this->maxCap = maxCap;
    this->invInit();
}

Inventory::~Inventory(){
    this->freeMem();
}

void Inventory::makeNull(unsigned int start) {
    for(int i = start; i < this->maxCap; i++){
        this->invArray[i] = nullptr;
    }
}

void Inventory::freeMem() {
    for(int i=0; i < this->numItems; i++){
        delete this->invArray[i];
    }

    delete[] this->invArray;
}

void Inventory::clear(){
    for(int i=0; i < this->numItems; i++){
        delete this->invArray[i];
    }
    this->numItems = 0;
    this->makeNull();

}

const bool Inventory::empty() const {

}

const unsigned& Inventory::getSize() const{
    return this->numItems;
}

const unsigned& Inventory::getCap() const{
    return this->maxCap;
}


const bool Inventory::add(Items *item) {
    if((this->numItems) < this->maxCap){
        unsigned next = this->numItems++;
        this->invArray[next] = item->clone();
        return true;
    }
    return false;
}

const bool Inventory::remove(const unsigned int index) {
    if(this->numItems > 0 && index < numItems){
        delete this->invArray[index];
        this->invArray[index]=nullptr;
        --this->numItems;
        return true;
    }
}

const bool Inventory::saveFile(const string fileName) {
    ofstream outfile;
    outfile.open(fileName);
    for(int i=0; i<numItems; i++){
        if(invArray[i] != nullptr){
            outfile << invArray[i]->getType()  << endl;
            outfile << invArray[i]->getLevel()  << endl;
            outfile << "\n" << endl;
        }
    }

}
