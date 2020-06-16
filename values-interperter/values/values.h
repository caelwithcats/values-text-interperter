#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <any>
#include <algorithm>

class VariableClass{
public:
    std::string varType;
    std::any varData;
};

bool is_number(const std::string& s);

std::string getStringFromVariable(std::string str);

int getIntFromVariable(std::string str);

std::string getTypeOfVariable(std::string str);

void saveValues(std::map<std::string, VariableClass> &variables, std::string path);

void loadValues(std::map<std::string, VariableClass> &variables, std::string path);
