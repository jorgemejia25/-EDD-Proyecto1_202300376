// Usuario.cpp
#include "Usuario.h"

/**
 * @brief Constructor de la clase Usuario
 * @param nombre Nombre del usuario
 * @param password Contraseña del usuario
 */
Usuario::Usuario(const std::string &nombre, const std::string &password)
    : Nombre(nombre), Password(password), activos(new AVL()) {}

/**
 * @brief Destructor de la clase Usuario
 * Libera la memoria del árbol AVL de activos
 */
Usuario::~Usuario()
{
    delete activos;
}

/**
 * @brief Agrega un nuevo activo al árbol AVL del usuario
 * @param activo Activo a agregar
 */
void Usuario::agregarActivo(const Activo &activo)
{
    activos->insertar(activo);
}

/**
 * @brief Busca un activo por su ID
 * @param id ID del activo a buscar
 * @return Puntero al activo encontrado o nullptr si no existe
 */
Activo *Usuario::buscarActivo(const std::string &id)
{
    return activos->buscar(id);
}

/**
 * @brief Muestra todos los activos del usuario en orden
 */
void Usuario::mostrarActivos() const
{
    activos->inorden();
}

/**
 * @brief Elimina un activo del árbol AVL por su ID
 * @param id ID del activo a eliminar
 */
void Usuario::eliminarActivo(const std::string &id)
{
    activos->eliminar(id);
}