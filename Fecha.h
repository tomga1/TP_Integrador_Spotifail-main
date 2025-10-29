#pragma once
#include <string>
#include <ctime>

class Fecha
{
public:
    Fecha();
    Fecha(int dia, int mes, int anio);
    int getDia();
    void setDia(int dia);
    int getMes();
    void setMes(int mes);
    int getAnio();
    void setAnio(int anio);
    std::string toString();

private:
    int _dia;
    int _mes;
    int _anio;
};
