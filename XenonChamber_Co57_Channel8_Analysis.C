#include "TStyle.h"
#include "TTree.h"
#include "TFile.h"
#include "TF1.h"
#include "TChain.h"
#include "TMath.h"
#include "TCut.h"
#include "TCanvas.h"
#include "TColor.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TLegend.h"
#include "TGraph.h"
#include "TGraphAsymmErrors.h"
#include "TPaveStats.h"
#include "TProfile.h"
#include "TString.h"
#include "TKey.h"

#include <stdio.h>
#include <fcntl.h>
#include <iostream>
#include <fstream>
#include "math.h"

#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>

//#include "myLib.C"
//#include "DBLib.h"

#include "EventData.hh"

using namespace std;



void XenonChamber_Co57_Channel8_Analysis(){

    
    
    TChain *T1 = new TChain("Events");
    
    //T1->AddFile("/xenon_data_1/Processed_Data/run0004_S1_0721.root"); //--- 6000V ---
    //T1->AddFile("/xenon_data_1/Processed_Data/run0007_S1_0721.root"); //--- 5000V ---
    //T1->AddFile("/xenon_data_1/Processed_Data/run0008_S1_0721.root"); //--- 4000V ---
    

    //T1->AddFile("/xenon_data_1/Processed_Data/run0014_S1_0721.root");   //--- 0V, PMT1400V ---
    //T1->AddFile("/xenon_data_1/Processed_Data/run0015_S1_0721.root"); //--- 0V, PMT1440V ---
    //T1->AddFile("/xenon_data_1/Processed_Data/run0016_S1_0721.root"); //--- 1000V ---
    //T1->AddFile("/xenon_data_1/Processed_Data/run0017_S1_0721.root"); //--- 2000V ---
    //T1->AddFile("/xenon_data_1/Processed_Data/run0018_S1_0721.root"); //--- 3000V ---
	T1->AddFile("/xenon_data_1/Run01/Processed_Data/Run10001.root"); //--- 0V, next day ---


    std::string AppendString = "LightYield";
    
    std::string RunName = "Channel8_Co57_0Vcm";

    
    EventData* T1Event = NULL;
    
    T1->SetBranchAddress("event", &T1Event);

    
    double S1_Spectrum_EndPoint   = 2000;
    double S1_Spectrum_StartPoint = 0.;

       int S1_Spectrum_BinNbr     = 1000;

//========================Histogram Setups ==================================
    
    TH1F          *hist_S1_Spectrum = new TH1F("hist_S1_Spectrum",  "",    S1_Spectrum_BinNbr, S1_Spectrum_StartPoint, S1_Spectrum_EndPoint);
    
    //hist_S1_Spectrum->SetStats(0);
    hist_S1_Spectrum->GetXaxis()->SetTitle("S1 [PE]");
    hist_S1_Spectrum->GetYaxis()->SetTitle("Events/Bin");
    //hist_S1_Spectrum->GetXaxis()->CenterTitle(true);
    hist_S1_Spectrum->GetXaxis()->SetTitleSize(0.04);
    hist_S1_Spectrum->GetYaxis()->SetTitleSize(0.04);
    hist_S1_Spectrum->SetTitle("S1 from ^{57}Co Calibration, E_{drfit}=0 V/cm");
    //hist_S1_Spectrum->SetTitleSize(0.05);
    //hist_S1_Spectrum->SetFillColor(38);
    hist_S1_Spectrum->SetLineColor(38);

//=============================================================================
    
    
   TH1F          *hist_Channel8_Pulse = new TH1F("hist_Channel8_Pulse",  "",    1500, 0., 1500);
    
    //hist_Channel8_Pulse->SetStats(0);
    hist_Channel8_Pulse->GetXaxis()->SetTitle("S1 [PE]");
    hist_Channel8_Pulse->GetYaxis()->SetTitle("Events/Bin");
    hist_Channel8_Pulse->GetXaxis()->SetTitleSize(0.04);
    hist_Channel8_Pulse->GetYaxis()->SetTitleSize(0.04);
    hist_Channel8_Pulse->SetTitle("S1 from Channel#8 (Btm PMT) ^{57}Co Calibration, E_{drfit}=0 V/cm");
    hist_Channel8_Pulse->SetLineColor(38);


//=============================================================================

    
    
    
    TH1F          *hist_Channel8_PulseWidth = new TH1F("hist_Channel8_PulseWidth",  "",    500, 0., 500);
    
    //hist_Channel8_PulseWidth->SetStats(0);
    hist_Channel8_PulseWidth->GetXaxis()->SetTitle("Pulse Width [ns]");
    hist_Channel8_PulseWidth->GetYaxis()->SetTitle("Events/Bin");
    hist_Channel8_PulseWidth->GetXaxis()->SetTitleSize(0.04);
    hist_Channel8_PulseWidth->GetYaxis()->SetTitleSize(0.04);
    hist_Channel8_PulseWidth->SetTitle("Pulse Width from Channel#8 (Btm PMT) ^{57}Co Calibration, E_{drfit}=0 V/cm");
    hist_Channel8_PulseWidth->SetLineColor(38);
    
    
    //=============================================================================

    
    TH1F          *hist_Channel8_PulsePeak = new TH1F("hist_Channel8_PulsePeak",  "",    1000, 0., 2000);
    
    //hist_Channel8_PulsePeak->SetStats(0);
    hist_Channel8_PulsePeak->GetXaxis()->SetTitle("Pulse Peak [ADC]");
    hist_Channel8_PulsePeak->GetYaxis()->SetTitle("Events/Bin");
    hist_Channel8_PulsePeak->GetXaxis()->SetTitleSize(0.04);
    hist_Channel8_PulsePeak->GetYaxis()->SetTitleSize(0.04);
    hist_Channel8_PulsePeak->SetTitle("Pulse Peak from Channel#8 (Btm PMT) ^{57}Co Calibration, E_{drfit}=0 V/cm");
    hist_Channel8_PulsePeak->SetLineColor(38);
    
    
    //=============================================================================

    
    TH2F          *hist_S1vsPulseMax = new TH2F("hist_S1vsPulseMax", "", 1000, 0., 2000, 1000, 0., 2000);
    
    hist_S1vsPulseMax->SetStats(0);
    hist_S1vsPulseMax->GetXaxis()->SetTitle("Pulse Max [ADC]");
    hist_S1vsPulseMax->GetYaxis()->SetTitle("S1 [PE]");
    //hist_S1vsPulseMax->GetXaxis()->CenterTitle(true);
    //hist_S1vsPulseMax->GetYaxis()->CenterTitle(true);
    hist_S1vsPulseMax->GetXaxis()->SetTitleSize(0.04);
    hist_S1vsPulseMax->GetYaxis()->SetTitleSize(0.04);
    hist_S1vsPulseMax->SetTitle("S1 vs. Pulse Max");
    //hist_S1vsPulseMax->SetTitleSize(0.05);
    //hist_F90vsTPC_TOF->SetFillColor(38);

    //=============================================================================

    
    
Int_t EntryNbr = T1->GetEntries();
std::cout<<"Total Entry# is: "<<EntryNbr<<std::endl;


    
T1->GetEntry(EntryNbr-1);
Double_t TotRunTime = T1Event->event_time/1e9;	//--- unit: ns ----



//for(Int_t i=0; i<EntryNbr; i++){
for(Int_t i=0; i<150000; i++){

	T1->GetEntry(i);

//std::cout<<event.event_time<<std::endl;

//event->GetChannelByID(-2)->pulses[1].start_time

    
    Int_t  TotPulseNbr = T1Event->GetChannelByID(-2)->npulses;
    Int_t       EvtNbr = T1Event->event_id;
    bool     Saturated = T1Event->saturated;
    
    Double_t           S1_PE    = T1Event->GetChannelByID(-2)->pulses[0].npe;
    Double_t  Channel1_S1_PE    = T1Event->GetChannelByID(7)->pulses[0].npe;
    Double_t  Channel1_S1_Peak  = T1Event->GetChannelByID(7)->pulses[0].peak_amplitude;

    Double_t  Channel1_S1_PulseWidth  = 1000*(T1Event->GetChannelByID(7)->pulses[0].end_time - T1Event->GetChannelByID(0)->pulses[0].start_time);

    
    if(!Saturated){
        hist_S1_Spectrum->Fill(S1_PE);
        if( (S1_PE>1000)&&(S1_PE<1400) ){
            hist_Channel8_Pulse->Fill(Channel1_S1_PE);
            hist_Channel8_PulseWidth->Fill(Channel1_S1_PulseWidth);
            hist_Channel8_PulsePeak->Fill(Channel1_S1_Peak);
            hist_S1vsPulseMax->Fill(Channel1_S1_Peak, Channel1_S1_PE);
        }


    }
    
}



    /*
    gStyle->SetOptFit(0111);
    gStyle->SetStatW(0.1);
    gStyle->SetStatH(0.05);
*/
    gStyle->SetOptFit(111);
    
    TF1 *Peak_GausFit = new TF1("Peak_GausFit", "gaus", 1050, 1300);

    
    TCanvas *c1 = new TCanvas("c1", "c1", 1400, 800);
    
	c1->cd();
	hist_S1_Spectrum->Draw("");
    hist_S1_Spectrum->Fit(Peak_GausFit, "R+");


    
    TPaveText *pave = new TPaveText(0.2,0.6,0.4,0.8, "NDC");
    //pave->SetFillColor(0);
    pave->SetFillStyle(0);
    pave->SetBorderSize(0);
    //pave->SetTextSize(0.03);
    
    
    TString Title = "Light Yield From ^{57}Co 122keV:";
    TString Blank = "";
    
    TString FitResult;
    TString LyResult;
    
    FitResult.Form(" Gaussian Peak Mean: %.2f PE",  Peak_GausFit->GetParameter(1));
     LyResult.Form(" Ligt Yield: %.3f PE/keV", (Peak_GausFit->GetParameter(1)/122));

    
    pave->AddText(Title);
    //pave->AddText(Blank);
    pave->AddText(FitResult);
    pave->AddText(LyResult);
    
    /*
    TText *t1=pave->AddText(Title);
    t1->SetTextColor(1);
    t1->SetTextSize(0.04);
    */
    
    pave->Draw("SAMES");
    

    
    std::string c1_pdf_name = RunName + "_S1_" + AppendString + ".pdf";
    std::string c1_eps_name = RunName + "_S1_" + AppendString + ".eps";
    
    
    c1->SaveAs(c1_pdf_name.c_str());
    c1->SaveAs(c1_eps_name.c_str());
        
    
    //----------------------------------------------------------------------
    
    
    TCanvas *c2 = new TCanvas("c2", "c2", 1400, 800);

    c2->cd();
	hist_Channel8_Pulse->Draw("");
    
    std::string c2_pdf_name = RunName + "_Channel1_S1_" + AppendString + ".pdf";
    std::string c2_eps_name = RunName + "_Channel1_S1_" + AppendString + ".eps";
    
    c2->SaveAs(c2_pdf_name.c_str());
    c2->SaveAs(c2_eps_name.c_str());
    
    
    //----------------------------------------------------------------------

    
    TCanvas *c3 = new TCanvas("c3", "c3", 1400, 800);
    
    c3->cd();
	hist_Channel8_PulseWidth->Draw("");
    
    std::string c3_pdf_name = RunName + "_Channel1_S1_Width_" + AppendString + ".pdf";
    std::string c3_eps_name = RunName + "_Channel1_S1_Width_" + AppendString + ".eps";
    
    c3->SaveAs(c3_pdf_name.c_str());
    c3->SaveAs(c3_eps_name.c_str());

    
    //----------------------------------------------------------------------
    
    TCanvas *c4 = new TCanvas("c4", "c4", 1400, 800);
    
    c4->cd();
	hist_Channel8_PulsePeak->Draw("");
    
    std::string c4_pdf_name = RunName + "_Channel1_S1_Peak_" + AppendString + ".pdf";
    std::string c4_eps_name = RunName + "_Channel1_S1_Peak_" + AppendString + ".eps";
    
    c4->SaveAs(c4_pdf_name.c_str());
    c4->SaveAs(c4_eps_name.c_str());
    
    //----------------------------------------------------------------------

    TCanvas *c5 = new TCanvas("c5", "c5", 1400, 800);

	c5->cd();
	hist_S1vsPulseMax->Draw("COLZ");

    
    /*
    std::string rootFieName = RunName + "_"+ AppendString + ".root";

    

    TFile *histFile = new TFile(rootFieName.c_str(), "RECREATE");

    
    histFile->cd();
 
     	      hist_F90vsPE->Write();
       hist_EJ_PSDvsEJ_TOF->Write();
      hist_TPC_TOFvsEJ_TOF->Write();
 hist_Full_TPC_TOFvsEJ_TOF->Write();
         hist_F90vsTPC_TOF->Write();
      	   hist_TOFCuts_S1->Write();
    
    
         hist_BasicCuts_S1->Write();
          EJ1_BasicCuts_S1->Write();
          EJ2_BasicCuts_S1->Write();
          EJ3_BasicCuts_S1->Write();
    
         EJ23_BasicCuts_S1->Write();
    EJ23_BasicCuts_S1_40Bin->Write();
    EJ23_BasicCuts_S1_80Bin->Write();
    EJ23_BasicCuts_S1_120Bin->Write();
    EJ23_BasicCuts_S1_200Bin->Write();
    EJ23_BasicCuts_S1_240Bin->Write();
    EJ23_BasicCuts_S1_280Bin->Write();


              hist_S1vsTOF->Write();
            EJ1_TOFCuts_S1->Write();
            EJ2_TOFCuts_S1->Write();
            EJ3_TOFCuts_S1->Write();
    
           EJ23_TOFCuts_S1->Write();
    EJ23_TOFCuts_S1_40Bin->Write();
    EJ23_TOFCuts_S1_80Bin->Write();
    EJ23_TOFCuts_S1_120Bin->Write();
    EJ23_TOFCuts_S1_200Bin->Write();
    EJ23_TOFCuts_S1_240Bin->Write();
    EJ23_TOFCuts_S1_280Bin->Write();

    
          hist_S1_Spectrum->Write();
           EJ1_S1_Spectrum->Write();
           EJ2_S1_Spectrum->Write();
           EJ3_S1_Spectrum->Write();
    
          EJ23_S1_Spectrum->Write();
    EJ23_S1_Spectrum_40Bin->Write();
    EJ23_S1_Spectrum_80Bin->Write();
    EJ23_S1_Spectrum_120Bin->Write();
    EJ23_S1_Spectrum_200Bin->Write();
    EJ23_S1_Spectrum_240Bin->Write();
    EJ23_S1_Spectrum_280Bin->Write();


         EJ23_S1_TOFCuts_F90->Write();
                 EJ23_S1_F90->Write();
    EJ23_S1_NoPulseLimit_F90->Write();
       EJ23_S1_BasicCuts_F90->Write();
    
    
      hist_PrimPulse_S1_Spectrum->Write();
    EJ1_S1_Spectrum_NoPulseLimit->Write();
    EJ2_S1_Spectrum_NoPulseLimit->Write();
    EJ3_S1_Spectrum_NoPulseLimit->Write();
    
    EJ23_S1_Spectrum_NoPulseLimit->Write();
    EJ23_S1_Spectrum_NoPulseLimit_40Bin->Write();
    EJ23_S1_Spectrum_NoPulseLimit_80Bin->Write();
    EJ23_S1_Spectrum_NoPulseLimit_120Bin->Write();
    EJ23_S1_Spectrum_NoPulseLimit_200Bin->Write();
    EJ23_S1_Spectrum_NoPulseLimit_240Bin->Write();
    EJ23_S1_Spectrum_NoPulseLimit_280Bin->Write();


    
    c0->Write();
    c8->Write();
    c9->Write();
    c10->Write();
    c11->Write();
    c12->Write();
    c13->Write();
   
    c14->Write();
    c15->Write();
    c16->Write();
    c17->Write();
    

    histFile->Close();

    */

}
