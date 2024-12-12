#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include "Usuario.h"
#include "Activo.h"

/**
 * @brief Clase que representa una transacción en el sistema
 * @details Gestiona el préstamo de activos entre usuarios
 */
class Transaction
{
private:
    std::string id;    ///< Identificador único de la transacción
    Usuario *user;     ///< Usuario que realiza la transacción
    Activo *asset;     ///< Activo involucrado en la transacción
    int days;          ///< Duración en días de la transacción
    bool status;       ///< Estado de la transacción (activa/inactiva)

    /**
     * @brief Genera un ID único aleatorio para la transacción
     * @return String con el ID generado
     */
    std::string generateId();

public:
    /**
     * @brief Constructor de Transaction
     * @param user Usuario que realiza la transacción
     * @param asset Activo involucrado
     * @param days Duración en días
     */
    Transaction(Usuario *user, Activo *asset, int days);

    // Getters
    std::string getId() const;     ///< Obtiene el ID de la transacción
    Usuario *getUser() const;      ///< Obtiene el usuario asociado
    Activo *getAsset() const;      ///< Obtiene el activo asociado
    int getDays() const;           ///< Obtiene la duración en días
    bool getStatus() const;        ///< Obtiene el estado de la transacción

    /**
     * @brief Modifica el estado de la transacción
     * @param status Nuevo estado
     */
    void setStatus(bool status);
};

#endif
