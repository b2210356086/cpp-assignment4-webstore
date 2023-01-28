#ifndef TREE_AVL_H
#define TREE_AVL_H

#include "node.h"

int getHeight(SecondaryNodeAVL* node); //Returns height of an AVL node
int getBalance(SecondaryNodeAVL* node); //Returns balance factor of an AVL node, balance factor = (height of left subtree - height of right subtree)
SecondaryNodeAVL* rotateLeftAVL(SecondaryNodeAVL *root); //Rotates the tree with given root to left
SecondaryNodeAVL* rotateRightAVL(SecondaryNodeAVL *root); //Rotates the tree with given root to right
SecondaryNodeAVL* insertSecondaryAVL(SecondaryNodeAVL* secondaryRootAVL, std::string name, int price); //Inserts an item with given name and price information to the secondary AVL tree
void insertPrimaryAVL(PrimaryNodeAVL* &primaryRootAVL, std::string category, std::string name, int price); //Finds the secondary tree which an item to be inserted with category information
SecondaryNodeAVL* deleteSecondaryAVL(SecondaryNodeAVL* secondaryRootAVL, std::string name); //Deletes an item with given name from the secondary AVL tree
void deletePrimaryAVL(PrimaryNodeAVL* &primaryRootAVL, std::string category, std::string name); //Finds the secondary tree which an item to be deleted belongs to

#endif