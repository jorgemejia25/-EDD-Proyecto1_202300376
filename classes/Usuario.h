// Usuario.h
#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include "AVL.h"

class Usuario
{
public:
    std::string Nombre;
    std::string Password;
    int id;
    AVL *activos;

    Usuario(const std::string &nombre, const std::string &password); // Solo declaración
    ~Usuario();

    void agregarActivo(const Activo &activo);
    Activo *buscarActivo(const std::string &id);
    void mostrarActivos() const;
    void eliminarActivo(const std::string &id);
};

#endif // USUARIO_H
