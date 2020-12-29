#include "Header.h"
#include <iostream>
#include <QMessageBox>
int getNumberOfUsers(){
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

int getNumberOfGuitars(Instrument Arr[]){
    for(int i = 0; i < 30; i++){
        if(Arr[i].name == " "){
            return i;
            break;
        }
    }
}
void ParseGuitars(Instrument Arr[]){
    std::ifstream ReadFile;
        int num = 0;
        ReadFile.open("Files/guitars.csv");
        if (ReadFile.is_open()) {
            //переменная для хранения количества строк в описании гитары
            int num_of_desc_strings;
            //переменная для хранения строк из файла
            std::string reader;

            while (ReadFile.good()) {
                    //считываем и вносим бренд

                std::getline(ReadFile, reader);
                if (reader == "") {
                    break;
                }
                else {
                    Arr[num].brand = reader;

                    //считываем и вносим форму
                    std::getline(ReadFile, reader);
                    Arr[num].shape = reader;

                    //считываем и вносим название модели
                    std::getline(ReadFile, reader);
                    Arr[num].name = reader;

                    //считываем и вносим прайс
                    std::getline(ReadFile, reader);
                    Arr[num].price = std::stoi(reader);

                    //считываем и вносим материал
                    std::getline(ReadFile, reader);
                    Arr[num].material = reader;

                    //считываем и вносим путь к изображению
                    std::getline(ReadFile, reader);
                    Arr[num].img_path = reader;

                    //получаем количество строк и считываем описание
                    std::string full_description;

                    std::getline(ReadFile, reader);
                    num_of_desc_strings = std::stoi(reader);
                    for (int i = 0; i < num_of_desc_strings; i++) {
                        std::getline(ReadFile, reader);
                        full_description = full_description+ reader + "\n";
                    }
                    Arr[num].descritp = full_description;
                    Arr[num].id = num;
                    num++;
                }

            }

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



User getUserInformationByLoginAndPassword(std::string login,std::string password){
    User user,Users[getNumberOfUsers()];
    ParseUsers(Users);
    for(int i = 0;i < getNumberOfUsers();i++){
        if(Users[i].login == login && Users[i].password == password){
            user.id = Users[i].id;
            user.login = Users[i].login;
            user.password = Users[i].password;
            user.role = Users[i].role;
        }
    }
    return user;
}

void findGuitars(Instrument arr_1[], Instrument arr_2[], std::string key_word){
    int number = getNumberOfGuitars(arr_1);
    int number_of_searched_guitars = 0;
    std::cout << key_word;
    for(int i = 0; i < number; i++){
        //спроси у Лады Андреевны как этот кал работает, а то нихера не понятно
        if(arr_1[i].name.find(key_word, 0) or arr_1[i].brand.find(key_word, 0) or arr_1[i].shape.find(key_word, 0)){
            arr_2[number_of_searched_guitars] = arr_1[i];
            number_of_searched_guitars++;
        }
    }
}
