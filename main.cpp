// FILE: main.cpp

#include "utilities/Login.h"
#include "classes/Usuario.h"
#include "classes/MatrizDispersa.h"
#include "classes/Activo.h"

int main()
{
    auto matriz = MatrizDispersa::obtenerInstancia();

    // Guatemala
    auto usuario_elian = std::make_shared<Usuario>("elian_estrada", "1234");
    auto usuario_juanma = std::make_shared<Usuario>("juanma", "32897");
    auto usuario_casimiro = std::make_shared<Usuario>("casimiro", "721896");

    // Jalapa
    auto usuario_pedrito = std::make_shared<Usuario>("pedrito", "48956");
    auto usuario_alcachofa = std::make_shared<Usuario>("alcachofa", "20435");

    // Jutiapa
    auto usuario_juanito = std::make_shared<Usuario>("juanito", "4567");
    auto usuario_fuego = std::make_shared<Usuario>("fuego03", "891346");
    auto usuario_azurdia = std::make_shared<Usuario>("azurdia", "780145");
    auto usuario_incrediboy = std::make_shared<Usuario>("incrediboy", "201598");

    // Peten
    auto usuario_mafer = std::make_shared<Usuario>("mafer", "54312");

    // Insertar usuarios en la matriz
    // Guatemala
    matriz->insertar("igss", "guatemala", usuario_elian);
    matriz->insertar("usac", "guatemala", usuario_juanma);
    matriz->insertar("max", "guatemala", usuario_casimiro);

    // Jalapa
    matriz->insertar("usac", "jalapa", usuario_pedrito);
    matriz->insertar("usac", "jalapa", usuario_alcachofa);

    // Jutiapa
    matriz->insertar("max", "jutiapa", usuario_juanito);
    matriz->insertar("cinepolis", "jutiapa", usuario_fuego);
    matriz->insertar("usac", "jutiapa", usuario_azurdia);
    matriz->insertar("max", "jutiapa", usuario_incrediboy);

    // Peten
    matriz->insertar("cinepolis", "peten", usuario_mafer);

    // Agregar activos a elian_estrada
    usuario_elian->agregarActivo(Activo("Madera", "madera para albañil"));
    usuario_elian->agregarActivo(Activo("Martillos", "martillos para madera"));
    usuario_elian->agregarActivo(Activo("Caladora", "caladora para cortar maderas prefabricadas"));
    usuario_elian->agregarActivo(Activo("Barreno", "barreno para concreto"));

    // Agregar activos a casimiro
    usuario_casimiro->agregarActivo(Activo("Balanza", "balanza con maximo de 25kg"));
    usuario_casimiro->agregarActivo(Activo("Canastas", "canastas para frutas y verduras"));
    usuario_casimiro->agregarActivo(Activo("Linternas", "linternas para alumbrar cuartos oscuros"));
    usuario_casimiro->agregarActivo(Activo("Cargadores", "cargadores de telefonos tipo c"));
    usuario_casimiro->agregarActivo(Activo("Cables", "cables de todo tipo"));
    usuario_casimiro->agregarActivo(Activo("Lazos", "lazos para tender ropa"));

    // Agregar activos a fuego03
    usuario_fuego->agregarActivo(Activo("Termos", "pequeños termos para bebidas calientes"));
    usuario_fuego->agregarActivo(Activo("Maletas", "maletas desde pequeñas a grandes"));
    usuario_fuego->agregarActivo(Activo("Peliculas", "todo tipo de peliculas de accion"));

    // Agregar activos a incrediboy
    usuario_incrediboy->agregarActivo(Activo("Casest", "casets con musica de todo tipo"));
    usuario_incrediboy->agregarActivo(Activo("Pantallas", "pantallas para proyección"));
    usuario_incrediboy->agregarActivo(Activo("Cañonera", "cañonera para proyeccion"));
    usuario_incrediboy->agregarActivo(Activo("Toldo", "toldo para eventos al exterior"));

    // Agregar activos a mafer
    usuario_mafer->agregarActivo(Activo("Audifonos", "audifonos para grabaciones de estudio"));
    usuario_mafer->agregarActivo(Activo("Microfonos", "microfonos de todo tipo"));
    usuario_mafer->agregarActivo(Activo("Pedestales", "pedestales para microfonos grandes y pequeños"));
    usuario_mafer->agregarActivo(Activo("Atriles", "atriles para colocar ojas con gancho"));

    login();
}