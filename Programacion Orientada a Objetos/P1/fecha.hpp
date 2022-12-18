#ifndef FECHA_HPP_
#define FECHA_HPP_

#include <iostream>

class Fecha {
    private:
        //Atributos
        int dia_, mes_, anno_;
        
        //Funciones auxiliares
        int diaMax() const noexcept;
        void valida();
        void actualiza();

    public:
        static const int AnnoMinimo = 1902, AnnoMaximo = 2037;

        class Invalida {
            private:
                const char *r_;
            public: 
                Invalida (const char *r) : r_(r){} //Constructor
                const char* por_que() const {return r_;} //Función excepción

        };

    //Constructores
    explicit Fecha (int d = 0, int m = 0, int a = 0); //a), b), c), d)
    Fecha (const char *cadf); //f)
    const char* cadena() const noexcept; //de Conversion

    //Metodos observadores
    inline const int dia() const noexcept {return dia_;}
    inline const int mes() const noexcept {return mes_;}
    inline const int anno() const noexcept {return anno_;}

    //Operadores matemáticos
    Fecha& operator += (int d);
    Fecha& operator -= (int d);
    Fecha& operator ++ (); //++f
    Fecha operator ++ (int); //f++ (el entero no sirve para nada, sólo distingue las funciones entre sí)
    Fecha operator + (int d) const;
    Fecha& operator -- (); //--f
    Fecha operator -- (int); //f--
    Fecha operator - (int d) const;
};
    //Operadores booleanos
    bool operator == (const Fecha &f1, const Fecha &f2) noexcept;
    bool operator != (const Fecha &f1, const Fecha &f2) noexcept;
    bool operator > (const Fecha &f1, const Fecha &f2) noexcept;
    bool operator < (const Fecha &f1, const Fecha &f2) noexcept;
    bool operator >= (const Fecha &f1, const Fecha &f2) noexcept;
    bool operator <= (const Fecha &f1, const Fecha &f2) noexcept;

    //Operadores de Entrada/Salida
    std::ostream& operator << (std::ostream &os, const Fecha &f) noexcept;
    std::istream& operator >> (std::istream &is, Fecha &f);

#endif
