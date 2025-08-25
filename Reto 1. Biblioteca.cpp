#include <iostream>
#include <string>
#include <vector>

// --- Definición de la clase Libro (mejorada) ---
class Libro {
public:
    std::string titulo;
    std::string autor;
    int anioPublicacion;
    bool estaDisponible; // Nuevo atributo

    // Constructor para inicializar los valores fácilmente
    Libro() : anioPublicacion(0), estaDisponible(true) {}

    void mostrarDetallesCompletos() {
        std::cout << "Titulo: " << titulo << std::endl
                  << "Autor: " << autor << std::endl
                  << "Año de publicacion: " << anioPublicacion << std::endl;
        if (estaDisponible) {
            std::cout << "Disponibilidad: Disponible";
        } else {
            std::cout << "Disponibilidad: Prestado";
        }
    }
};

// --- Definición de la clase Biblioteca ---
class Biblioteca {
private:
    std::vector<Libro> coleccion;

public:
    void agregarLibro(const Libro& nuevoLibro) {
            for (const Libro& libro : coleccion) {
            if (libro.titulo == nuevoLibro.titulo) {
                std::cout << "El libro" << nuevoLibro.titulo 
                          << "ya existe en la biblioteca." << std::endl;
                return;
            }
        }
        coleccion.push_back(nuevoLibro);
        std::cout << "Libro agregado con exito.";
    }

    void mostrarInventario() {
        if (coleccion.empty()) {
            std::cout << "La biblioteca esta vacia.\n";
            return;
        }
        for (Libro& libro : coleccion) {
            libro.mostrarDetallesCompletos();
        }
    }

    Libro* buscarLibro(const std::string& tituloBuscado) {
        for (Libro& libro : coleccion) {
            if (libro.titulo == tituloBuscado) {
                return &libro;
            }
        }
        return nullptr;
    }

    void prestarLibro(const std::string& tituloPrestamo) {
        Libro* libro = buscarLibro(tituloPrestamo);
        if (libro == nullptr) {
            std::cout << "El libro no esta en la biblioteca";
        } else if (libro->estaDisponible==true) {
            std::cout << "El libro ya esta prestado";
        } else {
            libro->estaDisponible = false;
            std::cout << "El Libro ha sido prestado correctammente";
        }
    }

    void devolverLibro(const std::string& tituloDevolucion) {
        Libro* libro = buscarLibro(tituloDevolucion);
        if (libro == nullptr) {
            std::cout << "El libro no esta en la biblioteca";
        } else if (libro->estaDisponible==true) {
            std::cout << "El libro ya estaba disponible";
        } else {
            libro->estaDisponible = true;
            std::cout << "El Libro ha sido devuelto correctammente";
        }
    }
};

// --- Función Principal con el Menú ---
int main() {
    Biblioteca miBiblioteca;
    int opcion = 0;

    // Agregar algunos libros de ejemplo para empezar
    Libro libroInicial;
    libroInicial.titulo = "El Hobbit";
    libroInicial.autor = "J.R.R. Tolkien";
    miBiblioteca.agregarLibro(libroInicial);


    while (opcion != 5) {
        std::cout << "--- BIBLIOTECA DIGITAL ---" << std::endl;
        std::cout << "1. Añadir libro" << std::endl;
        std::cout << "2. Mostrar inventario" << std::endl;
        std::cout << "3. Prestar libro" << std::endl;
        std::cout << "4. Devolver libro" << std::endl;
        std::cout << "5. Salir" << std::endl;
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;

        // Limpiar el buffer de entrada para futuras lecturas de texto
        std::cin.ignore(); 

        if (opcion == 1) {
            std::string titulo, autor;
            int anio;
            std::cout << "Titulo: ";
            std::getline(std::cin, titulo);
            std::cout << "Autor: ";
            std::getline(std::cin, autor);
            std::cout << "Año de publicacion: ";
            std::cin >> anio;
            std::cin.ignore();

            Libro libronuevo;
            libronuevo.titulo = titulo;
            libronuevo.autor = autor;
            libronuevo.anioPublicacion = anio;

            miBiblioteca.agregarLibro(libronuevo);

        } else if (opcion == 2) {
            miBiblioteca.mostrarInventario();

        } else if (opcion == 3) {
            std::string titulo;
            std::cout << "Ingrese el titulo del libro a prestar: ";
            std::getline(std::cin, titulo);
            miBiblioteca.prestarLibro(titulo);

        } else if (opcion == 4) {
            std::string titulo;
            std::cout << "Ingrese el titulo del libro a devolver: ";
            std::getline(std::cin, titulo);
            miBiblioteca.devolverLibro(titulo);

        } else if (opcion == 5) {
            std::cout << "Adios" ;;
        } else {
            std::cout << "Opcion invalida" ;;
        }
    }

    return 0;
}
