#pragma once
#ifdef ENCODER_EXPORTS
#define ENCODER __declspec(dllexport)
#else
#define ENCODER __declspec(dllimport)
#endif
using std::vector;
constexpr auto AMPLITUDE = 32000;
constexpr auto SAMPLE_RATE = 96000;
constexpr auto M_PI = 3.14159265359;
constexpr auto BAUD = 520 + 5/6;
constexpr auto PER_BIT = 0.00192;
constexpr auto PER_SAMPLE = 0.00001041666;
using std::vector;
using std::size_t;
extern "C" ENCODER int encode(std::string& alert, bool attn, int attntime, int delaybeforetone, int delaybefore, int delayafter, int delayend);