#pragma once
#include "pch.h"
#ifdef ENCODER_EXPORTS
#define ENCODER __declspec(dllexport)
#else
#define ENCODER __declspec(dllimport)
#endif
#ifndef M_PI
#define M_PI 3.1415926535
#endif // !M_PI

using std::vector;
double AMPLITUDE = 1;
double SAMPLE_RATE = 44100;
double BAUD = 520 + 5/6;
double PER_BIT = 0.00192;
double PER_SAMPLE = 1 / SAMPLE_RATE;
using std::vector;
using std::size_t;
	void chartobinary(vector<bool>* Vectorptr, string c);
	inline int addwave(vector<float>* Vectorptr, vector<bool>& invect);
	inline void delay(vector<float>* Vectorptr, int delay);
	inline void effect(vector<float>* Vectorptr, unsigned int times, bool hilo);
	inline void attna(vector<float>* Vectorptr, int time);
	inline void attnb(vector<float>* Vectorptr, int time);
	void encode(std::string alert, bool attn, int attntime, int delaybeforetone, int delaybefore, int delayafter, int delayend);