#include "Fecha.h"

Fecha::Fecha()
{
    setDia(1);
    setMes(1);
    setAnio(1900);
}

Fecha::Fecha(int dia, int mes, int anio)
{
    setDia(dia);
    setMes(mes);
    setAnio(anio);
}

int Fecha::getDia() { return _dia; }
void Fecha::setDia(int dia) { _dia = dia; }

int Fecha::getMes() { return _mes; }
void Fecha::setMes(int mes) { _mes = mes; }

int Fecha::getAnio() { return _anio; }
void Fecha::setAnio(int anio) { _anio = anio; }

std::string Fecha::toString() {
    std::string dd;
    std::string mm;
    std::string yyyy = std::to_string(_anio);

    if (_dia < 10) {
        dd = "0" + std::to_string(_dia);
    } else {
        dd = std::to_string(_dia);
    }

    if (_mes < 10) {
        mm = "0" + std::to_string(_mes);
    } else {
        mm = std::to_string(_mes);
    }

    return dd + "/" + mm + "/" + yyyy;
}
