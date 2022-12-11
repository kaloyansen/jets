/*
  K4Pad instances
*/



TPad*padPtHatK3()
{
    TChain chain3("K3");
    TChain chain4("K3");
    TChain chain5("K3");
    chain3.Add("files/k3/toTrip/K3pui00.root");
    chain4.Add("files/k3/toTrip/K3pvi00.root");
    chain5.Add("files/k3/toTrip/K3pwi00.root");

    TCanvas*canvas=new TCanvas("ds","cdsa",1500,1000);
    TPad*pad=new TPad("take","p_{T,hat}",0,0,1,1);
    pad->SetFillColor(10);
    pad->Draw("N");
    pad->cd();
    pad->Divide(1,3);

    const char*limits="b_detector.h1Pt2HatGki<20&&b_hadron.Et(0)<20";
    const char*pthat="sqrt(b_detector.h1Pt2HatGki)";
    const char*pt1="b_hadron.Et(0)";
    const char*option="";


    pad->cd(1);
    chain3.Draw(Form("%s:%s",pthat,pt1),Form("%s<4&&%s<12",pthat,pt1),option);
    pad->Update();

    pad->cd(2);
    chain4.Draw(Form("%s:%s",pthat,pt1),Form("%s<5&&%s<12",pthat,pt1),option);
    pad->Update();

    pad->cd(3);
    chain5.Draw(Form("%s:%s",pthat,pt1),Form("%s<6&&%s<12",pthat,pt1),option);
    pad->Update();

    return pad;

}


/*
TPad*padPtHatFromAnalysis(K3Ana*a)
{
    TPad*pad=new TPad("pt","var",0,0,1,1);
    pad->Draw("N");
    pad->cd();

    TH2F*pth3=a->Control("pui")->FindHi2("PtHatEt1Gen");
    TH2F*pth4=a->Control("pvi")->FindHi2("PtHatEt1Gen");
    TH2F*pth5=a->Control("pwi")->FindHi2("PtHatEt1Gen");
    pth3->SetLineColor(kRed);
    pth4->SetLineColor(kBlue);
    pth3->Draw("box");
    pth4->Draw("boxsame");
    pth5->Draw("boxsame");
    return pad;
}



TPad*padPtHat(TString file)
{
    cout<<"Loading H1..."<<endl;
    rLoadH1Libs();
    H1Tree*h13=H1Tree::Instance();
    h13->AddList(file);
    h13->Open();

    TCanvas*canvas=new TCanvas();
    TPad*pad=new TPad("take","p_{T,hat}",0,0,1,1);
    pad->SetFillColor(10);
    pad->Draw("N");
    pad->cd();
    pad->Divide(4,4);


    TString ptHat="sqrt(Pt2HatGki)";
    TString pt1="KtJetPt";
    
    pad->cd(1);
    h13->DrawHat(ptHat,ptHat+"<15");
    pad->Update();
    pad->cd(2);
    h13->DrawHat(ptHat,ptHat+"<15&&"+pt1+">13");
    pad->Update();
    pad->cd(3);
    h13->DrawHat(ptHat,ptHat+"<15&&"+pt1+">12");
    pad->Update();
    pad->cd(4);
    h13->DrawHat(ptHat,ptHat+"<15&&"+pt1+">11");
    pad->Update();
    pad->cd(5);
    h13->DrawHat(ptHat,ptHat+"<15&&"+pt1+">10");
    pad->Update();
    pad->cd(6);
    h13->DrawHat(ptHat,ptHat+"<15&&"+pt1+">9");
    pad->Update();
    pad->cd(7);
    h13->DrawHat(ptHat,ptHat+"<15&&"+pt1+">8");
    pad->Update();
    pad->cd(8);
    h13->DrawHat(ptHat,ptHat+"<15&&"+pt1+">7");
    
    pad->Update();
    pad->cd(10);
    h13->DrawHat(pt1,pt1+"<15&&"+ptHat+">5");
    pad->Update();
    pad->cd(11);
    h13->DrawHat(pt1,pt1+"<15&&"+ptHat+">6");
    pad->Update();
    pad->cd(12);
    h13->DrawHat(pt1,pt1+"<15&&"+ptHat+">7");
    pad->Update();
    pad->cd(13);
    h13->DrawHat(pt1,pt1+"<15&&"+ptHat+">8");
    pad->Update();
    pad->cd(14);
    h13->DrawHat(pt1,pt1+"<15&&"+ptHat+">9");
    pad->Update();
    pad->cd(15);
    h13->DrawHat(pt1,pt1+"<15&&"+ptHat+">10");
    pad->Update();
    pad->cd(16);
    h13->DrawHat(pt1,pt1+"<15&&"+ptHat+">11");

    return pad;

}


TPad*pad2d(K3Ana*a,TString samples,TString var,TString option="box",Int_t logx=0,Int_t logy=0)
{
    TPad*pad=new TPad(var,var,0,0,1,1);
    pad->Draw("N");
    pad->cd();

    TString sample,symbol,unit;
    TH2F*h;
    Bool_t first=kTRUE;
    Int_t i=0;
    do {
	sample=K4Stack::TakeString(samples,i);
	if (!sample.CompareTo("")) break;
	
	TString dir,res,sam=sample;
	sam.ToLower();
    //    TString mid=sam(1,1);
	TString mid=sample(1,1);

    
	Int_t generator=0;
	Bool_t iserror,ismc,iserror,issim,isgas,iscomb,isdir,isres,isincl;
	if (sam.BeginsWith("energy")) iserror=kTRUE;
	if (sam.BeginsWith("d")) {
	    ismc=kFALSE;
	//	iserror=kTRUE;
	//	if (rIsLower(mid)) iserror=kFALSE;
	} else {
	    ismc=kTRUE;
	    if (sam.BeginsWith("p")) generator=1;
	    else if (sam.BeginsWith("h")) generator=2;
	    else if (sam.BeginsWith("c")) {
		if (mid.CompareTo("b")) generator=3;
		else generator=4;
	    } else generator=5;
	}
    
	if (!mid.CompareTo("y")) issim=kTRUE;
	else if (!mid.CompareTo("p")) issim=kTRUE;
	else if (!mid.CompareTo("m")) issim=kTRUE;
	else if (!ismc) issim=kTRUE;
	else issim=kFALSE;
    
	if (sam.CompareTo("dbg")) isgas=kFALSE;
	else isgas=kTRUE;
	
	iscomb=isdir=isres=isincl=kFALSE;
	if (sam.EndsWith("c")) {
	    iscomb=kTRUE;
	    dir=res=sam;
	    res.Replace(2,1,"r");
	    dir.Replace(2,1,"d");
	    if (!issim) dir.Replace(1,1,"n");
	//	if (generator==1) dir.Replace(1,1,"m");
	}



	if (!sample.EndsWith("c")) {
	    h=a->GetHi2(var,sample);
	} else {//combined
	    //	    h=a->Hist2Plus(var,sample(0,2)+"d",sample(0,2)+"r","pyc","Pythia");
	    h=a->Hist2Plus(var,dir,res,"sam","sample");
	}

	if (!h) cout<<"pad2d::h=0"<<endl;

	h->SetLabelSize(0.06, "X");
	h->SetLabelSize(0.06, "Y");
	h->SetTitleSize(0.08, "X");
	h->SetTitleSize(0.08, "Y");
	if (i==0) {
	    h->SetFillColor(kMagenta);
	    h->SetLineWidth(1);
	    h->SetLineColor(kRed);
	    h->SetMarkerSize(2);
	} else {
	    h->SetLineWidth(1);
	    h->SetLineColor(kBlack);
	}

	symbol=h->GetXaxis()->GetTitle();
	unit=h->GetYaxis()->GetTitle();

	if (var.EndsWith("Rec")) {
	    if (unit.CompareTo("")) unit="["+unit+"]";
	    h->SetXTitle(symbol+"^{rec} "+unit);
	    h->SetYTitle(symbol+"^{had} "+unit);
	} else {
	    ;
	}

	if (!first) option+="same";
	h->Draw(option);
	Float_t min,max;
	TF1*fitbias=a->FitBias(var.Remove(var.Length()-3,3),"py",min,max);
	TF1*diagonal=new TF1("diagonal","x",min,max);
	if (fitbias) { 
	    fitbias->SetLineWidth(1);
	    fitbias->SetLineColor(kMagenta);
	    fitbias->Draw("same");
	    diagonal->SetLineWidth(1);
	    diagonal->SetLineColor(kCyan);
	    diagonal->Draw("same");
	}

	if (first&&h->GetNbinsX()==h->GetNbinsY()) {
	    if (var.EndsWith("Rec")) {
		TLine*l=new TLine(h->GetXaxis()->GetXmin(),h->GetYaxis()->GetXmin(),
				  h->GetXaxis()->GetXmax(),h->GetYaxis()->GetXmax());
		l->SetLineStyle(3);
		l->Draw("same");
	    }
	}
	
	if (first&&var.Contains("XY")&&option.Contains("cont")) {
	    TLine*l=new TLine(0.1,0.1,0.6,1.2);
	    l->Draw("same");
	}


	i++;
	first=kFALSE;

    } while(1);

    gPad->SetLogy(logy);
    gPad->SetLogx(logx);
    return pad;
}

TPad*pad3d(K3Ana*a,TString samples,TString var,TString option="",Int_t logx=0,Int_t logy=0)
{
    TPad*pad=new TPad(var,var,0,0,1,1);
    pad->Draw("N");
    pad->cd();

    TString sample,symbol,unit;
    TH3F*h;
    Bool_t first=kTRUE;
    Int_t i=0;
    do {
	sample=K4Stack::TakeString(samples,i);
	if (!sample.CompareTo("")) break;
	if (!sample.EndsWith("c")) {
	    h=a->GetHi3(var,sample);
	} else {//combined
	    h=a->Hist3Plus(var,sample(0,2)+"d",sample(0,2)+"r","pyc","Pythia");
	}

	if (!h) cout<<"h=0 in pad3d"<<endl;

	h->SetLabelSize(0.06, "X");
	h->SetLabelSize(0.06, "Y");
	h->SetLabelSize(0.06, "Z");
	h->SetTitleSize(0.08, "X");
	h->SetTitleSize(0.08, "Y");
	h->SetTitleSize(0.08, "Z");
	h->SetFillColor(kBlue);
	h->SetLineWidth(0);
	h->SetLineColor(kRed);

	symbol=h->GetXaxis()->GetTitle();
	unit=h->GetYaxis()->GetTitle();

	if (var.EndsWith("Rec")) {
	    if (unit.CompareTo("")) unit="["+unit+"]";
	    h->SetXTitle(symbol+"^{rec} "+unit);
	    h->SetYTitle(symbol+"^{had} "+unit);
	} else {
	    //	    h->SetXTitle(var);
	    //	    h->SetYTitle(symbol);
	}

	//	stackColorize(h,sample);
	//	h->SetFillStyle(0);
	if (!first) option+="same";
	h->Draw(option);

	i++;
	first=kFALSE;

    } while(1);

    gPad->SetLogy(logy);
    gPad->SetLogx(logx);
    return pad;
}




TPad*padBalance(K3Ana*a,TString var,TH1F&*hist,Int_t calibration=0,Int_t rebin=0)
{
    TPad*pad=new TPad(var,var,0,0,1,1);
    pad->Draw("N");
    pad->cd();

    Int_t n=hist->GetNbinsX();
    Bool_t notDivided=kTRUE;
    Int_t x=0;
    do {
	x++;
	if (x*x>=n) {
	    pad->Divide(x,x,0,0);
	    notDivided=kFALSE;
	}
    } while (notDivided);

    TString bin;
    Int_t i;
    Float_t mean,error;

    TString dName="do6";
    TString mName="jan";
    mName="pyd";
    if (calibration>0) {
	dName=Form("%sc%d",dName.Data(),calibration);
	mName=Form("%sc%d",mName.Data(),calibration);
    }

    a->Send("padBalance",Form(" %s %s",dName.Data(),mName.Data()));

    for (i=1;i<n;++i) {
	bin=Form("%sBin%d",var.Data(),i);
	//	cout<<bin<<endl;
	pad->cd(i+1);
	if (stackDrawBalance(a,bin,mean,error,dName,mName)) {
	    pad->Update();
	    pad->Modified();
	}
	hist->SetBinContent(i,mean);
	hist->SetBinError(i,error);
	//	cout<<mean<<" "<<error<<endl;
    }

    hist->SetMarkerStyle(kFullCircle);
    if (rebin>0) {
	hist->Rebin(rebin);
	Float_t scale=1./rebin;
	hist->Scale(scale);
    }

    return pad;
}




K4Pad*padCompAndRatio(K3Ana*a,TString var,TString norm,TString sample,Int_t legend=1,Int_t logy=0) 
{
    K4Stack*comp=stackComp(a,var,norm,sample,legend);
    comp->Logy(logy);
    K4Stack*ratio=stackRatio(a,var,norm,sample,0);
    TObjArray*array=new TObjArray();
    array->Add(comp);
    array->Add(ratio);
    K4Pad*p=new K4Pad(array,kTRUE);
    return p;
}



K4Pad*padHatVar(K3Ana*a,TString norm,TString layers) {
    const Int_t maxVar=18;
    TString var[]={"BGBits","ElecE","Epz","Etag6","Ivtyp","KtJetPt","KtJetTheta","NumCentralTracks","NumEmParts","NumHfs","NumKtJets","PtMiss","Q2e","Q2h","RunNumber","ScalEt","VtxZ","Yh"};
    TObjArray*arr=new TObjArray();
    for (Int_t i=0;i<maxVar;++i) arr->Add(stackComp(a,var[i],norm,layers,0));
    K4Pad*p=new K4Pad(arr);
    return p;
}


K4Pad*padAll(K3Ana*a,TString norm,TString layers,Int_t from,Int_t to) {
    TString histName;
    TObjArray*arr=new TObjArray();
    for (Int_t i=from;i<to;++i) {
	histName=a->HistName("do6",i);

	if (histName.EndsWith("Gen")) continue;
	if (histName.EndsWith("Par")) continue;
	if (histName.Contains("_")) continue;
	Error("padAll","%d %s",i,histName.Data());
	arr->Add(stackComp(a,histName,norm,layers,0));
    }
    K4Pad*p=new K4Pad(arr);
    return p;
}




K4Pad*padTriggerEfficiency(K3Ana*a,TString layer)
{
    TObjArray*oa=new TObjArray();
    Int_t maxTrig=4;
    TString trig[]={"s74","s76","s56","all"};
    Int_t maxVar=5;
    TString var[]={"Et1","Et2","Eta1","Eta2","Yh"};

    for (Int_t t=0;t<maxTrig;++t) for (Int_t v=0;v<maxVar;++v) {
	oa->Add(a->StackEff(layer,var[v],trig[t],"m03"));
    }

    K4Pad*gl=new K4Pad(oa,1,maxVar);
    return gl;
}


K4Pad*padTriggerEfficiency2(K3Ana*a,TString layer)
{
    TObjArray*oa=new TObjArray();
    Int_t maxTrig=2;
    TString trig[]={"s76","s74"};
    Int_t maxVar=2;
    TString var[]={"Et1","Et2"};

    for (Int_t t=0;t<maxTrig;++t) for (Int_t v=0;v<maxVar;++v) {
	oa->Add(a->StackEff(layer,var[v],trig[t],"m03"));
    }

    K4Pad*gl=new K4Pad(oa,1,maxVar);
    return gl;
}

*/



K4Pad*padBG(Bool_t doCut=kFALSE) {
    //ne e tuka


/*  
  826662   total entries 
       0  -1  if information is absent in the database
     642   0  for the empty bunch
    8727   1  for the p-pilot bunch
     446   2  for the e-pilot bunch
    9815      for non-colliding bunch   
  816847   3  for the colliding bunch
ratio col/non=83


mean proton pilot current = 2.841
mean proton current = 86.88
ratio = 0.0327002762430939273

*/
    gROOT->SetBatch(kTRUE);
    TCanvas*del=new TCanvas("fdsv","gfds");

    Float_t k=0.0327002762430939273;

    TChain*chain=coreChain("data");

    /*
    if (doCut) {
	TFile*flist=new TFile("list.root");
	TEventList*list=(TEventList*)flist->Get("evList");
	chain->SetEventList(list);
    }
    */

    TH1F*bunches=new TH1F("bunches","bunch type",6,0.0,6.0);

    TH1F*cjc=new TH1F("cjc","T0_CJC coll.",100,-1000.0,4000.0);
    TH1F*cjcac=new TH1F("cjcac","pilot(Ip/Ipp)",100,-1000.0,4000.0);
    
    TH1F*lar=new TH1F("lar","T0_LAr",33,-7.0,7.0);
    TH1F*larac=new TH1F("larac","pilot(Ip/Ipp)",33,-7.0,7.0);
    
    TH1F*pcur=new TH1F("pcur","proton current",100,-10.0,120.0);
    TH1F*ppcur=new TH1F("ppcur","pilot current",100,-10.0,120.0);

    chain->Draw("b_detector.h1BunchType>>bunches");
    chain->Draw("b_detector.h1T0_CJC>>cjc","b_detector.h1BunchType==3");
    chain->Draw("b_detector.h1T0_CJC>>cjcac","b_detector.h1BunchType==1");
    chain->Draw("b_detector.h1T0_LAr>>lar","b_detector.h1BunchType==3");
    chain->Draw("b_detector.h1T0_LAr>>larac","b_detector.h1BunchType==1");
    chain->Draw("b_detector.h1P_current>>pcur");
    chain->Draw("b_detector.h1P_p_current>>ppcur");

    cjcac->Scale(1.0/k);
    larac->Scale(1.0/k);

    Int_t fs0=1002;
    Int_t fc=1;
    Int_t fs=3004;

    K4Stack*kCurr=new K4Stack("kCurr","");
    pcur->SetFillStyle(fs0);
    kCurr->Add(pcur);
    ppcur->SetFillColor(fc);
    ppcur->SetFillStyle(fs);
    kCurr->Add(ppcur);
    kCurr->Logy(1);

    K4Stack*kBunch=new K4Stack("kBunch","");
    bunches->SetFillStyle(fs0);
    kBunch->Add(bunches);
    kBunch->Logy(1);


    K4Stack*kLAr=new K4Stack("kLAr","");
    lar->SetFillStyle(fs0);
    kLAr->Add(lar);
    larac->SetFillColor(fc);
    larac->SetFillStyle(fs);
    kLAr->Add(larac);
    kLAr->Logy(1);

    K4Stack*kCJC=new K4Stack("kCJC","");
    cjc->SetFillStyle(fs0);
    kCJC->Add(cjc);
    cjcac->SetFillColor(fc);
    cjcac->SetFillStyle(fs);
    kCJC->Add(cjcac);
    kCJC->Logy(1);


    del->Clear();
    
    TObjArray*oa=new TObjArray();
    oa->Add(kBunch);
    oa->Add(kCurr);
    oa->Add(kLAr); 
    oa->Add(kCJC); 

    K4Pad*gl=new K4Pad(oa);
    return gl;
    
    /*
    if (nomer==1) {
	return kCurr;
    } else if (nomer==0) {
	return kBunch;
    } else if (nomer==2) {
	return kLAr;
    } else {
	return kCJC;
    }

    
    TString cStr;
    if (doCut) cStr="bgAfterCuts";
    else cStr="bgBeforeCuts";
    TCanvas*can=new TCanvas(cStr,cStr);
    can->SetFillColor(10);
    return can;

    */

}



TPad*padDetector(Float_t forward,Float_t back,Float_t x,Float_t y,Int_t color) {
    TPad*pad=new TPad("c1", "A canvas", .0,.0, 1., 1.);
    pad->SetFillColor(0);
    pad->SetFillStyle(0);
    pad->Draw("N");
    pad->cd();
    TImage*img=TImage::Open("h1red/disputation.jpg");
    img->Draw();

    /*
    Float_t bang=180-back;

    Int_t fillStyle=3399;
    Int_t lineColor=kWhite;
    //backword shadin
    TArc*arc=new TArc(x,y,1.-x,-1*bang,bang);
    arc->SetFillStyle(fillStyle);
    arc->SetFillColor(color);
    arc->SetLineColor(lineColor);
    arc->Draw("only");
    //forward shadin
    arc=new TArc(x,y,x,180-forward,180+forward);
    arc->SetFillStyle(fillStyle);
    arc->SetFillColor(color);
    arc->SetLineColor(lineColor);
    arc->Draw("only");
    */

    return pad;
}

TPad*padPhi() {
    TString arrOpt="-|>";
    Float_t arrSize=0.02;
    Int_t lineWidth=3;
    TPad*pad=new TPad("c1", "A canvas", .0,.0, 1., 1.);
    pad->Draw("N");
    pad->cd();
    TArc*arc=new TArc(.5,.5,.4); arc->SetLineWidth(lineWidth); arc->Draw();
    arc=new TArc(.5,.5,.05,0,154); arc->SetLineWidth(lineWidth); arc->SetFillColor(kRed); arc->Draw();
    TArrow*arrow=new TArrow(.5,.5,.5,1.0,arrSize,arrOpt); arrow->SetLineWidth(lineWidth); arrow->Draw();//j1
    arrow=new TArrow(.5,.5,.3,.0,arrSize,arrOpt); arrow->SetLineWidth(lineWidth); arrow->Draw();//j2
    arrow=new TArrow(.5,.5,.3,.59,arrSize,"-|>"); arrow->SetLineWidth(lineWidth); arrow->SetFillColor(kWhite); arrow->Draw();//pseudo
    arrow=new TArrow(.5,.5,1.,.5,arrSize,arrOpt); arrow->SetLineWidth(lineWidth); arrow->Draw();//j3
    TLatex t;
    //    t.SetTextAlign(22);
    t.SetTextSize(0.1);
    t.DrawLatex(.6,.95,"jet1");
    t.DrawLatex(.45,.0,"jet2");
    t.DrawLatex(.01,.45,"pseudojet");
    t.DrawLatex(.97,.6,"jet3");
    t.SetTextSize(0.1);

    arrow=new TArrow(.97,.03,.80,.03,.02); arrow->Draw();  t.DrawLatex(.75,.06,"x");
    arrow=new TArrow(.97,.03,.97,.20,.02); arrow->Draw();  t.DrawLatex(.97,.25,"y");

    t.SetTextColor(kRed);
    t.SetTextSize(0.15);
    t.DrawLatex(.52,.58,"#Delta#phi");

    return pad;

}


TPad*padLadder() {
    TPad*pad=new TPad("c1", "A canvas", .0,.0, 1., 1.);
    pad->Draw("N");
    pad->cd();

    Float_t lineWidth=1;
    TString arrOpt="->-";
    Float_t arrSize=0.01;
    Float_t verRadius=0.007;
    Float_t objRadius=0.04;
    Float_t objRadihus=0.02;
    Float_t objDelta=0.01;
    Float_t objDiverge=0.03;

    Int_t linsav = gStyle->GetLineWidth();
    gStyle->SetLineWidth(lineWidth);

    //frame
    Float_t x0=0.3;
    Float_t x1=0.6;
    Float_t y0=0.05;
    Float_t y1=0.95;

    //electron&proton
    Float_t vEx,vEy,vPx,vPy;
    vEx=vPx=0.4;
    vEy=0.9;
    vPy=0.1;


    Float_t v0x=0.45;
    Float_t v1x=0.45;
    Float_t v2x=0.44;
    Float_t v3x=0.43;
    Float_t v4x=0.42;
    Float_t v5x=0.41;

    Float_t v0y=0.82; 
    Float_t v1y=0.70; 
    Float_t v2y=0.58; 
    Float_t v3y=0.46; 
    Float_t v4y=0.34; 
    Float_t v5y=0.22; 



    TArrow*f=new TArrow();
    TArc*arc=new TArc();   
    TEllipse*ell=new TEllipse();
    TCurlyLine*cl=new TCurlyLine();
    TLatex t;
    t.SetTextAlign(22);
    t.SetTextSize(0.08);


    //label
    f=new TArrow(x1+0.05,v5y,x1+0.05,v2y,arrSize,"->"); f->Draw();
    t.DrawLatex(x1+0.2,v3y,"DGLAP");
    t.DrawLatex(x1+0.2,v4y,"CCFM");

    
    //ELECTRON
    f=new TArrow(x0,y1,vEx,vEy,arrSize,arrOpt); f->Draw();
    f=new TArrow(vEx,vEy,x1,y1,arrSize,arrOpt); f->Draw();
    arc=new TArc(vEx,vEy,verRadius); arc->SetFillColor(kBlack); arc->Draw();
    t.DrawLatex((x0+vEx)/2,y1-0.07,"e");

    //PHOTON
    cl=new TCurlyLine(vEx,vEy,v0x,v0y); cl->SetWavy(); cl->Draw();
    arc=new TArc(v0x,v0y,verRadius); arc->SetFillColor(kBlack); arc->Draw();

    //quark box
    f=new TArrow(x1,v0y,v0x,v0y,arrSize,arrOpt); f->Draw();
    f=new TArrow(v0x,v0y,v1x,v1y,arrSize,arrOpt); f->Draw();
    f=new TArrow(v1x,v1y,x1,v1y,arrSize,arrOpt); f->Draw();

    //gluon
    //    cl=new TCurlyLine(v0x,v1y,vPx,vPy); cl->Draw();
    cl=new TCurlyLine(vPx,vPy,v5x,v5y); cl->Draw();
    cl=new TCurlyLine(v5x,v5y,v4x,v4y); cl->Draw();
    cl=new TCurlyLine(v4x,v4y,v3x,v3y); cl->Draw();
    cl=new TCurlyLine(v3x,v3y,v2x,v2y); cl->Draw();
    cl=new TCurlyLine(v2x,v2y,v1x,v1y); cl->Draw();

    cl=new TCurlyLine(v5x,v5y,x1,v5y); cl->Draw();
    cl=new TCurlyLine(v4x,v4y,x1,v4y); cl->Draw();
    cl=new TCurlyLine(v3x,v3y,x1,v3y); cl->Draw();
    cl=new TCurlyLine(v2x,v2y,x1,v2y); cl->Draw();

    arc=new TArc(v5x,v5y,verRadius); arc->SetFillColor(kBlack); arc->Draw();
    arc=new TArc(v4x,v4y,verRadius); arc->SetFillColor(kBlack); arc->Draw();
    arc=new TArc(v3x,v3y,verRadius); arc->SetFillColor(kBlack); arc->Draw();
    arc=new TArc(v2x,v2y,verRadius); arc->SetFillColor(kBlack); arc->Draw();
    arc=new TArc(v1x,v1y,verRadius); arc->SetFillColor(kBlack); arc->Draw();

    //PROTON
    //initial
    f=new TArrow(x0,y0,vPx,vPy,arrSize,arrOpt); f->Draw();
    f=new TArrow(x0,y0+objDelta,vPx,vPy+objDelta,arrSize,arrOpt); f->Draw();
    f=new TArrow(x0,y0-objDelta,vPx,vPy-objDelta,arrSize,arrOpt); f->Draw();
    
    //final
    f=new TArrow(vPx,vPy,x1,y0,arrSize,arrOpt); f->Draw();
    f=new TArrow(vPx,vPy-objDelta,x1,y0-objDiverge,arrSize,arrOpt); f->Draw();
    f=new TArrow(vPx,vPy+objDelta,x1,y0+objDiverge,arrSize,arrOpt); f->Draw();

    ell=new TEllipse(vPx,vPy,objRadihus,objRadius); ell->SetFillColor(kBlack); ell->Draw();
    t.DrawLatex((x0+vPx)/2.,y0/2.,"p");


    gStyle->SetLineWidth(linsav);
    return pad;
}


TPad*padDIS(Bool_t withMass=kTRUE,Bool_t withX=kTRUE) {

    TPad*pad=new TPad("c1", "A canvas", .0,.0, 1., 1.);
    pad->Draw("N");
    pad->cd();

    Float_t lineWidth=2;
    TString arrOpt="->-";
    Float_t arrSize=0.01;
    Float_t verRadius=0.007;
    Float_t objRadius=0.04;
    Float_t objRadihus=0.02;
    Float_t objDelta=0.01;
    Float_t objDiverge=0.03;

    Int_t linsav = gStyle->GetLineWidth();
    gStyle->SetLineWidth(lineWidth);

    Float_t x0,x1,vEx,vPx;
    Float_t y0,y1,vEy,vPy;
    x0=0.2; y0=0.15; x1=0.8; y1=0.85; //frame
    vEx=vPx=0.4;
    vEy=0.8;
    vPy=0.2;

    Float_t v0x,v0y; //photon coordinated 
    v0x=v0y=0.5;

    TArrow*arrow=new TArrow();
    TArc*arc=new TArc();   
    TEllipse*ell=new TEllipse();
    TCurlyLine*cl=new TCurlyLine();
    TLatex t;
    t.SetTextAlign(22);
    t.SetTextSize(0.08);

    if (withMass) {
	//s
	ell=new TEllipse(.5,.5,.3,.6,150,210); ell->SetLineWidth(lineWidth); ell->SetLineStyle(2); ell->Draw();
	ell=new TEllipse(.5,.5,.29,.59,150,210); ell->SetLineColor(kWhite); ell->SetLineWidth(lineWidth+1); ell->Draw();
	t.DrawLatex(x0-0.03,0.5,"s");
	
	//W
	ell=new TEllipse(.55,.3,.3,.6,-25,25); ell->SetLineWidth(lineWidth); ell->SetLineStyle(2); ell->Draw();
	ell=new TEllipse(.55,.3,.29,.59,-25,25); ell->SetLineColor(kWhite); ell->SetLineWidth(lineWidth+1); ell->Draw();
	t.DrawLatex(x1+0.1,0.3,"W");
	
	//Q^2
	//	ell=new TEllipse(vEx,vEy,.1,.1,20,150); ell->SetLineWidth(lineWidth); ell->SetLineStyle(2); ell->Draw();
	//	ell=new TEllipse(vEx,vEy,.09,.09,20,150); ell->SetLineColor(kWhite); ell->SetLineWidth(lineWidth+1); ell->Draw();
	t.DrawLatex(v0x,0.7,"Q^{2}");

	//xP
    }

    if (withX) {
	t.DrawLatex(0.7,0.45,"(xP)");
	t.DrawLatex(vEx-0.03,0.75,"y");
    }

    
    //ELECTRON
    arrow=new TArrow(x0,y1,vEx,vEy,arrSize,arrOpt); arrow->Draw();
    arrow=new TArrow(vEx,vEy,x1,y1,arrSize,arrOpt); arrow->Draw();
    arc=new TArc(vEx,vEy,verRadius); arc->SetFillColor(kBlack); arc->Draw();
    t.DrawLatex((x0+vEx)/2.-0.1,y1+0.07,"e(k)");
    t.DrawLatex(x0+vEx,y1+0.05,"e'(k')");
    //PROTON
    //initial
    arrow=new TArrow(x0,y0,vPx,vPy,arrSize,arrOpt); arrow->Draw();
    arrow=new TArrow(x0,y0+objDelta,vPx,vPy+objDelta,arrSize,arrOpt); arrow->Draw();
    arrow=new TArrow(x0,y0-objDelta,vPx,vPy-objDelta,arrSize,arrOpt); arrow->Draw();
    //final
    arrow=new TArrow(vPx,vPy,x1,y0,arrSize,arrOpt); arrow->Draw();
    arrow=new TArrow(vPx,vPy+objDelta,v0x,v0y,arrSize,arrOpt); arrow->Draw();
    arrow=new TArrow(v0x,v0y,x1,v0y,arrSize,arrOpt); arrow->Draw();
    arrow=new TArrow(vPx,vPy-objDelta,x1,y0-objDiverge,arrSize,arrOpt); arrow->Draw();
    ell=new TEllipse(vPx,vPy,objRadihus,objRadius); ell->SetFillColor(kBlack); ell->Draw();
    t.DrawLatex((x0+vPx)/2.,y0/2.,"p(P)");
    //PHOTON
    cl=new TCurlyLine(vEx,vEy,v0x,v0y); cl->SetWavy(); cl->Draw();
    arc=new TArc(v0x,v0y,verRadius); arc->SetFillColor(kBlack); arc->Draw();
    t.DrawLatex(vEx-.05,vEy-.2,"#gamma,Z^{0}(q)");
    //LABELS



    gStyle->SetLineWidth(linsav);
    return pad;

}

TPad*padFeynman(TString name)
{
    TPad*pad=new TPad("c1", "A canvas", .0,.0, 1., 1.);
    pad->Draw("N");
    pad->cd();

    Float_t lineWidth=1.5;
    TString arrOpt="-|>-";
    Float_t arrSize=0.006;
    Float_t verRadius=0.007;
    Float_t objRadius=0.04;
    Float_t objRadihus=0.02;
    Float_t objDelta=0.01;
    Float_t objDiverge=0.03;

    Int_t linsav = gStyle->GetLineWidth();
    gStyle->SetLineWidth(lineWidth);

    Float_t x0,x1,vEx,vPx;
    Float_t y0,y1,vEy,vPy;
    x0=0.2; y0=0.1; x1=0.8; y1=0.9; //frame
    vEx=vPx=0.4;
    vEy=0.8;
    vPy=0.2;

    Float_t v0x,v0y; //photon coordinated 

    TArrow*arrow=new TArrow();
    TArc*arc=new TArc();   
    TEllipse*ell=new TEllipse();
    TCurlyLine*cl=new TCurlyLine();
    TLatex t;
    t.SetTextAlign(22);
    t.SetTextSize(0.1);


    if (!name.CompareTo("direct")) {
	v0x=0.45; v0y=0.60;
	Float_t quVx=0.45;
	Float_t quVy=0.40;

	//	arc=new TArc(quVx,quVy,verRadius); quVer->SetFillColor(kBlack); arc->Draw();
	//QUARK
	arrow=new TArrow(x1,v0y,v0x,v0y,arrSize,arrOpt); arrow->Draw();
	arrow=new TArrow(v0x,v0y,quVx,quVy,arrSize,arrOpt); arrow->Draw();
	arrow=new TArrow(quVx,quVy,x1,quVy,arrSize,arrOpt); arrow->Draw();
	//QLUON
	cl=new TCurlyLine(quVx,quVy,vPx,vPy); cl->Draw();

    } else if (name.Contains("3")) {
	
	v0x=0.45;v0y=0.65;
	Float_t quVx=0.46,glVx=0.45;
	Float_t quVy=0.50,glVy=0.35;
	
	arc=new TArc(quVx,quVy,verRadius); arc->SetFillColor(kBlack); arc->Draw();
	arc=new TArc(glVx,glVy,verRadius); arc->SetFillColor(kBlack); arc->Draw();
	
	//QUARK
	arrow=new TArrow(v0x,v0y,quVx,quVy,arrSize,arrOpt); arrow->Draw();
	arrow=new TArrow(quVx,quVy,x1,quVy,arrSize,arrOpt); arrow->Draw();
	arrow=new TArrow(x1,v0y,v0x,v0y,arrSize,arrOpt); arrow->Draw();
	//QLUONS
	cl=new TCurlyLine(quVx,quVy,glVx,glVy); cl->Draw();
	cl=new TCurlyLine(glVx,glVy,x1,glVy); cl->Draw();
	cl=new TCurlyLine(glVx,glVy,vPx,vPy); cl->Draw();
	
	
    } else if (name.Contains("katja")) {
	Float_t v2x,v3x,v4x;
	Float_t v2y,v3y,v4y;
	v0x=v4x=0.45;
	v2x=v3x=.46;
	v0y=.7;
	v2y=.55;
	v3y=.45;
	v4y=.35;
	arc=new TArc(v2x,v2y,verRadius); arc->SetFillColor(kBlack); arc->Draw();
	arc=new TArc(v3x,v3y,verRadius); arc->SetFillColor(kBlack); arc->Draw();
	arc=new TArc(v4x,v4y,verRadius); arc->SetFillColor(kBlack); arc->Draw();
	//GLUON
	cl=new TCurlyLine(v0x,v0y,v2x,v2y); cl->Draw();
	//QUARK
	arrow=new TArrow(x1,v2y,v2x,v2y,arrSize,arrOpt); arrow->Draw();
	arrow=new TArrow(v2x,v2y,v3x,v3y,arrSize,arrOpt); arrow->Draw();
	arrow=new TArrow(v3x,v3y,x1,v3y,arrSize,arrOpt); arrow->Draw();
	//QLUONS
	cl=new TCurlyLine(v3x,v3y,v4x,v4y); cl->Draw();
	cl=new TCurlyLine(v4x,v4y,x1,v4y); cl->Draw();
	cl=new TCurlyLine(v4x,v4y,vPx,vPy); cl->Draw();
	
    } else if (name.Contains("thomas")) {
	Float_t v1x,v2x,v3x,v4x;
	Float_t v1y,v2y,v3y,v4y;
	v0x=0.45;
	v1x=v2x=0.5;
	v3x=v4x=0.6;

	v0y=0.7;
    	    v3y=0.60;
	v1y=0.55;
	v2y=0.35;
	    v4y=0.30;
      //vPy=0.2

	arc=new TArc(v1x,v1y,verRadius); arc->SetFillColor(kBlack); arc->Draw();
	arc=new TArc(v2x,v2y,verRadius); arc->SetFillColor(kBlack); arc->Draw();
	arc=new TArc(v3x,v3y,verRadius); arc->SetFillColor(kBlack); arc->Draw();
	arc=new TArc(v4x,v4y,verRadius); arc->SetFillColor(kBlack); arc->Draw();
	//SECOND INTERACTION
	arrow=new TArrow(vPx,vPy,v4x,v4y,arrSize,arrOpt); arrow->Draw(); arrow->SetLineColor(kRed); 
	arrow=new TArrow(v4x,v4y,v3x,v3y,arrSize,arrOpt); arrow->Draw(); arrow->SetLineColor(kRed); 
	arrow=new TArrow(v3x,v3y,x1,v3y,arrSize,arrOpt); arrow->Draw(); arrow->SetLineColor(kRed); 
	cl=new TCurlyLine(v0x,v0y,v3x,v3y); cl->Draw(); cl->SetLineColor(kRed); 
	cl=new TCurlyLine(v4x,v4y,x1,v4y); cl->Draw(); cl->SetLineColor(kRed); 
	//FIRST INTERACTION
	cl=new TCurlyLine(vPx,vPy,v2x,v2y); cl->Draw(); cl->SetLineColor(kBlue); 
	cl=new TCurlyLine(x1,v1y,v1x,v1y); cl->Draw(); cl->SetLineColor(kBlue); 
	arrow=new TArrow(v0x,v0y,v1x,v1y,arrSize,arrOpt); arrow->Draw(); arrow->SetLineColor(kBlue); 
	//	arrow=new TArrow(x1,v1y,v1x,v1y,arrSize,arrOpt); arrow->Draw();
	arrow=new TArrow(v1x,v1y,v2x,v2y,arrSize,arrOpt); arrow->Draw(); arrow->SetLineColor(kBlue); 
	arrow=new TArrow(v2x,v2y,x1,v2y,arrSize,arrOpt); arrow->Draw(); arrow->SetLineColor(kBlue); 


    } else {
	Error("PadFeynman","%s undefined",name.Data());
    }


    
    //ELECTRON
    arrow=new TArrow(x0,y1,vEx,vEy,arrSize,arrOpt); arrow->Draw();
    arrow=new TArrow(vEx,vEy,x1,y1,arrSize,arrOpt); arrow->Draw();
    arc=new TArc(vEx,vEy,verRadius); arc->SetFillColor(kBlack); arc->Draw();
    t.DrawLatex((x0+vEx)/2.,y1,"e^{-}");
    //PROTON
    arrow=new TArrow(x0,y0,vPx,vPy,arrSize,arrOpt); arrow->Draw();
    arrow=new TArrow(x0,y0+objDelta,vPx,vPy+objDelta,arrSize,arrOpt); arrow->Draw();
    arrow=new TArrow(x0,y0-objDelta,vPx,vPy-objDelta,arrSize,arrOpt); arrow->Draw();
    arrow=new TArrow(vPx,vPy,x1,y0,arrSize,arrOpt); arrow->Draw();
    arrow=new TArrow(vPx,vPy+objDelta,x1,y0+objDiverge,arrSize,arrOpt); arrow->Draw();
    arrow=new TArrow(vPx,vPy-objDelta,x1,y0-objDiverge,arrSize,arrOpt); arrow->Draw();
    ell=new TEllipse(vPx,vPy,objRadihus,objRadius); ell->SetFillColor(kBlack); ell->Draw();
    t.DrawLatex((x0+vPx)/2.,y0/2.,"p");
    //PHOTON
    cl=new TCurlyLine(vEx,vEy,v0x,v0y); cl->SetWavy(); cl->Draw();
    arc=new TArc(v0x,v0y,verRadius); arc->SetFillColor(kBlack); arc->Draw();
    if (name.Contains("res")) {
	arrow=new TArrow(v0x,v0y+objDelta,x1,v0y+2*objDiverge,arrSize,arrOpt); arrow->Draw();
	arrow=new TArrow(v0x,v0y,x1,v0y+objDiverge,arrSize,arrOpt); arrow->Draw();
	ell=new TEllipse(v0x,v0y,objRadihus,objRadius); ell->SetFillColor(kBlack); ell->Draw();
	t.DrawLatex(v0x-.04,v0y-.07,"x_{#gamma}");
    } else {
	t.DrawLatex(vEx-.04,vEy-.07,"y");
    }   
    //LABELS

    gStyle->SetLineWidth(linsav);
    return pad;

}





/*
K4Pad*padComp(K3Ana*a,TString sample,TString vars,TString norm,Int_t logy=0,Int_t logx=0,TString legend="") {
    //K4Stack*stackComp(K3Ana*a,TString sample,TString var,TString norm,TString legend="",Int_t logy=0,Int_t logx=0) 
    //    cout<<"padComp for "<<vars<<endl;
    K4Pad*pad=new K4Pad();
    TString var;
    Int_t i=0;
    K4Stack*stack=new K4Stack();
    do {
	//	var=K4Stack::TakeString(vars,i);
	var=stack->TakeString(vars,i);
	if (!var.CompareTo("")) break;
	K4Stack*k=stackComp(a,sample,var,norm,logy,logx,legend); 
	pad->Add(k);
	++i;
    } while (1);
    delete stack;
    return pad;
}


K4Pad*padRatio(K3Ana*a,TString sample,TString vars,TString norm="lumi",TString legend="",Int_t logy=0,Int_t logx=0) {
    //K4Stack*stackRatio(K3Ana*a,TString sample,TString var,TString norm,TString legend="") 
    K4Pad*pad=new K4Pad();
    TString var;
    Int_t i=0;
    do {
	var=K4Stack::TakeString(vars,i);
	if (!var.CompareTo("")) break;
	K4Stack*k=stackRatio(a,sample,var,norm,legend); 
	pad->Add(k);
	++i;
    } while (1);
    return pad;
}



K4Pad*padCPS(K3Ana*a,TString sample,TString vars,Int_t logy=0,Int_t logx=0,TString legend="") {
    //K4Stack*stackCPS(K3Ana*a,TString sample,TString var,Int_t legend=3,Int_t logy=0,Int_t logx=0) 
    K4Pad*pad=new K4Pad();
    TString var;
    Int_t i=0;
    K4Stack*stack=new K4Stack();
    do {
	//	var=K4Stack::TakeString(vars,i);
	var=stack->TakeString(vars,i);
	if (!var.CompareTo("")) break;
	K4Stack*k=stackCPS(a,sample,var,logy,logx,legend); 
	pad->Add(k);
	++i;
    } while (1);
    delete stack;
    return pad;
}

K4Pad*padBias(K3Ana*a,TString sample,TString vars,TString legend="",Int_t logy=0,Int_t logx=0) {
    //K4Stack*stackCPS(K3Ana*a,TString sample,TString var,Int_t legend=3,Int_t logy=0,Int_t logx=0) 
    K4Pad*pad=new K4Pad();
    TString var;
    Int_t i=0;
    do {
	var=K4Stack::TakeString(vars,i);
	if (!var.CompareTo("")) break;
	K4Stack*k=stackBias(a,sample,var,legend,logy,logx); 
	pad->Add(k);
	++i;
    } while (1);
    return pad;
}


K4Pad*padSyst(K3Ana*a,TString vars) {
    //    cout<<"padSyst for "<<vars<<endl;
    //K4Stack*stackSyst(K3Ana*a,TString var)
    K4Pad*pad=new K4Pad();
    TString var;
    Int_t i=0;
    do {
	var=K4Stack::TakeString(vars,i);
	if (!var.CompareTo("")) break;
	K4Stack*k=stackSyst(a,var); 
	pad->Add(k);
	++i;
    } while (1);
    return pad;
}

*/
