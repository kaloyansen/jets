/*
  tools and fun
*/


void rEnd() {;} // gSystem->Exec("xmessage -center -buttons F_I_N_I_S_H_E_D -timeout 1 -file slides/banner&"); }
void rMessages(Int_t g)
{
    gErrorIgnoreLevel=g; 
    Info("tripMessages","Info");
    Warning("tripMessages","Warning");
    Error("tripMessages","Error");
}


TH1F*rDiv(TH1F*h1,TH1F*h2,Float_t k=1,TString name="noName",TString title="noTitle")
{
    TH1F*r=new TH1F();
    r=(TH1F*)h1->Clone(name);
    for (Int_t i=1;i<=r->GetNbinsX()+1;++i) {
	Float_t x1=h1->GetBinContent(i);
	Float_t x2=h2->GetBinContent(i);
	Float_t ratio=0.0;
	if (x1>0.&&x2>0.) ratio=(k*x1)/x2;
	r->SetBinContent(i,ratio);
    }
    r->SetTitle(title);
    return r;
}

TH1F*rMul(TH1F*h1,TH1F*h2,Float_t k=1,TString name="noName",TString title="noTitle")
{
    TH1F*r=new TH1F();
    r=(TH1F*)h1->Clone(name);
    for (Int_t i=1;i<=r->GetNbinsX()+1;++i) {
	Float_t x1=h1->GetBinContent(i);
	Float_t x2=h2->GetBinContent(i);
	Float_t ratio=0.0;
	ratio=k*x1*x2;
	r->SetBinContent(i,ratio);
    }
    r->SetTitle(title);
    return r;
}




void rLoadH1Libs() {
    gInterpreter->ExecuteMacro("../../../H1Macros/skel_loadlib.C");
}


TChain*rChain(TString fileName) {
    TChain*ch=new TChain("K3");
    ch->Add(fileName);
    return ch;
}


/*
H1Tree*rH1Tree(TString fileName,Int_t input=0) {
    H1Tree*h13=H1Tree::Instance();
    if (input==0) h13->AddList(fileName);
    h13->Open();
    return h13;
}
*/





Bool_t rIsUpper(TString&str)
{
    Bool_t is=kTRUE;
    TString old=str;
    str.ToUpper();
    if (old.CompareTo(str)) is=kFALSE;
    str=old;
    return is;
}

Bool_t rIsLower(TString&str)
{
    Bool_t is=kTRUE;
    TString old=str;
    str.ToLower();
    if (old.CompareTo(str)) is=kFALSE;
    str=old;
    return is;
}


Float_t rEtaTheta(Float_t degree)
{
    Float_t eta=TMath::DegToRad()*degree;
    eta=eta/2.0;
    eta=TMath::Tan(eta);
    eta=TMath::Log(eta);
    eta=-1*eta;
    return eta;
}




void rFonts() {

    TText*t;
    Double_t x=0.02,y=0;
    TString text="Multijets in Photoproduction ";
    TCanvas*c1=new TCanvas("rootFonts","RooT fonts",0,200,1200,1200);
    Int_t font=0;
    for (Int_t i=0;i<20;++i) { 
	K3Base::ShowHide(i);
	y=0.02*i+0.02;
	font=10*i+2;
	//    font=i;
	t=new TText(x,y,text+font);
	t->SetTextFont(font);
	t->SetTextSize(0.02); 
	t->Draw();
    }
    c1->Print("rootFonts.ps");
}


void rDrawtext(double x, double y, int f, char *s)
{
    TLatex *t = new TLatex(x,y,Form("%d : %s",f,s));
    t->SetTextFont(f);
    t->SetTextAlign(12);
    t->Draw();
}


TCanvas*rFonts() {
    TCanvas *Tf = new TCanvas("Tf", "Tf",0,0,500,700);
    Tf->Range(0,0,1,1);
    Tf->SetBorderSize(2);
    Tf->SetFrameFillColor(0);
                                                                                
    double y = 0.95;
    for (int f = 12; f<=200; f+=10) {
	rDrawtext(0.02,y,f,"ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz");
	y-=0.04;
    }
    return Tf;
}


void rTestClass() {
    Int_t fI=0,j=0;
    TClonesArray*fClonesArray=new TClonesArray("K3Squeeze",0);

    while (1) {
	Info("here","Calling class dtor...");
	fClonesArray->Delete();
	Info("here","Calling clear...");
	fClonesArray->Clear();
	fI=0;
	Info("here","Calling &*");
	for (j=0;j<10;++j) {
	    TString name=Form("delete%d.ps",j++);
	    Info("here","Calling class ctor...");
	    TClonesArray&andClonesArray=*fClonesArray;
	    K3Squeeze*object=new(andClonesArray[fI++]) K3Squeeze(name,name);
	}
	for (Int_t i=0;i<fI;++i) {
	    K3Squeeze*object=(K3Squeeze*)fClonesArray->At(i);
	    object->Dump();
	}
    }
}

