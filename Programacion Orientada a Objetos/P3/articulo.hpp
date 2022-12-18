#ifndef ARTICULO_HPP_
#define ARTICULO_HPP_

#include "fecha.hpp"
#include "cadena.hpp"

class Articulo {
    private:
        //Atributos
        Cadena referencia_, titulo_;
        Fecha f_publi_;
        double precio_;
        unsigned stock_;
    
    public:
        //Constructor
        Articulo (const Cadena &r, const Cadena &t, const Fecha &f, double p, unsigned s);

        //Metodos observadores
        Cadena referencia() const {return referencia_;}
        Cadena titulo() const {return titulo_;}
        Fecha f_publi() const {return f_publi_;}
        double precio() const {return precio_;}
        unsigned int stock() const {return stock_;}
        double& precio() {return precio_;}
        unsigned& stock() {return stock_;}
};

//Operador de Salida
std::ostream& operator << (std::ostream &os, const Articulo &a) noexcept;

#endif

