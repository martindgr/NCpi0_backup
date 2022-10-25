#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <THStack.h>
#include <TArrow.h>
#include <iostream>

void FormatHist(THStack* h, int linecolor, int linestyle){
  //  h->SetStats(0);
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

//  h->SetLineWidth(2);
//  h->SetLineColor(linecolor);
//  h->SetLineStyle(linestyle);
}

void DrawHist(THStack* histo, std::string outpath, std::string title){

auto c_hist = new TCanvas();
  histo->Draw("hist pfc");
	gPad->BuildLegend(0.7,0.5,0.9,0.9,"", "f");
	gPad->SetLeftMargin(0.12);
  histo->GetXaxis()->SetTitle(title.c_str());
	histo->SetTitle("");
	FormatHist(histo, 1, 2);
  c_hist->SaveAs(Form( "%s", outpath.c_str()));
}


void SKMCdataTree_NCbgplot(){

	std::string ifilename = "/home/dm3315/Documents/T2K-SK/NCpi0/NCpi0_output/mc/NCpi0_2ReePID_13av7p1_t2ksk19b.fqv4r0.fhc.all.root";
	
	std::string odir = "/home/dm3315/Documents/T2K-SK/NCpi0/figs/selection_plots/NCbackground/";

  TFile* ifile = new TFile(Form("%s", ifilename.c_str()));
  auto h1 = ifile->Get<TTree>("h1");	

	h1->Draw("fqpi0mass[0]>>m41(200,0,1000)","totweight*((mode==41)||(mode==-41))");
  h1->Draw("fqpi0mass[0]>>m42(200,0,1000)","totweight*((mode==42)||(mode==43)||(mode==-42)||(mode==-43))");
  h1->Draw("fqpi0mass[0]>>m44(200,0,1000)","totweight*((mode==44)||(mode==45)||(mode==-44)||(mode==-45))");
  h1->Draw("fqpi0mass[0]>>m46(200,0,1000)","totweight*((mode==46)||(mode==-46))");
  h1->Draw("fqpi0mass[0]>>m51(200,0,1000)","totweight*((mode==51)||(mode==-51))");
  h1->Draw("fqpi0mass[0]>>m52(200,0,1000)","totweight*((mode==52)||(mode==-52))");
  h1->Draw("fqpi0mass[0]>>m512(200,0,1000)","totweight*((mode==51)||(mode==-51)||(mode==52)||(mode==-52))");
  h1->Draw("fqpi0mass[0]>>m35(200,0,1000)","totweight*((mode==35)||(mode==-35))");
  
	TH1F *m41 = (TH1F*)gDirectory->Get("m41");
  TH1F *m42 = (TH1F*)gDirectory->Get("m42");
  TH1F *m44 = (TH1F*)gDirectory->Get("m44");
  TH1F *m46 = (TH1F*)gDirectory->Get("m46");
  TH1F *m51 = (TH1F*)gDirectory->Get("m51");
  TH1F *m52 = (TH1F*)gDirectory->Get("m52");
  TH1F *m512 = (TH1F*)gDirectory->Get("m512");
  TH1F *m35 = (TH1F*)gDirectory->Get("m35");
	
	m41->SetTitle("41:multiPi");
	m42->SetTitle("42, 43: Eta");
	m44->SetTitle("44, 45: #Lambda K");
	m46->SetTitle("46: DIS");
	m51->SetTitle("51: Elastic P->P");
	m52->SetTitle("52: Elastic N->N");
	m35->SetTitle("35: Pi0 diffractive");





	THStack *NCbkg = new THStack("NCbkgStack", "");
	NCbkg->Add(m42);
	NCbkg->Add(m44);
	NCbkg->Add(m46);
	NCbkg->Add(m51);
	NCbkg->Add(m52);
	NCbkg->Add(m35);
	NCbkg->Add(m41);
	
	double leg_x1 = 0.55;
	double leg_y1 = 0.65;
	double leg_x2 = 0.9;
	double leg_y2 = 0.9;
	
	std::cout << m51->Integral() + m52->Integral() << std::endl;

	auto c_1 = new TCanvas();
	NCbkg->Draw("hist pfc");
	gPad->BuildLegend(leg_x1,leg_y1,leg_x2,leg_y2,"", "f");
	//gPad->SetLeftMargin(0.12);
  NCbkg->GetXaxis()->SetTitle("Reconstructed Pi0 mass");
	NCbkg->SetTitle("NCOther background");
	FormatHist(NCbkg, 1, 2);
	c_1->SaveAs(Form("%sNCbkg.png", odir.c_str()));


	auto c_512 = new TCanvas();
	m512->Draw("hist pfc");
//	gPad->BuildLegend(leg_x1,leg_y1,leg_x2,leg_y2,"", "f");
	//gPad->SetLeftMargin(0.12);
  m512->GetXaxis()->SetTitle("Reconstructed Pi0 mass");
	m512->SetTitle("NCelastic background");
//	FormatHist(NCbkg, 1, 2);
	c_512->SaveAs(Form("%sNCelastic.png", odir.c_str()));


  h1->Draw("fqpi0mass[0]>>fc1(200,0,1000)","totweight*(((mode>40)||(mode<-40)||(mode>32&&mode<36)||(mode>-36&&mode<-32))&&(numnu==4))");//elastic
  h1->Draw("fqpi0mass[0]>>fc2(200,0,1000)","totweight*(((mode>40)||(mode<-40)||(mode>32&&mode<36)||(mode>-36&&mode<-32))&&(numnu==5&&ipnu[4]==111))");//1pi0
  h1->Draw("fqpi0mass[0]>>fc3(200,0,1000)","totweight*(((mode>40)||(mode<-40)||(mode>32&&mode<36)||(mode>-36&&mode<-32))&&(numnu==5&&(ipnu[4]==211||ipnu[4]==-211)))");//1pipm
  h1->Draw("fqpi0mass[0]>>fc4(200,0,1000)","totweight*(((mode>40)||(mode<-40)||(mode>32&&mode<36)||(mode>-36&&mode<-32))&&(numnu==5&&(ipnu[4]==221||ipnu[4]==-221)))");//eta
  h1->Draw("fqpi0mass[0]>>fc5(200,0,1000)","totweight*(((mode>40)||(mode<-40)||(mode>32&&mode<36)||(mode>-36&&mode<-32))&&(numnu>5&&ipnu[4]==111&&ipnu[5]==111))");//2pi0
  h1->Draw("fqpi0mass[0]>>fc6(200,0,1000)","totweight*(((mode>40)||(mode<-40)||(mode>32&&mode<36)||(mode>-36&&mode<-32))&&(numnu>5&&ipnu[4]==111&&ipnu[5]!=111))");//1pi0+other
  h1->Draw("fqpi0mass[0]>>fc7(200,0,1000)","totweight*(((mode>40)||(mode<-40)||(mode>32&&mode<36)||(mode>-36&&mode<-32))&&(numnu>5&&ipnu[4]!=111))");//other
	
	TH1F *fc1 = (TH1F*)gDirectory->Get("fc1");
	TH1F *fc2 = (TH1F*)gDirectory->Get("fc2");
	TH1F *fc3 = (TH1F*)gDirectory->Get("fc3");
	TH1F *fc4 = (TH1F*)gDirectory->Get("fc4");
	TH1F *fc5 = (TH1F*)gDirectory->Get("fc5");
	TH1F *fc6 = (TH1F*)gDirectory->Get("fc6");
	TH1F *fc7 = (TH1F*)gDirectory->Get("fc7");

	fc1->SetTitle("elastic");
	fc2->SetTitle("1pi0");
	fc3->SetTitle("1pipm");
	fc4->SetTitle("eta");
	fc5->SetTitle("2pi0");
	fc6->SetTitle("1pi0+other");
	fc7->SetTitle("other");





	THStack *NCbkgfc = new THStack("NCbkgStack", "");
	NCbkgfc->Add(fc1);
	NCbkgfc->Add(fc2);
	NCbkgfc->Add(fc3);
	NCbkgfc->Add(fc4);
	NCbkgfc->Add(fc5);
	NCbkgfc->Add(fc6);
	NCbkgfc->Add(fc7);
	

	

	auto c_2 = new TCanvas();
	NCbkgfc->Draw("hist pfc");
	gPad->BuildLegend(leg_x1,leg_y1,leg_x2,leg_y2,"", "f");
	//gPad->SetLeftMargin(0.12);
  NCbkgfc->GetXaxis()->SetTitle("Reconstructed Pi0 mass");
	NCbkgfc->SetTitle("NCOther background by final state");
	FormatHist(NCbkg, 1, 2);
	c_2->SaveAs(Form("%sNCbkgfs.png", odir.c_str()));



}
