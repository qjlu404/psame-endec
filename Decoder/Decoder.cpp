#include "pch.h"
#include "Decoder.h"
using std::vector;
using std::size_t;
Decoder::Decoder()
{
	amplitude = 100000;
	samplerate = 44100;
	baud = 520.0 + 5.0 / 6.0;
}
void Decoder::Test(std::vector<float> _in)
{
	std::vector<float> qsignal1;
	std::vector<float> isignal1;
	std::vector<float> qsignal0;
	std::vector<float> isignal0;
	for (size_t i = 0; i < samplerate/baud; i++)
	{
		qsignal1.push_back(amplitude * sin(2 * M_PI * (baud * 4) * (i / samplerate) + 0));
		qsignal0.push_back(amplitude * sin(2 * M_PI * (baud * 3) * (i / samplerate) + 0));
		isignal1.push_back(amplitude * cos(2 * M_PI * (baud * 4) * (i / samplerate) + 0));
		isignal0.push_back(amplitude * cos(2 * M_PI * (baud * 3) * (i / samplerate) + 0));
	}
	std::vector<float> DCQ1;
	std::vector<float> DCI1;
	std::vector<float> DCQ0;
	std::vector<float> DCI0;
	float q1mean = 0.0;
	float i1mean = 0.0;
	float q0mean = 0.0;
	float i0mean = 0.0;
	for (size_t i = 0; i < samplerate/baud; i++)
	{
		DCQ1.push_back(_in[i] * qsignal1[i]);
		q1mean += _in[i] * qsignal1[i];
		DCI1.push_back(_in[i] * isignal1[i]);
		i1mean += _in[i] * isignal1[i];
		DCQ0.push_back(_in[i] * qsignal0[i]);
		q0mean += _in[i] * qsignal0[i];
		DCI0.push_back(_in[i] * isignal0[i]);
		i0mean += _in[i] * isignal0[i];
	}
	float zerooffset = ((i0mean / DCI0.size()) + (q0mean / DCQ0.size()))/2;
	std::cout << "Zero Offset: " << zerooffset << std::endl;
	float oneoffset = ((i1mean / DCI1.size()) + (q1mean / DCQ1.size()))/2;
	std::cout << "One Offset : " << oneoffset << std::endl;
}
