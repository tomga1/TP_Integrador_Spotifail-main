#include "Cancion.h"

Cancion::Cancion()
{
    setIdCancion(0);
    setTitulo("N/A");
    setAutor("N/A");
    setIdInterprete(0);
    setIdGenero(0);
    setIdAlbum(0);
    setFechaPublicacion(Fecha());
    setInactivo(false);
}

Cancion::Cancion(int idCancion, std::string &titulo, std::string &autor,
                 int idInterprete, int idGenero, int idAlbum, Fecha fechaPublicacion, bool inactivo)
{
    setIdCancion(idCancion);
    setTitulo(titulo);
    setAutor(autor);
    setIdInterprete(idInterprete);
    setIdGenero(idGenero);
    setIdAlbum(idAlbum);
    setFechaPublicacion(fechaPublicacion);
    setInactivo(inactivo);
}

int Cancion::getIdCancion() { return _idCancion; }
void Cancion::setIdCancion(int idCancion) { _idCancion = idCancion; }

const char* Cancion::getTitulo() { return _titulo; }
void Cancion::setTitulo(const std::string &titulo) { strcpy(_titulo, titulo.c_str()); }

const char* Cancion::getAutor() { return _autor; }
void Cancion::setAutor(const std::string &autor) { strcpy(_autor, autor.c_str()); }

int Cancion::getIdInterprete() { return _idInterprete; }
void Cancion::setIdInterprete(int idInterprete) { _idInterprete = idInterprete; }

int Cancion::getIdGenero() { return _idGenero; }
void Cancion::setIdGenero(int idGenero) { _idGenero = idGenero; }

int Cancion::getIdAlbum() { return _idAlbum; }
void Cancion::setIdAlbum(int idAlbum) { _idAlbum = idAlbum; }

Fecha Cancion::getFechaPublicacion() { return _fechaPublicacion; }
void Cancion::setFechaPublicacion(Fecha fechaPublicacion) { _fechaPublicacion = fechaPublicacion; }

bool Cancion::getInactivo() { return _inactivo; }
void Cancion::setInactivo(bool inactivo) { _inactivo = inactivo; }
