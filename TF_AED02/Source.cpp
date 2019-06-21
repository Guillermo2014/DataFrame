#include <iostream>
#include <string>
#include <vector>
#include "Dataframe.h"

using namespace std;

int main() {
	Dataframe *df;
	df = new Dataframe();
	df->importar("airlines.csv");
	system("pause");
	df->imprimir(1);
	system("pause");
	df->limpiarSeleccion();
	df->agregarSeleccion(2);
	df->agregarSeleccion(5);
	df->agregarSeleccion(7);
	df->seleccionar();
	df->exportar("datitos.csv");
	df->imprimir(1);

	int f, c;
	while (false){
		cout << endl << endl;
		cout << "Inserte fila: "; cin >> f;
		cout << "Inserte columna: "; cin >> c;
		df->consultar(f, c);
	}
	system("pause>NULL");
	return 0;
}