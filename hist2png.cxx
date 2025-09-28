// 将TH1*转换为png 并保存起来

// g++ hist2png.cxx -o hist2png $(root-config --cflags --glibs)
// ./hist2png *.root 


#include <TFile.h>
#include <TKey.h>
#include <TClass.h>
#include <TH1.h>
#include <TCanvas.h>
#include <TSystem.h>

#include <iostream>
#include <string>

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "用法: " << argv[0] << " file.root" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    TFile *f = TFile::Open(filename.c_str());
    if (!f || f->IsZombie()) {
        std::cerr << "无法打开文件: " << filename << std::endl;
        return 1;
    }

    // 获取文件名（去掉路径和 .root 后缀）
    std::string base = gSystem->BaseName(filename.c_str());
    if (base.size() > 5 && base.substr(base.size() - 5) == ".root") {
        base = base.substr(0, base.size() - 5);
    }

    // 创建输出目录 ./png/base/
    std::string outdir = "./png/";
    gSystem->Exec(("mkdir -p " + outdir).c_str());

    // 遍历所有对象
    TIter next(f->GetListOfKeys());
    TKey *key;
    while ((key = (TKey*)next())) {
        TObject *obj = key->ReadObj();
        if (obj->InheritsFrom("TH1")) {
            TH1 *h = dynamic_cast<TH1*>(obj);
            if (!h) continue;

            // 只处理 1D 直方图
            if (h->GetDimension() != 1) continue;

            // 建立画布并画图
            TCanvas *c = new TCanvas("c","c",800,600);
            h->Draw();

            // 输出文件名
            std::string outname = outdir + "/" + base + h->GetName() + ".png";
            c->SaveAs(outname.c_str());
            delete c;

            std::cout << "已导出: " << outname << std::endl;
        }
    }

    f->Close();
    return 0;
}
