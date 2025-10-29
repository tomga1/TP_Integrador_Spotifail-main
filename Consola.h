#pragma once
#include <iostream>
#include <string>
#include <cstring>

class Consola {
public:
    Consola();
    void setAnchoLinea(int ancho);
    int getAnchoLinea();
    void setTextoVolver(const std::string& texto);
    std::string getTextoVolver();
    void limpiar();
    void pausar();
    void imprimirLinea();
    void centrarYMostrar(const std::string& texto);
    void mostrarOpcionVolver();
    void mostrarEncabezadoMenu(const std::string& titulo);
    void mostrarPieMenu();
    void imprimirBool(bool valor, const std::string& textoSi, const std::string& textoNo);
    bool validarBool();
    int validarInt();
    int validarInt(int minimo);
    int validarInt(int minimo, int maximo);
    long long int validarLong();
    long long int validarLong(int minimo);
    long long int validarLong(int minimo, int maximo);
    double validarDouble();
    double validarDouble(double minimo);
    double validarDouble(double minimo, double maximo);
    char validarChar();
    void limpiarBuffer();
    std::string rellenar(const std::string& texto, unsigned int longitud = 26);

private:
    int _ancho_linea;
    char _texto_volver[30];
};
