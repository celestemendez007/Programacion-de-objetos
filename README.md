# Sistema de Gestión de Biblioteca Escolar

Este proyecto implementa un sistema de gestión de biblioteca escolar en C++, siguiendo un modelo relacional simplificado con vectores de struct para simular tablas y archivos .txt para la persistencia de datos.

El sistema permite manejar:
- Autores
- Libros
- Estudiantes
- Préstamos

El sistema guarda y carga automáticamente desde los siguientes archivos en el mismo directorio:
- autores.txt
- libros.txt
- estudiantes.txt
- prestamos.txt

Cada vez que se modifica la base de datos, los cambios quedan guardados.

## Requisitos
- Compilador C++ (g++ recomendado).
- Compatible con C++17 o superior.
- No se usan librerías externas (solo `<iostream>`, `<vector>`, `<string>`, `<fstream>`, `<sstream>`, `<algorithm>`).

## Funcionalidades:

### Autores
- Agregar, listar, actualizar, eliminar.

### Libros
- Agregar, listar, actualizar, eliminar.
- Control de disponibilidad (prestado/disponible).

### Estudiantes
- Agregar, listar, actualizar, eliminar.

### Préstamos
- Agregar préstamo (solo si el libro está disponible).
- Listar préstamos.
- Devolver libro (cambia estado a disponible).
- Eliminar préstamo.

## Consultas disponibles
- Buscar libro por ISBN.
- Ver libros prestados por estudiante.
- Consultar autor(es) con más libros registrados.

## Ejemplo de uso
¿Qué quieres hacer?
1. Gestionar Autores
2. Gestionar Libros
3. Gestionar Estudiantes
4. Gestionar Préstamos
5. Consultas
6. Salir
Seleccione una opción: ###1

Al elegir 1, aparece el submenú para CRUD de autores.
