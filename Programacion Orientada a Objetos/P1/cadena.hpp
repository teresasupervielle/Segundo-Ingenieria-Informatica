#ifndef CADENA_HPP_
#define CADENA_HPP_

#include <iostream>
#include <iterator>
#include <cstring>

class Cadena {
    private:
        //Atributos
        unsigned int tam;
        char *s;

        //Funciones auxiliares
        void copiar (const Cadena &c) noexcept;
        void copiar (const char *c) noexcept;

    public:
        //Constructores
        explicit Cadena (unsigned int t = 0, char c = ' '); //Constructor explicito
        Cadena (const Cadena &c);
        Cadena (const char *s_);
        Cadena (Cadena &&c); //Constructor de copia
        ~Cadena(); //Destructor

        //Metodos observadores
        unsigned int length () noexcept {return tam;}
        const unsigned int length () const noexcept {return tam;}

        unsigned int length (const char *c) noexcept;
        const unsigned int length (const char *c) const noexcept;

        const char *c_str() const noexcept {return s;}

        //Operadores concatenacion
        Cadena operator+= (const Cadena &c) noexcept;
        Cadena& operator= (const Cadena &c) noexcept;
        Cadena& operator= (const char *c) noexcept;
        Cadena& operator= (Cadena &&c) noexcept;

        //Operadores y funcion busqueda de caracter
        char& operator[](unsigned int it) {return this->s[it];}
        const char& operator[] (unsigned int it) const {return this->s[it];}
        char& at (unsigned int it);
        const char& at (unsigned int it) const;
        Cadena substr (unsigned int indice, unsigned int tam_) const;
        
        //Definición tipos iterator
        typedef char *iterator;
        typedef const char *const_iterator;
        typedef std::reverse_iterator <iterator> reverse_iterator;
        typedef std::reverse_iterator <const_iterator> const_reverse_iterator;

        //Funciones para iterator
        iterator begin() {return s;}
        iterator end() {return s + tam;}
        const_iterator begin() const {return const_iterator(s);}
        const_iterator end() const {return const_iterator(s + tam);}
        
        const_iterator cbegin() const {return const_iterator(s);}
        const_iterator cend() const {return const_iterator(s + tam);}

        reverse_iterator rbegin() {return reverse_iterator(end());}
        reverse_iterator rend() {return reverse_iterator(begin());}
        const_reverse_iterator rbegin() const {return const_reverse_iterator(end());}
        const_reverse_iterator rend() const {return const_reverse_iterator(begin());}

        const_reverse_iterator crbegin() const {return const_reverse_iterator(end());}
        const_reverse_iterator crend() const {return const_reverse_iterator(begin());}
};

    //Operador de concatenacion entre dos cadenas 
    Cadena operator+ (const Cadena &c1, const Cadena &c2) noexcept;

    //Operadores booleanos
    bool operator== (const Cadena &c1, const Cadena &c2) noexcept;
    bool operator!= (const Cadena &c1, const Cadena &c2) noexcept;
    bool operator< (const Cadena &c1, const Cadena &c2) noexcept;
    bool operator> (const Cadena &c1, const Cadena &c2) noexcept;
    bool operator<= (const Cadena &c1, const Cadena &c2) noexcept;
    bool operator>= (const Cadena &c1, const Cadena &c2) noexcept;

    //Operadores de Entrada/Salida
    std::ostream& operator << (std::ostream &os, const Cadena &c) noexcept;
    std::istream& operator >> (std::istream &is, Cadena &c) noexcept;

#endif
