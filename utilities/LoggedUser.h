#ifndef LOGGED_USER_H
#define LOGGED_USER_H

#include "../classes/Usuario.h"
#include <memory>

/**
 * @brief Clase Singleton que gestiona el usuario actualmente autenticado
 * 
 * Esta clase implementa el patrón de diseño Singleton para mantener
 * una única instancia que controla el usuario que ha iniciado sesión
 * en el sistema. Proporciona métodos para gestionar el estado de la
 * autenticación del usuario.
 */
class LoggedUser
{
private:
    static LoggedUser *instance;  ///< Instancia única de la clase
    Usuario *currentUser;         ///< Usuario actualmente autenticado

    /**
     * @brief Constructor privado del Singleton
     * 
     * Se mantiene privado para evitar instanciación directa,
     * siguiendo el patrón Singleton.
     */
    LoggedUser();

public:
    // Prevenir copias del singleton
    LoggedUser(const LoggedUser &) = delete;
    LoggedUser &operator=(const LoggedUser &) = delete;

    /**
     * @brief Obtiene la instancia única de LoggedUser
     * @return Puntero a la única instancia de LoggedUser
     */
    static LoggedUser *getInstance();

    /**
     * @brief Establece el usuario que ha iniciado sesión
     * @param user Puntero al usuario que inicia sesión
     */
    void setCurrentUser(Usuario *user);

    /**
     * @brief Obtiene el usuario actual que ha iniciado sesión
     * @return Puntero al usuario actual o nullptr si no hay sesión
     */
    Usuario *getCurrentUser();

    /**
     * @brief Verifica si existe un usuario con sesión activa
     * @return true si hay un usuario autenticado, false en caso contrario
     */
    bool isUserLogged();

    /**
     * @brief Cierra la sesión del usuario actual
     */
    void logout();
};

#endif // LOGGED_USER_H