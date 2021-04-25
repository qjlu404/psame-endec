#pragma once
#include "pch.h"
#ifdef ENCODER_EXPORTS
#define ENCODER __declspec(dllexport)
#else
#define ENCODER __declspec(dllimport)
#endif
using std::vector;
double AMPLITUDE = 32700;
double SAMPLE_RATE = 96000;
double M_PI = 3.14159265359;
double BAUD = 520 + 5/6;
double PER_BIT = 0.00192;
double PER_SAMPLE = 0.00001041666;
using std::vector;
using std::size_t;
extern "C" class ENCODER encoder
{
public:
	void encode(std::string& alert, bool attn, int attntime, int delaybeforetone, int delaybefore, int delayafter, int delayend);
};