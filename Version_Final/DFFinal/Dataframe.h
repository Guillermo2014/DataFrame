#pragma once
#include "DataFrameUtil.h"

enum ordenamiento{ numerico, alfabetico };
enum filtro{ mayor_que, menor_que, igual_a, inicia_con, finaliza_con, contiene, no_contiene };

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
	void importar(string dir) {
		clock_t begin = clock();
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
			clock_t end = clock();
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
			double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
			color(8);
			cout << "Se cargaron " << columnas *filas << " datos al Df en ";
			cout << elapsed_secs << " segundos." << endl;
			color();
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
	string consultar(int fila, int columna) {
		if (fila > 0 && fila<=filas && columna > 0 && columna <= columnas) {
			DF::Nodo *aux;
			aux = datos->buscar(fila)->buscar(columna);
			if (aux != nullptr) {
				return aux->getDato();
			}
			else {
				return "error";
			}
		}
	}
	void imprimir(int pagina = 1, int nFila = 1) {
		if (cargado == true) {
			if (filas == 0) {
				color(14);
				cout << "(!) Advertencia: el Dataframe está vacio." << endl;
				color();
			}
			if (pagina > 0 && pagina <= paginas) {
				pantallaCompleta();
				string fila;
				DF::ArbolCOL *aux;
				for (int i = nFila; i <= filas; ++i) {
					fila = std::to_string(i);
					fila.resize(7);
					color(12); 
					cout << fila;
					if (i % 2 == 0) { color(8); }
					else { color(); } 
					cout << " | ";
					aux = datos->buscar(i);
					if (aux != nullptr) {
						aux->imprimir(pagina);
					}
					else {
						cout << "Uups! Algo anda mal. No se pudo acceder a los datos.";
					}
					cout << endl;
				}
				cout << "        | ";
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
	void seleccionar() {
		if (cargado == false) { return; }
		if (seleccion.empty() == true) { return; }
		clock_t begin = clock();
		DF::ArbolCOL *columna;
		for (int i = 1; i <= filas; ++i) {
			columna = datos->buscar(i);
			for (int j = 1; j <= columnas; ++j) {
				if (verificar(j) == false) {
					columna->eliminar(j);
				}
			}
			columna->arreglarColumnas();
		}
		columnas = seleccion.size();
		paginas = columnas / max_col;
		if (paginas * max_col < columnas) { ++paginas; }

		clock_t end = clock();
		double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
		cout << "La accion tomo " << elapsed_secs << " segundos." << endl;
	}
	void filtrar(filtro tipo, string dato) {
		if (seleccion.empty() == true) {
			return;
		}
		else if (seleccion.size() == 1) {
			filtrar(tipo, dato, seleccion.at(0));
		}
		else if(seleccion.size() >= 2){
			filtrar(tipo, dato, seleccion.at(0), seleccion.at(1));
		}
	}
	void ordenar(ordenamiento tipo) {
		if (cargado == false) { return; }
		if (seleccion.empty() == true) { return; }
		if (tipo == numerico) {
			ordenar(tipo, seleccion.at(0));
		}
		else if (tipo == alfabetico) {
			ordenar(tipo, seleccion.at(0));
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
		if (columna > 0 && columna <= columnas && verificar(columna) == false) {
			seleccion.push_back(columna);
		}
		else {
			color(12); cout << "(!) Parametro erroneo." << endl;
			color();
		}
	}
	~Dataframe() {

	}
private:
	void ordenar(ordenamiento tipo, int columna) {
		DF::ArbolFIL *nuevo;
		DF::ArbolCOL *aux;
		nuevo = new DF::ArbolFIL();
		if (tipo == numerico) {
			for (int i = 1; i <= filas; ++i) {
				aux = datos->buscar(i);
				if (aux != nullptr) {
					DF::ArbolCOL *col;
					col = new DF::ArbolCOL(stof(aux->buscar(columna)->getDato()));
					col->setRaiz(aux->getRaiz());
					col->setSize(aux->getSize());
					nuevo->insertar(col);
				}
				datos->eliminar(i);
			}
		}
		else if (tipo == alfabetico) {
			for (int i = 1; i <= filas; ++i) {
				aux = datos->buscar(i);
				if (aux != nullptr) {
					DF::ArbolCOL *col;
					string dato = aux->buscar(columna)->getDato();
					int valorascii = (int)dato.at(0);
					col = new DF::ArbolCOL(valorascii);
					col->setRaiz(aux->getRaiz());
					col->setSize(aux->getSize());
					nuevo->insertar(col);
				}
				datos->eliminar(i);
			}
		}
		else {
			return;
		}
		nuevo->arreglarFilas();
		datos = nuevo;
	}
	void filtrar(filtro tipo, string dato, int columna) {
		string consulta;
		int resultados = 0;
		if (tipo == mayor_que) {
			for (int i = 1; i <= filas; ++i) {
				consulta = consultar(i, columna);
				if (stof(consulta) > stof(dato)) {
					++resultados;
				}
				else {
					datos->eliminar(i);
				}
			}
		}
		else if (tipo == menor_que) {
			for (int i = 1; i <= filas; ++i) {
				consulta = consultar(i, columna);
				if (stof(consulta) < stof(dato)) {
					++resultados;
				}
				else {
					datos->eliminar(i);
				}
			}
		}
		else if (tipo == igual_a) {
			for (int i = 1; i <= filas; ++i) {
				consulta = consultar(i, columna);
				if (consulta == dato) {
					++resultados;
				}
				else {
					datos->eliminar(i);
				}
			}
		}
		else if (tipo == inicia_con) {
			for (int i = 1; i <= filas; ++i) {
				consulta = consultar(i, columna);
				if (consulta.find(dato) == 0) {
					++resultados;
				}
				else {
					datos->eliminar(i);
				}
			}
		}
		else if (tipo == finaliza_con) {
			for (int i = 1; i <= filas; ++i) {
				consulta = consultar(i, columna);
				if (endsWith(consulta, dato) == true) {
					++resultados;
				}
				else {
					datos->eliminar(i);
				}
			}
		}
		else if (tipo == contiene) {
			for (int i = 1; i <= filas; ++i) {
				consulta = consultar(i, columna);
				if (consulta.find(dato) != std::string::npos) {
					++resultados;
				}
				else {
					datos->eliminar(i);
				}
			}
		}
		else if (tipo == no_contiene) {
			for (int i = 1; i <= filas; ++i) {
				consulta = consultar(i, columna);
				if (consulta.find(dato) == std::string::npos) {
					++resultados;
				}
				else {
					datos->eliminar(i);
				}
			}
		}
		else {
			return;
		}
		datos->arreglarFilas();
		filas = resultados;
		color(10); cout << "Columna filtrada: "; color();
		cout << columna << endl;
		color(10); cout << "Resultados en total: "; color();
		cout << resultados << endl;
		if (filas == 0) {
			color(14);
			cout << "(!) Advertencia: el Dataframe ahora está vacio." << endl;
			color();
		}
	}
	void filtrar(filtro tipo, string dato, int columna1, int columna2) {
		DF::ArbolFIL *nuevoDatos;
		string consulta;
		string consulta2;
		int resultados = 0;
		nuevoDatos = new DF::ArbolFIL();
		if (tipo == mayor_que) {
			for (int i = 1; i <= filas; ++i) {
				consulta = consultar(i, columna1);
				consulta2 = consultar(i, columna2);
				if (stof(consulta) > stof(dato) &&
					stof(consulta2) > stof(dato)) {
					++resultados;
				}
				else {
					datos->eliminar(i);
				}
			}
		}
		else if (tipo == menor_que) {
			for (int i = 1; i <= filas; ++i) {
				consulta = consultar(i, columna1);
				consulta2 = consultar(i, columna2);
				if (stof(consulta) < stof(dato) &&
					stof(consulta2) < stof(dato)) {
					++resultados;
				}
				else {
					datos->eliminar(i);
				}
			}
		}
		else if (tipo == igual_a) {
			for (int i = 1; i <= filas; ++i) {
				consulta = consultar(i, columna1);
				consulta2 = consultar(i, columna2);
				if (consulta == dato &&
					consulta2 == dato) {
					++resultados;
				}
				else {
					datos->eliminar(i);
				}
			}
		}
		else if (tipo == inicia_con) {
			for (int i = 1; i <= filas; ++i) {
				consulta = consultar(i, columna1);
				consulta2 = consultar(i, columna2);
				if (consulta.find(dato) == 0 &&
					consulta2.find(dato) == 0) {
					++resultados;
				}
				else {
					datos->eliminar(i);
				}
			}
		}
		else if (tipo == finaliza_con) {
			for (int i = 1; i <= filas; ++i) {
				consulta = consultar(i, columna1);
				consulta2 = consultar(i, columna2);
				if (endsWith(consulta, dato) == true &&
					endsWith(consulta2, dato) == true) {
					++resultados;
				}
				else {
					datos->eliminar(i);
				}
			}
		}
		else if (tipo == contiene) {
			for (int i = 1; i <= filas; ++i) {
				consulta = consultar(i, columna1);
				consulta2 = consultar(i, columna2);
				if (consulta.find(dato) != std::string::npos &&
					consulta2.find(dato) != std::string::npos) {
					++resultados;
				}
				else {
					datos->eliminar(i);
				}
			}
		}
		else if (tipo == no_contiene) {
			for (int i = 1; i <= filas; ++i) {
				consulta = consultar(i, columna1);
				consulta2 = consultar(i, columna1);
				if (consulta.find(dato) == std::string::npos &&
					consulta2.find(dato) == std::string::npos) {
					++resultados;
				}
				else {
					datos->eliminar(i);
				}
			}
		}
		else {
			return;
		}
		datos->arreglarFilas();
		filas = resultados;
		color(10); cout << "Columnas filtradas: "; color();
		cout << columna1; 
		color(10); cout << " y "; color();
		cout << columna2 << endl;
		color(10); cout << "Resultados en total: "; color();
		cout << resultados << endl;
		if (filas == 0) {
			color(14);
			cout << "(!) Advertencia: el Dataframe ahora está vacio." << endl;
			color();
		}
	}
	bool verificar(int col) {
		for (int i = 0; i < seleccion.size(); ++i) {
			if (col == seleccion.at(i)) {
				return true;
			}
		}
		return false;
	}
	bool endsWith(const std::string &mainStr, const std::string &toMatch)
	{
		if (mainStr.size() >= toMatch.size() &&
			mainStr.compare(mainStr.size() - toMatch.size(), toMatch.size(), toMatch) == 0)
			return true;
		else
			return false;
	}
	void color(int k = 15) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, k);
		//15: Blanco
		//12: Rojo
	}
	void pantallaCompleta() {
		SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);
	}
};