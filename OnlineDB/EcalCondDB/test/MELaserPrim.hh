#ifndef MELaserPrim_hh
#define MELaserPrim_hh

#include <iostream>
#include <fstream>
#include <vector>
#include <map>

#include <TROOT.h>
#include <TChain.h>
#include <TH2I.h>
#include <TH2F.h>
#include <TFile.h>
#include <TString.h>

class MELaserPrim 
{

public:

  // enums
  enum apdpn_array_num    { iAPD, iAPDoPN, iAPDoPNA, iAPDoPNB, iSizeArray_apdpn }; 
  enum apdpn_var_num      { iMean, iRMS, iWbin, iSumPk, iNevt, iSize_apdpn }; 
  enum apdpn_extraVar_num { iShapeCor, iSizeExtra_apdpn };
  enum ab_var_num         { iAlpha, iBeta, iWidth, iChi2, iSize_ab };
  enum mtq_var_num        { iPeak, iSigma, iFit, iAmpl, iTrise, iFwhm, iFw20, iFw80, iSize_mtq };
  enum laser_color_num    { iBlue, iGreen, iRed, iIRed, iLed1, iLed2, iSizeColor };  
  enum vfe_gain_num       { iVfeGain12=1, iVfeGain6, iVfeGain1, iSizeVfeGain };  
  enum pn_gain_num        { iPnGain1, iPnGain16, iSizePnGain };  
  enum lmf_laser_num      { iLmfLaserRun,
                            iLmfLaserConfig,  
			    iLmfLaserPulse,  
			    iLmfLaserPrim,   
			    iLmfLaserPnPrim,
                            iSizeLmfLaser   }; 

  // constructor
  MELaserPrim( int dcc, int side, int color, int run, int ts, const char* inpath, const char* outpath ); 

  // destructor
  virtual ~MELaserPrim();

  // functions
  void init();
  void bookHistograms();
  void fillHistograms();
  void writeHistograms();
  void print(std::ostream& o );

  // name of tables
  static TString lmfLaserName( int table, int color=iBlue );

  // fill histograms from a user application (e.g. DB )
  bool setInt( const char*, int ix, int iy,   int ival );
  bool setVal( const char*, int ix, int iy, float  val );

  // fill tree variables from a user application (e.g. DB )
  bool setInt( const char* tname, const char* vname, int ival );
  bool setVal( const char* tname, const char* vname, float  val );

  bool fill( const char* tname );

  // access
  Int_t    getInt( const char*, int ix, int iy );
  Float_t  getVal( const char*, int ix, int iy );

private:

  // monitoring region (dcc+side), wavelength, run number and timestamp
  int   _dcc;
  int  _side;
  int _color;
  int   _run;
  int    _ts;

  // useful 
  int  _ecal_region;
  int    _sm;
  std::map< int, std::pair<int, int> > _pn;  // association module -> pair of PN diodes

  TString _detStr;
  TString _sectorStr;
  TString _regionStr;
  TString _primStr;
  TString _pnPrimStr;
  TString _pulseStr;

  // root files
  TFile* apdpn_file;
  TFile*    ab_file;
  TFile*    pn_file;
  TFile*   mtq_file;
  TFile*   out_file;

  // root trees
  TTree* apdpn_tree;
  TTree*    ab_tree;
  TTree*    pn_tree;
  TTree*   mtq_tree;
  
  // paths to root trees
  TString  _inpath;
  TString _outpath;

  // index limits (depends on dcc)
  int nx;
  int ixmin;
  int ixmax;
  int ny;
  int iymin;
  int iymax;

  // 2D-histograms
  std::map< TString, TH2* > i_h;    // integer quantities
  std::map< TString, TH2* > f_h;    // floating point quantities

  // trees
  std::map< TString, TTree* >  t_t;  // map of trees
  std::map< TString, int >     i_t;  // integer values
  std::map< TString, float >   f_t;  // float values
  std::map< TString, const char* > c_t;  // string values
  
  // leaves for the APDPN ntuple
  Int_t           apdpn_dccID;
  Int_t           apdpn_towerID;
  Int_t           apdpn_channelID;
  Int_t           apdpn_moduleID;
  Double_t        apdpn_gainID;
  Int_t           apdpn_ieta;
  Int_t           apdpn_iphi;
  Int_t           apdpn_flag;
  Double_t        apdpn_ShapeCor;
  Double_t        apdpn_apdpn[iSizeArray_apdpn][iSize_apdpn];

  // leaves for the AB ntuple
  Int_t           ab_dccID;
  Int_t           ab_towerID;
  Int_t           ab_channelID;
  Int_t           ab_ieta;
  Int_t           ab_iphi;
  Int_t           ab_flag;
  Double_t        ab_ab[iSize_ab];

  // leaves for the PN ntuple
  Int_t           pn_pnID;
  Int_t           pn_moduleID;
  Double_t        pn_PN[iSize_apdpn];
  Double_t        pn_PNoPN[iSize_apdpn];
  Double_t        pn_PNoPNA[iSize_apdpn];
  Double_t        pn_PNoPNB[iSize_apdpn];

  // leaves for the MTQ ntuple
  Int_t           mtq_event;
  Int_t           mtq_laser_color;
  Int_t           mtq_status;
  Double_t        mtq_mtq[iSize_mtq];

  // List of branches for APDPN
  TBranch        *b_apdpn_dccID;   //!
  TBranch        *b_apdpn_towerID;   //!
  TBranch        *b_apdpn_channelID;   //!
  TBranch        *b_apdpn_moduleID;   //!
  TBranch        *b_apdpn_gainID;   //!
  TBranch        *b_apdpn_ieta;   //!
  TBranch        *b_apdpn_iphi;   //!
  TBranch        *b_apdpn_flag;   //!
  TBranch        *b_apdpn_ShapeCor;   //!
  TBranch        *b_apdpn_apdpn[iSizeArray_apdpn];   //!

  // List of branches for AB
  TBranch        *b_ab_dccID;   //!
  TBranch        *b_ab_towerID;   //!
  TBranch        *b_ab_channelID;   //!
  TBranch        *b_ab_ieta;   //!
  TBranch        *b_ab_iphi;   //!
  TBranch        *b_ab_flag;   //!
  TBranch        *b_ab_ab[iSize_ab];   //!

  // List of branches for PN
  TBranch        *b_pn_pnID;   //!
  TBranch        *b_pn_moduleID;   //!
  TBranch        *b_pn_PN;   //!
  TBranch        *b_pn_PNoPN;   //!
  TBranch        *b_pn_PNoPNA;   //!
  TBranch        *b_pn_PNoPNB;   //!

  // List of branches for MTQ
  TBranch        *b_mtq_event;   //!
  TBranch        *b_mtq_laser_color;   //!
  TBranch        *b_mtq_status;   //!  
  TBranch        *b_mtq_mtq[iSize_mtq]; //!

  static TString apdpn_arrayName[iSizeArray_apdpn];
  static TString apdpn_varName[iSize_apdpn];
  static TString apdpn_varUnit[iSizeArray_apdpn][iSize_apdpn];
  static TString apdpn_extraVarName[iSizeExtra_apdpn];
  static TString apdpn_extraVarUnit[iSizeExtra_apdpn];
  static TString ab_varName[iSize_ab];
  static TString mtq_varName[iSize_mtq];
  static TString mtq_varUnit[iSize_mtq];
  static TString separator;

  void setHistoStyle( TH1* );
  void refresh();
  void addBranchI( const char* t_name, const char* v_name );
  void addBranchF( const char* t_name, const char* v_name );
  void addBranchC( const char* t_name, const char* v_name );
  void bookHistoI( const char* t_name, const char* v_name );
  void bookHistoF( const char* t_name, const char* v_name );

};

#endif
