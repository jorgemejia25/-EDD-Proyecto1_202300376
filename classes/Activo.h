#ifndef ACTIVO_H
#define ACTIVO_H

#include <string>

/**
 * @brief Clase que representa un activo del sistema
 *
 * Esta clase maneja la información de los activos que pueden ser rentados,
 * incluyendo su identificación, nombre, descripción y estado de renta.
 */
class Activo
{
private:
    std::string id;          ///< Identificador único del activo
    std::string nombre;      ///< Nombre del activo
    std::string descripcion; ///< Descripción detallada del activo
    bool rentado;            ///< Estado de renta del activo
    int idUsuario;           ///< ID del usuario que tiene rentado el activo

public:
    /**
     * @brief Constructor de la clase Activo
     * @param _nombre Nombre del activo
     * @param _descripcion Descripción del activo
     */
    Activo(const std::string &_nombre, const std::string &_descripcion);

    /**
     * @brief Obtiene el ID del activo
     * @return ID del activo
     */
    std::string getId() const;

    /**
     * @brief Obtiene el nombre del activo
     * @return Nombre del activo
     */
    std::string getNombre() const;

    /**
     * @brief Obtiene la descripción del activo
     * @return Descripción del activo
     */
    std::string getDescripcion() const;

    /**
     * @brief Obtiene el ID del usuario que rentó el activo
     * @return ID del usuario
     */
    int getIdUsuario() const;

    /**
     * @brief Verifica si el activo está rentado
     * @return true si está rentado, false si no
     */
    bool getRentado() const;

    /**
     * @brief Establece el ID del activo
     * @param _id Nuevo ID
     */
    void setId(int _id);

    /**
     * @brief Establece el nombre del activo
     * @param _nombre Nuevo nombre
     */
    void setNombre(const std::string &_nombre);

    /**
     * @brief Establece la descripción del activo
     * @param _descripcion Nueva descripción
     */
    void setDescripcion(const std::string &_descripcion);

    /**
     * @brief Establece el ID del usuario que renta el activo
     * @param _idUsuario Nuevo ID de usuario
     */
    void setIdUsuario(const int &_idUsuario);

    /**
     * @brief Establece el estado de renta del activo
     * @param _rentado Nuevo estado de renta
     */
    void setRentado(bool _rentado);

    /**
     * @brief Convierte la información del activo a string
     * @return String con la información del activo
     */
    std::string toString() const;
};

#endif // ACTIVO_H