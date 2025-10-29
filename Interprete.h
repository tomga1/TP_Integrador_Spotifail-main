#pragma once
#include <string>
#include <cstring>

class Interprete
{
    public:
        Interprete();
        Interprete(int idInterprete, std::string & nombre, int idGenero, bool activo);
        int getIdInterprete();
        void setIdInterprete(int idInterprete);
        const char* getNombre();
        void setNombre(const std::string & nombre);
        int getIdGenero();
        void setIdGenero(int idGenero);
        bool getActivo();
        void setActivo(bool activo);

    private:
        int _idInterprete;
        char _nombre[30];
        int _idGenero;
        bool _activo;

};
