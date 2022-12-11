/*
  MultiGraph manipulations
  Ne e testvano
*/




TMultiGraph*multigraphEff(TGraphAsymmErrors*before,TGraphAsymmErrors*after)
{
    TMultiGraph*s=new TMultiGraph("a","");
    s->SetMinimum(-0.1);
    s->SetMaximum(1.1);
    TString title=before->GetTitle();
    title.Append(" -> ");
    title.Append(after->GetTitle());
    after->SetMarkerStyle(kOpenTriangleUp);
    s->Add(after,"ap");
    s->Add(before,"p");
    //    s->SetTitle(title);
    return s;
}


TMultiGraph*multigraphEff(K3Ana*a,TString layer,TString var,TString trigger,TString monitor)
{


    TGraphAsymmErrors*before=a->GraphEff(layer,var,
					 Form("%s%d",trigger.Data(),0),
					 Form("%s%d",monitor.Data(),0));
    TGraphAsymmErrors*after=a->GraphEff(layer,var,
					Form("%s%d",trigger.Data(),1),
					Form("%s%d",monitor.Data(),1));

    //    TString eff=after->GetTitle();
    TMultiGraph*s=new TMultiGraph(trigger,monitor);
    s->SetMinimum(-0.1);
    s->SetMaximum(1.1);
    s->Add(after,"ap");
    s->Add(before,"p");


    return s;
}


/*
TMultiGraph*multigraphEff(K3Ana*a,TString layer,TString var,TString st,TString monitor,TString suffix="0")
{
    TString trig=st+suffix;
    //    TString trig2=st+"_l2"+suffix;
    //    TString trig3=st+"_l3"+suffix;
    TString mon=monitor+suffix;

    TMultiGraph*s=new TMultiGraph(trig,st);
    s->SetMinimum(0);
    s->SetMaximum(1.2);

    TGraphAsymmErrors*L1=a->GraphEff(layer,var,trig,mon);
    if (!L1) return s;
    //    L1->SetLineColor(kBlack);
    s->Add(L1);

    TGraphAsymmErrors*L2=a->GraphEff(layer,var,trig2,mon);
    if (!L2) return s;
    L2->SetLineStyle(2);
    s->Add(L2);

    
    TGraphAsymmErrors*L3=a->GraphEff(layer,var,trig3,mon);
    if (!L3) return s;
    L3->SetLineStyle(3);
    s->Add(L3);

    return s;
}
*/

