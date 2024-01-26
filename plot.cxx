#include "TFile.h"
#include "TH2D.h"
#include "TH1D.h"
#include "TAxis.h"
#include "TString.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TLatex.h"
#include "TLegend.h"

#include <vector>
#include <algorithm>

int main(int argc, char** argv){
    const char* trg = argv[1];
    const char* ref3Tag = argv[2];
    TFile* tf1 = new TFile(Form("high_end_point_vz_Ref%s_%s_raw.root", ref3Tag, trg));
    TFile* tf2 = new TFile(Form("high_end_point_vz_Ref%s_%s_corr.root", ref3Tag, trg));

    TGraphErrors* tg1;
    TGraphErrors* tg2;

    TF1* tfunc1;
    TF1* tfunc2;

    tf1->GetObject("hVsVz", tg1);
    tf2->GetObject("hVsVz", tg2);
    tf1->GetObject("hfunc", tfunc1);
    tf2->GetObject("hfunc", tfunc2);

    // Axis range finding Block: 
    int nPoints = tg1->GetN(); // tg1 and tg2 should have the same number of points
    auto tg1vec = tg1->GetY();
    auto tg2vec = tg2->GetY();
    std::vector<Double_t> mVec(tg1vec, tg1vec+nPoints);
    mVec.insert(mVec.end(), tg2vec, tg2vec+nPoints);
    double yMax = *std::max_element(mVec.begin(), mVec.end());
    double yMin = *std::min_element(mVec.begin(), mVec.end());
    double yMean = yMax*0.5 + yMin*0.5;
    double yWidth = yMax - yMin;
    const double factor = 4.5;
    double yTop = yMean+0.5*factor*yWidth;
    double yBot = yMean-0.5*factor*yWidth;
    // std::cout << "DEBUG: ymax " << yMax << std::endl;
    // std::cout << "DEBUG: ymin " << yMin << std::endl;
    // std::cout << "DEBUG: ymean " << yMean << std::endl;
    // std::cout << "DEBUG: ywidth " << yWidth << std::endl;
    // std::cout << "DEBUG: ytop " << yTop << std::endl;
    // std::cout << "DEBUG: ybot " << yBot << std::endl;

    TCanvas* c = new TCanvas();
    c->cd();
    TH1* th = gPad->DrawFrame(-75, yBot, 75, yTop);
    th->SetTitle(Form("Trigger ID: %s (RefMult%s);Vz [cm];High end point", trg, ref3Tag));
    
    tg1->SetLineColor(1);
    tg1->SetMarkerColor(1);
    tg1->SetMarkerStyle(20);
    tfunc1->SetLineColor(1);

    tg2->SetLineColor(2);
    tg2->SetMarkerColor(2);
    tg2->SetMarkerStyle(21);
    tfunc2->SetLineColor(2);

    tg2->Draw("eplsame");
    tfunc2->Draw("lsame");
    tg1->Draw("eplsame");
    tfunc1->Draw("lsame");
    
    TLegend* leg = new TLegend(0.21, 0.66, 0.5, 0.87);
    leg->AddEntry(tg1, "Raw", "lep");
    leg->AddEntry(tg2, "Vz Corrected", "lep");
    leg->SetLineColor(0);
    leg->Draw();

    TLatex* lat = new TLatex();
    lat->SetTextSize(0.03);
    lat->SetTextColor(1);
    for (int i=0; i<7; i++){
        if (i==0) {
            // p0 (const) using 2 digits float
            lat->DrawLatexNDC(0.48, 0.85-i*0.03, Form("p_{%d}=%6.2f\t\t#Rightarrow%6.2f", i, tfunc1->GetParameter(i), tfunc2->GetParameter(i)));
        } else {
            // higher orders using 2 scientific form
            lat->DrawLatexNDC(0.48, 0.85-i*0.03, Form("p_{%d}=%6.2e\t\t#Rightarrow%6.2e", i, tfunc1->GetParameter(i), tfunc2->GetParameter(i)));
        }
    }
    lat->SetTextSize(0.05);
    lat->DrawLatexNDC(0.5, 0.30, "h(V_{z})=#sum_{i=0}^{6}p_{i}V_{z}^{i}");
    lat->DrawLatexNDC(0.24, 0.25, "STAR BES-II");
    lat->DrawLatexNDC(0.24, 0.20, "Au+Au @ 14.6 GeV");

    c->Print(Form("hvz_Ref%s_%s.pdf", ref3Tag, trg));
    return 0;
}
