// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "encoder.h"
#include <iostream>
#include <vector>
#include <cmath>
using std::vector;
using std::size_t;

void chartobinary(vector<bool>* Vectorptr, char c[])
{
	for (int i = 0; i < strlen(c) - 1; i++)
	{
		char output[8];
		_itoa_s(c[i], output, 2);
		for (int j = 0; j <= 8; j++)
		{
			if (output[j] == '1')
			{
				Vectorptr->push_back(1);
			}
			else
			{
				Vectorptr->push_back(0);
			}
		}
	}
}
int binarytosine(vector<double>* Vectorptr, vector<bool>* invect)
{   
	
	for (size_t j = 0; j < invect->size(); j++)
	{
		if ((*invect)[j] == true)
		{
			double i = 0;
			while (i <= PER_BIT)
			{
				Vectorptr->push_back(AMPLITUDE * sin(2 * M_PI * (BAUD * 4) * i + 0));
				i += PER_SAMPLE;
			}
		}
		else if ((*invect)[j] == false)
		{
			double i = 0;
			while (i <= PER_BIT)
			{
				Vectorptr->push_back(AMPLITUDE * sin(2 * M_PI * (BAUD * 3) * i + 0));
				i += PER_SAMPLE;
			}
		}
		else
		{
			double i = 0;
			while (i <= PER_BIT)
			{
				Vectorptr->push_back(0);
				i += PER_SAMPLE;
			}
		}
	}
	return 0;
}


