#include <fstream>
#include <iostream>
#include <string>
{
    const int N=7;
    TString filenames = {"4800.root"};
    TFile* files;
    TTree* trees;
    double Z, En;
    char Particle_Name[256];
    TH1F* hBetheBloch[N];
    TProfile* pBetheBloch[N];

    gROOT->Reset();
    gStyle->SetOptFit(0);
    gStyle->SetLabelFont(42);
    gStyle->SetTitleFont(42);
    gStyle->SetPadLeftMargin(0.12);
    gStyle->SetPadRightMargin(0.12);
    gStyle->SetPadTopMargin(0.07);
    gStyle->SetPadBottomMargin(0.12);
    gStyle->SetPadTickX(1);
    gStyle->SetPadTickY(1);
    gStyle->SetLineStyleString(11,"32 18");
    double TextSizeScale = 1.0;

        files = new TFile(filenames);
        trees = (TTree*)files->Get("Produced particles");
        trees->SetBranchAddress("Particle_Name", Particle_Name);
        trees->SetBranchAddress("Z", &Z);
        trees->SetBranchAddress("En", &En);
 
    for (int i=0; i<N; i++){
        hBetheBloch[i]= new TH1F(Form("hBetheBloch%d", i+1), "amount of different produced particles in depth", 100, 0, 300);}
        
        int nentries = trees->GetEntries();
        for (int j = 0; j < nentries; ++j) {
            trees->GetEntry(j);
            if (std::string(Particle_Name)=="C12") {
                hBetheBloch[0]->Fill(Z);
            }
            if (std::string(Particle_Name)=="alpha") {
                hBetheBloch[1]->Fill(Z);
            }
            if (std::string(Particle_Name)=="proton") {
                hBetheBloch[2]->Fill(Z);
            }
            if (std::string(Particle_Name)=="gamma") {
                hBetheBloch[3]->Fill(Z);
            }
            if (std::string(Particle_Name)=="O16") {
                hBetheBloch[4]->Fill(Z);
            }
            if (std::string(Particle_Name)=="neutron") {
                hBetheBloch[5]->Fill(Z);
            }
            if (std::string(Particle_Name)=="deuteron") {
                hBetheBloch[6]->Fill(Z);
            }
        }
    
        TCanvas *c1 = new TCanvas("c1", "c1", 1020, 720);
        hBetheBloch[0]->GetYaxis()->SetTickLength(0.02);
        hBetheBloch[0]->GetYaxis()->SetNdivisions(505);
        hBetheBloch[0]->GetXaxis()->CenterTitle();
        hBetheBloch[0]->GetYaxis()->CenterTitle();
        hBetheBloch[0]->GetXaxis()->SetTitle("Z");
        hBetheBloch[0]->GetYaxis()->SetTitleSize(0.045*TextSizeScale);
        hBetheBloch[0]->GetYaxis()->SetTitleOffset(1.2);
        hBetheBloch[0]->GetXaxis()->SetTitleSize(0.045*TextSizeScale);
        hBetheBloch[0]->GetXaxis()->SetTitleOffset(1.0);
        hBetheBloch[0]->GetYaxis()->SetLabelSize(0.04*TextSizeScale);
        hBetheBloch[0]->GetXaxis()->SetLabelSize(0.04*TextSizeScale);
        hBetheBloch[0]->GetYaxis()->SetLabelFont(42);
        hBetheBloch[0]->GetYaxis()->SetTitleFont(42);
        hBetheBloch[0]->GetYaxis()->SetRangeUser(0, 200);
        hBetheBloch[0]->GetXaxis()->SetTitleFont(42);
        hBetheBloch[0]->SetLineColor(8);
        hBetheBloch[0]->SetLineWidth(2);
        hBetheBloch[0]->Draw("hist");
    for (int i=1; i<N; i++){
           hBetheBloch[i]->SetLineColor(i);
           hBetheBloch[i]->SetLineWidth(2);
           hBetheBloch[i]->SetLineStyle(1);
           hBetheBloch[i]->SetMarkerStyle(1);
           hBetheBloch[i]->SetMarkerSize(0);
           hBetheBloch[i]->Draw("same");
       }
       
       TLegend* legend = new TLegend(0.50, 0.65, 0.7, 0.80);
           legend->SetTextSize(0.036);
           legend->SetTextFont(42);
           legend->SetHeader("Type of particle:");
           legend->AddEntry(hBetheBloch[0], "C12");
           legend->AddEntry(hBetheBloch[1], "alpha");
           legend->AddEntry(hBetheBloch[2], "proton");
           legend->AddEntry(hBetheBloch[3], "gamma");
           legend->AddEntry(hBetheBloch[4], "O16");
           legend->AddEntry(hBetheBloch[5], "neutron");
           legend->AddEntry(hBetheBloch[6], "deuteron");
          // legend->AddEntry(hBetheBloch[7], "e-");
           legend->SetFillColor(kWhite);
           legend->SetLineColor(kWhite);
           legend->Draw();
}
