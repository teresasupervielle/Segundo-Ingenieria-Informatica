#include "articulo.hpp"
#include "fecha.hpp"
#include "cadena.hpp"

#include <iomanip>
#include <stdlib.h>
#include <iostream>
#include <locale>

using namespace std;

    //Constructor
    Articulo::Articulo (const Cadena &r, const Cadena &t, const Fecha &f, double p, unsigned s) :
    referencia_(r), titulo_(t), f_publi_(f), precio_(p), stock_(s) {if(a.empty()) throw Autores_vacios();}

    //Operador de salida
    std::ostream& operator << (std::ostream &os, const Articulo &a) noexcept {
        setlocale(LC_ALL, "");

        os << "[" << a.referencia() << "]  \"" << a.titulo() << "\", " << a.f_publi().anno() << ". " << std::fixed << std::setprecision(2) << a.precio() << "€";

        return os;

        setlocale(LC_ALL, "");
	
		os << "[" << a.referencia() << "] \"" << a.titulo() << "\"";
		for (auto i : a.autores()) {
			if(i == *a.autores().begin()) os << ", de " << i->apellidos();
			else os <<", " << i->apellidos();
		}
		os << ". " << a.f_publi().anno() << ". " << std::fixed << td::setprecision(2) << a.precio() << " €\n\t";
		a.impresion_especifica(os);
	return os;
    }
