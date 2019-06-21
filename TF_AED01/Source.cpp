#include <iostream>
#include <string>
#include <vector>
#include "Dataframe.h"

using namespace std;

int main() {
	Dataframe *df;
	df = new Dataframe();
	cout << "Presione algo para empezar a importar" << endl;
	system("pause>NULL");
	df->importar("airlines.csv");
	system("pause>NULL");
	df->imprimir(1);
	df->imprimir(2);
	system("pause>NULL");
	return 0;
}