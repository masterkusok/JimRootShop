#include "Header.h"

void ParseUsers(User Arr[]){
    std::ifstream ReadFile;
    ReadFile.open("Files/Users.csv");
    int i = 0;
    while(ReadFile.good()){
        std::getline(ReadFile, Arr[i].login, ' ');
        std::getline(ReadFile, Arr[i].password, ' ');
        std::string temp_role;
        std::getline(ReadFile, temp_role, ' ');
        Arr[i].role = std::stoi(temp_role);
        Arr[i].id = i;
        i++;
    }
}
