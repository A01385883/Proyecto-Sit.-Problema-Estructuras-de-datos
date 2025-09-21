
#include <iostream>
#include <string>
#include <algorithm> // para sort de los meses a numeros

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::to_string;

//Clase Orden
class Orden{
private:
  string Mes;
  int Dia;
  int Hora;
  int Minuto;
  int Segundos;
  string Restaurante;
  int Costo;

public:
//Default Constructor
Orden(){
  this->Mes = "ene";
  this->Dia = 01;
  this->Hora = 01;
  this->Minuto = 01;
  this->Segundos = 01;
  this->Restaurante = "Cafeteria Tec";
  this->Costo = 100;
}
  Orden(string Mes, int Dia, int Hora, int Minuto, int Segundos, string Restaurante, int Costo){
    this -> Mes = Mes;
    this -> Dia = Dia;
    this -> Hora = Hora;
    this -> Minuto = Minuto;
    this -> Segundos = Segundos;
    this -> Restaurante = Restaurante;
    this -> Costo = Costo;
  }

//Mosrtrar Orden
string show(){
  return "Mes: " + Mes + "\nDia: " + to_string(Dia) + "\nHora: " + to_string(Hora) + "\nMinuto: " + to_string(Minuto) +"Segundos: " + to_string(Segundos) + "\nRestaurante: " + Restaurante + "\nCosto: " + to_string(Costo);}

//Sobrecarga Operadores
bool operator<(const Orden & otro){
  return this->Costo < otro.Costo;
}

};

/*Algoritmo Quick Sort:
Su peor caso es un Big de (N^2) en caso de que todos
los elementos esten ordenados, pero normalmente su caso comun
es de O(n*log(n))*/

int partition(Orden *A, int low, int high, bool asc=true) {
    Orden pivot = A[high]; // pivote al final
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (asc ? (A[j] < pivot) : (pivot < A[j])) {
            i++;
            Orden aux = A[i];
            A[i] = A[j];
            A[j] = aux;
        }
    }

    Orden aux = A[i + 1];
    A[i + 1] = A[high];
    A[high] = aux;

    return i + 1;
}

void quicksort(Orden *A, int low, int high) {
    if (low < high) {
        int pivot = partition(A, low, high);
        quicksort(A, low, pivot - 1);
        quicksort(A, pivot + 1, high);
    }
}

// Arreglo de meses (abreviados en orden)
const std::string meses[12] = {
//Enero es el unico con Minuscula en el de Ordenes.txt
    "ene", "Feb", "Mar", "Abr", "May", "Jun",
    "Jul", "Ago", "Sep", "Oct", "Nov", "Dic"
};

// Función que convierte un string de mes a número (1-12)
int mesAEntero(const std::string& mes) {
    for (int i = 0; i < 12; i++) {
        if (meses[i] == mes) {
            return i + 1; // +1 porque los arrays empiezan en 0
        }
    }
    return -1; // si no se encuentra
}

int main (){
  //Aun no es necesario de mayor a menor
  int i, opcion, n;
do{
  //Menu
  cout << "\nOrdenes de Restaurantes Situacion Problema" << endl;
  cout << "1.- Ver Primeros 10 Elementos" << endl;
  cout << "2.- Buscar Elementos en Cierta Fecha"<< endl;
  cout << "0.- Salir"<< endl;
  cout << "Opcion: ";
  cin >> opcion;

  if(opcion == 0){
    cout << "\nSaliendo del Programa..." << endl;
    break;

    switch(opcion){
      case 1:
      cout << "Imprimir 10 primeros datos ya ordenados" << endl;
      break;
      case 2: 
      cout << "Ordenar los datos" << endl;
      break;
      default:
      cout << "Opcion no valida." << endl;
    }
  }
} while(opcion != 0);
}
