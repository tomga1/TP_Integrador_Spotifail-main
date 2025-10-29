#include "CancionesArchivo.h"

CancionesArchivo::CancionesArchivo() : _path("registers/canciones.dat") {}

CancionesArchivo::CancionesArchivo(const std::string &path) : _path(path) {}

void CancionesArchivo::setPath(const std::string &path)
{
    _path = path;
}

std::string CancionesArchivo::getPath() const
{
    return _path;
}

bool CancionesArchivo::escribir(Cancion &reg)
{
    FILE *p = fopen(getPath().c_str(), "ab");
    if (p == NULL)
    {
        std::cerr << "Error al abrir el archivo para escritura." << std::endl;
        return false;
    }
    bool ok = fwrite(&reg, sizeof(Cancion), 1, p);
    fclose(p);
    return ok;
}

bool CancionesArchivo::sobreEscribir(Cancion &reg, int index)
{
    FILE *p = fopen(getPath().c_str(), "rb+");
    if (p == NULL)
    {
        std::cerr << "Error al abrir el archivo para sobreescritura." << std::endl;
        return false;
    }
    fseek(p, sizeof(Cancion) * index, SEEK_SET);
    bool ok = fwrite(&reg, sizeof(Cancion), 1, p);
    fclose(p);
    return ok;
}

Cancion CancionesArchivo::leer(int index)
{
    Cancion reg;
    FILE *p = fopen(getPath().c_str(), "rb");
    if (p == NULL)
    {
        std::cerr << "Error al abrir el archivo para lectura." << std::endl;
        return reg;
    }
    fseek(p, sizeof(Cancion) * index, SEEK_SET);
    fread(&reg, sizeof(Cancion), 1, p);
    fclose(p);
    return reg;
}

Cancion CancionesArchivo::leerPorId(int id) {
    int indice = buscarPorId(id);
    if (indice == -1) {
        Cancion vacia;
        return vacia;
    }
    return leer(indice);
}

bool CancionesArchivo::sobreEscribirPorId(Cancion &reg, int indice)
{
    FILE *p = fopen(getPath().c_str(), "rb+");
    if (p == NULL)
    {
        std::cerr << "Error al abrir el archivo para sobreescritura." << std::endl;
        return false;
    }

    fseek(p, sizeof(Cancion) * indice, SEEK_SET);

    bool ok = fwrite(&reg, sizeof(Cancion), 1, p);
    fclose(p);
    return ok;
}



int CancionesArchivo::buscarPorId(int id)
{
    int cantidad = getCantidadRegistros();
    Cancion reg;
    for (int i = 0; i < cantidad; i++)
    {
        reg = leer(i);
        if (reg.getIdCancion() == id)
        {
            return i;
        }
    }
    return -1;
}

int CancionesArchivo::getCantidadRegistros()
{
    FILE *p = fopen(getPath().c_str(), "rb");
    if (p == NULL)
    {
        return 0;
    }
    fseek(p, 0, SEEK_END);
    int bytes = ftell(p);
    fclose(p);
    return bytes / sizeof(Cancion);
}

void CancionesArchivo::crearArchivoVacio()
{
    FILE *p = fopen(getPath().c_str(), "wb");
    if (p == NULL)
    {
        std::cerr << "Error al crear el archivo vacío." << std::endl;
    }
    else
    {
        fclose(p);
    }
}
