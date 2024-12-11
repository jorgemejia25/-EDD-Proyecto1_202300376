#ifndef MATRIZDISPERSA_H
#define MATRIZDISPERSA_H

#include <memory>
#include <string>
#include <ostream>
#include "Usuario.h"
#include "Activo.h"
#include "AVL.h"

class Nodo
{
public:
    std::shared_ptr<Usuario> usuario;
    std::shared_ptr<Nodo> izquierda, derecha, arriba, abajo, adelante, atras;

    explicit Nodo(const std::shared_ptr<Usuario> &usuario);
};

class NodoCabecera
{
public:
    std::string nombre;
    std::shared_ptr<NodoCabecera> siguiente;
    std::shared_ptr<Nodo> primerNodo;

    explicit NodoCabecera(const std::string &nombre);
};

class MatrizDispersa
{
private:
    std::shared_ptr<NodoCabecera> primerFila;
    std::shared_ptr<NodoCabecera> primerColumna;

    MatrizDispersa();

    static std::shared_ptr<MatrizDispersa> instancia;

    void escribirEncabezado(std::ostream &out, const std::string &NODE_STYLE);
    std::string procesarFilas(std::ostream &out, const std::string &NODE_STYLE);
    std::pair<std::string, std::string> procesarColumnas(std::ostream &out, const std::string &NODE_STYLE);
    void generarNodos(std::ostream &out, const std::string &NODE_STYLE);

    Nodo *buscarNodoEnPosicion(const std::shared_ptr<Nodo> &nodoFila,
                               const std::shared_ptr<Nodo> &nodoCol);

public:
    static std::shared_ptr<MatrizDispersa> obtenerInstancia();

    void insertar(const std::string &empresa, const std::string &departamento,
                  const std::shared_ptr<Usuario> &usuario);
    void mostrar();
    void generarDot(std::ostream &out);

    int obtenerFilaDeIdUsuario(int id);
    int obtenerColumnaDeIdUsuario(int id);

    Nodo *buscarNodoEnPosicionPorDepartamentoEmpresa(const std::string &empresa,
                                                     const std::string &departamento);

    Usuario *buscarUsuarioPorNombre(const std::string &nombre, const std::string &departamento,
                                    const std::string &empresa);

    void mostrarActivosDeMatriz(int userId);
    Activo *buscarActivosDeMatriz(const std::string &idActivp);
    AVL *arbolAVLDepartamentos(const std::string &departamento);
    AVL *arbolAVLEmpresas(const std::string &empresa);
};

#endif // MATRIZDISPERSA_H