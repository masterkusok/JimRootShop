#include "Header.h"
#include <iostream>
#include <QMessageBox>
int getNumberOfUsers(){
//    for(int i = 0; i < 100; i++){
//        if(Arr[i].login == " "){
//            return i;
//        }
//    }
    std::ifstream ReadFile;
    std::string temp;
    int n;
    ReadFile.open("Files\\Users.csv");
    for(int i = 0;ReadFile.good();i++){
        getline(ReadFile,temp,'\n');
        n = i + 1;
    }
    ReadFile.close();
    return n;
}

void ParseUsers(User Arr[]){
    std::ifstream ReadFile;
    ReadFile.open("Files\\Users.csv");
    int i = 0;
    std::string temp_role, temp_login, temp_password;
    while(ReadFile.good()){
        std::getline(ReadFile, temp_login, ' ');
        std::getline(ReadFile, temp_password, ' ');
        std::getline(ReadFile, temp_role, '\n');
        Arr[i].role = std::stoi(temp_role);
        Arr[i].id = i;
        Arr[i].login = temp_login;
        Arr[i].password = temp_password;
        i++;
    }
    ReadFile.close();
}

int CheckUsers(User Arr[], std::string password, std::string login){
    bool checking = true;
    for(int i = 0; i < getNumberOfUsers(); i++){
        if(Arr[i].login == login && Arr[i].password == password){
            checking = false;
            return Arr[i].role;
            break;
        }
    }
    if(checking){
        return 0;
    }
}
