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



void XenonChamber_S2_Analysis(){

    
    
    TChain *T1 = new TChain("Events");
    
 
	T1->AddFile("/xenon_data_1/Run01/Processed_Data/Run10027.root"); //--- ---


    std::string AppendString = "S2Run";
    
    std::string RunName = "Run10027_Co57";

    
    EventData* T1Event = NULL;
    
    T1->SetBranchAddress("event", &T1Event);


    double S1_Spectrum_EndPoint   = 2000;
    double S1_Spectrum_StartPoint = 0.;

       int S1_Spectrum_BinNbr     = 1000;

    //========================Histogram Setups ==================================
    
    TH1F          *hist_PrimPulse_Spectrum = new TH1F("hist_PrimPulse_Spectrum",  "",    S1_Spectrum_BinNbr, S1_Spectrum_StartPoint, S1_Spectrum_EndPoint);
    
    //hist_PrimPulse_Spectrum->SetStats(0);
    hist_PrimPulse_Spectrum->GetXaxis()->SetTitle("S1 [PE]");
    hist_PrimPulse_Spectrum->GetYaxis()->SetTitle("Events/Bin");
    //hist_PrimPulse_Spectrum->GetXaxis()->CenterTitle(true);
    hist_PrimPulse_Spectrum->GetXaxis()->SetTitleSize(0.04);
    hist_PrimPulse_Spectrum->GetYaxis()->SetTitleSize(0.04);
    hist_PrimPulse_Spectrum->SetTitle("Primary Pulse from ^{57}Co S2 Run");
    //hist_PrimPulse_Spectrum->SetTitleSize(0.05);
    //hist_PrimPulse_Spectrum->SetFillColor(38);
    hist_PrimPulse_Spectrum->SetLineColor(38);

    
    
//========================Histogram Setups ==================================
    
    TH1F          *hist_S1_Spectrum = new TH1F("hist_S1_Spectrum",  "",    S1_Spectrum_BinNbr, S1_Spectrum_StartPoint, S1_Spectrum_EndPoint);
    
    //hist_S1_Spectrum->SetStats(0);
    hist_S1_Spectrum->GetXaxis()->SetTitle("S1 [PE]");
    hist_S1_Spectrum->GetYaxis()->SetTitle("Events/Bin");
    //hist_S1_Spectrum->GetXaxis()->CenterTitle(true);
    hist_S1_Spectrum->GetXaxis()->SetTitleSize(0.04);
    hist_S1_Spectrum->GetYaxis()->SetTitleSize(0.04);
    hist_S1_Spectrum->SetTitle("S1 from ^{57}Co S2 events");
    //hist_S1_Spectrum->SetTitleSize(0.05);
    //hist_S1_Spectrum->SetFillColor(38);
    hist_S1_Spectrum->SetLineColor(38);

//=============================================================================
    
    double S2_Spectrum_EndPoint   = 80000;
    double S2_Spectrum_StartPoint = 0.;
    
      int S2_Spectrum_BinNbr     = 1000;

    
    TH1F          *hist_S2_Spectrum = new TH1F("hist_S2_Spectrum",  "",    S2_Spectrum_BinNbr, S2_Spectrum_StartPoint, S2_Spectrum_EndPoint);
    
    //hist_S2_Spectrum->SetStats(0);
    hist_S2_Spectrum->GetXaxis()->SetTitle("S2 [PE]");
    hist_S2_Spectrum->GetYaxis()->SetTitle("Events/Bin");
    //hist_S2_Spectrum->GetXaxis()->CenterTitle(true);
    hist_S2_Spectrum->GetXaxis()->SetTitleSize(0.04);
    hist_S2_Spectrum->GetYaxis()->SetTitleSize(0.04);
    hist_S2_Spectrum->SetTitle("S2 from ^{57}Co");
    //hist_S2_Spectrum->SetTitleSize(0.05);
    //hist_S2_Spectrum->SetFillColor(38);
    hist_S2_Spectrum->SetLineColor(38);
    
    //=============================================================================


    
   TH1F          *hist_S2like_Spectrum = new TH1F("hist_S2like_Spectrum",  "",    S2_Spectrum_BinNbr, S2_Spectrum_StartPoint, S2_Spectrum_EndPoint);
    
    //hist_S2like_Spectrum->SetStats(0);
    hist_S2like_Spectrum->GetXaxis()->SetTitle("S2 [PE]");
    hist_S2like_Spectrum->GetYaxis()->SetTitle("Events/Bin");
    //hist_S2like_Spectrum->GetXaxis()->CenterTitle(true);
    hist_S2like_Spectrum->GetXaxis()->SetTitleSize(0.04);
    hist_S2like_Spectrum->GetYaxis()->SetTitleSize(0.04);
    hist_S2like_Spectrum->SetTitle("S2 from ^{57}Co");
    //hist_S2like_Spectrum->SetTitleSize(0.05);
    //hist_S2like_Spectrum->SetFillColor(38);
    hist_S2like_Spectrum->SetLineColor(38);

//=============================================================================
/*
    
    
    
    TH1F          *hist_Channel1_PulseWidth = new TH1F("hist_Channel1_PulseWidth",  "",    500, 0., 500);
    
    //hist_Channel1_PulseWidth->SetStats(0);
    hist_Channel1_PulseWidth->GetXaxis()->SetTitle("Pulse Width [ns]");
    hist_Channel1_PulseWidth->GetYaxis()->SetTitle("Events/Bin");
    hist_Channel1_PulseWidth->GetXaxis()->SetTitleSize(0.04);
    hist_Channel1_PulseWidth->GetYaxis()->SetTitleSize(0.04);
    hist_Channel1_PulseWidth->SetTitle("122keV Pulse Width from Channel#1 (Top Center PMT) ^{57}Co Calibration, E_{drfit}=0 V/cm");
    hist_Channel1_PulseWidth->SetLineColor(38);
    
    
    //=============================================================================

    
    TH1F          *hist_Channel1_PulsePeak = new TH1F("hist_Channel1_PulsePeak",  "",    600, 0., 300);
    
    //hist_Channel1_PulsePeak->SetStats(0);
    hist_Channel1_PulsePeak->GetXaxis()->SetTitle("Pulse Peak [PE]");
    hist_Channel1_PulsePeak->GetYaxis()->SetTitle("Events/Bin");
    hist_Channel1_PulsePeak->GetXaxis()->SetTitleSize(0.04);
    hist_Channel1_PulsePeak->GetYaxis()->SetTitleSize(0.04);
    hist_Channel1_PulsePeak->SetTitle("122keV Pulse Peak from Channel#1 (Top Center PMT) ^{57}Co Calibration, E_{drfit}=0 V/cm");
    hist_Channel1_PulsePeak->SetLineColor(38);
  */
    
    //=============================================================================

    
    TH2F          *hist_Ratio_vs_dt = new TH2F("hist_Ratio_vs_dt", "", 200, 0., 500, 300, 0., 300);
    
    hist_Ratio_vs_dt->SetStats(0);
    hist_Ratio_vs_dt->GetXaxis()->SetTitle("Time Difference between S2 and S1 [ns]");
    hist_Ratio_vs_dt->GetYaxis()->SetTitle("S2/S1");
    //hist_Ratio_vs_dt->GetXaxis()->CenterTitle(true);
    //hist_Ratio_vs_dt->GetYaxis()->CenterTitle(true);
    hist_Ratio_vs_dt->GetXaxis()->SetTitleSize(0.04);
    hist_Ratio_vs_dt->GetYaxis()->SetTitleSize(0.04);
    hist_Ratio_vs_dt->SetTitle("S2/S1 vs. dt");
    //hist_Ratio_vs_dt->SetTitleSize(0.05);
    //hist_Ratio_vs_dt->SetFillColor(38);

    //=============================================================================

    
    
    TH2F          *hist_S2_vs_PulseWidth = new TH2F("hist_S2_vs_PulseWidth", "",  200, 0., 2000, 500, 0., 50000);
    
    hist_S2_vs_PulseWidth->SetStats(0);
    hist_S2_vs_PulseWidth->GetXaxis()->SetTitle("S2 Pulse Width [ns]");
    hist_S2_vs_PulseWidth->GetYaxis()->SetTitle("S2 [PE]");
    //hist_S2_vs_PulseWidth->GetXaxis()->CenterTitle(true);
    //hist_S2_vs_PulseWidth->GetYaxis()->CenterTitle(true);
    hist_S2_vs_PulseWidth->GetXaxis()->SetTitleSize(0.04);
    hist_S2_vs_PulseWidth->GetYaxis()->SetTitleSize(0.04);
    hist_S2_vs_PulseWidth->SetTitle("S2 vs. Pulse Width");
    //hist_S2_vs_PulseWidth->SetTitleSize(0.05);
    //hist_S2_vs_PulseWidth->SetFillColor(38);
    
    //=============================================================================

    
    
    
    
Int_t EntryNbr = T1->GetEntries();
std::cout<<"Total Entry# is: "<<EntryNbr<<std::endl;

Int_t S2_EvtNbr = 0;
Int_t Good_S2_EvtNbr = 0; //--- events with both S1 & S2 ---
    
T1->GetEntry(EntryNbr-1);
Double_t TotRunTime = T1Event->event_time/1e9;	//--- unit: ns ----



for(Int_t i=0; i<EntryNbr; i++){
//for(Int_t i=0; i<10000; i++){

	T1->GetEntry(i);

//std::cout<<event.event_time<<std::endl;

//event->GetChannelByID(-2)->pulses[1].start_time

    
    Int_t  TotPulseNbr = T1Event->GetChannelByID(-2)->npulses;
    Int_t       EvtNbr = T1Event->event_id;
    bool     Saturated = T1Event->saturated;
    
    for(int k=0; k<TotPulseNbr; k++){
	
    Double_t  PulseWidth = 1000*(T1Event->GetChannelByID(-2)->pulses[k].end_time - T1Event->GetChannelByID(-2)->pulses[k].start_time);
    Double_t       S2_PE = T1Event->GetChannelByID(-2)->pulses[k].npe;
        
        if(PulseWidth>500){
            hist_S2like_Spectrum->Fill(S2_PE);
            S2_EvtNbr++;
        }
        
    }
	
    if( (!Saturated)&&(TotPulseNbr>1) ){
        
        Double_t   S1_PE    = T1Event->GetChannelByID(-2)->pulses[0].npe;
        Double_t   S2_PE    = T1Event->GetChannelByID(-2)->pulses[1].npe;
        Double_t  S1_PulseWidth  = 1000*(T1Event->GetChannelByID(-2)->pulses[0].end_time - T1Event->GetChannelByID(-2)->pulses[0].start_time);
        Double_t  S2_PulseWidth  = 1000*(T1Event->GetChannelByID(-2)->pulses[1].end_time - T1Event->GetChannelByID(-2)->pulses[1].start_time);
        Double_t  dt = 1000*(T1Event->GetChannelByID(-2)->pulses[1].start_time - T1Event->GetChannelByID(-2)->pulses[0].end_time);
        Double_t Ratio = S2_PE/S1_PE;
        
        if( (S2_PulseWidth>500)&&(S1_PulseWidth<250) ){
            
            hist_S1_Spectrum->Fill(S1_PE);
            hist_S2_Spectrum->Fill(S2_PE);
            Good_S2_EvtNbr++;
            
            if(dt>0)
                hist_Ratio_vs_dt->Fill(dt, Ratio);
           hist_S2_vs_PulseWidth->Fill(S2_PulseWidth, S2_PE);

        }

    }
    
    if(!Saturated){
        
        Double_t   S1_PE    = T1Event->GetChannelByID(-2)->pulses[0].npe;
        Double_t  S1_PulseWidth  = 1000*(T1Event->GetChannelByID(-2)->pulses[0].end_time - T1Event->GetChannelByID(-2)->pulses[0].start_time);
	if(S1_PulseWidth<300)
        hist_PrimPulse_Spectrum->Fill(S1_PE);
        
    }
    
}



    /*
    gStyle->SetOptFit(0111);
    gStyle->SetStatW(0.1);
    gStyle->SetStatH(0.05);
*/
    
    /*
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
    
    
    
    pave->Draw("SAMES");
    */
    
    std::cout<<"Total Event#: "<<EntryNbr<<", S2 Event#: "<<S2_EvtNbr<<", Good S2 Event#: "<<Good_S2_EvtNbr<<std::endl;
    
    TCanvas *c1 = new TCanvas("c1", "c1", 1400, 800);
    
	c1->cd();
	hist_PrimPulse_Spectrum->Draw("");

    std::string c1_pdf_name = RunName + "_PrimaryPulse_" + AppendString + ".pdf";
    std::string c1_eps_name = RunName + "_PrimaryPulse_" + AppendString + ".eps";
    
    
    c1->SaveAs(c1_pdf_name.c_str());
    c1->SaveAs(c1_eps_name.c_str());

    //----------------------------------------------------------------------
    
    
    TCanvas *c2 = new TCanvas("c2", "c2", 1400, 800);

    c2->cd();
	//hist_Channel1_Pulse->Draw("");
    hist_S1_Spectrum->Draw("");
    
    std::string c2_pdf_name = RunName + "_S1_" + AppendString + ".pdf";
    std::string c2_eps_name = RunName + "_S1_" + AppendString + ".eps";
    
    c2->SaveAs(c2_pdf_name.c_str());
    c2->SaveAs(c2_eps_name.c_str());
    
    
    //----------------------------------------------------------------------

    
    TCanvas *c3 = new TCanvas("c3", "c3", 1400, 800);
    
    c3->cd();
	//hist_Channel1_PulseWidth->Draw("");
    hist_S2_Spectrum->Draw("");

    
    std::string c3_pdf_name = RunName + "_S2_" + AppendString + ".pdf";
    std::string c3_eps_name = RunName + "_S2_" + AppendString + ".eps";
    
    c3->SaveAs(c3_pdf_name.c_str());
    c3->SaveAs(c3_eps_name.c_str());

    
    //----------------------------------------------------------------------
    
    TCanvas *c4 = new TCanvas("c4", "c4", 1400, 800);
    
    c4->cd();
	//hist_Channel1_PulsePeak->Draw("");
    hist_S2_vs_PulseWidth->Draw("COLZ");
    
    std::string c4_pdf_name = RunName + "_S2_vs_PulseWidth_" + AppendString + ".pdf";
    std::string c4_eps_name = RunName + "_S2_vs_PulseWidth_" + AppendString + ".eps";
    
    c4->SaveAs(c4_pdf_name.c_str());
    c4->SaveAs(c4_eps_name.c_str());
    
    //----------------------------------------------------------------------

    TCanvas *c5 = new TCanvas("c5", "c5", 1400, 800);

	c5->cd();
	//hist_S1vsPulseMax->Draw("COLZ");
    hist_Ratio_vs_dt->Draw("COLZ");
    
    std::string c5_pdf_name = RunName + "_Ratio_vs_dt_" + AppendString + ".pdf";
    std::string c5_eps_name = RunName + "_Ratio_vs_dt_" + AppendString + ".eps";
    
    c5->SaveAs(c5_pdf_name.c_str());
    c5->SaveAs(c5_eps_name.c_str());
    
    //----------------------------------------------------------------------

    TCanvas *c6 = new TCanvas("c6", "c6", 1400, 800);
    
	c6->cd();
    c6->SetLogy();
    
    TF1 *profile_fit = new TF1("profile_fit", "expo", 5, 150);

    
    TProfile *profile_dt = hist_Ratio_vs_dt->ProfileX("profile_dt", 0, 300); // where firstYbin = 0 and lastYbin = 300

    profile_dt->SetStats(0);
    profile_dt->Draw("");
    profile_dt->Fit(profile_fit, "R+");

    
    TPaveText *pave = new TPaveText(0.6,0.6,0.8,0.8, "NDC");
    //pave->SetFillColor(0);
    pave->SetFillStyle(0);
    pave->SetBorderSize(0);
    //pave->SetTextSize(0.03);
    
    TString Title = "exponential fit on S2/S1 vs. dt profile:";
    TString Blank = "";
    
    TString FitResult;
    
    FitResult.Form(" electron lifetime: %.2f ns",  -1/profile_fit->GetParameter(1));
    
    pave->AddText(Title);
    //pave->AddText(Blank);
    pave->AddText(FitResult);
    
    pave->Draw("SAMES");

    std::string c6_pdf_name = RunName + "_lifetime_" + AppendString + ".pdf";
    std::string c6_eps_name = RunName + "_lifetime_" + AppendString + ".eps";
    
    c6->SaveAs(c6_pdf_name.c_str());
    c6->SaveAs(c6_eps_name.c_str());
    
    //----------------------------------------------------------------------
  
    
    TCanvas *c7 = new TCanvas("c7", "c7", 1400, 800);
    
	c7->cd();
    hist_S2like_Spectrum->Draw("");
    
    std::string c7_pdf_name = RunName + "_S2like_Pulse_" + AppendString + ".pdf";
    std::string c7_eps_name = RunName + "_S2like_Puslse_" + AppendString + ".eps";
    
    c7->SaveAs(c7_pdf_name.c_str());
    c7->SaveAs(c7_eps_name.c_str());

    
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
