#ifndef _QuadriaticHashing_h_
#define _QuadriaticHashing_h_
#include "AddressFunction.h"
class QuadriaticHashing : public AddressFunction
{
	int c;
public:
	QuadriaticHashing() = default;
	QuadriaticHashing(int x): c(x){}
	void addC(double x) { c = x; }
	int getAddress(int indeks, int base, int i, int size) override
	{
		int x = (base + c * i * i) % size;
		return (base + c * i * i) % size;
	}


};
#endif
