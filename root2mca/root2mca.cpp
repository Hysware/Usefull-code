#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <TROOT.h>
#include <TCanvas.h>
#include <TString.h>
#include <iostream>
#include <fstream>
#include <string>

void root2mca() {
    // 你可以根据实际情况修改这行
    std::string sourceFile = "/media/zhy/exp/2025_HIL/rf/run_0064_03-07-2025_14h29m35s/eagleLF_i2884_0064_0000_sorted.root";

    TFile *file = TFile::Open(sourceFile.c_str());
    //TFile *file = new TFile(filename.Data(),"READ");

    if (!file || file->IsZombie()) {
        std::cerr << "Error opening file: " << sourceFile << std::endl;
        return;
    }

    TTree *tree = (TTree*)file->Get("NeedleTree");
    if (!tree) {
        std::cerr << "Error getting tree: NeedleTree" << std::endl;
        file->Close();
        return;
    }
    TFile *rootfile = new TFile("./raw_th1.root","RECREATE");
    if(!rootfile->IsOpen())
    {
      std::cout<<"Can't create root file"<<std::endl;
    }
    rootfile->cd();
    for (int sid = 0; sid <= 2; ++sid) {
        for (int ch = 0; ch <= 15; ch += 2) {
	    if (sid ==2 && ch== 2) break;
            std::string histName = "sid" + std::to_string(sid) + "_ch" + std::to_string(ch);
            // TH1F *hist = new TH1F(histName.c_str(), histName.c_str(), 32768, 0, 32768);
            TH1F *hist = new TH1F(histName.c_str(), histName.c_str(), 31900, 100, 32000);

            std::string drawCmd = "EAGLE.fEnergy>>" + histName;
            std::string cut = "EAGLE.fBoard==" + std::to_string(sid) + " && EAGLE.fChannel==" + std::to_string(ch);

            std::cout << "Processing sid = " << sid << ", ch = " << ch << std::endl;
            tree->Draw(drawCmd.c_str(), cut.c_str(), "goff"); // 'goff' means off-screen, faster
	    hist->Write();
            std::string outFile = "./board_" + std::to_string(sid) + "ch_" + std::to_string(ch) + ".mca";
            std::ofstream fout(outFile);
            if (!fout.is_open()) {
                std::cerr << "Failed to open output file: " << outFile << std::endl;
                delete hist;
                continue;
            }

            fout << "<<PMCA SPECTRUM>>" << std::endl;
            fout << "TAG - PKUXIADAQ" << std::endl;
            fout << "DESCRIPTION - Hongyi Wu" << std::endl;
            fout << "GAIN - 6" << std::endl;
            fout << "THRESHOLD - " << std::endl;
            fout << "LIVE_MODE - " << std::endl;
            fout << "PRESET_TIME - " << std::endl;
            fout << "LIVE_TIME - " << std::endl;
            fout << "REAL_TIME - " << std::endl;
            fout << "START_TIME - " << std::endl;
            fout << "SERIAL_NUMBER - " << std::endl;
            fout << "<<DATA>>" << std::endl;

            for (int i = 1; i <= hist->GetNbinsX(); ++i) {
                int count = static_cast<int>(hist->GetBinContent(i));
                fout << count << "\n";
            }

            fout << "<<END>>" << std::endl;
            fout.close();
            delete hist;
        }
    }

    file->Close();
    delete file;
    rootfile->Close();
    delete rootfile;
}

// 主函数，供独立编译时使用
int main() {
     // 可按需修改
    root2mca();
    return 0;
}

