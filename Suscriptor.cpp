#include "Suscriptor.h"

Suscriptor::Suscriptor()
{
    setIdSuscriptor(1);
    setDni(0);
    setNombre("N/A");
    setApellido("N/A");
    setTelefono("N/A");
    setEmail("N/A");
    setFechaNacimiento(Fecha());
    setInactivo(false);
}

Suscriptor::Suscriptor(int idSuscriptor, int dni, std::string & nombre, std::string & apellido,
                       std::string & telefono, std::string & email, Fecha fechaNacimiento, bool inactivo)
{
    setIdSuscriptor(idSuscriptor);
    setDni(dni);
    setNombre(nombre);
    setApellido(apellido);
    setTelefono(telefono);
    setEmail(email);
    setFechaNacimiento(fechaNacimiento);
    setInactivo(inactivo);
}

int Suscriptor::getIdSuscriptor() { return _idSuscriptor; }

void Suscriptor::setIdSuscriptor(int idSuscriptor)
{
    _idSuscriptor = idSuscriptor;
}

int Suscriptor::getDni() { return _dni; }

void Suscriptor::setDni(int dni)
{
    _dni = dni;
}

const char* Suscriptor::getNombre() { return _nombre; }

void Suscriptor::setNombre(const std::string & nombre)
{
    strcpy(_nombre, nombre.c_str());
}

const char* Suscriptor::getApellido() { return _apellido; }

void Suscriptor::setApellido(const std::string & apellido)
{
    strcpy(_apellido, apellido.c_str());
}

const char* Suscriptor::getTelefono() { return _telefono; }

void Suscriptor::setTelefono(const std::string & telefono)
{
    strcpy(_telefono, telefono.c_str());
}

const char* Suscriptor::getEmail() { return _email; }

void Suscriptor::setEmail(const std::string & email)
{
    strcpy(_email, email.c_str());
}

Fecha Suscriptor::getFechaNacimiento() { return _fechaNacimiento; }

void Suscriptor::setFechaNacimiento(Fecha fechaNacimiento)
{
    _fechaNacimiento = fechaNacimiento;
}

bool Suscriptor::getInactivo() { return _inactivo; }

void Suscriptor::setInactivo(bool inactivo)
{
    _inactivo = inactivo;
}

const char* Suscriptor::getClave() {
    return _clave;
}

void Suscriptor::setClave(const std::string & clave) {
    strcpy(_clave, clave.c_str());
}

