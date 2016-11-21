# ofHzpiral

*** Work in Progress ***

Hzpiral using Open Frameworks for iOS and (soon to implement) Faust frameworks
Final Project for 256A

Hzpiral is a playable pitch-space in polar coordinates, with chroma corresponding to theta and pitch height corresponding to radius.  Planned Hzpiral features include polyphony, quantized pitch tuning based on multiple tuning systems, programmable chords, controllable synth and envelope parameters, and over-network control to MIDI and OSC compatible software synths.

Current version is modified from audioOutput example from iOS openframeworks examples.
Polar-coordinate pitch-space paradigm has been implemented for monophony. 
Required open frameworks addons: 
- ofxAssets (required for ofxKCTouchGui2),
- ofxfft (for visualization), 
- ofxKCTouchGui2 (multitouch),
- ofxNetwork (future communication to software synths), 
- ofxOsc (future communication to software synths)
(not yet added) - ofxMidi

Much more to come.
