#include "../Encoder/Encoder.h"
#include "../Decoder/Decoder.h"
void testit(int phase, int b)
{
	std::cout << "**Testwave Begin**" << std::endl;
	std::vector<float> testwave;
	Decoder d;
	for (int i = 0; i < d.samplerate / d.baud; i++)
	{
		testwave.push_back(d.amplitude * sin(2 * M_PI * (d.baud * b)) * (i / d.samplerate) + phase);
	}
	d.Test(testwave);
	std::cout << "**Testwave End**" << std::endl;
}
void main()
{
	//Encoder e;
	//e.Generate("ZCZC-WXR-TOR-039173-039051-139069+0030-1591829-KCLE/NWS");
	testit(0, 3); /* Zero Offset: -0.14805	 zero greater than one
					 One Offset : -0.112531 */
	testit(0, 4); /*Zero Offset: -457060 zero still greater than one -_- (aargh!)
					One Offset : -347407*/
	testit(90, 3);/*Zero Offset: 16047.9
					One Offset : 15600.2*/
	testit(90, 4);/*Zero Offset: -441012
					One Offset : -331807	yup still the same shituation.
										  Ill figure it out tommorow*/
}