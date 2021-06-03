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

//[Headers] You can add your own extra header files here...
#include "PluginProcessor.h"
//[/Headers]

#include "PluginEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...

//LookAndFeelCustom* GhostFuzzAudioProcessorEditor::customLookAndFeel = NULL;

//[/MiscUserDefs]

//==============================================================================
GhostFuzzAudioProcessorEditor::GhostFuzzAudioProcessorEditor (GhostFuzzAudioProcessor* ownerFilter)
    : AudioProcessorEditor (ownerFilter)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (bypassButton = new TextButton ("on off button"));
    bypassButton->setButtonText (TRANS("Bypass"));
    bypassButton->addListener (this);
    bypassButton->setColour (TextButton::buttonColourId, Colour (0xffad8585));
    bypassButton->setColour (TextButton::buttonOnColourId, Colour (0xffe4610c));

    addAndMakeVisible (gainSlider = new Slider ("new slider"));
    gainSlider->setRange (0, 24, 0.01);
    gainSlider->setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    gainSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    gainSlider->setColour (Slider::rotarySliderFillColourId, Colour (0x7fff0000));
    gainSlider->setColour (Slider::textBoxTextColourId, Colours::white);
    gainSlider->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    gainSlider->setColour (Slider::textBoxOutlineColourId, Colour (0x00808080));
    gainSlider->addListener (this);

    addAndMakeVisible (typeComboBox = new ComboBox ("new combo box"));
    typeComboBox->setEditableText (false);
    typeComboBox->setJustificationType (Justification::centredLeft);
    typeComboBox->setTextWhenNothingSelected (String());
    typeComboBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    typeComboBox->addItem (TRANS("Valve"), 1);
    typeComboBox->addItem (TRANS("Overdrive"), 2);
    typeComboBox->addItem (TRANS("Clipping"), 3);
    typeComboBox->addItem (TRANS("Fuzz"), 4);
    typeComboBox->addItem (TRANS("Crusher"), 5);
    typeComboBox->addListener (this);

    addAndMakeVisible (drySlider = new Slider ("new slider"));
    drySlider->setRange (0, 100, 1);
    drySlider->setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    drySlider->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    drySlider->setColour (Slider::backgroundColourId, Colour (0x00fd7004));
    drySlider->setColour (Slider::rotarySliderFillColourId, Colour (0x7fff0000));
    drySlider->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66000000));
    drySlider->setColour (Slider::textBoxTextColourId, Colours::white);
    drySlider->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    drySlider->setColour (Slider::textBoxOutlineColourId, Colour (0x00808080));
    drySlider->addListener (this);

    addAndMakeVisible (wetSlider = new Slider ("new slider"));
    wetSlider->setRange (0, 100, 1);
    wetSlider->setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    wetSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    wetSlider->setColour (Slider::backgroundColourId, Colour (0x00fd7004));
    wetSlider->setColour (Slider::rotarySliderFillColourId, Colour (0x7fff0000));
    wetSlider->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66000000));
    wetSlider->setColour (Slider::textBoxTextColourId, Colours::white);
    wetSlider->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    wetSlider->setColour (Slider::textBoxOutlineColourId, Colour (0x00808080));
    wetSlider->addListener (this);

    addAndMakeVisible (feedbackSlider = new Slider ("new slider"));
    feedbackSlider->setRange (0, 100, 1);
    feedbackSlider->setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    feedbackSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    feedbackSlider->setColour (Slider::backgroundColourId, Colour (0x00fd7004));
    feedbackSlider->setColour (Slider::rotarySliderFillColourId, Colour (0x7fff0000));
    feedbackSlider->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66000000));
    feedbackSlider->setColour (Slider::textBoxTextColourId, Colours::white);
    feedbackSlider->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    feedbackSlider->setColour (Slider::textBoxOutlineColourId, Colour (0x00808080));
    feedbackSlider->addListener (this);

    addAndMakeVisible (dryLabel = new Label ("new label",
                                             TRANS("Dry Level")));
    dryLabel->setFont (Font (13.00f, Font::plain));
    dryLabel->setJustificationType (Justification::centred);
    dryLabel->setEditable (false, false, false);
    dryLabel->setColour (Label::textColourId, Colours::white);
    dryLabel->setColour (TextEditor::textColourId, Colours::black);
    dryLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (wetLabel = new Label ("new label",
                                             TRANS("Wet Level")));
    wetLabel->setFont (Font (13.00f, Font::plain));
    wetLabel->setJustificationType (Justification::centred);
    wetLabel->setEditable (false, false, false);
    wetLabel->setColour (Label::textColourId, Colours::white);
    wetLabel->setColour (TextEditor::textColourId, Colours::black);
    wetLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (feedbackLabel = new Label ("new label",
                                                  TRANS("Feedback")));
    feedbackLabel->setFont (Font (13.00f, Font::plain));
    feedbackLabel->setJustificationType (Justification::centred);
    feedbackLabel->setEditable (false, false, false);
    feedbackLabel->setColour (Label::textColourId, Colours::white);
    feedbackLabel->setColour (TextEditor::textColourId, Colours::black);
    feedbackLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (delaySlider = new Slider ("new slider"));
    delaySlider->setRange (0, 2, 0.01);
    delaySlider->setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    delaySlider->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    delaySlider->setColour (Slider::backgroundColourId, Colour (0x00fd7004));
    delaySlider->setColour (Slider::rotarySliderFillColourId, Colour (0x7fff0000));
    delaySlider->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66000000));
    delaySlider->setColour (Slider::textBoxTextColourId, Colours::white);
    delaySlider->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    delaySlider->setColour (Slider::textBoxOutlineColourId, Colour (0x00808080));
    delaySlider->addListener (this);

    addAndMakeVisible (delayLabel = new Label ("new label",
                                               TRANS("Delay (secs)")));
    delayLabel->setFont (Font (13.00f, Font::plain));
    delayLabel->setJustificationType (Justification::centred);
    delayLabel->setEditable (false, false, false);
    delayLabel->setColour (Label::textColourId, Colours::white);
    delayLabel->setColour (TextEditor::textColourId, Colours::black);
    delayLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (outputSlider = new Slider ("new slider"));
    outputSlider->setRange (-24, 0, 0.01);
    outputSlider->setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    outputSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    outputSlider->setColour (Slider::rotarySliderFillColourId, Colour (0x7fff0000));
    outputSlider->setColour (Slider::textBoxTextColourId, Colours::white);
    outputSlider->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    outputSlider->setColour (Slider::textBoxOutlineColourId, Colour (0x00808080));
    outputSlider->addListener (this);

    addAndMakeVisible (gainLabel = new Label ("new label",
                                              TRANS("Gain (dB)")));
    gainLabel->setFont (Font (13.00f, Font::plain));
    gainLabel->setJustificationType (Justification::centred);
    gainLabel->setEditable (false, false, false);
    gainLabel->setColour (Label::textColourId, Colours::white);
    gainLabel->setColour (TextEditor::textColourId, Colours::black);
    gainLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (gainLabel2 = new Label ("new label",
                                               TRANS("Output (dB)")));
    gainLabel2->setFont (Font (13.00f, Font::plain));
    gainLabel2->setJustificationType (Justification::centred);
    gainLabel2->setEditable (false, false, false);
    gainLabel2->setColour (Label::textColourId, Colours::white);
    gainLabel2->setColour (TextEditor::textColourId, Colours::black);
    gainLabel2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (lowpassSlider = new Slider ("new slider"));
    lowpassSlider->setRange (1000, 20000, 25);
    lowpassSlider->setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    lowpassSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    lowpassSlider->setColour (Slider::rotarySliderFillColourId, Colour (0x7fff0000));
    lowpassSlider->setColour (Slider::textBoxTextColourId, Colours::white);
    lowpassSlider->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    lowpassSlider->setColour (Slider::textBoxOutlineColourId, Colour (0x00808080));
    lowpassSlider->addListener (this);

    addAndMakeVisible (highcutLabel = new Label ("new label",
                                                 TRANS("High Cut (Hz)")));
    highcutLabel->setFont (Font (13.00f, Font::plain));
    highcutLabel->setJustificationType (Justification::centred);
    highcutLabel->setEditable (false, false, false);
    highcutLabel->setColour (Label::textColourId, Colours::white);
    highcutLabel->setColour (TextEditor::textColourId, Colours::black);
    highcutLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label = new Label ("new label",
                                          TRANS("Delay")));
    label->setFont (Font ("Avenir", 35.00f, Font::plain));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label2 = new Label ("new label",
                                           TRANS("Distortion")));
    label2->setFont (Font ("Avenir", 35.00f, Font::plain));
    label2->setJustificationType (Justification::centredLeft);
    label2->setEditable (false, false, false);
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label3 = new Label ("new label",
                                           TRANS("Filter")));
    label3->setFont (Font ("Avenir", 35.00f, Font::plain));
    label3->setJustificationType (Justification::centredRight);
    label3->setEditable (false, false, false);
    label3->setColour (TextEditor::textColourId, Colours::black);
    label3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (highpassSlider = new Slider ("new slider"));
    highpassSlider->setRange (20, 1000, 10);
    highpassSlider->setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    highpassSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    highpassSlider->setColour (Slider::rotarySliderFillColourId, Colour (0x7fff0000));
    highpassSlider->setColour (Slider::textBoxTextColourId, Colours::white);
    highpassSlider->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    highpassSlider->setColour (Slider::textBoxOutlineColourId, Colour (0x00808080));
    highpassSlider->addListener (this);

    addAndMakeVisible (lowcutLabel = new Label ("new label",
                                                TRANS("Low Cut (Hz)")));
    lowcutLabel->setFont (Font (13.00f, Font::plain));
    lowcutLabel->setJustificationType (Justification::centred);
    lowcutLabel->setEditable (false, false, false);
    lowcutLabel->setColour (Label::textColourId, Colours::white);
    lowcutLabel->setColour (TextEditor::textColourId, Colours::black);
    lowcutLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (soloButton = new TextButton ("on off button"));
    soloButton->setButtonText (TRANS("Solo"));
    soloButton->addListener (this);
    soloButton->setColour (TextButton::buttonColourId, Colour (0xffad8585));
    soloButton->setColour (TextButton::buttonOnColourId, Colour (0xff81e40c));

    addAndMakeVisible (bypassButton2 = new TextButton ("on off button"));
    bypassButton2->setButtonText (TRANS("Bypass"));
    bypassButton2->addListener (this);
    bypassButton2->setColour (TextButton::buttonColourId, Colour (0xffad8585));
    bypassButton2->setColour (TextButton::buttonOnColourId, Colour (0xffe4610c));

    addAndMakeVisible (gainLabel3 = new Label ("new label",
                                               TRANS("Type")));
    gainLabel3->setFont (Font (13.00f, Font::plain));
    gainLabel3->setJustificationType (Justification::centredLeft);
    gainLabel3->setEditable (false, false, false);
    gainLabel3->setColour (Label::textColourId, Colours::white);
    gainLabel3->setColour (TextEditor::textColourId, Colours::black);
    gainLabel3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
    addAndMakeVisible (resizer = new ResizableCornerComponent (this, &resizeLimits));
    resizeLimits.setSizeLimits (150, 150, 850, 290);
    //[/UserPreSize]

    setSize (400, 400);


    //[Constructor] You can add your own custom stuff here..
	bypassButton->setClickingTogglesState(true);
	soloButton->setClickingTogglesState(true);
	bypassButton2->setClickingTogglesState(true);
	UpdateInterfaceValues();

	//************************************ SET LOOKANDFEEL **********************************
//	if( customLookAndFeel == NULL )
//	{
//		customLookAndFeel = new LookAndFeelCustom();
//		LookAndFeel::setDefaultLookAndFeel (/*&*/customLookAndFeel);
//	}

	//***************************************************************************************

    startTimer (50);

    //[/Constructor]
}

GhostFuzzAudioProcessorEditor::~GhostFuzzAudioProcessorEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    bypassButton = nullptr;
    gainSlider = nullptr;
    typeComboBox = nullptr;
    drySlider = nullptr;
    wetSlider = nullptr;
    feedbackSlider = nullptr;
    dryLabel = nullptr;
    wetLabel = nullptr;
    feedbackLabel = nullptr;
    delaySlider = nullptr;
    delayLabel = nullptr;
    outputSlider = nullptr;
    gainLabel = nullptr;
    gainLabel2 = nullptr;
    lowpassSlider = nullptr;
    highcutLabel = nullptr;
    label = nullptr;
    label2 = nullptr;
    label3 = nullptr;
    highpassSlider = nullptr;
    lowcutLabel = nullptr;
    soloButton = nullptr;
    bypassButton2 = nullptr;
    gainLabel3 = nullptr;


    //[Destructor]. You can add your own custom destruction code here..

    //[/Destructor]
}

//==============================================================================
void GhostFuzzAudioProcessorEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff588cc8));

    g.setColour (Colours::black);
    g.fillRect (290, 160, 1, 230);

    g.setColour (Colours::black);
    g.fillRect (10, 140, 380, 1);

    //[UserPaint] Add your own custom painting code here..

    //[/UserPaint]
}

void GhostFuzzAudioProcessorEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    bypassButton->setBounds (205, 365, 60, 20);
    gainSlider->setBounds (10, 290, 80, 80);
    typeComboBox->setBounds (20, 230, 140, 25);
    drySlider->setBounds (110, 40, 80, 80);
    wetSlider->setBounds (210, 40, 80, 80);
    feedbackSlider->setBounds (310, 40, 80, 80);
    dryLabel->setBounds (100, 110, 100, 30);
    wetLabel->setBounds (200, 110, 100, 30);
    feedbackLabel->setBounds (300, 110, 100, 30);
    delaySlider->setBounds (10, 40, 80, 80);
    delayLabel->setBounds (0, 110, 100, 30);
    outputSlider->setBounds (110, 290, 80, 80);
    gainLabel->setBounds (0, 360, 100, 30);
    gainLabel2->setBounds (100, 360, 100, 30);
    lowpassSlider->setBounds (310, 270, 70, 70);
    highcutLabel->setBounds (295, 330, 100, 30);
    label->setBounds (10, 10, 150, 24);
    label2->setBounds (10, 155, 150, 24);
    label3->setBounds (300, 155, 80, 24);
    highpassSlider->setBounds (310, 185, 70, 70);
    lowcutLabel->setBounds (295, 245, 100, 30);
    soloButton->setBounds (205, 230, 60, 26);
    bypassButton2->setBounds (315, 365, 60, 20);
    gainLabel3->setBounds (15, 200, 100, 30);
    //[UserResized] Add your own custom resize handling here..
    getProcessor()->_lastUIWidth = getWidth();
    getProcessor()->_lastUIHeight = getHeight();
    //[/UserResized]
}

void GhostFuzzAudioProcessorEditor::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]

    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == bypassButton)
    {
        //[UserButtonCode_bypassButton] -- add your button handler code here..
        getProcessor()->_distortionBypass = bypassButton->getToggleState();
        //[/UserButtonCode_bypassButton]
    }
    else if (buttonThatWasClicked == soloButton)
    {
        //[UserButtonCode_soloButton] -- add your button handler code here..
        getProcessor()->_distortionSolo = soloButton->getToggleState();
        //[/UserButtonCode_soloButton]
    }
    else if (buttonThatWasClicked == bypassButton2)
    {
        //[UserButtonCode_bypassButton2] -- add your button handler code here..
        getProcessor()->_filterBypass = bypassButton2->getToggleState();
        //[/UserButtonCode_bypassButton2]
    }

    //[UserbuttonClicked_Post]
	UpdateInterfaceValues();
    //[/UserbuttonClicked_Post]
}

void GhostFuzzAudioProcessorEditor::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    GhostFuzzAudioProcessor* ourProcessor = getProcessor();
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == gainSlider)
    {
        //[UserSliderCode_gainSlider] -- add your slider handling code here..
         ourProcessor->SetGainIndB(gainSlider->getValue());
        //[/UserSliderCode_gainSlider]
    }
    else if (sliderThatWasMoved == drySlider)
    {
        //[UserSliderCode_drySlider] -- add your slider handling code here..
         ourProcessor->SetDryMix(drySlider->getValue());
        //[/UserSliderCode_drySlider]
    }
    else if (sliderThatWasMoved == wetSlider)
    {
        //[UserSliderCode_wetSlider] -- add your slider handling code here..
         ourProcessor->SetWetMix(wetSlider->getValue());
        //[/UserSliderCode_wetSlider]
    }
    else if (sliderThatWasMoved == feedbackSlider)
    {
        //[UserSliderCode_feedbackSlider] -- add your slider handling code here..
        ourProcessor->SetFeedback(feedbackSlider->getValue());
        //[/UserSliderCode_feedbackSlider]
    }
    else if (sliderThatWasMoved == delaySlider)
    {
        //[UserSliderCode_delaySlider] -- add your slider handling code here..
        ourProcessor->SetDelay((float)delaySlider->getValue());
        //[/UserSliderCode_delaySlider]
    }
    else if (sliderThatWasMoved == outputSlider)
    {
        //[UserSliderCode_outputSlider] -- add your slider handling code here..
        ourProcessor->SetOutputIndB((float)outputSlider->getValue());
        //[/UserSliderCode_outputSlider]
    }
    else if (sliderThatWasMoved == lowpassSlider)
    {
        //[UserSliderCode_lowpassSlider] -- add your slider handling code here..
        ourProcessor->SetHighCutoff((float)lowpassSlider->getValue());
        //[/UserSliderCode_lowpassSlider]
    }
    else if (sliderThatWasMoved == highpassSlider)
    {
        //[UserSliderCode_highpassSlider] -- add your slider handling code here..
        ourProcessor->SetLowCutoff((float)highpassSlider->getValue());
        //[/UserSliderCode_highpassSlider]
    }

    //[UsersliderValueChanged_Post]
    UpdateInterfaceValues();
    //[/UsersliderValueChanged_Post]
}

void GhostFuzzAudioProcessorEditor::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    GhostFuzzAudioProcessor* ourProcessor = getProcessor();
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == typeComboBox)
    {
        //[UserComboBoxCode_typeComboBox] -- add your combo box handling code here..
        ourProcessor->SetType((GhostFuzzAudioProcessor::Types) typeComboBox->getSelectedItemIndex());
        //[/UserComboBoxCode_typeComboBox]
    }

    //[UsercomboBoxChanged_Post]
    UpdateInterfaceValues();
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void GhostFuzzAudioProcessorEditor::SetComboBoxActivity(ComboBox * comboBox, bool active)
{
	if (active){
		comboBox->setColour(ComboBox::backgroundColourId, Colours::white);
	}else{
		comboBox->setColour(ComboBox::backgroundColourId, Colours::grey);
	}
}

void GhostFuzzAudioProcessorEditor::SetSliderActivity(Slider * slider, bool active)
{
	if (active){
		slider->setColour (Slider::rotarySliderFillColourId, Colour (0xffff5c00));
		slider->addListener (this);
	}else{
		slider->setColour (Slider::rotarySliderFillColourId, Colours::grey);
		slider->removeListener(this);
	}
}

void GhostFuzzAudioProcessorEditor::UpdateInterfaceValues()
{
	GhostFuzzAudioProcessor* ourProcessor = getProcessor();

    // Update Sliders
    gainSlider	->setValue(ourProcessor->_gainIndB,dontSendNotification);
    drySlider	->setValue(ourProcessor->dryMix_,dontSendNotification);
    wetSlider	->setValue(ourProcessor->wetMix_,dontSendNotification);
    feedbackSlider	->setValue(ourProcessor->feedback_,dontSendNotification);
    delaySlider	->setValue(ourProcessor->delayLength_,dontSendNotification);
    outputSlider	->setValue(ourProcessor->_outputIndB,dontSendNotification);
    lowpassSlider	->setValue(ourProcessor->_highCutoff,dontSendNotification);
    highpassSlider	->setValue(ourProcessor->_lowCutoff,dontSendNotification);
    // Update ComboBox
    typeComboBox->setItemEnabled(ourProcessor->GetType(), true);
}

// This timer periodically checks whether any of the parameters have changed...
void GhostFuzzAudioProcessorEditor::timerCallback()
{
    // Display the ON/OFF button in its correct state
	if (bypassButton->getToggleState()) bypassButton->setToggleState(true, dontSendNotification);
	else bypassButton->setToggleState(false, dontSendNotification);
    if (soloButton->getToggleState()) soloButton->setToggleState(true, dontSendNotification);
	else soloButton->setToggleState(false, dontSendNotification);
	if (bypassButton2->getToggleState()) bypassButton2->setToggleState(true, dontSendNotification);
	else bypassButton2->setToggleState(false, dontSendNotification);



}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="GhostFuzzAudioProcessorEditor"
                 componentName="" parentClasses="public AudioProcessorEditor, public Timer"
                 constructorParams="GhostFuzzAudioProcessor* ownerFilter" variableInitialisers="AudioProcessorEditor (ownerFilter)"
                 snapPixels="10" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="400" initialHeight="400">
  <BACKGROUND backgroundColour="ff588cc8">
    <RECT pos="290 160 1 230" fill="solid: ff000000" hasStroke="0"/>
    <RECT pos="10 140 380 1" fill="solid: ff000000" hasStroke="0"/>
  </BACKGROUND>
  <TEXTBUTTON name="on off button" id="85bb206557e8f33d" memberName="bypassButton"
              virtualName="" explicitFocusOrder="0" pos="205 365 60 20" bgColOff="ffad8585"
              bgColOn="ffe4610c" buttonText="Bypass" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <SLIDER name="new slider" id="b7cd5ae6d0a3bfc6" memberName="gainSlider"
          virtualName="" explicitFocusOrder="0" pos="10 290 80 80" rotarysliderfill="7fff0000"
          textboxtext="ffffffff" textboxbkgd="ffffff" textboxoutline="808080"
          min="0" max="24" int="0.010000000000000000208" style="RotaryHorizontalVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <COMBOBOX name="new combo box" id="c80cc28cc68984e4" memberName="typeComboBox"
            virtualName="" explicitFocusOrder="0" pos="20 230 140 25" editable="0"
            layout="33" items="Valve&#10;Overdrive&#10;Clipping&#10;Fuzz&#10;Crusher"
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <SLIDER name="new slider" id="146ca47eadbe9069" memberName="drySlider"
          virtualName="" explicitFocusOrder="0" pos="110 40 80 80" bkgcol="fd7004"
          rotarysliderfill="7fff0000" rotaryslideroutline="66000000" textboxtext="ffffffff"
          textboxbkgd="ffffff" textboxoutline="808080" min="0" max="100"
          int="1" style="RotaryHorizontalVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <SLIDER name="new slider" id="d87d7c84215b6973" memberName="wetSlider"
          virtualName="" explicitFocusOrder="0" pos="210 40 80 80" bkgcol="fd7004"
          rotarysliderfill="7fff0000" rotaryslideroutline="66000000" textboxtext="ffffffff"
          textboxbkgd="ffffff" textboxoutline="808080" min="0" max="100"
          int="1" style="RotaryHorizontalVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <SLIDER name="new slider" id="2dde832890549706" memberName="feedbackSlider"
          virtualName="" explicitFocusOrder="0" pos="310 40 80 80" bkgcol="fd7004"
          rotarysliderfill="7fff0000" rotaryslideroutline="66000000" textboxtext="ffffffff"
          textboxbkgd="ffffff" textboxoutline="808080" min="0" max="100"
          int="1" style="RotaryHorizontalVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <LABEL name="new label" id="99a81053df7e7aae" memberName="dryLabel"
         virtualName="" explicitFocusOrder="0" pos="100 110 100 30" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Dry Level" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="13" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="8a17bb72545dbfde" memberName="wetLabel"
         virtualName="" explicitFocusOrder="0" pos="200 110 100 30" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Wet Level" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="13" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="1c5c9e0a9557605" memberName="feedbackLabel"
         virtualName="" explicitFocusOrder="0" pos="300 110 100 30" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Feedback" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="13" bold="0" italic="0" justification="36"/>
  <SLIDER name="new slider" id="e9018dd58f0c349e" memberName="delaySlider"
          virtualName="" explicitFocusOrder="0" pos="10 40 80 80" bkgcol="fd7004"
          rotarysliderfill="7fff0000" rotaryslideroutline="66000000" textboxtext="ffffffff"
          textboxbkgd="ffffff" textboxoutline="808080" min="0" max="2"
          int="0.010000000000000000208" style="RotaryHorizontalVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <LABEL name="new label" id="8b94018d3cc2e3c2" memberName="delayLabel"
         virtualName="" explicitFocusOrder="0" pos="0 110 100 30" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Delay (secs)" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="13" bold="0" italic="0" justification="36"/>
  <SLIDER name="new slider" id="166c6a7443c11524" memberName="outputSlider"
          virtualName="" explicitFocusOrder="0" pos="110 290 80 80" rotarysliderfill="7fff0000"
          textboxtext="ffffffff" textboxbkgd="ffffff" textboxoutline="808080"
          min="-24" max="0" int="0.010000000000000000208" style="RotaryHorizontalVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <LABEL name="new label" id="256edc96edc5d272" memberName="gainLabel"
         virtualName="" explicitFocusOrder="0" pos="0 360 100 30" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Gain (dB)" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="13" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="57e8403b4d595d84" memberName="gainLabel2"
         virtualName="" explicitFocusOrder="0" pos="100 360 100 30" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Output (dB)" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="13" bold="0" italic="0" justification="36"/>
  <SLIDER name="new slider" id="a102875879b86b2" memberName="lowpassSlider"
          virtualName="" explicitFocusOrder="0" pos="310 270 70 70" rotarysliderfill="7fff0000"
          textboxtext="ffffffff" textboxbkgd="ffffff" textboxoutline="808080"
          min="1000" max="20000" int="25" style="RotaryHorizontalVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <LABEL name="new label" id="d22d32ce64b8194c" memberName="highcutLabel"
         virtualName="" explicitFocusOrder="0" pos="295 330 100 30" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="High Cut (Hz)" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="13" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="c10564dc49b34c1f" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="10 10 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Delay" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Avenir" fontsize="35" bold="0"
         italic="0" justification="33"/>
  <LABEL name="new label" id="7c168c911f8ee1d5" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="10 155 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Distortion" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Avenir" fontsize="35" bold="0"
         italic="0" justification="33"/>
  <LABEL name="new label" id="762282ffe2ebaf29" memberName="label3" virtualName=""
         explicitFocusOrder="0" pos="300 155 80 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Filter" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Avenir" fontsize="35" bold="0"
         italic="0" justification="34"/>
  <SLIDER name="new slider" id="9cb82b99f8406d03" memberName="highpassSlider"
          virtualName="" explicitFocusOrder="0" pos="310 185 70 70" rotarysliderfill="7fff0000"
          textboxtext="ffffffff" textboxbkgd="ffffff" textboxoutline="808080"
          min="20" max="1000" int="10" style="RotaryHorizontalVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <LABEL name="new label" id="8e76d4bb3dee6602" memberName="lowcutLabel"
         virtualName="" explicitFocusOrder="0" pos="295 245 100 30" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Low Cut (Hz)" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="13" bold="0" italic="0" justification="36"/>
  <TEXTBUTTON name="on off button" id="15b96f4723c190f3" memberName="soloButton"
              virtualName="" explicitFocusOrder="0" pos="205 230 60 26" bgColOff="ffad8585"
              bgColOn="ff81e40c" buttonText="Solo" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="on off button" id="3f2170a2f2301b07" memberName="bypassButton2"
              virtualName="" explicitFocusOrder="0" pos="315 365 60 20" bgColOff="ffad8585"
              bgColOn="ffe4610c" buttonText="Bypass" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <LABEL name="new label" id="42be6ea078208156" memberName="gainLabel3"
         virtualName="" explicitFocusOrder="0" pos="15 200 100 30" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Type" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="13" bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
