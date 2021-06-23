#pragma once
#include "pch.h"
#ifdef ENCODER_EXPORTS
#define EXPORT extern "C" __declspec(dllexport)
#else
#define EXPORT __declspec(dllimport)
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
EXPORT void chartobinary(vector<bool>* Vectorptr, std::string c);
EXPORT inline int addwave(vector<float>* Vectorptr, vector<bool>& invect);
EXPORT inline void delay(vector<float>* Vectorptr, int delay);
EXPORT inline void effect(vector<float>* Vectorptr, unsigned int times, bool hilo);
EXPORT inline void attna(vector<float>* Vectorptr, int time);
EXPORT inline void attnb(vector<float>* Vectorptr, int time);
EXPORT void encode(std::string alert, bool attn, int attntime, int delaybeforetone, int delaybefore, int delayafter, int delayend);
EXPORT void encodebin(bool alert[], bool attn, int attntime, int delaybeforetone, int delaybefore, int delayafter, int delayend);
EXPORT void ezencodebin(bool alert[], bool pream[], bool eom[]);