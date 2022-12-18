#include "fecha.hpp"
#include <ctime>
#include <iostream>
#include <locale>
#include <cstdio>
#include <new>

using namespace std;

    //Funciones auxiliares
    int Fecha::diaMax() const noexcept {
        if (mes_ == 1 || mes_ == 3 || mes_ == 5 || mes_ == 7 || mes_ == 8 || mes_ == 10 || mes_ == 12) return 31;
        else {
            if (mes_ == 4 || mes_ == 6 || mes_ == 9 || mes_ == 11) return 30;
            else {
                if (anno_ % 4 == 0 && (anno_ % 400 == 0 || anno_ % 100 != 0)) return 29; //Calculo año bisiesto
                else return 28;
            }
        }
    }

    void Fecha::valida() {
        if (anno_ < Fecha::AnnoMinimo || anno_ > Fecha::AnnoMaximo) throw (Invalida("ERROR. Anno fuera del rango permitido"));
        if (mes_ < 0 || mes_ > 12) throw (Invalida("ERROR. Mes inexistente, fuera del rango"));
        if (dia_ < 0 || dia_ > diaMax()) throw (Invalida("ERROR. Dia inexistente, fuera del rango"));
    }

    void Fecha::actualiza(){
        tm f = {0};
        f.tm_mday = dia_;
        f.tm_mon = mes_ - 1;
        f.tm_year = anno_ - 1900;

        mktime(&f);

        dia_ = f.tm_mday;
        mes_ = f.tm_mon + 1;
        anno_ = f.tm_year + 1900;
        
    	if (anno_ < Fecha::AnnoMinimo) throw (Invalida("ERROR: Anno menor al anno minimo"));
    	if (anno_ > Fecha::AnnoMaximo) throw (Invalida("ERROR: Anno mayor a anno maximo"));
    }
    
    //Constructores
    Fecha::Fecha (int d, int m, int a) : dia_(d), mes_(m), anno_(a) {
        std::time_t tiempo_calendario = std::time(nullptr);
        std::tm* tiempo_descompuesto = std::localtime(&tiempo_calendario);
        if (dia_ == 0) dia_ = tiempo_descompuesto->tm_mday;
        if (mes_ == 0) mes_ = tiempo_descompuesto->tm_mon + 1;
        if (anno_ == 0) anno_ = tiempo_descompuesto->tm_year + 1900;

        Fecha::valida();
    }

    Fecha::Fecha (const char *cadf){
    	std::time_t tiempo_calendario = std::time(nullptr);
        std::tm* tiempo_descompuesto = std::localtime(&tiempo_calendario);
        int i = sscanf (cadf, "%d/%d/%d", &dia_, &mes_, &anno_);

        if (i != 3) throw (Invalida("ERROR. Formato de fecha invalido"));
        if (dia_ == 0) dia_ = tiempo_descompuesto->tm_mday;
        if (mes_ == 0) mes_ = tiempo_descompuesto->tm_mon + 1;
        if (anno_ == 0) anno_ = tiempo_descompuesto->tm_year + 1900;
        
        Fecha::valida();
    }

    const char* Fecha::cadena() const noexcept{
        setlocale(LC_ALL, "");
        static char buffer[sizeof("miércoles 12 de septiembre de 2001")]{'\0'};
        
        tm f = {};
        f.tm_mday = dia_;
        f.tm_mon = mes_ - 1;
        f.tm_year = anno_ - 1900;

        mktime(&f);
        strftime (buffer, sizeof(buffer), "%A %d de %B de %Y", &f);

        return buffer;

    }

    //Operadores matemáticos
    Fecha& Fecha::operator += (int d){
        dia_ += d;
        Fecha::actualiza();
        return *this;
    }

    Fecha& Fecha::operator -= (int d){
        *this += -d; //Hacemos uso del operador ya creado
        return *this;
    }
    
    Fecha& Fecha::operator ++ (){
        *this += 1; //Hacemos uso del operador ya creado
        return *this;
    }

    Fecha Fecha::operator ++ (int){
        Fecha f = *this;
        *this += 1; //Hacemos uso del operador ya creado
        return f;
    }

    Fecha Fecha::operator + (int d) const {
        Fecha f = *this;
        f += d; //Hacemos uso del operador ya creado
        return f;
    }

    Fecha& Fecha::operator -- (){
        *this += -1; //Hacemos uso del operador ya creado
        return *this;
    }

    Fecha Fecha::operator -- (int){
        Fecha f = *this;
        *this += -1; //Hacemos uso del operador ya creado
        return f;
    }

    Fecha Fecha::operator - (int d) const{
        Fecha f = *this;
        f += -d; //Hacemos uso del operador ya creado
        return f;
    }


    //Operadores booleanos
    bool operator == (const Fecha &f1, const Fecha &f2) noexcept {
            return ((f1.dia() == f2.dia()) && (f1.mes() == f2.mes()) && (f1.anno() == f2.anno()));
        }

    bool operator != (const Fecha &f1, const Fecha &f2) noexcept { 
        return !(f1 == f2);
    }

    bool operator > (const Fecha &f1, const Fecha &f2) noexcept{
        if (f1.anno() > f2.anno()) return true;
        else {
            if (f1.anno() == f2.anno()){
                if (f1.mes() > f2.mes()) return true;
                else {
                    if (f1.mes() == f2.mes()){
                        if (f1.dia() > f2.dia()) return true;
                    }
                }
            }
        }
        return false;
    }

    bool operator < (const Fecha &f1, const Fecha &f2) noexcept {
        return (f2 > f1);
    }

    bool operator >= (const Fecha &f1, const Fecha &f2) noexcept {
        return !(f1 < f2);
    }

    bool operator <= (const Fecha &f1, const Fecha &f2) noexcept {
        return !(f1 > f2);
    }

    //Operadores de Entrada/Salida
    std::ostream& operator << (std::ostream &os, const Fecha &f) noexcept {
        setlocale(LC_ALL, "");
        os << f.cadena();
        return os;
    }

    std::istream& operator >> (std::istream &is, Fecha &f) {
        char *aux = new char[11];
        is.width(11);

        is >> aux;

        try{
            f = aux;
        } catch (Fecha::Invalida res) {
        	is.setstate(ios::failbit);
        	delete[] aux;
        	throw Fecha::Invalida("ERROR. Formato incorrecto");
        } 
        return is;
    }
