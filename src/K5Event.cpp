#include "K5Event.h"

ClassImp(K5Hit)
ClassImp(K5Track)
ClassImp(K5Event)
    
TClonesArray *K5Event::fgTracks = 0;
TClonesArray *K5Event::fgHits = 0;

// UInt_t K5Hit::fNumPad = 6;
// UInt_t K5Hit::fNumColumn = 18;
// UInt_t K5Hit::fNumRow = 18;
// UInt_t K5Hit::fNumLayer = 30;


K5Hit::K5Hit(Int_t column, Int_t row, Int_t layer, Double_t energy) {
    Code(column, row, layer, fCellNumber);
    fEnergy = energy;
}

K5Hit::K5Hit(Int_t index, Double_t energy) {
    fCellNumber = index;
    fEnergy = energy;
}

void K5Hit::Code(Int_t column, Int_t row, Int_t layer, Int_t&cellnumber) { 
    //    cellnumber = column + fNumColumn * row + fNumRow * fNumColumn * layer; }
    cellnumber = column + kNumColumn * row + kNumRow * kNumColumn * layer; }

Int_t K5Hit::GetLayer(Int_t cellnumber) { if (cellnumber < 0) cellnumber = fCellNumber; return cellnumber / GetPadsInLayer(); }
//Int_t K5Hit::GetRow(Int_t cellnumber) { return (cellnumber - GetPadsInLayer() * GetLayer(cellnumber)) / fNumRow; }
Int_t K5Hit::GetRow(Int_t cellnumber) { return (cellnumber - GetPadsInLayer() * GetLayer(cellnumber)) / kNumRow; }
//Int_t K5Hit::GetColumn(Int_t cellnumber) { return cellnumber - GetPadsInLayer() * GetLayer(cellnumber) - fNumColumn*GetRow(cellnumber); }
Int_t K5Hit::GetColumn(Int_t cellnumber) { return cellnumber - GetPadsInLayer() * GetLayer(cellnumber) - kNumColumn*GetRow(cellnumber); }

void K5Hit::Decode(Int_t&column, Int_t&row, Int_t&layer, Int_t cellnumber) {
    if (cellnumber < 0) 
	cellnumber = fCellNumber;
    column = GetColumn(cellnumber);
    row = GetRow(cellnumber);
    layer = GetLayer(cellnumber);
}


K5Track::K5Track() { Reset(); }
K5Track::K5Track(Double_t a, Double_t b, Double_t c, Double_t d) { SetABCD(a, b, c, d); }
K5Track::K5Track(Double_t x0, Double_t y0, Double_t z0, Double_t x1, Double_t y1, Double_t z1) { 
    fX0 = x0;
    fY0 = y0;
    fZ0 = z0;
    fX1 = x1;
    fY1 = y1;
    fZ1 = z1;
    CalculateTrack();
}

void K5Track::Reset() { fA = fB = fC = fD = fX0 = fY0 = fZ0 = fX1 = fY1 = fZ1 = 12345; fIsCalculated = kFALSE; }
void K5Track::SetABCD(Double_t a, Double_t b, Double_t c, Double_t d) { fA = a; fB = b; fC = c; fD = d; fIsCalculated = kTRUE; }
void K5Track::SetX0X1(Double_t x0, Double_t x1) { fX0 = x0; fX1 = x1; }
void K5Track::SetY0Y1(Double_t y0, Double_t y1) { fY0 = y0; fY1 = y1; }
void K5Track::SetZ0Z1(Double_t z0, Double_t z1) { fZ0 = z0; fZ1 = z1; }
void K5Track::Print() { Info("Print", "a = %f, b = %f, c = %f, d = %f", fA, fB, fC, fD); }
void K5Track::CalculateTrack()
{//x(z)=fA*z+fB, y(z)=fC*z+fD
    if (CheckPoints()) {
	fA=(fX0 - fX1) / (fZ0 - fZ1);
	fB=fX0 - fA * fZ0;
	fC=(fY0 - fY1) / (fZ0 - fZ1);
	fD=fY0 - fC * fZ0;
	fIsCalculated = kTRUE;
    } else fIsCalculated = kFALSE;
}

Bool_t K5Track::CheckPoints()
{
    if (fX0==12345. || fY0==12345. || fZ0==12345. || fX1==12345. || fY1==12345. || fZ1==12345. || fZ0==fZ1) {
	Error("CheckPoints",Form("Calculate track error %f %f %f %f %f %f",fX0, fY0, fZ0, fX1, fY1, fZ1));
	return kFALSE;
    } else return kTRUE;
}

TVector3*K5Track::GetDirection()
{
    TVector3*direction = new TVector3(0, 0, 0);
    if (fIsCalculated) direction->SetXYZ(fA / fC, fC / fA, (fA - fC) / (fA * fC));
    else Error("GetDirection", "The track has not been calculated");
    return direction;
}


TVector3*K5Track::NewVectorAtZ(Double_t z)
{
    Double_t x=fA * z + fB;
    Double_t y=fC * z + fD;
    TVector3*vec=new TVector3(x, y, z);
    return vec;
}



K5Event::K5Event()
{
    if (!fgTracks) fgTracks = new TClonesArray("K5Track", 10);
    if (!fgHits) fgHits = new TClonesArray("K5Hit", 10);
    fTracks = fgTracks;
    fHits = fgHits;
}

K5Event::~K5Event() { Reset(); }
/*
EBeam K5Evemt::GetBeam() const
{
    if (fBeamEnergy > 44. && fBeamEnergy < 46.) return _45;
    else if (*energyBeam > 29. && *energyBeam < 31.) return _30;
    else Warning("GetBeam", Form("beam energy = %f", fBeamEnergy));
}
*/
K5Track *K5Event::AddTrack()
{
    TClonesArray &tracks = *fTracks;
    K5Track *track = new(tracks[fNtrack++]) K5Track();
    return track;
}

K5Track*K5Event::AddTrack(Double_t x0, Double_t y0, Double_t z0, Double_t x1, Double_t y1, Double_t z1)
{
    TClonesArray &tracks = *fTracks;
    K5Track *track = new(tracks[fNtrack++]) K5Track(x0,y0,z0,x1,y1,z1);
    return track;
}

K5Track*K5Event::AddTrack(Double_t a, Double_t b, Double_t c, Double_t d)
{
    TClonesArray &tracks = *fTracks;
    K5Track *track = new(tracks[fNtrack++]) K5Track(a, b, c, d);
    return track;
}


K5Hit*K5Event::AddHit(Int_t column, Int_t row, Int_t layer, Double_t energy)
{
    TClonesArray &hits = *fHits;
    K5Hit*hit = new(hits[fNhit++]) K5Hit(column, row, layer, energy);
    return hit;
}

K5Hit*K5Event::AddHit(Int_t index, Double_t energy)
{
    TClonesArray &hits = *fHits;
    K5Hit*hit = new(hits[fNhit++]) K5Hit(index, energy);
    return hit;
}

K5Hit*K5Event::GetHit(Int_t n)
{
    K5Hit*hit = (K5Hit*)fHits->At(n);
    return hit;
}


K5Track*K5Event::GetTrack(Int_t n)
{
    if (n<0) n=fNtrack-1;
    K5Track*track=(K5Track*)fTracks->At(n);
    return track;
}


void K5Event::SetEventRun(Int_t event,Int_t run) { fEventNumber=event; fRunNumber=run; }

void K5Event::Clear(Option_t *option)
{
    fBeamEnergy = 0; 
    fIsMC = kFALSE;
    fNtrack = fNhit = 0;
    SetEventRun();
    fBeamTrigger=kFALSE;
    fCherenkovTrigger=kFALSE;
    fTracks->Clear(option);
    fHits->Clear(option);
    fEnergy = 0;
}

void K5Event::Reset(Option_t *) { delete fgTracks; fgTracks = 0; }




TVectorD K5Event::LinearFit(Int_t nrPnts, Double_t*ax, Double_t*ay, Double_t*ae)
{
    const Int_t nrVar = 2;
    TVectorD x, y, e; 
    x.Use(nrPnts, ax);
    y.Use(nrPnts, ay);
    e.Use(nrPnts, ae);

    TMatrixD A(nrPnts, nrVar);
    TMatrixDColumn(A, 0) = 1.0;
    TMatrixDColumn(A, 1) = x;
    // first bring the weights in place
    TMatrixD Aw = A;
    TVectorD yw = y;
    for (Int_t irow = 0; irow < A.GetNrows(); irow++) {
	TMatrixDRow(Aw, irow) *= e(irow);
	yw(irow) *= e(irow);
    }
    
    TDecompSVD svd(Aw);
    Bool_t ok;
    return svd.Solve(yw, ok);
}


