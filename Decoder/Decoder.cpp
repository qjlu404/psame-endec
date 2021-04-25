#include "pch.h"
#include "Decoder.h"
double AMPLITUDE = 32767;
double SAMPLE_RATE = 96000;
double M_PI = 3.14159265359;
double BAUD = 520 + 5 / 6;
double PER_BIT = 0.00192;
double PER_SAMPLE = 1 / SAMPLE_RATE;
using std::vector;
using std::size_t;
void decoder::phasesync(std::vector<double>& signal)
{
    vector<int> zeroxindexes;
    size_t j = 0;
    while (j < signal.size())
    {
        vector<double> zeroxperiod;
        for (size_t i = 0; i < signal.size() - 1; i++)
        {
            if (signal[i] != 0 && signbit(signal[i + 1]) != signbit(signal[i]))
            {
                zeroxindexes.push_back(i);
                j = i;
            }

        }
        for (int k = 1; k < zeroxindexes[k] - zeroxindexes[k - 1]; k++)
        {
            vector<double> coscheck;
            for (int l = 0; l < 360; l++)
            {
                coscheck.push_back(signal[l] + ((AMPLITUDE) * cos(2 * M_PI * ((double)BAUD * 4) + (l / 360) * M_PI)));
            }
            std::cout << *std::max_element(std::begin(coscheck), std::end(coscheck)) << std::endl;
        }
    }

}
