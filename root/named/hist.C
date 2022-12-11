void histRemoveZeroes(TH1*h) {
    Int_t n=h->GetNbinsX();
    Double_t content;
    for (Int_t bin=1;bin<=n;++bin) {
	content=h->GetBinContent(bin);
	if (content==0.) {
	    h->SetBinContent(bin,1);
	    //	    h->SetBinError(bin,1);
	}
    } 
}


void histColorize(TH1*h,TString&option,Int_t color=1,Int_t line=1) {
    Int_t fillStyle=3809;//,lineWidth=2;
    fillStyle=3006;
    Float_t markerSize=0.7;

    if (!h) {
	//	Error("histColorize","h==0");
	return;
    }

    cout<<"."<<flush;

    TString z=h->GetZaxis()->GetTitle();
    TString title=h->GetTitle();
    TString name=h->GetName();
    if (name.Contains("pause")) return;

    option="][";
    option="";

    Bool_t bias,data,pythia,herwig,django,cascade;
    Bool_t inclusive,combined,direct,resolved;
    Bool_t up,down,background,art;
    if (z.BeginsWith("d")) data=kTRUE;
    if (title.EndsWith(",")) bias=kTRUE;
    if (z.BeginsWith("p")) pythia=kTRUE;
    if (z.BeginsWith("j")) django=kTRUE;
    if (z.BeginsWith("h")) herwig=kTRUE;
    if (z.BeginsWith("c")) cascade=kTRUE;
    if (z.EndsWith("i")) inclusive=kTRUE;
    if (z.EndsWith("c")) combined=kTRUE;
    if (z.EndsWith("d")) direct=kTRUE;
    if (z.EndsWith("r")) resolved=kTRUE;
    if (z.EndsWith("u")) up=kTRUE;
    if (z.EndsWith("d")) down=kTRUE;
    if (z.EndsWith("g")) background=kTRUE;
    if (title.Contains("artificial")) art=kTRUE;

    if (name.EndsWith("+")) up=kTRUE;
    if (name.EndsWith("-")) down=kTRUE;

    if (art) {
	;
    } else if (data) {
	h->SetLineStyle(1);
	if (up||down) {
	    //	    option+="HIST,L,][";
	    option+="HIST,][";
	    h->SetLineWidth(0);
	    if (up) {
		//	    if (down) {
		h->SetTitle("en.sc.unc.");
		//		h->SetLineStyle(2);
	    } else {
		h->SetTitle("");
		//		h->SetLineStyle(3);
	    }
	    
	    //	    h->SetLineColor(kMagenta);
	    if (up) {
	    //	    if (down) {
		//		h->SetLineWidth(1);
		h->SetLineColor(ENERGY_COLOR);
		h->SetFillColor(ENERGY_COLOR);
		//		h->SetFillStyle(fillStyle);
	    } else {
		//		h->SetLineWidth(1);
		h->SetLineColor(10);
		h->SetFillColor(10);
		//		h->SetFillStyle(0);
	    }

	} else {
	    option+="PE1";
	    h->SetMarkerStyle(kFullCircle);
	    h->SetMarkerSize(markerSize);
	    if (background||bias) h->SetMarkerStyle(BACKGROUND_MARKER_STYLE);
	    else h->SetLineWidth(1);

	}
    } else {//should be monte carlo
	Int_t l;
	if (line>4) l=1;
	else if (line>2) l=1;
	else l=2;
	h->SetLineWidth(l);

	Int_t lineStyle=line;
	while (lineStyle>3) lineStyle=lineStyle-3;	
	h->SetLineStyle(lineStyle);


	option+=MC_DRAW_OPTION;
	//	option+="E1";
	//	option+="][";
	if (name.EndsWith("pause")) {
	    ;
	} else if (cascade) {
	    h->SetLineColor(color);
	    //	    h->SetFillColor(color);
	    //	    h->SetFillStyle(fillStyle);
	} else if (pythia) {
	    if (inclusive||direct||resolved) {
		h->SetLineColor(color);
	    } else if (combined) {
		h->SetLineColor(color);
		//		h->SetFillColor(color);
		//		h->SetFillStyle(fillStyle);
	    } else Error("histColorize;pythia","<%s><%s><%s>",name.Data(),title.Data(),z.Data());
	} else if (herwig) {
	    h->SetLineColor(color);
	} else {
	    Error("histColorize","<%s><%s><%s>",name.Data(),title.Data(),z.Data());
	    //	    h->Dump();
	}
    } 
}




void histNormalize(K3Ana*a,TH1F*h,TString norm) {
    if (!norm.CompareTo("no")) {;
    } else if (!norm.CompareTo("/data")) {;
    } else if (!norm.CompareTo("one")) {
	a->Norm(h,1.0);
    } else if (!norm.CompareTo("lumi")) {
	a->Norm(h,"lumi");
    } else if (!norm.CompareTo("bin")) {
	a->Norm(h,1.0);
	a->Norm(h,"bin");
    } else if (!norm.CompareTo("diff")) {
	a->Norm(h,"lumi");
	a->Norm(h,"bin");
    } else if (!norm.CompareTo("sigma")) {
	a->Norm(h,"lumi");
	Float_t sigma=h->Integral();
	a->Norm(h,"bin");
	if (sigma>0.) h->Scale(1./sigma);
	else ;//Error("histNormalize","sigma =%f",sigma);
    } else Error("histNormalize","Unforseen norm string %s",norm.Data());
}














TH2F*hist2d(K3Ana*a,TString samples,TString var,TString option="box",Int_t logx=0,Int_t logy=0)
{
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
	    h=a->Hist2Plus(var,dir,res,var+"_correlation","correlation");
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
	    //	    h->SetXTitle(var);
	    //	    h->SetYTitle(symbol);
	}

	//	stackColorize(h,sample);
	//	h->SetFillStyle(0);
	


	i++;
	first=kFALSE;

    } while(1);

    return h;
}
