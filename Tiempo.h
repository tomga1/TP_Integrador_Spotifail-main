#pragma once
#include <string>
#include <ctime>

class Tiempo
{
public:
    Tiempo();
    Tiempo(int hora, int minuto, int segundo);
    int getHora();
    void setHora(int hora);
    int getMinuto();
    void setMinuto(int minuto);
    int getSegundo();
    void setSegundo(int segundo);
    void setTiempoAhora();
    std::string toString();

private:
    int _hora;
    int _minuto;
    int _segundo;
};
