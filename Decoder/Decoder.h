#pragma once
#ifdef DECODER_EXPORTS
#define DECODER __declspec(dllexport)
#else
#define DECODER __declspec(dllimport)
#endif
#ifndef M_PI
#define M_PI 3.1415926535
#endif // !M_PI

extern "C" class DECODER Decoder
{
public:
    float amplitude;
    float samplerate;
    float baud;
    Decoder();
    virtual void Test(std::vector<float> _in);
};