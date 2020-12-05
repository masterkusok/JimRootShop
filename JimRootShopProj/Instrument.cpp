#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdlib.h>
#include <string>

class Instrument {
    public:
        std::string brand;
        std::string shape;
        std::string name;
        std::string img_path;
        int price;
        std::string material;
        std::string descritp;
        int id;
    //конструктор по умолчанию
        Instrument() {
            brand = " ";
            shape = " ";
            name = " ";
            img_path = " ";
            price = 0;
            material = " ";
            descritp = " ";
            id = 99999999;
        }
    /* я внезапно понял что этот конструктор не особо нужен но на всякий случай пусть тут лежит
         Instrument(std::string brand_temp, std::string shape_temp, std::string name_temp, int price_temp, std::string material_temp,
            std::string descript_temp, int id_temp) {
            brand = brand_temp;
            shape = shape_temp;
            name = name_temp;
            price = price_temp;
            material = material_temp;
            descritp = descript_temp;
            id = id_temp;
        }
        */
};
