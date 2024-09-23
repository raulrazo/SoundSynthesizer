#include <iostream>
using namespace std;

#include "olcNoiseMaker.h"

atomic <double> dFrequencyOutput = 0.0;

double MakeNoise(double dTime) {
	double dOutput = 1.0 * (sin(dFrequencyOutput * 2 * 3.14159 * dTime) + sin((dFrequencyOutput + 20.0) * 2 * 3.14159 * dTime));


//	// Makes it a square wave
//	if (dOutput > 0.0) {
//		return 0.2;
//	}
//	else {
//		return -0.2;
//	}
}

int main() {
	wcout << "onelonecoder.com - Synthesizer Part 1" << endl;

	// Get all sound hardware
	vector<wstring> devices = olcNoiseMaker<short>::Enumerate();

	// Display findings
	for (auto d : devices) wcout << "Found Output Device: " << d << endl;

	// Create sound machine
	olcNoiseMaker<short> sound(devices[0], 44100, 1, 8, 512);

	// Link noise function with sound machine
	sound.SetUserFunction(MakeNoise);

	double dOctaveBaseFrequency = 110.0; // A2
	double d12thRootOf2 = pow(2.0, 1.0 / 12.0); // Divides into 12 notes

	while (1) {
		// Add a keyboard like a piano

		bool bKeyPressed = false;
		for (int k = 0; k < 15; k++) {
			// Maps out keys like piano keys, xbc = , and xbc = .
			if (GetAsyncKeyState((unsigned char)("ZSXCFVGBNJMK\xbcL\xbe"[k])) & 0x8000) {
				dFrequencyOutput = dOctaveBaseFrequency * pow(d12thRootOf2, k); // 2nd num in pow represents # of semitones
				bKeyPressed = true;
			}
		}

		if (!bKeyPressed) {
			dFrequencyOutput = 0.0;
		}

	}


	return 0;
}