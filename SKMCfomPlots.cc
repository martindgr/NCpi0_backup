
//#define SKMCfomPlots_cxx
//#include "SKMCfomPlots.h"

#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
//#include "Prob3/BargerPropagator.h"
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include<iostream>
#include<fstream>

#include <TH1.h>
#include <TEllipse.h>
#include "SetT2KStyle.H"


#include <TMath.h>

#include <TPad.h>
#include <TArrow.h>
#include <cmath>

double GetFOM(double sig, double bkg){
	if ((sig == 0)||(sig+bkg) <= 0 ) {
		return 0;
	} else {
  	return (sig / (sqrt(sig + bkg)));
	}
}

double GetEff(double sig, double total_sig){
	if ((total_sig == 0)) {
		return 0;
	} else {
  	return (sig / total_sig);
	}
}

double GetPur(double sig, double bkg){
	
	if((sig<0)||(bkg<0)){
		std::cout << "negative purity error" << std::endl;
		return 0;
	}
	else if ((sig+bkg) == 0) {
		return 0;
	} else {
  	return (sig / (sig + bkg));
	}
}
/*
void get_intervals(TH2F *post, std::vector<double> levels, std::vector<double> &contours, int *bestfit){
    int n_levels = levels.size();
    double tot_sum = 0;
    double integral = post->Integral();
    TH2F *tmp = (TH2F*)post->Clone();
    *bestfit = tmp->GetMaximumBin();
    std::cout<<*bestfit<<std::endl;
    std::cout<<integral<<std::endl;
    while(tot_sum/integral < levels[n_levels-1]){
  //  while(tot_sum < levels[n_levels-1]){
			 // std::cout << tot_sum/integral << std::endl;
        double max_val = tmp->GetMaximum();
        int max_bin = tmp->GetMaximumBin();
        tmp->SetBinContent(max_bin, -1);
        tot_sum += max_val;
        for(int i=0; i<n_levels; i++){
            if(tot_sum/integral < levels[i]){
            //if(tot_sum < levels[i]){
                contours[i] = max_val;

            }
        }
    }
}
*/

void get_intervals(TH2F *post, std::vector<double> levels, std::vector<double> &contours, int *bestfit){
    int n_levels = levels.size();
    double tot_level = 1000000;
    double integral = post->GetMaximum();
    TH2F *tmp = (TH2F*)post->Clone();
    *bestfit = tmp->GetMaximumBin();
    std::cout<<*bestfit<<std::endl;
    std::cout<<integral<<std::endl;

    while(tot_level/integral > levels[n_levels-1]){
  //  while(tot_sum < levels[n_levels-1]){
			 // std::cout << tot_sum/integral << std::endl;
        double max_val = tmp->GetMaximum();
        int max_bin = tmp->GetMaximumBin();
        tmp->SetBinContent(max_bin, -1);
        tot_level = max_val;
        for(int i=0; i<n_levels; i++){
            if(tot_level/integral > levels[i]){
            //if(tot_sum < levels[i]){
                contours[i] = max_val;

            }
        }
    }
}

void FormatHist(TH1F* h, int linecolor, int linestyle){
    h->SetStats(0);
    h->GetXaxis()->SetTitleFont(132);
    h->GetYaxis()->SetTitleFont(132);
    h->GetXaxis()->SetTitleSize(0.04);
    h->GetYaxis()->SetTitleSize(0.04);
    h->GetXaxis()->SetLabelFont(132);
    h->GetYaxis()->SetLabelFont(132);
    h->GetXaxis()->SetLabelSize(0.04);
    h->GetYaxis()->SetLabelSize(0.04);
    h->GetYaxis()->SetTitleOffset(1.3);
  h->GetYaxis()->SetTitle("Events");

  h->SetLineWidth(2);
  h->SetLineColor(linecolor);
  h->SetLineStyle(linestyle);
}
void make1DFOMS(std::string ifilename, std::string odir){

  
	SetT2KStyle(1);	
  const static int Nvars1D = 5;
  const static int Nvars2D = 1;
	
	//use nring for total signal and bacground

  std::string plot_title[Nvars1D] = {"ToWall", "DWall", "Evis", "ln(L_{2Rother}/L_{ee})", "ln(L_e/L_{#pi^0})"};
  std::string FOMvars1D[Nvars1D] = {"towall", "dwall", "fq1rmom", "nllr_2Rother_ee", "fqpi0nll_1D"};
 
  int FOMcuts1D[Nvars1D] = {1, 1, 2, 5, 6};
  // >0 is more than, <0 is less than
  int FOMcutDir1D[Nvars1D] = {1, 1, 1, -1, 1};
 // std::string FOMvars2D[Nvars2D] = {"fqpi0nll"};
  
  
	std::cout << "here\n " << std::endl;
  const static int NSigVars = 2;
  const static int NBkgVars = 14;
  std::string SignalName[NSigVars] = {"NC1pi0", "NCCoh"}; 
  std::string BkgName[NBkgVars] = {"CCqe", "CC1pi", "CCCoh", "CCmultipi", "CCDis", "NC1pipm", "NCOther", "CC2p2h", "NC1gamma", "CCmisc", "NCmpi", "NCEta", "NCDIS", "NCElastic"} ; 
	


	std::cout << "here\n " << std::endl;
	TFile ifile(Form("%s", ifilename.c_str()));
  TFile *ofile = TFile::Open(Form("%sFOMplots.root", odir.c_str()), "recreate"); 


	std::cout << "here\n " << std::endl;
  TH1D *init_BG = (TH1D*)ifile.Get(Form("%s_nring_histo_0", BkgName[0].c_str()));
  TH1D *init_SIG = (TH1D*)ifile.Get(Form("%s_nring_histo_0", SignalName[0].c_str()));

		double fomMax = 0;
		double effMax = 0;
		double purMax = 0;
		double fomMax_cut = 0;
  
	for (int FOMid=0; FOMid<Nvars1D; FOMid++){
    TH1F *FOM_BG = (TH1F*)ifile.Get(Form("%s_%s_histo_%d", BkgName[0].c_str(), FOMvars1D[FOMid].c_str(), FOMcuts1D[FOMid]));
    TH1F *FOM_SIG = (TH1F*)ifile.Get(Form("%s_%s_histo_%d", SignalName[0].c_str(), FOMvars1D[FOMid].c_str(), FOMcuts1D[FOMid]));

    for (int i=1; i<NBkgVars; i++){
			TH1F *temp_BG = (TH1F*)ifile.Get(Form("%s_%s_histo_%d", BkgName[i].c_str(), FOMvars1D[FOMid].c_str(), FOMcuts1D[FOMid]));
      FOM_BG->Add(temp_BG);
    }

    for (int i=1; i<NSigVars; i++){
      FOM_SIG->Add((TH1F*)ifile.Get(Form("%s_%s_histo_%d", SignalName[i].c_str(), FOMvars1D[FOMid].c_str(), FOMcuts1D[FOMid])));
    }
		

		FOM_BG->SetNameTitle(Form("%s Background", FOMvars1D[FOMid].c_str()),Form("%s Background", FOMvars1D[FOMid].c_str()) );
		FOM_SIG->SetNameTitle(Form("%s Signal", FOMvars1D[FOMid].c_str()),Form("%s Signal", FOMvars1D[FOMid].c_str()) );
	  FOM_BG->Write();
	  FOM_SIG->Write();
    double totSig = FOM_SIG->Integral();
    double totBkg = FOM_BG->Integral();
    TH1F* FOM_hist =  (TH1F*) FOM_SIG->Clone(0);
    TH1F* Eff_hist =  (TH1F*) FOM_SIG->Clone(0);
    TH1F* Pur_hist =  (TH1F*) FOM_SIG->Clone(0);
		FOM_hist->SetNameTitle(Form("%s FOM", FOMvars1D[FOMid].c_str()),Form("%s FOM", FOMvars1D[FOMid].c_str()) );
		Eff_hist->SetNameTitle(Form("%s Efficiency", FOMvars1D[FOMid].c_str()),Form("%s Efficiency", FOMvars1D[FOMid].c_str()) );
		Pur_hist->SetNameTitle(Form("%s Purity", FOMvars1D[FOMid].c_str()),Form("%s Purity", FOMvars1D[FOMid].c_str()) );
    int Nbins = FOM_hist->GetNbinsX();

    double cutval = 0;
    double cutBkg = 0;
    double cutSig = 0;
    
    double FOM_val = 0;
    double Eff_val = 0;
    double Pur_val = 0;


    for (int j=0; j<Nbins; j++){
      cutval = FOM_hist->GetBinLowEdge(j);
     	 
      cutBkg += FOM_BG->GetBinContent(j);
      cutSig += FOM_SIG->GetBinContent(j);

      if (FOMcutDir1D[FOMid] > 0) {
        FOM_val = GetFOM((totSig - cutSig), (totBkg - cutBkg));
        Eff_val = GetEff((totSig - cutSig), totSig);
        Pur_val = GetPur((totSig - cutSig), (totBkg - cutBkg));
      }
      else {
        FOM_val = GetFOM(cutSig, cutBkg);
        Eff_val = GetEff(cutSig, totSig);
        Pur_val = GetPur(cutSig, cutBkg);
      }
      FOM_hist->SetBinContent(j, FOM_val);
      Eff_hist->SetBinContent(j, Eff_val);
      Pur_hist->SetBinContent(j, Pur_val);
			
	//		std::cout << cutval << " " << totBkg - cutBkg << " " << totSig-cutSig << " " << Pur_val << std::endl;
			if (FOM_val> fomMax) {
				fomMax = FOM_val;
				effMax = Eff_val;
				purMax = Pur_val;
				fomMax_cut = cutval;
			}
					//	std::cout << cutval << " " << cutBkg << " " << cutSig << " " << FOM_val << std::endl;
    }
   FOM_hist->Write();
   Eff_hist->Write();
   Pur_hist->Write();
  	
		TCanvas c1("c7","FOM",30,10,800,900);
		//TEllipse *el1 = new TEllipse((175/ var2Dmax[FOMid][1])-0.1,(0.875/ var2Dmax[FOMid][0])-0.1,(175/ var2Dmax[FOMid][1])+0.1,(0.875/ var2Dmax[FOMid][0])+0.1);
		TLine* l2 = new TLine( fomMax_cut, 0,   fomMax_cut, fomMax);
		l2->SetLineStyle(2);
		FOM_hist->SetStats(0);
	//	FOM_hist.SetMinimum(8);
		FOM_hist->GetXaxis()->SetTitle(Form("%s", plot_title[FOMid].c_str()));
		FOM_hist->GetYaxis()->SetTitle("#frac{S}{#sqrt{S+B}}");
		FOM_hist->SetTitle(Form("%s FOM", FOMvars1D[FOMid].c_str()));
		FOM_hist->GetYaxis()->SetTitleOffset(1);
		FormatHist(FOM_hist, 4, 1);
		FOM_hist->Draw("hist");
		l2->Draw();
		//arw1->DrawLine( 0, 180,175 , 0);
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.12);
		c1.Update();
		c1.SaveAs(Form("%sFOM_%s.png", odir.c_str(), FOMvars1D[FOMid].c_str()) );

		TCanvas c2("c7","FOM",30,10,800,900);
		//TEllipse *el1 = new TEllipse((175/ var2Dmax[FOMid][1])-0.1,(0.875/ var2Dmax[FOMid][0])-0.1,(175/ var2Dmax[FOMid][1])+0.1,(0.875/ var2Dmax[FOMid][0])+0.1);
		l2 = new TLine( fomMax_cut, 0,   fomMax_cut, 1);
		Eff_hist->SetStats(0);
		Eff_hist->GetXaxis()->SetTitle(Form("%s", plot_title[FOMid].c_str()));
		Eff_hist->GetYaxis()->SetTitle("S_{sel}/S_{total}");
		Eff_hist->SetTitle(Form("%s Efficiency", FOMvars1D[FOMid].c_str()));
		Eff_hist->GetYaxis()->SetTitleOffset(1.2);
		FormatHist(Eff_hist, 4, 1);
		Eff_hist->Draw("hist");
		l2->Draw();
		//arw1->DrawLine( 0, 180,175 , 0);
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.12);
		c2.Update();
		c2.SaveAs(Form("%sEff_%s.png", odir.c_str(), FOMvars1D[FOMid].c_str()) );
	
		TCanvas c3("c7","FOM",30,10,800,900);
		//TEllipse *el1 = new TEllipse((175/ var2Dmax[FOMid][1])-0.1,(0.875/ var2Dmax[FOMid][0])-0.1,(175/ var2Dmax[FOMid][1])+0.1,(0.875/ var2Dmax[FOMid][0])+0.1);
		l2 = new TLine( fomMax_cut, 0,   fomMax_cut, 1);
		Pur_hist->SetStats(0);
		Pur_hist->GetXaxis()->SetTitle(Form("%s", plot_title[FOMid].c_str()));
		Pur_hist->GetYaxis()->SetTitle("S_{sel}/(S_{sel}+B_{sel})");
		Pur_hist->SetTitle(Form("%s Purity", FOMvars1D[FOMid].c_str()));
		Pur_hist->GetYaxis()->SetTitleOffset(1);
		FormatHist(Pur_hist, 4, 1);
		Pur_hist->Draw("hist");
		l2->Draw();
		//arw1->DrawLine( 0, 180,175 , 0);
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.12);
		c2.Update();
		c3.SaveAs(Form("%sPUR_%s.png", odir.c_str(), FOMvars1D[FOMid].c_str()) );

	}

  ofile->Close();
}





void make2DFOMS(std::string ifilename, std::string odir){
	TFile ifile(Form("%s", ifilename.c_str()));
 	TFile *ofile = TFile::Open(Form("%s2DFOMplots.root", odir.c_str()), "recreate"); 

	const static int Nvar2D = 2;
  std::string FOMvar2D[Nvar2D] = {"fqpi0nll", "nllr_pi0mom_2Ree"};
  int FOMcuts2D[Nvar2D] = {6, 5};
 // >0 is more than, <0 is less than
  int FOMcutDir2D[Nvar2D] = {1, -1};
  bool FOMcut2Dmore[Nvar2D] = {true, false};
  double var2Dmax[Nvar2D][2] = {{1000, 2.0}, {1000.0, 1.0}};
  double var2Dmin[Nvar2D][2] = {{0.0, -10.0}, {-200.0, -10.0}};
  double var2Dstep[Nvar2D][2] = {{10, 0.05}, {10.0, 0.01}};
 // double var2Dmax[Nvar2D][2] = {{850, 5.0}, {500, 5.0}};
 // double var2Dmin[Nvar2D][2] = {{150, 0.0}, {-200, -1}};
 // double var2Dstep[Nvar2D][2] = {{10, 0.05}, {5, 0.05}};

  const static int NSigVars = 2;
  const static int NBkgVars = 14;
  std::string SignalName[NSigVars] = {"NC1pi0", "NCCoh"}; 
  std::string BkgName[NBkgVars] = {"CCqe", "CC1pi", "CCCoh", "CCmultipi", "CCDis", "NC1pipm", "NCOther", "CC2p2h", "NC1gamma", "CCmisc", "NCmpi", "NCEta", "NCDIS", "NCElastic"} ; 
	
	TH2F* FOM_BG;
	TH2F* FOM_SIG;
	TH2F FOM_hist;
	TH2F FOM_cont;
	TH2F EFF_hist;
	TH2F PUR_hist;
	double fomMax = 0;
	double fomMax_A = 0;
	double fomMax_B = 0;

	for (int FOMid=0; FOMid<Nvar2D; FOMid++){
		std::ofstream file;
		file.open("FOMdata.txt");

    TH2F* FOM_BG = (TH2F*)ifile.Get(Form("%s_%s_histo_%d", BkgName[0].c_str(), FOMvar2D[FOMid].c_str(), FOMcuts2D[FOMid]));
    TH2F* FOM_SIG = (TH2F*)ifile.Get(Form("%s_%s_histo_%d", SignalName[0].c_str(), FOMvar2D[FOMid].c_str(), FOMcuts2D[FOMid]));
    TH2F* tot_SIG = (TH2F*)ifile.Get(Form("%s_nring_histo_0", SignalName[0].c_str()));

    for (int i=1; i<NBkgVars; i++){
      FOM_BG->Add((TH2F*)ifile.Get(Form("%s_%s_histo_%d", BkgName[i].c_str(), FOMvar2D[FOMid].c_str(), FOMcuts2D[FOMid])));
    }

    for (int i=1; i<NSigVars; i++){
      FOM_SIG->Add((TH2F*)ifile.Get(Form("%s_%s_histo_%d", SignalName[i].c_str(), FOMvar2D[FOMid].c_str(), FOMcuts2D[FOMid])));
      tot_SIG->Add((TH2F*)ifile.Get(Form("%s_nring_histo_0", SignalName[i].c_str())));
    }
		
		//ifile.Close();	
		//Variable plts
    int fomNBinsX = FOM_SIG->GetNbinsX();
    int fomNBinsY = FOM_SIG->GetNbinsY();

		double allSig = tot_SIG->Integral();
    double totSig = FOM_SIG->Integral();
    double totBkg = FOM_BG->Integral();
    int NBinsX = (var2Dmax[FOMid][0] - var2Dmin[FOMid][0])/var2Dstep[FOMid][0];
    int NBinsY = (var2Dmax[FOMid][1] - var2Dmin[FOMid][1])/var2Dstep[FOMid][1];
		
		TH2F* FOM_SEL = (TH2F*)FOM_SIG->Clone();
		FOM_SEL->Reset("ICESM");


		//FOM plots
    FOM_hist =  TH2F(Form("FOM_%s", FOMvar2D[FOMid].c_str()), "", NBinsX, var2Dmin[FOMid][0], var2Dmax[FOMid][0], NBinsY, var2Dmin[FOMid][1], var2Dmax[FOMid][1]);
    FOM_cont =  TH2F(Form("FOM_%s", FOMvar2D[FOMid].c_str()), "", NBinsX, var2Dmin[FOMid][0], var2Dmax[FOMid][0], NBinsY, var2Dmin[FOMid][1], var2Dmax[FOMid][1]);
    EFF_hist =  TH2F(Form("EFF_%s", FOMvar2D[FOMid].c_str()), "", NBinsX, var2Dmin[FOMid][0], var2Dmax[FOMid][0], NBinsY, var2Dmin[FOMid][1], var2Dmax[FOMid][1]);
    PUR_hist =  TH2F(Form("PUR_%s", FOMvar2D[FOMid].c_str()), "", NBinsX, var2Dmin[FOMid][0], var2Dmax[FOMid][0], NBinsY, var2Dmin[FOMid][1], var2Dmax[FOMid][1]);

    double cutvarA = 0;
    double cutvarB = 0;
    double fomBinLocX = 0;
    double fomBinLocY = 0;
		fomMax = 0;
		double effMax = 0;
		double purMax = 0;
		fomMax_A = 0;
		fomMax_B = 0;
		//Loop through bins in FOM plots
    for (int i=0; i<=NBinsX; i++) {
      for (int j=0; j<=NBinsY; j++) {
			//	std::cout << "Bin (" << i << ", " << j << ") of (" << NBinsX << ", " << NBinsY << ")" <<std::endl;
		//	file << "#####################################################################################" << std::endl;	
				//cutSig -> Signal selected by cut
				//cutBkg -> Background that makes the cut
    		double cutSig = 0;
    		double cutBkg = 0;	
        cutvarB = var2Dmin[FOMid][0] + i * var2Dstep[FOMid][0];
        cutvarA = var2Dmin[FOMid][1] + j * var2Dstep[FOMid][1];
				
				//Loop through variable plot bins
        for (int k=0; k<=fomNBinsX; k++){
          for (int l=0; l<=fomNBinsY; l++){
            //save time by calculating these?
						//either p/m 0.5
						//fomBinLocX = var2Dmin[FOMid][0] + ((k-0.5) * var2Dstep[FOMid][0]); 
						//fomBinLocY = var2Dmin[FOMid][1] + ((l-0.5) * var2Dstep[FOMid][1]); 
            fomBinLocX = FOM_SIG->GetXaxis()->GetBinCenter(k);
            fomBinLocY = FOM_SIG->GetYaxis()->GetBinCenter(l);
						if (FOMcutDir2D[FOMid] > 0) {
							if (fomBinLocY > (cutvarB + cutvarA * fomBinLocX)) {
							//	file << fomBinLocY << " " << cutvarB + cutvarA * fomBinLocX << " " << cutvarA <<  " " << cutvarB << " " << fomBinLocX << " " << k << " " << l << " " <<var2Dmin[FOMid][1] << " " <<var2Dstep[FOMid][1] << " in" << std::endl;
								cutSig += FOM_SIG->GetBinContent(FOM_SIG->GetBin(k, l));
								cutBkg += FOM_BG->GetBinContent(FOM_BG->GetBin(k, l));
							} else {

							//	file << fomBinLocY << " " << cutvarB + cutvarA * fomBinLocX << " " << cutvarA <<  " " << cutvarB << " " << fomBinLocX << " " << k << " " << l << " out" << std::endl;
								}
						} else {
							if (fomBinLocY < (cutvarB + cutvarA * fomBinLocX)) {
							/*	if (FOMid == 1) {
								file << cutvarB << " " << cutvarA << " " << FOM_SIG->GetBinContent(FOM_SIG->GetBin(k, l)) <<  " " << FOM_SIG->GetBin(k, l) <<std::endl;
								}*/
								//std::cout << FOM_SIG->GetBinContent(FOM_SIG->GetBin(k, l)) <<  " " << FOM_SIG->GetBin(k, l) <<std::endl;
								cutSig += FOM_SIG->GetBinContent(FOM_SIG->GetBin(k, l));
								cutBkg += FOM_BG->GetBinContent(FOM_BG->GetBin(k, l));
							}

						}

          }
     		}
       //	std::cout << cutSig <<", " << cutBkg <<", " << GetFOM(cutSig, cutBkg) <<", "<< FOM_hist.GetBin(i,j) << std::endl; 
        //FOM_hist.SetBinContent(FOM_hist.GetBin(i, j), GetFOM(cutSig, cutBkg));
        FOM_hist.SetBinContent(i, j, GetFOM(cutSig, cutBkg));
        FOM_cont.SetBinContent(i, j, GetFOM(cutSig, cutBkg));
        EFF_hist.SetBinContent(i, j, GetEff(cutSig, allSig));
        PUR_hist.SetBinContent(i, j, GetPur(cutSig, cutBkg));
				if (GetFOM(cutSig, cutBkg) > fomMax) {
					fomMax = GetFOM(cutSig, cutBkg);
					effMax = GetEff(cutSig, allSig);
					purMax = GetPur(cutSig, cutBkg);
					fomMax_A = cutvarA;
					fomMax_B = cutvarB;
				}
				if (FOMid == 1){
			//	file << cutSig << " " << cutBkg << " " << GetFOM(cutSig, cutBkg) << " " <<  GetEff(cutSig, allSig)<< " " << GetPur(cutSig, cutBkg) << " " << cutvarA << " " << cutvarB <<std::endl;
				}
         for (int k=0; k<=fomNBinsX; k++){
          for (int l=0; l<=fomNBinsY; l++){
								FOM_SEL->SetBinContent(k, l, 0);
            fomBinLocX = FOM_SIG->GetXaxis()->GetBinCenter(k);
            fomBinLocY = FOM_SIG->GetYaxis()->GetBinCenter(l);
						if (FOMcutDir2D[FOMid] > 0) {
							if (fomBinLocY > (fomMax_B + fomMax_A * fomBinLocX)) {

								FOM_SEL->SetBinContent(k, l,FOM_BG->GetBinContent(FOM_BG->GetBin(k, l)) + FOM_SIG->GetBinContent(FOM_SIG->GetBin(k, l)));
							}
						} else {
							if (fomBinLocY < (fomMax_B + fomMax_A * fomBinLocX)) {
								FOM_SEL->SetBinContent(k, l,FOM_BG->GetBinContent(FOM_BG->GetBin(k, l)) + FOM_SIG->GetBinContent(FOM_SIG->GetBin(k, l)));
							//	FOM_SEL->SetBinContent(k, l, 0);
							}

						}

          }
     		}
    


			}

    }
	
	 file.close();

   FOM_hist.Write();
   EFF_hist.Write();
   PUR_hist.Write();
	
 	TH2F* contHists[Nvar2D][4] = {{0}};
  
  std::vector<double> contour_levels;
	contour_levels.push_back(0.999);
  contour_levels.push_back(0.99);
  contour_levels.push_back(0.95);
  contour_levels.push_back(0.9);

	std::cout << "here" <<std::endl;
	std::vector<double> contour;
	contour.resize(contour_levels.size());
	int bestbin;
	get_intervals(&FOM_hist, contour_levels, contour, &bestbin);
	std::cout << "here" <<std::endl;

	for(int i=0; i<contour.size(); i++){
			const double val = contour[i];
			contHists[FOMid][i] = (TH2F*) FOM_hist.Clone(Form("contour_%i", i));
		//	contHists[FOMid][i]->SetTitle();
			contHists[FOMid][i]->SetContour(1, &val);
		//	std::cout<< i << " " << val<< " " << contour[i] << std::endl;
			
			//contHists[FOMid][i]->Write();
	}


	std::cout << "For variable: " << FOMvar2D[FOMid] << std::endl;
	std::cout << "Max FOM: " << fomMax << std::endl;
	std::cout << "Max FOM Eff: " << effMax << std::endl;
	std::cout << "Max FOM Pur: " << purMax << std::endl;
	std::cout << "Max FOM A: " << fomMax_A << std::endl;
	std::cout << "Max FOM B: " << fomMax_B << std::endl;
	
	//FOM_cont = FOM_hist.Clone();
//	FOM_cont.SetContourLevel(fomMax, fomMax - 1);
//	FOM_cont.SetContour(3, contour_levels);
	
	


	TArrow *arw1 = new TArrow();
  TArrow *arw2 = new TArrow();
  arw1->SetLineColor(kOrange);
  arw2->SetLineColor(kOrange);
  arw1->SetLineWidth(3);
  arw2->SetLineWidth(3);

	double contColour[contour.size()] = {kWhite, kGray+1, kGray+3, kBlack};
	
//fqpi0nll
	if (FOMid == 0){
	
		TCanvas c1("c7","FOM",30,10,800,900);
		//TEllipse *el1 = new TEllipse((175/ var2Dmax[FOMid][1])-0.1,(0.875/ var2Dmax[FOMid][0])-0.1,(175/ var2Dmax[FOMid][1])+0.1,(0.875/ var2Dmax[FOMid][0])+0.1);
		TEllipse *el1 = new TEllipse(175,-0.875,10, 0.025);
		TLine* l1 = new TLine(fomMax_B, var2Dmin[FOMid][1], fomMax_B, var2Dmax[FOMid][1]);
		TLine* l2 = new TLine(var2Dmin[FOMid][0], fomMax_A, var2Dmax[FOMid][0],  fomMax_A);
		gStyle->SetPalette(kRainBow);
		gStyle->SetNumberContours(256);
		FOM_hist.SetStats(0);
	//	FOM_hist.SetMinimum(8);
		FOM_hist.GetXaxis()->SetTitle("B");
		FOM_hist.GetYaxis()->SetTitle("A");
		FOM_hist.SetTitle("ln(L_{#pi}/L_{e}) > B - A #times M_{#pi^0}^{reco} FOM");
		FOM_hist.GetYaxis()->SetTitleOffset(1.75);
		FOM_hist.Draw("colz");
    for(int i=0; i<contour.size(); i++){
       // TH2D *onesig =(TH2D*)in->Get(Form("contour_%i", i))->Clone();
        contHists[FOMid][i]->Smooth(1);
        contHists[FOMid][i]->SetLineColor(contColour[i]);
     //   contHists[FOMid][i]->SetOptStat(0);
        contHists[FOMid][i]->Draw("cont3 same");
    }

		//FOM_cont.Draw("cont3 same");
		l1->Draw();
		l2->Draw();
		el1->Draw();
		//arw1->DrawLine( 0, 180,175 , 0);
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.12);
		c1.Update();
		c1.SaveAs(Form("%sFOM_%s.png", odir.c_str(), FOMvar2D[FOMid].c_str()) );
	

	/////zoom z axis
		TCanvas c1_zoom("c7","FOM",30,10,800,900);
		//TEllipse *el1 = new TEllipse((175/ var2Dmax[FOMid][1])-0.1,(0.875/ var2Dmax[FOMid][0])-0.1,(175/ var2Dmax[FOMid][1])+0.1,(0.875/ var2Dmax[FOMid][0])+0.1);
		gStyle->SetPalette(kRainBow);
		gStyle->SetNumberContours(256);
		FOM_hist.SetStats(0);
		FOM_hist.SetMinimum(fomMax*0.99);
		FOM_hist.GetXaxis()->SetTitle("B");
		FOM_hist.GetYaxis()->SetTitle("A");
		FOM_hist.SetTitle("ln(L_{#pi}/L_{e}) > B - A #times M_{#pi^0}^{reco} FOM Top 99%");
		FOM_hist.GetYaxis()->SetTitleOffset(1.75);
		FOM_hist.Draw("colz");

		//FOM_cont.Draw("cont3 same");
		l1->Draw();
		l2->Draw();
		el1->Draw();
		//arw1->DrawLine( 0, 180,175 , 0);
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.12);
		c1_zoom.Update();
		c1_zoom.SaveAs(Form("%sFOM_zoom_%s.png", odir.c_str(), FOMvar2D[FOMid].c_str()) );

		TCanvas c2("c2","Eff",30,10,800,900);
		//TEllipse *el1 = new TEllipse((175/ var2Dmax[FOMid][1])-0.1,(0.875/ var2Dmax[FOMid][0])-0.1,(175/ var2Dmax[FOMid][1])+0.1,(0.875/ var2Dmax[FOMid][0])+0.1);
		el1 = new TEllipse(175,0.875,10, 0.025);
		l1 = new TLine(fomMax_B, var2Dmin[FOMid][1], fomMax_B, var2Dmax[FOMid][1]);
		l2 = new TLine(var2Dmin[FOMid][0], fomMax_A, var2Dmax[FOMid][0],  fomMax_A);
		gStyle->SetPalette(kRainBow);
		gStyle->SetNumberContours(256);
		EFF_hist.SetStats(0);
		EFF_hist.GetXaxis()->SetTitle("B");
		EFF_hist.GetYaxis()->SetTitle("A");
		EFF_hist.SetTitle("ln(L_{#pi}/L_{e}) > B - A #times M_{#pi^0}^{reco} Eff");
		EFF_hist.GetYaxis()->SetTitleOffset(1.75);
		EFF_hist.Draw("colz");
	//  FOM_cont.Draw("cont3 same");
		l1->Draw();
		l2->Draw();
		el1->Draw();
		//arw1->DrawLine( 0, 180,175 , 0);
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.12);
		c2.Update();
		c2.SaveAs(Form("%sEff_%s.png", odir.c_str(), FOMvar2D[FOMid].c_str()) );

		TCanvas c3("c3","Pur",30,10,800,900);
		//TEllipse *el1 = new TEllipse((175/ var2Dmax[FOMid][1])-0.1,(0.875/ var2Dmax[FOMid][0])-0.1,(175/ var2Dmax[FOMid][1])+0.1,(0.875/ var2Dmax[FOMid][0])+0.1);
		el1 = new TEllipse(175,0.875,10, 0.025);
		l1 = new TLine(fomMax_B, var2Dmin[FOMid][1], fomMax_B, var2Dmax[FOMid][1]);
		l2 = new TLine(var2Dmin[FOMid][0], fomMax_A, var2Dmax[FOMid][0],  fomMax_A);
		gStyle->SetPalette(kRainBow);
		gStyle->SetNumberContours(256);
		PUR_hist.SetStats(0);
		PUR_hist.GetXaxis()->SetTitle("B");
		PUR_hist.GetYaxis()->SetTitle("A");
		PUR_hist.SetTitle("ln(L_{#pi}/L_{e}) > B - A #times M_{#pi^0}^{reco} Purity");
		PUR_hist.GetYaxis()->SetTitleOffset(1.75);
		PUR_hist.Draw("colz");
	//  FOM_cont.Draw("cont3 same");
		l1->Draw();
		l2->Draw();
		el1->Draw();
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.12);
		c3.Update();
		c3.SaveAs(Form("%sPUR_%s.png", odir.c_str(), FOMvar2D[FOMid].c_str()) );
		


		double x_int = 0;

		TCanvas c_var_epi0PID("c_var_epi0PID","Pur",30,10,800,900);
		//TEllipse *el1 = new TEllipse((175/ var2Dmax[FOMid][1])-0.1,(0.875/ var2Dmax[FOMid][0])-0.1,(175/ var2Dmax[FOMid][1])+0.1,(0.875/ var2Dmax[FOMid][0])+0.1);
		//TLine* minline = new TLine(0, y intercept, x intercept, 0);
		TLine* minline = new TLine(FOM_BG->GetXaxis()->GetXmin(), var2Dmin[FOMid][0] + FOM_BG->GetXaxis()->GetXmin() * var2Dmin[FOMid][1], 
																FOM_BG->GetXaxis()->GetXmax(), var2Dmin[FOMid][0]+ FOM_BG->GetXaxis()->GetXmax() * var2Dmin[FOMid][1]);
		TLine* bestline = new TLine(FOM_BG->GetXaxis()->GetXmin(), fomMax_B + FOM_BG->GetXaxis()->GetXmin() * fomMax_A, 
																FOM_BG->GetXaxis()->GetXmax(), fomMax_B+ FOM_BG->GetXaxis()->GetXmax() * fomMax_A);
		TLine* maxline = new TLine(FOM_BG->GetXaxis()->GetXmin(), var2Dmax[FOMid][0] + FOM_BG->GetXaxis()->GetXmin() * var2Dmax[FOMid][1], 
																FOM_BG->GetXaxis()->GetXmax(), var2Dmax[FOMid][0]+ FOM_BG->GetXaxis()->GetXmax() * var2Dmax[FOMid][1]);
		bestline->SetLineColor(kRed);
		bestline->SetLineWidth(3);
		gStyle->SetPalette(kRainBow);
		gStyle->SetNumberContours(256);
		FOM_BG->SetStats(0);
		FOM_BG->GetXaxis()->SetTitle("M_{#pi^0}^{reco}");
		FOM_BG->GetYaxis()->SetTitle("ln(L_{#pi}/L_{e})");
		FOM_BG->SetTitle("ln(L_{#pi}/L_{e}) > B - A #times M_{#pi^0}^{reco} ");
		FOM_BG->GetYaxis()->SetTitleOffset(1.75);
		FOM_BG->Draw("colz");
	//  FOM_cont.Draw("cont3 same");
	//	minline->Draw();
//		maxline->Draw();
		bestline->Draw();
		arw1->DrawLine( 0, 180,175 , 0);
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.12);
		c_var_epi0PID.Update();
		c_var_epi0PID.SaveAs(Form("%sepi0PID_%s.png", odir.c_str(), FOMvar2D[FOMid].c_str()) );
	
		TCanvas c_var_sig("c_var_epi0PID","Pur",30,10,800,900);
		//TEllipse *el1 = new TEllipse((175/ var2Dmax[FOMid][1])-0.1,(0.875/ var2Dmax[FOMid][0])-0.1,(175/ var2Dmax[FOMid][1])+0.1,(0.875/ var2Dmax[FOMid][0])+0.1);
		//TLine* minline = new TLine(0, y intercept, x intercept, 0);
		minline = new TLine(FOM_BG->GetXaxis()->GetXmin(), var2Dmin[FOMid][0] + FOM_BG->GetXaxis()->GetXmin() * var2Dmin[FOMid][1], 
																FOM_BG->GetXaxis()->GetXmax(), var2Dmin[FOMid][0]+ FOM_BG->GetXaxis()->GetXmax() * var2Dmin[FOMid][1]);
		bestline = new TLine(FOM_BG->GetXaxis()->GetXmin(), fomMax_B + FOM_BG->GetXaxis()->GetXmin() * fomMax_A, 
																FOM_BG->GetXaxis()->GetXmax(), fomMax_B+ FOM_BG->GetXaxis()->GetXmax() * fomMax_A);
		maxline = new TLine(FOM_BG->GetXaxis()->GetXmin(), var2Dmax[FOMid][0] + FOM_BG->GetXaxis()->GetXmin() * var2Dmax[FOMid][1], 
																FOM_BG->GetXaxis()->GetXmax(), var2Dmax[FOMid][0]+ FOM_BG->GetXaxis()->GetXmax() * var2Dmax[FOMid][1]);
		bestline->SetLineColor(kRed);
		bestline->SetLineWidth(3);
		gStyle->SetPalette(kRainBow);
		gStyle->SetNumberContours(256);
		FOM_SIG->SetStats(0);
		FOM_SIG->GetXaxis()->SetTitle("M_{#pi^0}^{reco}");
		FOM_SIG->GetYaxis()->SetTitle("ln(L_{#pi}/L_{e})");
		FOM_SIG->SetTitle("ln(L_{#pi}/L_{e}) > B - A #times M_{#pi^0}^{reco} Signal");
		FOM_SIG->GetYaxis()->SetTitleOffset(1.75);
		FOM_SIG->Draw("colz");
	//  FOM_cont.Draw("cont3 same");
		//minline->Draw();
		//maxline->Draw();
		bestline->Draw();
		arw1->DrawLine( 0, 180,175 , 0);
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.12);
		c_var_sig.Update();
		c_var_sig.SaveAs(Form("%sepi0PID_sig_%s.png", odir.c_str(), FOMvar2D[FOMid].c_str()) );

		TCanvas c_var_sel("c_var_epi0PID_sel","Pur",30,10,800,900);
		//TEllipse *el1 = new TEllipse((175/ var2Dmax[FOMid][1])-0.1,(0.875/ var2Dmax[FOMid][0])-0.1,(175/ var2Dmax[FOMid][1])+0.1,(0.875/ var2Dmax[FOMid][0])+0.1);
		//TLine* minline = new TLine(0, y intercept, x intercept, 0);
		minline = new TLine(FOM_BG->GetXaxis()->GetXmin(), var2Dmin[FOMid][0] + FOM_BG->GetXaxis()->GetXmin() * var2Dmin[FOMid][1], 
																FOM_BG->GetXaxis()->GetXmax(), var2Dmin[FOMid][0]+ FOM_BG->GetXaxis()->GetXmax() * var2Dmin[FOMid][1]);
		bestline = new TLine(FOM_BG->GetXaxis()->GetXmin(), fomMax_B + FOM_BG->GetXaxis()->GetXmin() * fomMax_A, 
																FOM_BG->GetXaxis()->GetXmax(), fomMax_B+ FOM_BG->GetXaxis()->GetXmax() * fomMax_A);
		maxline = new TLine(FOM_BG->GetXaxis()->GetXmin(), var2Dmax[FOMid][0] + FOM_BG->GetXaxis()->GetXmin() * var2Dmax[FOMid][1], 
																FOM_BG->GetXaxis()->GetXmax(), var2Dmax[FOMid][0]+ FOM_BG->GetXaxis()->GetXmax() * var2Dmax[FOMid][1]);
		bestline->SetLineColor(kRed);
		bestline->SetLineWidth(3);
		gStyle->SetPalette(kRainBow);
		gStyle->SetNumberContours(256);
		FOM_SEL->SetStats(0);
		FOM_SEL->GetXaxis()->SetTitle("M_{#pi^0}^{reco}");
		FOM_SEL->GetYaxis()->SetTitle("ln(L_{#pi}/L_{e})");
		FOM_SEL->SetTitle("ln(L_{#pi}/L_{e}) > B - A #times M_{#pi^0}^{reco} Signal");
		FOM_SEL->GetYaxis()->SetTitleOffset(1.75);
		FOM_SEL->Draw("colz");
	//  FOM_cont.Draw("cont3 same");
		//minline->Draw();
		//maxline->Draw();
		bestline->Draw();
		arw1->DrawLine( 0, 180,175 , 0);
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.12);
		c_var_sel.Update();
		c_var_sel.SaveAs(Form("%sepi0PID_sel_%s.png", odir.c_str(), FOMvar2D[FOMid].c_str()) );
	
	}



	///////////////////////2Rother_ee ///////////////////////////////////
	if(FOMid == 1){
		TCanvas c1_fom("c7","FOM",30,10,800,900);
		//TEllipse *el1 = new TEllipse((175/ var2Dmax[FOMid][1])-0.1,(0.875/ var2Dmax[FOMid][0])-0.1,(175/ var2Dmax[FOMid][1])+0.1,(0.875/ var2Dmax[FOMid][0])+0.1);
	//	TEllipse *el1 = new TEllipse(175,0.875,10, 0.025);
		TLine* l1 = new TLine(fomMax_B, var2Dmin[FOMid][1], fomMax_B, var2Dmax[FOMid][1]);
		TLine* l2 = new TLine(var2Dmin[FOMid][0], fomMax_A, var2Dmax[FOMid][0],  fomMax_A);
		gStyle->SetPalette(kRainBow);
		gStyle->SetNumberContours(256);
		FOM_hist.SetStats(0);
	//	FOM_hist.SetMinimum(8);
		FOM_hist.GetXaxis()->SetTitle("B");
		FOM_hist.GetYaxis()->SetTitle("A");
		FOM_hist.SetTitle("ln(L_{2Rother}/L_{ee}) > B - A #times P_{#pi^0}^{reco} FOM");
		FOM_hist.GetYaxis()->SetTitleOffset(1.75);
		FOM_hist.Draw("colz");

    for(int i=0; i<contour.size(); i++){
       // TH2D *onesig =(TH2D*)in->Get(Form("contour_%i", i))->Clone();
        contHists[FOMid][i]->Smooth(1);
        contHists[FOMid][i]->SetLineColor(contColour[i]);
     //   contHists[FOMid][i]->SetOptStat(0);
        contHists[FOMid][i]->Draw("cont3 same");
    }
		//FOM_cont.Draw("cont3 same");
		l1->Draw();
		l2->Draw();
	//	el1->Draw();
		//arw1->DrawLine( 0, 180,175 , 0);
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.12);
		c1_fom.Update();
		c1_fom.SaveAs(Form("%sFOM_%s.png", odir.c_str(), FOMvar2D[FOMid].c_str()) );
		
		///zoom z axis
		TCanvas c1_fom_zoom("c7","FOM",30,10,800,900);
		//TEllipse *el1 = new TEllipse((175/ var2Dmax[FOMid][1])-0.1,(0.875/ var2Dmax[FOMid][0])-0.1,(175/ var2Dmax[FOMid][1])+0.1,(0.875/ var2Dmax[FOMid][0])+0.1);
	//	TEllipse *el1 = new TEllipse(175,0.875,10, 0.025);
		gStyle->SetPalette(kRainBow);
		gStyle->SetNumberContours(256);
		FOM_hist.SetStats(0);
		FOM_hist.SetMinimum(fomMax*0.99);
		FOM_hist.GetXaxis()->SetTitle("B");
		FOM_hist.GetYaxis()->SetTitle("A");
		FOM_hist.SetTitle("ln(L_{2Rother}/L_{ee}) > B - A #times P_{#pi^0}^{reco} FOM Top 99%");
		FOM_hist.GetYaxis()->SetTitleOffset(1.75);
		FOM_hist.Draw("colz");
		//FOM_cont.Draw("cont3 same");
		l1->Draw();
		l2->Draw();
	//	el1->Draw();
		//arw1->DrawLine( 0, 180,175 , 0);
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.12);
		c1_fom_zoom.Update();
		c1_fom_zoom.SaveAs(Form("%sFOM_zoom_%s.png", odir.c_str(), FOMvar2D[FOMid].c_str()) );

		TCanvas c1_eff("c2","Eff",30,10,800,900);
		//TEllipse *el1 = new TEllipse((175/ var2Dmax[FOMid][1])-0.1,(0.875/ var2Dmax[FOMid][0])-0.1,(175/ var2Dmax[FOMid][1])+0.1,(0.875/ var2Dmax[FOMid][0])+0.1);
	//	el1 = new TEllipse(175,0.875,10, 0.025);
		l1 = new TLine(fomMax_B, var2Dmin[FOMid][1], fomMax_B, var2Dmax[FOMid][1]);
		l2 = new TLine(var2Dmin[FOMid][0], fomMax_A, var2Dmax[FOMid][0],  fomMax_A);
		gStyle->SetPalette(kRainBow);
		gStyle->SetNumberContours(256);
		EFF_hist.SetStats(0);
		EFF_hist.GetXaxis()->SetTitle("B");
		EFF_hist.GetYaxis()->SetTitle("A");
		EFF_hist.SetTitle("ln(L_{2Rother}/L_{ee}) > B - A #times P_{#pi^0}^{reco} Eff");
		EFF_hist.GetYaxis()->SetTitleOffset(1.75);
		EFF_hist.Draw("colz");
	//  FOM_cont.Draw("cont3 same");
		l1->Draw();
		l2->Draw();
		//el1->Draw();
		//arw1->DrawLine( 0, 180,175 , 0);
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.12);
		c1_eff.Update();
		c1_eff.SaveAs(Form("%sEff_%s.png", odir.c_str(), FOMvar2D[FOMid].c_str()) );

		TCanvas c1_pur("c3","Pur",30,10,800,900);
		//TEllipse *el1 = new TEllipse((175/ var2Dmax[FOMid][1])-0.1,(0.875/ var2Dmax[FOMid][0])-0.1,(175/ var2Dmax[FOMid][1])+0.1,(0.875/ var2Dmax[FOMid][0])+0.1);
	//	el1 = new TEllipse(175,0.875,10, 0.025);
		l1 = new TLine(fomMax_B, var2Dmin[FOMid][1], fomMax_B, var2Dmax[FOMid][1]);
		l2 = new TLine(var2Dmin[FOMid][0], fomMax_A, var2Dmax[FOMid][0],  fomMax_A);
		gStyle->SetPalette(kRainBow);
		gStyle->SetNumberContours(256);
		PUR_hist.SetStats(0);
		PUR_hist.GetXaxis()->SetTitle("B");
		PUR_hist.GetYaxis()->SetTitle("A");
		PUR_hist.SetTitle("ln(L_{2Rother}/L_{ee}) > B - A #times P_{#pi^0}^{reco} Purity");
		PUR_hist.GetYaxis()->SetTitleOffset(1.75);
		PUR_hist.Draw("colz");
	//  FOM_cont.Draw("cont3 same");
		l1->Draw();
		l2->Draw();
	//	el1->Draw();
	//	arw1->DrawLine( 0, 180,175 , 0);
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.12);
		c1_pur.Update();
		c1_pur.SaveAs(Form("%sPUR_%s.png", odir.c_str(), FOMvar2D[FOMid].c_str()) );
		


		double x_int = 0;

		TCanvas c1_var("c_var_epi0PID","Pur",30,10,800,900);
		//TEllipse *el1 = new TEllipse((175/ var2Dmax[FOMid][1])-0.1,(0.875/ var2Dmax[FOMid][0])-0.1,(175/ var2Dmax[FOMid][1])+0.1,(0.875/ var2Dmax[FOMid][0])+0.1);
		//TLine* minline = new TLine(0, y intercept, x intercept, 0);
		TLine* minline = new TLine(FOM_BG->GetXaxis()->GetXmin(), var2Dmin[FOMid][0] +  FOM_BG->GetXaxis()->GetXmin() * var2Dmin[FOMid][1], 
																FOM_BG->GetXaxis()->GetXmax(), var2Dmin[FOMid][0] + FOM_BG->GetXaxis()->GetXmax() * var2Dmin[FOMid][1]);
		TLine* bestline = new TLine(FOM_BG->GetXaxis()->GetXmin(), fomMax_B + FOM_BG->GetXaxis()->GetXmin() * fomMax_A, 
																FOM_BG->GetXaxis()->GetXmax(), fomMax_B + FOM_BG->GetXaxis()->GetXmax() * fomMax_A);
		TLine* maxline = new TLine(FOM_BG->GetXaxis()->GetXmin(), var2Dmax[FOMid][0] + FOM_BG->GetXaxis()->GetXmin() * var2Dmax[FOMid][1], 
																FOM_BG->GetXaxis()->GetXmax(), var2Dmax[FOMid][0] + FOM_BG->GetXaxis()->GetXmax() * var2Dmax[FOMid][1]);
		bestline->SetLineColor(kRed);
		bestline->SetLineWidth(3);
		gStyle->SetPalette(kRainBow);
		gStyle->SetNumberContours(256);
		FOM_BG->SetStats(0);
		FOM_BG->GetXaxis()->SetTitle("P_{#pi^0}^{reco}");
		FOM_BG->GetYaxis()->SetTitle("ln(L_{2Rother}/L_{ee})");
		FOM_BG->SetTitle("ln(L_{2Rother}/L_{ee}) < B - A #times P_{#pi^0}^{reco} ");
		FOM_BG->GetYaxis()->SetTitleOffset(1.75);
		FOM_BG->Draw("colz");
	  FOM_cont.Draw("cont3 same");
//		minline->Draw();
//	maxline->Draw();
		bestline->Draw();
		arw1->DrawLine( 0, 100,FOM_BG->GetXaxis()->GetXmax() , 100);
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.12);
		c1_var.Update();
		c1_var.SaveAs(Form("%svar_%s.png", odir.c_str(), FOMvar2D[FOMid].c_str()) );
	
		TCanvas c1_var_sig("c_var_epi0PID","Pur",30,10,800,900);
		//TEllipse *el1 = new TEllipse((175/ var2Dmax[FOMid][1])-0.1,(0.875/ var2Dmax[FOMid][0])-0.1,(175/ var2Dmax[FOMid][1])+0.1,(0.875/ var2Dmax[FOMid][0])+0.1);
		//TLine* minline = new TLine(0, y intercept, x intercept, 0);
		minline = new TLine(FOM_BG->GetXaxis()->GetXmin(), var2Dmin[FOMid][0] + FOM_BG->GetXaxis()->GetXmin() * var2Dmin[FOMid][1], 
																FOM_BG->GetXaxis()->GetXmax(), var2Dmin[FOMid][0] + FOM_BG->GetXaxis()->GetXmax() * var2Dmin[FOMid][1]);
		bestline = new TLine(FOM_BG->GetXaxis()->GetXmin(), fomMax_B + FOM_BG->GetXaxis()->GetXmin() * fomMax_A, 
																FOM_BG->GetXaxis()->GetXmax(), fomMax_B + FOM_BG->GetXaxis()->GetXmax() * fomMax_A);
		maxline = new TLine(FOM_BG->GetXaxis()->GetXmin(), var2Dmax[FOMid][0] + FOM_BG->GetXaxis()->GetXmin() * var2Dmax[FOMid][1], 
																FOM_BG->GetXaxis()->GetXmax(), var2Dmax[FOMid][0] + FOM_BG->GetXaxis()->GetXmax() * var2Dmax[FOMid][1]);
		bestline->SetLineColor(kRed);
		gStyle->SetPalette(kRainBow);
		gStyle->SetNumberContours(256);
		FOM_SIG->SetStats(0);
		FOM_SIG->GetXaxis()->SetTitle("P_{#pi^0}^{reco}");
		FOM_SIG->GetYaxis()->SetTitle("ln(L_{2Rother}/L_{ee})");
		FOM_SIG->SetTitle("ln(L_{2Rother}/L_{ee}) < B - A #times P_{#pi^0}^{reco} Signal");
		FOM_SIG->GetYaxis()->SetTitleOffset(1.75);
		FOM_SIG->Draw("colz");
	  FOM_cont.Draw("cont3 same");
	//	minline->Draw();
	//	maxline->Draw();
		bestline->SetLineWidth(3);
		bestline->Draw();
		arw1->DrawLine( 0, 100,FOM_BG->GetXaxis()->GetXmax() , 100);
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.12);
		c1_var_sig.Update();
		c1_var_sig.SaveAs(Form("%svar_sig_%s.png", odir.c_str(), FOMvar2D[FOMid].c_str()) );

		TCanvas c1_var_sel("c_var_epi0PID_sel","Pur",30,10,800,900);
		//TEllipse *el1 = new TEllipse((175/ var2Dmax[FOMid][1])-0.1,(0.875/ var2Dmax[FOMid][0])-0.1,(175/ var2Dmax[FOMid][1])+0.1,(0.875/ var2Dmax[FOMid][0])+0.1);
		//TLine* minline = new TLine(0, y intercept, x intercept, 0);
		minline = new TLine(FOM_BG->GetXaxis()->GetXmin(), var2Dmin[FOMid][0] + FOM_BG->GetXaxis()->GetXmin() * var2Dmin[FOMid][1], 
																FOM_BG->GetXaxis()->GetXmax(), var2Dmin[FOMid][0]+ FOM_BG->GetXaxis()->GetXmax() * var2Dmin[FOMid][1]);
		bestline = new TLine(FOM_BG->GetXaxis()->GetXmin(), fomMax_B + FOM_BG->GetXaxis()->GetXmin() * fomMax_A, 
																FOM_BG->GetXaxis()->GetXmax(), fomMax_B+ FOM_BG->GetXaxis()->GetXmax() * fomMax_A);
		maxline = new TLine(FOM_BG->GetXaxis()->GetXmin(), var2Dmax[FOMid][0] + FOM_BG->GetXaxis()->GetXmin() * var2Dmax[FOMid][1], 
																FOM_BG->GetXaxis()->GetXmax(), var2Dmax[FOMid][0]+ FOM_BG->GetXaxis()->GetXmax() * var2Dmax[FOMid][1]);
		bestline->SetLineColor(kRed);
		bestline->SetLineWidth(3);
		gStyle->SetPalette(kRainBow);
		gStyle->SetNumberContours(256);
		FOM_SEL->SetStats(0);
		FOM_SEL->GetXaxis()->SetTitle("P_{#pi^0}^{reco}");
		FOM_SEL->GetYaxis()->SetTitle("ln(L_{2Rother}/L_{ee})");
		FOM_SEL->SetTitle("ln(L_{2Rother}/L_{ee}) < B - A #times P_{#pi^0}^{reco} Signal");
		FOM_SEL->GetYaxis()->SetTitleOffset(1.75);
		FOM_SEL->Draw("colz");
	//  FOM_cont.Draw("cont3 same");
		//minline->Draw();
		//maxline->Draw();
		bestline->Draw();
		arw1->DrawLine( 0, 180,175 , 0);
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.12);
		c1_var_sel.Update();
		c1_var_sel.SaveAs(Form("%svar_sel_%s.png", odir.c_str(), FOMvar2D[FOMid].c_str()) );

}

	
	

 
  }
	ofile->Write();
  ofile->Close();
	



}





int main(int argc, char ** argv){
  //std::string idir = "/vols/t2k/ysers/dmartin/NCpi0/code/selection/figs/"
  //std::string ifile = "NCpi0_MC_histos_t2ksk19b.fqv4r0.fhc.all_merged.root"
  std::string idir = argv[1];
  std::string ifilename = argv[2];
   
  
  
  std::string ifile = Form("%s%s", idir.c_str(), ifilename.c_str());
  make1DFOMS(ifile, idir);
  //make2DFOMS(ifile, idir);
  
}







