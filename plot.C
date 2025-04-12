 #include <TFile.h>
 #include <TTree.h>
 #include <TCanvas.h>
 #include <TH1F.h>
 #include <iostream>
 #include <string>
 #include "TApplication.h"
 
 void plot(int fileNumber1, int sid) {
     // 构造文件名
     TString sourceFile1 = TString::Format("fit_csi_%04d.root", fileNumber1);
 
     // 打开ROOT文件
     TFile *file = TFile::Open(sourceFile1);
     if (!file || file->IsZombie()) {
         std::cout << "Error: Could not open ROOT file!" << std::endl;
         return;
     }
 
     // 获取树（TTree）
     TTree *tree = (TTree*)file->Get("tree");
     if (!tree) {
         std::cout << "Error: Could not find tree in the file!" << std::endl;
         file->Close();
         return;
     }
 
     // 创建画布并分成2行4列
     TCanvas *c1 = new TCanvas("c1", Form("f:s Plots,SID = %d,RunNum = %d",sid, fileNumber1), 200, 10, 700, 900);
     c1->Divide(4, 4);
 
     // 创建直方图

     //int sid = 2;  // sid

     TH2F *h1[16]; // 用数组存储8个直方图对象
     for (int i = 0; i < 16; i++) {
         h1[i] = new TH2F(Form("h%d", i + 1), Form("8 detectors Histogram %d", i + 1), 2000, 200, 4200, 2000, 200, 4200);
	 c1->cd(i+1);
	 tree->Draw(Form("f:s>>h1[%d](800,0,8000,1600, 0, 16000)",i), Form("sid==%d&&ch==%d", sid, i), "colz");

     }
/* 
     // 逐个子画布绘制直方图
     c1->cd(1);
     tree->Draw("f:s>>h1[0](800,0,8000,1600, 0, 16000)", Form("sid==%d&&ch==0", sid), "colz");
     //c1->GetPad(1)->SetLogy(1);//c1->Update();

 
     c1->cd(2);
     tree->Draw("f:s>>h1[1](800,0,8000,1600, 0, 16000)", "sid==2&&ch==1", "colz");
     //c1->GetPad(2)->SetLogy(1);
 
     c1->cd(3);
     tree->Draw("f:s>>h1[2](800,0,8000,1600, 0, 16000)", "sid==2&&ch==2", "colz");
     //c1->GetPad(3)->SetLogy(1);
 
     c1->cd(4);
     tree->Draw("f:s>>h1[3](800,0,8000,1600, 0, 16000)", "sid==2&&ch==3", "colz");
     //c1->GetPad(4)->SetLogy(1);
 
     c1->cd(5);
     tree->Draw("f:s>>h1[4](800,0,8000,1600, 0, 16000)", "sid==2&&ch==4", "colz");
     //c1->GetPad(5)->SetLogy(1);
 
     c1->cd(6);
     tree->Draw("f:s>>h1[5](800,0,8000,1600, 0, 16000)", "sid==2&&ch==5", "colz");
     //c1->GetPad(6)->SetLogy(1);
 
     c1->cd(7);
     tree->Draw("f:s>>h1[6](800,0,8000,1600, 0, 16000)", "sid==2&&ch==6", "colz");
     //c1->GetPad(7)->SetLogy(1);
 
     c1->cd(8);
     tree->Draw("f:s>>h1[7](800,0,8000,1600, 0, 16000)", "sid==2&&ch==7", "colz");
     //c1->GetPad(8)->SetLogy(1);
 
     c1->cd(9);
     tree->Draw("f:s>>h1[8](800,0,8000,1600, 0, 16000)", "sid==2&&ch==8", "colz");
     //c1->GetPad(8)->SetLogy(1);
 
     c1->cd(10);
     tree->Draw("f:s>>h1[9](800,0,8000,1600, 0, 16000)", "sid==2&&ch==9", "colz");
     //c1->GetPad(8)->SetLogy(1);
 
     c1->cd(11);
     tree->Draw("f:s>>h1[10](800,0,8000,1600, 0, 16000)", "sid==2&&ch==10", "colz");
     //c1->GetPad(8)->SetLogy(1);
 
     c1->cd(12);
     tree->Draw("f:s>>h1[11](800,0,8000,1600, 0, 16000)", "sid==2&&ch==11", "colz");
     //c1->GetPad(8)->SetLogy(1);
 
     c1->cd(13);
     tree->Draw("f:s>>h1[12](800,0,8000,1600, 0, 16000)", "sid==2&&ch==12", "colz");
     //c1->GetPad(8)->SetLogy(1);
 
     c1->cd(14);
     tree->Draw("f:s>>h1[13](800,0,8000,1600, 0, 16000)", "sid==2&&ch==13", "colz");
     //c1->GetPad(8)->SetLogy(1);
 
     c1->cd(15);
     tree->Draw("f:s>>h1[14](800,0,8000,1600, 0, 16000)", "sid==2&&ch==14", "colz");
     //c1->GetPad(8)->SetLogy(1);
 
     c1->cd(16);
     tree->Draw("f:s>>h1[15](800,0,8000,1600, 0, 16000)", "sid==2&&ch==15", "colz");
     //c1->GetPad(8)->SetLogy(1);
 */
     // 更新画布
     c1->Update();
     //file->Close(); // 关闭文件
 }
