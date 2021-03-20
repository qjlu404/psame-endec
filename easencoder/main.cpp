#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "../Encoder/Encoder.h"
using std::vector;
using std::ofstream;


void writeToFile(ofstream& file, int value, int size) {
	file.write(reinterpret_cast<const char*> (&value), size);
}

int main()
{
	char alert[] = "ZCZC-WXR-RWT-017091-017091-017091-017063-017091-017197-017089-017091-017097-017089-017091-017093-017089-017091-017089-017091-017043-017091-018089+0015-3651704-KLOT/NWS\xff";
	vector<double> totaldata;
	vector<bool> binarydata = { 1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,1
	};
	chartobinary(&binarydata, alert);
	binarytosine(&totaldata, &binarydata);
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
	for (size_t i = 0; i < totaldata.size(); i++) 
	{
		writeToFile(audioFile, totaldata[i], 2);
	}
}