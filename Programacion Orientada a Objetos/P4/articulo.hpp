#ifndef ARTICULO_HPP_
#define ARTICULO_HPP_

#include "fecha.hpp"
#include "cadena.hpp"
#include <set>
#include <ostream>

class Autor {
    private:
        //Atributos
        const Cadena nom, apel, dir;
    
    public:
        //Constructor
        Autor (Cadena n, Cadena a, Cadena d) : nom(n), apel(a), dir(d) {}

        //Metodos observadores
        const Cadena& nombre() const noexcept {return nom;}
        const Cadena& apellidos() const noexcept {return apel;}
        const Cadena& direccion() const noexcept {return dir;}
};

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

        //Destructor
        virtual ~Articulo() = default;

        //Metodos observadores
        Cadena referencia() const {return referencia_;}
        Cadena titulo() const {return titulo_;}
        Fecha f_publi() const {return f_publi_;}
        double precio() const {return precio_;}
        unsigned int stock() const {return stock_;}
        double& precio() {return precio_;}
        unsigned& stock() {return stock_;}

        //Definicion set
        typedef std::set<Autor*> Autores;

        //Operador de salida especifico
        virtual void impresion_especifica (std::ostream &os) const = 0;
        class Autores_vacios{};
};

//Operador de Salida
std::ostream& operator << (std::ostream &os, const Articulo &a) noexcept;


//Clases especificas
class LibroDigital : public Articulo {
    private:
        //Atributos
        const Fecha f_exp;
    
    public:
        //Constructor
        LibroDigital (Autores a, Cadena r, Cadena t, Fecha f, double p, Fecha fe) : Articulo(a,r,t,f,p), f_exp(fe){}

        //Destructor
        ~LibroDigital() = default;

        //Metodo observador
        Fecha f_expir() const {return f_exp;}

        //Operador de salida especifico
        virtual void impresion_especifica (std::ostream &os) const {os << "A la venta hasta el " << f_exp<< ".";}
};

class ArticuloAlmacenable : public Articulo {
    private:
        //Atributos
        int stck;
    
    public:
        //Constructor
        ArticuloAlmacenable (Autores a, Cadena r, Cadena t, Fecha f, double p, int s = 0) : Articulo(a,r,t,f,p), stck(s){}


        //Destructor
        virtual ~ArticuloAlmacenable() = default;

        //Metodo observador
        int stock() const {return stck;}
        int& stock() {return stck;}
};

class Libro : public ArticuloAlmacenable {
    private:
        //Atributos
        const int num_pag;
    
    public:
        //Constructor
        Libro (Autores a, Cadena r, Cadena t, Fecha f, double p, int np, int s = 0) : ArticuloAlmacenable(a,r,t,f,p,s), num_pag(np) {}

        //Destructor
        ~Libro() = default;

        //Metodo observador
        int n_pag() const {return num_pag;}
        
        //Operador de salida especifico
        void impresion_especifica (std::ostream &os) const {os << num_pag << " págs., " << stck << " unidades.";}
};

class Cederron : public ArticuloAlmacenable {
    private:
        //Atributos
        const int tam_;
    
    public:
        //Constructor
        Cederron (Autores a, Cadena r, Cadena t, Fecha f, double p, int tam, int s = 0) : ArticuloAlmacenable(a,r,t,f,p,s), tam_(tam){}

        //Destructor
        ~Cederron() = default;

        //Metodo observador
        int tam() const {return tam_;}
        
        //Operador de salida especifico
        void impresion_especifica (std::ostream &os) const {os << tam_ << " MB, " << stck << " unidades.";}
};

#endif

