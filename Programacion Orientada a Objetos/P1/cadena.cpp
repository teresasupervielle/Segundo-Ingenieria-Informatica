#include "cadena.hpp"
#include <stdexcept>
#include <algorithm>

using namespace std;

    //Funciones auxiliares
    void Cadena::copiar (const Cadena &c) noexcept {
        tam = c.tam;
        delete[] s;
        s = new char [tam + 1];
        strcpy (s, c.s);
    }

    void Cadena::copiar (const char *c) noexcept {
        tam = strlen(c);
        delete[] s;
        s = new char [tam + 1];
        strcpy (s, c);
    }

    //Constructores
    Cadena::Cadena (unsigned int t, char c) : tam(t), s(new char[t + 1]) {
        for (unsigned int i = 0; i < tam; i++) s[i] = c;
        s[tam] = '\0';
    }

    Cadena::Cadena (const Cadena &c) : tam(c.tam), s(new char[c.tam + 1]) {copiar(c);}

    Cadena::Cadena (const char *s_) : tam(length(s_)), s(new char[length(s_) + 1]) {copiar(s_);}
    
    Cadena::Cadena (Cadena &&c) : tam (c.tam), s(c.s) {
        c.tam = 0;
        c.s = nullptr;
    }
    
    //Destructor
    Cadena::~Cadena(){delete[] s;}

    //Metodos observadores
    unsigned int Cadena::length (const char *c) noexcept {
        unsigned int i = 0;
        while (c[i]) i++;

        return i;
    }

    const unsigned int Cadena::length (const char *c) const noexcept {
        unsigned int i = 0;
        while (c[i]) i++;

        return i;
    }

    //Operadores concatenacion
    Cadena Cadena::operator+= (const Cadena &c) noexcept {
        char *aux = new char[tam + 1];
        strcpy(aux, s);
        tam += c.tam;

        delete[] s;
        s = new char [tam + 1];
        unsigned int i = 0;
        
        while (aux[i]){
        	s[i] = aux[i];
        	i++;
    	}

        delete[] aux;
        unsigned int j = i;
        i = 0;

        while(c[i]){
        	s[j] = c.s[i];
        	i++;
        	j++;
    	}

        s[j] = '\0';
        return *this;
    }

    Cadena& Cadena::operator= (const Cadena &c) noexcept {
        if(*this != c) copiar(c);
        return *this;
    }

    Cadena& Cadena::operator= (const char *c) noexcept {
        Cadena cc(c);
        if(*this != cc) copiar(c);
        return *this;
    }

    Cadena& Cadena::operator= (Cadena &&c) noexcept{
        tam = c.tam;
        delete[] s;
        s = c.s;
        c.tam = 0;
        c.s = nullptr;
        return *this;
    }

    //Operadores y funcion busqueda de caracter
    char& Cadena::at (unsigned int it) {
        if (it < tam) return s[it];
        else throw out_of_range("Indice fuera de rango");
    }

    const char& Cadena::at (unsigned int it) const {
        if (it < tam) return s[it];
        else throw out_of_range("Indice fuera de rango");
    }

    Cadena Cadena::substr (unsigned int indice, unsigned int tam_) const {
        if (indice >= tam || tam_ > tam - indice) throw out_of_range("Indice fuera de rango");

        char *aux = new char[tam_ + 1];
        int i = 0;
        unsigned int fin = indice + tam_;

        while (indice < fin) {
            aux[i] = s[indice];
            indice++;
            i++;
        }

        aux[i] = '\0';
        Cadena cc(aux);
        delete[] aux;

        return cc;
    }

    //Operador de concatenacion entre dos cadenas 
    Cadena operator+ (const Cadena &c1, const Cadena &c2) noexcept {
        Cadena aux(c1);
        return aux += c2;
    }

    //Operadores booleanos
    bool operator== (const Cadena &c1, const Cadena &c2) noexcept {
        if (c1.length() != c2.length()) return false;
        
        for (int i = 0; i < min(c1.length(), c2.length()); i++){
            if (c1.at(i) != c2.at(i)) return false;
        }
        return true;
    }

    bool operator!= (const Cadena &c1, const Cadena &c2) noexcept {
        return !(c1 == c2);
    }

    bool operator< (const Cadena &c1, const Cadena &c2) noexcept {
        if(strcmp(c1.c_str(), c2.c_str()) < 0) return true;
        else return false; 
    }

    bool operator> (const Cadena &c1, const Cadena &c2) noexcept {
        return (c2 < c1);
    }
    
    bool operator<= (const Cadena &c1, const Cadena &c2) noexcept {
        return !(c1 > c2);
    }

    bool operator>= (const Cadena &c1, const Cadena &c2) noexcept {
        return !(c1 < c2);
    }

    //Operadores de Entrada/Salida
    std::ostream& operator << (std::ostream &os, const Cadena &c) noexcept {
        os << c.c_str();
        return os;
    }

    std::istream& operator >> (std::istream &is, Cadena &c) noexcept {
        char s[33] ="";
        is.width(33);
        is >> s;
        c = s;
        return is;
    }
