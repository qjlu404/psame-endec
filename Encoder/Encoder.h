#pragma once
#ifdef ENCODER_EXPORTS
#define ENCODER __declspec(dllexport)
#else
#define ENCODER __declspec(dllimport)
#endif
#include <vector>
using std::vector;
constexpr auto AMPLITUDE = 30000;
constexpr auto SAMPLE_RATE = 44100;
constexpr auto M_PI = 3.1415926535;
constexpr auto BAUD = 520.825;
constexpr auto PER_BIT = 0.00192;
constexpr auto PER_SAMPLE = 0.00002267573;
#define SPACE 86 // Sample rate divided by baud rounded up to the nearest integer


extern "C" ENCODER void chartobinary(vector<bool>* Vectorptr, char c[]);
extern "C" ENCODER int binarytosine(vector<double>* Vectorptr, vector<bool>* invect);