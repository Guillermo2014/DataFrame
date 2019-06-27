#include <iostream>
#include <string>
#include <vector>
#include "Dataframe.h"

using namespace std;


void Opcion1(Dataframe*obj);
void Opcion2(Dataframe*obj);
void Opcion3(Dataframe*obj);
void Opcion4(Dataframe*obj);
void Opcion5(Dataframe*obj);
void Opcion6(Dataframe*obj);
void Opcion7(Dataframe*obj);

int main() {
	Dataframe *df;
	df = new Dataframe();
	string direc;
	char op;
	char op1;

	df->importar("datosDf.csv");
	system("pause");
	do
	{
		System::Console::Clear();
		cout << "====[MENU DATAFRAME ALGORITMOS 2019]=====" << endl;
		cout << "1.-Imprimir" << endl;
		cout << "2.-Seleccionar Columna" << endl;
		cout << "3.-Filtrar una Columna" << endl;
		cout << "4.-Filtrar dos Columnas" << endl;
		cout << "5.-Ordenar Columna Alfabeticamente" << endl;
		cout << "6.-Ordenar Columna Numericamente" << endl;
		cout << "7.-Exportar Archivo" << endl;
		cout << "0.-Salir" << endl;
		cout << "Digite una opcion: " << endl;
		cin >> op;
		cout << endl;

		switch (op)
		{
		case '1':
			Opcion1(df);
			break;

		case '2':
			Opcion2(df);
			break;

		case '3':
			cout << "=====FILTRAR COLUMNA=====" << endl;
			Opcion3(df);
			break;

		case '4':
			cout << "=====FILTRAR COLUMNA=====" << endl;
			Opcion4(df);
			break;

		case '5':
			cout << "=====ORDENAR COLUMNA=====" << endl;
			Opcion5(df);
			break;

		case '6':
			Opcion6(df);
			break;

		case '7':
			Opcion7(df);
			break;

		case '0':
			cout << "Gracias." << endl;
			break;
		}
		system("pause");

	} while (op!='0');
	
	return 0;
}

void Opcion1(Dataframe*obj){
	int pag;
	cout << "Digite pagina a imprimir: " << endl;
	cin >> pag;
	obj->imprimir(pag);
}

void Opcion2(Dataframe*obj){
	int col;
	cout << "Digite columna a seleccionar" << endl;
	cout << "Ingrese 0 para romper el ciclo" << endl;
	obj->limpiarSeleccion();
	do
	{
		cout << "Columna: " << endl;
		cin >> col;
		if (col == 0) { break; }
		obj->agregarSeleccion(col);
	} while (true);
	obj->seleccionar();
}

void Opcion3(Dataframe*obj) {
	int x;
	string dato;
	int filtro;
	cout << "Ingrese la columna a filtrar" << endl;
	cin >> x;
	cout << "1.-Mayor que" << endl;
	cout << "2.-Menor que" << endl;
	cout << "3.-Igual a" << endl;
	cout << "4.-Inicia con" << endl;
	cout << "5.-Finaliza con" << endl;
	cout << "6.-Contiene" << endl;
	cout << "7.-No contiene" << endl;
	cout << "Ingrese el filtro: " << endl;
	cin >> filtro;
	cout << "Ingrese el parametro" << endl;
	cin >> dato;
	obj->limpiarSeleccion();
	obj->agregarSeleccion(x);
	switch (filtro)
	{
	default:
		Opcion3(obj);
		break;

	case 1:
		obj->filtrar(mayor_que, dato);
		cout << endl;
		break;

	case 2:
		obj->filtrar(menor_que, dato);
		cout << endl;
		break;

	case 3:
		obj->filtrar(igual_a, dato);
		cout << endl;
		break;

	case 4:
		obj->filtrar(inicia_con, dato);
		cout << endl;
		break;

	case 5:
		obj->filtrar(finaliza_con, dato);
		cout << endl;
		break;

	case 6:
		obj->filtrar(contiene, dato);
		cout << endl;
		break;

	case 7:
		obj->filtrar(no_contiene, dato);
		cout << endl;
		break;
	}
}

void Opcion4(Dataframe*obj) {
	int x;
	int y;
	string dato;
	int filtro;
	cout << "Ingrese la columna 1 a filtrar" << endl;
	cin >> x;
	cout << "Ingrese la columna 2 a filtrar" << endl;
	cin >> y;
	cout << "1.-Mayor que" << endl;
	cout << "2.-Menor que" << endl;
	cout << "3.-Igual a" << endl;
	cout << "4.-Inicia con" << endl;
	cout << "5.-Finaliza con" << endl;
	cout << "6.-Contiene" << endl;
	cout << "7.-No contiene" << endl;
	cout << "Ingrese el filtro: " << endl;
	cin >> filtro;
	cout << "Ingrese el parametro" << endl;
	cin >> dato;
	obj->limpiarSeleccion();
	obj->agregarSeleccion(x);
	obj->agregarSeleccion(y);

	switch (filtro)
	{
	default:
		Opcion3(obj);
		break;

	case 1:
		obj->filtrar(mayor_que, dato);
		cout << endl;
		break;

	case 2:
		obj->filtrar(menor_que, dato);
		cout << endl;
		break;

	case 3:
		obj->filtrar(igual_a, dato);
		cout << endl;
		break;

	case 4:
		obj->filtrar(inicia_con, dato);
		cout << endl;
		break;

	case 5:
		obj->filtrar(finaliza_con, dato);
		cout << endl;
		break;

	case 6:
		obj->filtrar(contiene, dato);
		cout << endl;
		break;

	case 7:
		obj->filtrar(no_contiene, dato);
		cout << endl;
		break;
	}
}

void Opcion5(Dataframe*obj) {
	int col;
	cout << "Digite columna a ordenar: " << endl;
	cin >> col;
	obj->limpiarSeleccion();
	obj->agregarSeleccion(col);
	obj->ordenar(alfabetico);
}

void Opcion6(Dataframe*obj){
	int col;
	cout << "Digite columna a ordenar: " << endl;
	cin >> col;
	obj->limpiarSeleccion();
	obj->agregarSeleccion(col);
	obj->ordenar(numerico);
}

void Opcion7(Dataframe*obj){
	string dir;
	cout << "Digite el directorio a exportar: " << endl;
	cin >> dir;
	obj->exportar(dir);
}