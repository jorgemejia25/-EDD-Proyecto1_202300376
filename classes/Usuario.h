#ifndef USUARIO_H
#define USUARIO_H

#include <string>

class Usuario
{
public:
    std::string Nombre;
    std::string Password;

    Usuario(const std::string &nombre, const std::string &password);
};

#endif // USUARIO_H