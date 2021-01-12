#ifndef HEADER_H
#define HEADER_H
#include <fstream>
#include <stdlib.h>
#include <windows.h>
#include <QWidget>
#include <QMainWindow>
#include <QApplication>
#include "User.cpp"
#include "Instrument.cpp"
#include <vector>
#include <iostream>
#include <ctype.h>
#include <algorithm>
int getNumberOfUsers();
int getNumberOfGuitars(Instrument Arr[]);
//функция для вытаскивания юзеров из файла (я между прочим создал класс для юзеров, ага да ага ага а? А? видишь не нужны вонючие матрицы здесь)
void ParseUsers(User Arr[]);
//функция для поиска совпадений по логину и паролю, потом она будет изменяться так что не трогай ее
int CheckUsers(User Arr[], std::string password, std::string login);
//Функция для получения всей информации о пользователе по логину и паролю
User getUserInformationByLoginAndPassword(std::string login,std::string password);
//функция для парса гитар
std::vector<Instrument> ParseGuitars();
//функция для поиска гитар
std::vector <Instrument> findGuitars(std::vector <Instrument> vect_1, std::string key_word, std::string brand, std::string shape);
//функция которая удаляет гитару
void DeleteGuitar(Instrument guitar);
//Функция, которая получает все формы бренды гитар (для реализации фильтров)
std::vector <std::string> getAllGuitarBrands();
//Тоже что и прошлое, но с формами
std::vector <std::string> getAllGuitarShapes();
#endif // HEADER_H
