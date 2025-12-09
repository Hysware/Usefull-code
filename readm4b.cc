// 2025.12.9
// used to read *.m4b and change the format to root TH2I
void readm4b(const char *m4bfilename, const char *rootfilename)
{
    const int NX = 4096;
    const int NY = 4096;

    // 1. open m4b
    FILE *fp = fopen(m4bfilename, "rb");
    if (!fp) {
        std::cerr << "Cannot open m4b file: " << m4bfilename << std::endl;
        return;
    }

    // 2. create output file
    TFile *file = new TFile(rootfilename, "RECREATE");
    if (!file->IsOpen()) {
        std::cerr << "Cannot create ROOT file!" << std::endl;
        fclose(fp);
        return;
    }

    // 3. create TH2I
    TH2I *mat = new TH2I("spectrum", "Spectrum",
                         NX, 0, NX,   // X
                         NY, 0, NY); // Y

    // 4. read & write TH2I
    int count;
    for (int i = 1; i <= NX; ++i)          //
    {
        for (int j = 1; j <= NY; ++j)
        {
            size_t ret = fread(&count, sizeof(int), 1, fp);
            if (ret != 1) {
                std::cerr << "Unexpected end of file at ("
                          << i << "," << j << ")" << std::endl;
                break;
            }
            mat->SetBinContent(i, j, count);
        }
    }

    // 5. save
    mat->GetXaxis()->SetLimits(0, NX * 0.5);   // keV
    mat->GetYaxis()->SetLimits(0, NY * 0.5);   // keV
    mat->Write();

    // 6. close file
    file->Close();
    fclose(fp);

    std::cout << "Done: m4b → ROOT conversion finished." << std::endl;
}
