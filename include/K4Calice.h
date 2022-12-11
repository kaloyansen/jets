// -*- mode: c++ -*-
//____________________________________________________________________
//
// $Id$
// Author: kkrastev <kkrastev@>
// Update: 2009-11-30 20:35:19+0100
// Copyright: 2009 (C) kkrastev
//
#ifndef ROOT_K4Calice
	#define ROOT_K4Calice

#ifndef ROOT_TObject
	#include "TObject.h"
#endif

#include "TClass.h"
#include "TF1.h"
#include "TFile.h"
#include "TGraph.h"
#include "TH2F.h"
#include "TKey.h"
#include "TObjString.h"
#include "TProfile.h"
#include "TSystem.h"

class K4Calice : public TObject
{
private:
    void 	Initialize(Int_t, Int_t, Int_t, Int_t, Int_t);
    void 	Loop(TString);
    void 	Noise();
    void 	Correlation();
    void    	Synchronize();
    TH1*	Teleh2(TH1*);
    TH1*	Teleprofile(TH1*);

    Int_t	fRunNumber, fMinRunNumber, fMaxRunNumber;
    Int_t       fRunsPerBin, fGapFrom, fGapTo, fGapW;
    TString 	fRunTitle;
    TDirectory*	fInput;
    TDirectory*	fOutput;
    TFile*	fInputFile;
    TFile*	fOutputFile;

public:
    K4Calice();
    K4Calice(Int_t minRun, Int_t maxRun, Int_t gapfrom, Int_t gapto, Int_t runsperbin, TString option);
    /* option
       noise -> space uniformity per run
       h2 -> run dimension
       profile -> run profile
     */
    virtual	~K4Calice();

    ClassDef(K4Calice,0) //time vectorize
};

#endif
//____________________________________________________________________
//
// EOF
//
