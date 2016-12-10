//----------------------------------------------------------
//
// Code generated with Faust 0.9.81 (http://faust.grame.fr)
//----------------------------------------------------------

/* link with  */
#include <math.h>
#ifndef FAUSTPOWER
#define FAUSTPOWER
#include <cmath>
template <int N> inline int faustpower(int x)              { return faustpower<N/2>(x) * faustpower<N-N/2>(x); } 
template <> 	 inline int faustpower<0>(int x)            { return 1; }
template <> 	 inline int faustpower<1>(int x)            { return x; }
template <> 	 inline int faustpower<2>(int x)            { return x*x; }
template <int N> inline float faustpower(float x)            { return faustpower<N/2>(x) * faustpower<N-N/2>(x); } 
template <> 	 inline float faustpower<0>(float x)          { return 1; }
template <> 	 inline float faustpower<1>(float x)          { return x; }
template <> 	 inline float faustpower<2>(float x)          { return x*x; }
#endif
#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif  


#ifndef FAUSTCLASS 
#define FAUSTCLASS HzpVoice
#endif

class HzpVoice : public dsp {
  private:
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT 	fslider3;
	int 	iVec0[2];
	FAUSTFLOAT 	fslider4;
	FAUSTFLOAT 	fcheckbox0;
	float 	fRec1[2];
	float 	fConst0;
	float 	fConst1;
	FAUSTFLOAT 	fslider5;
	float 	fRec2[2];
	float 	fRec3[2];
	FAUSTFLOAT 	fslider6;
	float 	fRec4[2];
	FAUSTFLOAT 	fcheckbox1;
	FAUSTFLOAT 	fslider7;
	float 	fRec5[2];
	FAUSTFLOAT 	fslider8;
	FAUSTFLOAT 	fslider9;
	float 	fRec7[2];
	float 	fConst2;
	FAUSTFLOAT 	fslider10;
	float 	fRec6[2];
	float 	fConst3;
	FAUSTFLOAT 	fslider11;
	FAUSTFLOAT 	fslider12;
	float 	fRec8[2];
	float 	fConst4;
	float 	fConst5;
	float 	fConst6;
	float 	fRec10[2];
	float 	fVec1[2];
	int 	IOTA;
	float 	fVec2[4096];
	float 	fRec9[2];
	FAUSTFLOAT 	fslider13;
	FAUSTFLOAT 	fslider14;
	float 	fRec11[2];
	float 	fRec13[2];
	float 	fVec3[2];
	float 	fVec4[4096];
	float 	fRec12[2];
	float 	fRec14[2];
	float 	fRec15[2];
	float 	fRec16[2];
	float 	fRec17[2];
	float 	fConst7;
	float 	fRec18[2];
	float 	fRec20[2];
	float 	fConst8;
	FAUSTFLOAT 	fslider15;
	float 	fRec22[2];
	FAUSTFLOAT 	fslider16;
	float 	fRec0[3];
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) 	{ 
		m->declare("basic.lib/name", "Faust Basic Element Library");
		m->declare("basic.lib/version", "0.0");
		m->declare("oscillator.lib/name", "Faust Oscillator Library");
		m->declare("oscillator.lib/version", "0.0");
		m->declare("filter.lib/name", "Faust Filter Library");
		m->declare("filter.lib/version", "2.0");
		m->declare("signal.lib/name", "Faust Signal Routing Library");
		m->declare("signal.lib/version", "0.0");
		m->declare("math.lib/name", "Faust Math Library");
		m->declare("math.lib/version", "2.0");
		m->declare("math.lib/author", "GRAME");
		m->declare("math.lib/copyright", "GRAME");
		m->declare("math.lib/license", "LGPL with exception");
		m->declare("envelope.lib/name", "Faust Envelope Library");
		m->declare("envelope.lib/version", "0.0");
		m->declare("envelope.lib/author", "GRAME");
		m->declare("envelope.lib/copyright", "GRAME");
		m->declare("envelope.lib/license", "LGPL with exception");
	}

	virtual int getNumInputs() 	{ return 0; }
	virtual int getNumOutputs() 	{ return 2; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceInit(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fslider0 = 1.0f;
		fslider1 = 0.0f;
		fslider2 = 0.0f;
		fslider3 = 0.0f;
		for (int i=0; i<2; i++) iVec0[i] = 0;
		fslider4 = 0.5f;
		fcheckbox0 = 0.0;
		for (int i=0; i<2; i++) fRec1[i] = 0;
		fConst0 = min(1.92e+05f, max(1.0f, (float)fSamplingFreq));
		fConst1 = (6.2831855f / fConst0);
		fslider5 = 6.0f;
		for (int i=0; i<2; i++) fRec2[i] = 0;
		for (int i=0; i<2; i++) fRec3[i] = 0;
		fslider6 = 0.5f;
		for (int i=0; i<2; i++) fRec4[i] = 0;
		fcheckbox1 = 0.0;
		fslider7 = 0.5f;
		for (int i=0; i<2; i++) fRec5[i] = 0;
		fslider8 = 0.1f;
		fslider9 = 0.1f;
		for (int i=0; i<2; i++) fRec7[i] = 0;
		fConst2 = (1.0f / fConst0);
		fslider10 = 75.0f;
		for (int i=0; i<2; i++) fRec6[i] = 0;
		fConst3 = (4.0f / fConst0);
		fslider11 = 4.4e+02f;
		fslider12 = 0.5f;
		for (int i=0; i<2; i++) fRec8[i] = 0;
		fConst4 = float(fConst0);
		fConst5 = (0.5f * fConst4);
		fConst6 = (0.25f * fConst4);
		for (int i=0; i<2; i++) fRec10[i] = 0;
		for (int i=0; i<2; i++) fVec1[i] = 0;
		IOTA = 0;
		for (int i=0; i<4096; i++) fVec2[i] = 0;
		for (int i=0; i<2; i++) fRec9[i] = 0;
		fslider13 = 4.4e+02f;
		fslider14 = 0.5f;
		for (int i=0; i<2; i++) fRec11[i] = 0;
		for (int i=0; i<2; i++) fRec13[i] = 0;
		for (int i=0; i<2; i++) fVec3[i] = 0;
		for (int i=0; i<4096; i++) fVec4[i] = 0;
		for (int i=0; i<2; i++) fRec12[i] = 0;
		for (int i=0; i<2; i++) fRec14[i] = 0;
		for (int i=0; i<2; i++) fRec15[i] = 0;
		for (int i=0; i<2; i++) fRec16[i] = 0;
		for (int i=0; i<2; i++) fRec17[i] = 0;
		fConst7 = (1.0f / fConst4);
		for (int i=0; i<2; i++) fRec18[i] = 0;
		for (int i=0; i<2; i++) fRec20[i] = 0;
		fConst8 = (3.1415927f / fConst0);
		fslider15 = 1e+04f;
		for (int i=0; i<2; i++) fRec22[i] = 0;
		fslider16 = 7.0f;
		for (int i=0; i<3; i++) fRec0[i] = 0;
	}
	virtual void init(int samplingFreq) {
		classInit(samplingFreq);
		instanceInit(samplingFreq);
	}
    
    //added virtual methods
    
    virtual void instanceConstants(int samplingRate) {}
    
    virtual void instanceResetUserInterface() {}
    
    virtual void instanceClear() {}
    
    //end added virtual methods
    
	virtual dsp* clone() {
		return new HzpVoice();
	}
	virtual int getSampleRate() {
		return fSamplingFreq;
	}
	virtual void buildUserInterface(UI* interface) {
		interface->openHorizontalBox("hzpVoice");
		interface->addVerticalSlider("Q", &fslider16, 7.0f, 1.0f, 2e+01f, 0.001f);
		interface->addVerticalSlider("att", &fslider8, 0.1f, 0.0f, 2.0f, 0.0001f);
		interface->addVerticalSlider("cutoff", &fslider15, 1e+04f, 2e+01f, 1e+04f, 0.01f);
		interface->addVerticalSlider("del", &fslider9, 0.1f, 0.0f, 2.0f, 0.0001f);
		interface->addVerticalSlider("freq", &fslider11, 4.4e+02f, 2e+01f, 2e+04f, 0.01f);
		interface->addVerticalSlider("freq2", &fslider13, 4.4e+02f, 2e+01f, 2e+04f, 0.01f);
		interface->addVerticalSlider("gain", &fslider6, 0.5f, 0.0f, 1.0f, 0.01f);
		interface->addCheckButton("gate", &fcheckbox1);
		interface->addVerticalSlider("rel", &fslider7, 0.5f, 0.0f, 4.0f, 0.0001f);
		interface->addVerticalSlider("sawMix", &fslider1, 0.0f, 0.0f, 1.0f, 0.001f);
		interface->addVerticalSlider("sineMix", &fslider0, 1.0f, 0.0f, 1.0f, 0.001f);
		interface->addVerticalSlider("squareMix", &fslider2, 0.0f, 0.0f, 1.0f, 0.001f);
		interface->addVerticalSlider("sus", &fslider10, 75.0f, 0.0f, 1e+02f, 0.1f);
		interface->addCheckButton("tremOn", &fcheckbox0);
		interface->addVerticalSlider("tremrate", &fslider5, 6.0f, 2.0f, 1e+01f, 0.001f);
		interface->addVerticalSlider("tremstr", &fslider4, 0.5f, 0.0f, 1.0f, 0.001f);
		interface->addVerticalSlider("triMix", &fslider3, 0.0f, 0.0f, 1.0f, 0.001f);
		interface->addVerticalSlider("vol1", &fslider12, 0.5f, 0.0f, 1.0f, 0.01f);
		interface->addVerticalSlider("vol2", &fslider14, 0.5f, 0.0f, 1.0f, 0.01f);
		interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		float 	fSlow0 = float(fslider0);
		float 	fSlow1 = float(fslider1);
		float 	fSlow2 = float(fslider2);
		float 	fSlow3 = float(fslider3);
		float 	fSlow4 = (1.0f / ((((fSlow0 + fSlow1) + fSlow2) + fSlow3) + 0.001f));
		float 	fSlow5 = float(fslider4);
		float 	fSlow6 = (0.001f * float(fcheckbox0));
		float 	fSlow7 = (fConst1 * float(fslider5));
		float 	fSlow8 = sinf(fSlow7);
		float 	fSlow9 = cosf(fSlow7);
		float 	fSlow10 = (0 - fSlow8);
		float 	fSlow11 = (0.001f * float(fslider6));
		float 	fSlow12 = float(fcheckbox1);
		int 	iSlow13 = (fSlow12 > 0);
		int 	iSlow14 = int((iSlow13 > 0));
		float 	fSlow15 = float(fslider7);
		float 	fSlow16 = (fConst0 * fSlow15);
		int 	iSlow17 = (1 - iSlow13);
		int 	iSlow18 = faustpower<2>(iSlow13);
		int 	iSlow19 = int(((fSlow12 == 0) > 0));
		float 	fSlow20 = float(fslider8);
		float 	fSlow21 = float(fslider9);
		float 	fSlow22 = (fConst0 * (fSlow20 + fSlow21));
		float 	fSlow23 = (fConst0 * fSlow20);
		float 	fSlow24 = (fConst2 / fSlow20);
		float 	fSlow25 = (0.01f * (fSlow12 * float(fslider10)));
		float 	fSlow26 = (fConst2 * ((fSlow25 - 1) / fSlow21));
		float 	fSlow27 = (fConst2 / fSlow15);
		float 	fSlow28 = (fConst3 * fSlow3);
		float 	fSlow29 = float(fslider11);
		float 	fSlow30 = (0.001f * float(fslider12));
		float 	fSlow31 = max(fSlow29, 23.44895f);
		float 	fSlow32 = max((float)0, min((float)2047, (fConst5 / fSlow31)));
		float 	fSlow33 = floorf(fSlow32);
		float 	fSlow34 = ((1 + fSlow33) - fSlow32);
		float 	fSlow35 = max(2e+01f, fabsf(fSlow31));
		float 	fSlow36 = (fConst6 / fSlow35);
		float 	fSlow37 = (fConst2 * fSlow35);
		int 	iSlow38 = int(fSlow32);
		float 	fSlow39 = (fSlow32 - fSlow33);
		int 	iSlow40 = int((1 + iSlow38));
		float 	fSlow41 = float(fslider13);
		float 	fSlow42 = (0.001f * float(fslider14));
		float 	fSlow43 = max(fSlow41, 23.44895f);
		float 	fSlow44 = max((float)0, min((float)2047, (fConst5 / fSlow43)));
		float 	fSlow45 = floorf(fSlow44);
		float 	fSlow46 = ((1 + fSlow45) - fSlow44);
		float 	fSlow47 = max(2e+01f, fabsf(fSlow43));
		float 	fSlow48 = (fConst6 / fSlow47);
		float 	fSlow49 = (fConst2 * fSlow47);
		int 	iSlow50 = int(fSlow44);
		float 	fSlow51 = (fSlow44 - fSlow45);
		int 	iSlow52 = int((1 + iSlow50));
		float 	fSlow53 = (fConst1 * fSlow29);
		float 	fSlow54 = sinf(fSlow53);
		float 	fSlow55 = cosf(fSlow53);
		float 	fSlow56 = (0 - fSlow54);
		float 	fSlow57 = (fConst1 * fSlow41);
		float 	fSlow58 = sinf(fSlow57);
		float 	fSlow59 = cosf(fSlow57);
		float 	fSlow60 = (0 - fSlow58);
		float 	fSlow61 = float(max(1e-07f, fabsf(fSlow29)));
		float 	fSlow62 = (fConst7 * fSlow61);
		float 	fSlow63 = (fSlow62 - 1);
		float 	fSlow64 = (1 - (fConst4 / fSlow61));
		float 	fSlow65 = float(max(1e-07f, fabsf(fSlow41)));
		float 	fSlow66 = (fConst7 * fSlow65);
		float 	fSlow67 = (fSlow66 - 1);
		float 	fSlow68 = (1 - (fConst4 / fSlow65));
		float 	fSlow69 = (0.001f * float(fslider15));
		float 	fSlow70 = (1.0f / float(fslider16));
		FAUSTFLOAT* output0 = output[0];
		FAUSTFLOAT* output1 = output[1];
		for (int i=0; i<count; i++) {
			iVec0[0] = 1;
			fRec1[0] = (fSlow6 + (0.999f * fRec1[1]));
			fRec2[0] = ((fSlow8 * fRec3[1]) + (fSlow9 * fRec2[1]));
			fRec3[0] = ((1 + ((fSlow9 * fRec3[1]) + (fSlow10 * fRec2[1]))) - iVec0[1]);
			fRec4[0] = (fSlow11 + (0.999f * fRec4[1]));
			fRec5[0] = ((iSlow14)?0:min(fSlow16, (1 + fRec5[1])));
			fRec7[0] = ((iSlow19)?0:min(fSlow22, (1 + fRec7[1])));
			int iTemp0 = int((fRec7[0] < fSlow23));
			fRec6[0] = ((iSlow17 * fRec6[1]) + (iSlow18 * ((iTemp0)?((int((fRec7[0] < 0)))?0:((iTemp0)?(fSlow24 * fRec7[0]):1)):((int((fRec7[0] < fSlow22)))?(1 + (fSlow26 * (fRec7[0] - fSlow23))):fSlow25))));
			float fTemp1 = ((int((fRec5[0] < 0)))?fRec6[0]:((int((fRec5[0] < fSlow16)))?(fRec6[0] + (fSlow27 * (fRec5[0] * (0 - fRec6[0])))):0));
			fRec8[0] = (fSlow30 + (0.999f * fRec8[1]));
			float fTemp2 = (fSlow37 + fRec10[1]);
			fRec10[0] = (fTemp2 - floorf(fTemp2));
			float fTemp3 = faustpower<2>(((2 * fRec10[0]) - 1));
			fVec1[0] = fTemp3;
			float fTemp4 = (fSlow36 * (iVec0[1] * (fVec1[0] - fVec1[1])));
			fVec2[IOTA&4095] = fTemp4;
			float fTemp5 = ((fSlow34 * fVec2[(IOTA-iSlow38)&4095]) + (fSlow39 * fVec2[(IOTA-iSlow40)&4095]));
			fRec9[0] = (0 - (fTemp5 - ((0.999f * fRec9[1]) + fVec2[IOTA&4095])));
			fRec11[0] = (fSlow42 + (0.999f * fRec11[1]));
			float fTemp6 = (fSlow49 + fRec13[1]);
			fRec13[0] = (fTemp6 - floorf(fTemp6));
			float fTemp7 = faustpower<2>(((2 * fRec13[0]) - 1));
			fVec3[0] = fTemp7;
			float fTemp8 = (fSlow48 * (iVec0[1] * (fVec3[0] - fVec3[1])));
			fVec4[IOTA&4095] = fTemp8;
			float fTemp9 = ((fSlow46 * fVec4[(IOTA-iSlow50)&4095]) + (fSlow51 * fVec4[(IOTA-iSlow52)&4095]));
			fRec12[0] = (0 - (fTemp9 - ((0.999f * fRec12[1]) + fVec4[IOTA&4095])));
			fRec14[0] = ((fSlow54 * fRec15[1]) + (fSlow55 * fRec14[1]));
			fRec15[0] = ((1 + ((fSlow55 * fRec15[1]) + (fSlow56 * fRec14[1]))) - iVec0[1]);
			fRec16[0] = ((fSlow58 * fRec17[1]) + (fSlow59 * fRec16[1]));
			fRec17[0] = ((1 + ((fSlow59 * fRec17[1]) + (fSlow60 * fRec16[1]))) - iVec0[1]);
			float fTemp10 = (fSlow63 + fRec18[1]);
			int iTemp11 = int((fTemp10 < 0));
			float fTemp12 = (fSlow62 + fRec18[1]);
			fRec18[0] = ((iTemp11)?fTemp12:fTemp10);
			float 	fRec19 = ((iTemp11)?fTemp12:(fSlow62 + (fRec18[1] + (fSlow64 * fTemp10))));
			float fTemp13 = (fSlow67 + fRec20[1]);
			int iTemp14 = int((fTemp13 < 0));
			float fTemp15 = (fSlow66 + fRec20[1]);
			fRec20[0] = ((iTemp14)?fTemp15:fTemp13);
			float 	fRec21 = ((iTemp14)?fTemp15:(fSlow66 + (fRec20[1] + (fSlow68 * fTemp13))));
			fRec22[0] = (fSlow69 + (0.999f * fRec22[1]));
			float fTemp16 = tanf((fConst8 * fRec22[0]));
			float fTemp17 = (1.0f / fTemp16);
			float fTemp18 = (1 + ((fSlow70 + fTemp17) / fTemp16));
			fRec0[0] = ((fSlow4 * ((((1 + (fSlow5 * (fRec1[0] * ((0.5f * (1.0f + fRec2[0])) - 1)))) * fRec4[0]) * fTemp1) * ((fSlow28 * ((fSlow29 * (fRec8[0] * fRec9[0])) + (fSlow41 * (fRec11[0] * fRec12[0])))) + (((fSlow0 * ((fRec14[0] * fRec8[0]) + (fRec16[0] * fRec11[0]))) + (fSlow1 * ((fRec8[0] * ((2 * fRec19) - 1)) + (fRec11[0] * ((2 * fRec21) - 1))))) + (fSlow2 * ((fRec8[0] * (0 - (fTemp5 - fVec2[IOTA&4095]))) + (fRec11[0] * (0 - (fTemp9 - fVec4[IOTA&4095]))))))))) - (((fRec0[2] * (1 + ((fTemp17 - fSlow70) / fTemp16))) + (2 * (fRec0[1] * (1 - (1.0f / faustpower<2>(fTemp16)))))) / fTemp18));
			output0[i] = (FAUSTFLOAT)((fRec0[0] + (fRec0[2] + (2.0f * fRec0[1]))) / fTemp18);
			output1[i] = (FAUSTFLOAT)fTemp1;
			// post processing
			fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
			fRec22[1] = fRec22[0];
			fRec20[1] = fRec20[0];
			fRec18[1] = fRec18[0];
			fRec17[1] = fRec17[0];
			fRec16[1] = fRec16[0];
			fRec15[1] = fRec15[0];
			fRec14[1] = fRec14[0];
			fRec12[1] = fRec12[0];
			fVec3[1] = fVec3[0];
			fRec13[1] = fRec13[0];
			fRec11[1] = fRec11[0];
			fRec9[1] = fRec9[0];
			IOTA = IOTA+1;
			fVec1[1] = fVec1[0];
			fRec10[1] = fRec10[0];
			fRec8[1] = fRec8[0];
			fRec6[1] = fRec6[0];
			fRec7[1] = fRec7[0];
			fRec5[1] = fRec5[0];
			fRec4[1] = fRec4[0];
			fRec3[1] = fRec3[0];
			fRec2[1] = fRec2[0];
			fRec1[1] = fRec1[0];
			iVec0[1] = iVec0[0];
		}
	}
};


