#pragma once

#include "pch.h"
using std::string;
#ifdef ENCODER_EXPORTS
#define EXPORT __declspec(dllexport)
#else
#define EXPORT __declspec(dllimport)
#endif
#ifndef M_PI
#define M_PI 3.1415926535
#endif // !M_PI

using std::vector;
class EXPORT Encoder
{
	double amplitude, samplerate, baud;
	int attntype, attntime, delay1, delay2, delay3, delay4;
	vector<int> bin;
	vector<float> wave0, wave1, effect, delay, attnAM, attnNWS, signalPCM, Preamble;
	vector<int> DebugSignalInput;
	string c;
	virtual void binaryConvert();
	virtual void save();
	virtual void addWave(vector<float>& _in);
	virtual void printStatus();
public:
	Encoder();
	virtual void getPCM(vector<float>* output);
	virtual void Generate(string message);
};