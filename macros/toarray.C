#include "TError.h"
#include "TFile.h"
#include "TH2D.h"
#include "TImage.h"

Int_t main(Int_t argc, char**argv) {
    const char*file;
    Int_t resolution = 500;

    if (argc > 1) file = argv[1];
    else Error("main", "Need image file name as first argument. Has to exit.");
    if (argc < 2) return 1;
    if (argc > 2) sscanf(argv[2], "%d", &resolution);

    TImage*image = TImage::Open(file);
    TArrayD*array = image->GetArray(resolution, resolution, gWebImagePalette);
    TH2D*h2d = new TH2D(file, "title", resolution, 0, 1, resolution, 0, 1);
    for (Int_t i = 0; i < resolution; ++i) 
	for (Int_t j = 0; j < resolution; ++j) 
	    h2d->SetBinContent(i, j, array->At(i + resolution * j));

    TFile fimages("~/Myxa/mode/c++/root/images.root", "UPDATE");
    fimages.cd();
    h2d->Write(file, TObject::kOverwrite);
    fimages.Close();
    return 0;
}
