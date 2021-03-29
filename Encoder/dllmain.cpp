// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "encoder.h"
using std::ofstream;
using std::string;

void writeToFile(ofstream& file, int value, int size) 
{
	file.write(reinterpret_cast<const char*> (&value), size);
}
void chartobinary(vector<bool>* Vectorptr, string c)
{
	for (int i = 0; i < c.size() - 1; i++)
	{
		string output;
		string a = "0";
		output.append(std::bitset<7>(c[i]).to_string());
		output.append(a);
		
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
int binarytosine(vector<double>* Vectorptr, vector<bool>* invect)
{   
	
	for (size_t j = 0; j < invect->size(); j++)
	{
		if ((*invect)[j] == true)
		{
			double i = 0;
			while (i <= PER_BIT)
			{
				Vectorptr->push_back((AMPLITUDE) * sin(2 * M_PI * (BAUD * 4) * i + 0));
				i += PER_SAMPLE;
			}
		}
		else
		{
			double i = 0;
			while (i <= PER_BIT)
			{
				Vectorptr->push_back((AMPLITUDE) * sin(2 * M_PI * (BAUD * 3) * i + 0));
				i += PER_SAMPLE;
			}
		}
	}
	return 0;
}
void delay(vector<double>* Vectorptr, int delay)
{
	double i = 0;
	while (i <= (double)SAMPLE_RATE * delay)
	{
		Vectorptr->push_back(0);
		i ++;
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
int encode(string alert, bool attn, int attntime, int delaybeforetone, int delaybefore, int delayafter, int delayend)
{
	string nnnn = "NNNN";
	vector<double> pcm;
	vector<bool> peep;
	int randnumber = (rand() % 10);
	for (int i = 0; i < randnumber; i++)
	{
		peep.push_back(1);
	}
	vector<bool> binarydata;
	vector<bool> EOM;
	delay(&pcm, delaybeforetone);
	chartobinary(&binarydata, alert);
	chartobinary(&EOM, nnnn);
	binarytosine(&pcm, &peep);
	binarytosine(&pcm, &binarydata);
	binarytosine(&pcm, &peep);
	delay(&pcm, 1);
	binarytosine(&pcm, &peep);
	binarytosine(&pcm, &binarydata);
	binarytosine(&pcm, &peep);
	delay(&pcm, 1);
	binarytosine(&pcm, &peep);
	binarytosine(&pcm, &binarydata);
	binarytosine(&pcm, &peep);
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
	binarytosine(&pcm, &peep);
	binarytosine(&pcm, &EOM);
	binarytosine(&pcm, &peep);
	delay(&pcm, 1);
	binarytosine(&pcm, &peep);
	binarytosine(&pcm, &EOM);
	binarytosine(&pcm, &peep);
	delay(&pcm, 1);
	binarytosine(&pcm, &peep);
	binarytosine(&pcm, &EOM);
	binarytosine(&pcm, &peep);
	delay(&pcm, 1);

	binarydata.clear();
	
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
	double preAudioPosition = audioFile.tellp();
	auto maxAmplitude = pow(2, 16 - 1) - 1;
	int b = pcm.size();
	for (size_t i = 0; i < pcm.size(); i++)
	{
		writeToFile(audioFile, pcm[i], 2);
	}

	return 0;
}