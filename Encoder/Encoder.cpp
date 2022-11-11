#include "pch.h"
#include <vector>
#include "encoder.h"
using std::ofstream;
using std::string;
void Encoder::binaryConvert()
{
	std::cout << "\n\n*Begin BinaryConvert\n\n";
	string output;
	for (int i = 0; i < c.size(); i++)
	{
		output.append(std::bitset<8>(c[i]).to_string());
	}

	std::cout << "* finished char to binary conversion." << std::endl;
	std::cout << "*  input: " << c << std::endl;
	std::cout << "* output string: " << output << std::endl;
	std::cout << "* output bin   : ";
	for (size_t i = 0; i < output.size(); i++)
	{
		char t[1];
		t[0] = output[i];
		int u = std::stoi(t);
		if (u == 1)
		{
			bin.push_back(1);
		}
		else
		{
			bin.push_back(0);
		}
	}
	std::cout << "\n\n*End of BinaryConvert\n\n";
}
void Encoder::save()
{
	AudioFile<float> audioFile;
	AudioFile<float>::AudioBuffer buffer;
	buffer.resize(1);
	buffer[0] = signalPCM;
	audioFile.setSampleRate(samplerate);
	audioFile.setNumChannels(1);
	int ok = audioFile.setAudioBuffer(buffer);
	if (ok)
	{
		std::cout << "\n*audioFile.setAudioBuffer returned code: " << ok << std::endl;
	}
	audioFile.save("pcm.wav");
}
void Encoder::printStatus()
{
	std::cout << "\n\n****PrintStatus****\n\n";
	std::cout << "Current message string: " << c << std::endl;
	std::cout << "Bin Data: ";
	for (size_t i = 0; i < bin.size(); i++)
	{
		std::cout << bin[i];
	}
	std::cout << "\n\n****End****\n\n";
}
Encoder::Encoder()
{

	std::cout << "\n* Initializing variables" << std::endl;
	amplitude = 1;
	samplerate = 9600;
	baud = 5.0 / 6.0 + 520.0;
	attntype = 1;
	attntime = 1;
	delay1 = 1;
	delay2 = 1;
	delay3 = 1;
	delay4 = 1;
	wave0 = vector<float>();
	wave1 = vector<float>();
	effect = vector<float>();
	delay = vector<float>();
	attnAM = vector<float>();
	attnNWS = vector<float>();
	signalPCM = vector<float>();
	DebugSignalInput = vector<int>();
	for (int i = 0; i<samplerate/baud;i++)
		{
			wave1.push_back(amplitude * sin(2 * M_PI * (baud * 4) * (i/ samplerate) + 0));
			wave0.push_back(amplitude * sin(2 * M_PI * (baud * 3) * (i / samplerate) + 0));
			effect.push_back(amplitude * sin(2 * M_PI * (baud * 4) * (i / samplerate) + 0));
		}
	for (int i = 0; i < samplerate; i++)
		{
			delay.push_back(0);
			attnAM.push_back(amplitude * sin(2 * M_PI * (853) * (i / samplerate) + 0)
						   + amplitude * sin(2 * M_PI * (960) * (i / samplerate) + 0));
			attnNWS.push_back(amplitude * sin(2 * M_PI * (1050) * (i / samplerate) + 0));
		}
	c = "\xab\xab\xab\xab\xab\xab\xab\xab\xab\xab\xab\xab\xab\xab\xab\xab";
	binaryConvert();
	std::cout << "\n* Done Initializing variables" << std::endl;
}
void Encoder::getPCM(vector<float>* output)
{
	for (size_t i = 0; i < signalPCM.size(); i++)
	{
		output->push_back(signalPCM[i]);
	}
}
void Encoder::Generate(string message)
{
	std::cout << "\n\n*Begin Generate\n\n";
	c.clear();
	c = message;
	delay1 = 3;
	delay2 = 1;
	delay3 = 1;
	delay4 = 1;
	binaryConvert();
	printStatus();
	//generate blank delay for 1 second * i
	for (int i = 0; i < delay1; i++)
	{
		addWave(delay);
	}
	printStatus();
	//read binary data and generate wave PCM
	std::cout << "* Debug Signal Output: ";
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < bin.size(); j++)
		{
			if (bin[j] == 1)
			{
				addWave(wave1);
				std::cout << '1';
			}
			if (bin[j] == 0)
			{
				addWave(wave0);
				std::cout << '0';
			}
		}
		addWave(effect);
		addWave(delay);
	}
	std::cout << std::endl;
	for (int i = 0; i < delay2; i++)
	{
		addWave(delay);
	}
	for (int i = 0; i < attntime; i++)
	{
		if (attntype)
		{
			addWave(attnAM);
		}
		if (!attntype)
		{
			addWave(attnNWS);
		}
	}
	for (int i = 0; i < delay3; i++)
	{
		addWave(delay);
	}

	c.clear();
	bin.clear();
	c = "\xab\xab\xab\xab\xab\xab\xab\xab\xab\xab\xab\xab\xab\xab\xab\xabNNNN";
	binaryConvert();
	std::cout << "*EOM Bin Debug: ";
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < bin.size(); j++)
		{
			if (bin[j] == 1)
			{
				addWave(wave1);
				std::cout << '1';
			}
			if (bin[j] == 0)
			{
				addWave(wave0);
				std::cout << '0';
			}
		}
		addWave(effect);
		addWave(delay);
	}
	std::cout << std::endl;
	for (int i = 0; i < delay4; i++)
	{
		addWave(delay);
	}

	save();
	std::cout << "\n\nEnd Generate\n\n";
}
void Encoder::addWave(vector<float>& _in)
{
	for (size_t i = 0; i < _in.size(); i++)
	{
		signalPCM.push_back(_in[i]);
	}
}