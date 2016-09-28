// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
    if (len < 1)
        throw(len);
    BitLen = len;
    MemLen = (BitLen + 31) >> 5;
    pMem = new TELEM[MemLen];
    if (pMem != NULL)
        for (int i = 0; i < MemLen; i++) 
            pMem[i] = 0;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    if (pMem != NULL)
        for (int i = 0; i < MemLen ; i++)
        {
            pMem[i] = bf.pMem[i];
        }
}

TBitField::~TBitField()
{
    delete [] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    return n >> 5;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    return 1 << (n & 31);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
    return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if (n < 0 || n >= BitLen)
        throw(n);
    pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if (n < 0 || n >= BitLen)
        throw(n);
    pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if (n < 0 || n >= BitLen)
        throw(n);
    if ((pMem[GetMemIndex(n)] & GetMemMask(n)) != 0)
        return 1;
    else
        return 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    if (*this == &bf)
        throw(this);
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
    {
        pMem[i] = bf.pMem[i];
    }
    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    if (BitLen != bf.BitLen)
        return 0;
    else
    {
        for (int i = 0; i < MemLen; i++)
            if (pMem[i] != bf.pMem[i])
                return 0;
    }
    return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    if ((*this == bf) == 0)
        return 1;
    else
        return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    int tmp_len;
    if (BitLen < bf.BitLen)
        tmp_len = bf.BitLen;
    else
        tmp_len = BitLen;
    TBitField tmp(tmp_len);
    for (int i = 0; i < MemLen; i++) 
        tmp.pMem[i] = pMem[i];
    for (int i = 0; i < bf.MemLen; i++)
        tmp.pMem[i] |= bf.pMem[i];
    return tmp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    int tmp_len;
    if (BitLen < bf.BitLen)
        tmp_len = bf.BitLen;
    else
        tmp_len = BitLen;
    TBitField tmp(tmp_len);
    for (int i = 0; i < MemLen; i++) 
        tmp.pMem[i] = pMem[i];
    for (int i = 0; i < bf.MemLen; i++) 
        tmp.pMem[i] &= bf.pMem[i];
    return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
    for (int i = 0; i < BitLen; i++)
        if (GetBit(i) == 0)
            SetBit(i);
        else
            ClrBit(i);
    return *this;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    for (int i = 0; i < bf.BitLen; i++)
        ostr << bf.GetBit(i);
    return ostr;
}
