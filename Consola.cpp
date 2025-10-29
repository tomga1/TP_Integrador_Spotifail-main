#include "Consola.h"

Consola::Consola() {
    setAnchoLinea(100);
    setTextoVolver("VOLVER");
}

void Consola::setAnchoLinea(int ancho) {
    _ancho_linea = ancho;
}

int Consola::getAnchoLinea() {
    return _ancho_linea;
}

void Consola::setTextoVolver(const std::string& texto) {
    strcpy(_texto_volver, texto.c_str());
}

std::string Consola::getTextoVolver() {
    return _texto_volver;
}

void Consola::limpiar() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void Consola::pausar() {
#ifdef _WIN32
    system("pause");
#else
    std::cout << "\nPresione ENTER para continuar...";
    std::cin.ignore();
    std::cin.get();
#endif
}

void Consola::imprimirLinea() {
    for (int i = 0; i < getAnchoLinea(); i++)
        std::cout << "-";
    std::cout << "\n";
}

void Consola::centrarYMostrar(const std::string& texto) {
    int espacios = (getAnchoLinea() - texto.length()) / 2;
    for (int i = 0; i < espacios; i++)
        std::cout << " ";
    std::cout << texto << "\n";
}

void Consola::mostrarOpcionVolver() {
    std::cout << "(0) " << getTextoVolver() << "\n";
}

void Consola::mostrarEncabezadoMenu(const std::string& titulo) {
    imprimirLinea();
    centrarYMostrar(titulo);
    imprimirLinea();
}

void Consola::mostrarPieMenu() {
    imprimirLinea();
    mostrarOpcionVolver();
}

void Consola::imprimirBool(bool valor, const std::string& textoSi, const std::string& textoNo) {
    std::cout << (valor ? textoSi : textoNo);
}

bool Consola::validarBool() {
    char input;
    while (true) {
        if (std::cin >> input && (input == 's' || input == 'S' || input == 'n' || input == 'N'))
            break;
        std::cin.clear();
        limpiarBuffer();
        std::cout << "Error: Ingrese 'S' para si o 'N' para no.\n";
    }
    return (input == 's' || input == 'S');
}

int Consola::validarInt() {
    int valor;
    while (!(std::cin >> valor)) {
        std::cin.clear();
        limpiarBuffer();
        std::cout << "Error: Ingrese un numero entero.\n";
    }
    return valor;
}

int Consola::validarInt(int minimo) {
    int valor;
    while (!(std::cin >> valor) || valor < minimo) {
        std::cin.clear();
        limpiarBuffer();
        std::cout << "Intente nuevamente, Ingrese un numero mayor o igual a " << minimo << ": ";
    }
    return valor;
}

int Consola::validarInt(int minimo, int maximo) {
    int valor;
    while (!(std::cin >> valor) || valor < minimo || valor > maximo) {
        std::cin.clear();
        limpiarBuffer();
        std::cout << "Error: Ingrese un numero entre " << minimo << " y " << maximo << ".\n";
    }
    return valor;
}

long long int Consola::validarLong() {
    long long int valor;
    while (!(std::cin >> valor)) {
        std::cin.clear();
        limpiarBuffer();
        std::cout << "Error: Ingrese un numero valido.\n";
    }
    return valor;
}

long long int Consola::validarLong(int minimo) {
    long long int valor;
    while (!(std::cin >> valor) || valor < minimo) {
        std::cin.clear();
        limpiarBuffer();
        std::cout << "Error: Ingrese un numero mayor o igual a " << minimo << ".\n";
    }
    return valor;
}

long long int Consola::validarLong(int minimo, int maximo) {
    long long int valor;
    while (!(std::cin >> valor) || valor < minimo || valor > maximo) {
        std::cin.clear();
        limpiarBuffer();
        std::cout << "Error: Ingrese un numero entre " << minimo << " y " << maximo << ".\n";
    }
    return valor;
}

double Consola::validarDouble() {
    double valor;
    while (!(std::cin >> valor)) {
        std::cin.clear();
        limpiarBuffer();
        std::cout << "Error: Ingrese un numero válido.\n";
    }
    return valor;
}

double Consola::validarDouble(double minimo) {
    double valor;
    while (!(std::cin >> valor) || valor < minimo) {
        std::cin.clear();
        limpiarBuffer();
        std::cout << "Error: Ingrese un numero mayor o igual a " << minimo << ".\n";
    }
    return valor;
}

double Consola::validarDouble(double minimo, double maximo) {
    double valor;
    while (!(std::cin >> valor) || valor < minimo || valor > maximo) {
        std::cin.clear();
        limpiarBuffer();
        std::cout << "Error: Ingrese un numero entre " << minimo << " y " << maximo << ".\n";
    }
    return valor;
}

char Consola::validarChar() {
    char valor;
    while (!(std::cin >> valor)) {
        std::cin.clear();
        limpiarBuffer();
        std::cout << "Error: Ingrese un caracter valido.\n";
    }
    return valor;
}

// Valida que se ingresen solamente letras o espacios, no mas que eso
std::string Consola::validarString() {
    std::string valor;
    while (true) {
        if (!std::getline(std::cin, valor)) {
            std::cin.clear();
            limpiarBuffer();
            std::cout << "Error: Ingrese un texto válido.\n";
            continue;
        }
        bool valido = true;
        for (char c : valor) {
            if ((c < 'A' || c > 'Z') && (c < 'a' || c > 'z') && c != ' ') {
                valido = false;
                break;
            }
        }
        if (!valor.empty() && valido) {
            return valor;
        } else {
            std::cout << "Ingrese nuevamente (solo letras): ";
        }
    }
}



void Consola::limpiarBuffer() {
    int aux;
    while ((aux = std::cin.get()) != '\n' && aux != EOF) {}
}

std::string Consola::rellenar(const std::string& texto, unsigned int longitud) {
    std::string resultado = texto;
    while (resultado.length() < longitud)
        resultado += " ";
    return resultado;
}

