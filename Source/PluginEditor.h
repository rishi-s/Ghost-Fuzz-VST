/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 4.3.1

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_A660A48E9E1E06CB__
#define __JUCE_HEADER_A660A48E9E1E06CB__

//[Headers]     -- You can add your own extra header files here --

//#include "../../Shared/LookAndFeelCustom.h" //used to be _nographics
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class GhostFuzzAudioProcessorEditor  : public AudioProcessorEditor,
                                       public Timer,
                                       public ButtonListener,
                                       public SliderListener,
                                       public ComboBoxListener
{
public:
    //==============================================================================
    GhostFuzzAudioProcessorEditor (GhostFuzzAudioProcessor* ownerFilter);
    ~GhostFuzzAudioProcessorEditor();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void timerCallback() override;
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

    ScopedPointer<ResizableCornerComponent> resizer;
    ComponentBoundsConstrainer resizeLimits;

	//static LookAndFeelCustom* customLookAndFeel;

	AudioPlayHead::CurrentPositionInfo lastDisplayedPosition;

    GhostFuzzAudioProcessor* getProcessor() const
    {
        return static_cast <GhostFuzzAudioProcessor*> (getAudioProcessor());
    }

    void displayPositionInfo (const AudioPlayHead::CurrentPositionInfo& pos);

	void UpdateInterfaceValues();

	void SetComboBoxActivity(ComboBox * comboBox, bool active);
	void SetSliderActivity(Slider * slider, bool active);


    //[/UserVariables]

    //==============================================================================
    ScopedPointer<TextButton> bypassButton;
    ScopedPointer<Slider> gainSlider;
    ScopedPointer<ComboBox> typeComboBox;
    ScopedPointer<Slider> drySlider;
    ScopedPointer<Slider> wetSlider;
    ScopedPointer<Slider> feedbackSlider;
    ScopedPointer<Label> dryLabel;
    ScopedPointer<Label> wetLabel;
    ScopedPointer<Label> feedbackLabel;
    ScopedPointer<Slider> delaySlider;
    ScopedPointer<Label> delayLabel;
    ScopedPointer<Slider> outputSlider;
    ScopedPointer<Label> gainLabel;
    ScopedPointer<Label> gainLabel2;
    ScopedPointer<Slider> lowpassSlider;
    ScopedPointer<Label> highcutLabel;
    ScopedPointer<Label> label;
    ScopedPointer<Label> label2;
    ScopedPointer<Label> label3;
    ScopedPointer<Slider> highpassSlider;
    ScopedPointer<Label> lowcutLabel;
    ScopedPointer<TextButton> soloButton;
    ScopedPointer<TextButton> bypassButton2;
    ScopedPointer<Label> gainLabel3;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GhostFuzzAudioProcessorEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_A660A48E9E1E06CB__
