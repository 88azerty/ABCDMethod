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

int main (){
  vector<string> filenames;
  vector<float> weights;

  ifstream list( "list.txt" , ios::in ); //read the list of ROOT files from a file
  while( list.good() ){
    string n, w;
    list >> n >> ws >> w;
    if( n.length() == 0 )             continue;
    if( n.compare( 0,1,"#" ) == 0 )   continue;
    filenames.push_back(n);
    weights.push_back( atof( w.c_str() ) );
  }

  TChain *mychain = new TChain("HistFitterTree"); //create a chain with all the files
  for( unsigned int i=0; i<filenames.size(); i++){
    const char *j = filenames.at(i).c_str();
    mychain->Add( j );
    delete j;
  }

  cout<<"TChain has "<<mychain->GetEntries()<< " entries."<<endl;
  // mychain->Draw("nPVWithJet150");
  // TCut *selectA = new TCut("nPVWithJet150 == 0 && nSVWith2Jets == 0");
  // TCut *selectB = new TCut("nPVWithJet150 == 1 && nSVWith2Jets == 0");
  // TCut *selectC = new TCut("nPVWithJet150 == 0 && nSVWith2Jets >= 1");
  // TCut *selectD = new TCut("nPVWithJet150 == 1 && nSVWith2Jets >= 1"); //old way (arguably less precise) of filtering events
  // float nRegionA = mychain->Draw("nPVWithJet150:nSVWith2Jets",*selectA);
  // float nRegionB = mychain->Draw("nPVWithJet150:nSVWith2Jets",*selectB);
  // float nRegionC = mychain->Draw("nPVWithJet150:nSVWith2Jets",*selectC);
  // float nRegionD = mychain->Draw("nPVWithJet150:nSVWith2Jets",*selectD);
  float nRegionA = 0; float wnA = 0;
  float nRegionB = 0; float wnB = 0;
  float nRegionC = 0; float wnC = 0;
  float nRegionD = 0; float wnD = 0;

  TTreeReader reader(mychain); //tree reader to process the data
  TTreeReaderValue<Int_t> nPVWithJet150(reader,"nPVWithJet150"); //branches to read
  TTreeReaderValue<Int_t> nSVWith2Jets(reader,"nSVWith2Jets"); //datatypes for TTreeReaderValue<T>: get from tree data
  TTreeReaderValue<Double_t> EventWeight(reader,"EventWeight");

  while( reader.Next() ){ //selection of events
    if( *nPVWithJet150 == 0 && *nSVWith2Jets == 0 ){
      nRegionA++;
      wnA += *EventWeight;
    }
    if( *nPVWithJet150 == 1 && *nSVWith2Jets == 0 ){
      nRegionB++;
      wnB += *EventWeight;
    }
    if( *nPVWithJet150 == 0 && *nSVWith2Jets >= 1 ){
      nRegionC++;
      wnC += *EventWeight;
    }
    if( *nPVWithJet150 == 1 && *nSVWith2Jets >= 1 ){
      nRegionD++;
      wnD += *EventWeight;
    }
  }

  cout<<"********NON WEIGHTED********"<<endl; //results of the process
  cout<<"Region A: "<<nRegionA<<endl;
  cout<<"Region B: "<<nRegionB<<endl;
  cout<<"Region C: "<<nRegionC<<endl;
  cout<<"Region D: "<<nRegionD<<endl;
  cout<<"Expected D: "<<nRegionB/nRegionA*nRegionC<<endl<<endl;
  cout<<"**********WEIGHTED**********"<<endl;
  cout<<"Region A: "<<wnA<<endl;
  cout<<"Region B: "<<wnB<<endl;
  cout<<"Region C: "<<wnC<<endl;
  cout<<"Region D: "<<wnD<<endl;
  cout<<"Expected D: "<<wnB/wnA*wnC<<endl;

  cout<<endl<<endl<<"All data processed."<<endl<<endl;
  return 0;

}
