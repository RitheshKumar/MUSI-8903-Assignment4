//
//  PeakProgramMeter.h
//  Vibrato2Plugin
//
//  Created by Music Technology on 4/19/16.
//
//

#ifndef __Vibrato2Plugin__PeakProgramMeter__
#define __Vibrato2Plugin__PeakProgramMeter__

#include <stdio.h>
#include <math.h>
#include <algorithm>
#include "ErrorDef.h"

class PeakProgramMeter {
    
public:
    
    static Error_t createInstance (PeakProgramMeter*& pPPM);
    static Error_t destroyInstance (PeakProgramMeter*& pPPM);
    
    Error_t initInstance(float sampleRate, int windowSize, int numChannel);
    Error_t resetInstance();
    
    Error_t process (const float **ppfInputBuffer, float **ppfOutputBuffer, int numOfFrames);
    Error_t ppmProcess (const float **ppfInputBuffer, float **ppfOutputBuffer, int numOfFrames, float filterBuf);
    
private:
    PeakProgramMeter();
    ~PeakProgramMeter();
    
    int m_iNumChannels;
    int m_iWindowSize;
    int m_iHopSize;
    float m_fSampleRate;
    float** m_ppfTempoBuffer;
    const float kfAlphaAtt = 1.f - (exp(-2.2f / (m_fSampleRate*.01f)));
    const float kfAlphaRelease = 1.f - (exp(-2.2f / (m_fSampleRate*1.5f)));
    const float kfEpsilon = 1e-5;
    bool m_bIsInitialized;
    
};

#endif /* defined(__Vibrato2Plugin__PeakProgramMeter__) */
