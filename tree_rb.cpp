#include "tree_rb.h"
#include "utility.h"

bool isRed(SecondaryNodeRB* node)
{
    if(node == nullptr)
    {
        return false;
    }
    return node->color;
}

void swapColors(SecondaryNodeRB* node1, SecondaryNodeRB* node2)
{
    bool temp = node2->color;
    node2->color = node1->color;
    node1->color = temp;
}

SecondaryNodeRB* rotateLeftRB(SecondaryNodeRB* root)
{
    SecondaryNodeRB* newRoot = root->pRight;
    SecondaryNodeRB* temp = newRoot->pLeft;

    newRoot->pLeft = root;
    root->pRight = temp;

    return newRoot;
}

SecondaryNodeRB* rotateRightRB(SecondaryNodeRB* root)
{
    SecondaryNodeRB* newRoot = root->pLeft;
    SecondaryNodeRB* temp = newRoot->pRight;

    newRoot->pRight = root;
    root->pLeft = temp;

    return newRoot;
}

SecondaryNodeRB* insertSecondaryRB(SecondaryNodeRB* secondaryRootRB, std::string name, int price)
{
    if(secondaryRootRB == nullptr)
    {
        SecondaryNodeRB* newSecondaryNode = new SecondaryNodeRB;
        newSecondaryNode->key = name;
        newSecondaryNode->price = price;
        return newSecondaryNode;
    }

    if(name.compare(secondaryRootRB->key) < 0)
    {
        secondaryRootRB->pLeft = insertSecondaryRB(secondaryRootRB->pLeft, name, price);
    }
    else if(name.compare(secondaryRootRB->key) > 0)
    {
        secondaryRootRB->pRight = insertSecondaryRB(secondaryRootRB->pRight, name, price);
    }
    else
    {
        return secondaryRootRB;
    }
    
    if(isRed(secondaryRootRB->pRight) && !(isRed(secondaryRootRB->pLeft)))
    {
        secondaryRootRB = rotateLeftRB(secondaryRootRB);
        swapColors(secondaryRootRB, secondaryRootRB->pLeft);
    }
    if(isRed(secondaryRootRB->pLeft) && isRed(secondaryRootRB->pLeft->pLeft))
    {
        secondaryRootRB = rotateRightRB(secondaryRootRB);
        swapColors(secondaryRootRB, secondaryRootRB->pRight);
    }
    if(isRed(secondaryRootRB->pLeft) && isRed(secondaryRootRB->pRight))
    {
        secondaryRootRB->pLeft->color = false;
        secondaryRootRB->pRight->color = false;
        secondaryRootRB->color = !(secondaryRootRB->color);
    }
    return secondaryRootRB;
}

void insertPrimaryRB(PrimaryNodeRB* &primaryRootRB, std::string category, std::string name, int price)
{
    if(primaryRootRB == nullptr)
    {
        PrimaryNodeRB* newPrimaryNode = new PrimaryNodeRB;
        newPrimaryNode->primaryKey = category;
        newPrimaryNode->pSecondary = insertSecondaryRB(newPrimaryNode->pSecondary, name, price);
        newPrimaryNode->pSecondary->color = false;
        primaryRootRB = newPrimaryNode;
        return;
    }

    if(category.compare(primaryRootRB->primaryKey) < 0)
    {
        insertPrimaryRB(primaryRootRB->pLeftPrimary, category, name, price);
    }
    else if(category.compare(primaryRootRB->primaryKey) > 0)
    {
        insertPrimaryRB(primaryRootRB->pRightPrimary, category, name, price);
    }
    else
    {
        primaryRootRB->pSecondary = insertSecondaryRB(primaryRootRB->pSecondary, name, price);
        primaryRootRB->pSecondary->color = false;
    }
}

SecondaryNodeRB* leanLeft(SecondaryNodeRB* node)
{
    SecondaryNodeRB* temp = rotateLeftRB(node);
    temp->color = temp->pLeft->color;
    temp->pLeft->color = true;
    return temp;
}

SecondaryNodeRB* leanRight(SecondaryNodeRB* node)
{
    SecondaryNodeRB* temp = rotateRightRB(node);
    temp->color = temp->pRight->color;
    temp->pRight->color = true;
    return temp;
}

SecondaryNodeRB* moveRedLeft(SecondaryNodeRB* node)
{
    node->color = false;
    node->pLeft->color = true;
    if(isRed(node->pRight->pLeft))
    {
        node->pRight = rotateRightRB(node->pRight);
        node = rotateLeftRB(node);
    }
    else
    {
        node->pRight->color = true;
    }
    return node;
}

SecondaryNodeRB* moveRedRight(SecondaryNodeRB* node)
{
    node->color = false;
    node->pRight->color = true;
    if(isRed(node->pLeft->pLeft))
    {
        node = rotateRightRB(node);
        node->color = true;
        node->pLeft->color = false;
    }
    else
    {
        node->pLeft->color = true;
    }
    return node;
}

SecondaryNodeRB* deleteMin(SecondaryNodeRB* node)
{
    if(node->pLeft == nullptr)
    {
        return nullptr;
    }
    if(!isRed(node->pLeft) && !isRed(node->pLeft->pLeft))
    {
        node = moveRedLeft(node);
    }
    node->pLeft = deleteMin(node->pLeft);
    if(isRed(node->pRight))
    {
        node = leanLeft(node);
    }
    return node;
}

SecondaryNodeRB* deleteSecondaryRB(SecondaryNodeRB* secondaryRootRB, std::string name)
{
    if(name.compare(secondaryRootRB->key) < 0)
    {
        if(!isRed(secondaryRootRB->pLeft) && !isRed(secondaryRootRB->pLeft->pLeft))
        {
            secondaryRootRB = moveRedLeft(secondaryRootRB);
        }
        secondaryRootRB->pLeft = deleteSecondaryRB(secondaryRootRB->pLeft, name);
    }
    else
    {
        if(isRed(secondaryRootRB->pLeft))
        {
            secondaryRootRB = leanRight(secondaryRootRB);
        }
        if(name == secondaryRootRB->key && secondaryRootRB->pRight == nullptr)
        {
            return nullptr;
        }
        if(!isRed(secondaryRootRB->pRight) && !isRed(secondaryRootRB->pRight->pLeft))
        {
            secondaryRootRB = moveRedRight(secondaryRootRB);
        }

        if(name == secondaryRootRB->key)
        {
            SecondaryNodeRB* temp = leftMostNode(secondaryRootRB->pRight);
            secondaryRootRB->key = temp->key;
            secondaryRootRB->price = temp->price;
            secondaryRootRB->pRight = deleteMin(secondaryRootRB->pRight);
        }
        else
        {
            secondaryRootRB->pRight = deleteSecondaryRB(secondaryRootRB->pRight, name);
        }
    }
    if(isRed(secondaryRootRB->pRight))
    {
        secondaryRootRB = leanLeft(secondaryRootRB);
    }
    return secondaryRootRB;
}

void deletePrimaryRB(PrimaryNodeRB* &primaryRootRB, std::string category, std::string name)
{
    if(primaryRootRB == nullptr)
    {
        return;
    }
    if(category.compare(primaryRootRB->primaryKey) < 0)
    {
        deletePrimaryRB(primaryRootRB->pLeftPrimary, category, name);
    }
    else if(category.compare(primaryRootRB->primaryKey) > 0)
    {
        deletePrimaryRB(primaryRootRB->pRightPrimary, category, name);
    }
    else
    {
        primaryRootRB->pSecondary = deleteSecondaryRB(primaryRootRB->pSecondary, name);
    }
}