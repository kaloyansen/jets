#include <fstream>
#include <stdlib.h>
#include "TROOT.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TStyle.h"
#include "TSystem.h"

using namespace std;

int main(int argc, char**argv) {

    gROOT->SetBatch();
    gROOT->SetStyle("Plain");
    gStyle->SetPalette(1);
    gStyle->SetPadTickX(1);
    gStyle->SetPadTickY(1);
    gStyle->SetLabelFont(42, "XYZ");
    gStyle->SetTitleFont(42);
    gStyle->SetTitleFont(42, "XYZ");
    gStyle->SetStatFont(42);
    gROOT->ForceStyle();


    //    gInterpreter->SetErrorMessages(kFALSE);
    //    gErrorIgnoreLevel=kError;
    const char*info0="/proc/acpi/battery/BAT0/state";
    const char*info1="/proc/acpi/battery/BAT1/state";
    const char*info2="/proc/acpi/thermal_zone/THM/temperature";
    TString buffer;
    Float_t time=0;
    Int_t point=0;
    Int_t voltage0,voltage1,capacity0,temperature;
    Float_t voltage0f,voltage1f,capacity0f;
    voltage0f = voltage1f = capacity0f = 0;
    //    gStyle->SetCanvasColor(0);
    TCanvas c("monitor","Kaloyan KRASTEV");
    c.Divide(1,2,0,0);
    TGraph gCapacity0(10);
    TGraph gVoltage0(10);
    TGraph gTemperature(10);

    gCapacity0.SetMarkerStyle(kFullCircle);
    gCapacity0.SetMarkerSize(0.4);
    gCapacity0.SetTitle("battery0 capacity, Ah");
    gVoltage0.SetMarkerStyle(kFullCircle);
    gVoltage0.SetMarkerSize(0.4);
    gVoltage0.SetTitle("battery0 voltage, V");
    gTemperature.SetMarkerStyle(kFullCircle);
    gTemperature.SetMarkerSize(0.4);
    gTemperature.SetTitle("processor temperature, C");
    gTemperature.SetMarkerColor(kRed);

    while (1) {
	ifstream*battery0=new ifstream(info0);
	ifstream*battery1=new ifstream(info1);
	ifstream*processor=new ifstream(info2);
	if (!battery0||!battery1||!processor) c.Error("main","Can't open file");

	do { 
	    buffer.ReadLine(*battery0);
	    if (buffer.Contains("present voltage")) {
		//		cout<<"all:"<<buffer<<endl;
		buffer =  buffer(16,14);
		//		cout<<"<"<<buffer<<">"<<endl;
		voltage0=atoi(buffer.Data());
		voltage0f=Float_t(voltage0/1000.);
	    } else if (buffer.Contains("remaining capacity")) {
		//		cout<<"all: "<<buffer<<endl;
		buffer =  buffer(19,10);
		//		cout<<"<"<<buffer<<">"<<endl;
		capacity0=atoi(buffer.Data());
		capacity0f=Float_t(capacity0/1000.);
	    } else {;}
	} while (!battery0->eof());

	do {buffer.ReadLine(*battery1);
	} while ( (!buffer.Contains("present voltage")) && (!battery1->eof()));
	buffer =  buffer(16,14);
	voltage1=atoi(buffer.Data());
	voltage1f=Float_t(voltage1/1000.);

	buffer.ReadFile(*processor);
	buffer =  buffer(13,14);
	temperature=atoi(buffer.Data());

	delete battery0;
	delete battery1;
	delete processor;

	gCapacity0.SetPoint(point,time,capacity0f);
	gVoltage0.SetPoint(point,time,voltage0f);
	gTemperature.SetPoint(point,time,temperature);

	point++;
	time=1.+1.001*time;

	
	//	if (time>10.) {
	//	    gCapacity0.Fit("expo","Q");
	    //	    gVoltage0.Fit("theFit","Q");
	//  gTemperature.Fit("expo","Q");
	    //	} 
	

	c.cd(1);
	gCapacity0.Draw("ap+");
	//	c.cd(2);
	//	gVoltage0.Draw("ap+");
	c.cd(2);
	gTemperature.Draw("ap+");
	c.Update();
	c.Print("/$HOME/Desktop/hot.ps");
	gSystem->Sleep(5000);
    }

    return 0;
}

/*
g++ -o applications/jets applications/jets.C -I`root-config --incdir` `root-config --glibs`
*/
