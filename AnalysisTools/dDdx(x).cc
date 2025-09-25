#include <fstream>
#include <iostream>
{
    const int N = 1;
    TString filenames[N] = {"3240.root"};
    TFile* files[N];
    TTree* trees[N];
    double Edep_MeV[N], Z[N], dose[N];
    TH2F* hBetheBloch[N];
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

    for (int i = 0; i < N; ++i) {
        files[i] = new TFile(filenames[i]);
        trees[i] = (TTree*)files[i]->Get("Dose_in_volume_N");
        trees[i]->SetBranchAddress("Edep_MeV", &Edep_MeV[i]);
        trees[i]->SetBranchAddress("Z", &Z[i]);
        trees[i]->SetBranchAddress("dose", &dose[i]);
    }

    for (int i = 0; i < N; ++i) {
        double a1 = trees[i]->GetMaximum("Edep_MeV");
        double b = trees[i]->GetMaximum("Z");
        double binsX = b;
        double binsY = a1;

        hBetheBloch[i] = new TH2F(Form("hBetheBloch%d", i+1), "Continious Energy Deposition In Water;E, MeV; #frac{dE}{dx}, #frac{MeV}{cm}",
                                  600, 0, b, binsY, 0, binsY*1.2);

        int nentries = trees[i]->GetEntries();
        for (int j = 0; j < nentries; ++j) {
            trees[i]->GetEntry(j);
            hBetheBloch[i]->Fill(Z[i], Edep_MeV[i]);
        }

        pBetheBloch[i] = hBetheBloch[i]->ProfileX(Form("pBetheBloch%d", i+1));
    }

    TCanvas *y = new TCanvas("y", "y", 1020, 720);
    pBetheBloch[0]->GetYaxis()->SetTickLength(0.02);
    pBetheBloch[0]->GetYaxis()->SetNdivisions(505);
    pBetheBloch[0]->GetXaxis()->CenterTitle();
    pBetheBloch[0]->GetYaxis()->CenterTitle();
    pBetheBloch[0]->GetYaxis()->SetTitle("#frac{dD}{dx}");
    pBetheBloch[0]->GetXaxis()->SetTitle("Z, mm");
    pBetheBloch[0]->GetYaxis()->SetTitleSize(0.045*TextSizeScale);
    pBetheBloch[0]->GetYaxis()->SetTitleOffset(1.2);
    pBetheBloch[0]->GetXaxis()->SetTitleSize(0.045*TextSizeScale);
    pBetheBloch[0]->GetXaxis()->SetTitleOffset(1.0);
    pBetheBloch[0]->GetYaxis()->SetLabelSize(0.04*TextSizeScale);
    pBetheBloch[0]->GetXaxis()->SetLabelSize(0.04*TextSizeScale);
    pBetheBloch[0]->GetYaxis()->SetLabelFont(42);
    pBetheBloch[0]->GetYaxis()->SetTitleFont(42);
    pBetheBloch[0]->GetXaxis()->SetTitleFont(42);
    pBetheBloch[0]->GetYaxis()->SetRangeUser(0, ((trees[N-1]->GetMaximum("Edep_MeV"))*1.2));
    pBetheBloch[0]->SetLineColor(8);
    pBetheBloch[0]->SetLineWidth(2);
    pBetheBloch[0]->SetLineStyle(1);
    pBetheBloch[0]->SetMarkerStyle(1);
    pBetheBloch[0]->SetMarkerSize(0);
    pBetheBloch[0]->Draw("hist");
 /*   for (int i=1; i<N; i++){
        pBetheBloch[i]->SetLineColor(i);
        pBetheBloch[i]->SetLineWidth(2);
        pBetheBloch[i]->SetLineStyle(1);
        pBetheBloch[i]->SetMarkerStyle(1);
        pBetheBloch[i]->SetMarkerSize(0);
        pBetheBloch[i]->Draw("same");
    }*/
    
  /*  TLegend* legend = new TLegend(0.50, 0.65, 0.7, 0.80);
        legend->SetTextSize(0.036);
        legend->SetTextFont(42);
        legend->SetHeader("Type of particle:");
        legend->AddEntry(pBetheBloch[0], "carbon ion");*/
      /*  legend->AddEntry(pBetheBloch[1], "oxygen ion");
        legend->AddEntry(pBetheBloch[2], "silicon ion");
        legend->AddEntry(pBetheBloch[3], "iron ion");*/
   /*     legend->SetFillColor(kWhite);
        legend->SetLineColor(kWhite);
        legend->Draw();*/
    /*
    std::ofstream outFile("ContiniousEnergyLossInAir.ascii");
        if (!outFile.is_open()) {
            std::cerr << "Error: Could not open file " << std::endl;
        } else {
            int Nbins = pBetheBloch[0]->GetNbinsX();
            outFile << std::fixed << std::setprecision(3);
            double b = trees[0]->GetMaximum("En");
            for (int i = 1; i <= Nbins; i++) {
                double edge1 = pBetheBloch[0]->GetXaxis()->GetBinLowEdge(i);
                double edge2 = pBetheBloch[0]->GetXaxis()->GetBinUpEdge(i);
                double content = pBetheBloch[0]->GetBinContent(i);
                if (edge2 <= b){
                    outFile << edge1 << "\t" << edge2 << "\t" << content << std::endl;}
            }
            outFile.close();
            std::cout << "Graph data successfully written to " << std::endl;
        }*/
}
