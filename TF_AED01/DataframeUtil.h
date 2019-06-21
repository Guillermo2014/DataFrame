#pragma once
#include <windows.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#define separador ','
#define max_col 10 // Máximo de columnas por página
#define max_char 10 // Máximo de caracteres por celda
#define ignorarLinea1 true // Ignorar la primera linea  del archivo

using std::cin;
using std::endl;
using std::cout;
using std::string;
using std::vector;
using std::getline;
using std::ifstream;
using std::ofstream;
using std::stringstream;
using System::String;

//Celdas
namespace DF {
	//
	class Nodo {
	private:
		Nodo *izquierda;
		Nodo *derecha;
		string dato;
		int altura;
		int columna;
	public:
		Nodo(string dato, int columna) {
			izquierda = nullptr;
			derecha = nullptr;
			this->dato = dato;
			this->columna = columna;
			altura = 0;
		}
		void setIzquierda(Nodo *izquierda) {
			this->izquierda = izquierda;
		}
		void setDerecha(Nodo *derecha) {
			this->derecha = derecha;
		}
		void setAltura(int altura) {
			this->altura = altura;
		}
		Nodo *&getDerecha() {
			return derecha;
		}
		Nodo *&getIzquierda() {
			return izquierda;
		}
		string getDato() {
			return dato;
		}
		int getAltura() {
			return altura;
		}
		int getColumna() {
			return columna;
		}
		~Nodo() {}
	};
}

//Columnas
namespace DF
{
	class ArbolCOL {
	private:
		Nodo *raiz;
		int size;
		int altura;
		string fila;
		ArbolCOL *izquierda;
		ArbolCOL *derecha;
	private:
		int _altura(Nodo*nodo) {
			if (nodo == nullptr) {
				return -1;
			}
			return nodo->getAltura();
		}
		bool _insertar(Nodo*& padre, Nodo*& nodo) {
			if (padre == nullptr) {
				padre = nodo;
				if (raiz == nullptr) { raiz = nodo; }
			}
			else if (nodo->getColumna() < padre->getColumna()) {
				_insertar(padre->getIzquierda(), nodo);
			}
			else if (nodo->getColumna() > padre->getColumna()) {
				_insertar(padre->getDerecha(), nodo);
			}
			// Inicio de balanceo
			int hi = _altura(padre->getIzquierda());
			int hd = _altura(padre->getDerecha());
			int d = hd - hi;
			if (d > 1) {
				int hni = _altura(padre->getDerecha()->getIzquierda());
				int hnd = _altura(padre->getDerecha()->getDerecha());
				if (hni>hnd) {
					rotarDerecha(padre->getDerecha()->getIzquierda(), padre->getDerecha(), padre->getDerecha());
				}
				rotarIzquierda(padre, padre->getDerecha(), padre);
			}
			else if (d < -1) {
				int hni = _altura(padre->getIzquierda()->getIzquierda());
				int hnd = _altura(padre->getIzquierda()->getDerecha());
				if (hnd > hni) {
					rotarIzquierda(padre->getIzquierda(), padre->getIzquierda()->getDerecha(), padre->getIzquierda());
				}
				rotarDerecha(padre->getIzquierda(), padre, padre);
			}
			// Fin de balanceo
			hi = _altura(padre->getIzquierda());
			hd = _altura(padre->getDerecha());
			padre->setAltura(1 + ((hi > hd) ? hi : hd));
			return true;
		}
		void rotarDerecha(Nodo*&x, Nodo*y, Nodo*&p) {
			p = x;
			y->setIzquierda(x->getDerecha());
			p->setDerecha(y);
		}
		void rotarIzquierda(Nodo*x, Nodo*&y, Nodo*&p) {
			p = y;
			x->setDerecha(y->getIzquierda());
			p->setIzquierda(x);
		}
		Nodo* _buscar(Nodo*nodo, int columna) {
			if (nodo == nullptr) {
				return nullptr;
			}
			else if (nodo->getColumna() == columna) {
				return nodo;
			}
			else if (columna < nodo->getColumna()) {
				return _buscar(nodo->getIzquierda(), columna);
			}
			else {
				return _buscar(nodo->getDerecha(), columna);
			}
		}
	public:
		ArbolCOL(int _fila) {
			izquierda = nullptr;
			derecha = nullptr;
			raiz = nullptr;
			size = 0;
			fila = std::to_string(_fila);
			fila.resize(6);
		}
		void verificar(int columnas) {
			while (size < columnas) {
				Nodo *aux;
				aux = new Nodo("null", size+1);
				insertar(aux);
			}
		}
		bool insertar(Nodo *nodo) {
			++size;
			return _insertar(raiz, nodo);
		}
		void imprimir(int pagina) {
			if (raiz != nullptr) {
				Nodo *aux;
				string dato;
				int i = ((pagina*max_col) - max_col) + 1;
				for (int k = 1; k <= max_col; ++k) {
					if (i > size) { break; }
					aux = buscar(i);
					dato = aux->getDato();
					dato.resize(max_char);
					cout << dato << " | ";
					++i;
				}
			}
		}
		void exportar(ofstream *archivo) {
			if (raiz != nullptr) {
				Nodo *aux;
				int n = 1;
				for (int i = 1; i <= size; ++i) {
					aux = buscar(i);
					*archivo << aux->getDato();
					if (i != size) {
						*archivo << separador;
					}
				}
				*archivo << endl;
			}
		}

		int getAltura() {
			return altura;
		}
		int getFila() {
			return stoi(fila);
		}
		Nodo*getRaiz() {
			return raiz;
		}
		Nodo* buscar(int columna) {
			return _buscar(raiz, columna);
		}
		void setIzquierda(ArbolCOL *izquierda) {
			this->izquierda = izquierda;
		}
		void setDerecha(ArbolCOL *derecha) {
			this->derecha = derecha;
		}
		void setAltura(int altura) {
			this->altura = altura;
		}
		ArbolCOL *&getDerecha() {
			return derecha;
		}
		ArbolCOL *&getIzquierda() {
			return izquierda;
		}
		~ArbolCOL() {}
	};
}

//Filas
namespace DF{
	class ArbolFIL {
	private:
		ArbolCOL *raiz;
		int size;
		int altura;
		string fila;
	private:
		int _altura(ArbolCOL*ArbolCOL) {
			if (ArbolCOL == nullptr) {
				return -1;
			}
			return ArbolCOL->getAltura();
		}
		bool _insertar(ArbolCOL*& padre, ArbolCOL*& nodo) {
			if (padre == nullptr) {
				padre = nodo;
				if (raiz == nullptr) { raiz = nodo; }
			}
			else if (nodo->getFila() < padre->getFila()) {
				_insertar(padre->getIzquierda(), nodo);
			}
			else if (nodo->getFila() > padre->getFila()) {
				_insertar(padre->getDerecha(), nodo);
			}
			// Inicio de balanceo
			int hi = _altura(padre->getIzquierda());
			int hd = _altura(padre->getDerecha());
			int d = hd - hi;
			if (d > 1) {
				int hni = _altura(padre->getDerecha()->getIzquierda());
				int hnd = _altura(padre->getDerecha()->getDerecha());
				if (hni>hnd) {
					rotarDerecha(padre->getDerecha()->getIzquierda(), padre->getDerecha(), padre->getDerecha());
				}
				rotarIzquierda(padre, padre->getDerecha(), padre);
			}
			else if (d < -1) {
				int hni = _altura(padre->getIzquierda()->getIzquierda());
				int hnd = _altura(padre->getIzquierda()->getDerecha());
				if (hnd > hni) {
					rotarIzquierda(padre->getIzquierda(), padre->getIzquierda()->getDerecha(), padre->getIzquierda());
				}
				rotarDerecha(padre->getIzquierda(), padre, padre);
			}
			// Fin de balanceo
			hi = _altura(padre->getIzquierda());
			hd = _altura(padre->getDerecha());
			padre->setAltura(1 + ((hi > hd) ? hi : hd));
			return true;
		}
		void rotarDerecha(ArbolCOL*&x, ArbolCOL*y, ArbolCOL*&p) {
			p = x;
			y->setIzquierda(x->getDerecha());
			p->setDerecha(y);
		}
		void rotarIzquierda(ArbolCOL*x, ArbolCOL*&y, ArbolCOL*&p) {
			p = y;
			x->setDerecha(y->getIzquierda());
			p->setIzquierda(x);
		}
		ArbolCOL* _buscar(ArbolCOL*nodo, int fila) {
			if (nodo == nullptr) {
				return nullptr;
			}
			else if (nodo->getFila() == fila) {
				return nodo;
			}
			else if (fila < nodo->getFila()) {
				return _buscar(nodo->getIzquierda(), fila);
			}
			else {
				return _buscar(nodo->getDerecha(), fila);
			}
		}
	public:
		ArbolFIL() {
			raiz = nullptr;
			size = 0;
		}
		bool insertar(ArbolCOL *nodo) {
			++size;
			return _insertar(raiz, nodo);
		}
		void exportar(ofstream *archivo) {
			if (raiz != nullptr) {
				ArbolCOL *aux;
				for (int i = 1; i <= size; ++i) {
					aux = buscar(i);
					aux->exportar(archivo);
				}
			}
		}

		ArbolCOL*getRaiz() {
			return raiz;
		}
		ArbolCOL* buscar(int fila) {
			return _buscar(raiz, fila);
		}
		~ArbolFIL() {}
	};
}