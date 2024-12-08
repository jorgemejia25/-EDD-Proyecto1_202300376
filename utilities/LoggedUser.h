#ifndef LOGGED_USER_H
#define LOGGED_USER_H

#include "../classes/Usuario.h"
#include <memory>

class LoggedUser
{
private:
    static LoggedUser *instance;
    Usuario *currentUser;

    // Constructor privado para singleton
    LoggedUser();

public:
    // Prevenir copias del singleton
    LoggedUser(const LoggedUser &) = delete;
    LoggedUser &operator=(const LoggedUser &) = delete;

    // Métodos públicos
    static LoggedUser *getInstance();
    void setCurrentUser(Usuario *user);
    Usuario *getCurrentUser();
    bool isUserLogged();
    void logout();
};

#endif // LOGGED_USER_H