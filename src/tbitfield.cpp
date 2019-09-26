// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	BitLen = len;
	MemLen = (BitLen + 31) >> 5;
	pMem = new TELEM[MemLen]; 
	if (pMem != NULL) {
		for (int i = 0; i < MemLen; i++) pMem[i] = 0;
	}
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	if (pMem != NULL) {
		for (int i = 0; i < MemLen; i++) pMem[i] = bf.pMem[i];
	}
}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return (n >> 5);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	TELEM mask = 1;
	mask << (n & 31);
	return mask;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n > -1) && (n < BitLen)) {
		pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] | GetMemMask(n);
	}
	else throw - 1;
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n > -1) && (n < BitLen)) {
		pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] & (~GetMemMask(n));
	}
	else throw - 1;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n > -1) && (n < BitLen)) {
		return (pMem[GetMemIndex(n)] & GetMemMask(n));
	}
	else throw - 1;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (this == &bf) {
		return *this;
	}
	else {
		delete[] pMem;
		BitLen = bf.BitLen;
		MemLen = bf.MemLen;
		pMem = new TELEM[MemLen];
		if (pMem != NULL) {
			for (int i = 0; i < MemLen; i++) pMem[i] = bf.pMem[i];
		}
		return *this;
	}
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	bool result = 1;
	if (BitLen != bf.BitLen) result = 0;
	else {
		for (int i = 0; i < MemLen; i++) {
			if (pMem[i] != bf.pMem[i]) {
				result = 0;
				break;
			}
		}
	}
	return result;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	return !(*this == bf);
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int tempLen = BitLen;
	if (bf.BitLen > BitLen) tempLen = bf.BitLen;
	TBitField result(tempLen);
	for (int i = 0; i < MemLen; i++) result.pMem[i] = pMem[i];
	for (int i = 0; i < result.MemLen; i++) result.pMem[i] = result.pMem[i] | bf.pMem[i];
	return result;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int tempLen = BitLen;
	if (bf.BitLen > BitLen) tempLen = bf.BitLen;
	TBitField result(tempLen);
	for (int i = 0; i < MemLen; i++) result.pMem[i] = pMem[i];
	for (int i = 0; i < result.MemLen; i++) result.pMem[i] = result.pMem[i] & bf.pMem[i];
	return result;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField result(BitLen);
	for (int i = 0; i < MemLen; i++) result.pMem[i] = ~pMem[i];
	return result;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	int a = 0;
	int i = 0;
	while ((a == 0) || (a == 1)) {
		istr >> a;
		if (a == 0) {
			bf.ClrBit(i);
			i++;
		}
		else if (a == 1) {
			bf.SetBit(i);
			i++;
		}
		else break;
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.BitLen; i++) {
		if (bf.GetBit == 0) ostr << "0";
		else ostr << "1";
	}
	return ostr;
}
