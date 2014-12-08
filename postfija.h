#include <iostream>
#include <string>
#include <cstdlib>
#include "Pila.h"
#include "cola.h"
using namespace std;

class Postfija {
private:
	Pila<int> op;
	string cuenta;

public:
	Postfija () {
	}

	Postfija (string s) {
		cuenta = s;
	}

	int Operacion () {
		unsigned n, i=0, j=0;
		char c;
		c = cuenta[i];
		i++;

		//teniendo en cuenta que en ascii los caracteres de
		//los operandos estan antes que los de los numeros
		while (i<=cuenta.size()) {
			if (c > '/') {
				char numero[5] = {'\0','\0','\0','\0','\0'};
				while (c != ' ' && c > '/') { // para numeros de varias cifras
					numero[j] = c;
					j++;
					c = cuenta[i];
					i++;
				}
				n = atoi(numero);
				op.Poner(n);
				j=0;
				c = cuenta[i];
				i++;
			}

			else if (c <= '/') {
				if (c!=' ') {
					// cogemos los dos ultimos valores:
					int valor1 = op.Tope();
					op.Quitar();
					int valor2 = op.Tope();
					op.Quitar();

					// dependiendo del valor de c hacemos una operacion u otra
					switch(c) {
						case('+'):
							op.Poner(valor1 + valor2);
							break;

						case('-'):
							op.Poner(valor2 - valor1);
							break;

						case('*'):
							op.Poner(valor1 * valor2);
							break;

						default:
							op.Poner(valor2 / valor1);
							break;
					}
				}

				c = cuenta[i];
				i++;
			}
		}
		return op.Tope();
	}
};

string infija2postfija (string s) {
	Cola<char> c;		// Cola en la que vamos a ir insertando la operacion
	Pila<char> p;		// Pila en la que vamos a ir guardando los operadores
	char ch;

	for (unsigned i=0;i<s.size();i++) {
		ch = s[i];
		if (ch > '/' || (ch >= 'a' && ch <= 'z') || (ch>='A' && ch <= 'Z'))
			c.poner(ch);

		else if (ch <= '/') {
			if (!p.Vacia() && ch != ' ') { // ya tenemos operadores en la pila
				//  tenemos que ver la precedencia que tiene respecto a los demas
				switch(ch) {
					case('*'):
						if (p.Tope()=='+' || p.Tope()=='-' || p.Tope()=='(')
							p.Poner(ch);

						else if (p.Tope()=='/' || p.Tope()=='*') {
							c.poner(p.Tope());
							p.Quitar();
							p.Poner(ch);
						}

						break;

					case('/'):
						if (p.Tope()=='+' || p.Tope()=='-' || p.Tope()=='(')
							p.Poner(ch);

						else if (p.Tope()=='/' || p.Tope()=='*') {
							c.poner(p.Tope());
							p.Quitar();
							p.Poner(ch);
						}

						break;

					case('+'):
						p.Poner(ch);
						break;

					case(')'):
						while (p.Tope() != '(') {
							c.poner(p.Tope());
							p.Quitar();
						}
						p.Quitar();
						break;

					default: // resta y parentesis abierto
						p.Poner(ch);
						break;
				}
			}

			else if (ch != ' ') {
				p.Poner(ch);
			}
		}
	}

	// ahora metemos en la cola todo lo que teniamos en la pila
	while (!p.Vacia()) {
		c.poner(p.Tope());
		p.Quitar();
	}

	// y por ultimo, como tenemos que devolverlo con un string, metemos
	// en un string el contenido de la cola separado por espacios en blanco
	string devuelto;
	while (!c.vacia()) {
		int i=0;
		ch = c.frente(); 
		devuelto.push_back(ch); 
		i++;

		// cada caracter se separa con un espacio
		devuelto.push_back(' ');

		// y eliminamos dicho elemento de la cola
		c.quitar();
	}

	return devuelto;
}
