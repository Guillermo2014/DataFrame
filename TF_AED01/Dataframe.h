#pragma once
#include "DataFrameUtil.h"

enum tipo{ ascendente, descendente };

class Dataframe {
private:
	vector<int> seleccion;
	DF::ArbolFIL *datos;
	int filas;
	int columnas;
	int paginas;
	bool cargado;
public:
	Dataframe(){
		filas = NULL;
		columnas = NULL;
		cargado = false;
		datos = new DF::ArbolFIL();
	}
	~Dataframe(){

	}
	void importar(string dir) {
		DF::Nodo *nodo;
		DF::ArbolCOL *columna;
		ifstream archivo;
		string registro, dato;

		archivo.open(dir);
		if (!archivo.fail()) {
			filas = 0;
			while (getline(archivo, registro)) {
				++filas;
				stringstream ss(registro);
				columna = new DF::ArbolCOL(filas);
				datos->insertar(columna);
				int col = 0;
				while (getline(ss, dato, separador)) {
					++col;
					if (columnas != NULL) {
						if (col <= columnas) {
							nodo = new DF::Nodo(dato, col);
							columna->insertar(nodo);
						}
						else {
							color(14); 
							cout << "(!) Advertencia: la linea " << filas;
							cout << " del archivo tiene valores de mas." << endl;
							color();
						}
					}
					else {
						nodo = new DF::Nodo(dato, col);
						columna->insertar(nodo);
					}
				}
				if (columnas == NULL) { columnas = col; }
				else { columna->verificar(columnas); }
			}
			paginas = columnas / max_col;
			if (paginas * max_col < columnas) { ++paginas; }

			color(10);
			cout << "El dataframe fue cargado de ";
			color(); cout << dir << endl;
			color(10); cout << "- Columnas: ";
			color(); cout << columnas << endl;
			color(10); cout << "- Filas: ";
			color(); cout << filas << endl;
			color(10); cout << "- Paginas: ";
			color(); cout << paginas << endl;
			cargado = true;
		}
		else {
			color(12);
			cout << "(!) " << dir << " inexistente o corrupto. " << endl;
			color();
		}
		archivo.close();
	}
	void exportar(string dir) {
		ofstream *archivo;
		archivo = new ofstream();
		archivo->open(dir);
		if (!archivo->fail()) {
			datos->exportar(archivo);
			color(10); 
			cout << "El dataframe fue exportado a ";
			color(); 
			cout << dir << endl;
		}
		else {
			color(12);
			cout << "(!) " << dir << " no se pudo abrir." << endl;
			color();
		}
		archivo->close();
	}
	void imprimir(int pagina = 1) {
		if (cargado == true) {
			if (pagina > 0 && pagina <= paginas) {
				/*pantallaCompleta();*/
				string fila;
				DF::ArbolCOL *aux;
				for (int i = 1; i <= filas; ++i) {
					fila = std::to_string(i);
					fila.resize(6);
					color(12); cout << fila;
					color(); cout << " | ";
					aux = datos->buscar(i);
					aux->imprimir(pagina);
					cout << endl;
				}
				cout << "       | ";
				for (int i = ((pagina * max_col) - max_col); i < max_col*pagina; ++i) {
					if (i + 1 > columnas) { break; }
					fila = std::to_string(i + 1);
					fila.resize(max_char);
					color(12); cout << fila;
					color(); cout << " | ";
				}
				cout << endl << endl;
				color(12);
				cout << "(" << filas << " F  " << columnas << " C) ";
				cout << "Se imprimio la pagina: " << pagina << " de " << paginas << endl;

				color();
			}
		}
	}
	void limpiarSeleccion() {
		if (cargado == false) {
			color(12);
			cout << "(!) Cargue un dataframe primero. " << endl;
			color();
			return;
		}
		seleccion.clear();
	}
	void agregarSeleccion(int columna) {
		if (cargado == false) {
			color(12); 
			cout << "(!) Cargue un dataframe primero." << endl;
			color();
			return;
		}
		if (columna > 0 && columna <= columnas) {
			seleccion.push_back(columna);
		}
		else {
			color(12); cout << "(!) Parametro erroneo." << endl;
			color();
		}
	}
	void color(int k = 15) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, k);
		//15: Blanco
		//12: Rojo
	}
	/*void pantallaCompleta() {
		SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);
	}*/
};