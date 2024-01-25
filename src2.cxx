#include <iostream>
#include <fstream>

#include "TFile.h"
#include "TChain.h"
#include "TH2F.h"
#include "TH1F.h"
#include "TString.h"

#include "tree_reader.h"
#include "./CentCorrTool/CentParams.h"


int main(){
    /*
    
        This src2 is for:
            - check the corrected RefMult3 distributions
    
    
    */
    using std::cout;
    using std::string;
    using std::vector;
    using std::ifstream;
    vector<string> file_list;
    ifstream fin("file.list");
    string strtmp;
    int n_file = 0;
    while (std::getline(fin, strtmp)){
        n_file ++;
        if (n_file % 500 == 0){
            cout << "[LOG] " << n_file << " files found.\n";
        }
        file_list.push_back(strtmp);
    }
    cout << "[LOG] All " << n_file << " files found.\n";

    TChain* chain = new TChain("centTree");

    Int_t ifile = 0;
    for (auto iter=file_list.begin(); iter!=file_list.end(); iter++){
        ifile ++;
        if (ifile % 500 == 0){
            cout << "[LOG] " << ifile << " trees read.\n";
        }
        chain->Add(iter->c_str());
    }
    cout << "[LOG] All " << ifile << " trees read.\n";

    cout << "[LOG] Preparing to get histograms.\n";
    TreeReader* maker = new TreeReader();
    maker->init_reader(chain);
    Int_t nev = maker->get_entries();

    CentCorrTool* corr = maker->GetCentCorrTool();
    corr->SetDoMatchPileUp(true);
    corr->SetDoBetaPileUp(true);
    corr->SetDoLumi(false);
    corr->SetDoVz(true);
    corr->SetDoLumiX(false);
    corr->SetDoVzX(true);
    corr->ReadParams();


    const int nTrg = cent_conf::nTrg;

    TH2F* hVzRef3[nTrg];
    for (int i=0; i<nTrg; i++) {
        hVzRef3[i] = new TH2F(
            Form("hVzRef3_%d", cent_conf::trgList[i]), 
            ";RefMult3;v_{z} [cm]", 
            850, -0.5, 849.5, 
            141, -70.5, 70.5
        );
    }
    TH2F* hVzRef3X[nTrg];
    for (int i=0; i<nTrg; i++) {
        hVzRef3X[i] = new TH2F(
            Form("hVzRef3X_%d", cent_conf::trgList[i]), 
            ";RefMult3X;v_{z} [cm]", 
            1350, -0.5, 1349.5, 
            141, -70.5, 70.5
        );
    }

    for (Int_t i=0; i<nev; i++) {
        maker->make(i);
        int trg = maker->get_converted_trg();
        if (trg < 0 || trg >= nTrg) {
            continue;
        }
        int vzbin = corr->GetPileUpVzBin(maker->vz);
        if (vzbin < 0) { continue; }
        int ref3 = corr->GetRefMult3Corr(maker->RefMult, maker->RefMult3, maker->nTofMatch, maker->nTofBeta, 0, maker->vz, maker->trgid);
        int ref3X = corr->GetRefMult3Corr(maker->RefMult, maker->RefMult3X, maker->nTofMatch, maker->nTofBeta, 0, maker->vz, maker->trgid, true);
        if (ref3 >= 0) {
            hVzRef3[trg]->Fill(ref3, maker->vz);
        }
        if (ref3X >= 0) {
            hVzRef3X[trg]->Fill(ref3X, maker->vz);
}
    }


    cout << "[LOG] All done, now saving.\n";
    TFile* tfout = new TFile("vz_ref3_corr.root", "recreate");
    tfout->cd();
    for (int i=0; i<nTrg; i++) {
        hVzRef3[i]->Write();
        hVzRef3X[i]->Write();
    }
    tfout->Close();
    cout << "[LOG] This is the end of this workshop.\n";
    return 0;
}