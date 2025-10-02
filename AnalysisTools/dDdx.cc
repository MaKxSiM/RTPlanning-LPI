#include <fstream>
#include <iostream>
{
    const int N = 1;
   // string filenames = "../build/output.root";
  //  TFile* files;
    TTree* trees;
    double Edep_MeV, Z, dose;
    TH1F* hBetheBloch;
    TProfile* pBetheBloch;

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


    TFile files("../../RTPlanning-LPI-build/output.root");
    trees = (TTree*)files.Get("dEdzD");
    trees->SetBranchAddress("Edep_MeV", &Edep_MeV);
    trees->SetBranchAddress("Z", &Z);
    //    trees[i]->SetBranchAddress("dose", &dose[i]);



    double a1 = trees->GetMaximum("Edep_MeV");
    double b = trees->GetMaximum("Z");
    double binsX = b;
    double binsY = a1;

    hBetheBloch= new TH1F( "hBetheBloch","Continious Energy Deposition In Water;E, MeV; #frac{dE}{dx}, #frac{MeV}{cm}",  900, 0, 900);

        int nentries = trees->GetEntries();
        for (int j = 0; j < nentries; ++j) {
            trees->GetEntry(j);
            hBetheBloch->Fill(Z, Edep_MeV);
        }



    TCanvas *y = new TCanvas("y", "y", 1020, 720);
    hBetheBloch->GetYaxis()->SetTickLength(0.02);
    hBetheBloch->GetYaxis()->SetNdivisions(505);
    hBetheBloch->GetXaxis()->CenterTitle();
    hBetheBloch->GetYaxis()->CenterTitle();
    hBetheBloch->GetYaxis()->SetTitle("#frac{dD}{dx}");
    hBetheBloch->GetXaxis()->SetTitle("Z, mm");
    hBetheBloch->GetYaxis()->SetTitleSize(0.045*TextSizeScale);
    hBetheBloch->GetYaxis()->SetTitleOffset(1.2);
    hBetheBloch->GetXaxis()->SetTitleSize(0.045*TextSizeScale);
    hBetheBloch->GetXaxis()->SetTitleOffset(1.0);
    hBetheBloch->GetYaxis()->SetLabelSize(0.04*TextSizeScale);
    hBetheBloch->GetXaxis()->SetLabelSize(0.04*TextSizeScale);
    hBetheBloch->GetYaxis()->SetLabelFont(42);
    hBetheBloch->GetYaxis()->SetTitleFont(42);
    hBetheBloch->GetXaxis()->SetTitleFont(42);
    cout<<trees->GetMaximum("Edep_MeV")<<endl;
  //  hBetheBloch[0]->GetYaxis()->SetRangeUser(0, ((trees[N-1]->GetMaximum("Edep_MeV"))*1.2));
    hBetheBloch->SetLineColor(8);
    hBetheBloch->SetLineWidth(2);
    hBetheBloch->SetLineStyle(1);
    hBetheBloch->SetMarkerStyle(1);
    hBetheBloch->SetMarkerSize(0);
    hBetheBloch->Draw("hist");
    TLegend* legend2 = new TLegend(0.40, 0.8, 0.6, 0.90);//
    legend2->SetTextSize(0.036);
    legend2->SetTextFont(42);
    legend2->SetHeader("1000 C12,E=3240 MeV","C");
    legend2->SetFillColor(kWhite);
    legend2->SetLineColor(kWhite);
    legend2->Draw();
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
