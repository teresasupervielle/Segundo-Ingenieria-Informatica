#ifndef USUARIO_HPP_
#define USUARIO_HPP_

#include "cadena.hpp"
#include "articulo.hpp"
#include "tarjeta.hpp"

#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <unistd.h>

class Numero;
class Tarjeta;

class Clave {
    private:
        //Atributo
        Cadena pass_;

    public:
        enum Razon {CORTA, ERROR_CRYPT};

        //Constructor
        Clave(const char *p);

        //Destructor
        ~Clave(){};

        //Funciones
        bool verifica (const char *c) const;
        Cadena clave () const {return pass_;}   

        class Incorrecta {
            private:
                //Atributo
                Clave::Razon r_;
            
            public:
                //Constructor
                Incorrecta (const Clave::Razon r) : r_(r) {}

                //Funcion observadora
                Clave::Razon razon() const {return r_;}
        };
};

class Usuario {    
    public:
        //Constructor
        Usuario (const Cadena &id, const Cadena &n, const Cadena &a, const Cadena &dir, const Clave &p);
        Usuario (const Usuario &u) = delete;
        Usuario& operator = (const Usuario &) = delete;

        //Destructor
        ~Usuario();
        
        //Defines
        typedef std::map <Numero, Tarjeta*> Tarjetas;
		typedef std::unordered_map <Articulo*, unsigned> Articulos;

        class Id_duplicado {
            private:
                //Atributos
                Cadena id_;
            
            public:
                //Constructor 
                Id_duplicado (const Cadena &c) : id_(c){}

                //Funcion observador
                const Cadena& idd () const {return id_;}
        };

        //Funciones observadoras
        const Cadena& id() const noexcept {return ID;}
        const Cadena& nombre() const noexcept {return nombre_;}
        const Cadena& apellidos() const noexcept {return apellido_;}
        const Cadena& direccion() const noexcept {return direccion_;}
        const Tarjetas& tarjetas() const noexcept {return tarjetas_;}
        const size_t n_articulos() const noexcept {return n_articulos_;}
        const Articulos& compra() const noexcept {return articulos_;}

        //Funciones auxiliares
        void es_titular_de (const Tarjeta &t);
        void no_es_titular_de (Tarjeta &t);
        void compra (const Articulo &a, size_t cant = 1);

        friend std::ostream& operator << (std::ostream &os, const Usuario &u) noexcept;

	private:
        //Atributos
        Cadena ID, nombre_, apellido_, direccion_;
        Clave pass;
        Tarjetas tarjetas_;
        Articulos articulos_;
        size_t n_articulos_;
        static std::unordered_set<Cadena> registrados;
};

std::ostream& operator << (std::ostream &os, const Usuario &u) noexcept;
void mostrar_carro (std::ostream &os, const Usuario &u) noexcept;

#endif
