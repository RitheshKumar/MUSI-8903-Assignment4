//
//  peakBar.cpp
//  Vibrato2Plugin
//
//  Created by Rithesh Kumar Ravikumar on 4/19/16.
//
//

#ifndef ThisIsCoptaa_CopterBody_h
#define ThisIsCoptaa_CopterBody_h

#include "../JuceLibraryCode/JuceHeader.h"

class peakBar : public Component {
public:
    peakBar(): _peakVal(0.5f){}
    ~peakBar(){}
    
    
    void paint(Graphics &g){
        g.setColour(Colours::yellow);
        g.fillRect( 0, 0, getWidth(), getHeight() );
        g.setColour(Colours::green);
        int widthVal = _peakVal*getWidth();
        g.fillRect(0, getHeight()*(0.13), widthVal, getHeight()*0.75 );
    }
    
    
    void setPeakVal(float val) { _peakVal = val; }
    
private:
    float _peakVal;
};
#endif