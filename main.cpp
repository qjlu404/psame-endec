#include <iostream>
#include <string>
#include <cmath>
#include <bitset>
#include <fstream>
#include <vector>
using std::vector;
using std::size_t;
using std::ofstream;
using std::string;
double AMPLITUDE = 32000;
double SAMPLE_RATE = 96000;
//double M_PI = 3.14159265359;
double BAUD = 520 + 5/6;
double PER_BIT = 0.00192;
double PER_SAMPLE = 0.00001041666;

void writeToFile(ofstream& file, int value, int size)
{
	file.write(reinterpret_cast<const char*> (&value), size);
}
void chartobinary(vector<bool>* Vectorptr, string c)
{
	for (size_t i = 0; i < c.size() - 1; i++)
	{
		string output;
		output.append(std::bitset<8>(c[i]).to_string());

		for (size_t j = 0; j <= output.size(); j++)
		{
			if (output[j] == '1')
			{
				Vectorptr->push_back(true);
			}
			else
			{
				Vectorptr->push_back(false);
			}

		}
	}
}
int addwave(vector<double>* Vectorptr, vector<bool>* invect)
{

	for (size_t j = 0; j < invect->size(); j++)
	{
		if ((*invect)[j] == true)
		{
			double i = 0;
			while (i <= PER_BIT)
			{
				Vectorptr->push_back((AMPLITUDE) * sin(2 * M_PI * ((double)BAUD * 4) * i + 0));
				i += PER_SAMPLE;
			}
		}
		else
		{
			double i = 0;
			while (i <= PER_BIT)
			{
				Vectorptr->push_back((AMPLITUDE) * sin(2 * M_PI * ((double)BAUD * 3) * i + 0));
				i += PER_SAMPLE;
			}
		}
	}
	return 0;
}
void delay(vector<double>* Vectorptr, int delay)
{
	double i = 0;
	unsigned long long int j = 1;
	while (j <= SAMPLE_RATE * delay)
	{
		Vectorptr->push_back((AMPLITUDE / 8)*sin(2 * M_PI *((rand()%time(NULL) / 100)) * i + 0));
		i += 0.00001041666;
		j++;
	}
}
void getdcoffset(vector<double>* Vectorptr1, vector<double>* Vectorptr0, vector<double>& Vectorref)
{
    double i = 0;
    for (size_t j = 0; j < Vectorref.size(); j++)
	{
        Vectorptr1->push_back(((AMPLITUDE / 2) * sin(2 * M_PI * ((double)BAUD * 4) * i + 0)) + Vectorref[j]);
        Vectorptr0->push_back(((AMPLITUDE / 2) * sin(2 * M_PI * ((double)BAUD * 3) * i + 0)) + Vectorref[j]);
        i += PER_SAMPLE;
    }
}
void effect(vector<double>* Vectorptr, unsigned int times, bool hilo)
{
	unsigned int j = 0;
	while (j <= times)
	{
		if (hilo)
		{
			double i = 0;
			while (i <= PER_BIT)
			{
				Vectorptr->push_back((AMPLITUDE)*sin(2 * M_PI * ((double)BAUD * 4) * i + 0));
				i += PER_SAMPLE;
			}
		}
		else
		{
			double i = 0;
			while (i <= PER_BIT)
			{
				Vectorptr->push_back((AMPLITUDE)*sin(2 * M_PI * ((double)BAUD * 3) * i + 0));
				i += PER_SAMPLE;
			}
		}
		j++;
	}
}
void attna(vector<double>* Vectorptr, int time)
{
	int i = 0;
	double j = 0;
	while (i <= SAMPLE_RATE * time)
	{
		Vectorptr->push_back(((AMPLITUDE/2) * sin(2 * M_PI * (853) * j + 0)) + ((AMPLITUDE/2) * sin(2 * M_PI * (960) * j + 0)));
		j+= PER_SAMPLE;
		i++;
	}
}
void attnb(vector<double>* Vectorptr, int time)
{
	double j = 0;
	int i = 0;
	while (i <= SAMPLE_RATE * time)
	{
		Vectorptr->push_back(AMPLITUDE * sin(2 * M_PI * 1050 * j + 0));
		j += PER_SAMPLE;
		i++;
	}
}
int encode(string& alert, bool attn, int attntime, int delaybeforetone, int delaybefore, int delayafter, int delayend)
{
	vector<bool> binarydata;
	vector<bool> preamble = {
		1,0,1,0,1,0,1,1,
		1,0,1,0,1,0,1,1,
		1,0,1,0,1,0,1,1,
		1,0,1,0,1,0,1,1,
		1,0,1,0,1,0,1,1,
		1,0,1,0,1,0,1,1,
		1,0,1,0,1,0,1,1,
		1,0,1,0,1,0,1,1,
		1,0,1,0,1,0,1,1,
		1,0,1,0,1,0,1,1,
		1,0,1,0,1,0,1,1,
		1,0,1,0,1,0,1,1,
		1,0,1,0,1,0,1,1,
		1,0,1,0,1,0,1,1,
		1,0,1,0,1,0,1,1,
		1,0,1,0,1,
	};
	vector<double> pcm;
	vector<bool> EOM;
	bool peepchoice;
	if (alert.size() % 2 == 0)
		peepchoice = 0;
	else
		peepchoice = 1;

	string nnnn = "NNNN";

	//char to binary and stuff
	delay(&pcm, delaybeforetone);
	chartobinary(&binarydata, alert);
	chartobinary(&EOM, nnnn);
	//main tones
	effect(&pcm, (unsigned int)(alert.size() / 2), peepchoice);
	addwave(&pcm, &preamble);
	addwave(&pcm, &binarydata);
	effect(&pcm, (unsigned int)(alert.size() / 2), peepchoice);

	delay(&pcm, 1);

	effect(&pcm, (unsigned int)(alert.size() / 2), peepchoice);
	addwave(&pcm, &preamble);
	addwave(&pcm, &binarydata);
	effect(&pcm, (unsigned int)(alert.size() / 2), peepchoice);

	delay(&pcm, 1);

	effect(&pcm, (unsigned int)(alert.size() / 2), peepchoice);
	addwave(&pcm, &preamble);
	addwave(&pcm, &binarydata);
	effect(&pcm, (unsigned int)(alert.size() / 2), peepchoice);
	//tone and msg
	delay(&pcm, delaybefore);
	if (attn)
	{
		attna(&pcm, attntime);
	}
	else
	{
		attnb(&pcm, attntime);
	}
	delay(&pcm, delayafter);
	//eom
	effect(&pcm, (unsigned int)(alert.size() / 2), peepchoice);
	addwave(&pcm, &preamble);
	addwave(&pcm, &EOM);
	effect(&pcm, (unsigned int)(alert.size() / 2), peepchoice);

	delay(&pcm, 1);

	effect(&pcm, (unsigned int)(alert.size() / 2), peepchoice);
	addwave(&pcm, &preamble);
	addwave(&pcm, &EOM);
	effect(&pcm, (unsigned int)(alert.size() / 2), peepchoice);

	delay(&pcm, 1);

	effect(&pcm, (unsigned int)(alert.size() / 2), peepchoice);
	addwave(&pcm, &preamble);
	addwave(&pcm, &EOM);
	effect(&pcm, (unsigned int)(alert.size() / 2), peepchoice);

	delay(&pcm, 1);

	ofstream audioFile;
	audioFile.open("eas.wav", std::ios::binary);

	audioFile << "RIFF";
	audioFile << "----";
	audioFile << "WAVE";

	audioFile << "fmt ";
	writeToFile(audioFile, 16, 4); // Size
	writeToFile(audioFile, 1, 2); // Compression code
	writeToFile(audioFile, 1, 2); // Number of channels
	writeToFile(audioFile, SAMPLE_RATE, 4); // Sample rate
	writeToFile(audioFile, SAMPLE_RATE * 16 / 8, 4); // Byte rate
	writeToFile(audioFile, 16 / 8, 2); // Block align
	writeToFile(audioFile, 16, 2); // Bit depth
	audioFile << "data";
	audioFile << "----";
	//double preAudioPosition = (double)audioFile.tellp();
	//auto maxAmplitude = pow(2, 16 - 1) - 1;
	vector<double> a, b;
	getdcoffset(&a,&b,pcm);
	for (size_t i = 0; i < a.size(); i++)
	{
		writeToFile(audioFile, a[i], 2);
	}

	return 0;
}

int main()
{
    string a = "zczc-wxr-tor-081376+0015-3451122-wxyz/tv";
    encode(a,1,1,1,1,1,1);
}
