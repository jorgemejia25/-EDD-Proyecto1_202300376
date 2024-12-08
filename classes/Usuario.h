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
    AVL *activos; // Árbol AVL para almacenar los activos del usuario

    Usuario(const std::string &nombre, const std::string &password)
        : Nombre(nombre), Password(password), activos(new AVL()) {}

    ~Usuario()
    {
        delete activos;
    }

    // Métodos para manipular los activos
    void agregarActivo(const Activo &activo)
    {
        activos->insertar(activo);
    }

    Activo *buscarActivo(const std::string &id)
    {
        return activos->buscar(id);
    }

    void mostrarActivos() const
    {
        activos->inorden();
    }
};

#endif // USUARIO_H