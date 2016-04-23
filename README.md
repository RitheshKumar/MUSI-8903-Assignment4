# MUSI-8903-Assignment4, and Part 2 of Assignment 5
## Master branch is made for Assignment 4 which is the vibrato plugin
## GUI branch is made for part of Assignment 5 which is adding PPM to the plugin
Assignment for Audio Software Engineering class: Vibrato vst + PPM

##Integrating PPM into vibrato plugin

We split the assignment 5 into two parts. Part 1 is the implementation and tests for the Peak Program Meter class. In part 2, we integrate tested PPM class into vibrato plugin which we created in assignment 4. Due to these two parts are relatively seperate to each other, we have two repos for assignment 5. 

This is the repository for second part of assignment 5. 

The repository of PPM is https://github.com/EDBE/MUSIC-8903-2016-assignment5-PPM

### Step 1: Implement a rectangular MeterComponent and add it to your GUI

### Step 2: Integrate the PPM into your PlugInProcessor
To simplify the display, the PlugInProcessor will take the average peak value from each channel, and display in the GUI.

### Step 3: Add a Timer to your PluginEditor that is called every 10ms
The timer callback ask peak value from pluginProcessor every 10ms, and update display.
