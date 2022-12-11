#include "K3Ana.h"

ClassImp(K3Ana)

K3Ana::K3Ana() : K3Control() { fN = 0; fI = -1; }
K3Ana::~K3Ana() { fList = 0; fSpace = 0; }

void K3Ana::GetFile(TString filename, Int_t max)
{
     Info("GetFile", "Looking for data in <%s>...", filename.Data());
     TFile file(filename);
     TList * list = file.GetListOfKeys();
     TIter iter(list);
     TKey * key;
     TString keynames;
     while ((key = (TKey *)iter.Next())) {
	  TString classname = key->GetClassName();
	  if (classname != "K3Control") continue;
// 	TString keyname = key->GetName();
// 	if (keynames.Contains(keyname)) continue;
// 	keynames += keyname;
//	fC[fN++] = *(K3Control*)key->ReadObj();
	  fC[fN++] = *dynamic_cast<K3Control*>(key->ReadObj());

	  TString keyname = fC[fN - 1].GetName();
	  fCname[fN - 1] = keyname;
	  Info("GetFile", "got %s", keyname.Data());
	  if (fN == max) break;
     }

     if (fN == 0) { 
	  Info("GetFile", "NOTHING TO ANALYSE; HAVE TO EXIT"); 
	  return;
     }

     file.Close();
     //    SetTitle(filename);
}




void K3Ana::GetControl(K3Control * control)
{
     fC[fN++] = *control;
}


Bool_t K3Ana::Loop(Int_t n)
{
     if (n >= fN) Error("Loop", "duhai");
     else if (n >= 0) fI = n;
     else {//rewind
	  fI++;
	  if (fI == fN) { fI = -1; return kFALSE; } 
     }

     fList = fC[fI].GetList();
     fSpace = fC[fI].GetSpace();
     SetName(fC[fI].GetName());
     SetTitle(fC[fI].GetTitle());

     return kTRUE;
}

void K3Ana::Control(TString name, K3Control&control)
{
     while (Loop()) 
	  if (!name.CompareTo(fName)) 
	       control = fC[fI];
}
//K3Control*K3Ana::Control(TString name)
// {
//     K3Control*control=0;
//     if (fArray->Contains(name)) {
// 	control=(K3Control*)fArray->FindObject(name);
// 	return control;
//     }
//     if (name.EndsWith("c")) return 0;
//     if (name.EndsWith("bg")) return 0;
//     //    Send("Control",Form("Control %s not found",name.Data()));
//     return 0;
    
// }


// K3Control*K3Ana::First()
// {
//     K3Control*control = (K3Control*)fArray->At(0);
//     return control;
// }



K4Stack*K3Ana::All(TString name, TString project, TString reproject, Int_t norm)
{
     K4Stack*s = new K4Stack(name + fTitle);
     while (Loop()) s->Add(Identify(name, project, reproject));
     return s;
}





TH1*K3Ana::Sum(TString name, TString project, TString reproject, Int_t norm)
{
     TH1*h = 0;
     while (Loop()) {
	  if (fI == 0) {
	       TH1*hh = Identify(name, project, reproject);
	       h = (TH1*)hh->Clone();
	  } else if (h) h->Add(Identify(name, project, reproject));
     }
     return h;
}

/*
  Float_t K3Ana::Lumi(TH1*h)
  {
  Float_t lumi=0;
  K3Control*control=Control(h);
  if (control) {
  lumi=control->GetLumi();
  } else {
  TString hZ=h->GetZaxis()->GetTitle();
  if (hZ.CompareTo("dbg")) {
	    
// 	    TString hZ1=hZ(0,2)+"d";
// 	    TString hZ2=hZ(0,2)+"r";
// 	    K3Control*c1=Control(hZ1);
// 	    K3Control*c2=Control(hZ2);
// 	    if (!c1||!c2) {
// 		Send("Lumi",Form("Out of control %s=%s+%s",hZ.Data(),hZ1.Data(),hZ2.Data()));
// 		return 100;
// 	    }
// 	    Float_t sigma=c1->GetSigma();
// 	    sigma+=c2->GetSigma();

// 	    Int_t n=c1->GetNumi()+c2->GetNumi();
// 	    lumi=(Float_t)n/sigma;
	    
lumi=1;
} else {
lumi=Control("do6")->GetLumi();//normalize bg
}
}

return lumi;
}



K3Control*K3Ana::Control(TObject*o)
{
if (!o) return 0;
if (o->InheritsFrom("TH1F")) {
TH1F*h=(TH1F*)o;
TString hZ=h->GetZaxis()->GetTitle();
return Control(hZ);    
} else if (o->InheritsFrom("TH2F")) {
TH2F*h=(TH2F*)o;
TString hZ=h->GetZaxis()->GetTitle();
return Control(hZ);    
} else if (o->InheritsFrom("TProfile")) {
TProfile*p=(TProfile*)o;
TString hZ=p->GetZaxis()->GetTitle();
return Control(hZ);    
} else {
Send("Control","Don't know what to do!");
return 0;
}
}


TH1F*K3Ana::GetHi(TString variable,TString sample,TString level,Float_t scale,Float_t r)
{
TH1F*h=0;
TString look=variable+level;
K3Control*c=Control(sample);
if (!c) {
Send("GetHi",Form("No control %s",sample.Data()));
} else {
if (sample.EndsWith("c")) {
h=HistPlus(variable,sample(0,2)+"d",sample(0,2)+"r","","",level,scale,r);
} else {
TH1F*find=(TH1F*)c->Identify(look);
if (!find) return h;
h=(TH1F*)find->Clone();
}
	
if (scale!=1.) h->Scale(scale);
}

return h;
}


TH2F*K3Ana::GetHi2(TString variable,TString sample,TString level,Float_t scale)
{
TH2F*h=0;
TString look=variable+level;
if (!Control(sample)) return h;
K3Control*c=Control(sample);
TH2F*find=(TH2F*)c->Identify(look);
if (!find) return h;
h=(TH2F*)find->Clone();
if (scale!=1.) h->Scale(scale);
return h;
}

TH3F*K3Ana::GetHi3(TString variable,TString sample,TString level,Float_t scale)
{
TH3F*h=0;
TString look=variable+level;
if (!Control(sample)) return h;
K3Control*c=Control(sample);
TH3F*find=(TH3F*)c->Identify(look);
if (!find) return h;
h=(TH3F*)find->Clone();
if (scale!=1.) h->Scale(scale);
return h;
}


 
TGraphAsymmErrors*K3Ana::GraphEff(TString sample,TString var,TString trigger,TString monitor)
{

TString vartrig=var+"_"+trigger;
TString varmon=var+"_"+monitor;

TH1F*hTrig=GetHi(vartrig,sample);
TH1F*hMon=GetHi(varmon,sample);
if (!hTrig||!hMon) {
Send("GraphEff",Form("%s %s failure",vartrig.Data(),varmon.Data()));
return 0;
}

Int_t n=hTrig->GetNbinsX();

if (n!=hMon->GetNbinsX()) return 0;

Float_t vMon,vTrig;
for (Int_t i=0;i<n+2;++i) {
vMon=hMon->GetBinContent(i);
vTrig=hTrig->GetBinContent(i);
if (vMon<vTrig) {//flip if more entries in the subsample
//could happen if weights have been asssigned
hMon->SetBinContent(i,vTrig);
hTrig->SetBinContent(i,vMon);
}
}
Float_t x0=hTrig->GetBinLowEdge(1);
Float_t x1=hTrig->GetBinLowEdge(hTrig->GetNbinsX())+hTrig->GetBinWidth(hTrig->GetNbinsX());

TString units=hTrig->GetYaxis()->GetTitle();
if (units.CompareTo("")) units=" ["+units+"]";

TString effStr;
Float_t eff=hTrig->Integral()/hMon->Integral();
effStr=Form(" int=%4.2f",eff);

TGraphAsymmErrors*gEff=new TGraphAsymmErrors(hTrig,hMon);
gEff->SetName(vartrig+varmon);
gEff->SetTitle(trigger.ReplaceAll("0",1,"",0)+effStr);
gEff->SetMaximum(1.1);
gEff->SetMinimum(-0.1);
gEff->SetLineWidth(2);
//     if (monitor.EndsWith("1")) {
// 	gEff->SetLineStyle(2);
// 	gEff->SetLineColor(kBlue);
//     }
gEff->GetXaxis()->SetTitle(var+units);
gEff->GetYaxis()->SetTitle("efficiency");

delete hTrig;
delete hMon;
TAxis*x=gEff->GetXaxis();
x->SetLimits(x0,x1);
return gEff;
}




TH1F*K3Ana::HistPlus(TString var,TString sample1,TString sample2,
TString name,TString title,
TString level,Float_t sc,Float_t r)
{//adds two histograms from different samples
TH1F*h1=GetHi(var,sample1,level);
TH1F*h2=GetHi(var,sample2,level);
if (!h1||!h2) return 0;
if (h1->GetUniqueID()==0) return 0;

Float_t N;
TH1F*h=Daeba(h1,Lumi(h1),h2,Lumi(h2),r,N);
if (sc!=1.) h->Scale(sc);
h->SetTitle(title);
h->GetZaxis()->SetTitle(name);
delete h1;
delete h2;
return h;
}


TH2F*K3Ana::Hist2Plus(TString var,TString sample1,TString sample2,
TString name,TString title,
TString level,Float_t sc,Float_t r)
{//adds two histograms from different samples
TH2F*h1=GetHi2(var,sample1,level);
TH2F*h2=GetHi2(var,sample2,level);
if (!h1||!h2) return 0;
if (h1->GetUniqueID()==0) return 0;

Float_t N;
TH2F*h=Daeba2(h1,Lumi(h1),h2,Lumi(h2),r,N);
if (sc!=1.) h->Scale(sc);
h->SetTitle(title);
h->GetZaxis()->SetTitle(name);
delete h1;
delete h2;
return h;

}


TH3F*K3Ana::Hist3Plus(TString var,TString sample1,TString sample2,
TString name,TString title,
TString level,Float_t sc,Float_t r)
{//adds two histograms from different samples
TH3F*h1=GetHi3(var,sample1,level);
TH3F*h2=GetHi3(var,sample2,level);
if (!h1||!h2) return 0;
if (h1->GetUniqueID()==0) return 0;

Float_t N1=h1->Integral();
Float_t N2=h2->Integral();
Float_t N=N1+N2;

Norm(h1,"lumi");
Norm(h2,"lumi");

Float_t k1=1;
Float_t k2=1;
Float_t x1=1;
Float_t x2=1;
Float_t sum=0;

if (r!=0.) {//ratio is to be adjusted
x1=h1->Integral();
x2=h2->Integral();
sum=x1+x2;
k2=sum/(r+1);
k1=k2*r;
//	Send("HistPlus","Component rescaling %f %f %f %f",x1,x2,k1,k2);
}


//    TH3F*h=(TH3F*)h1->Clone(); 	    
h1->Add(h1,h2,Float_t(k1/x1),Float_t(k2/x2));

Norm(h1,N);//back to number of events
if (sc!=1.) h1->Scale(sc);
h1->SetTitle(title);
//    h->GetZaxis()->SetTitle(name);
//    delete h1;
delete h2;
return h1;
}


TH1F*K3Ana::HistStay(TString var,TString mc)
{
TString dir=mc+"d";
TString res=mc+"r";
TH2F*correlation=this->Hist2Plus(var+"Rec",dir,res,"sam","sample");
if (!correlation) return 0;
TH1F*projx=(TH1F*)correlation->ProjectionX();
TH1F*stay=(TH1F*)projx->Clone(var+"_stay");
for (Int_t i=0;i<correlation->GetNbinsX()+2;++i) {
Float_t n=correlation->GetBinContent(i,i);
Float_t dn=correlation->GetBinError(i,i);
stay->SetBinContent(i,n);
stay->SetBinError(i,dn);
}
delete correlation;
return stay;

}

TF1*K3Ana::FitBias(TString var,TString mc,Float_t&min,Float_t&max)
{
TH2F*correlation=this->Hist2Plus(var+"Rec",mc+"d",mc+"r","sam","sample");
if (!correlation) return 0;
Int_t n=correlation->GetNbinsX();
min=correlation->GetBinLowEdge(1);
max=correlation->GetBinLowEdge(n+1);

TF1*gausfit=new TF1("gausfit","gaus");
TF1*fitbias=new TF1("fitbias","[0]*x+[1]");
TProfile*result=new TProfile("result","result",2*n-1,min,max);
for (Int_t i=1;i<2*n;++i) {
Float_t boundary=correlation->GetBinLowEdge(i+1);
TH1F*h=new TH1F(Form("hist%d",i),Form("hist%d",i),i,-1.*boundary,boundary);
Float_t content,error,location,sum=0;
for (Int_t bin=1;bin<i+1;++bin) {
content=correlation->GetBinContent(i+1-bin,bin);
error=correlation->GetBinError(i+1-bin,bin);
sum+=content;
h->SetBinContent(bin,content);
h->SetBinError(bin,error);
}

if (sum==0.) {
delete h;
continue;
}

h->Fit(gausfit,"NQ");
location=result->GetBinCenter(i);
result->Fill(location,gausfit->GetParameter(1),sum);
result->SetBinError(i,gausfit->GetParameter(2));
delete h;
}

result->Fit(fitbias,"NQ");
Float_t par0=fitbias->GetParameter(0);
Float_t par1=fitbias->GetParameter(1);
fitbias->SetParameters(par0+1.,par1);

delete correlation; 
delete gausfit;
delete result;
return fitbias;

}

TH1F*K3Ana::HistBias(TString var,TString mc)
{
Float_t min,max;
TF1*fitbias=this->FitBias(var,mc,min,max);
TH2F*correlation=this->Hist2Plus(var+"Rec",mc+"d",mc+"r","sam","sample");
if (!correlation) return 0;
TH1F*projx=(TH1F*)correlation->ProjectionX();
TH1F*histbias=(TH1F*)projx->Clone(var+"_bias");
TAxis*axis=histbias->GetXaxis();
for (Int_t i=1;i<histbias->GetNbinsX()+1;++i) {
Float_t x=axis->GetBinCenter(i);
Float_t y=fitbias->Eval(x);
histbias->SetBinContent(i,x-y);
histbias->SetBinError(i,0);//hmm
}

delete fitbias;
delete correlation;
delete projx;
return histbias;
}


TH1F*K3Ana::HistMCPlus(TString var,TString name,TString mc,Float_t sc,Float_t r,TString option)
{    
//        Divides two different level histograms.
//        As the errors are correlated, they must be added by quadrature

//        names:                     
//        detector( correction)       
//        hadron(ization correction) 
//        purity                    
//        stability                
    

TString dir=mc+"d";
TString res=mc+"r";
TString com=mc+"c";

TH1F*his[3];
his[0]=HistPlus(var,       dir,res,com,"PYTHIA","",   sc,r);//det
his[1]=HistPlus(var,       dir,res,com,"PYTHIA","Gen",sc,r);//had
//    his[2]=HistPlus(var,       dir,res,com,"PYTHIA","Par",sc,r);//par
//    his[2]=new TH1F("del","del",10,0,1);
his[2]=HistStay(var,mc);
//    his[3]=HistBias(var,mc);
//    his[3]=HistPlus(var+"Stay",dir,res,com,"PYTHIA","",   sc,r);//stay

TH1F*h=0;
if (!name.CompareTo("detector")) { h=Product(his[0],his[1],option);	if (h) h->SetTitle("correction");
} else if (!name.CompareTo("purity")) { h=Product(his[2],his[0],option); if (h) h->SetTitle("purity");
} else if (!name.CompareTo("stability")) { h=Product(his[2],his[1],option); if (h) h->SetTitle("stability");
} else if (!name.CompareTo("stay")) { h=(TH1F*)his[2]->Clone(); if (h) h->SetTitle("stay");
} else Send("HistMCPlus",Form("Unexpected option %s",name.Data())); 

for (Int_t i=0;i<3;++i) if (his[i]) delete his[i];

if (h) h->SetLineWidth(2);
else { Send("HistMCPlus","return 0"); }
return h;
}



TH1F*K3Ana::HistCorrectedError(TString sample,TString var,TString mc,Float_t sc,Float_t r,TString option,Bool_t bias)
{
TH1F*data=HistCorrectedData(sample,var,mc,sc,r,bias);

TH1F*mean=this->HistPlus(var,"pyd","pyr",var,"syst","",sc,r);
TH1F*plus=this->HistPlus(var,"ppd","ppr",var,"syst","",sc,r);
TH1F*minu=this->HistPlus(var,"pmd","pmr",var,"syst","",sc,r);
if (!mean||!plus||!minu) return data;

   
TH1F*error=(TH1F*)data->Clone(option);

if (option.Contains("+")) {
TH1F*divide=this->Systematics(mean,plus);
error->Divide(divide);
delete divide;
} else if (option.Contains("-")) {
TH1F*divide=this->Systematics(mean,minu);
error->Divide(divide);
delete divide;
} else Send("HistCorrectedError",Form("Unknown option %s",option.Data()));
    
    
//     data->SetName("option");

//     if (option.Contains("+")) {
// 	TH1F*divide=this->Systematics(mean,plus);
// 	data->Divide(divide);
// 	delete divide;
//     } else if (option.Contains("-")) {
// 	TH1F*divide=this->Systematics(mean,minu);
// 	data->Divide(divide);
// 	delete divide;
//     } else Send("HistCorrectedError",Form("Unknown option %s",option.Data()));
    

delete data;
delete mean;
delete plus;
delete minu;
return error;
}



TH1F*K3Ana::HistSimulatedMC(TString sample,TString var,TString mc,Float_t sc,Float_t r,TString option)
{//   Applies correction factors to simulate detector effects

TH1F*h=GetHi(var,sample,"Gen");//hadron level to be simulated
if (!h) Send("HistSimulatedMC","!h");


TH1F*correction=HistMCPlus(var,"detector",mc,sc,r,option);
if (!correction) {
//	Send("HistCorrectedData",Form("Cannot find correction for %s",var.Data()));
return h;
}

TH1F*simulated=Product(h,correction,option);

//     TString title=h->GetTitle();
//     TString newtitle=title+",";
//     simulated->SetTitle(newtitle);
//     simulated->SetLineWidth(3);

delete h;
delete correction;
return simulated;
}



TH1F*K3Ana::HistCorrectedData(TString sample,TString var,TString mc,Float_t sc,Float_t r,TString option,Bool_t bias)
{//   Applies correction factors to get hadron level
//    TString mopt="muno";
//    mopt="mul";

TH1F*h=GetHi(var,sample);//data to be corrected
if (!h) Send("HistCorrectedData","!h");

// Correct to hadron level
//    TH1F*de=HistDetectorCorrections(var,cLayer);

TH1F*correction;
if (!bias) correction=HistMCPlus(var,"detector",mc,sc,r,option);
else correction=HistMCPlus(var,"elsen",mc,sc,r,option);
//    TH1F*biashist=HistMCPlus(var,"bias",mc,sc,r,option);
if (!correction) {
//  Send("HistCorrectedData",Form("Cannot find correction for %s",var.Data()));
return h;
}

TH1F*corrected=Product(h,correction,option);
if (bias) {
TString title=h->GetTitle();
TString newtitle=title+",";
corrected->SetTitle(newtitle);
}

//     Float_t min,max;
//     TF1*fitbias=this->FitBias(var,mc,min,max);
//     TF1*diagonal=new TF1("diagonal","x",min,max);
//     if (bias&&fitbias) {
// 	//	corrected->Add(biashist);
// 	for (Int_t bin=1;bin<=corrected->GetNbinsX();++bin) {
// 	    Float_t content=corrected->GetBinContent(bin);
// 	    if (content==0.) continue;
// 	    Float_t center=corrected->GetBinCenter(bin);
// 	    Float_t bias=fitbias->Eval(center)/diagonal->Eval(center);
// 	    Send("HistCorrectedData",Form("%f %f",content,bias));
// 	    corrected->SetBinContent(bin,content*bias);
// 	}
// 	TString title=h->GetTitle();
// 	TString newtitle=title+",";
// 	corrected->SetTitle(newtitle);
//     }
    
    
//     TString title=h->GetTitle();
//     TString newtitle=title+",";
//     corrected->SetTitle(newtitle);
//     corrected->SetLineWidth(3);
    

delete h;
delete correction;
//    delete biashist;
//    delete fitbias;
//    delete diagonal;
return corrected;
}





void K3Ana::Norm(TH1*h,Float_t k) { h->Scale(k/h->Integral()); }
void K3Ana::Norm(TH1*h,TString s)
{
if (!h) return;
if (!s.CompareTo("lumi")) {
h->Scale(1.0/Lumi(h));
} else if (!s.CompareTo("bin")) {
Int_t n=h->GetNbinsX();
for (Int_t i=0;i<=n+1;++i) {
h->SetBinContent(i,h->GetBinContent(i)/h->GetBinWidth(i));
h->SetBinError(i,h->GetBinError(i)/h->GetBinWidth(i));
}
} else {
Send("Norm",Form("Unexpected option %s",s.Data()));
}
}


Float_t K3Ana::Norm(TH1*h,TH1*to)
{
if (!h&&!to) {
Send("Norm","Empty histogram");
return 0;
}
Float_t toint=to->Integral();
Float_t hint=h->Integral();
Float_t r=toint/hint;
h->Scale(r);
return r;
}


void K3Ana::Norm(TProfile*h,TString s)
{
if (!h) return;
if (!s.CompareTo("lumi")) {
K3Control*control=Control(h);
if (!control) {
//	    Send("Norm","Virtual layer!");
return;
}
h->Scale(1.0/Control(h)->GetLumi());
} else if (!s.CompareTo("bin")) {
Int_t n=h->GetNbinsX();
for (Int_t i=0;i<=n+1;++i) {
h->SetBinContent(i,h->GetBinContent(i)/h->GetBinWidth(i));
h->SetBinError(i,h->GetBinError(i)/h->GetBinWidth(i));
}
} else {
Send("Norm",Form("Unexpected option %s",s.Data()));
}
}




TString K3Ana::HistName(TString layer,Int_t i)
{
K3Control*control=Control(layer);
TList*clist=control->fArray;
TObject*o=clist->At(i);
TString hName="";
if (o->InheritsFrom("TH1")) {
TH1*h=(TH1*)o;
hName=h->GetName();
return hName;
}
return hName;
}



TH1F*K3Ana::Systematics(TH1F*mean,TH1F*divide)
{
    
TH1F*syst=(TH1F*)mean->Clone();
syst->Divide(divide);
return syst;
    
}

*/






TGraphErrors*K3Ana::Resolution(TString mode, Bool_t space, TClonesArray*stax, TString title)
{
     Info("Resolution", "begin");
     TGraphErrors*resolution = new TGraphErrors();
     //    TDatime a;
     TRandom random(title.Hash());
     //    TRandom random(a.GetSecond());
     Int_t color = kBlack;//random.Integer(10);
     resolution->SetLineColor(color);
     resolution->SetMarkerColor(color);
     resolution->SetLineStyle(random.Integer(5));
     resolution->SetMarkerStyle(20 + random.Integer(10));
     resolution->SetMarkerSize(1);

     TH1*h = 0;
     TF1*gaus=new TF1("gaus", "gaus");//, min, max);
     gaus->SetLineColor(color);
     //    fits = new K4Stack();

     K4Stack*fits = 0;
     if (stax) {
	  TClonesArray &staxon = *stax;
	  fits = new(staxon[stax->GetEntries()]) K4Stack(mode, title);
     }

     Info("Resolution", "gonna loop");

     while (Loop()) {
	  Info("Resolution", "in loop");
	  TString name = fName;
	  name.ReplaceAll("test", "");	
	  Double_t e = Double_t(name.Atoi());

	  Info("Resolution", "before identify");
	  h = Identify(mode);
	  Info("Resolution", "after identify");
	  resolution->SetTitle(title);
	  if (h) {
	       Info("Resolution", "if h");
	       gaus->SetRange(-10, 10);

	       Info("Resolution", "fit 1");
	       h->Fit(gaus, "Q,R,N");
	       Double_t mean = gaus->GetParameter("Mean");
	       Double_t sigma = gaus->GetParameter("Sigma");
	       //	    Info("Resolution", "%f GeV: mean:%f sigma:%f", e, mean, sigma);	    	    

	       if (!space) gaus->SetRange(mean - sigma, mean + 2 * sigma);
	       else gaus->SetRange(mean - 2 * sigma, mean + 2 * sigma);

	       Info("Resolution", "fit 2");
	       h->Fit(gaus, "Q,R,N");
	    
	       TH1*hh = (TH1*)h->Clone();
	       hh->Scale(hh->Integral());
	       hh->SetTitle(Form("%.0f GeV", e));
	       if (fits) fits->Add(hh);
	       resolution->SetPoint(fI, e, gaus->GetParameter(2));
	       //	    resolution->SetPoint(fI, 1 / TMath::Sqrt(e), gaus->GetParameter(2));
	       resolution->SetPointError(fI, 0, gaus->GetParError(2));
	  } else { 
	       Error("resolution", "!h"); 
	  }
     }

     Info("Resolution", "did loop");


     delete gaus;

     Info("Resolution", "end");
     return resolution;
}






TF1 * K3Ana::Resolution( TH1 * h, Float_t minus, Float_t plus) 
{
//    TF1 * g = new TF1("g", "[0]*exp(-0.5*((x-[1])/[2])**2)");
//     h->SetOption("Show Fit Parameters");
//     h->SetDrawOption("E");
     h->SetFillStyle(0);
     TF1 * g = new TF1("g", "gaus");
     g->SetLineColor(kRed);
     g->SetLineWidth(1);
     Float_t constant, mean, sigma, convergency;
     Float_t econstant, emean, esigma;

     h->Fit(g, "Q");

     constant = g->GetParameter(0); mean = g->GetParameter(1); sigma = g->GetParameter(2);
     econstant = g->GetParError(0); emean = g->GetParError(1); esigma = g->GetParError(2);

//    Int_t loop;
//    for (loop = 0; loop < 10; ++loop) {
     Bool_t stop = kFALSE;
     Int_t iteration = 1;
     while (!stop) {

	  cout << iteration << " iteration: " 
	       << constant << "("<< econstant <<")" << " " 
	       << mean << "("<< emean <<")" << " " 
	       << sigma << "("<< esigma <<")";

	  g->SetParameters(constant, mean, sigma);
	  g->SetRange(mean + minus * sigma, mean + plus * sigma);

	  h->Fit(g, "RQ");

	  convergency = (constant / Float_t(g->GetParameter(0))) * (mean / Float_t(g->GetParameter(1))) * (sigma / Float_t(g->GetParameter(2)));

	  if ( convergency == 1. || iteration++ > 10)  {
	       cout << " converged" << endl;
	       break;
	  } else cout << " convergency:"<< convergency << endl;

	  constant = g->GetParameter(0); mean = g->GetParameter(1); sigma = g->GetParameter(2);
	  econstant = g->GetParError(0); emean = g->GetParError(1); esigma = g->GetParError(2);
     }

     return g;
}


void K3Ana::PrintFitGausParameters(TF1 * fitfctn)
{
     TPaveText * pt = new TPaveText(0.24, 0.7, 0.9, 0.9,"tbNDC");
     pt->SetFillStyle(0);
     pt->SetTextSize(0.04);
     pt->SetTextColor(kBlue);
     pt->SetTextAlign(12);
     pt->SetBorderSize(0);

     TText * pte;
     /*char array to hold the legend's entries:*/
     char display[50];

     /*extract the fit parameters*/
     Double_t p0 = fitfctn->GetParameter(0);
     Double_t e0 = fitfctn->GetParError(0);
     sprintf(display, "c = %5.2f #pm %3.2f", p0, e0);
     pte = pt->AddText(display);

     Double_t p1 = fitfctn->GetParameter(1);
     Double_t e1 = fitfctn->GetParError(1);
     sprintf(display, "#mu = %5.4f #pm %3.2f", p1, e1);
     pte = pt->AddText(display);

     Double_t p2 = fitfctn->GetParameter(2);
     Double_t e2 = fitfctn->GetParError(2);
     sprintf(display, "#sigma = %5.4f #pm %3.2f", p2, e2);
     pte = pt->AddText(display);

     pt->SetTextFont(102);
     pt->Draw();

}




TF1*K3Ana::Resolution(TMultiGraph*m, TString option) {
     if (!m) {	cout << "m == 0" << endl;	return 0;    }
     //    TF1*f1 = new TF1("f1", "[0]*x+[1]");
     //    TF1*f1 = new TF1("f1", "[0]/sqrt(x)+[1]");
     //    TF1*f1 = new TF1("f1", "sqrt(([0]/sqrt(x))*([0]/sqrt(x))+[1]*[1])");
     TF1*f1 = new TF1("f1", "sqrt([0]*[0]/x+[1]*[1])");
     //    TF1*f1 = new TF1("f1", "sqrt([0]/x+[1])");
     
     TIter next(m->GetListOfGraphs());
     TObject*o = 0;
     while ((o = next())) {    
	  if (o->InheritsFrom("TGraph")) {
	       TGraph*g=(TGraph*)o;
	       TString gtitle = g->GetTitle();
	       f1->SetParNames(gtitle+", stochastic term", gtitle+", constant term");
	       f1->SetLineColor(g->GetLineColor());
	       f1->SetLineStyle(g->GetLineStyle());
	       f1->SetLineWidth(g->GetLineWidth());
	       g->Fit(f1, option);
	  }
     }
     return f1;
}
