#ifndef TARJETA_HPP_
#define TARJETA_HPP_

#include "cadena.hpp"
#include "articulo.hpp"
#include "usuario.hpp"

class Usuario;
class Clave;

class Numero {   
    public:
        enum Razon {LONGITUD, DIGITOS, NO_VALIDO}; //Representacion numero no valido

        //Constructor
        Numero (const Cadena &n);

        //Destructor
        ~Numero(){};

        //Operador de conversion
        operator const char* () const {return numero_.c_str();}

        //Metodo observador
        const Cadena& num() const {return numero_;}

        class Incorrecto {
            private:
                //Atributos
                Numero::Razon r_;

            public:
                //Constructor
                Incorrecto (const Numero::Razon r):r_(r){}

                //Metodo observador
                Numero::Razon razon() const {return r_;}
        };
        
	private:
        //Atributos
        Cadena numero_;
};

class Tarjeta {
    public:
        enum Tipo {Otro, VISA, Mastercard, Maestro, JCB, AmericanExpress};

        //Constructor
        Tarjeta (const Numero &n, Usuario &u, const Fecha &c);
        Tarjeta (const Tarjeta &t) = delete;
        Tarjeta& operator = (const Tarjeta &t) = delete;

        //Destructor
        ~Tarjeta();

        //Metodos observadores
        const Numero& numero() const {return numero_;}
        Usuario* titular() const {return usuario_;}
        const Fecha& caducidad() const {return caducidad_;}
        const bool activa() const {return estado_;}
        const Tarjeta::Tipo& tipo() const {return tipo_;}
        bool& activa(bool a = true) {estado_ = a; return estado_;}
        Tipo esTipo();

        class Caducada {
            private:
                //Atributos
                Fecha f_caducada_;

            public:
                //Constructor
                Caducada (const Fecha &fc) : f_caducada_(fc){}

                //Metodo observador
                const Fecha& cuando() const {return f_caducada_;}
        };

        class Num_duplicado {
            private:
                //Atributos
                Numero num_;

            public:
                //Constructor
                Num_duplicado (const Numero &n) : num_(n){}

                //Metodo observador
                const Numero& que() const {return num_;}
        };

        class Desactivada {
            public:
                //Constructor
                Desactivada(){}           
        };

        friend class Usuario;
        private:
            void anula_titular() {estado_ = false; const_cast <Usuario*&>(usuario_) = nullptr;}
        friend std::ostream& operator << (std::ostream &os, const Tarjeta &t);
        
    private:
        //Atributos
        Numero numero_;
        Usuario* const usuario_; 
        Fecha caducidad_;
        bool estado_;
        Tipo tipo_;


};

//Operadores de salida
std::ostream& operator << (std::ostream &os, const Tarjeta &t);
std::ostream& operator << (std::ostream &os, const Tarjeta::Tipo &tipo);

//Operadores logicos
bool operator < (const Numero &x, const Numero &y);
bool operator < (const Tarjeta &x, const Tarjeta &y);

#endif
