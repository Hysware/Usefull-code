#include <TFile.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <iostream>

void tree2hist(int fileNumber) {
    std::string sourceFile = "data_C1_0" + std::to_string(fileNumber) + ".root";
    TFile *file = TFile::Open(sourceFile.c_str());

    if (!file || file->IsZombie()) {
        std::cerr << "Error opening file" << std::endl;
        return;
    }

    TTree *tree = (TTree*)file->Get("tree");
    if (!tree) {
        std::cerr << "Error getting tree" << std::endl;
        file->Close();
        return;
    }

    std::string targetFile = "./hist_files/data_hist_0" + std::to_string(fileNumber) + ".root";
    TFile *file1 = TFile::Open(targetFile.c_str(), "UPDATE");

    for (int sid = 2; sid <=12; ++sid)
    for (int ch = 0; ch <= 15; ++ch) {  // Adjust the range as needed
        std::string histName = "hist"+std::to_string(sid)+"_ch" + std::to_string(ch);
        TH1F *hist = new TH1F(histName.c_str(), ("Histogram for ch " + std::to_string(ch)).c_str(), 5000, 100, 10100);
        
        tree->Draw(("evte>>+" + histName).c_str(), ("sid=="+std::to_string(sid)+"&&ch==" + std::to_string(ch)).c_str());

        // Optionally create a canvas to draw the histogram
        TCanvas *c1 = new TCanvas(histName.c_str(), histName.c_str(), 800, 600);
        //hist->Draw();
        
        // Write histogram to the ROOT file
        file1->cd();
        hist->Write();

        delete c1;  // Clean up canvas if not needed
        delete hist; // Clean up histogram
    }

    file->Close();
    file1->Close();
    delete file;
    delete file1;
    gROOT->ProcessLine(".q");
}
