#include "tree_avl.h"
#include "utility.h"

int getHeight(SecondaryNodeAVL* node)
{
    if(node == nullptr)
    {
        return 0;
    }
    return node->height;
}

int getBalance(SecondaryNodeAVL* node)
{
    if(node == nullptr)
    {
        return 0;
    }
    return getHeight(node->pLeft) - getHeight(node->pRight);
}

SecondaryNodeAVL* rotateLeftAVL(SecondaryNodeAVL *root)
{
    SecondaryNodeAVL *newRoot = root->pRight;
    SecondaryNodeAVL *temp = newRoot->pLeft;
 
    newRoot->pLeft = root;
    root->pRight = temp;
 
    root->height = max(getHeight(root->pLeft), getHeight(root->pRight)) + 1;
    newRoot->height = max(getHeight(newRoot->pLeft), getHeight(newRoot->pRight)) + 1;
 
    return newRoot;
}

SecondaryNodeAVL* rotateRightAVL(SecondaryNodeAVL *root)
{
    SecondaryNodeAVL *newRoot = root->pLeft;
    SecondaryNodeAVL *temp = newRoot->pRight;
 
    newRoot->pRight = root;
    root->pLeft = temp;
 
    root->height = max(getHeight(root->pLeft), getHeight(root->pRight)) + 1;
    newRoot->height = max(getHeight(newRoot->pLeft), getHeight(newRoot->pRight)) + 1;
 
    return newRoot;
}

SecondaryNodeAVL* insertSecondaryAVL(SecondaryNodeAVL* secondaryRootAVL, std::string name, int price)
{
    if(secondaryRootAVL == nullptr)
    {
        SecondaryNodeAVL* newSecondaryNode = new SecondaryNodeAVL;
        newSecondaryNode->key = name;
        newSecondaryNode->price = price;
        return newSecondaryNode;
    }

    if(name.compare(secondaryRootAVL->key) < 0)
    {
        secondaryRootAVL->pLeft = insertSecondaryAVL(secondaryRootAVL->pLeft, name, price);
    }
    else if(name.compare(secondaryRootAVL->key) > 0)
    {
        secondaryRootAVL->pRight = insertSecondaryAVL(secondaryRootAVL->pRight, name, price);
    }
    else
    {
        return secondaryRootAVL;
    }

    secondaryRootAVL->height = max(getHeight(secondaryRootAVL->pLeft), getHeight(secondaryRootAVL->pRight)) + 1;

    int balance = getBalance(secondaryRootAVL);

    if(balance < -1 && name.compare(secondaryRootAVL->pRight->key) > 0)
    {
        return rotateLeftAVL(secondaryRootAVL);
    }
    if(balance > 1 && name.compare(secondaryRootAVL->pLeft->key) < 0)
    {
        return rotateRightAVL(secondaryRootAVL);
    }
    if(balance < -1 && name.compare(secondaryRootAVL->pRight->key) < 0)
    {
        secondaryRootAVL->pRight = rotateRightAVL(secondaryRootAVL->pRight);
        return rotateLeftAVL(secondaryRootAVL);
    }
    if(balance > 1 && name.compare(secondaryRootAVL->pLeft->key) > 0)
    {
        secondaryRootAVL->pLeft = rotateLeftAVL(secondaryRootAVL->pLeft);
        return rotateRightAVL(secondaryRootAVL);
    }

    return secondaryRootAVL;
}

void insertPrimaryAVL(PrimaryNodeAVL* &primaryRootAVL, std::string category, std::string name, int price)
{
    if(primaryRootAVL == nullptr)
    {
        PrimaryNodeAVL* newPrimaryNode = new PrimaryNodeAVL;
        newPrimaryNode->primaryKey = category;
        newPrimaryNode->pSecondary = insertSecondaryAVL(newPrimaryNode->pSecondary, name, price);
        primaryRootAVL = newPrimaryNode;
        return;
    }

    if(category.compare(primaryRootAVL->primaryKey) < 0)
    {
        insertPrimaryAVL(primaryRootAVL->pLeftPrimary, category, name, price);
    }
    else if(category.compare(primaryRootAVL->primaryKey) > 0)
    {
        insertPrimaryAVL(primaryRootAVL->pRightPrimary, category, name, price);
    }
    else
    {
        primaryRootAVL->pSecondary = insertSecondaryAVL(primaryRootAVL->pSecondary, name, price);
    }
}

SecondaryNodeAVL* deleteSecondaryAVL(SecondaryNodeAVL* secondaryRootAVL, std::string name)
{
    if(secondaryRootAVL == nullptr)
    {
        return secondaryRootAVL;
    }

    if(name.compare(secondaryRootAVL->key) < 0)
    {
        secondaryRootAVL->pLeft = deleteSecondaryAVL(secondaryRootAVL->pLeft, name);
    }
    else if(name.compare(secondaryRootAVL->key) > 0)
    {
        secondaryRootAVL->pRight = deleteSecondaryAVL(secondaryRootAVL->pRight, name);
    }
    else
    {
        if(secondaryRootAVL->pLeft == nullptr || secondaryRootAVL->pRight == nullptr)
        {
            SecondaryNodeAVL* temp;
            if(secondaryRootAVL->pLeft != nullptr)
            {
                temp = secondaryRootAVL->pLeft;
            }
            else
            {
                temp = secondaryRootAVL->pRight;
            }
            
            if(temp == nullptr)
            {
                temp = secondaryRootAVL;
                secondaryRootAVL = nullptr;
            }
            else
            {
                *secondaryRootAVL = *temp;
            }
        }
        else
        {
            SecondaryNodeAVL* temp = leftMostNode(secondaryRootAVL->pRight);
            secondaryRootAVL->key = temp->key;
            secondaryRootAVL->price = temp->price;
            secondaryRootAVL->pRight = deleteSecondaryAVL(secondaryRootAVL->pRight, temp->key);
        }
    }

    if(secondaryRootAVL == nullptr)
    {
        return secondaryRootAVL;
    }
    secondaryRootAVL->height = max(getHeight(secondaryRootAVL->pLeft), getHeight(secondaryRootAVL->pRight)) + 1;
    
    int balance = getBalance(secondaryRootAVL);
    if(balance < -1 && getBalance(secondaryRootAVL->pRight) < 0)
    {
        return rotateLeftAVL(secondaryRootAVL);
    }
    if(balance < -1 && getBalance(secondaryRootAVL->pRight) > 0)
    {
        secondaryRootAVL->pRight = rotateRightAVL(secondaryRootAVL->pRight);
        return rotateLeftAVL(secondaryRootAVL);
    }
    if(balance > 1 && getBalance(secondaryRootAVL->pLeft) > 0)
    {
        return rotateRightAVL(secondaryRootAVL);
    }
    if(balance > 1 && getBalance(secondaryRootAVL->pLeft) < 0)
    {
        secondaryRootAVL->pLeft = rotateLeftAVL(secondaryRootAVL->pLeft);
        return rotateRightAVL(secondaryRootAVL);
    }
    return secondaryRootAVL;
}

void deletePrimaryAVL(PrimaryNodeAVL* &primaryRootAVL, std::string category, std::string name)
{
    if(primaryRootAVL == nullptr)
    {
        return;
    }
    if(category.compare(primaryRootAVL->primaryKey) < 0)
    {
        deletePrimaryAVL(primaryRootAVL->pLeftPrimary, category, name);
    }
    else if(category.compare(primaryRootAVL->primaryKey) > 0)
    {
        deletePrimaryAVL(primaryRootAVL->pRightPrimary, category, name);
    }
    else
    {
        primaryRootAVL->pSecondary = deleteSecondaryAVL(primaryRootAVL->pSecondary, name);
    }
}