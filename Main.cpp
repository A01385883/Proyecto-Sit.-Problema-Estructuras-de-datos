#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

// Clase Orden 
class Orden {
private:
    string Mes;
    int Dia;
    int Hora;
    int Minuto;
    int Segundos;
    string Restaurante;
    string Pedido;
    int Costo;

public:
    Orden() {
        Mes = "ene";
        Dia = 1;
        Hora = 1;
        Minuto = 1;
        Segundos = 1;
        Restaurante = "Cafeteria Tec";
        Pedido = "Sandwich";
        Costo = 100;
    }

    Orden(string Mes, int Dia, int Hora, int Minuto, int Segundos, string Restaurante, string Pedido, int Costo) {
        this->Mes = Mes;
        this->Dia = Dia;
        this->Hora = Hora;
        this->Minuto = Minuto;
        this->Segundos = Segundos;
        this->Restaurante = Restaurante;
        this->Pedido = Pedido;
        this->Costo = Costo;
    }

    string show() {
        return "Mes: " + Mes +
               "\nDia: " + to_string(Dia) +
               "\nHora: " + to_string(Hora) +
               "\nMinuto: " + to_string(Minuto) +
               "\nSegundos: " + to_string(Segundos) +
               "\nRestaurante: " + Restaurante +
               "\nPedido: " + Pedido +
               "\nCosto: " + to_string(Costo) + "\n";
    }

    bool operator<(const Orden &otro) {
        return this->Costo < otro.Costo;
    }
};

// Lectura del archivo 
int leerOrdenes(const string &filename, Orden ordenes[], int maxOrdenes) {
    ifstream archivo(filename);
    if (!archivo.is_open()) {
        cerr << "Error al abrir archivo\n";
        return 0;
    }

    string linea;
    int count = 0;

    while (getline(archivo, linea) && count < maxOrdenes) {
        stringstream ss(linea);

        string mes;
        int dia;
        string tiempo; // "19:39:45"

        // 1) Obtener mes, día y tiempo
        ss >> mes >> dia >> tiempo;

        // 2) Separar tiempo en hora:minuto:segundos
        int hora, minuto, segundos;
        size_t p1 = tiempo.find(':');
        size_t p2 = tiempo.find(':', p1 + 1);

        hora = stoi(tiempo.substr(0, p1));
        minuto = stoi(tiempo.substr(p1 + 1, p2 - p1 - 1));
        segundos = stoi(tiempo.substr(p2 + 1));

        // 3) Restaurante (entre "R:" y "O:")
        size_t posR = linea.find("R:");
        size_t posO = linea.find("O:");
        string restaurante = linea.substr(posR + 2, posO - (posR + 2));
        // quitar espacios extra al inicio
        if (!restaurante.empty() && restaurante[0] == ' ') {
            restaurante = restaurante.substr(1);
        }

        // 4) Pedido y Costo (después de "O:")
        string pedidoYCosto = linea.substr(posO + 2);
        size_t posParA = pedidoYCosto.find("(");
        size_t posParC = pedidoYCosto.find(")");

        string pedido = pedidoYCosto.substr(0, posParA);
        if (!pedido.empty() && pedido[0] == ' ') {
            pedido = pedido.substr(1);
        }
        int costo = stoi(pedidoYCosto.substr(posParA + 1, posParC - posParA - 1));

        // 5) Crear la orden
        Orden o(mes, dia, hora, minuto, segundos, restaurante, pedido, costo);
        ordenes[count] = o;
        count++;
    }

    return count;
}

// Main
int main() {
    const int MAX_ORDENES = 10000;
    Orden ordenes[MAX_ORDENES];
    int totalOrdenes = leerOrdenes("orders.txt", ordenes, MAX_ORDENES);

    cout << "Se cargaron " << totalOrdenes << " ordenes.\n";

    // Probar: imprimir las primeras 3
    for (int i = 0; i < 10 && i < totalOrdenes; i++) {
        cout << ordenes[i].show() << endl;
    }

    return 0;
}
