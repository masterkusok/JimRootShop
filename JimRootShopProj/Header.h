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
int getNumberOfUsers();
int getNumberOfGuitars(Instrument Arr[]);
//функция для вытаскивания юзеров из файла (я между прочим создал класс для юзеров, ага да ага ага а? А? видишь не нужны вонючие матрицы здесь)
void ParseUsers(User Arr[]);
//функция для поиска совпадений по логину и паролю, потом она будет изменяться так что не трогай ее
int CheckUsers(User Arr[], std::string password, std::string login);
//Функция для получения всей информации о пользователе по логину и паролю
User getUserInformationByLoginAndPassword(std::string login,std::string password);
//функция для парса гитар
void ParseGuitars(Instrument Arr[]);
//
void findGuitars(Instrument arr_1[], Instrument arr_2[], std::string key_word);
#endif // HEADER_H
