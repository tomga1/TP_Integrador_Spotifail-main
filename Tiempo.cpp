#include "Tiempo.h"

Tiempo::Tiempo()
{
    setTiempoAhora();
}

Tiempo::Tiempo(int hora, int minuto, int segundo)
{
    if (0 <= segundo && segundo < 60 && 0 <= minuto && minuto < 60 && 0 <= hora && hora < 24)
    setHora(hora);
    setMinuto(minuto);
    setSegundo(segundo);
}

int Tiempo::getHora() { return _hora; }
void Tiempo::setHora(int hora) {
     if (0 <= hora && hora < 24) {
        _hora = hora;
    }
}

int Tiempo::getMinuto() { return _minuto; }
void Tiempo::setMinuto(int minuto) {
    if (0 <= minuto && minuto < 60) {
        _minuto = minuto;
    }
}

int Tiempo::getSegundo() { return _segundo; }
void Tiempo::setSegundo(int segundo) {
    if (0 <= segundo && segundo < 60) {
        _segundo = segundo;
    }
}

void Tiempo::setTiempoAhora() {
    std::time_t now = std::time(NULL);
    std::tm * local_time = std::localtime(& now);
    setSegundo((* local_time).tm_sec);
    setMinuto((* local_time).tm_min);
    setHora((* local_time).tm_hour);
}

std::string Tiempo::toString() {
    std::string ss;
    std::string mm;
    std::string hh;

    if (_segundo < 10) {
        ss = "0" + std::to_string(_segundo);
    } else {
        ss = std::to_string(_segundo);
    }

    if (_minuto < 10) {
        mm = "0" + std::to_string(_minuto);
    } else {
        mm = std::to_string(_minuto);
    }

    if (_hora < 10) {
        hh = "0" + std::to_string(_hora);
    } else {
        hh = std::to_string(_hora);
    }

    return hh + ":" + mm + ":" + ss;
}
