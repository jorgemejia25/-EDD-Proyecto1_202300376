#ifndef ACTIVO_H
#define ACTIVO_H

#include <string>

class Activo
{
private:
    std::string id;
    std::string nombre;
    std::string descripcion;
    bool rentado;
    int idUsuario;

public:
    Activo(const std::string &_nombre, const std::string &_descripcion);

    std::string getId() const;
    std::string getNombre() const;
    std::string getDescripcion() const;
    int getIdUsuario() const;
    bool getRentado() const;

    void setId(int _id);
    void setNombre(const std::string &_nombre);
    void setDescripcion(const std::string &_descripcion);
    void setIdUsuario(const int &_idUsuario);
    void setRentado(bool _rentado);

    std::string toString() const;
};

#endif // ACTIVO_H