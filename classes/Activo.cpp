// Activo.cpp
#include "Activo.h"
#include <sstream>
#include <random>
#include <chrono>

// Función auxiliar para generar ID alfanumérico
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

// Constructor modificado
Activo::Activo(const std::string &_nombre, const std::string &_descripcion)
    : nombre(_nombre), descripcion(_descripcion)
{
    id = generarIdAlfanumerico();
    rentado = false;
}

// Getters
std::string Activo::getId() const
{
    return id;
}

std::string Activo::getNombre() const
{
    return nombre;
}

std::string Activo::getDescripcion() const
{
    return descripcion;
}

int Activo::getIdUsuario() const
{
    return idUsuario;
}

bool Activo::getRentado() const
{
    return rentado;
}

// Setters
void Activo::setId(int _id)
{
    id = _id;
}

void Activo::setNombre(const std::string &_nombre)
{
    nombre = _nombre;
}

void Activo::setDescripcion(const std::string &_descripcion)
{
    descripcion = _descripcion;
}

void Activo::setRentado(bool _rentado)
{
    rentado = _rentado;
}

void Activo::setIdUsuario(const int &_idUsuario)
{
    idUsuario = _idUsuario;
}

// toString
std::string Activo::toString() const
{
    std::stringstream ss;
    ss << "ID: " << id << "\n"
       << "Nombre: " << nombre << "\n"
       << "Descripción: " << descripcion;
    return ss.str();
}