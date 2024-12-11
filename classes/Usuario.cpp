// Usuario.cpp
#include "Usuario.h"

Usuario::Usuario(const std::string &nombre, const std::string &password)
    : Nombre(nombre), Password(password), activos(new AVL()) {}

Usuario::~Usuario()
{
    delete activos;
}

void Usuario::agregarActivo(const Activo &activo)
{
    activos->insertar(activo);
}

Activo *Usuario::buscarActivo(const std::string &id)
{
    return activos->buscar(id);
}

void Usuario::mostrarActivos() const
{
    activos->inorden();
}

void Usuario::eliminarActivo(const std::string &id)
{
    activos->eliminar(id);
}