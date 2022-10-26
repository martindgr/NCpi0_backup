////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Jun 14 15:33:16 2021 by ROOT version 6.22/02
// from TTree h1/DST
// found on file: t2ksk19b.fqv4r0.fhc.nue_x_nue.0319.009.root
//////////////////////////////////////////////////////////
#pragma once

#ifndef SKMCdataTree_h
#define SKMCdataTree_h

//#include "SKMCdataTree_NCpi0.h"
//#include "SKMCdataTree_1RePi0.h"

//#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

#include <TH2.h>
#include <TH1.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TMath.h>

#include <BargerPropagator.h>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TPad.h>
#include <TArrow.h>


//#include "SetT2KStyle.H"
// Header file for the classes stored in the TTree if any.

class SKMCdataTree {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           nring;
   UInt_t          nrun;
   Int_t           nev;
   Int_t           nsub;
   UInt_t          cate;
   Float_t         potot;
   UInt_t          nhit;
   Float_t         pomax;
   Float_t         potota;
   UInt_t          nhita;
   UInt_t          nhitac;
   Float_t         pomaxa;
   Float_t         wall;
   Float_t         evis;
   Float_t         rtsum;
   Float_t         rtmax;
   Float_t         wlen;
   UInt_t          ip[10];   //[nring]
   Float_t         pos[3];
   Float_t         dir[10][3];   //[nring]
   Float_t         dirtot[3];
   Float_t         ang[10];   //[nring]
   Float_t         rtot[10];   //[nring]
   Float_t         amom[10];   //[nring]
   Float_t         rtote[10];   //[nring]
   Float_t         amome[10];   //[nring]
   Float_t         rtotm[10];   //[nring]
   Float_t         amomm[10];   //[nring]
   UInt_t          nsube;
   UInt_t          ndcy;
   UInt_t          ngate;
   UInt_t          nbye;
   Float_t         probms[10][6];   //[nring]
   Float_t         prmslg[10][6];   //[nring]
   Int_t           date[3];
   Int_t           time[4];
   Float_t         elpsday;
   Int_t           numpo[10];   //[nring]
   Float_t         apos[3];
   Float_t         adir[3];
   Float_t         aang;
   Float_t         agood;
   Float_t         wgain;
   Int_t           nbad;
   Int_t           nbada;
   Float_t         msdir[10][3][6];   //[nring]
   Float_t         amomp[10];
   Float_t         ange[10];
   Float_t         angm[10];
   Float_t         angp[10];
   Int_t           ntot[10];
   Float_t         probth[10][6];
   Float_t         probpt[10][6];
   Float_t         pi0like[2];
   Float_t         pi0_e[2][2];
   Float_t         pi0_dir[2][2][3];
   Float_t         pi0mass[2];
   Float_t         evisold;
   Float_t         evisoldxe;
   Float_t         evisnew;
   Int_t           nmue;
   UInt_t          etype[12];   //[nmue]
   Float_t         etime[12];   //[nmue]
   Float_t         epos[12][3];   //[nmue]
   Float_t         edir[12][3];   //[nmue]
   Float_t         egood[12];   //[nmue]
   Float_t         ehit[12];   //[nmue]
   Float_t         mueprob[2];
   Int_t           nmue_sel;
   Int_t           Rnring;
   Float_t         Rdir[30][3];   //[Rnring]
   Float_t         Rang[30];   //[Rnring]
   UInt_t          Riring;
   Float_t         Rtwout[30];   //[Rnring]
   Float_t         Rtwith[30];   //[Rnring]
   Float_t         Alwout;
   Float_t         Alwith;
   Float_t         Qsmi;
   Float_t         Qsmo;
   Float_t         Qexi;
   Float_t         Qexo;
   Float_t         Pe5d;
   Float_t         En5d;
   Float_t         Eh5d;
   Float_t         Pe5do;
   Float_t         En5do;
   Float_t         Eh5do;
   Float_t         Rtadd;
   Float_t         Pdgeta;
   Float_t         Pd5d;
   Float_t         Pdthre;
   Float_t         Pd5do;
   Float_t         Delpd;
   Float_t         Ropena[30];   //[Rnring]
   Int_t           Maxth;
   Float_t         Pkang;
   Float_t         Qrfct;
   Float_t         Pdfct;
   Float_t         Pkfct;
   Float_t         Agfct;
   Float_t         Dlfct;
   Int_t           Iflag;
   Float_t         Pmfct;
   Float_t         Imfct;
   Float_t         Rilike;
   Int_t           ri_ver;
   Float_t         ri_pid;
   Int_t           ri_nring;
   Float_t         ri_flag[10];   //[ri_nring]
   Float_t         ri_dlfct[10];   //[ri_nring]
   Float_t         ri_pdfct[10];   //[ri_nring]
   Float_t         ri_pkfct[10];   //[ri_nring]
   Float_t         ri_vafct[10];   //[ri_nring]
   Float_t         ri_total[10];   //[ri_nring]
   Float_t         ri_dir[10][3];   //[ri_nring]
   Float_t         ri_imfct[10];   //[ri_nring]
   Float_t         ri_pmfct[10];   //[ri_nring]
   Int_t           npar;
   Float_t         wallv;
   UInt_t          ipv[50];   //[npar]
   Float_t         posv[3];
   Float_t         dirv[50][3];   //[npar]
   Float_t         pmomv[50];   //[npar]
   Int_t           light_flag[50];   //[npar]
   Int_t           npar2;
   Float_t         wallv2[60];   //[npar2]
   UInt_t          ipv2[60];   //[npar2]
   UInt_t          iorg[60];   //[npar2]
   Float_t         posv2[60][3];   //[npar2]
   Float_t         dirv2[60][3];   //[npar2]
   Float_t         pmomv2[60];   //[npar2]
   Int_t           numnu;
   Int_t           mode;
   Int_t           ipnu[50];   //[numnu]
   Float_t         pnu[50];   //[numnu]
   Float_t         dirnu[50][3];   //[numnu]
   Float_t         flxg[3];
   Float_t         flxh01[3];
   Float_t         kflux[4];
   Float_t         bs71[3];
   Float_t         bs74[3];
   Float_t         flxf[3];
   Float_t         flxh1d[3];
   Float_t         flxb03[3];
   Float_t         flxf03[3];
   Float_t         flxh06[3];
   Float_t         flxh11[3];
   Int_t           scan[2];
   Int_t           nuceff_version;
   Int_t           charge_exchange;
   Int_t           absorbed;
   Int_t           multipi_gen;
   Int_t           scattering;
   Int_t           piless_dcy;
   Int_t           nscndprt;
   Int_t           itrkscnd[1000];   //[nscndprt]
   Int_t           istakscnd[1000];   //[nscndprt]
   Float_t         vtxscnd[1000][3];   //[nscndprt]
   Float_t         pscnd[1000][3];   //[nscndprt]
   Int_t           iprtscnd[1000];   //[nscndprt]
   Float_t         tscnd[1000];   //[nscndprt]
   Int_t           iprntprt[1000];   //[nscndprt]
   Int_t           lmecscnd[1000];   //[nscndprt]
   Int_t           iprnttrk[1000];   //[nscndprt]
   Int_t           iorgprt[1000];   //[nscndprt]
   Float_t         pprnt[1000][3];   //[nscndprt]
   Int_t           iflgscnd[1000];   //[nscndprt]
   Float_t         pprntinit[1000][3];   //[nscndprt]
   Float_t         vtxprnt[1000][3];   //[nscndprt]
   Int_t           iprntidx[1000];   //[nscndprt]
   Int_t           nchilds[1000];   //[nscndprt]
   Int_t           ichildidx[1000];   //[nscndprt]
   Int_t           Npvcscnd;
   Int_t           Nchildsvc[100];   //[Npvcscnd]
   Int_t           Ichildidxvc[100];   //[Npvcscnd]
   Int_t           Neutmode;
   Int_t           Npne;
   Int_t           Ipne[100];   //[Npne]
   Float_t         Abspne[100];   //[Npne]
   Float_t         Pvecne[100][3];   //[Npne]
   Int_t           Npvc;
   Int_t           Ipvc[100];   //[Npvc]
   Int_t           Ichvc[100];   //[Npvc]
   Int_t           Iorgvc[100];   //[Npvc]
   Int_t           Iflvc[100];   //[Npvc]
   Float_t         Abspvc[100];   //[Npvc]
   Float_t         Pvc[100][3];   //[Npvc]
   Float_t         Crsx;
   Float_t         Crsy;
   Float_t         Crsz;
   Float_t         Crsphi;
   Int_t           Numbndn;
   Int_t           Numbndp;
   Int_t           Numfrep;
   Int_t           Numatom;
   Int_t           Ibound;
   Int_t           Neutinpmt;
   Int_t           Nvert;
   Float_t         Posvert[300][3];   //[Nvert]
   Int_t           Iflgvert[300];   //[Nvert]
   Int_t           Nvcvert;
   Float_t         Dirvert[900][3];   //[Nvcvert]
   Float_t         Abspvert[900];   //[Nvcvert]
   Float_t         Abstpvert[900];   //[Nvcvert]
   Int_t           Ipvert[900];   //[Nvcvert]
   Int_t           Iverti[900];   //[Nvcvert]
   Int_t           Ivertf[900];   //[Nvcvert]
   Float_t         Fsiprob;
   Float_t         Fsivarwt[24];
   Int_t           catpc;
   Int_t           pcst_segment;
   Float_t         pcst_qobserved;
   Float_t         pcst_qexpected;
   Float_t         pcst_qobserved_raw;
   Float_t         pcst_pathod;
   Int_t           pcst_nhits;
   Int_t           pcst_oldhits;
   Int_t           pcst_newhits;
   Float_t         pcst_newq;
   Float_t         pcst_oldq;
   Float_t         pcst_odpos[3];
   Int_t           catpc_orig;
   Int_t           catpc_qrat_corrected;
   Float_t         pcst_qrat_correction;
   Float_t         trgoff;
   Int_t           fqntwnd;
   Int_t           fqtwnd_iclstr[10];   //[fqntwnd]
   Int_t           fqtwnd_npeak[10];   //[fqntwnd]
   Float_t         fqtwnd_prftt0[10];   //[fqntwnd]
   Float_t         fqtwnd_prftpos[10][3];   //[fqntwnd]
   Float_t         fqtwnd[10][2];   //[fqntwnd]
   Float_t         fqtwnd_peakt0[10][10];   //[fqntwnd]
   Float_t         fqtwnd_peakiness[10][10];   //[fqntwnd]
   Int_t           fqnse;
   Int_t           fqitwnd[12];   //[fqnse]
   Int_t           fqipeak[12];   //[fqnse]
   Int_t           fqnhitpmt[12];   //[fqnse]
   Float_t         fqtotq[12];   //[fqnse]
   Float_t         fq0rtotmu[12];   //[fqnse]
   Float_t         fq0rnll[12];   //[fqnse]
   Int_t           fqn50[12];   //[fqnse]
   Float_t         fqq50[12];   //[fqnse]
   Int_t           fq1rpcflg[12][7];   //[fqnse]
   Float_t         fq1rmom[12][7];   //[fqnse]
   Float_t         fq1rt0[12][7];   //[fqnse]
   Float_t         fq1rtotmu[12][7];   //[fqnse]
   Float_t         fq1rnll[12][7];   //[fqnse]
   Float_t         fq1rpos[12][7][3];   //[fqnse]
   Float_t         fq1rdir[12][7][3];   //[fqnse]
   Float_t         fq1rdconv[12][7];   //[fqnse]
   Float_t         fq1reloss[12][7];   //[fqnse]
   Int_t           fqpi0pcflg[2];
   Float_t         fqpi0mom1[2];
   Float_t         fqpi0mom2[2];
   Float_t         fqpi0momtot[2];
   Float_t         fqpi0dconv1[2];
   Float_t         fqpi0dconv2[2];
   Float_t         fqpi0t0[2];
   Float_t         fqpi0totmu[2];
   Float_t         fqpi0nll[2];
   Float_t         fqpi0mass[2];
   Float_t         fqpi0photangle[2];
   Float_t         fqpi0pos[2][3];
   Float_t         fqpi0dir1[2][3];
   Float_t         fqpi0dir2[2][3];
   Float_t         fqpi0dirtot[2][3];
   Int_t           fqpmgpcflg[2];
   Float_t         fqpmgmom1[2];
   Float_t         fqpmgmom2[2];
   Float_t         fqpmgt01[2];
   Float_t         fqpmgt02[2];
   Float_t         fqpmgtotmu[2];
   Float_t         fqpmgnll[2];
   Float_t         fqpmgpos1[2][3];
   Float_t         fqpmgpos2[2][3];
   Float_t         fqpmgdir1[2][3];
   Float_t         fqpmgdir2[2][3];
   Int_t           fqnmrfit;
   Int_t           fqmrifit[32];   //[fqnmrfit]
   Int_t           fqmrnring[32];   //[fqnmrfit]
   Int_t           fqmrpcflg[32];   //[fqnmrfit]
   Float_t         fqmrnll[32];   //[fqnmrfit]
   Float_t         fqmrtotmu[32];   //[fqnmrfit]
   Int_t           fqmrpid[32][6];   //[fqnmrfit]
   Float_t         fqmrmom[32][6];   //[fqnmrfit]
   Float_t         fqmrdconv[32][6];   //[fqnmrfit]
   Float_t         fqmreloss[32][6];   //[fqnmrfit]
   Float_t         fqmrt0[32][6];   //[fqnmrfit]
   Float_t         fqmrpos[32][6][3];   //[fqnmrfit]
   Float_t         fqmrdir[32][6][3];   //[fqnmrfit]
   Int_t           fqmsnfit;
   Int_t           fqmspcflg[5];   //[fqmsnfit]
   Int_t           fqmsnseg[5];   //[fqmsnfit]
   Int_t           fqmspid[5];   //[fqmsnfit]
   Int_t           fqmsifit[5];   //[fqmsnfit]
   Int_t           fqmsimer[5];   //[fqmsnfit]
   Float_t         fqmstotmu[5];   //[fqmsnfit]
   Float_t         fqmsnll[5];   //[fqmsnfit]
   Float_t         fqmsmom[5][20];   //[fqmsnfit]
   Float_t         fqmseloss[5][20];   //[fqmsnfit]
   Float_t         fqmst0[5][20];   //[fqmsnfit]
   Float_t         fqmspos[5][20][3];   //[fqmsnfit]
   Float_t         fqmsdir[5][20][3];   //[fqmsnfit]
   Float_t         prid_ang;
   Float_t         prid_len;
   Float_t         prid_pmom;
   Float_t         prid_mang;
   Float_t         prid_plike;
   Float_t         prid_mlike;
   Int_t           prid_nused;
   Float_t         dirtotepi[3];
   Float_t         dirtotenpi[3];
   Float_t         dirtotmue[3];
   Float_t         dirsum[3];
   Float_t         etot;
   Float_t         etotepi;
   Float_t         etotenpi;
   Float_t         etotmue;
   Float_t         oscweight[2][4];
   Float_t         oscwgt;
   Float_t         live;
   Float_t         sacth;
   Float_t         sactg;
   Float_t         sacth1d;
   Float_t         ccqelike;
   Float_t         mulike;
   Float_t         mproton;
   Float_t         outdir[3];
   Int_t           nused2;
   Float_t         vsum;
   Float_t         qsep;
   Float_t         qpeak;
   Float_t         qhigh;
   Float_t         qlow;
   Int_t           nzeros2;
   Float_t         moyenne2;
   Float_t         lproton;
   Float_t         qwin;
   Float_t         ent_pos[3];
   Float_t         ent_dir[3];
   Float_t         length;
   Float_t         tr_mom1;
   Float_t         A_ent_mom;
   Float_t         A_ent_pos[3];
   Float_t         A_ent_dir[3];
   Float_t         A_ext_mom;
   Float_t         A_ext_pos[3];
   Float_t         A_ext_dir[3];
   Float_t         Fit_pos[3];
   Float_t         Fit_dir[3];
   Float_t         Fit_len;
   Float_t         Fit_mom;
   Int_t           Fit_pid;
   Int_t           Um_ehit8m;
   Int_t           Um_ohit8m;
   Float_t         Um_qent;
   Float_t         Sh_chi1p;
   Float_t         Sh_delta;
   Float_t         Sh_mean;
   Float_t         Sh_meanq;
   Int_t           Sh_id;
   Float_t         Tr_stop[3];
   Float_t         Tr_mom;
   Float_t         Tr_len;
   Float_t         Tr_len1;
   Int_t           Pid_flg;
   Float_t         Crs1;
   Float_t         Crs2;
   Int_t           iclass;
   Int_t           mu_class;
   Int_t           mu_dec;
   Float_t         mu_dir[3];
   Float_t         mu_pos[3];
   Float_t         mu_good;
   Int_t           history;
   Int_t           Pdst;
   Int_t           idoff;
   Float_t         anthit;
   Int_t           idseq;
   Float_t         tstfrac;
   Int_t           judge;
   Float_t         Upcrs1;
   Float_t         Upcrs2;
   Float_t         lst;
   Int_t           jd;
   Float_t         fjd;
   Float_t         alt;
   Float_t         azi;
   Float_t         ra;
   Float_t         dec;
   Float_t         glat;
   Float_t         glong;
   Float_t         t2kposc[2][6];
   Int_t           evclass;
   Float_t         dt0;
   Float_t         pototin;
   Int_t           nurun;
   Int_t           good_spill_flag;
   Int_t           nspill;
   Int_t           t2knuefs;
   Int_t           t2knuenpi0;
   Int_t           t2knueflag;

   // List of branches
   TBranch        *b_nring;   //!
   TBranch        *b_nrun;   //!
   TBranch        *b_nev;   //!
   TBranch        *b_nsub;   //!
   TBranch        *b_cate;   //!
   TBranch        *b_potot;   //!
   TBranch        *b_nhit;   //!
   TBranch        *b_pomax;   //!
   TBranch        *b_potota;   //!
   TBranch        *b_nhita;   //!
   TBranch        *b_nhitac;   //!
   TBranch        *b_pomaxa;   //!
   TBranch        *b_wall;   //!
   TBranch        *b_evis;   //!
   TBranch        *b_rtsum;   //!
   TBranch        *b_rtmax;   //!
   TBranch        *b_wlen;   //!
   TBranch        *b_ip;   //!
   TBranch        *b_pos;   //!
   TBranch        *b_dir;   //!
   TBranch        *b_dirtot;   //!
   TBranch        *b_ang;   //!
   TBranch        *b_rtot;   //!
   TBranch        *b_amom;   //!
   TBranch        *b_rtote;   //!
   TBranch        *b_amome;   //!
   TBranch        *b_rtotm;   //!
   TBranch        *b_amomm;   //!
   TBranch        *b_nsube;   //!
   TBranch        *b_ndcy;   //!
   TBranch        *b_ngate;   //!
   TBranch        *b_nbye;   //!
   TBranch        *b_probms;   //!
   TBranch        *b_prmslg;   //!
   TBranch        *b_date;   //!
   TBranch        *b_time;   //!
   TBranch        *b_elpsday;   //!
   TBranch        *b_numpo;   //!
   TBranch        *b_apos;   //!
   TBranch        *b_adir;   //!
   TBranch        *b_aang;   //!
   TBranch        *b_agood;   //!
   TBranch        *b_wgain;   //!
   TBranch        *b_nbad;   //!
   TBranch        *b_nbada;   //!
   TBranch        *b_msdir;   //!
   TBranch        *b_amomp;   //!
   TBranch        *b_ange;   //!
   TBranch        *b_angm;   //!
   TBranch        *b_angp;   //!
   TBranch        *b_ntot;   //!
   TBranch        *b_probth;   //!
   TBranch        *b_probpt;   //!
   TBranch        *b_pi0like;   //!
   TBranch        *b_pi0_e;   //!
   TBranch        *b_pi0_dir;   //!
   TBranch        *b_pi0mass;   //!
   TBranch        *b_evisold;   //!
   TBranch        *b_evisoldxe;   //!
   TBranch        *b_evisnew;   //!
   TBranch        *b_nmue;   //!
   TBranch        *b_etype;   //!
   TBranch        *b_etime;   //!
   TBranch        *b_epos;   //!
   TBranch        *b_edir;   //!
   TBranch        *b_egood;   //!
   TBranch        *b_ehit;   //!
   TBranch        *b_mueprob;   //!
   TBranch        *b_nmue_sel;   //!
   TBranch        *b_Rnring;   //!
   TBranch        *b_Rdir;   //!
   TBranch        *b_Rang;   //!
   TBranch        *b_Riring;   //!
   TBranch        *b_Rtwout;   //!
   TBranch        *b_Rtwith;   //!
   TBranch        *b_Alwout;   //!
   TBranch        *b_Alwith;   //!
   TBranch        *b_Qsmi;   //!
   TBranch        *b_Qsmo;   //!
   TBranch        *b_Qexi;   //!
   TBranch        *b_Qexo;   //!
   TBranch        *b_Pe5d;   //!
   TBranch        *b_En5d;   //!
   TBranch        *b_Eh5d;   //!
   TBranch        *b_Pe5do;   //!
   TBranch        *b_En5do;   //!
   TBranch        *b_Eh5do;   //!
   TBranch        *b_Rtadd;   //!
   TBranch        *b_Pdgeta;   //!
   TBranch        *b_Pd5d;   //!
   TBranch        *b_Pdthre;   //!
   TBranch        *b_Pd5do;   //!
   TBranch        *b_Delpd;   //!
   TBranch        *b_Ropena;   //!
   TBranch        *b_Maxth;   //!
   TBranch        *b_Pkang;   //!
   TBranch        *b_Qrfct;   //!
   TBranch        *b_Pdfct;   //!
   TBranch        *b_Pkfct;   //!
   TBranch        *b_Agfct;   //!
   TBranch        *b_Dlfct;   //!
   TBranch        *b_Iflag;   //!
   TBranch        *b_Pmfct;   //!
   TBranch        *b_Imfct;   //!
   TBranch        *b_Rilike;   //!
   TBranch        *b_ri_ver;   //!
   TBranch        *b_ri_pid;   //!
   TBranch        *b_ri_nring;   //!
   TBranch        *b_ri_flag;   //!
   TBranch        *b_ri_dlfct;   //!
   TBranch        *b_ri_pdfct;   //!
   TBranch        *b_ri_pkfct;   //!
   TBranch        *b_ri_vafct;   //!
   TBranch        *b_ri_total;   //!
   TBranch        *b_ri_dir;   //!
   TBranch        *b_ri_imfct;   //!
   TBranch        *b_ri_pmfct;   //!
   TBranch        *b_npar;   //!
   TBranch        *b_wallv;   //!
   TBranch        *b_ipv;   //!
   TBranch        *b_posv;   //!
   TBranch        *b_dirv;   //!
   TBranch        *b_pmomv;   //!
   TBranch        *b_light_flag;   //!
   TBranch        *b_npar2;   //!
   TBranch        *b_wallv2;   //!
   TBranch        *b_ipv2;   //!
   TBranch        *b_iorg;   //!
   TBranch        *b_posv2;   //!
   TBranch        *b_dirv2;   //!
   TBranch        *b_pmomv2;   //!
   TBranch        *b_numnu;   //!
   TBranch        *b_mode;   //!
   TBranch        *b_ipnu;   //!
   TBranch        *b_pnu;   //!
   TBranch        *b_dirnu;   //!
   TBranch        *b_flxg;   //!
   TBranch        *b_flxh01;   //!
   TBranch        *b_kflux;   //!
   TBranch        *b_bs71;   //!
   TBranch        *b_bs74;   //!
   TBranch        *b_flxf;   //!
   TBranch        *b_flxh1d;   //!
   TBranch        *b_flxb03;   //!
   TBranch        *b_flxf03;   //!
   TBranch        *b_flxh06;   //!
   TBranch        *b_flxh11;   //!
   TBranch        *b_scan;   //!
   TBranch        *b_nuceff_version;   //!
   TBranch        *b_charge_exchange;   //!
   TBranch        *b_absorbed;   //!
   TBranch        *b_multipi_gen;   //!
   TBranch        *b_scattering;   //!
   TBranch        *b_piless_dcy;   //!
   TBranch        *b_nscndprt;   //!
   TBranch        *b_itrkscnd;   //!
   TBranch        *b_istakscnd;   //!
   TBranch        *b_vtxscnd;   //!
   TBranch        *b_pscnd;   //!
   TBranch        *b_iprtscnd;   //!
   TBranch        *b_tscnd;   //!
   TBranch        *b_iprntprt;   //!
   TBranch        *b_lmecscnd;   //!
   TBranch        *b_iprnttrk;   //!
   TBranch        *b_iorgprt;   //!
   TBranch        *b_pprnt;   //!
   TBranch        *b_iflgscnd;   //!
   TBranch        *b_pprntinit;   //!
   TBranch        *b_vtxprnt;   //!
   TBranch        *b_iprntidx;   //!
   TBranch        *b_nchilds;   //!
   TBranch        *b_ichildidx;   //!
   TBranch        *b_Npvcscnd;   //!
   TBranch        *b_Nchildsvc;   //!
   TBranch        *b_Ichildidxvc;   //!
   TBranch        *b_Neutmode;   //!
   TBranch        *b_Npne;   //!
   TBranch        *b_Ipne;   //!
   TBranch        *b_Abspne;   //!
   TBranch        *b_Pvecne;   //!
   TBranch        *b_Npvc;   //!
   TBranch        *b_Ipvc;   //!
   TBranch        *b_Ichvc;   //!
   TBranch        *b_Iorgvc;   //!
   TBranch        *b_Iflvc;   //!
   TBranch        *b_Abspvc;   //!
   TBranch        *b_Pvc;   //!
   TBranch        *b_Crsx;   //!
   TBranch        *b_Crsy;   //!
   TBranch        *b_Crsz;   //!
   TBranch        *b_Crsphi;   //!
   TBranch        *b_Numbndn;   //!
   TBranch        *b_Numbndp;   //!
   TBranch        *b_Numfrep;   //!
   TBranch        *b_Numatom;   //!
   TBranch        *b_Ibound;   //!
   TBranch        *b_Neutinpmt;   //!
   TBranch        *b_Nvert;   //!
   TBranch        *b_Posvert;   //!
   TBranch        *b_Iflgvert;   //!
   TBranch        *b_Nvcvert;   //!
   TBranch        *b_Dirvert;   //!
   TBranch        *b_Abspvert;   //!
   TBranch        *b_Abstpvert;   //!
   TBranch        *b_Ipvert;   //!
   TBranch        *b_Iverti;   //!
   TBranch        *b_Ivertf;   //!
   TBranch        *b_Fsiprob;   //!
   TBranch        *b_Fsivarwt;   //!
   TBranch        *b_catpc;   //!
   TBranch        *b_pcst_segment;   //!
   TBranch        *b_pcst_qobserved;   //!
   TBranch        *b_pcst_qexpected;   //!
   TBranch        *b_pcst_qobserved_raw;   //!
   TBranch        *b_pcst_pathod;   //!
   TBranch        *b_pcst_nhits;   //!
   TBranch        *b_pcst_oldhits;   //!
   TBranch        *b_pcst_newhits;   //!
   TBranch        *b_pcst_newq;   //!
   TBranch        *b_pcst_oldq;   //!
   TBranch        *b_pcst_odpos;   //!
   TBranch        *b_catpc_orig;   //!
   TBranch        *b_catpc_qrat_corrected;   //!
   TBranch        *b_pcst_qrat_correction;   //!
   TBranch        *b_trgoff;   //!
   TBranch        *b_fqntwnd;   //!
   TBranch        *b_fqtwnd_iclstr;   //!
   TBranch        *b_fqtwnd_npeak;   //!
   TBranch        *b_fqtwnd_prftt0;   //!
   TBranch        *b_fqtwnd_prftpos;   //!
   TBranch        *b_fqtwnd;   //!
   TBranch        *b_fqtwnd_peakt0;   //!
   TBranch        *b_fqtwnd_peakiness;   //!
   TBranch        *b_fqnse;   //!
   TBranch        *b_fqitwnd;   //!
   TBranch        *b_fqipeak;   //!
   TBranch        *b_fqnhitpmt;   //!
   TBranch        *b_fqtotq;   //!
   TBranch        *b_fq0rtotmu;   //!
   TBranch        *b_fq0rnll;   //!
   TBranch        *b_fqn50;   //!
   TBranch        *b_fqq50;   //!
   TBranch        *b_fq1rpcflg;   //!
   TBranch        *b_fq1rmom;   //!
   TBranch        *b_fq1rt0;   //!
   TBranch        *b_fq1rtotmu;   //!
   TBranch        *b_fq1rnll;   //!
   TBranch        *b_fq1rpos;   //!
   TBranch        *b_fq1rdir;   //!
   TBranch        *b_fq1rdconv;   //!
   TBranch        *b_fq1reloss;   //!
   TBranch        *b_fqpi0pcflg;   //!
   TBranch        *b_fqpi0mom1;   //!
   TBranch        *b_fqpi0mom2;   //!
   TBranch        *b_fqpi0momtot;   //!
   TBranch        *b_fqpi0dconv1;   //!
   TBranch        *b_fqpi0dconv2;   //!
   TBranch        *b_fqpi0t0;   //!
   TBranch        *b_fqpi0totmu;   //!
   TBranch        *b_fqpi0nll;   //!
   TBranch        *b_fqpi0mass;   //!
   TBranch        *b_fqpi0photangle;   //!
   TBranch        *b_fqpi0pos;   //!
   TBranch        *b_fqpi0dir1;   //!
   TBranch        *b_fqpi0dir2;   //!
   TBranch        *b_fqpi0dirtot;   //!
   TBranch        *b_fqpmgpcflg;   //!
   TBranch        *b_fqpmgmom1;   //!
   TBranch        *b_fqpmgmom2;   //!
   TBranch        *b_fqpmgt01;   //!
   TBranch        *b_fqpmgt02;   //!
   TBranch        *b_fqpmgtotmu;   //!
   TBranch        *b_fqpmgnll;   //!
   TBranch        *b_fqpmgpos1;   //!
   TBranch        *b_fqpmgpos2;   //!
   TBranch        *b_fqpmgdir1;   //!
   TBranch        *b_fqpmgdir2;   //!
   TBranch        *b_fqnmrfit;   //!
   TBranch        *b_fqmrifit;   //!
   TBranch        *b_fqmrnring;   //!
   TBranch        *b_fqmrpcflg;   //!
   TBranch        *b_fqmrnll;   //!
   TBranch        *b_fqmrtotmu;   //!
   TBranch        *b_fqmrpid;   //!
   TBranch        *b_fqmrmom;   //!
   TBranch        *b_fqmrdconv;   //!
   TBranch        *b_fqmreloss;   //!
   TBranch        *b_fqmrt0;   //!
   TBranch        *b_fqmrpos;   //!
   TBranch        *b_fqmrdir;   //!
   TBranch        *b_fqmsnfit;   //!
   TBranch        *b_fqmspcflg;   //!
   TBranch        *b_fqmsnseg;   //!
   TBranch        *b_fqmspid;   //!
   TBranch        *b_fqmsifit;   //!
   TBranch        *b_fqmsimer;   //!
   TBranch        *b_fqmstotmu;   //!
   TBranch        *b_fqmsnll;   //!
   TBranch        *b_fqmsmom;   //!
   TBranch        *b_fqmseloss;   //!
   TBranch        *b_fqmst0;   //!
   TBranch        *b_fqmspos;   //!
   TBranch        *b_fqmsdir;   //!
   TBranch        *b_prid_ang;   //!
   TBranch        *b_prid_len;   //!
   TBranch        *b_prid_pmom;   //!
   TBranch        *b_prid_mang;   //!
   TBranch        *b_prid_plike;   //!
   TBranch        *b_prid_mlike;   //!
   TBranch        *b_prid_nused;   //!
   TBranch        *b_dirtotepi;   //!
   TBranch        *b_dirtotenpi;   //!
   TBranch        *b_dirtotmue;   //!
   TBranch        *b_dirsum;   //!
   TBranch        *b_etot;   //!
   TBranch        *b_etotepi;   //!
   TBranch        *b_etotenpi;   //!
   TBranch        *b_etotmue;   //!
   TBranch        *b_oscweight;   //!
   TBranch        *b_oscwgt;   //!
   TBranch        *b_live;   //!
   TBranch        *b_sacth;   //!
   TBranch        *b_sactg;   //!
   TBranch        *b_sacth1d;   //!
   TBranch        *b_ccqelike;   //!
   TBranch        *b_mulike;   //!
   TBranch        *b_mproton;   //!
   TBranch        *b_outdir;   //!
   TBranch        *b_nused2;   //!
   TBranch        *b_vsum;   //!
   TBranch        *b_qsep;   //!
   TBranch        *b_qpeak;   //!
   TBranch        *b_qhigh;   //!
   TBranch        *b_qlow;   //!
   TBranch        *b_nzeros2;   //!
   TBranch        *b_moyenne2;   //!
   TBranch        *b_lproton;   //!
   TBranch        *b_qwin;   //!
   TBranch        *b_ent_pos;   //!
   TBranch        *b_ent_dir;   //!
   TBranch        *b_length;   //!
   TBranch        *b_tr_mom1;   //!
   TBranch        *b_A_ent_mom;   //!
   TBranch        *b_A_ent_pos;   //!
   TBranch        *b_A_ent_dir;   //!
   TBranch        *b_A_ext_mom;   //!
   TBranch        *b_A_ext_pos;   //!
   TBranch        *b_A_ext_dir;   //!
   TBranch        *b_Fit_pos;   //!
   TBranch        *b_Fit_dir;   //!
   TBranch        *b_Fit_len;   //!
   TBranch        *b_Fit_mom;   //!
   TBranch        *b_Fit_pid;   //!
   TBranch        *b_Um_ehit8m;   //!
   TBranch        *b_Um_ohit8m;   //!
   TBranch        *b_Um_qent;   //!
   TBranch        *b_Sh_chi1p;   //!
   TBranch        *b_Sh_delta;   //!
   TBranch        *b_Sh_mean;   //!
   TBranch        *b_Sh_meanq;   //!
   TBranch        *b_Sh_id;   //!
   TBranch        *b_Tr_stop;   //!
   TBranch        *b_Tr_mom;   //!
   TBranch        *b_Tr_len;   //!
   TBranch        *b_Tr_len1;   //!
   TBranch        *b_Pid_flg;   //!
   TBranch        *b_Crs1;   //!
   TBranch        *b_Crs2;   //!
   TBranch        *b_iclass;   //!
   TBranch        *b_mu_class;   //!
   TBranch        *b_mu_dec;   //!
   TBranch        *b_mu_dir;   //!
   TBranch        *b_mu_pos;   //!
   TBranch        *b_mu_good;   //!
   TBranch        *b_history;   //!
   TBranch        *b_Pdst;   //!
   TBranch        *b_idoff;   //!
   TBranch        *b_anthit;   //!
   TBranch        *b_idseq;   //!
   TBranch        *b_tstfrac;   //!
   TBranch        *b_judge;   //!
   TBranch        *b_Upcrs1;   //!
   TBranch        *b_Upcrs2;   //!
   TBranch        *b_lst;   //!
   TBranch        *b_jd;   //!
   TBranch        *b_fjd;   //!
   TBranch        *b_alt;   //!
   TBranch        *b_azi;   //!
   TBranch        *b_ra;   //!
   TBranch        *b_dec;   //!
   TBranch        *b_glat;   //!
   TBranch        *b_glong;   //!
   TBranch        *b_t2kposc;   //!
   TBranch        *b_evclass;   //!
   TBranch        *b_dt0;   //!
   TBranch        *b_pototin;   //!
   TBranch        *b_nurun;   //!
   TBranch        *b_good_spill_flag;   //!
   TBranch        *b_nspill;   //!
   TBranch        *b_t2knuefs;   //!
   TBranch        *b_t2knuenpi0;   //!
   TBranch        *b_t2knueflag;   //!


  typedef enum{
    NCPi0 = 0,
    _1RePi0,
    _1dcyePi0,
    noemupid,
  } SelType;

   SKMCdataTree(TTree *tree=0);
   virtual ~SKMCdataTree();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   void     LoopSelection(std::string horn_current, std::string osc_sample); //Just selection
   void		LoopNCHistos(std::string horn_current, std::string osc_sample, int sel);    //Main selection and histograms


   void     LoopHKCutPlots(std::string horn_current, std::string osc_sample);
   void     LoopEffHistosHK(std::string horn_current, std::string osc_sample);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);

//Particle indices for SK arrays
    typedef enum{
        ELECTRON = 1,
        MUON,
        PION
    } fq_particle;
   

	typedef enum{
		NUMU = 0, 
		NUE,
		NUMUBAR,
		NUEBAR,
		NUMUTONUE,
		NUMUBARTONUEBAR
	} FileFlavor;

  
/*
	double numerators[12];
	numerators[0]  = 1373.8715753; // NHC numu
	numerators[1]  = 26.224814886; // NHC nue
	numerators[2]  = 48.4951744134; // NHC numubar
	numerators[3]  = 2.74910336093; // NHC nuebar
	numerators[4]  = 1458.3399999; // NHC signue
	numerators[5]  = 50.2120145538; // NHC signuebar
	numerators[6]  = 205.213957312; // RHC numu
	numerators[7]  = 8.79315608601; // RHC nue
	numerators[8]  = 338.496583643; // RHC numubar
	numerators[9]  = 6.52180351576; // RHC nuebar
	numerators[10] = 211.81697101 ; // RHC signue
	numerators[11] = 357.710318015; // RHC signuebar

	double denominators[12];
	denominators[0] = 634441; // NHC numu
	denominators[1] = 127010; // NHC nue
	denominators[2] = 635545; // NHC numubar
	denominators[3] = 126865; // NHC nuebar
	denominators[4] = 127017; // NHC signue
	denominators[5] = 126509; // NHC signuebar
	denominators[6] = 634250; // RHC numu
	denominators[7] = 126829; // RHC nue
	denominators[8] = 634817; // RHC numubar
	denominators[9] = 126982; // RHC nuebar
	denominators[10] = 126923; // RHC signue
	denominators[11] = 126928; // RHC signuebar
*/	
	
	double fhcfileWeights[6] = {1373.8715753 / 634441, 26.224814886 / 127010, 48.4951744134 / 635545, 2.74910336093 / 126865,1458.3399999 / 127017, 50.2120145538 / 126509};
	double rhcfileWeights[6] = {205.213957312 / 634250, 8.79315608601 / 126829, 338.496583643 / 634817, 6.52180351576/ 126982, 211.81697101/126923 , 357.710318015 / 126928};
	
	//double fhcfileWeights[6] = {1396.245 / 634881., 26.663 / 126899., 50.964 / 634600., 2.884 / 126728.,1483.994 / 126916., 52.939 / 126984.};
	//double rhcfileWeights[6] = {208.369 / 634659.,  8.941 / 127262., 353.789 / 633988., 6.811 / 127013., 215.099 / 127278., 376.420 / 126812.};
	
	void AddFileFlavorInt(vector<int> fileFlavor);
    vector<int> fileFlavorInt;

	double weight;
	int mainEventIndex;
	bool IsRecoElectron();
	float GetRecoDWall();
	float GetRecoDWall_pi0();
	float GetRecoToWall();
	float GetRecoToWall_pi0();
	float ComputeDWall(float x, float y, float z);
	float ComputeToWall(float x, float y, float z, float dx, float dy, float dz);
	
	bool IsFCFV(); 
	float TwoRingpi0InvMass();
	bool IsSingleRingELike();
	bool IsSingleRingMuLike();
	void FormatHist(TH1D* h, int linecolor, int linestyle);
	void FormatHist2D(TH2F* h);
	void AddEventToHisto(int cutID, float w);
	bool CanReco();
	bool IsfQPi0();
	bool IsfQPi0tuned();
  float ifitPi0mom();
	void DrawHist(TH1D* histo, std::string mode, std::string param,  std::string horn_current, std::string osc_sample, std::string figs_subdir, std::string settitle="default" );
	void DrawHist2D(TH2F* histo, std::string mode, std::string x_param,  std::string y_param, std::string horn_current, std::string osc_sample, std::string figs_subdir);
	float rc_par();

	float electron_muon_PID();
	float piplus_muon_PID();
	float pi0_electron_PID();
  
 
  float nllr_2Rother_ee();
  float nllr_pi0_ee();
	float nllr_2Rother_pipi();
	float sum_eloss_pipi();
	float nllr_pipi_e();
	float ComputeErec(float LeptonP, fq_particle i_particle, float cosBeam);
	float ComputeCosBeam( int nsubevent, fq_particle i_particle);
	int GetNRings(double cut_value);
	//int ComputeRCInitialFitter(double cut_value_Ea0 = 0, double cut_value_Mua0 = 0, double cut_value_a0 = 0, double cut_value_a1 = 0, bool verbose = false, int plot_hypothesis = 0, double * maxNLL_2Re = NULL, double * minMom_2Re = NULL, double * minAngle_2Re = NULL);

	int ComputeRCInitialFitter(double cut_value_Ea0 , double cut_value_Mua0 , double cut_value_a0 , double cut_value_a1 , bool verbose,  int plot_hypothesis , double * maxNLL_2Re , double * minMom_2Re , double * minAngle_2Re );

	bool kSquared; 
	int    kNuBar ;
	double DM2    ;
	double Theta23;
	double Theta13;
	double dm2    ;
	double Theta12;
	double dcp   ;

	// Density and path length
	double BasePath;
	double Density ;

  void ProbSK();
  void SetAntiNeutrino(bool isAntiNeutrino);
  double GetProb(int initialSpecies, int finalSpecies);
  double GetOscProb(int initialSpecies, int finalSpecies, float energy);
  double GetProbNuMuNuE(float energy);
  double GetProbNuMuNuMu(float energy);
  double GetProbNuMuBarNuMuBar(float energy);
  double GetProbNuMuBarNuEBar(float energy);
  double GetProbNuENuE(float energy);
  double GetProbNuEBarNuEBar(float energy);
  BargerPropagator   * bNu; 
	void FillHistos(int cut, int mode, float w);
  void InitNCHistos();	
	float ComputeTrueCosBeam();

private:
   bool phase0;
   double beamdir[3] = { 0.669764, -0.742179, 0.024223 }; 
   float IDRadius;
   float IDHalfLength;
   float IDCenterY;
   float beamDecay[3];
   float beamDir[3];
      
   float dwall_lim;
   float towall_lim;
   float ev_towall;
   float ev_dwall;
   double true_selected = 0;
   double total_selected = 0;
   double total_true = 0;
   double CCqe_tot, CC1pi_tot, CCOther_tot, NC1pi0_tot, NC1pipm_tot, NCOther_tot;
   double CC2p2h_tot, CCmisc_tot, CCCoh_tot, CCmpi_tot, CCdis_tot, NCCoh_tot, NC1gamma_tot;
   double NCmpi_tot, NCEta_tot, NCDIS_tot, NCElastic_tot;
   

   /////////////////////    HISTOS    /////////////////
  const static int numHist = 16;
	const static int numCuts = 10;
	float totSel[2][numCuts] = {{0}};
	float peakSel[2][numCuts] = {{0}};
std::string varNames[numHist] = {"CCqe", "CC1pi", "CCCoh", "CCmultipi", "CCDis", "NC1pi0", "NC1pipm", "NCCoh", "NCOther", "CC2p2h", "NC1gamma", "CCmisc", "NCmpi", "NCEta", "NCDIS", "NCElastic"} ;
  
  TH1D* nhitac_histo[numCuts][numHist] = {{0}};
	TH1F* evis_histo[numCuts][numHist] = {{0}};
	TH1F* towall_histo[numCuts][numHist] = {{0}};
	TH1F* dwall_histo[numCuts][numHist] = {{0}};
	TH1D* nring_histo[numCuts][numHist] = {{0}};
	TH1D* pid1_histo[numCuts][numHist] = {{0}};
	TH1D* pid2_histo[numCuts][numHist] = {{0}};
	TH1D* fqnse_histo[numCuts][numHist] = {{0}};
	TH1F* fq1rmom_histo[numCuts][numHist] = {{0}};
	TH1F* Erec_histo[numCuts][numHist] = {{0}};
	TH1F* apfitEvis_histo[numCuts][numHist] = {{0}};
	TH2F* fqpi0nll_histo[numCuts][numHist] = {{0}};
	TH1F* fqpi0nll_1D_histo[numCuts][numHist] = {{0}};
	TH2F* fqpi0nll_highmass_histo[numCuts][numHist] = {{0}};
	TH1F* fqpi0mass_histo[numCuts][numHist] = {{0}};
	TH1F* trueE_histo[numCuts][numHist] = {{0}};
	TH1F* Q2_histo[numCuts][numHist] = {{0}};
	TH2F* mom_dir_histo[numCuts][numHist] = {{0}};
	TH2F* x_y_histo[numCuts][numHist] = {{0}};
	TH2F* r2_z_histo[numCuts][numHist] = {{0}};
	TH1F* ring_2_mom_histo[numCuts][numHist] = {{0}};
  TH1F* fq1Remunll_histo[numCuts][numHist] = {{0}};
  TH1F* nllr_2Rother_ee_histo[numCuts][numHist] = {{0}};
  TH2F* nllr_pi0mom_2Ree_histo[numCuts][numHist] = {{0}};
  TH1F* pi0mom_histo[numCuts][numHist] = {{0}};
  TH1F* pi0momR1_histo[numCuts][numHist] = {{0}};
  TH1F* pi0momR2_histo[numCuts][numHist] = {{0}};
  TH1F* fqtotq_histo[numCuts][numHist] = {{0}};
  TH1F* nllr_ee_pi0_histo[numCuts][numHist] = {{0}};
/*
	TH1D* CC1pipm_histo[numHist]
	CC1pipm_histo[0] = new TH1D ("CC1pipm_nhitac_histo", "",40, 0, 100);
	CC1pipm_histo[1] = new TH1F ("CC1pipm_evis_histo", "",100, 0, 500);
	CC1pipm_histo[2] = new TH1F ("CC1pipm_towall_histo", "",40, 0, 300);
	CC1pipm_histo[3] = new TH1F ("CC1pipm_dwall_histo", "",40, 0, 300);
	CC1pipm_histo[4] = new TH1D ("CC1pipm_nring_histo", "",40, 0, 6);
	CC1pipm_histo[5] = new TH1D ("CC1pipm_PID1_histo", "",40, 0, 6);
	CC1pipm_histo[6] = new TH1D ("CC1pipm_PID2_histo", "",40, 0, 6);
	CC1pipm_histo[7] = new TH1D ("CC1pipm_fqnse_histo", "",40, 0, 10);
	CC1pipm_histo[8]= new TH1F ("CC1pipm_pi0mass_histo", "",100, 0, 300);
	CC1pipm_histo[9] = new TH2D ("CC1pipm_fQpi0nll_histo", "",40, 0, 300, 40, -50, 500);

	TH1D* CC1pi0_histo[numHist]
	CC1pi0_histo[0] = new TH1D ("CC1pi0_nhitac_histo", "",40, 0, 100);
	CC1pi0_histo[1] = new TH1F ("CC1pi0_evis_histo", "",100, 0, 500);
	CC1pi0_histo[2] = new TH1F ("CC1pi0_towall_histo", "",40, 0, 300);
	CC1pi0_histo[3] = new TH1F ("CC1pi0_dwall_histo", "",40, 0, 300);
	CC1pi0_histo[4] = new TH1D ("CC1pi0_nring_histo", "",40, 0, 6);
	CC1pi0_histo[5] = new TH1D ("CC1pi0_PID1_histo", "",40, 0, 6);
	CC1pi0_histo[6] = new TH1D ("CC1pi0_PID2_histo", "",40, 0, 6);
	CC1pi0_histo[7] = new TH1D ("CC1pi0_fqnse_histo", "",40, 0, 10);
	CC1pi0_histo[8]= new TH1F ("CC1pi0_pi0mass_histo", "",100, 0, 300);
	CC1pi0_histo[9] = new TH2D ("CC1pi0_fQpi0nll_histo", "",40, 0, 300, 40, -50, 500);

	TH1D* CCOther_histo[numHist]
	CCOther_histo[0] = new TH1D ("CCOther_nhitac_histo", "",40, 0, 100);
	CCOther_histo[1] = new TH1F ("CCOther_evis_histo", "",100, 0, 500);
	CCOther_histo[2] = new TH1F ("CCOther_towall_histo", "",40, 0, 300);
	CCOther_histo[3] = new TH1F ("CCOther_dwall_histo", "",40, 0, 300);
	CCOther_histo[4] = new TH1D ("CCOther_nring_histo", "",40, 0, 6);
	CCOther_histo[5] = new TH1D ("CCOther_PID1_histo", "",40, 0, 6);
	CCOther_histo[6] = new TH1D ("CCOther_PID2_histo", "",40, 0, 6);
	CCOther_histo[7] = new TH1D ("CCOther_fqnse_histo", "",40, 0, 10);
	CCOther_histo[8]= new TH1F ("CCOther_pi0mass_histo", "",100, 0, 300);
	CCOther_histo[9] = new TH2D ("CCOther_fQpi0nll_histo", "",40, 0, 300, 40, -50, 500);
	
	TH1D* NC1pi0_histo[numHist]
	NC1pi0_histo[0] = new TH1D ("NC1pi0_nhitac_histo", "",40, 0, 100);
	NC1pi0_histo[1] = new TH1F ("NC1pi0_evis_histo", "",100, 0, 500);
	NC1pi0_histo[2] = new TH1F ("NC1pi0_towall_histo", "",40, 0, 300);
	NC1pi0_histo[3] = new TH1F ("NC1pi0_dwall_histo", "",40, 0, 300);
	NC1pi0_histo[4] = new TH1D ("NC1pi0_nring_histo", "",40, 0, 6);
	NC1pi0_histo[5] = new TH1D ("NC1pi0_PID1_histo", "",40, 0, 6);
	NC1pi0_histo[6] = new TH1D ("NC1pi0_PID2_histo", "",40, 0, 6);
	NC1pi0_histo[7] = new TH1D ("NC1pi0_fqnse_histo", "",40, 0, 10);
	NC1pi0_histo[8]= new TH1F ("NC1pi0_pi0mass_histo", "",100, 0, 300);
	NC1pi0_histo[9] = new TH2D ("NC1pi0_fQpi0nll_histo", "",40, 0, 300, 40, -50, 500);
	
	TH1D* NC1pipm_histo[numHist]
	NC1pipm_histo[0] = new TH1D ("NC1pipm_nring_histo", "",40, 0, 100);
	NC1pipm_histo[1] = new TH1F ("NC1pipm_evis_histo", "",100, 0, 500);
	NC1pipm_histo[2] = new TH1F ("NC1pipm_towall_histo", "",40, 0, 300);
	NC1pipm_histo[3] = new TH1F ("NC1pipm_dwall_histo", "",40, 0, 300);
	NC1pipm_histo[4] = new TH1D ("NC1pipm_nring_histo", "",40, 0, 6);
	NC1pipm_histo[5] = new TH1D ("NC1pipm_PID1_histo", "",40, 0, 6);
	NC1pipm_histo[6] = new TH1D ("NC1pipm_PID2_histo", "",40, 0, 6);
	NC1pipm_histo[7] = new TH1D ("NC1pipm_fqnse_histo", "",40, 0, 10);
	NC1pipm_histo[8]= new TH1F ("NC1pipm_pi0mass_histo", "",100, 0, 300);
	NC1pipm_histo[9] = new TH2D ("NC1pipm_fQpi0nll_histo", "",40, 0, 300, 40, -50, 500);
	
	TH1D* NCOther_histo[numHist]
	NCOther_histo[0] = new TH1D ("NCOther_nring_histo", "",40, 0, 100);
	NCOther_histo[1] = new TH1F ("NCOther_evis_histo", "",100, 0, 500);
	NCOther_histo[2] = new TH1F ("NCOther_towall_histo", "",40, 0, 300);
	NCOther_histo[3] = new TH1F ("NCOther_dwall_histo", "",40, 0, 300);
	NCOther_histo[4] = new TH1D ("NCOther_nring_histo", "",40, 0, 6);
	NCOther_histo[5] = new TH1D ("NCOther_PID1_histo", "",40, 0, 6);
	NCOther_histo[6] = new TH1D ("NCOther_PID2_histo", "",40, 0, 6);
	NCOther_histo[7] = new TH1D ("NCOther_fqnse_histo", "",40, 0, 10);
	NCOther_histo[8]= new TH1F ("NCOther_pi0mass_histo", "",100, 0, 300);
	NCOther_histo[9] = new TH2D ("NCOther_fQpi0nll_histo", "",40, 0, 300, 40, -50, 500);
*/	
	
	
};

#endif

#ifdef SKMCdataTree_cxx


SKMCdataTree::SKMCdataTree(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("t2ksk19b.fqv4r0.fhc.nue_x_nue.0319.009.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("t2ksk19b.fqv4r0.fhc.nue_x_nue.0319.009.root");
      }
      f->GetObject("h1",tree);

   }
   Init(tree);
}

SKMCdataTree::~SKMCdataTree()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t SKMCdataTree::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t SKMCdataTree::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void SKMCdataTree::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("nring", &nring, &b_nring);
   fChain->SetBranchAddress("nrun", &nrun, &b_nrun);
   fChain->SetBranchAddress("nev", &nev, &b_nev);
   fChain->SetBranchAddress("nsub", &nsub, &b_nsub);
   fChain->SetBranchAddress("cate", &cate, &b_cate);
   fChain->SetBranchAddress("potot", &potot, &b_potot);
   fChain->SetBranchAddress("nhit", &nhit, &b_nhit);
   fChain->SetBranchAddress("pomax", &pomax, &b_pomax);
   fChain->SetBranchAddress("potota", &potota, &b_potota);
   fChain->SetBranchAddress("nhita", &nhita, &b_nhita);
   fChain->SetBranchAddress("nhitac", &nhitac, &b_nhitac);
   fChain->SetBranchAddress("pomaxa", &pomaxa, &b_pomaxa);
   fChain->SetBranchAddress("wall", &wall, &b_wall);
   fChain->SetBranchAddress("evis", &evis, &b_evis);
   fChain->SetBranchAddress("rtsum", &rtsum, &b_rtsum);
   fChain->SetBranchAddress("rtmax", &rtmax, &b_rtmax);
   fChain->SetBranchAddress("wlen", &wlen, &b_wlen);
   fChain->SetBranchAddress("ip", ip, &b_ip);
   fChain->SetBranchAddress("pos", pos, &b_pos);
   fChain->SetBranchAddress("dir", dir, &b_dir);
   fChain->SetBranchAddress("dirtot", dirtot, &b_dirtot);
   fChain->SetBranchAddress("ang", ang, &b_ang);
   fChain->SetBranchAddress("rtot", rtot, &b_rtot);
   fChain->SetBranchAddress("amom", amom, &b_amom);
   fChain->SetBranchAddress("rtote", rtote, &b_rtote);
   fChain->SetBranchAddress("amome", amome, &b_amome);
   fChain->SetBranchAddress("rtotm", rtotm, &b_rtotm);
   fChain->SetBranchAddress("amomm", amomm, &b_amomm);
   fChain->SetBranchAddress("nsube", &nsube, &b_nsube);
   fChain->SetBranchAddress("ndcy", &ndcy, &b_ndcy);
   fChain->SetBranchAddress("ngate", &ngate, &b_ngate);
   fChain->SetBranchAddress("nbye", &nbye, &b_nbye);
   fChain->SetBranchAddress("probms", probms, &b_probms);
   fChain->SetBranchAddress("prmslg", prmslg, &b_prmslg);
   fChain->SetBranchAddress("date", date, &b_date);
   fChain->SetBranchAddress("time", time, &b_time);
   fChain->SetBranchAddress("elpsday", &elpsday, &b_elpsday);
   fChain->SetBranchAddress("numpo", numpo, &b_numpo);
   fChain->SetBranchAddress("apos", apos, &b_apos);
   fChain->SetBranchAddress("adir", adir, &b_adir);
   fChain->SetBranchAddress("aang", &aang, &b_aang);
   fChain->SetBranchAddress("agood", &agood, &b_agood);
   fChain->SetBranchAddress("wgain", &wgain, &b_wgain);
   fChain->SetBranchAddress("nbad", &nbad, &b_nbad);
   fChain->SetBranchAddress("nbada", &nbada, &b_nbada);
   fChain->SetBranchAddress("msdir", msdir, &b_msdir);
   fChain->SetBranchAddress("amomp", amomp, &b_amomp);
   fChain->SetBranchAddress("ange", ange, &b_ange);
   fChain->SetBranchAddress("angm", angm, &b_angm);
   fChain->SetBranchAddress("angp", angp, &b_angp);
   fChain->SetBranchAddress("ntot", ntot, &b_ntot);
   fChain->SetBranchAddress("probth", probth, &b_probth);
   fChain->SetBranchAddress("probpt", probpt, &b_probpt);
   fChain->SetBranchAddress("pi0like", pi0like, &b_pi0like);
   fChain->SetBranchAddress("pi0_e", pi0_e, &b_pi0_e);
   fChain->SetBranchAddress("pi0_dir", pi0_dir, &b_pi0_dir);
   fChain->SetBranchAddress("pi0mass", pi0mass, &b_pi0mass);
   fChain->SetBranchAddress("evisold", &evisold, &b_evisold);
   fChain->SetBranchAddress("evisoldxe", &evisoldxe, &b_evisoldxe);
   fChain->SetBranchAddress("evisnew", &evisnew, &b_evisnew);
   fChain->SetBranchAddress("nmue", &nmue, &b_nmue);
   fChain->SetBranchAddress("etype", etype, &b_etype);
   fChain->SetBranchAddress("etime", etime, &b_etime);
   fChain->SetBranchAddress("epos", epos, &b_epos);
   fChain->SetBranchAddress("edir", edir, &b_edir);
   fChain->SetBranchAddress("egood", egood, &b_egood);
   fChain->SetBranchAddress("ehit", ehit, &b_ehit);
   fChain->SetBranchAddress("mueprob", mueprob, &b_mueprob);
   fChain->SetBranchAddress("nmue_sel", &nmue_sel, &b_nmue_sel);
   fChain->SetBranchAddress("Rnring", &Rnring, &b_Rnring);
   fChain->SetBranchAddress("Rdir", Rdir, &b_Rdir);
   fChain->SetBranchAddress("Rang", Rang, &b_Rang);
   fChain->SetBranchAddress("Riring", &Riring, &b_Riring);
   fChain->SetBranchAddress("Rtwout", Rtwout, &b_Rtwout);
   fChain->SetBranchAddress("Rtwith", Rtwith, &b_Rtwith);
   fChain->SetBranchAddress("Alwout", &Alwout, &b_Alwout);
   fChain->SetBranchAddress("Alwith", &Alwith, &b_Alwith);
   fChain->SetBranchAddress("Qsmi", &Qsmi, &b_Qsmi);
   fChain->SetBranchAddress("Qsmo", &Qsmo, &b_Qsmo);
   fChain->SetBranchAddress("Qexi", &Qexi, &b_Qexi);
   fChain->SetBranchAddress("Qexo", &Qexo, &b_Qexo);
   fChain->SetBranchAddress("Pe5d", &Pe5d, &b_Pe5d);
   fChain->SetBranchAddress("En5d", &En5d, &b_En5d);
   fChain->SetBranchAddress("Eh5d", &Eh5d, &b_Eh5d);
   fChain->SetBranchAddress("Pe5do", &Pe5do, &b_Pe5do);
   fChain->SetBranchAddress("En5do", &En5do, &b_En5do);
   fChain->SetBranchAddress("Eh5do", &Eh5do, &b_Eh5do);
   fChain->SetBranchAddress("Rtadd", &Rtadd, &b_Rtadd);
   fChain->SetBranchAddress("Pdgeta", &Pdgeta, &b_Pdgeta);
   fChain->SetBranchAddress("Pd5d", &Pd5d, &b_Pd5d);
   fChain->SetBranchAddress("Pdthre", &Pdthre, &b_Pdthre);
   fChain->SetBranchAddress("Pd5do", &Pd5do, &b_Pd5do);
   fChain->SetBranchAddress("Delpd", &Delpd, &b_Delpd);
   fChain->SetBranchAddress("Ropena", Ropena, &b_Ropena);
   fChain->SetBranchAddress("Maxth", &Maxth, &b_Maxth);
   fChain->SetBranchAddress("Pkang", &Pkang, &b_Pkang);
   fChain->SetBranchAddress("Qrfct", &Qrfct, &b_Qrfct);
   fChain->SetBranchAddress("Pdfct", &Pdfct, &b_Pdfct);
   fChain->SetBranchAddress("Pkfct", &Pkfct, &b_Pkfct);
   fChain->SetBranchAddress("Agfct", &Agfct, &b_Agfct);
   fChain->SetBranchAddress("Dlfct", &Dlfct, &b_Dlfct);
   fChain->SetBranchAddress("Iflag", &Iflag, &b_Iflag);
   fChain->SetBranchAddress("Pmfct", &Pmfct, &b_Pmfct);
   fChain->SetBranchAddress("Imfct", &Imfct, &b_Imfct);
   fChain->SetBranchAddress("Rilike", &Rilike, &b_Rilike);
   fChain->SetBranchAddress("ri_ver", &ri_ver, &b_ri_ver);
   fChain->SetBranchAddress("ri_pid", &ri_pid, &b_ri_pid);
   fChain->SetBranchAddress("ri_nring", &ri_nring, &b_ri_nring);
   fChain->SetBranchAddress("ri_flag", ri_flag, &b_ri_flag);
   fChain->SetBranchAddress("ri_dlfct", ri_dlfct, &b_ri_dlfct);
   fChain->SetBranchAddress("ri_pdfct", ri_pdfct, &b_ri_pdfct);
   fChain->SetBranchAddress("ri_pkfct", ri_pkfct, &b_ri_pkfct);
   fChain->SetBranchAddress("ri_vafct", ri_vafct, &b_ri_vafct);
   fChain->SetBranchAddress("ri_total", ri_total, &b_ri_total);
   fChain->SetBranchAddress("ri_dir", ri_dir, &b_ri_dir);
   fChain->SetBranchAddress("ri_imfct", ri_imfct, &b_ri_imfct);
   fChain->SetBranchAddress("ri_pmfct", ri_pmfct, &b_ri_pmfct);
   fChain->SetBranchAddress("npar", &npar, &b_npar);
   fChain->SetBranchAddress("wallv", &wallv, &b_wallv);
   fChain->SetBranchAddress("ipv", ipv, &b_ipv);
   fChain->SetBranchAddress("posv", posv, &b_posv);
   fChain->SetBranchAddress("dirv", dirv, &b_dirv);
   fChain->SetBranchAddress("pmomv", pmomv, &b_pmomv);
   fChain->SetBranchAddress("light_flag", light_flag, &b_light_flag);
   fChain->SetBranchAddress("npar2", &npar2, &b_npar2);
   fChain->SetBranchAddress("wallv2", wallv2, &b_wallv2);
   fChain->SetBranchAddress("ipv2", ipv2, &b_ipv2);
   fChain->SetBranchAddress("iorg", iorg, &b_iorg);
   fChain->SetBranchAddress("posv2", posv2, &b_posv2);
   fChain->SetBranchAddress("dirv2", dirv2, &b_dirv2);
   fChain->SetBranchAddress("pmomv2", pmomv2, &b_pmomv2);
   fChain->SetBranchAddress("numnu", &numnu, &b_numnu);
   fChain->SetBranchAddress("mode", &mode, &b_mode);
   fChain->SetBranchAddress("ipnu", ipnu, &b_ipnu);
   fChain->SetBranchAddress("pnu", pnu, &b_pnu);
   fChain->SetBranchAddress("dirnu", dirnu, &b_dirnu);
   fChain->SetBranchAddress("flxg", flxg, &b_flxg);
   fChain->SetBranchAddress("flxh01", flxh01, &b_flxh01);
   fChain->SetBranchAddress("kflux", kflux, &b_kflux);
   fChain->SetBranchAddress("bs71", bs71, &b_bs71);
   fChain->SetBranchAddress("bs74", bs74, &b_bs74);
   fChain->SetBranchAddress("flxf", flxf, &b_flxf);
   fChain->SetBranchAddress("flxh1d", flxh1d, &b_flxh1d);
   fChain->SetBranchAddress("flxb03", flxb03, &b_flxb03);
   fChain->SetBranchAddress("flxf03", flxf03, &b_flxf03);
   fChain->SetBranchAddress("flxh06", flxh06, &b_flxh06);
   fChain->SetBranchAddress("flxh11", flxh11, &b_flxh11);
   fChain->SetBranchAddress("scan", scan, &b_scan);
   fChain->SetBranchAddress("nuceff_version", &nuceff_version, &b_nuceff_version);
   fChain->SetBranchAddress("charge_exchange", &charge_exchange, &b_charge_exchange);
   fChain->SetBranchAddress("absorbed", &absorbed, &b_absorbed);
   fChain->SetBranchAddress("multipi_gen", &multipi_gen, &b_multipi_gen);
   fChain->SetBranchAddress("scattering", &scattering, &b_scattering);
   fChain->SetBranchAddress("piless_dcy", &piless_dcy, &b_piless_dcy);
   fChain->SetBranchAddress("nscndprt", &nscndprt, &b_nscndprt);
   fChain->SetBranchAddress("itrkscnd", itrkscnd, &b_itrkscnd);
   fChain->SetBranchAddress("istakscnd", istakscnd, &b_istakscnd);
   fChain->SetBranchAddress("vtxscnd", vtxscnd, &b_vtxscnd);
   fChain->SetBranchAddress("pscnd", pscnd, &b_pscnd);
   fChain->SetBranchAddress("iprtscnd", iprtscnd, &b_iprtscnd);
   fChain->SetBranchAddress("tscnd", tscnd, &b_tscnd);
   fChain->SetBranchAddress("iprntprt", iprntprt, &b_iprntprt);
   fChain->SetBranchAddress("lmecscnd", lmecscnd, &b_lmecscnd);
   fChain->SetBranchAddress("iprnttrk", iprnttrk, &b_iprnttrk);
   fChain->SetBranchAddress("iorgprt", iorgprt, &b_iorgprt);
   fChain->SetBranchAddress("pprnt", pprnt, &b_pprnt);
   fChain->SetBranchAddress("iflgscnd", iflgscnd, &b_iflgscnd);
   fChain->SetBranchAddress("pprntinit", pprntinit, &b_pprntinit);
   fChain->SetBranchAddress("vtxprnt", vtxprnt, &b_vtxprnt);
   fChain->SetBranchAddress("iprntidx", iprntidx, &b_iprntidx);
   fChain->SetBranchAddress("nchilds", nchilds, &b_nchilds);
   fChain->SetBranchAddress("ichildidx", ichildidx, &b_ichildidx);
   fChain->SetBranchAddress("Npvcscnd", &Npvcscnd, &b_Npvcscnd);
   fChain->SetBranchAddress("Nchildsvc", Nchildsvc, &b_Nchildsvc);
   fChain->SetBranchAddress("Ichildidxvc", Ichildidxvc, &b_Ichildidxvc);
   fChain->SetBranchAddress("Neutmode", &Neutmode, &b_Neutmode);
   fChain->SetBranchAddress("Npne", &Npne, &b_Npne);
   fChain->SetBranchAddress("Ipne", Ipne, &b_Ipne);
   fChain->SetBranchAddress("Abspne", Abspne, &b_Abspne);
   fChain->SetBranchAddress("Pvecne", Pvecne, &b_Pvecne);
   fChain->SetBranchAddress("Npvc", &Npvc, &b_Npvc);
   fChain->SetBranchAddress("Ipvc", Ipvc, &b_Ipvc);
   fChain->SetBranchAddress("Ichvc", Ichvc, &b_Ichvc);
   fChain->SetBranchAddress("Iorgvc", Iorgvc, &b_Iorgvc);
   fChain->SetBranchAddress("Iflvc", Iflvc, &b_Iflvc);
   fChain->SetBranchAddress("Abspvc", Abspvc, &b_Abspvc);
   fChain->SetBranchAddress("Pvc", Pvc, &b_Pvc);
   fChain->SetBranchAddress("Crsx", &Crsx, &b_Crsx);
   fChain->SetBranchAddress("Crsy", &Crsy, &b_Crsy);
   fChain->SetBranchAddress("Crsz", &Crsz, &b_Crsz);
   fChain->SetBranchAddress("Crsphi", &Crsphi, &b_Crsphi);
   fChain->SetBranchAddress("Numbndn", &Numbndn, &b_Numbndn);
   fChain->SetBranchAddress("Numbndp", &Numbndp, &b_Numbndp);
   fChain->SetBranchAddress("Numfrep", &Numfrep, &b_Numfrep);
   fChain->SetBranchAddress("Numatom", &Numatom, &b_Numatom);
   fChain->SetBranchAddress("Ibound", &Ibound, &b_Ibound);
   fChain->SetBranchAddress("Neutinpmt", &Neutinpmt, &b_Neutinpmt);
   fChain->SetBranchAddress("Nvert", &Nvert, &b_Nvert);
   fChain->SetBranchAddress("Posvert", Posvert, &b_Posvert);
   fChain->SetBranchAddress("Iflgvert", Iflgvert, &b_Iflgvert);
   fChain->SetBranchAddress("Nvcvert", &Nvcvert, &b_Nvcvert);
   fChain->SetBranchAddress("Dirvert", Dirvert, &b_Dirvert);
   fChain->SetBranchAddress("Abspvert", Abspvert, &b_Abspvert);
   fChain->SetBranchAddress("Abstpvert", Abstpvert, &b_Abstpvert);
   fChain->SetBranchAddress("Ipvert", Ipvert, &b_Ipvert);
   fChain->SetBranchAddress("Iverti", Iverti, &b_Iverti);
   fChain->SetBranchAddress("Ivertf", Ivertf, &b_Ivertf);
   fChain->SetBranchAddress("Fsiprob", &Fsiprob, &b_Fsiprob);
   fChain->SetBranchAddress("Fsivarwt", Fsivarwt, &b_Fsivarwt);
   fChain->SetBranchAddress("catpc", &catpc, &b_catpc);
   fChain->SetBranchAddress("pcst_segment", &pcst_segment, &b_pcst_segment);
   fChain->SetBranchAddress("pcst_qobserved", &pcst_qobserved, &b_pcst_qobserved);
   fChain->SetBranchAddress("pcst_qexpected", &pcst_qexpected, &b_pcst_qexpected);
   fChain->SetBranchAddress("pcst_qobserved_raw", &pcst_qobserved_raw, &b_pcst_qobserved_raw);
   fChain->SetBranchAddress("pcst_pathod", &pcst_pathod, &b_pcst_pathod);
   fChain->SetBranchAddress("pcst_nhits", &pcst_nhits, &b_pcst_nhits);
   fChain->SetBranchAddress("pcst_oldhits", &pcst_oldhits, &b_pcst_oldhits);
   fChain->SetBranchAddress("pcst_newhits", &pcst_newhits, &b_pcst_newhits);
   fChain->SetBranchAddress("pcst_newq", &pcst_newq, &b_pcst_newq);
   fChain->SetBranchAddress("pcst_oldq", &pcst_oldq, &b_pcst_oldq);
   fChain->SetBranchAddress("pcst_odpos", pcst_odpos, &b_pcst_odpos);
   fChain->SetBranchAddress("catpc_orig", &catpc_orig, &b_catpc_orig);
   fChain->SetBranchAddress("catpc_qrat_corrected", &catpc_qrat_corrected, &b_catpc_qrat_corrected);
   fChain->SetBranchAddress("pcst_qrat_correction", &pcst_qrat_correction, &b_pcst_qrat_correction);
   fChain->SetBranchAddress("trgoff", &trgoff, &b_trgoff);
   fChain->SetBranchAddress("fqntwnd", &fqntwnd, &b_fqntwnd);
   fChain->SetBranchAddress("fqtwnd_iclstr", fqtwnd_iclstr, &b_fqtwnd_iclstr);
   fChain->SetBranchAddress("fqtwnd_npeak", fqtwnd_npeak, &b_fqtwnd_npeak);
   fChain->SetBranchAddress("fqtwnd_prftt0", fqtwnd_prftt0, &b_fqtwnd_prftt0);
   fChain->SetBranchAddress("fqtwnd_prftpos", fqtwnd_prftpos, &b_fqtwnd_prftpos);
   fChain->SetBranchAddress("fqtwnd", fqtwnd, &b_fqtwnd);
   fChain->SetBranchAddress("fqtwnd_peakt0", fqtwnd_peakt0, &b_fqtwnd_peakt0);
   fChain->SetBranchAddress("fqtwnd_peakiness", fqtwnd_peakiness, &b_fqtwnd_peakiness);
   fChain->SetBranchAddress("fqnse", &fqnse, &b_fqnse);
   fChain->SetBranchAddress("fqitwnd", fqitwnd, &b_fqitwnd);
   fChain->SetBranchAddress("fqipeak", fqipeak, &b_fqipeak);
   fChain->SetBranchAddress("fqnhitpmt", fqnhitpmt, &b_fqnhitpmt);
   fChain->SetBranchAddress("fqtotq", fqtotq, &b_fqtotq);
   fChain->SetBranchAddress("fq0rtotmu", fq0rtotmu, &b_fq0rtotmu);
   fChain->SetBranchAddress("fq0rnll", fq0rnll, &b_fq0rnll);
   fChain->SetBranchAddress("fqn50", fqn50, &b_fqn50);
   fChain->SetBranchAddress("fqq50", fqq50, &b_fqq50);
   fChain->SetBranchAddress("fq1rpcflg", fq1rpcflg, &b_fq1rpcflg);
   fChain->SetBranchAddress("fq1rmom", fq1rmom, &b_fq1rmom);
   fChain->SetBranchAddress("fq1rt0", fq1rt0, &b_fq1rt0);
   fChain->SetBranchAddress("fq1rtotmu", fq1rtotmu, &b_fq1rtotmu);
   fChain->SetBranchAddress("fq1rnll", fq1rnll, &b_fq1rnll);
   fChain->SetBranchAddress("fq1rpos", fq1rpos, &b_fq1rpos);
   fChain->SetBranchAddress("fq1rdir", fq1rdir, &b_fq1rdir);
   fChain->SetBranchAddress("fq1rdconv", fq1rdconv, &b_fq1rdconv);
   fChain->SetBranchAddress("fq1reloss", fq1reloss, &b_fq1reloss);
   fChain->SetBranchAddress("fqpi0pcflg", fqpi0pcflg, &b_fqpi0pcflg);
   fChain->SetBranchAddress("fqpi0mom1", fqpi0mom1, &b_fqpi0mom1);
   fChain->SetBranchAddress("fqpi0mom2", fqpi0mom2, &b_fqpi0mom2);
   fChain->SetBranchAddress("fqpi0momtot", fqpi0momtot, &b_fqpi0momtot);
   fChain->SetBranchAddress("fqpi0dconv1", fqpi0dconv1, &b_fqpi0dconv1);
   fChain->SetBranchAddress("fqpi0dconv2", fqpi0dconv2, &b_fqpi0dconv2);
   fChain->SetBranchAddress("fqpi0t0", fqpi0t0, &b_fqpi0t0);
   fChain->SetBranchAddress("fqpi0totmu", fqpi0totmu, &b_fqpi0totmu);
   fChain->SetBranchAddress("fqpi0nll", fqpi0nll, &b_fqpi0nll);
   fChain->SetBranchAddress("fqpi0mass", fqpi0mass, &b_fqpi0mass);
   fChain->SetBranchAddress("fqpi0photangle", fqpi0photangle, &b_fqpi0photangle);
   fChain->SetBranchAddress("fqpi0pos", fqpi0pos, &b_fqpi0pos);
   fChain->SetBranchAddress("fqpi0dir1", fqpi0dir1, &b_fqpi0dir1);
   fChain->SetBranchAddress("fqpi0dir2", fqpi0dir2, &b_fqpi0dir2);
   fChain->SetBranchAddress("fqpi0dirtot", fqpi0dirtot, &b_fqpi0dirtot);
   fChain->SetBranchAddress("fqpmgpcflg", fqpmgpcflg, &b_fqpmgpcflg);
   fChain->SetBranchAddress("fqpmgmom1", fqpmgmom1, &b_fqpmgmom1);
   fChain->SetBranchAddress("fqpmgmom2", fqpmgmom2, &b_fqpmgmom2);
   fChain->SetBranchAddress("fqpmgt01", fqpmgt01, &b_fqpmgt01);
   fChain->SetBranchAddress("fqpmgt02", fqpmgt02, &b_fqpmgt02);
   fChain->SetBranchAddress("fqpmgtotmu", fqpmgtotmu, &b_fqpmgtotmu);
   fChain->SetBranchAddress("fqpmgnll", fqpmgnll, &b_fqpmgnll);
   fChain->SetBranchAddress("fqpmgpos1", fqpmgpos1, &b_fqpmgpos1);
   fChain->SetBranchAddress("fqpmgpos2", fqpmgpos2, &b_fqpmgpos2);
   fChain->SetBranchAddress("fqpmgdir1", fqpmgdir1, &b_fqpmgdir1);
   fChain->SetBranchAddress("fqpmgdir2", fqpmgdir2, &b_fqpmgdir2);
   fChain->SetBranchAddress("fqnmrfit", &fqnmrfit, &b_fqnmrfit);
   fChain->SetBranchAddress("fqmrifit", fqmrifit, &b_fqmrifit);
   fChain->SetBranchAddress("fqmrnring", fqmrnring, &b_fqmrnring);
   fChain->SetBranchAddress("fqmrpcflg", fqmrpcflg, &b_fqmrpcflg);
   fChain->SetBranchAddress("fqmrnll", fqmrnll, &b_fqmrnll);
   fChain->SetBranchAddress("fqmrtotmu", fqmrtotmu, &b_fqmrtotmu);
   fChain->SetBranchAddress("fqmrpid", fqmrpid, &b_fqmrpid);
   fChain->SetBranchAddress("fqmrmom", fqmrmom, &b_fqmrmom);
   fChain->SetBranchAddress("fqmrdconv", fqmrdconv, &b_fqmrdconv);
   fChain->SetBranchAddress("fqmreloss", fqmreloss, &b_fqmreloss);
   fChain->SetBranchAddress("fqmrt0", fqmrt0, &b_fqmrt0);
   fChain->SetBranchAddress("fqmrpos", fqmrpos, &b_fqmrpos);
   fChain->SetBranchAddress("fqmrdir", fqmrdir, &b_fqmrdir);
   fChain->SetBranchAddress("fqmsnfit", &fqmsnfit, &b_fqmsnfit);
   fChain->SetBranchAddress("fqmspcflg", fqmspcflg, &b_fqmspcflg);
   fChain->SetBranchAddress("fqmsnseg", fqmsnseg, &b_fqmsnseg);
   fChain->SetBranchAddress("fqmspid", fqmspid, &b_fqmspid);
   fChain->SetBranchAddress("fqmsifit", fqmsifit, &b_fqmsifit);
   fChain->SetBranchAddress("fqmsimer", fqmsimer, &b_fqmsimer);
   fChain->SetBranchAddress("fqmstotmu", fqmstotmu, &b_fqmstotmu);
   fChain->SetBranchAddress("fqmsnll", fqmsnll, &b_fqmsnll);
   fChain->SetBranchAddress("fqmsmom", fqmsmom, &b_fqmsmom);
   fChain->SetBranchAddress("fqmseloss", fqmseloss, &b_fqmseloss);
   fChain->SetBranchAddress("fqmst0", fqmst0, &b_fqmst0);
   fChain->SetBranchAddress("fqmspos", fqmspos, &b_fqmspos);
   fChain->SetBranchAddress("fqmsdir", fqmsdir, &b_fqmsdir);
   fChain->SetBranchAddress("prid_ang", &prid_ang, &b_prid_ang);
   fChain->SetBranchAddress("prid_len", &prid_len, &b_prid_len);
   fChain->SetBranchAddress("prid_pmom", &prid_pmom, &b_prid_pmom);
   fChain->SetBranchAddress("prid_mang", &prid_mang, &b_prid_mang);
   fChain->SetBranchAddress("prid_plike", &prid_plike, &b_prid_plike);
   fChain->SetBranchAddress("prid_mlike", &prid_mlike, &b_prid_mlike);
   fChain->SetBranchAddress("prid_nused", &prid_nused, &b_prid_nused);
   fChain->SetBranchAddress("dirtotepi", dirtotepi, &b_dirtotepi);
   fChain->SetBranchAddress("dirtotenpi", dirtotenpi, &b_dirtotenpi);
   fChain->SetBranchAddress("dirtotmue", dirtotmue, &b_dirtotmue);
   fChain->SetBranchAddress("dirsum", dirsum, &b_dirsum);
   fChain->SetBranchAddress("etot", &etot, &b_etot);
   fChain->SetBranchAddress("etotepi", &etotepi, &b_etotepi);
   fChain->SetBranchAddress("etotenpi", &etotenpi, &b_etotenpi);
   fChain->SetBranchAddress("etotmue", &etotmue, &b_etotmue);
   fChain->SetBranchAddress("oscweight", oscweight, &b_oscweight);
   fChain->SetBranchAddress("oscwgt", &oscwgt, &b_oscwgt);
   fChain->SetBranchAddress("live", &live, &b_live);
   fChain->SetBranchAddress("sacth", &sacth, &b_sacth);
   fChain->SetBranchAddress("sactg", &sactg, &b_sactg);
   fChain->SetBranchAddress("sacth1d", &sacth1d, &b_sacth1d);
   fChain->SetBranchAddress("ccqelike", &ccqelike, &b_ccqelike);
   fChain->SetBranchAddress("mulike", &mulike, &b_mulike);
   fChain->SetBranchAddress("mproton", &mproton, &b_mproton);
   fChain->SetBranchAddress("outdir", outdir, &b_outdir);
   fChain->SetBranchAddress("nused2", &nused2, &b_nused2);
   fChain->SetBranchAddress("vsum", &vsum, &b_vsum);
   fChain->SetBranchAddress("qsep", &qsep, &b_qsep);
   fChain->SetBranchAddress("qpeak", &qpeak, &b_qpeak);
   fChain->SetBranchAddress("qhigh", &qhigh, &b_qhigh);
   fChain->SetBranchAddress("qlow", &qlow, &b_qlow);
   fChain->SetBranchAddress("nzeros2", &nzeros2, &b_nzeros2);
   fChain->SetBranchAddress("moyenne2", &moyenne2, &b_moyenne2);
   fChain->SetBranchAddress("lproton", &lproton, &b_lproton);
   fChain->SetBranchAddress("qwin", &qwin, &b_qwin);
   fChain->SetBranchAddress("ent_pos", ent_pos, &b_ent_pos);
   fChain->SetBranchAddress("ent_dir", ent_dir, &b_ent_dir);
   fChain->SetBranchAddress("length", &length, &b_length);
   fChain->SetBranchAddress("tr_mom1", &tr_mom1, &b_tr_mom1);
   fChain->SetBranchAddress("A_ent_mom", &A_ent_mom, &b_A_ent_mom);
   fChain->SetBranchAddress("A_ent_pos", A_ent_pos, &b_A_ent_pos);
   fChain->SetBranchAddress("A_ent_dir", A_ent_dir, &b_A_ent_dir);
   fChain->SetBranchAddress("A_ext_mom", &A_ext_mom, &b_A_ext_mom);
   fChain->SetBranchAddress("A_ext_pos", A_ext_pos, &b_A_ext_pos);
   fChain->SetBranchAddress("A_ext_dir", A_ext_dir, &b_A_ext_dir);
   fChain->SetBranchAddress("Fit_pos", Fit_pos, &b_Fit_pos);
   fChain->SetBranchAddress("Fit_dir", Fit_dir, &b_Fit_dir);
   fChain->SetBranchAddress("Fit_len", &Fit_len, &b_Fit_len);
   fChain->SetBranchAddress("Fit_mom", &Fit_mom, &b_Fit_mom);
   fChain->SetBranchAddress("Fit_pid", &Fit_pid, &b_Fit_pid);
   fChain->SetBranchAddress("Um_ehit8m", &Um_ehit8m, &b_Um_ehit8m);
   fChain->SetBranchAddress("Um_ohit8m", &Um_ohit8m, &b_Um_ohit8m);
   fChain->SetBranchAddress("Um_qent", &Um_qent, &b_Um_qent);
   fChain->SetBranchAddress("Sh_chi1p", &Sh_chi1p, &b_Sh_chi1p);
   fChain->SetBranchAddress("Sh_delta", &Sh_delta, &b_Sh_delta);
   fChain->SetBranchAddress("Sh_mean", &Sh_mean, &b_Sh_mean);
   fChain->SetBranchAddress("Sh_meanq", &Sh_meanq, &b_Sh_meanq);
   fChain->SetBranchAddress("Sh_id", &Sh_id, &b_Sh_id);
   fChain->SetBranchAddress("Tr_stop", Tr_stop, &b_Tr_stop);
   fChain->SetBranchAddress("Tr_mom", &Tr_mom, &b_Tr_mom);
   fChain->SetBranchAddress("Tr_len", &Tr_len, &b_Tr_len);
   fChain->SetBranchAddress("Tr_len1", &Tr_len1, &b_Tr_len1);
   fChain->SetBranchAddress("Pid_flg", &Pid_flg, &b_Pid_flg);
   fChain->SetBranchAddress("Crs1", &Crs1, &b_Crs1);
   fChain->SetBranchAddress("Crs2", &Crs2, &b_Crs2);
   fChain->SetBranchAddress("iclass", &iclass, &b_iclass);
   fChain->SetBranchAddress("mu_class", &mu_class, &b_mu_class);
   fChain->SetBranchAddress("mu_dec", &mu_dec, &b_mu_dec);
   fChain->SetBranchAddress("mu_dir", mu_dir, &b_mu_dir);
   fChain->SetBranchAddress("mu_pos", mu_pos, &b_mu_pos);
   fChain->SetBranchAddress("mu_good", &mu_good, &b_mu_good);
   fChain->SetBranchAddress("history", &history, &b_history);
   fChain->SetBranchAddress("Pdst", &Pdst, &b_Pdst);
   fChain->SetBranchAddress("idoff", &idoff, &b_idoff);
   fChain->SetBranchAddress("anthit", &anthit, &b_anthit);
   fChain->SetBranchAddress("idseq", &idseq, &b_idseq);
   fChain->SetBranchAddress("tstfrac", &tstfrac, &b_tstfrac);
   fChain->SetBranchAddress("judge", &judge, &b_judge);
   fChain->SetBranchAddress("Upcrs1", &Upcrs1, &b_Upcrs1);
   fChain->SetBranchAddress("Upcrs2", &Upcrs2, &b_Upcrs2);
   fChain->SetBranchAddress("lst", &lst, &b_lst);
   fChain->SetBranchAddress("jd", &jd, &b_jd);
   fChain->SetBranchAddress("fjd", &fjd, &b_fjd);
   fChain->SetBranchAddress("alt", &alt, &b_alt);
   fChain->SetBranchAddress("azi", &azi, &b_azi);
   fChain->SetBranchAddress("ra", &ra, &b_ra);
   fChain->SetBranchAddress("dec", &dec, &b_dec);
   fChain->SetBranchAddress("glat", &glat, &b_glat);
   fChain->SetBranchAddress("glong", &glong, &b_glong);
   fChain->SetBranchAddress("t2kposc", t2kposc, &b_t2kposc);
   fChain->SetBranchAddress("evclass", &evclass, &b_evclass);
   fChain->SetBranchAddress("dt0", &dt0, &b_dt0);
   fChain->SetBranchAddress("pototin", &pototin, &b_pototin);
   fChain->SetBranchAddress("nurun", &nurun, &b_nurun);
   fChain->SetBranchAddress("good_spill_flag", &good_spill_flag, &b_good_spill_flag);
   fChain->SetBranchAddress("nspill", &nspill, &b_nspill);
   fChain->SetBranchAddress("t2knuefs", &t2knuefs, &b_t2knuefs);
   fChain->SetBranchAddress("t2knuenpi0", &t2knuenpi0, &b_t2knuenpi0);
   fChain->SetBranchAddress("t2knueflag", &t2knueflag, &b_t2knueflag);
   Notify();
}

Bool_t SKMCdataTree::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void SKMCdataTree::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t SKMCdataTree::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}




void SKMCdataTree::AddFileFlavorInt(vector<int> fileFlavor){
	fileFlavorInt = fileFlavor;
}



//Apply the likelihood cuts to separate electrons from muons
bool SKMCdataTree::IsRecoElectron(){
	//printf("%f", fq1rnll[mainEventIndex][1]);
    float lr = -1.0*fq1rnll[mainEventIndex][ELECTRON]+fq1rnll[mainEventIndex][MUON];
	return (lr > (0.2 * fq1rmom[mainEventIndex][ELECTRON]));
}


bool SKMCdataTree::IsfQPi0(){
	//printf("%f", fq1rnll[mainEventIndex][1]);
    float lr = -1.0*fqpi0nll[0]+fq1rnll[mainEventIndex][ELECTRON];
	return (lr > (175 - 0.875 * fqpi0mass[0]));
}

bool SKMCdataTree::IsfQPi0tuned(){
	//printf("%f", fq1rnll[mainEventIndex][1]);
    float lr = -1.0*fqpi0nll[0]+fq1rnll[mainEventIndex][ELECTRON];
	return (lr > (860 - 9.20 * fqpi0mass[0]));
}

//PID and variables
float SKMCdataTree::electron_muon_PID(){
    // Electrons are positive
    return fq1rnll[mainEventIndex][MUON]-fq1rnll[mainEventIndex][ELECTRON]-0.2*fq1rmom[mainEventIndex][ELECTRON];
    }
             
float SKMCdataTree::piplus_muon_PID(){
	// Pions are positive
    return fq1rnll[mainEventIndex][MUON]-fq1rnll[mainEventIndex][PION] - 0.15*fq1rmom[mainEventIndex][MUON];
  }

float SKMCdataTree::pi0_electron_PID(){
     // Pions are positive
     return fq1rnll[mainEventIndex][ELECTRON]-fqpi0nll[mainEventIndex]-175+0.875*fqpi0mass[mainEventIndex];
}
       
float SKMCdataTree::nllr_pipi_e(){
     int ipp = -1;
     int ie = -1;
     for (int ifit=0; ifit<fqnmrfit; ++ifit) {
         if (std::abs(fqmrifit[ifit]) == 20000033) {
             ipp = ifit;
         } else if (std::abs(fqmrifit[ifit]) == 10000001) {
		     ie = ifit;
		 }
		 if ((ipp >= 0) and (ie >= 0)) break;
	 }
											      
     if ((ipp < 0) or (ie < 0)) {
         throw std::runtime_error("t2ksk_eventSelections: ERROR! Couldn't find FiTQun multi-ring result. I need to run on files with all multi-ring results written out.");
	 }
	 return fqmrnll[ie] - fqmrnll[ipp];
}


float SKMCdataTree::nllr_2Rother_ee(){
	int ipp = -1;
    int i2Rbest = -1;
    float nllBest = 1000000.;
				     
    for (int ifit=0; ifit<fqnmrfit; ++ifit) {
       if (std::abs(fqmrifit[ifit]) == 20000011) {
           ipp = ifit;
       } else if (std::abs(std::abs(fqmrifit[ifit]) - (2*10000000)) < 4 * std::abs(std::pow(10, 1))) { // We want the best 2-ring fit which is not ee 
           if (fqmrnll[ifit] < nllBest){
               nllBest = fqmrnll[ifit];
               i2Rbest = ifit;
           }
       }
	}
    if (ipp < 0) {
        throw std::runtime_error("t2ksk_eventSelections: ERROR! Couldn't find FiTQun ee multi-ring result. I need to run on files with all multi-ring results written out.");
    }
    if (i2Rbest < 0){
       throw std::runtime_error("t2ksk_eventSelections: ERROR! Couldn't find best non-ee FiTQun multi-ring result. I need to run on files with all multi-ring results written out.");
    }
    return fqmrnll[ipp] - fqmrnll[i2Rbest];
}


float SKMCdataTree::nllr_pi0_ee(){
	int ipp = -1;
    float nllBest = 1000000.;
				     
    for (int ifit=0; ifit<fqnmrfit; ++ifit) {
       if (std::abs(fqmrifit[ifit]) == 30000111) {
           ipp = ifit;
       }
       
       
       }
    if (ipp < 0) {
        throw std::runtime_error("t2ksk_eventSelections: ERROR! Couldn't find FiTQun ee multi-ring result. I need to run on files with all multi-ring results written out.");
    }

    return -1*(fqmrnll[ipp] - fqpi0nll[0]);
}

float SKMCdataTree::ifitPi0mom(){
    float pi0mom = -1;
    for (int ifit=0; ifit<fqnmrfit; ++ifit) {
       if (std::abs(fqmrifit[ifit]) == 20000011) {
           pi0mom = sqrt(
                        (fqmrdir[ifit][0][0]*fqmrmom[ifit][0] + fqmrdir[ifit][1][0]*fqmrmom[ifit][1]) * (fqmrdir[ifit][0][0]*fqmrmom[ifit][0] + fqmrdir[ifit][1][0]*fqmrmom[ifit][1]) + 
                        (fqmrdir[ifit][0][1]*fqmrmom[ifit][0] + fqmrdir[ifit][1][1]*fqmrmom[ifit][1]) * (fqmrdir[ifit][0][1]*fqmrmom[ifit][0] + fqmrdir[ifit][1][1]*fqmrmom[ifit][1]) + 
                        (fqmrdir[ifit][0][2]*fqmrmom[ifit][0] + fqmrdir[ifit][1][2]*fqmrmom[ifit][1]) * (fqmrdir[ifit][0][2]*fqmrmom[ifit][0] + fqmrdir[ifit][1][2]*fqmrmom[ifit][1]) 
                        );    
       // std::cout<< fqpi0momtot[0] << " " << pi0mom << std::endl;
       }
    }
  return pi0mom;

}





float SKMCdataTree::nllr_2Rother_pipi(){
	int ipp = -1;
    int i2Rbest = -1;
    float nllBest = 1000000.;
				     
    for (int ifit=0; ifit<fqnmrfit; ++ifit) {
       if (std::abs(fqmrifit[ifit]) == 20000033) {
           ipp = ifit;
       } else if (std::abs(std::abs(fqmrifit[ifit]) - (2*10000000)) < 4 * std::abs(std::pow(10, 1))) { // We want the best 2-ring fit which is not pipi
           if (fqmrnll[ifit] < nllBest){
               nllBest = fqmrnll[ifit];
               i2Rbest = ifit;
           }
       }
	}
    if (ipp < 0) {
        throw std::runtime_error("t2ksk_eventSelections: ERROR! Couldn't find FiTQun pipi multi-ring result. I need to run on files with all multi-ring results written out.");
    }
    if (i2Rbest < 0){
       throw std::runtime_error("t2ksk_eventSelections: ERROR! Couldn't find best non-pipi FiTQun multi-ring result. I need to run on files with all multi-ring results written out.");
    }
    return fqmrnll[ipp] - fqmrnll[i2Rbest];
}


float SKMCdataTree::sum_eloss_pipi(){
    int ipp = -1;
		    
    for (int ifit=0; ifit<fqnmrfit; ++ifit) {
        if (std::abs(fqmrifit[ifit]) == 20000033) {
	        ipp = ifit;
	        break;
	    }
	}
	if (ipp < 0) {
	    throw std::runtime_error("t2ksk_eventSelections: ERROR! Couldn't find FiTQun multi-ring result. I need to run on files with all multi-ring results written out.");
	}
	return fqmreloss[ipp][0] + fqmreloss[ipp][1];
}





float SKMCdataTree::TwoRingpi0InvMass(){
	if (nring !=2){
		return -1.;
	}
	else{
		float stdpi0mass = TMath::Sqrt(2.*amome[0]*amome[1]*(1.-dir[0][0]*dir[1][0]-dir[0][1]*dir[1][1]-dir[0][2]*dir[1][2]));
		return stdpi0mass;
	}

}


  // CCQE Erec
  //   // Lifted from minituple code
float SKMCdataTree::ComputeErec(float LeptonP, fq_particle i_particle, float cosBeam){

	int flag = -1;
    if (i_particle == ELECTRON) flag = 1;
    else if (i_particle == MUON) flag = 0;
    else throw std::runtime_error("Cannot compute Erec if particle isn't an electron or a muon");
  
   static const double Vnuc  = 27.0        ; // MeV 
   static const double mn    = 939.565346  ; // MeV
   static const double mp    = 938.272013  ; // MeV
                             
   static const double me    = 0.510998   ; // MeV
   static const double mm    = 105.65836  ; // MeV
  
   double mass ;
   if( flag == 1 ) mass = me ;
   else            mass = mm ;
                                                      
   float E  = 0.;
   float LeptonE = sqrt( mass*mass + LeptonP*LeptonP );
                                                                             
                                                                                
   E  = ( mn - Vnuc)*LeptonE - mass*mass/2. ;
   E +=   mn*Vnuc  - Vnuc*Vnuc/2.;
   E += ( mp*mp - mn*mn)/2.;
                                                                                            
   E /= ( mn - Vnuc - LeptonE + LeptonP*cosBeam );
                                                                                                      
   // returns value in MeV 
   return E;
}


float SKMCdataTree::ComputeCosBeam( int nsubevent, fq_particle i_particle)
{

	float dirx = fq1rdir[nsubevent][i_particle][0];
    float diry = fq1rdir[nsubevent][i_particle][1];
    float dirz = fq1rdir[nsubevent][i_particle][2];

    return  dirx*beamdir[0] + diry*beamdir[1] + dirz*beamdir[2] ;
}


float SKMCdataTree::ComputeTrueCosBeam()
{
	//neutrino direction = 0
	float dirx = dirnu[0][0];
    float diry = dirnu[1][0] ;
    float dirz = dirnu[2][0];
	//Mayn= need to get indexes correct, check ipnu to see what the particle is.:

    return  dirx*beamdir[0] + diry*beamdir[1] + dirz*beamdir[2] ;
}




//Selections

bool SKMCdataTree::IsSingleRingMuLike(){	
  bool kPass = false ;
  if (this->IsFCFV()){ 
   if( fqmrnring[0] == 1 && (! this->IsRecoElectron()) && (fqnse == 2 || fqnse == 1) ) {// single-ring mu-like 
     if( fq1rmom[0][2] > 200. ) {// momentum threshold
       if ( fq1rnll[0][2] - fq1rnll[0][3] < 0.15 * fq1rmom[0][2] ) {
			kPass = true;
	   }
	 }
   }
  }
  return kPass;
}


bool SKMCdataTree::IsSingleRingELike(){
  bool kPass = false ;
   if( fqmrnring[0] == 1 && this->IsRecoElectron() ) { // single-ring e-like
     if( fqnse==1 && fq1rmom[0][1] > 100.0 ) {// no decay electrons (fqnmue, fqevis)
       if( fq1rnll[0][1] - fqpi0nll[0]  < 175. - 0.875 * fqpi0mass[0] ) { // pi0 rejection
		   float EcosBeam = ComputeCosBeam(mainEventIndex, ELECTRON);
		   float Erec = ComputeErec(fq1rmom[mainEventIndex][ELECTRON], ELECTRON, EcosBeam);
		   if (Erec < 1250.){
			   kPass = true ;

	   }
      }
     }
    }
  
   return kPass;
}




bool SKMCdataTree::IsFCFV(){
	if (nhitac < 16 and evclass == 1 and fq1rmom[mainEventIndex][1] > 30) {
			if (this->IsRecoElectron()){
				dwall_lim = 80.;
				towall_lim = 170.;
			}	
			else{
				dwall_lim = 50.;
				towall_lim=270.;
			}
			if (this->GetRecoDWall() > dwall_lim and this->GetRecoToWall() > towall_lim){
				return true;
			}
			else{
				return false;
			}
		}
		else{
			return false;
		}
	
}


// Loose cuts for cut tuning
bool SKMCdataTree::CanReco(){
	if (nhitac < 16 and ndcy == 0 and evis > 30.) {
		return true;
	} else {
		return false;
	}
}


//Calculate and return the reconstructed dWall
//
float SKMCdataTree::ComputeDWall(float x, float y, float z){
   //cout << "x, y, z " << x << y << z << "\n";                                                                                                                                                            
	
	 
     float Rmax = 1690.;
     float Zmax = 1810.;
     float rr   = sqrt(x*x + y*y);
     float absz = TMath::Abs(z);
     //check if vertex is outside tank                                                                                                                                                                       
    float signflg = 1.;
    if (absz>Zmax) signflg = -1.;
    if (rr>Rmax)   signflg = -1.;  //find min distance to wall                                                                                                                                              
    float distz = TMath::Abs(Zmax-absz);
    float distr = TMath::Abs(Rmax-rr);
    float dwall = signflg*fmin(distz,distr);                                                                                                                                                              
    if(distz <= distr){ float dwall = signflg*distz;
    }
    else {float dwall = signflg*distr;
}
//  cout << "dwall = " << dwall << ", x = " << x << "\n";                                                                                                                                               
return dwall;
}

float SKMCdataTree::ComputeToWall(float x, float y, float z, float dx, float dy, float dz){
		
    Double_t const R(1690);
    Double_t l_b(100000.0), H;
    Double_t l_t(100000.0);
    Double_t A, B, C, RAD;

    if(dx!=0 || dy!=0){
        A=(dx*dx+dy*dy);B=2*(x*dx+y*dy);C=(x*x+y*y-R*R);RAD=(B*B)-(4*A*C);l_b=((-1*B)+sqrt(RAD))/(2*A);
    }
    if (dz==0){
        return l_b;
    }
    else if(dz>0){
        H=1810;
    }
    else if(dz<0){
        H=-1810;
    }
    l_t=(H - z)/dz;
    return  (l_t > l_b ? l_b:l_t);
}



//Calculate and return the reconstructed dWall
//
float SKMCdataTree::GetRecoDWall(){
   //cout << "x, y, z " << x << y << z << "\n";                                                                                                                                                            

  	float x = fq1rpos[mainEventIndex][1][0];
   	float y = fq1rpos[mainEventIndex][1][1];
   	float z = fq1rpos[mainEventIndex][1][2];
	
	 
     float Rmax = 1690.;
     float Zmax = 1810.;
     float rr   = sqrt(x*x + y*y);
     float absz = TMath::Abs(z);
     //check if vertex is outside tank                                                                                                                                                                       
    float signflg = 1.;
    if (absz>Zmax) signflg = -1.;
    if (rr>Rmax)   signflg = -1.;  //find min distance to wall                                                                                                                                              
    float distz = TMath::Abs(Zmax-absz);
    float distr = TMath::Abs(Rmax-rr);
    float dwall = signflg*fmin(distz,distr);                                                                                                                                                              
    if(distz <= distr){ float dwall = signflg*distz;
    }
    else {float dwall = signflg*distr;
}
//  cout << "dwall = " << dwall << ", x = " << x << "\n";                                                                                                                                               
return dwall;
}

//Calculate and return the reconstructed dWall for 2 ring
//
float SKMCdataTree::GetRecoDWall_pi0(){
   //cout << "x, y, z " << x << y << z << "\n";                                                                                                                                                            

  /*	float x = fqpi0pos[0][0];
   	float y = fqpi0pos[0][1];
   	float z = fqpi0pos[0][2];
    */
    int ipp = -1;
    for (int ifit=0; ifit<fqnmrfit; ++ifit) {
      if (std::abs(fqmrifit[ifit]) == 20000011) {
          ipp = ifit;   
      }
    }
     if (ipp < 0) {
        throw std::runtime_error("GetRecoDwall_pi0: ERROR! Couldn't find FiTQun ee multi-ring result. I need to run on files with all multi-ring results written out.");
    }
   
    int hiq_ring = -1;
    if (fqmrmom[ipp][0]>fqmrmom[ipp][1]){
      hiq_ring = 0;
    }
    else {
      hiq_ring = 1;
    }
    
  	float x = fqmrpos[ipp][hiq_ring][0];
   	float y = fqmrpos[ipp][hiq_ring][1];
   	float z = fqmrpos[ipp][hiq_ring][2];

	 
    float Rmax = 1690.;
    float Zmax = 1810.;
    float rr   = sqrt(x*x + y*y);
    float absz = TMath::Abs(z);
    //check if vertex is outside tank                                                                                                                                                                       
    float signflg = 1.;
    if (absz>Zmax) signflg = -1.;
    if (rr>Rmax)   signflg = -1.;  //find min distance to wall                                                                                                                                              
    float distz = TMath::Abs(Zmax-absz);
    float distr = TMath::Abs(Rmax-rr);
    float dwall = signflg*fmin(distz,distr);                                                                                                                                                              
    if(distz <= distr){ float dwall = signflg*distz;
    }
    else {float dwall = signflg*distr;
}
//  cout << "dwall = " << dwall << ", x = " << x << "\n";                                                                                                                                               
return dwall;

}
//Calculate and return the reconstructed toWall for 2 ring
float SKMCdataTree::GetRecoToWall_pi0(){
	
    int ipp = -1;
    for (int ifit=0; ifit<fqnmrfit; ++ifit) {
      if (std::abs(fqmrifit[ifit]) == 20000011) {
          ipp = ifit;   
      }
    }
     if (ipp < 0) {
        throw std::runtime_error("GetRecoDwall_pi0: ERROR! Couldn't find FiTQun ee multi-ring result. I need to run on files with all multi-ring results written out.");
    }	
    
    
    int hiq_ring = -1;
    if (fqmrmom[ipp][0]>fqmrmom[ipp][1]){
      hiq_ring = 0;
    }
    else {
      hiq_ring = 1;
    }
    
  	float x = fqmrpos[ipp][hiq_ring][0];
   	float y = fqmrpos[ipp][hiq_ring][1];
   	float z = fqmrpos[ipp][hiq_ring][2];
  
	  float dx = fqmrdir[ipp][hiq_ring][0];
	  float dy = fqmrdir[ipp][hiq_ring][1];
	  float dz = fqmrdir[ipp][hiq_ring][2];
    
    Double_t const R(1690);
    Double_t l_b(100000.0), H;
    Double_t l_t(100000.0);
    Double_t A, B, C, RAD;

    if(dx!=0 || dy!=0){
        A=(dx*dx+dy*dy);B=2*(x*dx+y*dy);C=(x*x+y*y-R*R);RAD=(B*B)-(4*A*C);l_b=((-1*B)+sqrt(RAD))/(2*A);
    }
    if (dz==0){
        return l_b;
    }
    else if(dz>0){
        H=1810;
    }
    else if(dz<0){
        H=-1810;
    }
    l_t=(H - z)/dz;
    return  (l_t > l_b ? l_b:l_t);
}
//Calculate and return the reconstructed toWall
float SKMCdataTree::GetRecoToWall(){
		
	float x = fq1rpos[mainEventIndex][1][0];
   	float y = fq1rpos[mainEventIndex][1][1];
   	float z = fq1rpos[mainEventIndex][1][2];
	float dx = fq1rdir[mainEventIndex][1][0];
	float dy = fq1rdir[mainEventIndex][1][1];
	float dz = fq1rdir[mainEventIndex][1][2];
    Double_t const R(1690);
    Double_t l_b(100000.0), H;
    Double_t l_t(100000.0);
    Double_t A, B, C, RAD;

    if(dx!=0 || dy!=0){
        A=(dx*dx+dy*dy);B=2*(x*dx+y*dy);C=(x*x+y*y-R*R);RAD=(B*B)-(4*A*C);l_b=((-1*B)+sqrt(RAD))/(2*A);
    }
    if (dz==0){
        return l_b;
    }
    else if(dz>0){
        H=1810;
    }
    else if(dz<0){
        H=-1810;
    }
    l_t=(H - z)/dz;
    return  (l_t > l_b ? l_b:l_t);
}


//Ring counting parameter(s)

//For NCpi0 selection
float SKMCdataTree::rc_par(){
    int i_2R_best = -1;
    float nll_2R_best = 1000000;

    for (int ifit=0; ifit<fqnmrfit; ++ifit) {

       // Two ring
        if (std::abs(std::abs(fqmrifit[ifit]) - (2*10000000)) < 4 * std::abs(std::pow(10, 1))){
            if (fqmrnll[ifit] < nll_2R_best){
                i_2R_best = ifit;
                nll_2R_best = fqmrnll[ifit];
                }
         }
    }
//    if (i_1R_best < 0 or i_2R_best < 0) {
    if (i_2R_best < 0) {
        throw std::runtime_error("t2ksk_eventSelections: ERROR! Couldn't find FiTQun multi-ring result. I need to run on files with all multi-ring results written out.");
    }
                                                               
    float mommin2R = std::min(fqmrmom[i_2R_best][0], fqmrmom[i_2R_best][1]);
    float cthreshold = std::max(150. -0.6*mommin2R, 0.);
    float deltalnL = std::min(fq1rnll[0][1], fq1rnll[0][2]) - fqmrnll[i_2R_best];
    float ringctpar = 50*std::sqrt(std::abs(deltalnL - cthreshold));
    if (ringctpar > 1000.) ringctpar = 999.;
    if (deltalnL - cthreshold < 0.)  ringctpar *= -1.;
  
    return ringctpar;
	
}

void SKMCdataTree::DrawHist2D(TH2F* histo, std::string mode, std::string x_param, std::string y_param,  std::string horn_current, std::string osc_sample, std::string figs_subdir){
	auto c_hist = new TCanvas();
	histo->SetTitle(Form("%s %s vs %s %s %s", mode.c_str(), y_param.c_str(), x_param.c_str(), horn_current.c_str(), osc_sample.c_str()));
	histo->GetXaxis()->SetTitle(Form("%s", x_param.c_str()));
	histo->GetYaxis()->SetTitle(Form("%s", y_param.c_str()));
	histo->Draw("colz");
	c_hist->SaveAs(Form("/vols/t2k/users/dmartin/NCpi0/code/selection/figs/%s/%s_%s_vs_%s_%s_%s.png", figs_subdir.c_str(), mode.c_str(), y_param.c_str(), x_param.c_str(), horn_current.c_str(), osc_sample.c_str()) );
}

void SKMCdataTree::DrawHist(TH1D* histo, std::string mode, std::string param,  std::string horn_current, std::string osc_sample, std::string figs_subdir, std::string settitle){
	auto c_hist = new TCanvas();
	if (settitle=="default"){
	histo->SetTitle(Form("%s %s %s %s", mode.c_str(), param.c_str(), horn_current.c_str(), osc_sample.c_str()));
	}
	else {
	histo->SetTitle(Form("%s", settitle.c_str()));
	}
	histo->GetXaxis()->SetTitle(Form("%s", param.c_str()));
	histo->Draw("hist");
	c_hist->SaveAs(Form("/vols/t2k/users/dmartin/NCpi0/code/selection/figs/%s/%s_%s_%s_%s.png", figs_subdir.c_str(), mode.c_str(), param.c_str(), horn_current.c_str(), osc_sample.c_str()) );
}

void SKMCdataTree::FormatHist2D(TH2F* h){
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
	

}

void SKMCdataTree::FormatHist(TH1D* h, int linecolor, int linestyle){
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

//////////////// prob3++  /////////////////////////////////


void SKMCdataTree::ProbSK(){
/// Oscillation Parameters from tn319
  kSquared  = true;   // using sin^2(x) variables?

  kNuBar  =  1;
  DM2     =  2.509e-3;
  Theta23 =  0.550   ;
  Theta13 =  0.0219  ;
  dm2     =  7.53e-5;
  Theta12 =  0.304;
  dcp   =  -1.728;

// Density and path length
  BasePath = 295.0;
  Density = 2.60;

  std::cout << "Using          " << std::endl
            << "      DM2      " <<  DM2      << std::endl
            << "      Theta23  " <<  Theta23  << std::endl
            << "      Theta13  " <<  Theta13  << std::endl
            << "      dm2      " <<  dm2      << std::endl
			<< "      Theta12  " <<  Theta12  << std::endl
            << "      dcp      " <<  dcp  << std::endl
            << "      BasePAth      " <<  BasePath  << std::endl
            << "      Density      " <<  Density  << std::endl;


  bNu = new BargerPropagator( );
  bNu->UseMassEigenstates( false );

}	

void SKMCdataTree::SetAntiNeutrino(bool isAntiNeutrino)
{
	    if (isAntiNeutrino) kNuBar = -1;
		    else kNuBar = 1;
}

double SKMCdataTree::GetOscProb(int initialSpecies, int finalSpecies, float energy)
{
    
    bNu->SetMNS( Theta12,  Theta13, Theta23, dm2, DM2, dcp , energy, kSquared, kNuBar ); 
    bNu->propagateLinear( 1*kNuBar, BasePath, Density );
	
	double total_prob = 0.0;
    for(int m=1; m<=3; m++) total_prob += bNu->GetProb(initialSpecies, m); // Normalize the Probabilities //
    if ( total_prob >1.00001 || total_prob<0.99998 ) {std::cerr << "ERROR Prob" << std::endl;}// abort();}

    // Get Muon appearance probability
	double prob = bNu->GetProb(initialSpecies,finalSpecies);     
	
	return prob;
}


double SKMCdataTree::GetProb(int initialSpecies, int finalSpecies)
{
	
	double total_prob = 0.0;
    for(int m=1; m<=3; m++) total_prob += bNu->GetProb(initialSpecies, m); // Normalize the Probabilities //
    if ( total_prob >1.00001 || total_prob<0.99998 ) {std::cerr << "ERROR Prob" << std::endl;}// abort();}

    // Get Muon appearance probability
	double prob = bNu->GetProb(initialSpecies,finalSpecies);     
	
	return prob;
}

double SKMCdataTree::GetProbNuMuNuE(float energy)
{
    SetAntiNeutrino(0);
    bNu->SetMNS( Theta12,  Theta13, Theta23, dm2, DM2, dcp , energy, kSquared, kNuBar ); 
    bNu->propagateLinear( 1*kNuBar, BasePath, Density );

    return bNu->GetProb(2,1);
}

double SKMCdataTree::GetProbNuMuNuMu(float energy)
{
	    SetAntiNeutrino(0);
	    bNu->SetMNS( Theta12,  Theta13, Theta23, dm2, DM2, dcp , energy, kSquared, kNuBar ); 
	    bNu->propagateLinear( 1*kNuBar, BasePath, Density );

	    return GetProb(2,2);
}

double SKMCdataTree::GetProbNuMuBarNuMuBar(float energy)
{
	    SetAntiNeutrino(1);
	    bNu->SetMNS( Theta12,  Theta13, Theta23, dm2, DM2, dcp , energy, kSquared, kNuBar ); 
	    bNu->propagateLinear( 1*kNuBar, BasePath, Density );

	    return GetProb(2,2);
}


double SKMCdataTree::GetProbNuMuBarNuEBar(float energy)
{
	    SetAntiNeutrino(1);
	    bNu->SetMNS( Theta12,  Theta13, Theta23, dm2, DM2, dcp , energy, kSquared, kNuBar ); 
	    bNu->propagateLinear( 1*kNuBar, BasePath, Density );

	    return GetProb(2,1);
}

double SKMCdataTree::GetProbNuENuE(float energy)
{
	    SetAntiNeutrino(0);
	    bNu->SetMNS( Theta12,  Theta13, Theta23, dm2, DM2, dcp , energy, kSquared, kNuBar ); 
	    bNu->propagateLinear( 1*kNuBar, BasePath, Density );

	    return GetProb(1,1);
}

double SKMCdataTree::GetProbNuEBarNuEBar(float energy)
{
	SetAntiNeutrino(1);
	bNu->SetMNS( Theta12,  Theta13, Theta23, dm2, DM2, dcp , energy, kSquared, kNuBar ); 
	bNu->propagateLinear( 1*kNuBar, BasePath, Density );

	return GetProb(1,1);
}

#endif // #ifdef SKMCdataTree_cxx
