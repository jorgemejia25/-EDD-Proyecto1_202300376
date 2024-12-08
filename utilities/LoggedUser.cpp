#include <memory>
#include "../classes/Usuario.h"

class LoggedUser
{
private:
    static LoggedUser *instance;
    Usuario *currentUser;

    // Constructor privado
    LoggedUser() : currentUser(nullptr) {}

public:
    // Evitar copias del singleton
    LoggedUser(const LoggedUser &) = delete;
    LoggedUser &operator=(const LoggedUser &) = delete;

    static LoggedUser *getInstance()
    {
        if (instance == nullptr)
        {
            instance = new LoggedUser();
        }
        return instance;
    }

    void setCurrentUser(Usuario *user)
    {
        currentUser = user;
    }

    Usuario *getCurrentUser()
    {
        return currentUser;
    }

    bool isUserLogged()
    {
        return currentUser != nullptr;
    }

    void logout()
    {
        currentUser = nullptr;
    }
};

// Inicializar el miembro estático
LoggedUser *LoggedUser::instance = nullptr;