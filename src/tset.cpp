// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : MaxPower(mp), BitField(mp)
{
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField), MaxPower(s.MaxPower)
{
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf), MaxPower(bf.GetLength())
{
}

TSet::operator TBitField()
{
	TBitField tmp((*this).BitField);
	return tmp;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
	return (*this).BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	(*this).BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	(*this).BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
    MaxPower = s.MaxPower;
    BitField = s.BitField;
    return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
    return BitField == s.BitField;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
    return BitField != s.BitField;
}

TSet TSet::operator+(const TSet &s) // объединение
{
    TSet tmp = BitField | s.BitField;
    return tmp;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    TSet tmp = BitField;
    tmp.InsElem(Elem);
    return tmp;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    TSet tmp = BitField;
    tmp.DelElem(Elem);
    return tmp;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
    TSet tmp = BitField & s.BitField;
    return tmp;
}

TSet TSet::operator~(void) // дополнение
{
    TSet tmp = ~BitField;
    return tmp;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
    //вводятся номера элементов, принадлежащих множеству
    //формат ввода {i1,i2,... in} (n=MaxPower)
    //игнорирование всех знаков перед '{' и ','
    char ch;
    int tmp;
    do
    {
        istr >> ch;
    } while (ch != '{');
    do
    {
        istr >> tmp;
        s.InsElem(tmp);
        do{
            istr >> ch;
        } while (ch != ',' && ch != '}');
    } while (ch != '}');
    return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
    //выводятся номера элементов, принадлежащих множеству
    int MAX = s.MaxPower;
    int i = 0;
    ostr << '{' << ' ';
    do
    {
        if (s.IsMember(i)){
            ostr << i;
            i++;
            break;
        }
        i++;
    } while (i < MAX);
    for (i; i < MAX; i++) {
        if (s.IsMember(i))
            ostr << ', ' << i;
    }
    ostr << ' ' << '}';
    return ostr;
}
