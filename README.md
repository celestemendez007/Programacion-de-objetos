# Reto 3: Diseño Conceptual. Sistema de gestión de una biblioteca escolar
```mermaid
erDiagram
    LIBRO {
        int ID_Libro PK
        string Titulo
        string ISBN
        int Ano_publicacion
        int ID_Autor FK
    }

    AUTOR {
        int ID_Autor PK
        string Nombre_Autor
        string Nacionalidad
    }

    ESTUDIANTE {
        int ID_Estudiante PK
        string Nombre_Estudiante
        string Grado_Estudiante
    }

    PRESTAMO {
        int ID_Prestamo PK
        int ID_Libro FK
        int ID_Estudiante FK
        date Fecha_prestamo
        date Fecha_devolucion
    }

    %% Relaciones
    AUTOR ||--o{ LIBRO : "escribe"
    LIBRO ||--o{ PRESTAMO : "se presta en"
    ESTUDIANTE ||--o{ PRESTAMO : "realiza"

Eliminado README.md (dejado vacío)
