// Usuario.h
#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include "AVL.h"

/**
 * @brief Clase que representa un usuario del sistema
 * @details Almacena la información básica del usuario y gestiona sus activos
 */
class Usuario
{
public:
    std::string Nombre;     ///< Nombre del usuario
    std::string Password;   ///< Contraseña del usuario
    int id;                 ///< Identificador único del usuario
    AVL *activos;          ///< Árbol AVL que almacena los activos del usuario

    /**
     * @brief Constructor de Usuario
     * @param nombre Nombre del usuario
     * @param password Contraseña del usuario
     */
    Usuario(const std::string &nombre, const std::string &password);
    
    /**
     * @brief Destructor de Usuario
     */
    ~Usuario();

    /**
     * @brief Agrega un nuevo activo al árbol AVL del usuario
     * @param activo Activo a agregar
     */
    void agregarActivo(const Activo &activo);

    /**
     * @brief Busca un activo por su ID
     * @param id ID del activo a buscar
     * @return Puntero al activo encontrado o nullptr si no existe
     */
    Activo *buscarActivo(const std::string &id);

    /**
     * @brief Muestra todos los activos del usuario en orden
     */
    void mostrarActivos() const;

    /**
     * @brief Elimina un activo por su ID
     * @param id ID del activo a eliminar
     */
    void eliminarActivo(const std::string &id);
};

#endif // USUARIO_H
