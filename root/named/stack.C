/*
  K4Stack manipulator
*/

void stackSample(TString sub,TString&dir,TString&res,Bool_t&ismc,Bool_t&issim,Bool_t&isgas,Bool_t&iscomb,Bool_t&isdir,Bool_t&isres,Bool_t&isincl,Bool_t&iscorr,Bool_t&isgen,Bool_t&iserror,Int_t&generator)
{
    dir=res="";
    TString sam=sub;
    sam.ToLower();
    //    TString mid=sam(1,1);
    TString mid=sub(1,1);

    
    generator=0;
    iserror=kFALSE;
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

    if (sam.EndsWith("d")) isdir=kTRUE;
    if (sam.EndsWith("r")) isres=kTRUE;
    if (sam.EndsWith("i")) isincl=kTRUE;
    
    if (sub.BeginsWith("D")) iscorr=kTRUE;
    else iscorr=kFALSE;
    
    if (rIsLower(sub)) isgen=kFALSE;
    else isgen=kTRUE;

    
    //    cout<<"."<<flush;
    //    cout<<"sub,dir,res,ismc,issim,isgas,iscomb,isdir,isres,isincl,iscorr,isgen,iserror"<<endl;
    //    cout<<sub<<dir<<res<<ismc<<issim<<isgas<<iscomb<<isdir<<isres<<isincl<<iscorr<<isgen<<iserror<<" "<<generator<<endl;
}

K4Stack*stackProject(K3Ana*a,TString sample,TString var,Int_t proj=0,
		     TString norm="no",TString legend="",Int_t logy=0,Int_t logx=0) 
{
    TH2F*h2=a->GetHi2(var,sample);
    TH2F*h2NonEP=a->GetHi2(var+"NonEP",sample);
    TH1F*h1=(TH1F*)h2->ProjectionX(Form("name%d",proj),proj+1,proj+2,"PE1");
    TH1F*h1NonEP=(TH1F*)h2NonEP->ProjectionX(Form("nameNonEP%d",proj),proj+1,proj+2,"PE1");
    h1->SetMarkerStyle(kFullCircle);
    h1->SetMarkerSize(0.7);
    h1NonEP->Scale(1.000/0.033);
    h1NonEP->SetMarkerStyle(kOpenTriangleUp);
    h1NonEP->SetMarkerSize(0.7);
    /*
    if (!BLACK_AND_WHITE) {
	h1NonEP->SetMarkerColor(kBlue);
	h1NonEP->SetLineColor(kBlue);
    }
    */
    h1NonEP->SetTitle("pilots");
    TString title=Form("%d-jet sample",proj);
    K4Stack*s=new K4Stack(var,title.Data(),norm);
    s->Hapi(h1);
    s->Hapi(h1NonEP);
    s->Logy(logy);
    return s;
}                  




K4Stack*stackComp(K3Ana*a,TString sample,TString var,TString norm="no",Int_t logy=0,Int_t logx=0,TString legend="",TString newx="no") 
{// this  is to deal a particular histogram put all levels in 
    //    cout<<"stackComp for "<<var<<endl;

    
    Float_t scale,pySc,ppSc,heSc,bgSc,caSc,cbSc;
    Float_t resScale,pyRes,ppRes,heRes,caRes,cbRes;

    pySc=ppSc=heSc=caSc=cbSc=scale=1;
    pyRes=ppRes=heRes=caRes=cbRes=resScale=1;

    bgSc=1./0.033;
    bgSc=31;    
    bgSc=41;    

    
    pySc=3.5;
    pySc=3;
    pySc=2.5;
    pySc=2.3;
    pySc=2;
    pySc=1.9;
    pySc=1.8;
    pySc=1.7;
    pySc=1.6;
    pySc=1.5;
    pySc=1.3;
    pySc=1;
    pySc=1.4;
    pySc=1.5;
    //    pySc=0.5;
    //    pyRes=3;

    ppSc=1.3;
    ppSc=1.2;
    ppSc=1.4;
    ppSc=1.5;


    heSc=1.5;
    heSc=1.7;
    heSc=1.8;
    heSc=1.9;

    caSc=1.6;
    caSc=1.5;
    caSc=1.7;
    caSc=1.7;

    cbSc=1.9;

    Bool_t ismc,issim,isgas,iscomb,isdir,isres,isincl,iscorr,isgen,iserror;
    Int_t i=0,generator=0;
    TString sub,directSampleName,resolvedSampleName,ing,title;
    TObjArray histograms;
    K4Stack*k=new K4Stack(); 
    do {

	sub=k->TakeString(sample,i++);
	if (!sub.CompareTo("")) break;

	stackSample(sub,directSampleName,resolvedSampleName,ismc,issim,isgas,iscomb,isdir,isres,isincl,iscorr,isgen,iserror,generator);
	if (isgen) ing="Gen";
	else ing="";
	sub.ToLower();

	scale=1;
	resScale=1;
	title="Pythia";

	if (issim&&ismc) { 
	    scale=pySc; 
	    resScale=pyRes; 
	} else if (generator==1) {
	    scale=ppSc; 
	    resScale=ppRes;
	    if (sub.Contains("n")||sub.Contains("g")) {
		title="Pythia";
	    } else {
		if (sub.Contains("pp")) title+=" +";
		else if (sub.Contains("pm")) title+=" -";
		//		else if (sub.Contains("b")) title+=" GRV";
		else if (sub.Contains("b")) title+=" MI";
		else if (sub.Contains("l")) title+=" SAS";
		else title+="MI";
	    }
	} else if (generator==2) {
	    scale=heSc; 
	    resScale=heRes;
	    title="Herwig";
	    //	    if (sub.Contains("n")) title+=" w/o MI";
	    if (!sub.Contains("n")) title+="MI";
	} else if (generator==3) {
	    scale=caSc; 
	    resScale=caRes;
	    title="Cascade"; 
	} else if (generator==4) {
	    scale=cbSc; 
	    resScale=cbRes;
	    title="Cascade"; 
	} else {;}

	if (iserror) {//systematic error
	    histograms.Add(a->HistCorrectedError("do6",var,"py",scale,resScale,"+"));
	    histograms.Add(a->HistCorrectedError("do6",var,"py",scale,resScale,"-"));
	} else if (iscorr) {//corrected data
	    histograms.Add(a->HistCorrectedData(sub,var,"py",scale,resScale,""));//c.K3Base.h for options
	    //	    histograms.Add(a->HistCorrectedData(sub,var,"py",scale,resScale,"",kTRUE));//c.K3Base.h for options
	} else if (iscomb) {//add direct and resolved
	    histograms.Add(a->HistPlus(var,directSampleName,resolvedSampleName,sub,
				       //Form("%s*%3.2f",sub.Data(),scale),
				       title,ing,scale,resScale)); 
	} else if (isgas) {//beam gas data
	    TH1F*bg=a->GetHi(var+"NonEP","do6","",bgSc);
	    bg->SetTitle("non-ep");
	    bg->SetZTitle("dbg");
	    histograms.Add(bg);
	} else {//data,mc
	    if (issim) {
		if (isres) {
		    scale=pySc;
		    if (isres) {
			scale*=pyRes;
		    }
		}
	    } else if (isincl) {
		if (generator==1) {
		    scale=ppSc;
		    resScale=ppRes;
		} else if (generator=2) {
		    ;
		} else if (generator=3) {
		    scale=caSc;
		    resScale=caRes;
		}
	    } else {;}

	    histograms.Add(a->GetHi(var,sub,ing,scale));
	}
    } while (1);

    k=stackTreatHistograms(histograms,a,var,norm,legend,logy,logx,newx);
    return k;
}





K4Stack*stackRatio(K3Ana*a,TString sample,TString var,TString norm,TString legend="",Int_t logy=0,Int_t logx=0) {
    Bool_t showSystematics=kFALSE;
    if (!norm.CompareTo("diff")) showSystematics=kTRUE;

    K4Stack*s=stackComp(a,sample,var,norm);

    s->Legend(legend);
    s->Logy(logy);
    s->Logx(logx);

    //    s->List();
    s->Renorm("ratio to data");
    //    TH1F*data=(TH1F*)s->HistFromSample("do6");



    TH1F*originaldata=s->Provide();
    TH1F*data=0;
    if (originaldata) data=(TH1F*)originaldata->Clone();
    TList*HiList=s->GetHists();

    TString dataname;

    if (!data) {
	if (var.CompareTo("pause")) {
	    Error("stackRatio","ERROR: No data found");
	    s->List();
	}
	return s;
    } else {
	dataname=data->GetName();
	//data->Print("all");
    }
 
    for (Int_t i=0;i<HiList->GetSize();++i) {
	TObject*o=HiList->At(i);	
	TH1*h=(TH1*)o;
	h->Divide(data);
    }

    if (showSystematics) {
	Error("","");
	Error("","\\mytab{|r|r|r|r|}{%s}{%s data}{",dataname.Data(),dataname.Data());
	Error("","\\hline");
	Error("","bin & %s & statistical error,\\\% & systematic error,\\\% \\\\",dataname.Data());
	Error("","\\hline");

	TH1F*plus=s->Provide("+");
	TH1F*minus=s->Provide("-");
	for (Int_t bin=1;bin<h->GetNbinsX()+1;++bin) {
	    Float_t sysplus=plus->GetBinContent(bin)*100.;
	    Float_t sysminus=minus->GetBinContent(bin)*100.;
	    Float_t datacontent=data->GetBinContent(bin);
	    Float_t dataerror=data->GetBinError(bin);
	    if (datacontent>0.) dataerror=100.*dataerror/datacontent;
	    else dataerror=0;
	    Error("","%d & %f & $\\pm$ %4.1f & +%4.1f/-%4.1f \\\\",bin,datacontent,dataerror,sysplus-100.,100.-sysminus);
	}

	Error("","\\hline");
	Error("","}");
    }

    delete data;
    return s;


}




Bool_t stackDrawBalance(K3Ana*a,TString var,Float_t&mean,Float_t&error,TString dName,TString mName) {
    mean=error=0;

    TH1F*data=a->GetHi(var,dName);
    TH1F*mc=a->GetHi(var,mName);

    if (!data||data->GetEntries()==0.||!mc||mc->GetEntries()==0.) return kFALSE;

    //    a->Norm(data,1);
    data->SetMarkerStyle(8);
    data->SetMarkerSize(.5);

    a->Norm(mc,data);
    mc->SetLineColor(kRed);
    mc->SetMarkerStyle(8);
    mc->SetMarkerSize(.5);
    mc->SetMarkerColor(kRed);

    TF1*dataFit=fitBalance(data);
    Float_t dataMean=dataFit->GetParameter(1);
    Float_t dataError=dataFit->GetParError(1);
    TF1*mcFit=fitBalance(mc);
    Float_t mcMean=mcFit->GetParameter(1);
    Float_t mcError=mcFit->GetParError(1);


    if (mcMean>0.&&dataMean>0.) {
	mean=dataMean/mcMean;
	error=mean*sqrt(pow(dataError/dataMean,2)+pow(mcError/mcMean,2));
    }

    /*        
    cout<<"set,mean,error"<<endl;
    cout<<"data: "<<dataMean<<" "<<dataError<<endl;
    cout<<"mc: "<<mcMean<<" "<<mcError<<endl;
    cout<<"data/mc: "<<mean<<" "<<error<<endl;
    */


    gStyle->SetOptStat();    
    mc->Draw("PE1");
    data->Draw("PE1sames");
    gPad->Update();
   
    TPaveStats*st=(TPaveStats*)mc->FindObject("stats");
    if (st) {
	st->SetTextColor(kRed);	st->SetFillStyle(0);
	st->SetLineColor(0);	st->SetLineWidth(0);
	st->SetY1NDC(0.30); 	st->SetY2NDC(0.60);
    }
    st=(TPaveStats*)data->FindObject("stats");
    if (st) {
	st->SetTextColor(kBlack);	st->SetFillStyle(0);
	st->SetLineColor(0);	st->SetLineWidth(0);
	st->SetY1NDC(0.60); 	st->SetY2NDC(0.90); 
    }


}

//STACKS

K4Stack*stackBalance(K3Ana*a,TString var,Float_t&mean,Float_t&error) {

    mean=error=0;

    TH1F*data=a->GetHi(var);
    if (!data||data->GetEntries()==0) return;
    a->Norm(data,1);

    TH1F*mc=a->HistPlus(var,"pyd","pyr","poo","PYTHIA");
    if (!mc||mc->GetEntries()==0) return;
    mc->SetLineColor(kRed);
    a->Norm(mc,1);

    K4Stack*s=new K4Stack(var,var);
    s->Hapi(mc);
    s->Hapi(data);
    
    TF1*dataFit=stackFit(data);
    Float_t dataMean=dataFit->GetParameter(1);
    Float_t dataError=dataFit->GetParError(1);
    TF1*mcFit=stackFit(mc);
    Float_t mcMean=mcFit->GetParameter(1);
    Float_t mcError=mcFit->GetParError(1);
    

    mean=dataMean/mcMean;
    error=mean*sqrt(pow(dataError/dataMean,2)+pow(mcError/mcMean,2));
    
    cout<<"set,mean,error"<<endl;
    cout<<"data: "<<dataMean<<" "<<dataError<<endl;
    cout<<"mc: "<<mcMean<<" "<<mcError<<endl;
    cout<<"data/mc: "<<mean<<" "<<error<<endl;
        


    return s;
    //    mc->Draw();
    //    gPad->Update();
    /*
    TPaveStats*st=(TPaveStats*)mc->FindObject("stats");
    st->SetTextColor(kRed);
    st->SetLineColor(kRed);
    st->SetY1NDC(0.55); //new x start position
    st->SetY2NDC(0.7); //new x end position
    */

    //    data->Draw("sames");
}








K4Stack*stackWithTriggers(K3Ana*a,TString var,TString mcLayer,TString dataLayer,Bool_t leg=kTRUE) {
    K4Stack*s=new K4Stack(var,var);
    TH1F*data=a->GetHi(var,dataLayer);
    TH1F*data74=a->GetHi(var+"_s74",dataLayer);
    TH1F*data76=a->GetHi(var+"_s76",dataLayer);
    TH1F*mc=a->GetHi(var,mcLayer);
    mc->Scale(data->Integral()/mc->Integral());
    s->Hapi(data,0);
    s->Hapi(data74,0);
    s->Hapi(data76,0);
    s->Hapi(mc,0);
    s->Legend(leg);
    return s;
}

K4Stack*stackBg(K3Ana*a,TString var) {
    K4Stack*s=new K4Stack(var,var);
    TH1F*data=a->GetHi(var,"do6");
    TH1F*mc=a->GetHi(var,"poo");
    mc->Scale(data->Integral()/mc->Integral());
    TH1F*bg=a->GetHi(var+"NonEP","do6");
    bg->Scale(1.000/0.033);
    bg->SetLineColor(kBlue);
    bg->SetMarkerColor(kBlue);
    bg->SetTitle("nonepbg");
    TH1F*ratio=rDiv(bg,data,10000,"do6","bg/data");
    ratio->SetLineColor(kGreen);
    s->Hapi(data);
    s->Hapi(mc);
    s->Hapi(bg);
    return s;
}



K4Stack*stackJetEt(K3Ana*a,TString var,TString norm, TString layers) {
    K4Stack*s=new K4Stack(var,norm);
    K4Stack*s1=stackComp(a,var+"1",norm,layers);
    K4Stack*s2=stackComp(a,var+"2",norm,layers);
    K4Stack*s3=stackComp(a,var+"3",norm,layers);
    K4Stack*s4=stackComp(a,var+"4",norm,layers);

    s1->X(var+"^{jet}");

    s->Hapi(s1,100000);
    s->Hapi(s2,1000);
    s->Hapi(s3,10);
    s->Hapi(s4);

    //    s->Norm(norm);
    s->Legend(0);
    return s;
}

K4Stack*stackJetEta(K3Ana*a,TString norm, TString layers) {
    K4Stack*s=new K4Stack("jets eta",norm);
    s->Hapi(a->StackComp("Eta3",norm,layers));
    s->Hapi(a->StackComp("Eta4",norm,layers));
    //    s->Norm(norm);
    s->Legend(0);
    return s;
}




K4Stack*stackCPS(K3Ana*a,TString sample,TString var,Int_t logy=0,Int_t logx=0,TString legend="") {
    TString option="HISTE1";
    option="HIST";

    K4Stack*s=new K4Stack(var,var,"C,P,S");
    s->Legend(legend);
    s->Logy(logy);
    s->Logx(logx);

    TH1F*correction=a->HistMCPlus(var,"detector",sample); 
    TH1F*purity=a->HistMCPlus(var,"purity",sample); 
    TH1F*stability=a->HistMCPlus(var,"stability",sample); 
    //    TH1F*bias=a->HistMCPlus(var,"elsen",sample); 

    cout<<"."<<flush;
    if (correction) { s->Add(correction,option); correction->SetLineStyle(1); }
    if (purity) { s->Add(purity,option); purity->SetLineStyle(2); }
    if (stability) { s->Add(stability,option); stability->SetLineStyle(3); }
    //    if (bias) { s->Add(bias,option); bias->SetLineStyle(4); }

    /*
    TList*list=s->GetHists();
    if (!list) Send("stackCPS",Form("Error: list %d",0));
    Int_t n=s->GetHists()->GetEntries();
    if (n==0) Send("stackCPS",Form("Error: %d histo(s) in stack",n));
    */

    return s;
}

K4Stack*stackBias(K3Ana*a,TString sample,TString var,TString legend="",Int_t logy=0,Int_t logx=0) {
    TString option="HISTE1";
    option="HIST";

    K4Stack*s=new K4Stack(var,"","C,P,S");
    s->Legend(legend);
    s->Logy(logy);
    s->Logx(logx);

    TH1F*bias=a->HistMCPlus(var,"bias",sample); 

    if (bias) { s->Add(bias,option); bias->SetLineStyle(4); }

    TList*list=s->GetHists();
    if (!list) Send("stackCPS",Form("Error: list %d",0));
    Int_t n=s->GetHists()->GetEntries();
    if (n==0) Send("stackCPS",Form("Error: %d histo(s) in stack",n));

    return s;
}


K4Stack*stackCorrections(K3Ana*a,TString var,Int_t legend=3) {
    K4Stack*s=new K4Stack(var,"","correction factors");
    s->Legend(legend);
    //    s->Norm("correction factors");
    TH1F*de=a->HistMCPlus(var,"detector");
    if (!de) return s;
    s->Add(de,"HistE1");
    /*    
    TH1F*ha=a->HistMCPlus(var,"hadron");
    if (!ha) return s;
    s->Add(ha,"HistE1");
    */
    return s;
}





K4Stack*stackTriggerBits(K3Ana*a,TString layer,Int_t index=0)
{

    TString title=Form("%d-jet sample",index);
    K4Stack*t=new K4Stack("mix",title.Data(),"no");

  //    t->Legend(1);
    //    t->Legend("5,5,11");
    //    t->Logy(1);





    
    TH1F*subtr_l1rw=a->GetHi(Form("Subtr_l1rw%d",index),layer);//->Clone();
    //    subtr_l1rw->SetFillColor(kGrey);
    //    subtr_l1rw->SetLineColor(kYellow);
    subtr_l1rw->SetFillStyle(kFillSolid);
    subtr_l1rw->SetLineWidth(1);
    subtr_l1rw->SetLineStyle(3);
    subtr_l1rw->SetTitle("L1^{rw}");
    //    subtr_l1rw->GetXaxis()->SetBit(TAxis::kLabelsHori);
    //   subtr_l1rw->GetXaxis()->SetBinLabel(3,"s2");
    //    subtr_l1rw->GetXaxis()->SetBinLabel(65,"s64");
    //    subtr_l1rw->GetXaxis()->SetBinLabel(75,"s74");
    t->Add(subtr_l1rw,"HIST");
    

    
    TH1F*subtr_l1ac=a->GetHi(Form("Subtr_l1ac%d",index),layer);//->Clone();
    //    subtr_l1ac->SetFillColor(kBlue);
    //    subtr_l1ac->SetLineColor(kBlue);
    subtr_l1ac->SetFillStyle(kFillSolid);
    subtr_l1ac->SetLineWidth(2);
    subtr_l1ac->SetLineStyle(2);
    subtr_l1ac->SetTitle("L1^{ac}");
    t->Add(subtr_l1ac,"HIST");
    


    TH1F*subtr_l1l2l3ac=a->GetHi(Form("Subtr_l1l2l3ac%d",index),layer);//->Clone();
    //    subtr_l1l2l3ac->SetFillColor(kRed);
    //    subtr_l1l2l3ac->SetLineColor(kRed);
    //    subtr_l1l2l3ac->SetLineWidth(2);
    subtr_l1l2l3ac->SetFillStyle(kFillSolid);
    subtr_l1l2l3ac->SetLineWidth(3);
    subtr_l1l2l3ac->SetLineStyle(1);
    subtr_l1l2l3ac->SetTitle("L1L2L3^{ac}");
    t->Add(subtr_l1l2l3ac,"HIST");





    /*
    TH1F*subtr_Trigac=a->GetHi(Form("Subtr_Trigac%d",index),layer);//->Clone();
    //    sabtr_Trigac->SetFillColor(kBlack);
    //    subtr_Trigac->SetLineColor(kRed);
    //    subtr_Trigac->SetLineStyle(1);
    //    subtr_Trigac->SetFillStyle(kFillSolid);
    subtr_Trigac->SetFillStyle(kFillSolid);
    subtr_Trigac->SetLineWidth(4);
    subtr_Trigac->SetLineStyle(1);
    subtr_Trigac->SetTitle("L1L2L3L4^{ac}");
    t->Add(subtr_Trigac,"HIST");
    */


    return t;
}



K4Stack*stackEff(K3Ana*a,TString layer,TString var,TString st,TString monitor,TString suffix="0")
{
    TString trig=st+suffix;
    //    TString trig2=st+"_l2"+suffix;
    //    TString trig3=st+"_l3"+suffix;
    TString mon=monitor+suffix;

    K4Stack*s=new K4Stack(trig,"efficiency");
    s->SetMaximum(1.2);
    //    s->Legend(0);

    TH1F*L1=a->HistEff(layer,var,trig,mon);
    L1->SetMarkerStyle(0);    
    L1->SetLineColor(2);
    if (!L1) {
	cout<<trig<<mon<<endl;
	return s;
    }
    s->Hapi(L1,"HISTE");
    s->X(var);

    /*    
    TH1F*L2=a->HistEff(layer,var,trig2,mon);
    L2->SetMarkerStyle(0);    
    L2->SetLineColor(4);
    if (L2->Integral()>0) s->Hapi(L2,"HISTE");
    
    TH1F*L3=a->HistEff(layer,var,trig3,mon);
    L3->SetMarkerStyle(0);    
    L3->SetLineColor(6);
    if (L3->Integral()>0) s->Hapi(L3,"HISTE");
    */
    
    //    s->Norm("efficiency");
    return s;
}







TLegend*stackLegend(K3Ana*a,TString sample,TString object="comp")
{
    K4Stack*s;
    if (!object.CompareTo("comp")) s=stackComp(a,sample,"VtxZ4","no",0);
    if (!object.CompareTo("cps")) s=stackCPS(a,sample,"Eta33",0);
    s->CreateLegend();
    TLegend*legend=s->GetLegend();
    legend->SetX1(0);
    legend->SetX2(1);
    legend->SetY1(0);
    legend->SetY2(1);
    return legend;
}








K4Stack*stackTreatHistograms(TObjArray histos,K3Ana*a,TString var,TString norm,
			     TString legend="",Int_t logy=0,Int_t logx=0,TString newx="") {
    TString title="";
    /*
      title=var;//
      TString last=var(Int_t(var.Length()),1);
      //    if (title.IsDigit()) 
      //	title=Form("%s-jet sample",title.Data());
      title+="<";
      title+=last;
      title+=">";
    */
    K4Stack*k=new K4Stack(var,title,norm,newx);
    k->Legend(legend);
    k->Logy(logy);
    k->Logx(logx);


    Int_t c=-1,line=0;
    TString z,name;

    for (Int_t i=0;i<histos.GetEntries();++i) {
	TH1F*h=(TH1F*)histos[i];
	if (!h) {
	    ;//	    Error("stackTreatHistograms","!h");
	} else {
	    //	    histNormalize(a,h,norm);
	    TString option;
	    Int_t color=1;
	    
	    z=h->GetZaxis()->GetTitle();
	    name=h->GetName();
	    if (!z.BeginsWith("d")) {
		//		if (!name.Contains("pause")) {
		    c++;
		    line++;
		    //		}
	    }

	    switch(c) {
	    case -1 : break;
	    case 0 : color=kBlack; break;
	    case 1 : color=kBlack; break;
	    case 2 : color=kRed; break;
	    case 3 : color=kMagenta; break;
	    case 4 : color=kBlue; break;
	    case 5 : color=kCyan; break;
	    case 6 : color=kGreen+3; break;
	    case 7 : color=kOrange+1; break;
	    case 8 : color=kPink; break;
	    case 9 : color=kYellow-3; break;
	    default: Error("stackTreatHistogarms","no more colors %d",c); break;
	    }

	    if (BLACK_AND_WHITE) color=1;
	    histColorize(h,option,color,line);	
	    k->Hapi(h,option);
	}
    }

    stackNormalize(a,k,norm);

    return k;
}


void stackNormalize(K3Ana*a,K4Stack*k,TString norm) {
    TH1F*data=k->Provide();
    TH1F*clone=0;
    Float_t sigma=1;
    if (data) {
	clone=(TH1F*)data->Clone();
	a->Norm(clone,"lumi");
	sigma=clone->Integral();
    }
    TList*list=k->HistogramList();
    if (!list) return;
    for (Int_t i=0;i<list->GetSize();++i) {
	TH1F*h=(TH1F*)list->At(i);
	if (!h) continue;
	if (norm.CompareTo("sigma")) {
	    histNormalize(a,h,norm);
	} else {
	    TString name=h->GetName();
	    if (name.Contains("+")||name.Contains("-")) {
		a->Norm(h,"lumi");
		a->Norm(h,"bin");
		h->Scale(1./sigma);
	    } else {
		histNormalize(a,h,norm);
	    }
	}
    }
    if (clone) delete clone;
}

K4Stack*stackSyst(K3Ana*a,TString var)
{
    //    cout<<"stackSyst for "<<vars<<endl;
    K4Stack*s=new K4Stack(var,"","syst");
    K4Stack*s0=0;

    TH1F*mean=a->HistPlus(var,"pyd","pyr",var,"syst");
    TH1F*plus=a->HistPlus(var,"ppd","ppr",var,"syst");
    TH1F*minu=a->HistPlus(var,"pmd","pmr",var,"syst");
    if (!mean||!plus||!minu) return s0;
    TH1F*systplus=a->Systematics(mean,plus);

    delete mean;
    delete plus;
    delete minu;

    mean=a->HistPlus(var,"pyd","pyr",var,"syst");
    plus=a->HistPlus(var,"ppd","ppr",var,"syst");
    minu=a->HistPlus(var,"pmd","pmr",var,"syst");
    TH1F*systminu=a->Systematics(mean,minu);

    delete mean;
    delete plus;
    delete minu;

    systplus->SetLineStyle(1);
    systminu->SetLineStyle(2);
    systplus->SetLineWidth(2);
    systminu->SetLineWidth(2);

    s->Hapi(systplus,"Hist");
    s->Hapi(systminu,"Hist");
    return s;
}





