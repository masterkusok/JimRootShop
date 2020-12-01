#include <string>
#include <stdlib.h>
#include <windows.h>
class User{
public:
        std::string login;
        std::string password;
        //1 - владелец 2 - покупатель
        int role;
        // айди че
        int id;

        User(){
            login = " ";
            password = " ";
            role = 0;
            id = 9999;
        }
};
