{
    K3Control * c = new K3Control("cname", "ctitle");
    c->Book(1, "a", "", "hit mul", "events", "", 33, -0.5, 2499.5);
    c->Book(1, "b", "", "threshold hit mul", "events", "", 33, -0.5, 1999.5);  

    K3Space * s = c->Space();
    s->Add("c1");
    s->Add("c2");
    s->Add("c3");
//    s->Add("c4");
//    s->Add("c5");

    c->Multiplex();


    s->On();
    s->State();


    s->Off();
    Int_t entry = 0;

    s->On("c1"); while (entry < 100) { c->Fill("a", 5); entry++; }
    s->On("c2"); while (entry < 200) { c->Fill("a", 5); entry++; }
    s->On("c3"); while (entry < 300) { c->Fill("a", 5); entry++; }

    s->CorrelationMatrixHistogram()->Draw("box");
//    s->Print();
//    c->Glist();

    delete c;
}
