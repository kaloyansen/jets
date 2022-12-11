/*
  Fits
*/


void fitPrintCorrections(TString output="slides/alphas.slide") {
    TFile small(WHERE_THE_FITS_WILL_BE);

    TH1F*nP=(TH1F*)small.Get("histNumJetsPythia"); 
    TH1F*nH=(TH1F*)small.Get("histNumJetsHerwig"); 
    TH1F*nC=(TH1F*)small.Get("histNumJetsCascade");

    ofstream tout(output.Data());

    tout.precision(3);
    tout<<"* "<<output<<endl;
    tout<<"*"<<endl<<endl;
    tout<<"MC normalization factors:"<<endl<<endl;
    tout<<endl<<"MC:\t"<<"Pythia\t"<<"Herwig\t"<<"Cascade"<<endl<<endl;
    tout<<endl<<"integrated\t"<<"1.4\t"<<"1.9\t"<<"1.9"<<endl<<endl;
    for (Int_t i=2;i<6;++i) {
	tout<<i<<" jets\t"
	    <<nP->GetBinContent(i)<<"\t"
	    <<nH->GetBinContent(i)<<"\t"
	    <<nC->GetBinContent(i)
	    <<endl<<endl;
    }

    tout<<"* end";
    tout.close();
    Info("fitPrintCorrection","Written to %s",output.Data());
    small.Close();
}

void fitJets(K3Ana*a,Bool_t save=kFALSE) {
      
    
    fitNumJetsIteratively(a,save);
    fitGenNumJets(a,save);
    fitIteratively(a,save,"VtxZUnweighted1","VtxZ","pol5",-40,40,kFALSE);//always FALSE
    

    Bool_t read=kTRUE;
    //E
    fitIteratively(a,save,"EtaPlus2","EtaJet","pol3",-2,6,read,"R");
    fitIteratively(a,save,"EtaPluss3","EttaTriJet","pol3",-2,6,read,"R");
    fitIteratively(a,save,"EtaPlusss4","EtttaFourJet","pol3",-2,6,read,"R");
    //X
    fitIteratively(a,save,"EtaMinus2","EraJet","pol4",-4,4,read,"R");
    fitIteratively(a,save,"EtaMinuss3","ErraTriJet","pol4",-4,4,read,"R");
    fitIteratively(a,save,"EtaMinusss4","ErrraFourJet","pol4",-4,4,read,"R");
    
    fitBabaRiba(save);
    
}

void fitBabaRiba(Bool_t save) {
    TFile big(WHERE_THE_FITS_ARE);
    TString option="READ";
    if (save) option="RECREATE";
    TFile small(WHERE_THE_FITS_WILL_BE,option);
    TCanvas*c=new TCanvas("a","baba riba"); c->Divide(4,3);
    small.cd();

    TH1F*n=(TH1F*)big.Get("histNumJets"); if (save) {n->Write("histNumJets");}                 c->cd(1); n->DrawCopy();
    TH1F*nP=(TH1F*)big.Get("histNumJetsPythia"); if (save) {nP->Write("histNumJetsPythia");}   c->cd(2); nP->DrawCopy();
    TH1F*nH=(TH1F*)big.Get("histNumJetsHerwig"); if (save) {nH->Write("histNumJetsHerwig");}   c->cd(3); nH->DrawCopy();
    TH1F*nC=(TH1F*)big.Get("histNumJetsCascade"); if (save) {nC->Write("histNumJetsCascade");} c->cd(4); nC->DrawCopy();
    TF1*etsum=(TF1*)big.Get("fitEtSum"); if (save) {etsum->Write("fitEtSum");}                 c->cd(5); etsum->DrawCopy();
    TF1*z=(TF1*)big.Get("fitVtxZ"); if (save) {z->Write("fitVtxZ");}                           c->cd(6); z->DrawCopy();
    //  TF1*psi=(TF1*)big.Get("fitPsi"); if (save) {psi->Write("fitPsi");}                         c->cd(7); psi->DrawCopy();
    TF1*eta2=(TF1*)big.Get("fitEtaJet"); if (save) {eta2->Write("fitEtaJet");}                 c->cd(7); eta2->DrawCopy();
    //    TF1*eta3=(TF1*)big.Get("fitEtaTriJet"); if (save) {eta3->Write("fitEtaTriJet");}           c->cd(8); eta3->DrawCopy();
    //    TF1*eta4=(TF1*)big.Get("fitEtaFourJet"); if (save) {eta4->Write("fitEtaFourJet");}         c->cd(9); eta4->DrawCopy();
    TF1*era2=(TF1*)big.Get("fitEraJet"); if (save) {era2->Write("fitEraJet");}                 c->cd(8);era2->DrawCopy();
    //    TF1*era3=(TF1*)big.Get("fitEraTriJet"); if (save) {era3->Write("fitEraTriJet");}           c->cd(11);era3->DrawCopy();
    //    TF1*era4=(TF1*)big.Get("fitEraFourJet"); if (save) {era4->Write("fitEraFourJet");}         c->cd(12);era4->DrawCopy();

    TF1*etta3=(TF1*)big.Get("fitEttaTriJet"); if (save) {etta3->Write("fitEttaTriJet");}       c->cd(9); etta3->DrawCopy();
    //    TF1*etta4=(TF1*)big.Get("fitEttaFourJet"); if (save) {etta4->Write("fitEttaFourJet");}     c->cd(14); etta4->DrawCopy();
    TF1*erra3=(TF1*)big.Get("fitErraTriJet"); if (save) {erra3->Write("fitErraTriJet");}       c->cd(10); erra3->DrawCopy();
    //    TF1*erra4=(TF1*)big.Get("fitErraFourJet"); if (save) {erra4->Write("fitErraFourJet");}     c->cd(16); erra4->DrawCopy();

    TF1*ettta4=(TF1*)big.Get("fitEtttaFourJet"); if (save) {ettta4->Write("fitEtttaFourJet");} c->cd(11); ettta4->DrawCopy();
    TF1*errra4=(TF1*)big.Get("fitErrraFourJet"); if (save) {errra4->Write("fitErrraFourJet");} c->cd(12); errra4->DrawCopy();
//     TF1*x2=(TF1*)big.Get("fitXGamma2"); if (save) {x2->Write("fitXGamma2");}                   c->cd(11);x2->DrawCopy();
//     TF1*x3=(TF1*)big.Get("fitXGamma3"); if (save) {x3->Write("fitXGamma3");}                   c->cd(12);x3->DrawCopy();
//     TF1*x4=(TF1*)big.Get("fitXGamma4"); if (save) {x4->Write("fitXGamma4");}                   c->cd(13);x4->DrawCopy();

    small.ls();
    small.Close();
    big.Close();

    Info("fitBabaRiba","Copy from %s to %s ? %d ",WHERE_THE_FITS_ARE,WHERE_THE_FITS_WILL_BE,save);        

} 


void fitDrawFunction(TString title,Float_t from,Float_t to) {
    TF1 fit("name",title,from,to);
    TCanvas c;
    fit.Draw();
    c.Print("fitDrawFunction.ps");

}


Double_t fitFermi(Double_t*x,Double_t*par)
{
    if (par[1]==0.) return 1;
    return par[2]/(par[2]+TMath::Exp((x[0]-par[0]))/par[1]);

    Double_t k;
    if (par[1]==0.) k=0.;
    else if (par[0]>=x[0]) k=0.;
    else k=TMath::Exp((x[0]-par[0])/par[1]);
    if (k==-1) return 1;
    return 1./(1.+k);

}



Double_t fitEtOld(Double_t*x,Double_t*par)
{
    Double_t in=(par[1]-x[0])*par[2];
    Double_t k=TMath::Exp(in);
    if (k+par[0]<=0) return 1.;
    return par[0]/(par[0]+k);
}





void fitAll(TString anaName,Bool_t setbatch=kTRUE,Bool_t save=kFALSE)
{
    gROOT->SetBatch(setbatch);
    K3Ana*a=new K3Ana(anaName);
    fitNumJetsIteratively(a,save);
    fitVtxZ(a,save);
    TGraphAsymmErrors*gEt1,*gEt2,*gEta1,*gEta2,*gYh;
    fitTriggerEfficiency(a,save,gEt1,gEt2,gEta1,gEta2,gYh);
    delete a;

    TCanvas*canvas=new TCanvas("trig","trig");
    canvas->Divide(3,2);
    canvas->cd(1); gEt1->Draw("ap");
    canvas->cd(2); gEt2->Draw("ap");
    canvas->cd(3); gEta1->Draw("ap");
    canvas->cd(4); gEta2->Draw("ap");
    canvas->cd(5); gYh->Draw("ap");

    if (save) {
	TFile*f=new TFile(WHERE_THE_FITS_ARE);
	f->ls();
	f->Close();
	delete f;
    }
}

Double_t fitAxel(Double_t*x,Double_t*par)
{
    Double_t efficiency=TMath::Power(par[0]-par[1]*x[0],par[2])*TMath::Exp(-1.*par[3]*x[0]);
    if (efficiency<0.) return 0;
    return efficiency;
}

Double_t fitEt(Double_t*x,Double_t*par) {
    //    Double_t efficiency=par[0]-TMath::Exp(par[1]*(x[0]-par[2]));
    //    Double_t exponenta=par[0]*x[0]*x[0]+par[1]*x[0]+par[2];
    //    Double_t efficiency=1.-TMath::Exp(exponenta);
    //    Double_t derivative=2.*par[0]*x[0]+par[1];
    //    derivative=-1.*(2.*par[0]*x[0]+par[1])*TMath::Exp(exponenta);
    //Double_t efficiency=1.-TMath::Exp(par[0]*(x[0]-par[1]));//fix max efficiency
    Double_t efficiency=par[0]-TMath::Exp(par[1]*(x[0]-par[2]));//free max efficiency
    //    Double_t efficiency=1.-TMath::Power(par[0],x[0]-par[1]);//fix max efficiency
    //    if (derivative>0.) efficiency=1;
    if (efficiency<0.) efficiency=0;
    //    if (x[0]>66.) return 1;
    return efficiency;
}



void fitTriggerEfficiency(K3Ana*a,
			  Bool_t save=kFALSE,
			  TGraphAsymmErrors&*gEt1,
			  TGraphAsymmErrors&*gEt2,
			  TGraphAsymmErrors&*gEt12,
			  TGraphAsymmErrors&*gEtSum,
			  TGraphAsymmErrors&*gEta1,
			  TGraphAsymmErrors&*gEta2,
			  //			  TGraphAsymmErrors&*gYh,
			  TGraphAsymmErrors&*gEt1After,
			  TGraphAsymmErrors&*gEt2After,
			  TGraphAsymmErrors&*gEt12After,
			  TGraphAsymmErrors&*gEtSumAfter,
			  TGraphAsymmErrors&*gEta1After,
			  TGraphAsymmErrors&*gEta2After,
			  //			  TGraphAsymmErrors&*gYhAfter,
			  TString trigger,
			  TString monitor,
			  Bool_t dofit=kFALSE)
{
    Int_t nParameters;
    nParameters=3;
    TF1*fit=new TF1("theFit",fitEt,0,100,nParameters); fit->SetLineColor(kBlack); fit->SetLineStyle(2);
    //    fit->Print();
    TString fitoption="R";
    //    fitoption+="Q";
    fitoption+="F";
	
    TString triggers=trigger+"0";
    TString monitors=monitor+"0";

    //    fit->FixParameter(0,1);
 
    //    TF1*fit=new TF1("theFit",fitFermi,0,50,3); fit->SetLineColor(kRed); fit->SetLineStyle(2);
    //    TF1*fit2=new TF1("theFit2","[0]*x+[1]"); fit2->SetLineColor(kRed); fit2->SetLineStyle(2);
    //    fit->SetParameter(1,5.0);//sriv
    //    fit->SetParameter(2,2.5);//naklon na sriv

    TFile*file=new TFile(WHERE_THE_FITS_ARE,"UPDATE");
    file->cd();


    gEt1=a->GraphEff("do6","Et1",triggers,monitors); 

    if (dofit) {
	//    gEt1->Fit("theFit",fitoption); 
	//	if (save) fit->Write("fitEt1");
    }

    gEt2=a->GraphEff("do6","Et2",triggers,monitors); 
    if (dofit) {
	//	gEt2->Fit("theFit",fitoption); 
	//    TString fitres=Form("a=%.2f b=%.2f c=%.2f",
	//		fit->GetParameter(0),
	//		fit->GetParameter(1),
	//		fit->GetParameter(2));
	//    m->Put(fitres,"3,2,2",kRed);
	//	if (save) fit->Write("fitEt2");
    }
    
    gEt12=a->GraphEff("do6","Et12",triggers,monitors); 
    if (dofit) {
	//	gEt12->Fit("theFit",fitoption); 
	//	if (save) fit->Write("fitEt12");
    }

    gEtSum=a->GraphEff("do6","EtSum",triggers,monitors); 
    if (dofit) {
	gEtSum->Fit("theFit",fitoption); 
	if (save) {
	    a->Send("fitTriggerEfficiency","Writing EtSum fit");
	    fit->Write("fitEtSum");
	}    
    }

    file->Close();
    delete file;
    
    gEta1=a->GraphEff("do6","Eta1",triggers,monitors); 
    //        gEta1->Fit("theFit2",fitoption); 
    //    if (save) fit2->Write("fitEta1");

    gEta2=a->GraphEff("do6","Eta2",triggers,monitors);
    //        gEta2->Fit("theFit2",fitoption);
    //    if (save) fit2->Write("fitEta2");

    //    gYh=a->GraphEff("do6","Yh",triggers,monitors); 
    //        gYh->Fit("theFit2",fitoption); 
    //    if (save) fit2->Write("fitYh");
    
    triggers=trigger+"1";
    monitors=monitor+"1";
    gEt1After=a->GraphEff("do6","Et1",triggers,monitors); 
    gEt2After=a->GraphEff("do6","Et2",triggers,monitors); 
    gEt12After=a->GraphEff("do6","Et12",triggers,monitors); 
    gEtSumAfter=a->GraphEff("do6","EtSum",triggers,monitors); 
    gEta1After=a->GraphEff("do6","Eta1",triggers,monitors); 
    gEta2After=a->GraphEff("do6","Eta2",triggers,monitors); 
    //    gYhAfter=a->GraphEff("do6","Yh",triggers,monitors); 


}



Double_t fitEta(Double_t*x,Double_t*par) {
    Double_t fit=par[0]+par[1]*x[0];
    return fit;
}

Double_t fitEta2(Double_t*x,Double_t*par) {
    Double_t fit=par[0]+par[1]*x[0]+par[2]*x[0]*x[0];
    return fit;
}

Double_t fitEta3(Double_t*x,Double_t*par) {
    Double_t fit=par[0]+par[1]*x[0]+par[2]*x[0]*x[0]+par[3]*x[0]*x[0]*x[0];
    return fit;
}




void fitIteratively(K3Ana*a,Bool_t save,TString var,TString name,TString function,Float_t min,Float_t max,Bool_t read=kTRUE,TString fitoption="R")
{
    TString histName=Form("hist%s",name.Data());
    TString fitName=Form("fit%s",name.Data());

    TF1*fit=new TF1("theFit",function,min,max); 
    fit->SetLineColor(kRed); fit->SetLineStyle(2);
    TCanvas*canvas=new TCanvas(var,var);
    canvas->Divide(2,2);

    canvas->cd(1);
    TH1F*data=a->GetHi(var,"do6");
    TH1F*mc=a->HistPlus(var,"pyd","pyr","pyc","name","",1,1); 
    //    data->DrawCopy("EH*");
    //    mc->DrawCopy("sameEH");
    data->Scale(1./data->Integral());
    mc->Scale(1./mc->Integral());
    mc->DrawCopy("EH");
    data->DrawCopy("sameEH*");

    canvas->cd(2);
    TH1F*ratio=(TH1F*)data->Clone("ratio");
    ratio->Divide(mc);
    histRemoveZeroes(ratio);
    ratio->DrawCopy("EH");

    canvas->cd(3);
    TFile*file=new TFile(WHERE_THE_FITS_ARE);
    TH1F*oldRatio=(TH1F*)file->Get(histName);
    if (oldRatio) {
	oldRatio->SetTitle("old");
	histRemoveZeroes(oldRatio);
	oldRatio->DrawCopy();
	
    }

    canvas->cd(4);
    if (oldRatio) if (read) ratio->Multiply(oldRatio);
    ratio->Fit("theFit",fitoption); 
    ratio->DrawCopy("EH*");

    file->Close();
    delete file;
    file=0;
    

    if (save) {
	file=new TFile(WHERE_THE_FITS_ARE,"UPDATE");
	ratio->Write(histName);
	fit->Write(fitName);
	file->Close();
	delete file;
	file=0;
	Info("fitIteratively",
	     " Reweight MC %s histogram and fit written to %s",
	     var.Data(),WHERE_THE_FITS_ARE);        
    }


    delete ratio;
    delete data;
    delete mc;
}


void fitNumJetsIteratively(K3Ana*a, Bool_t save=kFALSE,TString var="NumJets0")
{
    TCanvas*canvas=new TCanvas(var,var);
    canvas->Divide(2,2);

    TH1F*data=a->GetHi(var,"do6");
    //    TH1F*mc=a->GetHi(var,"pyc");
    TH1F*mc=a->HistPlus(var,"pyd","pyr","pyc","name","",1,1); 

    canvas->cd(1);
    data->DrawCopy("EH*");
    mc->DrawCopy("sameEH");
    gPad->SetLogy();

    data->Scale(1./data->Integral());
    mc->Scale(1./mc->Integral());

    canvas->cd(2);
    mc->DrawCopy("EH");
    data->DrawCopy("sameEH*");
    gPad->SetLogy();

    TH1F*ratio=(TH1F*)data->Clone("ratio");
    ratio->Divide(mc);


    TFile*file=new TFile(WHERE_THE_FITS_ARE);
    TH1F*oldRatio=file->Get("histNumJets");
    histRemoveZeroes(oldRatio);

    canvas->cd(3);
    oldRatio->DrawCopy();
    ratio->DrawCopy("sameEH*");
    gPad->SetLogy();


    canvas->cd(4);
    ratio->Multiply(oldRatio);
    ratio->DrawCopy();
    gPad->SetLogy();

    Info("fitNumJetsIteratively","old");
    oldRatio->Print("all");
    Info("fitNumJetsIteratively","new");
    ratio->Print("all");

    file->Close();
    delete file;

    if (save) {
	TFile*file=new TFile(WHERE_THE_FITS_ARE,"UPDATE");
	ratio->Write("histNumJets");
	file->Close();
	delete file;
	Info("fitNumJets",
	     " Reweight MC %s distribution histogram written to %s",
	     var.Data(),WHERE_THE_FITS_ARE);        
    }
    delete data;
    delete mc;
    delete ratio;//new

}



void fitGenNumJets(K3Ana*a,Bool_t save=kFALSE)
{
    fitNumJets(a,"Pythia",save,WHERE_THE_FITS_ARE);
    fitNumJets(a,"Herwig",save,WHERE_THE_FITS_ARE);
    fitNumJets(a,"Cascade",save,WHERE_THE_FITS_ARE);
}

void fitNumJets(K3Ana*a,TString mcname="Pythia",Bool_t save=kFALSE,TString fileName="")
{
    TCanvas*canvas=new TCanvas(mcname,mcname);
    canvas->Divide(2,2);

    TH1F*data=a->HistCorrectedData("do6","NumJets0","py",1,1);
    TH1F*mc;
    if (!mcname.CompareTo("Pythia")) 
	//	mc=a->HistPlus("NumJetsUnweighted0","pid","pir","pic","name","Gen",1,1); 
	mc=a->HistPlus("NumJetsUnweighted0","pnd","pbr","pbc","name","Gen",1,1); 
    else if (!mcname.CompareTo("Herwig")) 
	mc=a->HistPlus("NumJetsUnweighted0","hnd","her","hec","name","Gen",1,1); 
    else if (!mcname.CompareTo("Cascade")) 
	mc=a->GetHi("NumJetsUnweighted0","cai","Gen",1);
    else {
	Info("fitNumJets","Unknown mcname: %s",mcname.Data());
	return;
    }

    canvas->cd(1);
    data->DrawCopy("EH*");
    mc->DrawCopy("sameEH");
    gPad->SetLogy();

    data->Scale(1./data->Integral());
    mc->Scale(1./mc->Integral());

    canvas->cd(2);
    mc->DrawCopy("EH");
    data->DrawCopy("sameEH*");

    TH1F*ratio=(TH1F*)data->Clone("ratio");
    ratio->Divide(mc);

    canvas->cd(3);
    ratio->DrawCopy();
    Info("fitNumJets","%s",mcname.Data());
    ratio->Print("all");

    if (save) {
	TString write="histNumJets"+mcname;
	TFile*file=new TFile(fileName,"UPDATE");
	ratio->Write(write);
	file->Close();
	Info("fitNumJets"," Reweight MC %s distribution histogram written to %s",write.Data(),fileName.Data());
    }
    delete data;
    delete mc;
}

void fitVtxZ(K3Ana*a,Bool_t save=kFALSE,TString var="VtxZUnweighted1")
{
    TH1F*data=a->GetHi(var,"do6");
    TH1F*mc=a->GetHi(var,"pyc");

    TCanvas*canvas=new TCanvas("z","z");
    canvas->Divide(2,2);

    canvas->cd(1);
    data->DrawCopy("EH*");
    mc->DrawCopy("sameEH");
    gPad->SetLogy();

    mc->Scale(1./mc->Integral());
    data->Scale(1./data->Integral());

    canvas->cd(2);
    mc->DrawCopy("EH");
    data->DrawCopy("sameEH*");
    
    canvas->cd(3);
    TF1*fitFunction=new TF1("theFit","gaus+pol11(3)",-40,40);	    
    TH1F*Myxa=(TH1F*)data->Clone("Myxa");
    Myxa->SetName("Myxa");
    Myxa->SetTitle("Myxa");
    Myxa->Divide(mc);
    Myxa->Fit("theFit","RQ");
    
    if (save) {
	TFile*file=new TFile(WHERE_THE_FITS_ARE,"UPDATE");
	fitFunction->Write("fitVtxZ");
	file->Close();
	Info("fitVtxZ","Reweight MC %s distribution fit written to %s",var.Data(),WHERE_THE_FITS_ARE);        
    }


    delete data;
    delete mc;
}



TF1*fitBalance(TH1F*h) {
    Float_t rms=h->GetRMS();
    Int_t ibinmax=h->GetMaximumBin();
    Float_t max=h->GetBinLowEdge(ibinmax)+0.5*h->GetBinWidth(ibinmax);

    TF1*g0=new TF1("g0","gaus",max-rms,max+rms);
    h->Fit("g0","RQ");
    Float_t mean=g0->GetParameter(1);
    Float_t sigma=g0->GetParameter(2);
    delete g0;

    TF1*g1=new TF1("g1","gaus",mean-2.*sigma,mean+2.*sigma);
    g1->SetLineColor(h->GetLineColor());
    g1->SetLineWidth(1);
    h->Fit("g1","RQ");
    return g1;
}



Double_t fit2(Double_t *x, Double_t *par) {
   Double_t r1 = Double_t((x[0]-par[1])/par[2]);
   Double_t r2 = Double_t((x[1]-par[3])/par[4]);
   return par[0]*TMath::Exp(-0.5*(r1*r1+r2*r2));
}   



TF1*fitCorrelation(TH2F*cor) {
    Int_t n=cor->GetNbinsX();
    Float_t min=cor->GetBinLowEdge(1);
    Float_t max=cor->GetBinLowEdge(n+1);

    TF1*gausfit=new TF1("gausfit","gaus");
    TF1*linefit=new TF1("linefit","[0]*x+[1]");
    TProfile*result=new TProfile("result","result",2*n-1,min,max);
    for (Int_t i=1;i<2*n;++i) {
	Float_t boundary=cor->GetBinLowEdge(i+1);
	TH1F*h=new TH1F(Form("hist%d",i),Form("hist%d",i),i,-1.*boundary,boundary);
	Float_t content,error,location,sum=0;
	for (Int_t bin=1;bin<i+1;++bin) {
	    content=cor->GetBinContent(i+1-bin,bin);
	    error=cor->GetBinError(i+1-bin,bin);
	    sum+=content;
	    h->SetBinContent(bin,content);
	    h->SetBinError(bin,error);
	}
	if (sum==0.) continue;
	h->Fit(gausfit,"NQ");
	location=result->GetBinCenter(i);
	result->Fill(location,gausfit->GetParameter(1),sum);
	result->SetBinError(i,gausfit->GetParameter(2));
	delete h;
    }

    result->Fit(linefit,"NQ");
    Float_t par0=linefit->GetParameter(0);
    Float_t par1=linefit->GetParameter(1);
    linefit->SetParameters(par0+1.,par1);
    delete result;
    delete gausfit;
    return linefit;
}
