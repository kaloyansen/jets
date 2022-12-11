/*
  Ultimate tools 
  Input: an instance of the analysis class K3Ana
*/



/*



 _/      _/   _/_/_/
 _/    _/   _/     _/
 _/  _/           _/
 _/_/          _/        
 _/  _/          _/
 _/    _/         _/
 _/      _/ _/    _/
 _/       _/  _/_/



*/
//LABELS

void anaLabel(K4Meet*m,Int_t kolko,Short_t align=33,Float_t size=0.5) {
    TString s0="no bg reduction";
    TString s1="with bg reduction";
    TString s2="dijet sample";
    TString s3="trijet sample";
    TString s4="fourjet sample";
    if (kolko==2) {
	size=0.7;
	m->Put(s3,"2,2,1",kBlack,size,align);
	m->Put(s4,"2,2,2",kBlack,size,align);
    } else if (kolko==3) {
	size=0.7;
	m->Put(s2,"2,2,1",kBlack,size,align);
	m->Put(s3,"2,2,3",kBlack,size,align);
	m->Put(s4,"2,2,4",kBlack,size,align);
    } else if (kolko==5) {
	size=0.7;
	m->Put(s0,"3,2,1",kBlack,size,align);
	m->Put(s1,"3,2,2",kBlack,size,align);
	m->Put(s2,"3,2,4",kBlack,size,align);
	m->Put(s3,"3,2,5",kBlack,size,align);
	m->Put(s4,"3,2,6",kBlack,size,align);
    } else if (kolko==6) {
	m->Put(s2,"3,3,1",kBlack,size,align);
	m->Put(s3,"3,3,4",kBlack,size,align);
	m->Put(s3,"3,3,5",kBlack,size,align);
	m->Put(s4,"3,3,7",kBlack,size,align);
	m->Put(s4,"3,3,8",kBlack,size,align);
	m->Put(s4,"3,3,9",kBlack,size,align);
    } else if (kolko==9) {
	m->Put(s2,"4,3,1",kBlack,size,align);
	m->Put(s2,"4,3,2",kBlack,size,align);
	m->Put(s3,"4,3,5",kBlack,size,align);
	m->Put(s3,"4,3,6",kBlack,size,align);
	m->Put(s3,"4,3,7",kBlack,size,align);
	m->Put(s4,"4,3,9",kBlack,size,align);
	m->Put(s4,"4,3,10",kBlack,size,align);
	m->Put(s4,"4,3,11",kBlack,size,align);
	m->Put(s4,"4,3,12",kBlack,size,align);
    } else Error("anaLabel","Unknown size");








}


void anaLabel2x2(K4Meet*m,
		 TString s1="dijet sample",TString s2="trijet sample",
		 TString s3="fourjet sample",TString s4="dijet sample",
		 TString s5="trijet sample",TString s6="fourjet sample",
		 Float_t size=0.7) {
    m->Put(s1,"2,2,1",kBlack,size,22);
    m->Put(s2,"2,2,3",kBlack,size,22);
    m->Put(s3,"2,2,4",kBlack,size,22);
}

void anaLabel3x2(K4Meet*m,
		 TString s1="dijet sample",TString s2="trijet sample",
		 TString s3="fourjet sample",TString s4="dijet sample",
		 TString s5="trijet sample",TString s6="fourjet sample",
		 Float_t size=0.5) {
    m->Put(s1,"3,2,1",kBlack,size,22);
    m->Put(s2,"3,2,4",kBlack,size,22);
    m->Put(s2,"3,2,5",kBlack,size,22);
    m->Put(s3,"3,2,7",kBlack,size,22);
    m->Put(s3,"3,2,8",kBlack,size,22);
    m->Put(s3,"3,2,9",kBlack,size,22);
}


void anaLabel3x3(K4Meet*m,
		 TString s1="dijet sample",TString s2="trijet sample",
		 TString s3="fourjet sample",TString s4="dijet sample",
		 TString s5="trijet sample",TString s6="fourjet sample",
		 Float_t size=0.5) {
    m->Put(s1,"3,3,1",kBlack,size,22);
    m->Put(s2,"3,3,4",kBlack,size,22);
    m->Put(s2,"3,3,5",kBlack,size,22);
    m->Put(s3,"3,3,7",kBlack,size,22);
    m->Put(s3,"3,3,8",kBlack,size,22);
    m->Put(s3,"3,3,9",kBlack,size,22);
}

void anaLabel4x3(K4Meet*m,Int_t align=22,
		 TString s1="dijet sample",TString s2="trijet sample",
		 TString s3="fourjet sample",Float_t size=0.5) {
    m->Put(s1,"4,3,1",kBlack,size,align);
    m->Put(s1,"4,3,2",kBlack,size,align);
    m->Put(s2,"4,3,5",kBlack,size,align);
    m->Put(s2,"4,3,6",kBlack,size,align);
    m->Put(s2,"4,3,7",kBlack,size,align);
    m->Put(s3,"4,3,9",kBlack,size,align);
    m->Put(s3,"4,3,10",kBlack,size,align);
    m->Put(s3,"4,3,11",kBlack,size,align);
    m->Put(s3,"4,3,12",kBlack,size,align);
}




//SLIDES
void anaXDefSlide(TString title,K4Meet*m) {
    m->Slide(title);
    Int_t color=kBlue;
    Float_t angle=0;
    Float_t size=0.6;
    Short_t align=22;

    m->Put("N_{i} = A_{i} #sigma_{i} #int Ldt",                                       "1,6,2",color,angle,size,align);
    m->Put("acceptance A_{i} = #varepsilon C_{i}",                                    "2,6,5",color,angle,size,align);
    m->Put("trigger efficiency  #varepsilon = #frac{N(phys. #wedge ref.)}{N(ref)}",   "2,6,7",color,angle,size,align);
    m->Put("correction factor C_{i} = #sum_{j}R_{j}^{i} / #sum_{j} R_{i}^{j}",        "2,6,9",color,angle,size,align);
    //	m->Put("correction C_{f} =  #frac{ N^{ rec}}{ N^{ had}}",                 "2,6,9");
    
    m->Put("purity P_{i} = R_{i}^{i} / #sum_{j} R_{j}^{i}",                           "3,5,9",color,angle,size,align);
    //	m->Put("purity P = #frac{ N^{ had&rec}}{ N^{ rec}}",                "3,5,9");
    m->Put("stability S_{i} = R_{i}^{i} / #sum_{j} R_{i}^{j}",                       "3,5,12",color,angle,size,align);
    //	m->Put("stability S = #frac{ N^{ had&rec}}{ N^{ had}}",             "3,5,12");
}


void anaFormulaSlide(TString title,K4Meet*m) {
    m->Slide(title);
    m->Put("x_{ #gamma}^{ obs} = #frac{1}{2yE_{e}}  #sum_{ j=1}^{ n_{ jets}} E_{T, j} e^{ - #eta_{ j}}", "3,3,2",kBlack,0,0.8,22);
    m->Put("x_{ p}^{ obs} = #frac{1}{2E_{p}}  #sum_{ j=1}^{ n_{ jets}} E_{T, j} e^{ #eta_{ j}}", "3,3,5",kBlack,0,0.8,22);
    m->Put("M_{nj}^{2} = (#sum_{i=1}^{n} p_{i})^{2}",                                     "3,3,8",kBlack,0,0.8,22);
}





void anaFeynDiagramsSlide(TString title,K4Meet*m,Float_t size=0.5) {
    m->Slide(title);

    m->Put(padFeynman("3"),.00,.33,.33,.66,0);
    m->Put(padFeynman("res,katja"),.30,.33,.66,.76,0);
    m->Put(padFeynman("res,thomas"),.6,.33,.99,.86,0);

    
    /*
    m->Put("y / x_{#gamma} = electron / photon energy fraction",.1,.05,.6,.09,kBlack);
    
    Float_t y0=0.2,y1=0.25;

    m->Put("direct",.1,y0,.2,y1,kBlack);
    m->Put("resolved",.4,y0,.5,y1,kBlack);
    m->Put("MI",.7,y0,.8,y1,kBlack);
    m->Put("#splitline{the photon is}{point-like}",0.05,0.7,0.25,0.75);
    m->Put("#splitline{composite}{object}",0.45,0.7,0.55,0.9,kRed);
    m->Put("#splitline{two independant}{parton pairs interacting}",0.7,0.05,0.9,0.15,kRed);

    TArrow*l=new TArrow(0.48,0.8,0.465,0.67, 0.01,"-|>");
    l->SetLineWidth(3);
    l->SetLineColor(kRed);
    l->SetFillColor(kRed);
    m->Put(l);
    */

    m->Put("(a)","3,3,7",kBlack,size);
    m->Put("(b)","3,3,8",kBlack,size);
    m->Put("(c)","3,3,9",kBlack,size);
    

    m->Export("feynman.eps");


}


void anaEventSelectionSlide(K3Ana*a,TString title,K4Meet*m) {
    m->NewSlide(title);
    Float_t x0=0.1,x1=0.45;
    m->Put("H1 2006 e^{-}, 50.813/pb",                 x0,0.85,x1,0.90,kRed);
    m->Put("CJC1,CJC2,CIP,COZ,LAR,SPAC,LUMI,TOF on",   x0,0.75,x1,0.85);
    m->Put("Photoproduction:",                         x0,0.70,x1,0.75);
    m->Put("Q^{2} < 4 GeV^{ 2}",                       x0,0.65,x1,0.70);
    m->Put("* No electron found",                      x0,0.60,x1,0.65);

    //    if (talk) m->Put(padDetector(9,140,.67,.53,kBlack),"r");//.4,.4,1.,1.);

    m->Put("Jets (lab, k_{T}):",                       x0,0.40,x1,0.48);
    //    m->Put("#splitline{in the acceptance of central tracking detector}{and liquid argon calorimeter}",  x0,0.25,.55,0.45);
    m->Put("* -0.5 <  #eta  < 2.5",          x0,0.30,x1,0.35);
    m->Put("*  118 > #Theta > 9 #circ",      x0,0.25,x1,0.30);
    //    m->Put("* 9 GeV < Three jet sample:",                 x0,0.20,x1,0.25);
    m->Put("* E_{T} > 8 GeV",       x0,0.15,x1,0.20);
    //    m->Put("Four jet sub-sample:",             x0,0.10,x1,0.15);
    //    m->Put("* E_{T,jet4} > 5 GeV",               x0,0.05,x1,0.10);
	
    //    m->Put(stackComp(a,"jetN","first","do6,poo"),"8");                  
    //    gPad->SetLogy();
    m->Put("Events survived:",0.7,0.25,1.0,0.30,kRed);
    m->Put("3-jet 14517",     0.7,0.20,1.0,0.25,kRed);
    m->Put("4-jet  1362",     0.7,0.15,1.0,0.20,kRed);

}



void anaTriggerEfficiency(TString title,K4Meet*m,TString data,K3Ana*a,TString trigger,TString monitor,
			  Bool_t dofit=kFALSE,Bool_t save=kFALSE,Bool_t after=kFALSE,TString file="") {

    m->Slide(title);

    TGraphAsymmErrors*gEt1,*gEt2,*gEt12,*gEtSum,*gEta1,*gEta2;//,*gYh;
    TGraphAsymmErrors*gEt1After,*gEt2After,*gEt12After,*gEtSumAfter,*gEta1After,*gEta2After;//,*gYhAfter;
    fitTriggerEfficiency(a,save,
			 gEt1,gEt2,gEt12,gEtSum,gEta1,gEta2,//gYh,
			 gEt1After,gEt2After,gEt12After,gEtSumAfter,gEta1After,gEta2After,//gYhAfter,
			 trigger,monitor,dofit);


    if (after) {
	TMultiGraph*check=(TMultiGraph*)m->Put(multigraphEff(gEt1,gEt1After),"3,2,1");
	m->Put(check->GetTitle(),"3,2,1",kBlack,0.6,23);
	check=(TMultiGraph*)m->Put(multigraphEff(gEt2,gEt2After),"3,2,2");
	m->Put(check->GetTitle(),"3,2,2",kBlack,0.6,23);
	//	m->Put(multigraphEff(gEt12,gEt12After),"3,3,4");
	check=(TMultiGraph*)m->Put(multigraphEff(gEtSum,gEtSumAfter),"3,2,3");
	m->Put(check->GetTitle(),"3,2,3",kBlack,0.6,23);
	check=(TMultiGraph*)m->Put(multigraphEff(gEta1,gEta1After),"3,2,4");    
	m->Put(check->GetTitle(),"3,2,4",kBlack,0.6,23);
	check=(TMultiGraph*)m->Put(multigraphEff(gEta2,gEta2After),"3,2,5");
	m->Put(check->GetTitle(),"3,2,5",kBlack,0.6,23);
	//	check=(TMultiGraph*)m->Put(multigraphEff(gYh,gYhAfter),"3,2,6");
	//	m->Put(check->GetTitle(),"3,2,6",kBlack,0.6,23);
	//	m->Put("#epsilon(E) = #theta(#DeltaE)(#epsilon_{max}-e^{k#DeltaE})","3,3,3",kRed);
	//	m->Put("#DeltaE=E-E_{min}","3,3,6",kRed);
	//	m->Put("Legend:","3,13,3");
	m->Put("             + efficiency","3,13,9",kBlack,.7,22);
	m->Put("     ----- fit","3,13,12",kBlack,.7,22);
	m->Put("           #Delta check ","3,13,15",kBlack,.7,22);
	check->Print("all");
    } else {
	m->Put(gEt1,"3,2,1");
	m->Put(gEt2,"3,2,2");
	//	m->Put(gEt12,"3,3,4");
	m->Put(gEtSum,"3,2,3");
	m->Put(gEta1,"3,2,4");    
	m->Put(gEta2,"3,2,5");
	//	m->Put(gYh,"3,2,6");
    }

    
    if (!file.CompareTo("")) m->Export(file);
    
}



TGraphAsymmErrors*anaOneTriggerEfficiency(K3Ana*a,TString var,TString trigger,TString monitor) {
    TGraphAsymmErrors*graph=a->GraphEff("do6",var,trigger,monitor); 
    return graph;
}




//MISC
/*
void anaRemoveWhiteSpace(TString file) {
    TString exec="/bin/zsh ";
    exec+=WHITE_SCRIPT;
    exec+=" ";
    exec+=file;
    cout<<"anaRemoveWhiteSpace executes "<<exec<<endl;
    gSystem->Exec(exec);
}
*/




