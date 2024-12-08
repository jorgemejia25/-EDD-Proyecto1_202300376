#ifndef ACTIVO_H
#define ACTIVO_H

#include <string>

class Activo
{
private:
    std::string id;
    std::string nombre;
    std::string descripcion;

public:
    Activo(const std::string &_nombre, const std::string &_descripcion);

    std::string getId() const;
    std::string getNombre() const;
    std::string getDescripcion() const;

    void setId(int _id);
    void setNombre(const std::string &_nombre);
    void setDescripcion(const std::string &_descripcion);

    std::string toString() const;
};

#endif // ACTIVO_H