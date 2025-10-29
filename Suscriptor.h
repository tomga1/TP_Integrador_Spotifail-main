#pragma once
#include <string>
#include <cstring>
#include "Fecha.h"

class Suscriptor
{
public:
    Suscriptor();
    Suscriptor(int idSuscriptor, int dni, std::string & nombre, std::string & apellido,
               std::string & telefono, std::string & email, Fecha fechaNacimiento, bool inactivo);
    int getIdSuscriptor();
    void setIdSuscriptor(int idSuscriptor);
    int getDni();
    void setDni(int dni);
    const char* getNombre();
    void setNombre(const std::string & nombre);
    const char* getApellido();
    void setApellido(const std::string & apellido);
    const char* getTelefono();
    void setTelefono(const std::string & telefono);
    const char* getEmail();
    void setEmail(const std::string & email);
    Fecha getFechaNacimiento();
    void setFechaNacimiento(Fecha fechaNacimiento);
    bool getInactivo();
    void setInactivo(bool inactivo);
    const char* getClave();
    void setClave(const std::string & clave);

private:
    int _idSuscriptor;
    int _dni;
    char _nombre[30];
    char _apellido[30];
    char _telefono[15];
    char _email[40];
    Fecha _fechaNacimiento;
    bool _inactivo;
    char _clave[30];
};
