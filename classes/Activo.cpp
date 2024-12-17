/**
 * @file Activo.cpp
 * @brief Implementación de la clase Activo que representa un activo rentable en el sistema
 */

#include "Activo.h"
#include <sstream>
#include <random>
#include <chrono>

/**
 * @brief Genera un identificador alfanumérico aleatorio
 * @return String de 15 caracteres alfanuméricos
 */
std::string generarIdAlfanumerico()
{
    const std::string caracteres = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    std::string id;

    // Inicializar generador de números aleatorios
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generador(seed);
    std::uniform_int_distribution<> distribucion(0, caracteres.length() - 1);

    // Generar ID de 15 caracteres
    for (int i = 0; i < 15; i++)
    {
        id += caracteres[distribucion(generador)];
    }

    return id;
}

/**
 * @brief Constructor de la clase Activo
 * @param _nombre Nombre del activo
 * @param _descripcion Descripción detallada del activo
 * @param _maxDias Número máximo de días que el activo puede ser rentado
 */
Activo::Activo(const std::string &_nombre, const std::string &_descripcion, int _maxDias)
    : nombre(_nombre), descripcion(_descripcion), maxDias(_maxDias)
{
    id = generarIdAlfanumerico();
    rentado = false;
}

// Getters
/**
 * @brief Obtiene el ID del activo
 * @return ID alfanumérico del activo
 */
std::string Activo::getId() const
{
    return id;
}

/**
 * @brief Obtiene el nombre del activo
 * @return Nombre del activo
 */
std::string Activo::getNombre() const
{
    return nombre;
}

/**
 * @brief Obtiene la descripción del activo
 * @return Descripción del activo
 */
std::string Activo::getDescripcion() const
{
    return descripcion;
}

/**
 * @brief Obtiene el ID del usuario que ha rentado el activo
 * @return ID del usuario que tiene el activo rentado
 */
int Activo::getIdUsuario() const
{
    return idUsuario;
}

/**
 * @brief Verifica si el activo está rentado
 * @return true si está rentado, false en caso contrario
 */
bool Activo::getRentado() const
{
    return rentado;
}

/**
 * @brief Obtiene el número máximo de días que el activo puede ser rentado
 * @return Número máximo de días
 */
int Activo::getMaxDias() const
{
    return maxDias;
}

// Setters
/**
 * @brief Establece el ID del activo
 * @param _id Nuevo ID para el activo
 */
void Activo::setId(int _id)
{
    id = _id;
}

/**
 * @brief Establece el nombre del activo
 * @param _nombre Nuevo nombre para el activo
 */
void Activo::setNombre(const std::string &_nombre)
{
    nombre = _nombre;
}

/**
 * @brief Establece la descripción del activo
 * @param _descripcion Nueva descripción para el activo
 */
void Activo::setDescripcion(const std::string &_descripcion)
{
    descripcion = _descripcion;
}

/**
 * @brief Establece el estado de renta del activo
 * @param _rentado true si está rentado, false en caso contrario
 */
void Activo::setRentado(bool _rentado)
{
    rentado = _rentado;
}

/**
 * @brief Establece el ID del usuario que renta el activo
 * @param _idUsuario ID del usuario que renta el activo
 */
void Activo::setIdUsuario(const int &_idUsuario)
{
    idUsuario = _idUsuario;
}

/**
 * @brief Establece el número máximo de días que el activo puede ser rentado
 * @param _maxDias Nuevo número máximo de días
 */
void Activo::setMaxDias(int _maxDias)
{
    maxDias = _maxDias;
}

/**
 * @brief Genera una representación en string del activo
 * @return String con la información del activo en formato legible
 */
std::string Activo::toString() const
{
    std::stringstream ss;
    ss << "ID: " << id << "\n"
       << "Nombre: " << nombre << "\n"
       << "Descripción: " << descripcion << "\n"
       << "Rentado: " << (rentado ? "Sí" : "No") << "\n"
       << "Máx. Días: " << maxDias;
    return ss.str();
}