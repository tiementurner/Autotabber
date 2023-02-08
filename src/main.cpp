
//////////////////////
// https://betterexplained.com/articles/an-interactive-guide-to-the-fourier-transform/
//////////////////////


#include "../inc/includes.hpp"
#include "../inc/wavheader.hpp"
// Function prototypes
int getFileSize(FILE* inFile);
int main(int argc, char* argv[])
{
    wav_hdr wavHeader;
    int headerSize = sizeof(wav_hdr), filelength = 0;
    const char* filePath;
    string input;
    
    if (argc <= 1)
    {
        cout << "Input wave file name: ";
        cin >> input;
        cin.get();
        filePath = input.c_str();
    }
    else
    {
        filePath = argv[1];
        cout << "Input wave file name: " << filePath << endl;
    }
    FILE* wavFile = fopen(filePath, "r");
    if (wavFile == nullptr)
    {
        fprintf(stderr, "Unable to open wave file: %s\n", filePath);
        return 1;
    }


    //Read the header
    size_t bytesRead = fread(&wavHeader, 1, headerSize, wavFile);
    cout << "Header Read " << bytesRead << " bytes." << endl;
    cout << "File is                    :" << filelength << " bytes." << endl;
    cout << "RIFF header                :" << wavHeader.RIFF[0] << wavHeader.RIFF[1] << wavHeader.RIFF[2] << wavHeader.RIFF[3] << endl;
    cout << "WAVE header                :" << wavHeader.WAVE[0] << wavHeader.WAVE[1] << wavHeader.WAVE[2] << wavHeader.WAVE[3] << endl;
    cout << "FMT                        :" << wavHeader.fmt[0] << wavHeader.fmt[1] << wavHeader.fmt[2] << wavHeader.fmt[3] << endl;
    cout << "Data size                  :" << wavHeader.ChunkSize << endl;
    // Display the sampling Rate from the header
    cout << "Sampling Rate              :" << wavHeader.SamplesPerSec << endl;
    cout << "Number of bits used        :" << wavHeader.bitsPerSample << endl;
    cout << "Number of channels         :" << wavHeader.NumOfChan << endl;
    cout << "Number of bytes per second :" << wavHeader.bytesPerSec << endl;
    cout << "Data length                :" << wavHeader.Subchunk2Size << endl;
    cout << "Audio Format               :" << wavHeader.AudioFormat << endl;
    // Audio format 1=PCM,6=mulaw,7=alaw, 257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM
    cout << "Block align                :" << wavHeader.blockAlign << endl;
    cout << "Data string                :" << wavHeader.Subchunk2ID[0] << wavHeader.Subchunk2ID[1] << wavHeader.Subchunk2ID[2] << wavHeader.Subchunk2ID[3] << endl;
    cout << "Audio Format               :" << wavHeader.AudioFormat << endl;


    if (bytesRead > 0)
    {
        //Read the data
        uint16_t bytesPerSample = wavHeader.bitsPerSample / 8;      //Number     of bytes per sample
        uint64_t numSamples = wavHeader.ChunkSize / bytesPerSample; //How many samples are in the wav file?
        static const uint16_t BUFFER_SIZE = 4096;
        short* buffer = new short[BUFFER_SIZE];
        int i = 0;
        std::vector<double> samples(numSamples);
        std::vector<double> peaks;

        while ((bytesRead = fread(buffer, sizeof buffer[0], bytesPerSample, wavFile)) > 0)
        {
            samples[i] = *buffer;
            i++;
        }

        // int numSamples = 44100;
        // double frequency = 440.0;
        // int size = 1024;

        // std::vector<double> sine_wave(size);

        // for (int i = 0; i < size; i++)
        // {
        //     double t = static_cast<double>(i) / numSamples;
        //     sine_wave[i] = sin(2 * M_PI * frequency * t);
        // }

        for (int i = 0; i < numSamples; i++)
        {
            double multiplier = 0.5 * (2 * M_PI * i / numSamples);
            samples[i] = samples[i] * multiplier;
        }

        fftw_complex in[numSamples], out[numSamples];
        for (int i = 0; i < numSamples; i++) {
            in[i][0] = samples[i];
            in[i][1] = 0.0;
        }
        fftw_plan p = fftw_plan_dft_1d(numSamples, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
        fftw_execute(p);

        double magnitude[numSamples];
        for (int i = 0; i < numSamples; i++) {
            magnitude[i] = std::sqrt(out[i][0] * out[i][0] + out[i][1] * out[i][1]);
        }
        
        double max = 0;
        int index=0;
        int j = 0;
        for (int i = 250; i < 800; i++) {
            if (magnitude[i] > max) {
                max = magnitude[i];
                index = i;
            }
            j = i;
        }
        cout << j << endl;
        cout << index << " ---- " << max << endl;
        cout << 220 << " --- " << magnitude[220] << endl;
        cout << 440 << " --- " << magnitude[440] << endl;

        //delete [] buffer;
        //buffer = nullptr;
        filelength = getFileSize(wavFile);
    }
    fclose(wavFile);
    return 0;
}
// find the file size
int getFileSize(FILE* inFile)
{
    int fileSize = 0;
    fseek(inFile, 0, SEEK_END);
    fileSize = ftell(inFile);
    fseek(inFile, 0, SEEK_SET);
    return fileSize;
}



        