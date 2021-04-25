#pragma once
#ifdef DECODER_EXPORTS
#define DECODER __declspec(dllexport)
#else
#define DECODER __declspec(dllimport)
#endif
extern "C" class DECODER decoder
{
public:
    void phasesync(std::vector<double>& signal);
};