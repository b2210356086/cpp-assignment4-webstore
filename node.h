#ifndef NODE_H
#define NODE_H

#include <string>

struct SecondaryNodeAVL
{
    std::string key; //Name
    SecondaryNodeAVL* pLeft = nullptr;
    SecondaryNodeAVL* pRight = nullptr;
    int price;
    int height = 1; //Height of AVL Node, initially nodes are added at leaf so default height is 1
};

struct SecondaryNodeRB
{
    std::string key; //Name
    SecondaryNodeRB* pLeft = nullptr;
    SecondaryNodeRB* pRight = nullptr;
    int price;
    bool color = 1; //Color of Red-Black Node. 0 = BLACK, 1 = RED. Initially nodes are added with red links so default color is 1
};

struct PrimaryNodeAVL
{
    std::string primaryKey; //Category
    PrimaryNodeAVL* pLeftPrimary = nullptr;
    PrimaryNodeAVL* pRightPrimary = nullptr;
    SecondaryNodeAVL* pSecondary = nullptr; //Corresponding AVL Tree
};

struct PrimaryNodeRB
{
    std::string primaryKey; //Category
    PrimaryNodeRB* pLeftPrimary = nullptr;
    PrimaryNodeRB* pRightPrimary = nullptr;
    SecondaryNodeRB* pSecondary = nullptr; //Corresponding Red-Black Tree
};

#endif