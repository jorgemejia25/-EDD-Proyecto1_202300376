#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include "Usuario.h"
#include "Activo.h"

class Transaction
{
private:
    std::string id;
    Usuario *user;
    Activo *asset;
    int days;
    bool status;

    std::string generateId();

public:
    Transaction(Usuario *user, Activo *asset, int days);

    // Getters
    std::string getId() const;
    Usuario *getUser() const;
    Activo *getAsset() const;
    int getDays() const;
    bool getStatus() const;

    // Setters
    void setStatus(bool status);
};

#endif
