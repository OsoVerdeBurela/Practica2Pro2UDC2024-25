# 🎓 Práctica 2 - Programación 2 (UDC 2024-2025)

![C](https://img.shields.io/badge/Lenguaje-C-blue.svg?logo=c&logoColor=white)
![CMake](https://img.shields.io/badge/Build-CMake-064F8C.svg?logo=cmake&logoColor=white)
![Nota](https://img.shields.io/badge/Nota-1,95%2F2-brightgreen.svg?logo=academia)
![Universidad](https://img.shields.io/badge/Universidad-UDC-purple.svg)

> **Práctica 2** correspondiente a la asignatura de **Programación 2** de la *Universidade da Coruña (UDC)* durante el curso académico 2024-2025. 

---

## 📝 Descripción

La práctica implementa en **C** diferentes Estructuras de Datos  necesarias para la gestión de un sistema propuesto en la práctica. Específicamente, el sistema hace uso de listas ordenadas y pilas para gestionar la información:

- **Listas de Consolas (`console_list`)**: Para almacenar y administrar las diferentes consolas.
- **Pilas de Pujas (`bid_stack`)**: Para gestionar un sistema de pujas apiladas.

*La práctica obtuvo un 1,95/2*

---

## 📂 Estructura del Proyecto

El repositorio está organizado con los siguientes archivos principales:

### 🧩 Código Fuente (Implementaciones y Cabeceras)
* `main.c`: Punto de entrada principal del programa.
* `console_list.c` / `console_list.h`: Implementación y definición del TAD Lista para consolas.
* `bid_stack.c` / `bid_stack.h`: Implementación y definición del TAD Pila para pujas.
* `types.h`: Definición de tipos de datos comunes utilizados en todo el programa. (Lo da la práctica)
   
### 🧪 Tests (Los da la práctica)
* `test.c`: Archivo general de pruebas.
* `test_console_list.c`: Pruebas unitarias específicas para comprobar la robustez de la lista de consolas.
* `test_bid_stack.c`: Pruebas unitarias específicas para la pila de pujas.

### 🛠️ Configuración y Construcción (Los da la práctica)
* `CMakeLists.txt` / `config.cmake`: Archivos de configuración para compilar el proyecto usando **CMake**.
* `script.sh`: Script de automatización en Bash para facilitar la compilación y/o ejecución de pruebas.

---
