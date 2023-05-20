#ifndef _AddressFunction_h_
#define _AddressFunction_h_
#include <iostream>
#include<cmath>
using namespace std;
class AddressFunction
{
public:
	virtual int getAddress(int indeks, int base, int i, int size) = 0;

};

#endif
