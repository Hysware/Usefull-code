// run with: root -l hist2txt.C
// Function： 将root文件中的直方图转为txt格式，并输出
// 2024.11.22

#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <iostream>
#include <fstream>

void hist2txt(int fileNumber) {
    // 构造ROOT文件名
    std::string soureFile = "data_C1_0" + std::to_string(fileNumber) + "_wave.root";

    // 打开ROOT文件
    TFile *file = TFile::Open(soureFile.c_str());
    if (!file || file->IsZombie()) {
        std::cerr << "Error opening file" << std::endl;
        return;
    }

    // 获取树
    TTree *tree = (TTree*)file->Get("tree");  // 假设树的名字是 "tree"
    if (!tree) {
        std::cerr << "Error getting tree" << std::endl;
        file->Close();
        return;
    }

    // 创建一个直方图
    TH1F *h1 = new TH1F("h1", "Filtered Histogram", 800, 0, 20);

    // 填充直方图
    tree->Draw("evte*0.0037798+0.0674093>>h1(750,0,50)", "sid==4&&ch==4");

///////////////////////////////////////////////////////////////////////////
// 取消注释即可将h1存为txt格式文件 
/*
    // 创建输出文件
   std::ofstream outfile("histogram_output.txt");
    if (!outfile.is_open()) {
        std::cerr << "Error opening output file" << std::endl;
        file->Close();
        return;
    }

    // 输出列标题
    outfile << "# BinCenter BinContent BinError" << std::endl;

    // 遍历直方图的所有 bins
    for (int i = 1; i <= h1->GetNbinsX(); ++i) {
        double binCenter = h1->GetBinCenter(i); // bin 中心
        double binContent = h1->GetBinContent(i); // bin 高度
        double binError = h1->GetBinError(i); // bin 误差

        // 写入文件
        outfile << binCenter << " " << binContent << " " << binError << std::endl;
    }

    // 关闭输出文件
    outfile.close();

    // 输出完成信息
    std::cout << "Histogram data saved to histogram_output.txt" << std::endl;

    // 关闭文件
    file->Close();
*/
}
