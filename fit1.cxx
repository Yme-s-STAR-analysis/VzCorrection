#include "TFile.h"
#include "TH2F.h"
#include "TH1D.h"
#include "TAxis.h"
#include "TString.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TLatex.h"

int main(int argc, char** argv){
    const char* trg = argv[1];
    const char* x1s = argv[2]; // fit range
    const char* x2s = argv[3];
    const char* ref3Tag = argv[4]; // 3 or 3X
    int x1 = atoi(x1s);
    int x2 = atoi(x2s);
    TFile* tf = new TFile("vz_ref3_raw.root");
    TH2F* th = (TH2F*)tf->Get(Form("hVzRef%s_%s", ref3Tag, trg));

    // prepare TH1Ds
    const Int_t nbins = 35;
    Double_t vzmin = -70;
    Double_t vzmax = 70;
    Double_t step = (vzmax-vzmin) / nbins;
    Double_t h[nbins] = {0};
    Double_t herr[nbins] = {0};
    Double_t vz[nbins] = {0};
    Double_t vzerr[nbins] = {0};
    TH1D* hRef3[nbins];
    TAxis* yaxis = th->GetYaxis();
    for (Int_t i=0; i<nbins; i++){
        hRef3[i] = (TH1D*)th->ProjectionX(
            Form("vz_%.0f_%.0f", vzmin+i*step, vzmin+i*step+step), 
            yaxis->FindBin(vzmin+i*step), 
            yaxis->FindBin(vzmin+i*step+step)
        );
        hRef3[i]->SetTitle(
            Form("v#in(%.0f, %.0f) [cm];RefMult%s;", vzmin+i*step, vzmin+i*step+step, ref3Tag)
        );
        vz[i] = vzmin+(i+0.5)*step;
    }

    // prepare h function
    TF1* tfunc = new TF1("tfunc", "[0]*TMath::Erf(-[1]*(x-[2]))+[0]", x1, x2);
    tfunc->SetLineColor(2);
    tfunc->SetParameter(1, 0.02);
    tfunc->SetParameter(2, 0.5 * (x1+x2));

    // set parameter limit
    tfunc->SetParLimits(2, x1, x2);

    // plot them
    TCanvas* c = new TCanvas();
    // page 1: TH2F
    c->cd();
    gPad->SetLogz();
    th->Draw("colz");
    c->Print(Form("vz_dist_raw_Ref%s_%s.pdf(", ref3Tag, trg));
    c->Print(Form("vz_dist_raw_Ref%s_%s_heatmap.png", ref3Tag, trg));
    // page 2 to 5, 60 figures
    for (int ipage=0; ipage<2; ipage++){ 
        c->Clear();
        c->Divide(5, 3);
        for (int i=0; i<15; i++){
            c->cd(i+1);
            gPad->SetLogy();
            hRef3[i+ipage*15]->Scale(1.0 / hRef3[i+ipage*15]->GetMaximum());
            hRef3[i+ipage*15]->Draw("lep");
            tfunc->SetParameter(0, 1.0);
            tfunc->SetParLimits(0, 1e-3, 1e-1);
            tfunc->SetParameter(1, 0.02);
            tfunc->SetParameter(2, 0.5 * (x1+x2));
            tfunc->SetParLimits(2, x1, x2);
            for (Int_t ifit=0; ifit<10; ifit++){
                hRef3[i+ipage*15]->Fit(tfunc, "RN0", "", x1, x2);
            }
            tfunc->DrawClone("lsame");
            h[i+ipage*15] = tfunc->GetParameter(2);
            herr[i+ipage*15] = tfunc->GetParError(2);
        }
        c->Print(Form("vz_dist_raw_Ref%s_%s.pdf", ref3Tag, trg));
        c->Print(Form("vz_dist_raw_Ref%s_%s_p%d.png", ref3Tag, trg, ipage+1));
    }
    // page 6:  10 figs (all 70 done)
    c->Clear();
    c->Divide(5, 3);
    for (int i=0; i<5; i++){
        c->cd(i+1);
        gPad->SetLogy();
        hRef3[i+30]->Scale(1.0 / hRef3[i+30]->GetMaximum());
        hRef3[i+30]->Draw("lep");
        tfunc->SetParameter(0, 1.0);
        tfunc->SetParameter(1, 0.02);
        tfunc->SetParameter(2, 0.5 * (x1+x2));
        for (Int_t ifit=0; ifit<5; ifit++){
            hRef3[i+30]->Fit(tfunc, "RN0Q", "", x1, x2);
        }
        tfunc->DrawClone("lsame");
        h[i+30] = tfunc->GetParameter(2);
        herr[i+30] = tfunc->GetParError(2);
    }
    // draw text
    TLatex* lat = new TLatex();
    lat->SetTextSize(0.04);
    c->cd();
    lat->DrawLatexNDC(0.3, 0.18, "STAR BES-II");
    lat->DrawLatexNDC(0.3, 0.08, "Au+Au @ 14.6 GeV");
    c->Print(Form("vz_dist_raw_Ref%s_%s.pdf)", ref3Tag, trg));
    c->Print(Form("vz_dist_raw_Ref%s_%s_p5.png", ref3Tag, trg));

    // save h(vz)
    TGraphErrors* tg = new TGraphErrors(nbins, vz, h, vzerr, herr);
    tg->SetName("hVsVz");
    TF1* hfunc = new TF1("hfunc", "pol6", vzmin, vzmax);
    tg->Fit(hfunc, "RN0", "", vzmin, vzmax);
    TFile* tsave = new TFile(Form("high_end_point_vz_Ref%s_%s_raw.root", ref3Tag, trg), "recreate");
    tsave->cd();
    tg->Write();
    hfunc->Write();
    tsave->Close();

    tf->Close();

    return 0;
}