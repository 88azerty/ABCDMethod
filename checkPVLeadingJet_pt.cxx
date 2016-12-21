#include <iostream>
#include <fstream>
#include <TFile.h>
#include <TChain.h>
#include <TCanvas.h>
#include <TROOT.h>
#include <stdlib.h>
#include <TStyle.h>
#include <TH2D.h>
#include <TLegend.h>
#include <TColor.h>
#include <math.h>
#include <THnSparse.h>
#include <TChain.h>
#include <map>
#include <string>
#include <vector>
#include <TRandom3.h>
#include "THnSparse.h"
#include "TF1.h"
#include "TSystem.h"
#include "THStack.h"
#include "TCut.h"
#include <TTree.h>
#include <TTreeReader.h>

using namespace std;

int main() {
  gROOT->Reset();
  vector<string> filenames;

  ifstream list( "list.txt" , ios::in ); //read the list of ROOT files from a file
  while( list.good() ){
    string n, w;
    list >> n >> ws >> w;
    if( n.length() == 0 )             continue;
    if( n.compare( 0,1,"#" ) == 0 )   continue;
    filenames.push_back(n);
  }

  TChain *mychain = new TChain("HistFitterTree"); //create a chain with all the files
  for( unsigned int i=0; i<filenames.size(); i++){
    const char *j = filenames.at(i).c_str();
    mychain->Add( j );
    delete j;
  }

  cout<<"TChain has "<<mychain->GetEntries()<< " entries."<<endl;
  TTreeReader reader(mychain); //tree reader to process the data
  TTreeReaderValue<Double_t> PVLeadingJet_pt(reader,"PVLeadingJet_pt"); //branches to read
  TTreeReaderValue<Double_t> LumiWeight(reader,"LumiWeight");

  TH1D *histo = new TH1D("histo","Histogram of PV-LeadingJet_pt, weighted by LumiWeight",500,0,0);
  while( reader.Next() ){
    histo->Fill(*PVLeadingJet_pt, *LumiWeight);
  }

  TFile f("histos.root","RECREATE");
  histo->Write();
  f.Write();

  cout<<endl<<"Finished."<<endl;
  return 0;
}
