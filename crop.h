#ifndef CROP_H_INCLUDED
#define CROP_H_INCLUDED
#define IMG_CROP_REP "crop_imgs/"

using namespace std;
using namespace cv;

void cropAndSave(Mat frame, vector<Rect> rects, string imgname) {
    stringstream filetosave;
    for (int ic = 0; ic < rects.size(); ic++) // Iterate through all current elements (detected faces)
    {
    filetosave << IMG_CROP_REP << imgname <<"_" << "face" << ic << "_crop.jpg";
    /* Crop the original image to the defined ROI */
    cv::Mat crop = frame(rects[ic]);
    cv::imshow("crop", crop);
    cv::imwrite(filetosave.str(), crop);
    }

    cv::waitKey(0);
}

#endif // CROP_H_INCLUDED
