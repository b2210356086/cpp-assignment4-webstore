#ifndef TREE_RB_H
#define TREE_RB_H

#include "node.h"

bool isRed(SecondaryNodeRB* node); //Returns true if a Red-Black node is red, otherwise false
void swapColors(SecondaryNodeRB* node1, SecondaryNodeRB* node2); //Swaps the colors of 2 R-B nodes
SecondaryNodeRB* rotateLeftRB(SecondaryNodeRB* root); //Rotates the tree with given root to left
SecondaryNodeRB* rotateRightRB(SecondaryNodeRB* root); //Rotates the tree with given root to right
SecondaryNodeRB* insertSecondaryRB(SecondaryNodeRB* secondaryRootRB, std::string name, int price); //Inserts an item with given name and price information to the secondary RB tree
void insertPrimaryRB(PrimaryNodeRB* &primaryRootRB, std::string category, std::string name, int price); //Finds the secondary tree which an item to be inserted with category information
SecondaryNodeRB* leanLeft(SecondaryNodeRB* node); //Leans the red link to left
SecondaryNodeRB* leanRight(SecondaryNodeRB* node); //Leans the red link to right
SecondaryNodeRB* moveRedLeft(SecondaryNodeRB* node); //Carries a red link down the left spine
SecondaryNodeRB* moveRedRight(SecondaryNodeRB* node); //Carries a red link down the right spine
SecondaryNodeRB* deleteMin(SecondaryNodeRB* node); //Deletes the smallest(left-most) node from a tree
SecondaryNodeRB* deleteSecondaryRB(SecondaryNodeRB* secondaryRootRB, std::string name); //Deletes an item with given name from the secondary RB tree
void deletePrimaryRB(PrimaryNodeRB* &primaryRootRB, std::string category, std::string name); //Finds the secondary tree which an item to be deleted belongs to

#endif