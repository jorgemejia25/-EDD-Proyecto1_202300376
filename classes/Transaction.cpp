#include "Transaction.h"
#include "Usuario.h"
#include "Activo.h"
#include <random>
#include <chrono>

Transaction::Transaction(Usuario *user, Activo *asset, int days)
{
    this->user = user;
    this->asset = asset;
    this->status = true;
    this->id = generateId();
    this->days = days;
}

std::string Transaction::generateId()
{
    const std::string chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    std::string id;

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator(seed);
    std::uniform_int_distribution<int> distribution(0, chars.size() - 1);

    for (int i = 0; i < 15; i++)
    {
        id += chars[distribution(generator)];
    }

    return id;
}

std::string Transaction::getId() const
{
    return id;
}

int Transaction::getDays() const
{
    return days;
}

Usuario *Transaction::getUser() const
{
    return user;
}

Activo *Transaction::getAsset() const
{
    return asset;
}

bool Transaction::getStatus() const
{
    return status;
}

void Transaction::setStatus(bool status)
{
    this->status = status;
}
