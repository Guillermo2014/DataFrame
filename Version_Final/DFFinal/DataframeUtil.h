#pragma once
#include <windows.h>
#include <iostream>
#include <iterator>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <ctime>

#define separador ';' //Separador de valores en archivo
#define max_col 11 // Máximo de columnas por página
#define max_char 9 // Máximo de caracteres por celda
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
		void setColumna(int columna) {
			this->columna = columna;
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
		~Nodo() {
			dato.clear();
			izquierda = nullptr;
			derecha = nullptr;
		}
	};
}

//Columnas
namespace DF {
	class ArbolCOL {
	private:
		Nodo *raiz;
		int size;
		int altura;
		int contador;
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
			hi = _altura(nodo->getIzquierda());
			hd = _altura(nodo->getDerecha());
			nodo->setAltura(1 + ((hi > hd) ? hi : hd));
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
		//
		int getAltura(Nodo* x) {
			if (x == nullptr)
			{
				return -1;
			}
			else
			{
				return x->getAltura();
			}
		}
		int Max(int hi, int hd) {
			if (hi>hd)
			{
				return hi;
			}
			else
			{
				return hd;
			}
		}
		Nodo* rotarDer(Nodo* c) {
			Nodo*aux = c->getDerecha();
			c->setDerecha(aux->getIzquierda());
			aux->setIzquierda(c);
			c->setAltura(Max(getAltura(c->getIzquierda()), getAltura(c->getDerecha())) + 1);
			aux->setAltura(Max(getAltura(aux->getIzquierda()), getAltura(aux->getDerecha())) + 1);
			return aux;
		}
		Nodo* rotarIzq(Nodo* c) {
			Nodo*aux = c->getIzquierda();
			c->setIzquierda(aux->getDerecha());
			aux->setDerecha(c);
			c->setAltura(Max(getAltura(c->getIzquierda()), getAltura(c->getDerecha())) + 1);
			aux->setAltura(Max(getAltura(aux->getIzquierda()), getAltura(aux->getDerecha())) + 1);
			return aux;
		}
		Nodo* _EliminarNodo(int identificador, Nodo* nodo) {
			if (nodo == nullptr)
			{
				return nullptr;
			}
			else
			{
				if (nodo->getColumna() < identificador)
				{
					nodo->setDerecha(_EliminarNodo(identificador, nodo->getDerecha()));
				}
				else if (nodo->getColumna() > identificador)
				{
					nodo->setIzquierda(_EliminarNodo(identificador, nodo->getIzquierda()));
				}
				else if (nodo->getIzquierda() == nullptr)
				{
					nodo = nodo->getDerecha();
				}
				else if (nodo->getDerecha() == nullptr)
				{
					nodo = nodo->getIzquierda();
				}
				else if (getAltura(nodo->getIzquierda()) > getAltura(nodo->getDerecha()))
				{
					nodo = rotarDer(nodo);
					nodo->setIzquierda(_EliminarNodo(identificador, nodo->getIzquierda()));
				}
				else
				{
					nodo = rotarIzq(nodo);
					nodo->setDerecha(_EliminarNodo(identificador, nodo->getDerecha()));
				}

				if (nodo != nullptr)
				{
					nodo->setAltura(getAltura(nodo->getIzquierda()) + getAltura(nodo->getDerecha()) - 1);
				}
			}
			return nodo;
		}
		void _inOrder(Nodo* nodo) {
			if (nodo == nullptr) return;
			_inOrder(nodo->getIzquierda());
			++contador;
			nodo->setColumna(contador);
			_inOrder(nodo->getDerecha());
		}
		//
	public:
		ArbolCOL(int _fila) {
			izquierda = nullptr;
			derecha = nullptr;
			raiz = nullptr;
			size = 0;
			fila = std::to_string(_fila);
			fila.resize(7);
		}
		void arreglarColumnas() {
			contador = 0;
			_inOrder(raiz);
		}
		void verificar(int columnas) {
			while (size < columnas) {
				Nodo *aux;
				aux = new Nodo("null", size+1);
				insertar(aux);
			}
		}
		void eliminar(int columna) {
			--size;
			_EliminarNodo(columna, raiz);
			if (raiz->getColumna() == columna) {
				if (raiz->getIzquierda() != nullptr) {
					raiz = raiz->getIzquierda();
				}
				else if(raiz->getDerecha() != nullptr) {
					raiz = raiz->getDerecha();
				}
				else {
					raiz = nullptr;
				}
			}
		}
		bool insertar(Nodo *nodo) {
			++size;
			nodo->setColumna(size);
			return _insertar(raiz, nodo);
		}
		void imprimir(int pagina) {
			if (raiz != nullptr) {
				Nodo *aux;
				string dato;
				int i = ((pagina*max_col) - max_col) + 1;
				for (int k = 1; k <= max_col; ++k) {
					if (i > size) { 
						break; }
					aux = buscar(i);
					if (aux == nullptr) {
						dato = "Error 404";
						dato.resize(max_char);
						cout << dato << " | ";
						++i;
					}
					else {
						dato = aux->getDato();
						dato.resize(max_char);
						cout << dato << " | ";
						++i;
					}
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
		int getSize() {
			return size;
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
		void setFila(int _fila) {
			fila = std::to_string(_fila);
			fila.resize(7);
		}
		void setRaiz(Nodo *raiz) {
			this->raiz = raiz;
		}
		void setSize(int size) {
			this->size = size;
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
		int contador;
		int altura;
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
			else if (nodo->getFila() >= padre->getFila()) {
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
			hi = _altura(nodo->getIzquierda());
			hd = _altura(nodo->getDerecha());
			nodo->setAltura(1 + ((hi > hd) ? hi : hd));
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
		//
		//
		int getAltura(ArbolCOL* x) {
			if (x == nullptr)
			{
				return -1;
			}
			else
			{
				return x->getAltura();
			}
		}
		int Max(int hi, int hd) {
			if (hi>hd)
			{
				return hi;
			}
			else
			{
				return hd;
			}
		}
		ArbolCOL* rotarDer(ArbolCOL* c) {
			ArbolCOL*aux = c->getDerecha();
			c->setDerecha(aux->getIzquierda());
			aux->setIzquierda(c);
			c->setAltura(Max(getAltura(c->getIzquierda()), getAltura(c->getDerecha())) + 1);
			aux->setAltura(Max(getAltura(aux->getIzquierda()), getAltura(aux->getDerecha())) + 1);
			return aux;
		}
		ArbolCOL* rotarIzq(ArbolCOL* c) {
			ArbolCOL*aux = c->getIzquierda();
			c->setIzquierda(aux->getDerecha());
			aux->setDerecha(c);
			c->setAltura(Max(getAltura(c->getIzquierda()), getAltura(c->getDerecha())) + 1);
			aux->setAltura(Max(getAltura(aux->getIzquierda()), getAltura(aux->getDerecha())) + 1);
			return aux;
		}
		ArbolCOL* EliminarNodo(int identificador, ArbolCOL* nodo) {
			if (nodo == nullptr)
			{
				return nullptr;
			}
			else
			{
				if (nodo->getFila() < identificador)
				{
					nodo->setDerecha(EliminarNodo(identificador, nodo->getDerecha()));
				}
				else if (nodo->getFila() > identificador)
				{
					nodo->setIzquierda(EliminarNodo(identificador, nodo->getIzquierda()));
				}
				else if (nodo->getIzquierda() == nullptr)
				{
					nodo = nodo->getDerecha();
				}
				else if (nodo->getDerecha() == nullptr)
				{
					nodo = nodo->getIzquierda();
				}
				else if (getAltura(nodo->getIzquierda()) > getAltura(nodo->getDerecha()))
				{
					nodo = rotarDer(nodo);
					nodo->setIzquierda(EliminarNodo(identificador, nodo->getIzquierda()));
				}
				else
				{
					nodo = rotarIzq(nodo);
					nodo->setDerecha(EliminarNodo(identificador, nodo->getDerecha()));
				}

				if (nodo != nullptr)
				{
					nodo->setAltura(getAltura(nodo->getIzquierda()) + getAltura(nodo->getDerecha()) - 1);
				}
			}
			return nodo;
		}
		void _inOrder(ArbolCOL* nodo) {
			if (nodo == nullptr) return;
			_inOrder(nodo->getIzquierda());
			++contador;
			nodo->setFila(contador);
			_inOrder(nodo->getDerecha());
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
		void arreglarFilas() {
			contador = 0;
			_inOrder(raiz);
		}
		void eliminar(int fila) {
			--size;
			EliminarNodo(fila, raiz);
			if (raiz->getFila() == fila) {
				if (raiz->getIzquierda() != nullptr) {
					raiz = raiz->getIzquierda();
				}
				else if (raiz->getDerecha() != nullptr) {
					raiz = raiz->getDerecha();
				}
				else {
					raiz = nullptr;
				}
			}
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
		int getSize() {
			return size;
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