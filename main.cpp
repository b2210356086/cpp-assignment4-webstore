#include "utility.h"
#include "tree_avl.h"
#include "tree_rb.h"

int main(int argc, char* argv[])
{
    PrimaryNodeAVL* primaryAVL = nullptr; //Create a Primary Tree for AVL Model, Currently Empty
    PrimaryNodeRB* primaryRB = nullptr; //Create a Primary Tree for Red-Black Model, Currently Empty

    std::ofstream outputFileAVL(argv[2]); //Output File for AVL Model Created
    std::ofstream outputFileRB(argv[3]); //Output File for Red-Black Model Created
    
    std::ifstream inputFile(argv[1]);
    std::string line;
    std::string command;
    int index;
    
    if(inputFile.is_open())
    {
        while(getline(inputFile, line)) //Operate on input file line by line, at each line commands are executed twice, once for AVL model and once for Red-Black model
        {
            index = line.find('\t');
            command = line.substr(0,index);
            if(command == "printAllItems" || command == "printAllItemsInCategory" || command == "printItem" || command == "find")
            {
                outputFileAVL << "command:" << line << '\n';
                outputFileRB << "command:" << line << '\n';
            }
            if(command == "insert")
            {
                line = line.substr(index + 1, line.length());
                index = line.find('\t');
                std::string category = line.substr(0, index);
                line = line.substr(index + 1, line.length());
                reverseString(line);
                index = line.find('\t');
                std::string reversedPrice = line.substr(0,index);
                std::string reversedName = line.substr(index + 1, line.length());
                reverseString(reversedPrice);
                int price = std::stoi(reversedPrice);
                reverseString(reversedName);
                std::string name = reversedName;
                insertPrimaryAVL(primaryAVL, category, name, price);
                insertPrimaryRB(primaryRB, category, name, price);
                continue;
            }
            if(command == "remove")
            {
                line = line.substr(index + 1, line.length());
                index = line.find('\t');
                std::string category = line.substr(0, index);
                std::string name = line.substr(index + 1, line.length());
                deletePrimaryAVL(primaryAVL, category, name);
                deletePrimaryRB(primaryRB, category, name);
                continue;
            }
            if(command == "printAllItems")
            {
                printAllItems(primaryAVL, outputFileAVL);
                printAllItems(primaryRB, outputFileRB);
                continue;
            }
            if(command == "printAllItemsInCategory")
            {
                std::string category = line.substr(index + 1, line.length());
                printAllItemsInCategory(primaryAVL, category, outputFileAVL);
                printAllItemsInCategory(primaryRB, category, outputFileRB);
                continue;
            }
            if(command == "printItem" || command == "find")
            {
                line = line.substr(index + 1, line.length());
                index = line.find('\t');
                std::string category = line.substr(0, index);
                std::string name = line.substr(index + 1, line.length());
                find(primaryAVL, category, name, outputFileAVL);
                find(primaryRB, category, name, outputFileRB);
                continue;
            }
            if(command == "updateData")
            {
                line = line.substr(index + 1, line.length());
                index = line.find('\t');
                std::string category = line.substr(0, index);
                line = line.substr(index + 1, line.length());
                reverseString(line);
                index = line.find('\t');
                std::string reversedPrice = line.substr(0,index);
                std::string reversedName = line.substr(index + 1, line.length());
                reverseString(reversedPrice);
                int price = std::stoi(reversedPrice);
                reverseString(reversedName);
                std::string name = reversedName;
                updateData(primaryAVL, category, name, price);
                updateData(primaryRB, category, name, price);
                continue;
            }
        }
        inputFile.close();
    }
    
    if(outputFileAVL.is_open())
    {
        outputFileAVL.close();
    }
    if(outputFileRB.is_open())
    {
        outputFileRB.close();
    }
    
    return 0;
}