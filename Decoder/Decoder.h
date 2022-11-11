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
    double Amplitude;
    double SampleRate;
    double baud;
    double bitime;
    double speriod;
    Decoder();
    virtual void fft(std::vector<float>& signal);
    virtual void phasesync(std::vector<float >& signal);
};