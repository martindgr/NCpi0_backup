#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <THStack.h>
#include <TArrow.h>
#include <iostream>

float ChThresh(int pid) {
	float thresh = -1;
	if (pid == 11) thresh =  0.583; //electron
	if (pid == 14) thresh = 120.5; //muon
	if (pid == 111) thresh = 0; //pi0 or is generator photon??
	if (pid == 211) thresh = 159.2; //pipm
	if (pid == 221) thresh = 0; //eta
	if (pid == 2212) thresh = 1070; //P
	if (pid == 2112) thresh = 0; 

	return thresh;
}

float CherenkovThresh_mass(float mass) {
	//mass in MeV/c2
	float n = 1.33;
	float thresh = mass / sqrt(n*n - 1);
	return thresh;
}

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


void SKMCdataTree_epi0reject(){

	std::string ifilename = "/home/dm3315/Documents/T2K-SK/NCpi0/output/NCpi0_tuned_13av7p1_t2ksk19b.fqv4r0.fhc.all_cut6.root";
	
	std::string odir = "/home/dm3315/Documents/T2K-SK/NCpi0/figs/selection_plots/_1Repi0_reject/";

  TFile* ifile = new TFile(Form("%s", ifilename.c_str()));
  auto h1 = ifile->Get<TTree>("h1");	
	
	//pi0mass
	h1->Draw("fqpi0mass[0]>>m41(100,0,1000)","totweight*(((-1.0*fqpi0nll[0]+fq1rnll[0][1])<100)&&((mode==1)||(mode==-1)||(mode==-2)||(mode==2)))");//CCQE
  h1->Draw("fqpi0mass[0]>>m42(100,0,1000)","totweight*(((-1.0*fqpi0nll[0]+fq1rnll[0][1])<100)&&((mode==11)||(mode==12)||(mode==13)||(mode==-11)||(mode==-12)||(mode==-13)))"); //CC1pi
  h1->Draw("fqpi0mass[0]>>m44(100,0,1000)","totweight*(((-1.0*fqpi0nll[0]+fq1rnll[0][1])<100)&&(((mode<-15)&&(mode>-30))||((mode>15)&&(mode<30))))");//CCOther
  h1->Draw("fqpi0mass[0]>>m46(100,0,1000)","totweight*(((-1.0*fqpi0nll[0]+fq1rnll[0][1])<100)&&((mode==31)||(mode==32)||(mode==-31)||(mode==-32)))");//NC1pi0
  h1->Draw("fqpi0mass[0]>>m47(100,0,1000)","totweight*(((-1.0*fqpi0nll[0]+fq1rnll[0][1])<100)&&((mode==33)||(mode==34)||(mode==-33)||(mode==-34)))");//NC1pipm
  h1->Draw("fqpi0mass[0]>>m51(100,0,1000)","totweight*(((-1.0*fqpi0nll[0]+fq1rnll[0][1])<100)&&((mode==45)||(mode==-45)))");//NCmpi
  h1->Draw("fqpi0mass[0]>>m52(100,0,1000)","totweight*(((-1.0*fqpi0nll[0]+fq1rnll[0][1])<100)&&(((mode>34)&&(mode<45))||(mode>45)||(mode<-34)&&(mode>-45)||(mode<-45)))");//NCother
  
	TH1F *m41 = (TH1F*)gDirectory->Get("m41");
  TH1F *m42 = (TH1F*)gDirectory->Get("m42");
  TH1F *m44 = (TH1F*)gDirectory->Get("m44");
  TH1F *m46 = (TH1F*)gDirectory->Get("m46");
  TH1F *m51 = (TH1F*)gDirectory->Get("m51");
  TH1F *m52 = (TH1F*)gDirectory->Get("m52");
  TH1F *m47 = (TH1F*)gDirectory->Get("m47");
	
	m41->SetTitle("CCQE");
	m42->SetTitle("CC1pi");
	m44->SetTitle("CCOther");
	m46->SetTitle("NC1pi0");
	m51->SetTitle("NCmpi");
	m52->SetTitle("NCOther");
	m47->SetTitle("NC1pipm");




	THStack *NCbkg = new THStack("NCbkgStack", "");
	NCbkg->Add(m41);
	NCbkg->Add(m42);
	NCbkg->Add(m44);
	NCbkg->Add(m46);
	NCbkg->Add(m51);
	NCbkg->Add(m52);
	NCbkg->Add(m47);
	
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
	NCbkg->SetTitle("Rejected by e/pi0 cut");
	FormatHist(NCbkg, 1, 2);
	c_1->SaveAs(Form("%sNCbkg.png", odir.c_str()));


	std::cout << "Total rejected: " << m41->Integral()+m42->Integral()+m44->Integral()+ m46->Integral()+m51->Integral()+m52->Integral()+m47->Integral() << std::endl;
	std::cout << "CC rejected: " << m41->Integral()+m42->Integral()+m44->Integral() << std::endl;
	



	h1->Draw("fqtotq[1]>>cc1(100,0,1000)","totweight*(((-1.0*fqpi0nll[0]+fq1rnll[0][1])<100)&&((mode==1)||(mode==-1)||(mode==-2)||(mode==2)))");//CCQE
  h1->Draw("fqtotq[1]>>cc2(100,0,1000)","totweight*(((-1.0*fqpi0nll[0]+fq1rnll[0][1])<100)&&((mode==11)||(mode==12)||(mode==13)||(mode==-11)||(mode==-12)||(mode==-13)))"); //CC1pi
  h1->Draw("fqtotq[1]>>cc3(100,0,1000)","totweight*(((-1.0*fqpi0nll[0]+fq1rnll[0][1])<100)&&(((mode<-15)&&(mode>-30))||((mode>15)&&(mode<30))))");//CCOther


	TH1F *cc1 = (TH1F*)gDirectory->Get("cc1");
  TH1F *cc2 = (TH1F*)gDirectory->Get("cc2");
  TH1F *cc3 = (TH1F*)gDirectory->Get("cc3");
	
	cc1->SetTitle("CCQE");
	cc2->SetTitle("CC1pi");
	cc3->SetTitle("CCOther");

	THStack *CCrj = new THStack("CCrjStack", "");
	CCrj->Add(cc1);
	CCrj->Add(cc2);
	CCrj->Add(cc3);

	auto c_2 = new TCanvas();
	CCrj->Draw("hist pfc");
	gPad->BuildLegend(leg_x1,leg_y1,leg_x2,leg_y2,"", "f");
	//gPad->SetLeftMargin(0.12);
  CCrj->GetXaxis()->SetTitle("fqtotq[0]");
	CCrj->SetTitle("Total charge for CC events rejected by e/pi0 cut");
	FormatHist(NCbkg, 1, 2);
	c_2->SaveAs(Form("%sCCrj.png", odir.c_str()));




	h1->Draw("fqpi0mom1[0]>>cc1r1(100,0,1000)","totweight*(((-1.0*fqpi0nll[0]+fq1rnll[0][1])<100)&&((mode==1)||(mode==-1)||(mode==-2)||(mode==2)))");//CCQE
  h1->Draw("fqpi0mom1[0]>>cc2r1(100,0,1000)","totweight*(((-1.0*fqpi0nll[0]+fq1rnll[0][1])<100)&&((mode==11)||(mode==12)||(mode==13)||(mode==-11)||(mode==-12)||(mode==-13)))"); //CC1pi
  h1->Draw("fqpi0mom1[0]>>cc3r1(100,0,1000)","totweight*(((-1.0*fqpi0nll[0]+fq1rnll[0][1])<100)&&(((mode<-15)&&(mode>-30))||((mode>15)&&(mode<30))))");//CCOther


	TH1F *cc1r1 = (TH1F*)gDirectory->Get("cc1r1");
  TH1F *cc2r1 = (TH1F*)gDirectory->Get("cc2r1");
  TH1F *cc3r1 = (TH1F*)gDirectory->Get("cc3r1");
	
	cc1r1->SetTitle("CCQE");
	cc2r1->SetTitle("CC1pi");
	cc3r1->SetTitle("CCOther");

	THStack *CCrjr1 = new THStack("CCrjStack", "");
	CCrjr1->Add(cc1r1);
	CCrjr1->Add(cc2r1);
	CCrjr1->Add(cc3r1);

	auto c_3 = new TCanvas();
	CCrjr1->Draw("hist pfc");
	gPad->BuildLegend(leg_x1,leg_y1,leg_x2,leg_y2,"", "f");
	//gPad->SetLeftMargin(0.12);
  CCrjr1->GetXaxis()->SetTitle("fqpi0mom1[0]");
	CCrjr1->SetTitle("1st ring fit momentum for CC events rejected by e/pi0 cut");
	FormatHist(NCbkg, 1, 2);
	c_3->SaveAs(Form("%sCCrjr1.png", odir.c_str()));


	h1->Draw("fqpi0mom2[0]>>cc1r2(100,0,1000)","totweight*(((-1.0*fqpi0nll[0]+fq1rnll[0][1])<100)&&((mode==1)||(mode==-1)||(mode==-2)||(mode==2)))");//CCQE
  h1->Draw("fqpi0mom2[0]>>cc2r2(100,0,1000)","totweight*(((-1.0*fqpi0nll[0]+fq1rnll[0][1])<100)&&((mode==11)||(mode==12)||(mode==13)||(mode==-11)||(mode==-12)||(mode==-13)))"); //CC1pi
  h1->Draw("fqpi0mom2[0]>>cc3r2(100,0,1000)","totweight*(((-1.0*fqpi0nll[0]+fq1rnll[0][1])<100)&&(((mode<-15)&&(mode>-30))||((mode>15)&&(mode<30))))");//CCOther


	TH1F *cc1r2 = (TH1F*)gDirectory->Get("cc1r2");
  TH1F *cc2r2 = (TH1F*)gDirectory->Get("cc2r2");
  TH1F *cc3r2 = (TH1F*)gDirectory->Get("cc3r2");
	
	cc1r2->SetTitle("CCQE");
	cc2r2->SetTitle("CC1pi");
	cc3r2->SetTitle("CCOther");

	THStack *CCrjr2 = new THStack("CCrjStack", "");
	CCrjr2->Add(cc1r2);
	CCrjr2->Add(cc2r2);
	CCrjr2->Add(cc3r2);

	auto c_4 = new TCanvas();
	CCrjr2->Draw("hist pfc");
	gPad->BuildLegend(leg_x1,leg_y1,leg_x2,leg_y2,"", "f");
	//gPad->SetLeftMargin(0.12);
  CCrjr2->GetXaxis()->SetTitle("fqpi0mom1[0]");
	CCrjr2->SetTitle("1st ring fit momentum for CC events rejected by e/pi0 cut");
	FormatHist(NCbkg, 1, 2);
	c_4->SaveAs(Form("%sCCrjr2.png", odir.c_str()));



///Difference in rings
	h1->Draw("(fqpi0mom1[0]-fqpi0mom2[0])>>cc1r1r2(100,0,1000)","totweight*(((-1.0*fqpi0nll[0]+fq1rnll[0][1])<100)&&((mode==1)||(mode==-1)||(mode==-2)||(mode==2)))");//CCQE
  h1->Draw("(fqpi0mom1[0]-fqpi0mom2[0])>>cc2r1r2(100,0,1000)","totweight*(((-1.0*fqpi0nll[0]+fq1rnll[0][1])<100)&&((mode==11)||(mode==12)||(mode==13)||(mode==-11)||(mode==-12)||(mode==-13)))"); //CC1pi
  h1->Draw("(fqpi0mom1[0]-fqpi0mom2[0])>>cc3r1r2(100,0,1000)","totweight*(((-1.0*fqpi0nll[0]+fq1rnll[0][1])<100)&&(((mode<-15)&&(mode>-30))||((mode>15)&&(mode<30))))");//CCOther


	TH1F *cc1r1r2 = (TH1F*)gDirectory->Get("cc1r1r2");
  TH1F *cc2r1r2 = (TH1F*)gDirectory->Get("cc2r1r2");
  TH1F *cc3r1r2 = (TH1F*)gDirectory->Get("cc3r1r2");
	
	cc1r1r2->SetTitle("CCQE");
	cc2r1r2->SetTitle("CC1pi");
	cc3r1r2->SetTitle("CCOther");

	THStack *CCrjr1r2 = new THStack("CCrjStack", "");
	CCrjr1r2->Add(cc1r1r2);
	CCrjr1r2->Add(cc2r1r2);
	CCrjr1r2->Add(cc3r1r2);

	auto c_5 = new TCanvas();
	CCrjr1r2->Draw("hist pfc");
	gPad->BuildLegend(leg_x1,leg_y1,leg_x2,leg_y2,"", "f");
	//gPad->SetLeftMargin(0.12);
  CCrjr1r2->GetXaxis()->SetTitle("fqpi0mom1[0]");
	CCrjr1r2->SetTitle("Difference in ring momeentum for CC events rejected by e/pi0 cut");
	FormatHist(NCbkg, 1, 2);
	c_5->SaveAs(Form("%sCCrjr1r2.png", odir.c_str()));


///how far above threshold
/*	h1->Draw("(fqpi0mom1[0]-fqpi0mom2[0])>>cc1r1r2(100,0,1000)","totweight*(((-1.0*fqpi0nll[0]+fq1rnll[0][1])<100)&&((mode==1)||(mode==-1)||(mode==-2)||(mode==2)))");//CCQE
  h1->Draw("(fqpi0mom1[0]-fqpi0mom2[0])>>cc2r1r2(100,0,1000)","totweight*(((-1.0*fqpi0nll[0]+fq1rnll[0][1])<100)&&((mode==11)||(mode==12)||(mode==13)||(mode==-11)||(mode==-12)||(mode==-13)))"); //CC1pi
  h1->Draw("(fqpi0mom1[0]-fqpi0mom2[0])>>cc3r1r2(100,0,1000)","totweight*(((-1.0*fqpi0nll[0]+fq1rnll[0][1])<100)&&(((mode<-15)&&(mode>-30))||((mode>15)&&(mode<30))))");//CCOther


	TH1F *cc1r1r2 = (TH1F*)gDirectory->Get("cc1r1r2");
  TH1F *cc2r1r2 = (TH1F*)gDirectory->Get("cc2r1r2");
  TH1F *cc3r1r2 = (TH1F*)gDirectory->Get("cc3r1r2");
	
	cc1r1r2->SetTitle("CCQE");
	cc2r1r2->SetTitle("CC1pi");
	cc3r1r2->SetTitle("CCOther");

	THStack *CCrjr1r2 = new THStack("CCrjStack", "");
	CCrjr1r2->Add(cc1r1r2);
	CCrjr1r2->Add(cc2r1r2);
	CCrjr1r2->Add(cc3r1r2);

	auto c_5 = new TCanvas();
	CCrjr1r2->Draw("hist pfc");
	gPad->BuildLegend(leg_x1,leg_y1,leg_x2,leg_y2,"", "f");
	//gPad->SetLeftMargin(0.12);
  CCrjr1r2->GetXaxis()->SetTitle("fqpi0mom1[0]");
	CCrjr1r2->SetTitle("Difference in ring momeentum for CC events rejected by e/pi0 cut");
	FormatHist(NCbkg, 1, 2);
	c_5->SaveAs(Form("%sCCrjr1r2.png", odir.c_str()));
*/
	//Ring momentum2d
	
	h1->Draw("fqpi0mom1[0]:fqpi0mom2[0]>>D2cc1r1r2(100,0,1000, 100, 0, 1000)","totweight*(((-1.0*fqpi0nll[0]+fq1rnll[0][1])<100)&&((mode==1)||(mode==-1)||(mode==-2)||(mode==2)))");//CCQE
  h1->Draw("fqpi0mom1[0]:fqpi0mom2[0]>>D2cc2r1r2(100,0,1000, 100, 0, 1000)","totweight*(((-1.0*fqpi0nll[0]+fq1rnll[0][1])<100)&&((mode==11)||(mode==12)||(mode==13)||(mode==-11)||(mode==-12)||(mode==-13)))"); //CC1pi
  h1->Draw("fqpi0mom1[0]:fqpi0mom2[0]>>D2cc3r1r2(100,0,1000, 100, 0, 1000)","totweight*(((-1.0*fqpi0nll[0]+fq1rnll[0][1])<100)&&(((mode<-15)&&(mode>-30))||((mode>15)&&(mode<30))))");//CCOther


	TH2F *D2cc1r1r2 = (TH2F*)gDirectory->Get("D2cc1r1r2");
  TH2F *D2cc2r1r2 = (TH2F*)gDirectory->Get("D2cc2r1r2");
  TH2F *D2cc3r1r2 = (TH2F*)gDirectory->Get("D2cc3r1r2");
	
//	D2cc1r1r2->SetTitle("CCQE");
//	D2cc2r1r2->SetTitle("CC1pi");
//	D2cc3r1r2->SetTitle("CCOther");

	TH2F *D2CCrjr1r2 = new TH2F();//"CCrj2D", "", 100, 0, 1000, 100, 0, 1000
	D2CCrjr1r2->Add(D2cc1r1r2);
	D2CCrjr1r2->Add(D2cc2r1r2);
	D2CCrjr1r2->Add(D2cc3r1r2);

	auto c_6 = new TCanvas();
	D2CCrjr1r2->Draw("colz");
	//gPad->BuildLegend(leg_x1,leg_y1,leg_x2,leg_y2,"", "f");
	//gPad->SetLeftMargin(0.12);
  D2CCrjr1r2->GetXaxis()->SetTitle("fqpi0mom1[0]");
  D2CCrjr1r2->GetYaxis()->SetTitle("fqpi0mom2[0]");
	D2CCrjr1r2->SetTitle("Ring momenta for CC events rejected by e/pi0 cut");
	TLine myline=TLine(0,0,1000,1000);
	myline.Draw("same");
	//FormatHist(NCbkg, 1, 2);
	c_6->SaveAs(Form("%sD2CCrjr1r2.png", odir.c_str()));


	//difference vs Ring 1 momentum2d
	
	h1->Draw("fqpi0mom1[0]:(fqpi0mom1[0]-fqpi0mom2[0])>>D2cc1r1r12(100,0,1000, 100, 0, 1000)","totweight*(((-1.0*fqpi0nll[0]+fq1rnll[0][1])<100)&&((mode==1)||(mode==-1)||(mode==-2)||(mode==2)))");//CCQE
  h1->Draw("fqpi0mom1[0]:(fqpi0mom1[0]-fqpi0mom2[0])>>D2cc2r1r12(100,0,1000, 100, 0, 1000)","totweight*(((-1.0*fqpi0nll[0]+fq1rnll[0][1])<100)&&((mode==11)||(mode==12)||(mode==13)||(mode==-11)||(mode==-12)||(mode==-13)))"); //CC1pi
  h1->Draw("fqpi0mom1[0]:(fqpi0mom1[0]-fqpi0mom2[0])>>D2cc3r1r12(100,0,1000, 100, 0, 1000)","totweight*(((-1.0*fqpi0nll[0]+fq1rnll[0][1])<100)&&(((mode<-15)&&(mode>-30))||((mode>15)&&(mode<30))))");//CCOther


	TH2F *D2cc1r1r12 = (TH2F*)gDirectory->Get("D2cc1r1r12");
  TH2F *D2cc2r1r12 = (TH2F*)gDirectory->Get("D2cc2r1r12");
  TH2F *D2cc3r1r12 = (TH2F*)gDirectory->Get("D2cc3r1r12");
	
//	D2cc1r1r2->SetTitle("CCQE");
//	D2cc2r1r2->SetTitle("CC1pi");
//	D2cc3r1r2->SetTitle("CCOther");

	TH2F *D2CCrjr1r12 = new TH2F();//"CCrj2D", "", 100, 0, 1000, 100, 0, 1000
	D2CCrjr1r12->Add(D2cc1r1r12);
	D2CCrjr1r12->Add(D2cc2r1r12);
	D2CCrjr1r12->Add(D2cc3r1r12);

	auto c_7 = new TCanvas();
	D2CCrjr1r12->Draw("colz");
	//gPad->BuildLegend(leg_x1,leg_y1,leg_x2,leg_y2,"", "f");
	//gPad->SetLeftMargin(0.12);
  D2CCrjr1r12->GetXaxis()->SetTitle("fqpi0mom1[0]-fqpi0mom2[0]");
  D2CCrjr1r12->GetYaxis()->SetTitle("fqpi0mom1[0]");
	D2CCrjr1r12->SetTitle("Momentum difference vs Ring 1 momenta for CC events rejected by e/pi0 cut");
	//myline=TLine(0,0,1000,1000)
	myline.Draw("same");
	//FormatHist(NCbkg, 1, 2);
	c_7->SaveAs(Form("%sD2CCrjr1r12.png", odir.c_str()));




	/// Above threshold
	
	//Do by output particle for anything that is outgoing
	//split by pid
	
	int outpid = 11;
	int intnum = 2;
	//electron
	float temp = ChThresh(outpid);
	std::cout << temp << std::endl;
	//h1->Draw("pnu[2]>>CherThresh311(100,0,100)", "totweight*(((-1.0*fqpi0nll[0]+fq1rnll[0][1])<100))&&(pnu[2]>0.583)&&((ipnu[2]==11)||(ipnu[2]==-11))");
	h1->Draw(Form("pnu[%d]-%f>>CherThresh311(50,0,15)", intnum, temp), Form("totweight*(((-1.0*fqpi0nll[0]+fq1rnll[0][1])<15)&&(pnu[%d]>0)&&((ipnu[%d]==%d)||(ipnu[%d]==-%d)))",intnum,  intnum, outpid, intnum, outpid));
	//muon
	outpid = 12;
	h1->Draw(Form("pnu[%d]-%f>>CherThresh312(50, 0, 15)", intnum, ChThresh(outpid)),Form("totweight*(((-1.0*fqpi0nll[0]+fq1rnll[0][1])<15)&&(pnu[%d]>0)&&((ipnu[%d]==%d)||(ipnu[%d]==-%d)))", intnum,  intnum, outpid, intnum, outpid));
	//proton
	outpid = 111;
	h1->Draw(Form("pnu[%d]-%f>>CherThresh3111(50, 0, 15)", intnum, ChThresh(outpid)),Form("totweight*(((-1.0*fqpi0nll[0]+fq1rnll[0][1])<15)&&(pnu[%d]>0)&&((ipnu[%d]==%d)||(ipnu[%d]==-%d)))", intnum,  intnum, outpid, intnum, outpid));
	outpid = 211; //pipm
	h1->Draw(Form("pnu[%d]-%f>>CherThresh3211(50, 0, 15)", intnum, ChThresh(outpid)),Form("totweight*(((-1.0*fqpi0nll[0]+fq1rnll[0][1])<15)&&(pnu[%d]>0)&&((ipnu[%d]==%d)||(ipnu[%d]==-%d)))", intnum,  intnum, outpid, intnum, outpid));
	outpid = 2212; //proton
	h1->Draw(Form("pnu[%d]-%f>>CherThresh32212(50, 0, 15)", intnum, ChThresh(outpid)),Form("totweight*(((-1.0*fqpi0nll[0]+fq1rnll[0][1])<15)&&(pnu[%d]>0)&&((ipnu[%d]==%d)||(ipnu[%d]==-%d)))", intnum,  intnum, outpid, intnum, outpid));

  intnum = 3; //ougoing target
	outpid = 11;//electron
	h1->Draw(Form("pnu[%d]-%f>>CherThresh411(50, 0, 15)", intnum, ChThresh(outpid)),Form("totweight*(((-1.0*fqpi0nll[0]+fq1rnll[0][1])<15)&&(pnu[%d]>0)&&((ipnu[%d]==%d)||(ipnu[%d]==-%d)))", intnum,  intnum, outpid, intnum, outpid));
	//muon
	outpid = 12;
	h1->Draw(Form("pnu[%d]-%f>>CherThresh412(50, 0, 15)", intnum, ChThresh(outpid)),Form("totweight*(((-1.0*fqpi0nll[0]+fq1rnll[0][1])<15)&&(pnu[%d]>0)&&((ipnu[%d]==%d)||(ipnu[%d]==-%d)))", intnum,  intnum, outpid, intnum, outpid));
	//proton
	outpid = 111;
	h1->Draw(Form("pnu[%d]-%f>>CherThresh4111(50, 0, 15)", intnum, ChThresh(outpid)),Form("totweight*(((-1.0*fqpi0nll[0]+fq1rnll[0][1])<15)&&(pnu[%d]>0)&&((ipnu[%d]==%d)||(ipnu[%d]==-%d)))", intnum,  intnum, outpid, intnum, outpid));
	outpid = 211; //pipm
	h1->Draw(Form("pnu[%d]-%f>>CherThresh4211(50, 0, 15)", intnum, ChThresh(outpid)),Form("totweight*(((-1.0*fqpi0nll[0]+fq1rnll[0][1])<15)&&(pnu[%d]>0)&&((ipnu[%d]==%d)||(ipnu[%d]==-%d)))", intnum,  intnum, outpid, intnum, outpid));
	outpid = 2212; //proton
	h1->Draw(Form("pnu[%d]-%f>>CherThresh42212(50, 0, 15)", intnum, ChThresh(outpid)),Form("totweight*(((-1.0*fqpi0nll[0]+fq1rnll[0][1])<15)&&(pnu[%d]>0)&&((ipnu[%d]==%d)||(ipnu[%d]==-%d)))", intnum,  intnum, outpid, intnum, outpid));


  intnum = 4; //other
	outpid = 11;//electron
	h1->Draw(Form("pnu[%d]-%f>>CherThresh511(50, 0, 15)", intnum, ChThresh(outpid)),Form("totweight*(((-1.0*fqpi0nll[0]+fq1rnll[0][1])<15)&&(pnu[%d]>0)&&((ipnu[%d]==%d)||(ipnu[%d]==-%d)))", intnum,  intnum, outpid, intnum, outpid));
	//muon
	outpid = 12;
	h1->Draw(Form("pnu[%d]-%f>>CherThresh512(50, 0, 15)", intnum, ChThresh(outpid)),Form("totweight*(((-1.0*fqpi0nll[0]+fq1rnll[0][1])<15)&&(pnu[%d]>0)&&((ipnu[%d]==%d)||(ipnu[%d]==-%d)))", intnum,  intnum, outpid, intnum, outpid));
	//proton
	outpid = 111;
	h1->Draw(Form("pnu[%d]-%f>>CherThresh5111(50, 0, 15)", intnum, ChThresh(outpid)),Form("totweight*(((-1.0*fqpi0nll[0]+fq1rnll[0][1])<15)&&(pnu[%d]>0)&&((ipnu[%d]==%d)||(ipnu[%d]==-%d)))", intnum,  intnum, outpid, intnum, outpid));
	outpid = 211; //pipm
	h1->Draw(Form("pnu[%d]-%f>>CherThresh5211(50, 0, 15)", intnum, ChThresh(outpid)),Form("totweight*(((-1.0*fqpi0nll[0]+fq1rnll[0][1])<15)&&(pnu[%d]>0)&&((ipnu[%d]==%d)||(ipnu[%d]==-%d)))", intnum,  intnum, outpid, intnum, outpid));
	outpid = 2212; //proton
	h1->Draw(Form("pnu[%d]-%f>>CherThresh52212(50, 0, 15)", intnum, ChThresh(outpid)),Form("totweight*(((-1.0*fqpi0nll[0]+fq1rnll[0][1])<15)&&(pnu[%d]>0)&&((ipnu[%d]==%d)||(ipnu[%d]==-%d)))", intnum,  intnum, outpid, intnum, outpid));

	std::cout << "here" << std::endl;
	TH1F *CherThresh311 = (TH1F*)gDirectory->Get("CherThresh311");
	TH1F *CherThresh312 = (TH1F*)gDirectory->Get("CherThresh312");
	TH1F *CherThresh3111 = (TH1F*)gDirectory->Get("CherThresh3111");
	TH1F *CherThresh3211 = (TH1F*)gDirectory->Get("CherThresh3211");
	TH1F *CherThresh32212 = (TH1F*)gDirectory->Get("CherThresh32212");
	
	TH1F *CherThresh511 = (TH1F*)gDirectory->Get("CherThresh511");
	TH1F *CherThresh512 = (TH1F*)gDirectory->Get("CherThresh512");
	TH1F *CherThresh5111 = (TH1F*)gDirectory->Get("CherThresh5111");
	TH1F *CherThresh5211 = (TH1F*)gDirectory->Get("CherThresh5211");
	TH1F *CherThresh52212 = (TH1F*)gDirectory->Get("CherThresh52212");
	
	TH1F *CherThresh411 = (TH1F*)gDirectory->Get("CherThresh411");
	TH1F *CherThresh412 = (TH1F*)gDirectory->Get("CherThresh412");
	TH1F *CherThresh4111 = (TH1F*)gDirectory->Get("CherThresh4111");
	TH1F *CherThresh4211 = (TH1F*)gDirectory->Get("CherThresh4211");
	TH1F *CherThresh42212 = (TH1F*)gDirectory->Get("CherThresh42212");

	CherThresh311->Add(CherThresh411);
	CherThresh311->Add(CherThresh511);
	
	CherThresh312->Add(CherThresh412);
	CherThresh312->Add(CherThresh512);
	
	CherThresh3111->Add(CherThresh4111);
	CherThresh3111->Add(CherThresh5111);
	
	CherThresh3211->Add(CherThresh4211);
	CherThresh3211->Add(CherThresh5211);
	
	CherThresh32212->Add(CherThresh42212);
	CherThresh32212->Add(CherThresh52212);

	CherThresh311->SetTitle("Electron");
	CherThresh312->SetTitle("Muon");
	CherThresh3111->SetTitle("pi0");
	CherThresh3211->SetTitle("pipm");
	CherThresh32212->SetTitle("proton");

	THStack *ChThreshStack = new THStack("ChThresh", "");
	ChThreshStack->Add(CherThresh311);
	ChThreshStack->Add(CherThresh312);
	ChThreshStack->Add(CherThresh3111);
	ChThreshStack->Add(CherThresh3211);
	ChThreshStack->Add(CherThresh32212);

	auto c_thresh = new TCanvas();
	ChThreshStack->Draw("hist pfc");
	gPad->BuildLegend(leg_x1,leg_y1,leg_x2,leg_y2,"", "f");
	//gPad->SetLeftMargin(0.12);
  ChThreshStack->GetXaxis()->SetTitle("pnu[numnu]-ChThresh[pid]");
	ChThreshStack->SetTitle("Rejected event momentum of particles above cherenkov threshold");
	FormatHist(ChThreshStack, 1, 2);
	c_thresh->SaveAs(Form("%sChThresh.png", odir.c_str()));



/*auto c_512 = new TCanvas();
	m512->Draw("hist pfc");
//	gPad->BuildLegend(leg_x1,leg_y1,leg_x2,leg_y2,"", "f");
	//gPad->SetLeftMargin(0.12);
  m512->GetXaxis()->SetTitle("Reconstructed Pi0 mass");
	m512->SetTitle("NCelastic background");
//	FormatHist(NCbkg, 1, 2);
	c_512->SaveAs(Form("%sNCelastic.png", odir.c_str()));
*/
//Final state
/*  h1->Draw("fqpi0mass[0]>>fc1(200,0,1000)","totweight*(-1.0*fqpi0nll[0]+fq1rnll[0][1])<100)&&(numnu==4))");//elastic
  h1->Draw("fqpi0mass[0]>>fc2(200,0,1000)","totweight*(-1.0*fqpi0nll[0]+fq1rnll[0][1])<100)&&(numnu==5&&ipnu[4]==111))");//1pi0
  h1->Draw("fqpi0mass[0]>>fc3(200,0,1000)","totweight*(-1.0*fqpi0nll[0]+fq1rnll[0][1])<100)&&(numnu==5&&(ipnu[4]==211||ipnu[4]==-211)))");//1pipm
  h1->Draw("fqpi0mass[0]>>fc4(200,0,1000)","totweight*(-1.0*fqpi0nll[0]+fq1rnll[0][1])<100)&&(numnu==5&&(ipnu[4]==221||ipnu[4]==-221)))");//eta
  h1->Draw("fqpi0mass[0]>>fc5(200,0,1000)","totweight*(-1.0*fqpi0nll[0]+fq1rnll[0][1])<100)&&(numnu>5&&ipnu[4]==111&&ipnu[5]==111))");//2pi0
  h1->Draw("fqpi0mass[0]>>fc6(200,0,1000)","totweight*(-1.0*fqpi0nll[0]+fq1rnll[0][1])<100)&&(numnu>5&&ipnu[4]==111&&ipnu[5]!=111))");//1pi0+other
  h1->Draw("fqpi0mass[0]>>fc7(200,0,1000)","totweight*(-1.0*fqpi0nll[0]+fq1rnll[0][1])<100)&&(numnu>5&&ipnu[4]!=111))");//other
	
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

*/

}
