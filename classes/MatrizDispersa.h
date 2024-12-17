#ifndef MATRIZDISPERSA_H
#define MATRIZDISPERSA_H

#include <memory>
#include <string>
#include <ostream>
#include "Usuario.h"
#include "Activo.h"
#include "AVL.h"

/**
 * @brief Clase que representa un nodo en la matriz dispersa
 */
class Nodo
{
public:
    std::shared_ptr<Usuario> usuario;
    std::shared_ptr<Nodo> izquierda, derecha, arriba, abajo, adelante, atras;

    /**
     * @brief Constructor del nodo
     * @param usuario Puntero compartido al usuario que contendrá el nodo
     */
    explicit Nodo(const std::shared_ptr<Usuario> &usuario);
};

/**
 * @brief Clase que representa un nodo cabecera de la matriz
 */
class NodoCabecera
{
public:
    std::string nombre;
    std::shared_ptr<NodoCabecera> siguiente;
    std::shared_ptr<Nodo> primerNodo;

    /**
     * @brief Constructor del nodo cabecera
     * @param nombre Identificador del nodo cabecera
     */
    explicit NodoCabecera(const std::string &nombre);
};

/**
 * @brief Clase que implementa una matriz dispersa utilizando el patrón Singleton
 */
class MatrizDispersa
{
private:
    std::shared_ptr<NodoCabecera> primerFila;
    std::shared_ptr<NodoCabecera> primerColumna;

    /**
     * @brief Constructor privado (patrón Singleton)
     */
    MatrizDispersa();

    static std::shared_ptr<MatrizDispersa> instancia;

    /**
     * @brief Métodos auxiliares para la generación del archivo DOT
     */
    void escribirEncabezado(std::ostream &out, const std::string &NODE_STYLE);
    std::string procesarFilas(std::ostream &out, const std::string &NODE_STYLE);
    std::pair<std::string, std::string> procesarColumnas(std::ostream &out, const std::string &NODE_STYLE);
    void generarNodos(std::ostream &out, const std::string &NODE_STYLE);
    std::shared_ptr<NodoCabecera> buscarFilaPorNodo(std::shared_ptr<Nodo> nodo);

    /**
     * @brief Busca un nodo en una posición específica
     * @param nodoFila Nodo de la fila
     * @param nodoCol Nodo de la columna
     * @return Puntero al nodo encontrado
     */
    Nodo *buscarNodoEnPosicion(const std::shared_ptr<Nodo> &nodoFila,
                               const std::shared_ptr<Nodo> &nodoCol);

public:
    /**
     * @brief Obtiene la instancia única de la matriz (Singleton)
     * @return Puntero compartido a la instancia de la matriz
     */
    static std::shared_ptr<MatrizDispersa> obtenerInstancia();

    /**
     * @brief Inserta un nuevo usuario en la matriz
     * @param empresa Nombre de la empresa
     * @param departamento Nombre del departamento
     * @param usuario Puntero compartido al usuario a insertar
     */
    void insertar(const std::string &empresa, const std::string &departamento,
                  const std::shared_ptr<Usuario> &usuario);

    /**
     * @brief Muestra la matriz en consola
     */
    void mostrar();

    /**
     * @brief Genera la representación gráfica de la matriz en formato DOT
     * @param out Stream de salida donde se escribirá el código DOT
     */
    void generarDot(std::ostream &out);

    /**
     * @brief Métodos de búsqueda y consulta
     */
    int obtenerFilaDeIdUsuario(int id);
    int obtenerColumnaDeIdUsuario(int id);

    /**
     * @brief Busca un nodo por departamento y empresa
     * @param empresa Nombre de la empresa
     * @param departamento Nombre del departamento
     * @return Puntero al nodo encontrado
     */
    Nodo *buscarNodoEnPosicionPorDepartamentoEmpresa(const std::string &empresa,
                                                     const std::string &departamento);

    /**
     * @brief Busca un usuario por nombre, departamento y empresa
     */
    Usuario *buscarUsuarioPorNombre(const std::string &nombre, const std::string &departamento,
                                    const std::string &empresa);

    /**
     * @brief Métodos relacionados con los activos
     */
    void mostrarActivosDeMatriz(int userId);
    Activo *buscarActivosDeMatriz(const std::string &idActivp);

    /**
     * @brief Métodos para generar árboles AVL
     */
    AVL *arbolAVLDepartamentos(const std::string &departamento);
    AVL *arbolAVLEmpresas(const std::string &empresa);
};

#endif // MATRIZDISPERSA_H