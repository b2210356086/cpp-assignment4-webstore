#ifndef UTILITY_H
#define UTILITY_H

#include <fstream>
#include <iostream>
#include <queue>

inline int max(int a, int b) //Returns maximum of two integers
{
    return (a > b) ? a : b;
}

inline void reverseString(std::string &str) //Reverses a string
{
    int n = str.length();
    for (int i = 0; i < n / 2; i++)
        std::swap(str[i], str[n - i - 1]);
}

template <typename secondaryT> secondaryT* leftMostNode(secondaryT* node) //Returns left-most child
{
    secondaryT* temp = node;
    while(temp->pLeft != nullptr)
    {
        temp = temp->pLeft;
    }
    return temp;
}

template <typename secondaryT> void updateDataHelper(secondaryT* &secondaryRoot, std::string name, int newPrice) //Recursively updates the price of an item in the secondary tree
{
    if(secondaryRoot == nullptr)
    {
        return;
    }
    
    if(name.compare(secondaryRoot->key) < 0)
    {
        updateDataHelper(secondaryRoot->pLeft, name, newPrice);
    }
    else if(name.compare(secondaryRoot->key) > 0)
    {
        updateDataHelper(secondaryRoot->pRight, name, newPrice);
    }
    else
    {
        secondaryRoot->price = newPrice;
    }
}

template <typename primaryT> void updateData(primaryT* &primaryRoot, std::string category, std::string name, int newPrice) //Recursively finds the secondary tree of the item to be updated
{
    if(primaryRoot == nullptr)
    {
        return;
    }
    
    if(category.compare(primaryRoot->primaryKey) < 0)
    {
        updateData(primaryRoot->pLeftPrimary, category, name, newPrice);
    }
    else if(category.compare(primaryRoot->primaryKey) > 0)
    {
        updateData(primaryRoot->pRightPrimary, category, name, newPrice);
    }
    else
    {
        updateDataHelper(primaryRoot->pSecondary, name, newPrice);
    }
}

template <typename secondaryT> void findSecondary(secondaryT* secondaryRoot, std::string category, std::string name, bool &isFound, std::ofstream &outputFile) //Recursively checks if an item with given name exists in a secondary tree
{
    if(secondaryRoot == nullptr)
    {
        return;
    }
    
    if(name.compare(secondaryRoot->key) < 0)
    {
        findSecondary(secondaryRoot->pLeft, category, name, isFound, outputFile);
    }
    else if(name.compare(secondaryRoot->key) > 0)
    {
        findSecondary(secondaryRoot->pRight, category, name, isFound, outputFile);
    }
    else
    {
        isFound = true;
        outputFile << "{\n\"" << category << "\":\n\t\"" << name << "\":\"" << secondaryRoot->price << "\"\n}\n";
    }
}

template <typename primaryT> void findPrimary(primaryT* primaryRoot, std::string category, std::string name, bool &isFound, std::ofstream &outputFile) //Recursively checks if a category exists in a primary tree
{
    if(primaryRoot == nullptr)
    {
        return;
    }
    
    if(category.compare(primaryRoot->primaryKey) < 0)
    {
        findPrimary(primaryRoot->pLeftPrimary, category, name, isFound, outputFile);
    }
    else if(category.compare(primaryRoot->primaryKey) > 0)
    {
        findPrimary(primaryRoot->pRightPrimary, category, name, isFound, outputFile);
    }
    else
    {
        findSecondary(primaryRoot->pSecondary, category, name, isFound, outputFile);
    }
}

template <typename primaryT> void find(primaryT* primaryRoot, std::string category, std::string name, std::ofstream &outputFile) //Checks if the item with given category and name information exists
{
    bool isFound = false;
    findPrimary(primaryRoot, category, name, isFound, outputFile);
    if(!isFound)
    {
        outputFile << "{}\n";
    }
}

template <typename secondaryT> void printSecondaryHelper(secondaryT* secondaryRoot, std::string category, bool &isFound, std::ofstream &outputFile) //Prints content of a secondary tree level by level by using breadth first traversal
{
    if(secondaryRoot == nullptr)
    {
        return;
    }
    isFound = true;
    outputFile << '\"' << category << "\":\n";
    
    std::queue<secondaryT*> q;
    q.push(secondaryRoot);
    while(q.empty() == false)
    {
        int level = q.size();
        int originalLevel = level;
        while(level > 0)
        {
            secondaryT* temp = q.front();
            q.pop();
            
            if(level == 1)
            {
                if(level == originalLevel)
                {
                    outputFile << '\t';
                }
                outputFile << "\"" << temp->key << "\":\"" << temp->price << "\"\n";
            }
            if(level != 1)
            {
                if(level == originalLevel)
                {
                    outputFile << '\t';
                }
                outputFile << "\"" << temp->key << "\":\"" << temp->price << "\",";
            }

            if(temp->pLeft != nullptr)
            {
                q.push(temp->pLeft);
            }
            if(temp->pRight != nullptr)
            {
                q.push(temp->pRight);
            }
            level--;
        }
    }
}

template <typename primaryT> void printCategoryHelper(primaryT* primaryRoot, std::string category, bool &isFound, std::ofstream &outputFile) //Finds the secondary tree to be printed
{
    if(primaryRoot == nullptr)
    {
        return;
    }
    if(category.compare(primaryRoot->primaryKey) < 0)
    {
        printCategoryHelper(primaryRoot->pLeftPrimary, category, isFound, outputFile);
    }
    else if(category.compare(primaryRoot->primaryKey) > 0)
    {
        printCategoryHelper(primaryRoot->pRightPrimary, category, isFound, outputFile);
    }
    else
    {
        if(primaryRoot->pSecondary != nullptr)
        {
            outputFile << "{\n";
        }
        printSecondaryHelper(primaryRoot->pSecondary, category, isFound, outputFile);
        if(primaryRoot->pSecondary != nullptr)
        {
            outputFile << "}\n";
        }
    }
}

template <typename primaryT> void printAllItems(primaryT* primaryRoot, std::ofstream &outputFile) //Prints all the items in the primary tree and corresponding secondary trees level by level, breadth first traversal is used
{
    if(primaryRoot == nullptr)
    {
        outputFile << "{}\n";
        return;
    }
    outputFile << "{\n";
    std::queue<primaryT*> q;
    q.push(primaryRoot);
    while(q.empty() == false)
    {
        bool isFound = false;
        primaryT* temp = q.front();
        q.pop();
        printSecondaryHelper(temp->pSecondary, temp->primaryKey, isFound, outputFile);
        if(temp->pLeftPrimary != nullptr)
        {
            q.push(temp->pLeftPrimary);
        }
        if(temp->pRightPrimary != nullptr)
        {
            q.push(temp->pRightPrimary);
        }
        if(!isFound)
        {
            outputFile << "\"" << temp->primaryKey << "\":{}\n";
        }
    }
    outputFile << "}\n";
}

template <typename primaryT> void printAllItemsInCategory(primaryT* primaryRoot, std::string category, std::ofstream &outputFile) //Checks if a category exists with given category name and prints all items of that category
{
    bool isFound = false;
    if(primaryRoot == nullptr)
    {
        outputFile << "{}\n";
        return;
    }
    printCategoryHelper(primaryRoot, category, isFound, outputFile);
    if(!isFound)
    {
        outputFile << "{\n\"" << category << "\":{}\n}\n";
    }
}

#endif