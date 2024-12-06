#ifndef MATRIZDISPERSA_H
#define MATRIZDISPERSA_H

#include <memory>
#include <string>
#include "Usuario.h"

class Nodo {
public:
    std::shared_ptr<Usuario> usuario;
    std::shared_ptr<Nodo> izquierda, derecha, arriba, abajo, adelante, atras;

    explicit Nodo(const std::shared_ptr<Usuario> &usuario);
};

class NodoCabecera {
public:
    std::string nombre;
    std::shared_ptr<NodoCabecera> siguiente;
    std::shared_ptr<Nodo> primerNodo;

    explicit NodoCabecera(const std::string &nombre);
};

/**
 * @brief 3D sparse matrix for user management
 */
class MatrizDispersa {
private:
    std::shared_ptr<NodoCabecera> primerFila;
    std::shared_ptr<NodoCabecera> primerColumna;

    std::pair<std::shared_ptr<NodoCabecera>, bool> 
    obtenerOCrearCabecera(std::shared_ptr<NodoCabecera>&, const std::string&);
    
    void insertarEnDimension(std::shared_ptr<Nodo>&, std::shared_ptr<Nodo>,
                            std::shared_ptr<Nodo> Nodo::*, std::shared_ptr<Nodo> Nodo::*);

    // Constructor privado para el patrón Singleton
    MatrizDispersa();

    // Instancia estática de la clase
    static std::shared_ptr<MatrizDispersa> instancia;

public:
    // Función estática para obtener la instancia única
    static std::shared_ptr<MatrizDispersa> obtenerInstancia();

    void insertar(const std::string &departamento, const std::string &empresa, 
                 const std::shared_ptr<Usuario> &usuario);
    void mostrar();
};

#endif // MATRIZDISPERSA_H