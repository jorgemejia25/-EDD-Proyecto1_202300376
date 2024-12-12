/**
 * @file LoggedUser.h
 * @brief Implementación del patrón Singleton para gestionar el usuario actual del sistema
 */

#include <memory>
#include "../classes/Usuario.h"

/**
 * @class LoggedUser
 * @brief Clase que implementa el patrón Singleton para manejar el usuario actualmente logueado
 * @details Mantiene una única instancia del usuario que ha iniciado sesión en el sistema
 */
class LoggedUser
{
private:
    static LoggedUser* instance;    ///< Instancia única de la clase
    Usuario* currentUser;           ///< Puntero al usuario actual

    /**
     * @brief Constructor privado para implementar Singleton
     */
    LoggedUser() : currentUser(nullptr) {}

public:
    // Evitar copias del singleton
    LoggedUser(const LoggedUser&) = delete;
    LoggedUser& operator=(const LoggedUser&) = delete;

    /**
     * @brief Obtiene la instancia única de LoggedUser
     * @return Puntero a la instancia única de LoggedUser
     */
    static LoggedUser* getInstance()
    {
        if (instance == nullptr)
        {
            instance = new LoggedUser();
        }
        return instance;
    }

    /**
     * @brief Establece el usuario actual del sistema
     * @param user Puntero al usuario que inició sesión
     */
    void setCurrentUser(Usuario* user)
    {
        currentUser = user;
    }

    /**
     * @brief Obtiene el usuario actual del sistema
     * @return Puntero al usuario actual
     */
    Usuario* getCurrentUser()
    {
        return currentUser;
    }

    /**
     * @brief Verifica si hay un usuario con sesión iniciada
     * @return true si hay un usuario logueado, false en caso contrario
     */
    bool isUserLogged()
    {
        return currentUser != nullptr;
    }

    /**
     * @brief Cierra la sesión del usuario actual
     */
    void logout()
    {
        currentUser = nullptr;
    }
};

// Inicializar el miembro estático
LoggedUser* LoggedUser::instance = nullptr;
