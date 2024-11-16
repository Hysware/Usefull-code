// run with: root -l plotFunWithBins.C
// Function： divide a continuous function with bins.
// 2024.11.16
#include <TF1.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <iostream>

void plotAtomBg() {
    // 定义一个函数
    TF1 *exp = new TF1("exp", "-1.24345+2743/(84.886*sqrt(3.1415926535/(4*log(2))))*exp(-4*log(2)*(x-100.5)^2/84.885^2)", 23, 217);
    //gaussFunc->SetParameters(1.0, 0.0, 1.0);  // 参数：常数项=1，均值=0，标准差=1

    // 设置直方图参数

     // 设置 bin 数目
    int nBins = 19;
    double xMin = 23;
    double xMax = 213;
    double binWidth = (xMax - xMin) / nBins;
    TCanvas* canvas = new TCanvas("canvas", "Data Plot with Fit", 800, 600);
    // 创建 TH1F 直方图来存储 bin 的数据
    TH1F *hist = new TH1F("hist", "Binned Fit Result;X-axis;Y-axis", nBins, xMin, xMax);

    // 填充 TH1F，每个 bin 使用函数在 bin 中心的值
    for (int i = 1; i <= nBins; ++i) {
        double xBinCenter = hist->GetBinCenter(i);
        double yBinValue = exp->Eval(xBinCenter);  // 在 bin 中心评估函数值
        hist->SetBinContent(i, yBinValue);  // 设置 bin 的内容
        //std::cout << "Bin " << i << "\tCenter: " << xBinCenter << "\tValue: " << yBinValue << std::endl;
        std::cout << i << "\t" << xBinCenter << "\t" << yBinValue << std::endl;
    }

    // 设置直方图样式
    hist->SetLineColor(3);
    hist->SetLineWidth(2);
    exp->Draw();
    // 绘制直方图为阶梯状
    hist->Draw("HIST same");  // "HIST" 选项将绘制阶梯状图形

    // 更新画布
    canvas->Update();
    // 可以使用 canvas->SaveAs("output.png"); 来保存图片

}
