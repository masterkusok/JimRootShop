#include "Header.h"
#include <iostream>
#include <QMessageBox>
#include <string>
int getNumberOfUsers(){
    std::ifstream ReadFile;
    std::string temp;
    int n = 1;
    ReadFile.open("Files\\Users.csv");
    for(int i = 0;ReadFile.good();i++){
        getline(ReadFile,temp);
        if(!temp.empty()){
            n+=1;
        }
    }
    ReadFile.close();
    return n;
}
int getNumberOfGuitars(){
    std::ifstream ReadFile;
    int n = 1;
    ReadFile.open("Files/Guitars.csv");
    while(ReadFile.good()){
        Instrument current_guitar;
        std::string reader;

        std::getline(ReadFile, reader);
        current_guitar.brand = reader;

        std::getline(ReadFile, reader);
        current_guitar.shape = reader;

        std::getline(ReadFile, reader);
        current_guitar.name = reader;

        std::getline(ReadFile, reader);
        current_guitar.price = std::stoi(reader);

        std::getline(ReadFile, reader);
        current_guitar.material = reader;

        std::getline(ReadFile, reader);
        current_guitar.img_path = reader;

        int desc_str_num = 0;
        std::getline(ReadFile, reader);
        desc_str_num = std::stoi(reader);
        std::string description;

        for(int i = 0; i < desc_str_num; i++){
            std::getline(ReadFile, reader);
            description+=reader + "\n";
        }
        current_guitar.descritp = description;
        n += 1;
    }
    return n;
}
void ParseUsers(User Arr[]){
    std::ifstream ReadFile;
    ReadFile.open("Files\\Users.csv");
    int i = 0;
    std::string temp_role, temp_login, temp_password;
    while(ReadFile.good()){
        std::getline(ReadFile, temp_login, ' ');
        if(!temp_login.empty()){
            std::getline(ReadFile, temp_password, ' ');
            std::getline(ReadFile, temp_role, '\n');
            Arr[i].role = std::stoi(temp_role);
            Arr[i].id = i;
            Arr[i].login = temp_login;
            Arr[i].password = temp_password;
            i++;
        }
    }
    ReadFile.close();
}

std::vector<Instrument> ParseGuitars(){
    std::ifstream ReadFile;
    std::vector <Instrument> vect;
    ReadFile.open("Files/Guitars.csv");
    while(ReadFile.good()){
        Instrument current_guitar;
        std::string reader;

        std::getline(ReadFile, reader);
        current_guitar.brand = reader;

        std::getline(ReadFile, reader);
        current_guitar.shape = reader;

        std::getline(ReadFile, reader);
        current_guitar.name = reader;

        std::getline(ReadFile, reader);
        current_guitar.price = std::stoi(reader);

        std::getline(ReadFile, reader);
        current_guitar.material = reader;

        std::getline(ReadFile, reader);
        current_guitar.img_path = reader;

        int desc_str_num = 0;
        std::getline(ReadFile, reader);
        desc_str_num = std::stoi(reader);
        std::string description;

        for(int i = 0; i < desc_str_num; i++){
            std::getline(ReadFile, reader);
            description+=reader + "\n";
        }
        current_guitar.descritp = description;
        vect.push_back(current_guitar);
    }
    return vect;
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

std::vector <Instrument> findGuitars(std::vector <Instrument> vect_1, std::string key_word, std::string brand, std::string shape){
    std::vector<Instrument> vect_2;
    //перевод ключевого слова в нижний регистр ( что бы потом поиск осуществлялся без учета регистра)
    std::transform(key_word.begin(), key_word.end(), key_word.begin(), tolower);
    std::transform(brand.begin(), brand.end(), brand.begin(), tolower);
    std::transform(shape.begin(), shape.end(), shape.begin(), tolower);

    for(int i = 0; i < vect_1.size(); i++){
        //перевод всего остального в нижний регистр
        std::string lowerName = vect_1[i].name;
        std::string lowerBrand = vect_1[i].brand;
        std::string lowerDesc = vect_1[i].descritp;
        std::string lowerMat = vect_1[i].material;
        std::string lowerShape = vect_1[i].shape;
        std::transform(lowerName.begin(), lowerName.end(), lowerName.begin(), tolower);
        std::transform(lowerBrand.begin(), lowerBrand.end(), lowerBrand.begin(), tolower);
        std::transform(lowerDesc.begin(), lowerDesc.end(), lowerDesc.begin(), tolower);
        std::transform(lowerMat.begin(), lowerMat.end(), lowerMat.begin(), tolower);
        std::transform(lowerShape.begin(), lowerShape.end(), lowerShape.begin(), tolower);

        if(lowerName.find(key_word, 0) != std::string::npos || lowerBrand.find(key_word, 0) != std::string::npos||
           lowerDesc.find(key_word, 0) != std::string::npos || lowerMat.find(key_word, 0) != std::string::npos){
            if(!brand.empty() && !shape.empty()){

               if(lowerBrand.find(brand, 0) != std::string::npos && lowerShape.find(shape, 0) != std::string::npos ){
                    vect_2.push_back(vect_1[i]);
                }
            }
            else if(!brand.empty()&&shape.empty()){
                if(lowerBrand.find(brand, 0) != std::string::npos){
                    vect_2.push_back(vect_1[i]);
                }
            }

            else if(brand.empty()&&!shape.empty()){
                if(lowerShape.find(shape, 0) != std::string::npos){
                    vect_2.push_back(vect_1[i]);
                }
            }
            else{
                vect_2.push_back(vect_1[i]);
            }
        }
    }
    return vect_2;
}

void DeleteGuitar(Instrument guitar){
    std::vector<Instrument> Guitars = ParseGuitars();
    int index;
    //находим индекс гитары что бы потом ее убрать
    for(int i = 0; i < Guitars.size(); i++){
        if(Guitars[i].name == guitar.name){
            index = i;
            break;
        }
    }

    std::ifstream ReadFile;
    std::ofstream WriteFile;
    WriteFile.open("Files/Temp.csv");
    ReadFile.open("Files/Guitars.csv");
    for(int i = 0; ReadFile.good(); i++){
        std::string reader;
        if(i !=index){

            std::getline(ReadFile, reader);
            WriteFile << reader << std::endl;

            std::getline(ReadFile, reader);
            WriteFile << reader << std::endl;

            std::getline(ReadFile, reader);
            WriteFile << reader << std::endl;

            std::getline(ReadFile, reader);
            WriteFile << reader << std::endl;

            std::getline(ReadFile, reader);
            WriteFile << reader << std::endl;

            std::getline(ReadFile, reader);
            WriteFile << reader << std::endl;

            int desc_str_num = 0;
            std::getline(ReadFile, reader);
            desc_str_num = std::stoi(reader);
            WriteFile << reader << std::endl;
            for(int j = 0; j < desc_str_num; j++){
                std::getline(ReadFile, reader);
                if(i == Guitars.size()-1){
                    if(j == desc_str_num-1){
                        WriteFile << reader;
                    }
                    else{
                        WriteFile << reader<<std::endl;
                    }
                }
                else{
                    WriteFile << reader<<std::endl;
                }
            }

        }
        else{
            std::getline(ReadFile, reader);

            std::getline(ReadFile, reader);

            std::getline(ReadFile, reader);

            std::getline(ReadFile, reader);

            std::getline(ReadFile, reader);

            std::getline(ReadFile, reader);

            int desc_str_num = 0;
            std::getline(ReadFile, reader);
            desc_str_num = std::stoi(reader);
            for(int i = 0; i < desc_str_num; i++){
                std::getline(ReadFile, reader);
            }
        }
    }
    WriteFile.close();
    ReadFile.close();
    std::remove("Files/Guitars.csv");
    std::rename("Files/Temp.csv", "Files/Guitars.csv");
}
std::vector <std::string> getAllGuitarBrands(){
    std::vector <Instrument> Guitars = ParseGuitars();
    std::vector <std::string> allBrands;
    std::string temp_brand;
    for(int i = 0; i < Guitars.size(); i++){
        bool found = false;
        temp_brand = Guitars[i].brand;
        for(int j = 0; j < allBrands.size(); j++){
            if(allBrands[j] == temp_brand){
                found = true;
                break;
            }
        }
        if(!found){
            allBrands.push_back(temp_brand);
        }
    }

    return allBrands;
}

std::vector <std::string> getAllGuitarShapes(){
    std::vector <Instrument> Guitars = ParseGuitars();
    std::vector <std::string> allShapes;
    std::string temp_shape;
    for(int i = 0; i < Guitars.size(); i++){
        bool found = false;
        temp_shape = Guitars[i].shape;
        for(int j = 0; j < allShapes.size(); j++){
            if(allShapes[j] == temp_shape){
                found = true;
            }
        }
        if(!found){
            allShapes.push_back(temp_shape);
        }
    }
    return allShapes;
}
void DeleteUser(int user_index){
    int i = 0;
    std::vector <User> users;
    std::ifstream ReadFile;
    int number = getNumberOfUsers();
    ReadFile.open("Files\\Users.csv");
    while(i < number){
        User temp;
        if(i!=user_index){
            ReadFile >> temp.login;
            ReadFile >> temp.password;
            ReadFile >> temp.role;
            users.push_back(temp);
        }
        i++;
    }
    ReadFile.close();
    std::ofstream WriteFile;
    i =0;
    WriteFile.open("Files\\Temp.csv");
    while(i < users.size()){
        WriteFile <<users[i].login << " " << users[i].password << " " << users[i].role << std::endl;
        i++;
    }
    WriteFile.close();
    std::remove("Files\\Users.csv");
    std::rename("Files\\Temp.csv", "Files\\Users.csv");
}

void addGuitar(std::string Brand, std::string Shape, std::string Name, std::string Price, std::string Material, std::string Img_path, std::string Description){
    std::ofstream File;
    File.open("Files/Guitars.csv",std::ios::app);
    File << std::endl << Brand
         << std::endl << Shape
         << std::endl << Name
         << std::endl << Price
         << std::endl << Material
         << std::endl << Img_path
         << std::endl << "1"
         << std::endl << Description;
}
