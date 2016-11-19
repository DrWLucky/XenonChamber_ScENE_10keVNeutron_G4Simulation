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

#include "Roi.hh"

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


  const int 		nbins = 700;
  //const double 		start= -50, end=300; //---for the Top PMTs ---
   const double 		start= -50, end=500; //---for the Btm PMTs ---

  const int ChannelNbr     = 5;
  const int Tot_ChannelNbr = nChans;

TCanvas c1("c1", "canvas", 900, 600);

TH1F *ROI_Spectrum = new TH1F("ROI_Spectrum", "ROI_Spectrum", nbins, start, end);
    ROI_Spectrum->GetXaxis()->SetTitle("ADC Counts");
    ROI_Spectrum->GetYaxis()->SetTitle("Events/Bin");
    //hist_PrimPulse_S1_Spectrum->GetXaxis()->CenterTitle(true);
    ROI_Spectrum->GetXaxis()->SetTitleSize(0.04);
    ROI_Spectrum->GetYaxis()->SetTitleSize(0.04);
    ROI_Spectrum->SetTitle("Integration over [-0.1 #mus, 0.2 #mus] Window");
    //ROI_Spectrum->SetTitleSize(0.05);
    //ROI_Spectrum->SetFillColor(38);
    ROI_Spectrum->SetLineColor(38);




 for(int i=0; i < Events->GetEntries(); i++){


    if(i%10000 == 0) cout<<"Processing Entry "<<i<<endl;
    
	Events->GetEntry(i);

	bool     Single_Pulse    = true;
	Double_t Pulse_Threshold = 500;

    // Loop over all pmt channels to the ROI value
    for(int j=0; j<Tot_ChannelNbr; j++){

	ChannelData* channel  = &(event->channels.at(j));
	Double_t     ROI_value;

		//std::cout<<channel->regions.size()<<std::endl;

	if(channel->regions.size()!=0)
		ROI_value = channel->regions[0].integral;
	else
		ROI_value = 0;

	if( (j!=ChannelNbr)&&(std::abs(ROI_value)>Pulse_Threshold) ){
		Single_Pulse = false;
		break;
	}

    }//--- End of Channel Loop ------


	Double_t   ROI_size  = event->GetChannelByID(ChannelNbr)->regions.size();

	if(Single_Pulse&&(ROI_size!=0)){

      		//ChannelData* channel  = &(event->channels.at(ChannelNbr));
      		//Double_t    ROI_value = channel->regions[0].integral;
    		Double_t   ROI_value  = -event->GetChannelByID(ChannelNbr)->regions[1].integral;
		ROI_Spectrum->Fill(ROI_value);
	}

  }//--- End of Event Loop -----




	//Draw all the histograms
	//root.AcquireLock();

	//double FitWindow_StartPoint[ChannelNbr] = {10.5, 10.5};
	//double   FitWindow_EndPoint[ChannelNbr] = {};

  gStyle->SetOptFit(111);


	//TF1 Gaus_Func = TF1("Gaus_Func","gaus",55, 130);//---for the Top PMTs ---
	TF1 Gaus_Func = TF1("Gaus_Func","gaus", 80, 200);//---for the Btm PMTs ---




   

	c1.cd();
	c1.SetLogy();
		
	ROI_Spectrum->Fit(&Gaus_Func,"R");
	ROI_Spectrum->Draw();

	c1.Update();




theApp->Run();


  return 1;
}
