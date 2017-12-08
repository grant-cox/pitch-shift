/*
Grant Cox
grant.cox@uky.edu
CS315 Final Project
11/28/2017
*/

/*
1.window function (fairly trivial, e.g. Hanning)
2.FFT (FFTW would be a good choice but if licensing is an issue then go for Kiss FFT or similar)
3.calculate log magnitude of frequency domain components (trivial: log(sqrt(re * re + im * im))
*/

//frequency = 440 * 2^(n/12)
//so have user input n for +n or -n shift in pitch, pass 2^(n/12) to smbpitchshift

#include <iostream>
#include <string>
#include <armadillo>
#include "smbPitchShift.cpp"
#include "AudioFile.h"
using namespace std;
using namespace arma;


int main(int argc, char* argv[]) {
     ///////////////////////////////////////////////////////////////////////////
     // open files
     //
     //
     string fname = argv[1];
     AudioFile<float> siginFloat;
     cout << "loading audio file(float)...";
     siginFloat.load(fname);
     cout << "done." << endl;
     

     ///////////////////////////////////////////////////////////////////////////
     // print file information
     //
     //
     cout << "\nSummary of input file: " << endl;
     siginFloat.printSummary();
     float pitchShift = stof(argv[3]);
     pitchShift = pow(2,pitchShift/12);
     cout << "shifting factor:\t" << pitchShift << endl;
     int samples = siginFloat.getNumSamplesPerChannel();
     long fftFrameSize = 2048;
     long osamp = 32;
     float sampleRate = siginFloat.getSampleRate();



     ///////////////////////////////////////////////////////////////////////////
     // allocate data to float and double arrays
     //
     //
     cout << "\nallocating memory and copying for pitch shifting...";
     float * dataFloat = new float[samples];
     for(int i = 0; i < samples; i++) dataFloat[i] = siginFloat.samples[0][i];



     ///////////////////////////////////////////////////////////////////////////
     // do the pitch shifting
     //
     //
     cout << "\npitch shifting...";
     smbPitchShift(pitchShift, samples, fftFrameSize, osamp, sampleRate, dataFloat, dataFloat);
     cout << "done\n";


     ///////////////////////////////////////////////////////////////////////////
     // output to file
     //
     //
     for(int i = 0; i < samples; i++)
          siginFloat.samples[0][i] = dataFloat[i];

     string fnameout = argv[2];
     cout << "writing to output file...";
     siginFloat.save(fnameout);
     cout << "done." << endl;

     cout << "deallocating and exiting..." << endl;
     delete[] dataFloat;
     return 0;
}
