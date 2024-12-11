# Manual técnico
### Gestor de activos
#### Jorge Mejía - Carné 202300376

## Introducción


El gestor de activos es una aplicación que permite llevar un control de los activos de una empresa, y de un departamento permitiendo agregar, modificar y eliminar activos, así como también visualizar los activos existentes.

El sistema está desarrollado en C++, es un programa en consola que permite al usuario interactuar con el sistema mediante un menú de opciones.

### Requerimientos

Para poder ejecutar el programa se necesita tener instalado un compilador de C++ en la computadora, como por ejemplo g++, y tener acceso a una terminal de comandos.

El programa cuenta con su archivo `tasks.json` que contiene los comandos necesarios para compilar y ejecutar el programa en una terminal de comandos de VSCode, facilitando la ejecución del programa en un entorno de desarrollo.

Es necesario tener instalado GraphViz para poder generar los reportes del sistema.

A su vez, se incluye el comando para compilar el programa en el archivo `ejectuar.txt` y el ejecutable del programa `main`.

Compilar el programa en una terminal de comandos:
```
g++ main.cpp classes/MatrizDispersa.cpp classes/CircleDoubleLinkedList.cpp classes/Usuario.cpp classes/Activo.cpp classes/Transaction.cpp classes/AVL.cpp utilities/Login.cpp utilities/AddUser.cpp utilities/AdminMenu.cpp utilities/ReporteMatriz.cpp utilities/UserMenu.cpp utilities/LoggedUser.cpp -o main
```

Ejecutar el programa:
```
./main
```

### Estructura del proyecto

El proyecto está estructurado en diferentes carpetas, cada una con un propósito específico.


```
.
├── build
│   └── Debug
│       └── main.o
├── classes
│   ├── Activo.cpp
│   ├── Activo.h
│   ├── AVL.cpp
│   ├── AVL.h
│   ├── CircleDoubleLinkedList.cpp
│   ├── CircleDoubleLinkedList.h
│   ├── MatrizDispersa.cpp
│   ├── MatrizDispersa.h
│   ├── Transaction.cpp
│   ├── Transaction.h
│   ├── Usuario.cpp
│   └── Usuario.h
├── ejecutar.txt
├── examples
├── main
├── main.cpp
├── manuales
│   ├── TECNICO.md
│   └── USUARIO.md
├── reportes
├── tasks.json
└── utilities
    ├── AddUser.cpp
    ├── AddUser.h
    ├── AdminMenu.cpp
    ├── AdminMenu.h
    ├── LoggedUser.cpp
    ├── LoggedUser.h
    ├── Login.cpp
    ├── Login.h
    ├── Menu.cpp
    ├── ReporteMatriz.cpp
    ├── ReporteMatriz.h
    ├── UserMenu.cpp
    └── UserMenu.h
```

El propósito de cada carpeta es el siguiente:

- `build`: Contiene los archivos objeto generados al compilar el programa.
- `classes`: Contiene las clases que representan los objetos del sistema.
- `examples`: Contiene ejemplos de archivos de entrada para el programa.
- `manuales`: Contiene los manuales de usuario y técnico del sistema.
- `reportes`: Contiene los reportes generados por el sistema.
- `utilities`: Contiene las utilidades del sistema, como el menú de opciones, el login, y la creación de usuarios.
- `main.cpp`: Archivo principal del programa.

## Estructura del programa

El programa está dividido en diferentes módulos, cada uno con un propósito específico.

Se utilizan clases para representar los objetos del sistema, como los activos, los usuarios, las transacciones, y la matriz dispersa que almacena los activos, junto con un árbol AVL que almacena los usuarios y una lista doblemente enlazada que almacena las transacciones.

### TDAs

Los TDAs utilizados en el sistema son los siguientes:

- Lista doblemente enlazada
- Matriz dispersa
- Árbol binario de búsqueda

La lista doblemente enlazada se utiliza para
almacenar las transacciones realizadas por los usuarios, la matriz dispersa se utiliza para almacenar los activos de la empresa y el árbol binario de búsqueda se utiliza para almacenar los usuarios del sistema.


### Clases

Las clases utilizadas en el sistema (Aparte de los TDAs)son las siguientes:

- Activo
- Usuario
- Transacción

Cada clase tiene sus métodos y atributos específicos, y se encarga de representar un objeto del sistema.


### Reportes

Los reportes generados por el sistema coinciden con las estructuras de datos utilizadas en el sistema, y se encuentran ejemplos de reportes en la carpeta `reportes/`.

Se utilizan archivos `.png` para almacenar los reportes generados por GraphViz.