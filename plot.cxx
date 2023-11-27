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

int main(int argc, char** argv){
    const char* trg = argv[1];
    TFile* tf1 = new TFile(Form("high_end_point_vz_%s_raw.root", trg));
    TFile* tf2 = new TFile(Form("high_end_point_vz_%s_corr.root", trg));

    TGraphErrors* tg1;
    TGraphErrors* tg2;

    TF1* tfunc1;
    TF1* tfunc2;

    tf1->GetObject("hVsVz", tg1);
    tf2->GetObject("hVsVz", tg2);
    tf1->GetObject("hfunc", tfunc1);
    tf2->GetObject("hfunc", tfunc2);

    TCanvas* c = new TCanvas();
    c->cd();
    TH1* th = gPad->DrawFrame(-75, 550, 75, 640);
    th->SetTitle(Form("Trigger ID: %s;Vz [cm];High end point", trg));
    
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
            lat->DrawLatex(-4, 635-i*4, Form("p_{%d}=%6.2f\t\t#Rightarrow%6.2f", i, tfunc1->GetParameter(i), tfunc2->GetParameter(i)));
        } else {
            // higher orders using 2 scientific form
            lat->DrawLatex(-4, 635-i*4, Form("p_{%d}=%6.2e\t\t#Rightarrow%6.2e", i, tfunc1->GetParameter(i), tfunc2->GetParameter(i)));
        }
    }
    lat->SetTextSize(0.05);
    lat->DrawLatex(0, 570, "h(V_{z})=#sum_{i=0}^{6}p_{i}V_{z}^{i}");
    lat->DrawLatex(-60, 573, "STAR BES-II");
    lat->DrawLatex(-60, 558, "Au+Au @ 17.3 GeV");

    c->Print(Form("hvz_%s.pdf", trg));
    return 0;
}
