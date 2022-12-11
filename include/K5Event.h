#ifndef __K5Event__
#define __K5Event__

#include "TDecompSVD.h"
#include "TClonesArray.h"
#include "TRefArray.h"
#include "TVector3.h"
#include "TVectorD.h"



enum ENum { kNumPad =6, kNumColumn =18, kNumRow =18, kNumLayer =30 };
    //    enum EBeam{_02, _04, _10, _20, _30, _45, _al};


class K5Hit : public TObject {
    Double_t             fEnergy;
    Int_t                fCellNumber;

public:
    K5Hit() { ; }
    K5Hit(Int_t column, Int_t row, Int_t layer, Double_t energy);
    K5Hit(Int_t index, Double_t energy);
    virtual             ~K5Hit() { ; }

    void                 Code(Int_t column, Int_t row, Int_t layer, Int_t&cellnumber);
    void                 Decode(Int_t&column, Int_t&row, Int_t&layer, Int_t cellnumber = -1);
    Int_t                GetCellNumber() { return fCellNumber; }
    Int_t                GetPadsInLayer() { return kNumRow * kNumColumn; }
    Int_t                GetLayer(Int_t cellnumber = -1);
    Int_t                GetRow(Int_t cellnumber);
    Int_t                GetColumn(Int_t cellnumber);
    Double_t             GetEnergy() { return fEnergy; }


    ClassDef(K5Hit,1);  //Calorimeter hit 
};


class K5Track : public TObject {

private:
    Double_t             fA;   
    Double_t             fB;
    Double_t             fC;
    Double_t             fD;
    Double_t             fX0;//!
    Double_t             fY0;//!
    Double_t             fZ0;//!
    Double_t             fX1;//!
    Double_t             fY1;//!
    Double_t             fZ1;//!
    Bool_t               fIsCalculated;
    Bool_t               CheckPoints();
public:
    K5Track();
    K5Track(Double_t a, Double_t b, Double_t c, Double_t d);
    K5Track(Double_t x0, Double_t y0, Double_t z0,Double_t x1, Double_t y1,Double_t z1);
    virtual             ~K5Track() { ; }
    virtual void         Print(); 

    void                 Reset();
    void                 SetABCD(Double_t a, Double_t b, Double_t c, Double_t d);
    void                 SetX0X1(Double_t x0, Double_t x1);
    void                 SetY0Y1(Double_t y0, Double_t y1);
    void                 SetZ0Z1(Double_t z0, Double_t z1);
    void                 CalculateTrack();

    Bool_t               IsCalculated() { return fIsCalculated; }

    Double_t             GetA() { return fA; }
    Double_t             GetB() { return fB; }
    Double_t             GetC() { return fC; }
    Double_t             GetD() { return fD; }

    TVector3            *NewVectorAtZ(Double_t z);
    TVector3            *GetDirection();

    ClassDef(K5Track,1);  //A track segment
};



class K5Event : public TObject {

private:
    TVector3             fVertex;      //!      //vertex coordinates
    Int_t                fNtrack;            //Number of tracks
    Int_t                fNhit;             //Number of hits
    TClonesArray        *fTracks;            //->array with tracks
    TClonesArray        *fHits;            //->array with hits
    static TClonesArray *fgTracks;
    static TClonesArray *fgHits;

public:
    K5Event();
    virtual             ~K5Event();

    Bool_t               fBeamTrigger;
    Bool_t               fCherenkovTrigger;
    Bool_t               fIsMC;
    Int_t                fEventNumber;
    Int_t                fRunNumber;
    Double_t             fBeamEnergy;
    Double_t             fEnergy;  //!


    Bool_t               IsMC() { return fIsMC; }
    void                 SetEventRun(Int_t event = 0, Int_t run = 0);
    void                 Clear(Option_t *option = "");
    void                 Reset(Option_t *option = "");
    Int_t                GetNtrack() const { return fNtrack; }
    Int_t                GetNhit() const { return fNhit; }
    //    Double_t             fHitEnergy[kNumColumn][kNumRow][kNumLayer];  //obsolete
    //    EBeam         GetBeam() const;
    static TVectorD      LinearFit(Int_t nrPnts, Double_t*ax, Double_t*ay, Double_t*ae);

    K5Track             *AddTrack();
    K5Track             *AddTrack(Double_t x0, Double_t y0, Double_t z0, Double_t x1, Double_t y1, Double_t z1);
    K5Track             *AddTrack(Double_t a, Double_t b, Double_t c, Double_t d);
    K5Hit               *AddHit(Int_t column, Int_t row, Int_t layer, Double_t energy);
    K5Hit               *AddHit(Int_t index, Double_t energy);

    K5Track             *GetTrack(Int_t n = -1);
    K5Hit               *GetHit(Int_t n);
    ClassDef(K5Event, 3);  //Event structure
};



#endif




















