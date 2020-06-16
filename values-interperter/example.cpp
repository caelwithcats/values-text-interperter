#include "values/values.h"

int main(){
    std::map<std::string, VariableClass> variables;
    loadValues(variables,"example/values.vls");

    std::cout << std::endl;
    std::string value;
    std::string typeValue = variables["valueString"].varType;
    if(typeValue == "words"){
        value = std::any_cast<std::string>(variables["valueString"].varData);
    }
    variables["valueString"].varData = std::string("hi");
    std::cout << value << std::endl;
    saveValues(variables,"example/output.vls");
}
