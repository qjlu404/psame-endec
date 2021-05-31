#include "pch.h"
#include "encoder.h"
#include "../Decoder/Decoder.h"
using std::ofstream;
using std::string;
void writeToFile(ofstream& file, int value, int size)
	{
		file.write(reinterpret_cast<const char*> (&value), size);
	}
void save(vector<double>& pcm, string fname)
{
	ofstream audioFile;
	audioFile.open(fname, std::ios::binary);

	audioFile << "RIFF---WAVEfmt ";
	writeToFile(audioFile, 16, 4);
	size_t setsizea = audioFile.tellp();
	writeToFile(audioFile, 2, 2);
	writeToFile(audioFile, 2, 2);
	writeToFile(audioFile, (int)SAMPLE_RATE, 4);
	writeToFile(audioFile, (int)SAMPLE_RATE * 4, 4);
	writeToFile(audioFile, 4, 2);
	writeToFile(audioFile, 32, 2);
	size_t data_chunk_pos = audioFile.tellp();
	audioFile << "data----";
	for (int i = 0; i < pcm.size(); i++)
	{
		writeToFile(audioFile, pcm[i], 2);
	}
	size_t file_length = audioFile.tellp();

	audioFile.seekp(setsizea);
	writeToFile(audioFile, pcm.size(), 4);
	audioFile.seekp(data_chunk_pos + 4);
	writeToFile(audioFile, file_length - data_chunk_pos + 8, sizeof(size_t));
	

	// Fix the file header to contain the proper RIFF chunk size, which is (file size - 8) bytes
	audioFile.seekp(0 + 4);
	writeToFile(audioFile, file_length - 8, 4);
}
void chartobinary(vector<bool>* Vectorptr, string c)
	{
		for (int i = 0; i < c.size() - 1; i++)
		{
			string output;
			output.append(std::bitset<8>(c[i] & 0x7f).to_string());;

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
inline int addwave(vector<double>* Vectorptr, vector<bool>& invect)
	{

		for (size_t j = 0; j < invect.size(); j++)
		{
			if (invect[j] == true)
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
		}
		return 0;
	}
inline void delay(vector<double>* Vectorptr, int delay)
	{
		double i = 0;
		unsigned long long int j = 1;
		while (j <= (double)SAMPLE_RATE * delay)
		{
			Vectorptr->push_back(0);//(AMPLITUDE / 32) * sin(2 * M_PI * ((rand() % time(NULL))) * i + 0));
			i += 0.00001041666;
			j++;
		}
	}
inline void effect(vector<double>* Vectorptr, unsigned int times, bool hilo)
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
inline void attna(vector<double>* Vectorptr, int time)
	{
		int i = 0;
		double j = 0;
		while (i <= SAMPLE_RATE * time)
		{
			Vectorptr->push_back(((AMPLITUDE / 2) * sin(2 * M_PI * (853) * j + 0)) + ((AMPLITUDE / 2) * sin(2 * M_PI * (960) * j + 0)));
			j += PER_SAMPLE;
			i++;
		}
	}
inline void attnb(vector<double>* Vectorptr, int time)
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
void Encoder::encode(string alert, bool attn, int attntime, int delaybeforetone, int delaybefore, int delayafter, int delayend)
{
	vector<bool> binarydata;
	vector<bool> EOM = {
	0,1,0,0,1,1,1,0,0,1,0,0,1,1,1,0,0,1,0,0,1,1,1,0,0,1,0,0,1,1,1,0,
	};
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
		1,0,1,0,1,0,1,1
	};
	vector<double> pcm;
	bool peepchoice;
	if (alert.size() % 2 != 0)
		peepchoice = 0;
	else
		peepchoice = 1;
	unsigned int pl = (unsigned int)(alert.size() / 2);

	//char to binary and stuff
	delay(&pcm, delaybeforetone);
	chartobinary(&binarydata, alert);
	//main tones
	if (peepchoice)
		effect(&pcm, pl, peepchoice);
	addwave(&pcm, preamble);
	addwave(&pcm, binarydata);
	effect(&pcm, pl, peepchoice);

	delay(&pcm, 1);

	if (peepchoice)
		effect(&pcm, pl, peepchoice);
	addwave(&pcm, preamble);
	addwave(&pcm, binarydata);
	effect(&pcm, pl, peepchoice);

	delay(&pcm, 1);

	if (peepchoice)
		effect(&pcm, pl, peepchoice);
	addwave(&pcm, preamble);
	addwave(&pcm, binarydata);
	effect(&pcm, pl, peepchoice);
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
	if (peepchoice)
		effect(&pcm, pl, peepchoice);
	addwave(&pcm, preamble);
	addwave(&pcm, EOM);
	effect(&pcm, pl, peepchoice);

	delay(&pcm, 1);

	if (peepchoice)
		effect(&pcm, pl, peepchoice);
	addwave(&pcm, preamble);
	addwave(&pcm, EOM);
	effect(&pcm, pl, peepchoice);

	delay(&pcm, 1);

	if (peepchoice)
		effect(&pcm, pl, peepchoice);
	addwave(&pcm, preamble);
	addwave(&pcm, EOM);
	effect(&pcm, pl, peepchoice);

	delay(&pcm, 1);
	//decoder a;
	//a.phasesync(pcm);

	save(pcm, "pcm.wav");
}