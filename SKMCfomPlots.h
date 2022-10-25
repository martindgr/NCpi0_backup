

#ifndef SKMCfomPlots_h
#define SKMCfomPlots_h

//#include <TROOT.h>

#include <TH2.h>
#include <TH1.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TMath.h>

#include <TROOT.h>
#include <TFile.h>
#include <TPad.h>
#include <TArrow.h>
#include <cmath>


class SKMCfomPlots {
  public :  

    const static int Nvars1D = 3;
    const static int Nvars2D = 1;

    std::string FOMvars1D[Nvars1D] = {0};
    int FOMcuts1D[Nvars1D] = {0};
    int FOMcutDir1D[Nvars1D] = {0};
    std::string FOMvars2D[Nvars2D] = {0};
    
    const static int NSigVars = 2;
    const static int NBkgVars = 10;
    std::string SignalName[NSigVars] = {"NC1pi0", "NCCoh"}; 
    std::string BkgName[NBkgVars] = {"CCQE", "CC1pi", "CCCoh", "CCmultipi", "CCDis", "NC1pipm", "NCOther", "CC2p2h", "NC1gamma", "CCmisc"} ;
     
    void make1DFOMS(std::string ifilename, std::string odir);
    double GetFOM(double sig, double bkg);
};
#endif
