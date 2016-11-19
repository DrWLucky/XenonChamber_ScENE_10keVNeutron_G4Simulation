#include "TNamed.h"
#include "TString.h"
#include "TCanvas.h"
#include "EventData.hh"
#include "TRint.h"
#include "utilities.hh"
#include "RootGraphix.hh"
#include "CommandSwitchFunctions.hh"
#include "ChanFitSettings.hh"
#include <sstream>
#include <fstream>
#include <map>
#include <vector>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "TTree.h"
#include "TApplication.h"
#include "TFile.h"
#include "TF1.h"
#include "TH1F.h"
#include "DBConst.hh"
#include <TStyle.h>

#include "LEDfitfunc.hh"


using namespace std;

int main( int argc, char** argv){

  if (argc != 2){
    cout<<"Usage: SPE_Fit <genroot-output-filename>"<<endl;
    return -1;
  } 




  //RootGraphix root;
  //root.Initialize();



TApplication *theApp = new TApplication("app", 0, 0); //<======
    
theApp->SetReturnFromRun(true);


  
TTree* Events = GetEventsTree(argv[1]);

  if (!Events) {
    cout<<"!Events"<<endl; 
    return -1;
  }
  EventData* event = 0;
  Events->SetBranchAddress("event",&event);
  Events->GetEntry(0); 
 

  // Print run id, no. of channels and no. of events
  int run = event->run_id;
  if(run < 0){
    std::cerr<<"Unable to read runid from rootfile! Aborting."<<std::endl;
    return -1;
  }

  int nChans = event->channels.size();

  cout<<"Processing Run "<<run<<" with "<<(nChans-1)<<" channels."<<endl;
  cout<<"There are "<<Events->GetEntries()<<" events in this run."<<endl;




  const int 		nbins = 450;
  const double 		start= -50, end=400;
 


/*
  std::map<int,TH1F*> spectra;
 
  // Populate histograms
  for(int i=0; i < Events->GetEntries(); i++){
    if(i%5000 == 0) cout<<"Processing Entry "<<i<<endl;
    Events->GetEntry(i);
    // Loop over all pmt channels
    for(int j=0; j <=1; j++){

      ChannelData* channel = &(event->channels.at(j));
     
   
      std::map<int,TH1F*>::iterator mapit = spectra.find(channel->channel_id);
      TH1F* histo=0;
      
	if(mapit == spectra.end()){
		
		TString name = "channel";
			name += channel->channel_id;
			cout<<"Creating new histogram with name "<<name<<endl;
			histo = new TH1F(name,name,nbins,start,end);
			spectra.insert(std::make_pair(channel->channel_id, histo));
      }
      else{
			histo = (mapit->second);
      }

      //fill the histogram
      if(!histo){
	cerr<<"Null pointer passed!\n";
	return -2;
      }
      for(size_t n=0; n<channel->single_pe.size(); n++){
	
	histo->Fill(channel->single_pe[n].integral);
      }

    }//--- End of Channel Loop ------

  }//--- End of Event Loop -----

*/


  //cout<<endl<<"About to fit"<<endl;
  
    const int ChannelNbr = 8;
    

TH1F *Spectra = new TH1F[ChannelNbr];

TCanvas *Canvas[ChannelNbr];

for(int j=0; j <ChannelNbr; j++){

	TString ChannelName = "channel";
	TString CanvasName = "Canvas";
	ChannelName += Form("_%i", j);
	CanvasName += Form("%i", j);
	
      	Spectra[j] = TH1F(ChannelName,ChannelName, nbins, start, end);
	 Canvas[j] = new TCanvas(CanvasName, CanvasName);
      
}


 for(int i=0; i < Events->GetEntries(); i++){


    if(i%10000 == 0) cout<<"Processing Entry "<<i<<endl;
    
	Events->GetEntry(i);
    

    // Loop over all pmt channels
    for(int j=0; j <ChannelNbr; j++){

      ChannelData* channel = &(event->channels.at(j));

	//--- loop through all the channels and collect the found spe ---
      for(size_t n=0; n<channel->single_pe.size(); n++){
	
	Spectra[j].Fill(channel->single_pe[n].integral);
      }

    }//--- End of Channel Loop ------

  }//--- End of Event Loop -----




	//Draw all the histograms
	//root.AcquireLock();

	//double FitWindow_StartPoint[ChannelNbr] = {10.5, 10.5};
	//double   FitWindow_EndPoint[ChannelNbr] = {};

  gStyle->SetOptFit(111);


	TF1 TopPMT_Gaus_Func = TF1("TopPMT_Gaus_Func","gaus",90, 240);

 	TF1 BtmPMT_Gaus_Func = TF1("BtmPMT_Gaus_Func","gaus",60, 140);


    for(int j=0; j <ChannelNbr; j++){

	Canvas[j]->cd();
	Canvas[j]->SetWindowSize(1.5*Canvas[j]->GetWw(),Canvas[j]->GetWh());
	Canvas[j]->Clear();
	//Canvas[j]->SetLogy();
		


	//Spectra[j].SetStats(1);

	std::cout<<"start fit for channel#: "<<j<<std::endl;
///*	
	if(j!=7)
	Spectra[j].Fit(&TopPMT_Gaus_Func,"R");
	else
	Spectra[j].Fit(&BtmPMT_Gaus_Func,"R");

	//std::cout<<"par#0: "<<Gaus_Func.GetParameter(0)<<", par#1: "<<Gaus_Func.GetParameter(1)<<", par#2: "<<Gaus_Func.GetParameter(2)<<std::endl;;
//*/

//TFitResultPtr ptr = LEDfitfunc::FitSPE(&Spectra[j], Canvas[j],  false);
	Spectra[j].Draw();

	Canvas[j]->Update();
}

/* 

  	TCanvas* c = new TCanvas("c","Canvas");
  	c->SetWindowSize(2*c->GetWw(),c->GetWh());

	c->Clear();
  	DividePad(c,2);
  	int padn=1;
  
	  for(int k=0; k<2; k++){

 		   c->cd(padn++);
    		gPad->SetLogy();
		Spectra[k].Draw();
    		
  	}


c->Update();

*/


/*
  for(std::map<int,TH1F*>::iterator it = spectra.begin(); it != spectra.end(); it++){
    TH1F* hist = (it->second);
    //cout<<endl<<"About to fit channel: "<<it->first<<endl<<endl;
    FitSPE(hist, ChannelsSettings[it->first]);
    //cout<<endl<<"Done fitting channel: "<<it->first<<endl<<endl;

*/


/*
 char pause;

std::cout<<"Paused and input whatever"<<std::endl;
std::cin>>pause;


	delete Spectra; 
*/

theApp->Run();


  return 1;
}
