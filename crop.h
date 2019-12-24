#ifndef CROP_H_INCLUDED
#define CROP_H_INCLUDED
#define IMG_CROP_REP "crop_imgs/"
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
using namespace std;
using namespace cv;

void cropAndSave(Mat frame, vector<Rect> rects, int imgname) {
    mkdir(IMG_CROP_REP,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    stringstream filetosave;
    cv::Mat crop;
    for (int ic = 0; ic < rects.size(); ic++) // Iterate through all current elements (detected faces)
    {
    filetosave.str("");
    filetosave << IMG_CROP_REP << "image"<< imgname <<"_"<<"face" << ic << "_crop.jpg";
    /* Crop the original image to the defined ROI */
    crop = frame(rects[ic]);
    cv::imshow(filetosave.str(), crop);
    cv::imwrite(filetosave.str(), crop);
    filetosave.clear();
    }
    waitKey(0);
}

#endif // CROP_H_INCLUDED
