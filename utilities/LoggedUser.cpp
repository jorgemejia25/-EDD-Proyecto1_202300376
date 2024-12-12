#include <memory>
#include "../classes/Usuario.h"

/**
 * @brief Clase Singleton que maneja el usuario actualmente autenticado en el sistema
 * 
 * Esta clase implementa el patrón Singleton para mantener una única instancia
 * que gestiona el usuario que ha iniciado sesión en la aplicación.
 */
class LoggedUser
{
private:
    static LoggedUser *instance;
    Usuario *currentUser;

    /**
     * @brief Constructor privado para implementar el patrón Singleton
     */
    LoggedUser() : currentUser(nullptr) {}

public:
    // Evitar copias del singleton
    LoggedUser(const LoggedUser &) = delete;
    LoggedUser &operator=(const LoggedUser &) = delete;

    /**
     * @brief Obtiene la instancia única de LoggedUser
     * @return Puntero a la instancia única de LoggedUser
     */
    static LoggedUser *getInstance()
    {
        if (instance == nullptr)
        {
            instance = new LoggedUser();
        }
        return instance;
    }

    /**
     * @brief Establece el usuario actual que ha iniciado sesión
     * @param user Puntero al usuario que ha iniciado sesión
     */
    void setCurrentUser(Usuario *user)
    {
        currentUser = user;
    }

    /**
     * @brief Obtiene el usuario actual que ha iniciado sesión
     * @return Puntero al usuario actual o nullptr si no hay usuario autenticado
     */
    Usuario *getCurrentUser()
    {
        return currentUser;
    }

    /**
     * @brief Verifica si hay un usuario con sesión iniciada
     * @return true si hay un usuario autenticado, false en caso contrario
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
LoggedUser *LoggedUser::instance = nullptr;