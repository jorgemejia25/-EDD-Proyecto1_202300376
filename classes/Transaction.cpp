#include "Transaction.h"
#include "Usuario.h"
#include "Activo.h"
#include <random>
#include <chrono>

/**
 * @brief Constructor de la clase Transaction
 * @param user Puntero al usuario que realiza la transacción
 * @param asset Puntero al activo involucrado
 * @param days Número de días de la transacción
 */
Transaction::Transaction(Usuario *user, Activo *asset, int days)
{
    this->user = user;
    this->asset = asset;
    this->status = true;
    this->id = generateId();
    this->days = days;
}

/**
 * @brief Genera un ID aleatorio único para la transacción
 * @return String de 15 caracteres alfanuméricos
 */
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

/**
 * @brief Obtiene el ID de la transacción
 * @return ID de la transacción
 */
std::string Transaction::getId() const
{
    return id;
}

/**
 * @brief Obtiene la duración en días de la transacción
 * @return Número de días
 */
int Transaction::getDays() const
{
    return days;
}

/**
 * @brief Obtiene el usuario asociado a la transacción
 * @return Puntero al usuario
 */
Usuario *Transaction::getUser() const
{
    return user;
}

/**
 * @brief Obtiene el activo asociado a la transacción
 * @return Puntero al activo
 */
Activo *Transaction::getAsset() const
{
    return asset;
}

/**
 * @brief Obtiene el estado actual de la transacción
 * @return true si está activa, false si no
 */
bool Transaction::getStatus() const
{
    return status;
}

/**
 * @brief Actualiza el estado de la transacción
 * @param status Nuevo estado de la transacción
 */
void Transaction::setStatus(bool status)
{
    this->status = status;
}
