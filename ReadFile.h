#ifndef READ_FILE_H
#define READ_FILE_H

#include "Clothes.h"
#include "LinkedList.h"
#include <string>

void readClothesFromFile(const std::string& filename, LinkedList<Clothes*>& list);
void addClothesManually(LinkedList<Clothes*>& list); 
#endif
