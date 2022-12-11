

TString tripNameOfControlInFile(TFile*file)
{
    TString name="";
    Int_t n=file->GetNkeys();
    Info("tripNameOfControlInFile","Nkeys=%d",n);
    TIter next(file->GetListOfKeys());
    TKey*key;
    while((key=(TKey*)next())) {
	name=key->GetName();
	Info("tripNameOfControlInFile","%s",name.Data());
    }
    if (n==1) return name;
    else return 0;
}

TString tripNameOfControlInFileName(TString fileName)
{
    TFile file(fileName);
    TString name="";
    Int_t n=file.GetNkeys();
    Info("tripNameOfControlInFile","Nkeys=%d",n);
    TIter next(file->GetListOfKeys());
    TKey*key;
    while((key=(TKey*)next())) {
	name=key->GetName();
	Info("tripNameOfControlInFile","%s",name.Data());
    }
    file.Close();
    //    delete file;
    return name;
}



K3Control*tripControlInFile(TString fileName)
{
    cout<<"Loading "<<fileName<<"...";
    TFile*file=new TFile(fileName);
    K3Control*control=(K3Control*)file->Get(tripNameOfControlInFile(file));
    cout<<"done."<<endl;
    return control;
}

void tripControlInfo(TString fileName)
{
    K3Control*control=tripControlInFile(fileName);
    TH1F*hist;    
    TList*list=control->HiList;
    TIter iter(list);	
    while ((hist=(TH1F*)iter.Next())) cout<<hist->GetName()<<"("<<hist->GetUniqueID()<<")"<<endl;
    delete hist;
}


TH1F*tripHistInControl(TString fileName,TString histName)
{
    K3Control*control=tripControlInFile(fileName);
    TH1F*h=control->FindHi(histName);
    return h;
}




void tripTogether(TString x)
{

    TString ext=".root";
    TString location=CONTROL_LOCATION;
    TString newLocation=COMBINED_LOCATION;
    TString outputFileName=newLocation+x+ext;
    TFile outputFile(outputFileName,"RECREATE");

    char*dir=gSystem->ExpandPathName(location.Data());
    Info("tripTogether","scan <%s> for <%s>",dir,x.Data());

    void*dirp=gSystem->OpenDirectory(dir);

    const char*entry;
    const char*filename[100];

    Int_t n=0;
    TString str;
    while((entry=(char*)gSystem->GetDirEntry(dirp))) {
	str=entry;
	//	Info("tripTogether","%d",n);
	//	Info("tripTogether","%s",entry);
	if (!str.CompareTo(x+ext)) continue;
	if(str.BeginsWith(x)&&str.EndsWith(ext))
	    if (str.Sizeof()==x.Sizeof()+ext.Sizeof()+3)
		filename[n++] = gSystem->ConcatFileName(dir, entry);
    }

    const Int_t max=n;
    TDCacheFile*file[max];
    K3Control*control[max];

    Info("tripTogether","add:");
    for (Int_t i=0;i<n;i++) {
	cout<<filename[i]<<" "<<flush;
	file[i]=new TDCacheFile(filename[i]);
	control[i]=(K3Control*)file[i]->Get(tripNameOfControlInFile(file[i]));
	control[i]->Panopm();
	outputFile.cd();
	control[i]->Write();
	file[i]->Close();
	cout<<endl;  
    }
 
    outputFile.Close();
    delete [] file;
    gSystem->FreeDirectory(dirp);
    gSystem->Exit(0);
}

