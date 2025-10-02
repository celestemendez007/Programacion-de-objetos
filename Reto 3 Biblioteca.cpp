#include <iostream> 
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <limits>

using namespace std;
// aca estoy creando los objetos de mi mini base de datos
// Autor, Libro, Estudiante y Prestamo

struct Autor {
    int id;
    string nombre;
    string nacionalidad;
};

struct Libro {
    int id;
    string titulo;
    string isbn;
    int ano;
    int id_autor;
    bool disponible; // true si se puede prestar, false si ya esta prestado

};

struct Estudiante {
    int id;
    string nombre;
    string grado;
};

struct Prestamo {
    int id;
    int id_libro;
    int id_estudiante;
    string fecha_prestamo;
    string fecha_devolucion; // si esta vacia significa que todavia no lo devolvio
};

// aca esta la clase que maneja toda la logica de la "base de datos"
// esta clase tiene todos los vectores y las funciones CRUD
class BibliotecaDB {
public:
    vector<Autor> autores;
    vector<Libro> libros;
    vector<Estudiante> estudiantes;
    vector<Prestamo> prestamos;

    // estas funciones me sirven para buscar si existe un registro por su id
    Autor* buscarAutorPorId(int id) {
        for (auto &a : autores) if (a.id == id) return &a;
        return nullptr;
    }
    Libro* buscarLibroPorId(int id) {
        for (auto &l : libros) if (l.id == id) return &l;
        return nullptr;
    }
    Estudiante* buscarEstudiantePorId(int id) {
        for (auto &e : estudiantes) if (e.id == id) return &e;
        return nullptr;
    }
    Prestamo* buscarPrestamoPorId(int id) {
        for (auto &p : prestamos) if (p.id == id) return &p;
        return nullptr;
    }

    // checar si un id ya existe para no duplicar datos
    bool idExisteAutor(int id) { return buscarAutorPorId(id) != nullptr; }
    bool idExisteLibro(int id) { return buscarLibroPorId(id) != nullptr; }
    bool idExisteEstudiante(int id) { return buscarEstudiantePorId(id) != nullptr; }
    bool idExistePrestamo(int id) { return buscarPrestamoPorId(id) != nullptr; }

    // revisa si el libro ya esta prestado y aun no devuelto
    bool libroTienePrestamoActivo(int id_libro) {
        for (auto &p : prestamos) if (p.id_libro == id_libro && p.fecha_devolucion.empty()) return true;
        return false;
    }
    //CRUD AUTOR

    bool agregarAutor(const Autor &a) {
        if (idExisteAutor(a.id)) {
            cout << "Error: ID de autor duplicado.\n";
            return false;
        }
        autores.push_back(a);
        return true;
    }
    void listarAutores() {
        if (autores.empty()) { cout << "No hay autores registrados.\n"; return; }
        for (auto &a : autores)
            cout << a.id << " - " << a.nombre << " (" << a.nacionalidad << ")\n";
    }
    bool actualizarAutor(int id, const string &nuevoNombre, const string &nuevaNacionalidad) {
        Autor* a = buscarAutorPorId(id);
        if (!a) { cout << "Autor no encontrado.\n"; return false; }
        a->nombre = nuevoNombre;
        a->nacionalidad = nuevaNacionalidad;
        return true;
    }
    bool eliminarAutor(int id) {
        for (auto &l : libros) if (l.id_autor == id) {
            cout << "No se puede eliminar autor: tiene libros asociados (ID libro: " << l.id << ").\n";
            return false;
        }
        for (auto it = autores.begin(); it != autores.end(); ++it) {
            if (it->id == id) { autores.erase(it); return true; }
        }
        cout << "Autor no encontrado.\n";
        return false;
    }
    //CRUD LIBRO 


    bool agregarLibro(const Libro &l) {
        if (idExisteLibro(l.id)) {
            cout << "Error: ID de libro duplicado.\n";
            return false;
        }
        if (!idExisteAutor(l.id_autor)) {
            cout << "Error: El autor con ID " << l.id_autor << " no existe.\n";
            return false;
        }
        libros.push_back(l);
        return true;
    }
    void listarLibros() {
        if (libros.empty()) { cout << "No hay libros registrados.\n"; return; }
        for (auto &l : libros) {
            string estado = l.disponible ? "Disponible" : "Prestado";
            cout << l.id << " - " << l.titulo << " (ISBN: " << l.isbn << ", " << l.ano << ") - " << estado << " - AutorID: " << l.id_autor << "\n";
        }
    }
    bool actualizarLibro(int id, const string &titulo, const string &isbn, int ano, int id_autor) {
        Libro* l = buscarLibroPorId(id);
        if (!l) { cout << "Libro no encontrado.\n"; return false; }
        if (!idExisteAutor(id_autor)) { cout << "Autor especificado no existe.\n"; return false; }
        l->titulo = titulo; l->isbn = isbn; l->ano = ano; l->id_autor = id_autor;
        return true;
    }
    bool eliminarLibro(int id) {
        // no se puede borrar si esta prestado
        if (libroTienePrestamoActivo(id)) {
            cout << "No se puede eliminar: el libro tiene prestamo activo.\n";
            return false;
        }
        for (auto it = libros.begin(); it != libros.end(); ++it) {
            if (it->id == id) { libros.erase(it); return true; }
        }
        cout << "Libro no encontrado.\n";
        return false;
    }
    //CRUD ESTUDIANTE
    bool agregarEstudiante(const Estudiante &e) {
        if (idExisteEstudiante(e.id)) { cout << "Error: ID de estudiante duplicado.\n"; return false; }
        estudiantes.push_back(e);
        return true;
    }
    void listarEstudiantes() {
        if (estudiantes.empty()) { cout << "No hay estudiantes registrados.\n"; return; }
        for (auto &e : estudiantes)
            cout << e.id << " - " << e.nombre << " - " << e.grado << "\n";
    }
    bool actualizarEstudiante(int id, const string &nombre, const string &grado) {
        Estudiante* e = buscarEstudiantePorId(id);
        if (!e) { cout << "Estudiante no encontrado.\n"; return false; }
        e->nombre = nombre; e->grado = grado;
        return true;
    }
    bool eliminarEstudiante(int id) {
        for (auto &p : prestamos) if (p.id_estudiante == id && p.fecha_devolucion.empty()) {
            cout << "No se puede eliminar: el estudiante tiene prestamos activos (ID prestamo: " << p.id << ").\n";
            return false;
        }
        for (auto it = estudiantes.begin(); it != estudiantes.end(); ++it) {
            if (it->id == id) { estudiantes.erase(it); return true; }
        }
        cout << "Estudiante no encontrado.\n";
        return false;
    }

    //CRUD PRESTAMO
    bool agregarPrestamo(const Prestamo &p) {
        if (idExistePrestamo(p.id)) {
            cout << "Error: ID de prestamo duplicado.\n";
            return false;
        }
        Libro* l = buscarLibroPorId(p.id_libro);
        if (!l) { cout << "Error: Libro no existe.\n"; return false; }
        if (!l->disponible) { cout << "Error: Libro no disponible.\n"; return false; }
        if (!idExisteEstudiante(p.id_estudiante)) { cout << "Error: Estudiante no existe.\n"; return false; }

        Prestamo copy = p;
        copy.fecha_devolucion = ""; 
        prestamos.push_back(copy);
        l->disponible = false;
        return true;
    }
    void listarPrestamos() {
        if (prestamos.empty()) { cout << "No hay prestamos registrados.\n"; return; }
        for (auto &p : prestamos) {
            string dev = p.fecha_devolucion.empty() ? "Pendiente" : p.fecha_devolucion;
            string titulo = "(titulo no encontrado)", nombreEst = "(estudiante no encontrado)";
            Libro* l = buscarLibroPorId(p.id_libro); if (l) titulo = l->titulo;
            Estudiante* e = buscarEstudiantePorId(p.id_estudiante); if (e) nombreEst = e->nombre;
            cout << p.id << " - LibroID: " << p.id_libro << " (" << titulo << "), EstudianteID: " << p.id_estudiante << " (" << nombreEst << ")"
                 << ", Fecha: " << p.fecha_prestamo << ", Devolucion: " << dev << "\n";
        }
    }

    bool devolverPrestamo(int id_prestamo, const string &fecha_devolucion) {
        Prestamo* p = buscarPrestamoPorId(id_prestamo);
        if (!p) { cout << "Prestamo no encontrado.\n"; return false; }
        if (!p->fecha_devolucion.empty()) { cout << "Prestamo ya devuelto el " << p->fecha_devolucion << "\n"; return false; }
        p->fecha_devolucion = fecha_devolucion;
        Libro* l = buscarLibroPorId(p->id_libro);
        if (l) l->disponible = true;
        cout << "Devolucion registrada correctamente.\n";
        return true;
    }
    bool actualizarPrestamo(int id, int nuevo_id_libro, int nuevo_id_estudiante, const string &nueva_fecha_prestamo) {
        Prestamo* p = buscarPrestamoPorId(id);
        if (!p) { cout << "Prestamo no encontrado.\n"; return false; }

        if (p->fecha_devolucion.empty()) {
            Libro* l_old = buscarLibroPorId(p->id_libro);
            if (l_old) l_old->disponible = true;
        }

        p->id_libro = nuevo_id_libro;
        p->id_estudiante = nuevo_id_estudiante;
        p->fecha_prestamo = nueva_fecha_prestamo;
        p->fecha_devolucion = "";

        Libro* l_new = buscarLibroPorId(nuevo_id_libro);
        if (l_new) l_new->disponible = false;

        cout << "Prestamo actualizado correctamente.\n";
        return true;
}

    bool eliminarPrestamo(int id) {
        Prestamo* p = buscarPrestamoPorId(id);
        if (!p) { cout << "Prestamo no encontrado.\n"; return false; }
        if (p->fecha_devolucion.empty()) {
            Libro* l = buscarLibroPorId(p->id_libro);
            if (l) l->disponible = true;
        }
        for (auto it = prestamos.begin(); it != prestamos.end(); ++it) {
            if (it->id == id) { prestamos.erase(it); return true; }
        }
        return false;
    }

    void librosPorEstudiante(int id_est) {
        cout << "Libros prestados por estudiante " << id_est << ":\n";
        bool found = false;
        for (auto &p : prestamos) {
            if (p.id_estudiante == id_est) {
                found = true;
                Libro* l = buscarLibroPorId(p.id_libro);
                string titulo = l ? l->titulo : "(titulo no encontrado)";
                string dev = p.fecha_devolucion.empty() ? "Pendiente" : p.fecha_devolucion;
                cout << "PrestamoID: " << p.id << " - Libro ID: " << p.id_libro << " - " << titulo 
                     << " - Fecha prestamo: " << p.fecha_prestamo << " - Devolucion: " << dev << "\n";
            }
        }
        if (!found) cout << "No se encontraron prestamos para ese estudiante.\n";
    }

    void autoresConMasLibros() {
        cout << "Autores con mas libros (ordenado):\n";
        vector<pair<string,int>> arr;
        for (auto &a : autores) {
            int cnt = 0;
            for (auto &l : libros) if (l.id_autor == a.id) cnt++;
            arr.push_back({a.nombre, cnt});
        }
        sort(arr.begin(), arr.end(), [](const pair<string,int>& x, const pair<string,int>& y){
            if (x.second != y.second) return x.second > y.second;
            return x.first < y.first;
        });
        for (auto &p : arr) cout << p.first << " - " << p.second << " libros\n";
    }

    void buscarPorISBN(const string &isbn) {
        for (auto &l : libros) {
            if (l.isbn == isbn) {
                cout << "Encontrado: " << l.id << " - " << l.titulo << " (" << (l.disponible? "Disponible":"Prestado") << ")\n";
                return;
            }
        }
        cout << "No se encontro libro con ISBN: " << isbn << "\n";
    }

    //GUARDAR Y CARGAR DATOS 

    void guardarDatos() {
        ofstream f_autores("autores.txt");
        if (f_autores.is_open()) {
            for (auto &a : autores)
                f_autores << a.id << "|" << a.nombre << "|" << a.nacionalidad << "\n";
            f_autores.close();
        } else {
            cout << "Error al abrir autores.txt para guardar.\n";
        }

        ofstream f_libros("libros.txt");
        if (f_libros.is_open()) {
            for (auto &l : libros)
                f_libros << l.id << "|" << l.titulo << "|" << l.isbn << "|" << l.ano << "|" 
                         << l.id_autor << "|" << (l.disponible ? 1 : 0) << "\n";
            f_libros.close();
        } else {
            cout << "Error al abrir libros.txt para guardar.\n";
        }

        ofstream f_estudiantes("estudiantes.txt");
        if (f_estudiantes.is_open()) {
            for (auto &e : estudiantes)
                f_estudiantes << e.id << "|" << e.nombre << "|" << e.grado << "\n";
            f_estudiantes.close();
        } else {
            cout << "Error al abrir estudiantes.txt para guardar.\n";
        }

        ofstream f_prestamos("prestamos.txt");
        if (f_prestamos.is_open()) {
            for (auto &p : prestamos)
                f_prestamos << p.id << "|" << p.id_libro << "|" << p.id_estudiante << "|" 
                            << p.fecha_prestamo << "|" << p.fecha_devolucion << "\n";
            f_prestamos.close();
        } else {
            cout << "Error al abrir prestamos.txt para guardar.\n";
        }
    }

    void cargarDatos() {
        string line;

        autores.clear(); libros.clear(); estudiantes.clear(); prestamos.clear();

        ifstream f_autores("autores.txt");
        if (f_autores.is_open()) {
            while (getline(f_autores, line)) {
                if (line.empty()) continue;
                stringstream ss(line);
                Autor a; string temp;
                getline(ss, temp, '|'); a.id = safeStoi(temp, -1);
                getline(ss, a.nombre, '|'); getline(ss, a.nacionalidad, '|');
                if (a.id != -1) autores.push_back(a);
            }
            f_autores.close();
        }
        for (auto &l : libros) l.disponible = true; 
        for (auto &p : prestamos) {
            if (p.fecha_devolucion.empty()) {
                Libro* l = buscarLibroPorId(p.id_libro);
                if (l) l->disponible = false;
            }
        }   
        ifstream f_libros("libros.txt");
        if (f_libros.is_open()) {
            while (getline(f_libros, line)) {
                if (line.empty()) continue;
                stringstream ss(line);
                Libro l; string temp;
                getline(ss, temp, '|'); l.id = safeStoi(temp, -1);
                getline(ss, l.titulo, '|'); getline(ss, l.isbn, '|');
                getline(ss, temp, '|'); l.ano = safeStoi(temp, 0);
                getline(ss, temp, '|'); l.id_autor = safeStoi(temp, -1);
                getline(ss, temp, '|'); l.disponible = (safeStoi(temp, 1) != 0);
                if (l.id != -1) libros.push_back(l);
            }
            f_libros.close();
        }

        ifstream f_estudiantes("estudiantes.txt");
        if (f_estudiantes.is_open()) {
            while (getline(f_estudiantes, line)) {
                if (line.empty()) continue;
                stringstream ss(line);
                Estudiante e; string temp;
                getline(ss, temp, '|'); e.id = safeStoi(temp, -1);
                getline(ss, e.nombre, '|'); getline(ss, e.grado, '|');
                if (e.id != -1) estudiantes.push_back(e);
            }
            f_estudiantes.close();
        }

        ifstream f_prestamos("prestamos.txt");
        if (f_prestamos.is_open()) {
            while (getline(f_prestamos, line)) {
                if (line.empty()) continue;
                stringstream ss(line);
                Prestamo p; string temp;
                getline(ss, temp, '|'); p.id = safeStoi(temp, -1);
                getline(ss, temp, '|'); p.id_libro = safeStoi(temp, -1);
                getline(ss, temp, '|'); p.id_estudiante = safeStoi(temp, -1);
                getline(ss, p.fecha_prestamo, '|'); getline(ss, p.fecha_devolucion, '|');
                if (p.id != -1) prestamos.push_back(p);
            }
            f_prestamos.close();
        }
    }

private:
    int safeStoi(const string &s, int defaultVal) {
        try {
            if (s.empty()) return defaultVal;
            size_t idx = 0;
            int v = stoi(s, &idx);
            return v;
        } catch (...) {
            return defaultVal;
        }
    }
};

void pausar() {
    cout << "Presiona Enter para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
// MENU PRINCIPAL 

int main() {
    BibliotecaDB db;
    db.cargarDatos();
    //MENU PRINCIPAL 
    int opcion;
    do {
        cout << "\n¿Que quieres hacer?\n";
        cout << "1. Agregar Autor\n2. Listar Autores\n3. Actualizar Autor\n4. Eliminar Autor\n";
        cout << "5. Agregar Libro\n6. Listar Libros\n7. Actualizar Libro\n8. Eliminar Libro\n";
        cout << "9. Agregar Estudiante\n10. Listar Estudiantes\n11. Actualizar Estudiante\n12. Eliminar Estudiante\n";
        cout << "13. Agregar Prestamo\n14. Listar Prestamos\n15. Devolver Prestamo\n16. Eliminar Prestamo\n";
        cout << "17. Libros por Estudiante\n18. Autores con mas libros\n19. Buscar por ISBN(Numero unico que identifica un libro a nivel internacional)\n";
        cout << "0. Guardar y Salir\nIngrese opcion: ";

        if (!(cin >> opcion)) {
            cout << "Entrada invalida.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            opcion = -1;
            continue;
        }
        cin.ignore(); 

        switch(opcion) {
            case 1: {
                Autor a;
                cout << "ID: "; cin >> a.id; cin.ignore();
                cout << "Nombre: "; getline(cin, a.nombre);
                cout << "Nacionalidad: "; getline(cin, a.nacionalidad);
                if(db.agregarAutor(a)) cout << "Autor agregado.\n";
                pausar();
                break;
            }
            case 2: db.listarAutores(); pausar(); break;
            case 3: {
                int id; cout << "ID autor a actualizar: "; cin >> id; cin.ignore();
                string nombre, nacionalidad;
                cout << "Nuevo nombre: "; getline(cin, nombre);
                cout << "Nueva nacionalidad: "; getline(cin, nacionalidad);
                if(db.actualizarAutor(id,nombre,nacionalidad)) cout << "Autor actualizado.\n";
                pausar();
                break;
            }
            case 4: {
                int id; cout << "ID autor a eliminar: "; cin >> id; cin.ignore();
                if(db.eliminarAutor(id)) cout << "Autor eliminado.\n";
                pausar();
                break;
            }
            case 5: {
                Libro l;
                cout << "ID: "; cin >> l.id; cin.ignore();
                cout << "Titulo: "; getline(cin, l.titulo);
                cout << "ISBN: "; getline(cin, l.isbn);
                cout << "Ano: "; cin >> l.ano; cin.ignore();
                cout << "ID Autor: "; cin >> l.id_autor; cin.ignore();
                l.disponible = true;
                if(db.agregarLibro(l)) cout << "Libro agregado.\n";
                pausar();
                break;
            }
            case 6: db.listarLibros(); pausar(); break;
            case 7: {
                int id; cout << "ID libro a actualizar: "; cin >> id; cin.ignore();
                string titulo, isbn; int ano, id_autor;
                cout << "Nuevo titulo: "; getline(cin, titulo);
                cout << "Nuevo ISBN: "; getline(cin, isbn);
                cout << "Nuevo ano: "; cin >> ano; cin.ignore();
                cout << "Nuevo ID Autor: "; cin >> id_autor; cin.ignore();
                if(db.actualizarLibro(id,titulo,isbn,ano,id_autor)) cout << "Libro actualizado.\n";
                pausar();
                break;
            }
            case 8: {
                int id; cout << "ID libro a eliminar: "; cin >> id; cin.ignore();
                if(db.eliminarLibro(id)) cout << "Libro eliminado.\n";
                pausar();
                break;
            }
            case 9: {
                Estudiante e;
                cout << "ID: "; cin >> e.id; cin.ignore();
                cout << "Nombre: "; getline(cin, e.nombre);
                cout << "Grado: "; getline(cin, e.grado);
                if(db.agregarEstudiante(e)) cout << "Estudiante agregado.\n";
                pausar();
                break;
            }
            case 10: db.listarEstudiantes(); pausar(); break;
            case 11: {
                int id; cout << "ID estudiante a actualizar: "; cin >> id; cin.ignore();
                string nombre, grado;
                cout << "Nuevo nombre: "; getline(cin, nombre);
                cout << "Nuevo grado: "; getline(cin, grado);
                if(db.actualizarEstudiante(id,nombre,grado)) cout << "Estudiante actualizado.\n";
                pausar();
                break;
            }
            case 12: {
                int id; cout << "ID estudiante a eliminar: "; cin >> id; cin.ignore();
                if(db.eliminarEstudiante(id)) cout << "Estudiante eliminado.\n";
                pausar();
                break;
            }
            case 13: {
                Prestamo p;
                cout << "ID Prestamo: "; cin >> p.id;
                cout << "ID Libro: "; cin >> p.id_libro;
                cout << "ID Estudiante: "; cin >> p.id_estudiante; cin.ignore();
                cout << "Fecha Prestamo (YYYY-MM-DD): "; getline(cin, p.fecha_prestamo);
                if(db.agregarPrestamo(p)) cout << "Prestamo registrado.\n";
                pausar();
                break;
            }
            case 14: db.listarPrestamos(); pausar(); break;
            case 15: {
                int id; cout << "ID prestamo a devolver: "; cin >> id; cin.ignore();
                string fecha; cout << "Fecha de devolucion (YYYY-MM-DD): "; getline(cin, fecha);
                db.devolverPrestamo(id,fecha);
                pausar();
                break;
            }
            case 16: {
                int id; cout << "ID prestamo a eliminar: "; cin >> id; cin.ignore();
                if(db.eliminarPrestamo(id)) cout << "Prestamo eliminado.\n";
                pausar();
                break;
            }
            case 17: {
                int id_est; cout << "ID Estudiante: "; cin >> id_est; cin.ignore();
                db.librosPorEstudiante(id_est); pausar();
                break;
            }
            case 18: db.autoresConMasLibros(); pausar(); break;
            case 19: {
                string isbn; cout << "ISBN a buscar: "; getline(cin, isbn);
                db.buscarPorISBN(isbn); pausar();
                break;
            }
            case 0: 
            // salgo del programa y guardo todo
                db.guardarDatos();
                cout << "Datos guardados. Hasta luego!\n";
                break;
            default:
                cout << "Opcion no valida.\n"; pausar(); break;
        }

    } while(opcion != 0);

    return 0;
}

