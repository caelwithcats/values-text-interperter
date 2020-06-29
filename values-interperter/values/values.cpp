#include "values.h"

bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

std::string getStringFromVariable(std::string str){
    str.erase(remove(str.begin(), str.end(), '\"'),str.end());
    return str;
}
int getIntFromVariable(std::string str){
    return std::stoi(str);
}

std::string getTypeOfVariable(std::string str){
    if(is_number(str)){
        return "number";
    }else{
        return "words";
    }
}

void saveValues(std::map<std::string, VariableClass> &variables, std::string path){
    std::string toSave = "#start\n";
    std::map<std::string, VariableClass>::iterator it = variables.begin();
    while (it != variables.end()){ 
        if(it->second.varType == "words"){
        toSave += "$" + it->first + "=" + "\"" + std::any_cast<std::string>(it->second.varData) + "\"" + "," + "\n";
        }else if(it->second.varType == "number"){
        toSave += "$" + it->first + "=" + std::to_string(std::any_cast<int>(it->second.varData)) + "," + "\n";
        }
        it++;
    }
    toSave += "\n#end";
    std::cout << toSave << std::endl;
    std::ofstream outfile;
    outfile.open(path);
    outfile << toSave;
    outfile.close();
}

void loadValues(std::map<std::string, VariableClass> &variables, std::string path){
    std::string source;
    /*std::string source = R"(//Comment
#start
//comment2
$valueString="Hello values",
$valueInt=54,
#end
    )";*/
    std::ifstream file(path);
    std::stringstream buffer;
    buffer << file.rdbuf();
    source = buffer.str();
    char lastChar;
    bool skip = false;
    for(int i = 0; i < source.length() - 1; i++){
        if(!skip){
        if(source.at(i) == '/' && lastChar == '/'){
            //the line is a comment and should be skipped
            std::cout << "comment found" << std::endl;
            skip = true;
        }else if(source.at(i) == '#'){
            int it = 1;
            std::string s;
            while(true){
                if(source.at(i + it) == '\n'){
                    break;
                }
                s += source.at(i + it);
                it++;
            }
            i = i + it;
            if(s == "start"){
                std::cout << "Start opening found" << std::endl;
            }else if(s == "end"){
                std::cout << "End closing found" << std::endl;
            }
        }else if(source.at(i) == '$'){
            std::string variableName;
            std::string variableValue;
            int it = 1;
            while(true){
                if(source.at(i + it) == '='){
                    break;
                }
                variableName += source.at(i + it);
                it++;
            }
            i = i + it;
            it = 1;

            while(true){
                if(source.at(i + it) == ','){
                    break;
                }
                variableValue += source.at(i + it);
                it++;
            }
            i = i + it;
            std::string variableType = getTypeOfVariable(variableValue);
            if(variableType == "words"){
            variableValue = getStringFromVariable(variableValue);
            VariableClass v;
            v.varData = getStringFromVariable(variableValue);
            v.varType = "words";
            variables[variableName] = v;
            }else if(variableType == "number")
            {
                VariableClass v;
                v.varData = getIntFromVariable(variableValue);
                v.varType = "number";
                variables[variableName] = v;
            }
            
            std::cout << "Variable with the name " << variableName << " with the value " << variableValue << std::endl;
        }
        if(source.at(i) != '/' && source.at(i) != ','){
        std::cout << source.at(i);
        }
        lastChar = source.at(i);
        }
        if(source.at(i) == '\n'){
            skip = false;
        }

    }
}
