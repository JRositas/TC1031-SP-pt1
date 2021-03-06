/* 
El programa realizará el ordenamiento de las entradas por UBI + Fecha , almacenadas en un vector llamado 'mivect'.  
Dará la opción de solicitar al usuario la serie a buscar , que en este caso son los 3 caracteres de UBI. 
Por ende, desplegará los puntos de Entrada al canal de los buques con los caracteres ingresados de forma ordenada 'UBI + Fecha'.
*/

// Integrantes (Equipo 12) :
// Daniel Evaristo Escalera Bonilla - A00831289
// José Arnoldo Rositas Salinas - A00829760
// Ángela Felicia Guajardo Olveda - A00829821

// SP TC1031
// 06 Sep 2021

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include "Entrada.h"

using namespace std;

// Complejidad O(n) Lineal, dependiente del largo de "date"
int date2Int(string date){
    int dateCode = 0;
    int aux = 0;
    int i = 0;
    while(date[i] != '-'){
        aux *= 10;
        aux += (date[i++] - '0');
    }
    dateCode += aux;

    string month = "";
    while(date[++i] != '-'){
        month += date[i];
    }
    int monthCode = 0;
    if(month == "jan"){
        monthCode = 1;
    } else if(month == "feb"){
        monthCode = 2;
    } else if(month == "mar"){
        monthCode = 3;
    } else if(month == "apr"){
        monthCode = 4;
    } else if(month == "may"){
        monthCode = 5;
    } else if(month == "jun"){
        monthCode = 6;
    } else if(month == "jul"){
        monthCode = 7;
    } else if(month == "aug"){
        monthCode = 8;
    } else if(month == "sep"){
        monthCode = 9;
    } else if(month == "oct"){
        monthCode = 10;
    } else if(month == "nov"){
        monthCode = 11;
    } else if(month == "dec"){
        monthCode = 12;
    }
    dateCode += (monthCode * 100);

    aux = 0;
    while(++i < date.length()){
        aux *= 10;
        aux += (date[i] - '0');
    }
    dateCode += (aux * 10000);

    return dateCode;
}

// Complejidad: 0(1) Revisa si los UBI de las entradas son iguales, si lo son, compara las fechas, si nó compara los UBI
bool comparaDate( Entrada x, Entrada y) // compara fecha por fecha
{
  if (x.getUbi() == y.getUbi()) // checar si hay empate, si hay empate ordena por fecha
  {
    return x.getFechaCode() < y.getFechaCode(); // cual de las dos fechas es más grande
  }
  return x.getUbi() < y.getUbi();
}


//Complejidad: O(1) Regresa los primeros tres caractéres de un código UBI ingresado
string countryFromUbi(string ubi){
    string pais;
    for (int i = 0; i < 3; i++)
    {
        pais += ubi[i];
    }
    return pais;
}



int main(){

    // Creación de variables
    int fechaCode;
    char puntoEntrada;
    string archivo, fecha, ubi, hora, pais, paisABuscar, paisaux;
    Entrada *objAuxiliar; //Crear variable que guarde el objeto fuera del ciclo
    vector<string> listaPaises;
    vector<string>::iterator inicioBuscado, finBuscado;
    vector<Entrada> mivect;

    //Leer archivo
    ifstream archivoSuez;

    cin >> archivo;

    archivoSuez.open(archivo);

    //Almacenar entradas como objetos en un vector
    while (archivoSuez >> fecha >> hora >> puntoEntrada >> ubi)
    {
        pais = countryFromUbi(ubi); //Extraer los los primeros carácteres del UBI y guardarlos como el país de origen 
        fechaCode = date2Int(fecha); //Convertir fechas a enteros para permitir la comparación
        objAuxiliar = new Entrada(fecha, fechaCode, hora, puntoEntrada, ubi, pais); //Igualas la variable al objAuxiliar
        mivect.push_back(*objAuxiliar);  //push_back() es el metodo que guarda los valores en el vector
    }

    //Complejidad O(nlog2(n)), ordena las entradas en base a un comparador.
    sort(mivect.begin(), mivect.end(), comparaDate);

    //Guarda los identificadores de paises de las entradas en un vector.
    for(int i = 0; i < mivect.size(); i++){
        paisaux = mivect[i].getPais();
        listaPaises.push_back(paisaux);
    } 

    //Se solicita un código de país a buscar
    cin >> paisABuscar;
    
    // Complejidad log2(n) + 1, funciones que regresan los apuntadores que indican el rango de índices donde se encuentran las entradas de un tipo de páis
    inicioBuscado = lower_bound(listaPaises.begin(), listaPaises.end(), paisABuscar);
    finBuscado = upper_bound(listaPaises.begin(), listaPaises.end(), paisABuscar);

    //Despliega los datos de las entradas del país buscado
    for(int i = (inicioBuscado- listaPaises.begin()); i < (finBuscado- listaPaises.begin()) ; i++){
       mivect[i].mostrar();
    }
  
}
