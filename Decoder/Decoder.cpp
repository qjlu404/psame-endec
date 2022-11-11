#include "pch.h"
#include "Decoder.h"
using std::vector;
using std::size_t;
Decoder::Decoder()
{
	Amplitude = 32767;
	SampleRate = 96000;
	baud = 520 + 5 / 6;
	bitime = 0.00192;
	speriod = 1 / SampleRate;
}

void Decoder::fft(std::vector<float>& signal)
{
	size_t samples = signal.size();
	vector<double> ccs;
	for (size_t i = 0; i < samples; i++)
	{
		ccs.push_back(cos(((2 * M_PI) / samples) * signal[i]));
	}
}
void Decoder::phasesync(std::vector<float>& signal)
{
}
