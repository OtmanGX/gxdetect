#include "opencv2/objdetect.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "facedetect.h"
#include <iostream>
#include <stdio.h>

String window_name = "Capture - Face detection";

int main( void )
{
int filenumber; // Number of file to be saved
string filename;
    //-- 1. Load the cascades
    if( !face_cascade.load( face_cascade_name ) ){
        printf("--(!)Error loading face cascade\n");
        return -1;
    };
    Mat frame;

    int mode=1; // 1-> Local image file Source ; 2-> Camera source
    if (mode==1) {
        // Read the image file
        Mat frame = imread("lena.tif");
        if( frame.empty() )
            {
                printf(" --(!) Error while loading the image -- Break!");
                exit(1);
            }
        detectAndDisplay( frame, "rect" );

          /* Set Region of Interest */
std::vector<Rect> faces;
    Mat frame_gray;

    Mat res;
    Mat gray;
    string text;
    stringstream sstm;

    cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
    equalizeHist(frame_gray, frame_gray);

    // Detect faces
    face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));

    // Set Region of Interest
    cv::Rect roi_b;
    cv::Rect roi_c;

    size_t ic = 0; // ic is index of current element
    int ac = 0; // ac is area of current element

    size_t ib = 0; // ib is index of biggest element
    int ab = 0; // ab is area of biggest element

    for (ic = 0; ic < faces.size(); ic++) // Iterate through all current elements (detected faces)

    {
        roi_c.x = faces[ic].x;
        roi_c.y = faces[ic].y;
        roi_c.width = (faces[ic].width);
        roi_c.height = (faces[ic].height);

        ac = roi_c.width * roi_c.height; // Get the area of current element (detected face)

        roi_b.x = faces[ib].x;
        roi_b.y = faces[ib].y;
        roi_b.width = (faces[ib].width);
        roi_b.height = (faces[ib].height);

        ab = roi_b.width * roi_b.height; // Get the area of biggest element, at beginning it is same as "current" element

        if (ac > ab)
        {
            ib = ic;
            roi_b.x = faces[ib].x;
            roi_b.y = faces[ib].y;
            roi_b.width = (faces[ib].width);
            roi_b.height = (faces[ib].height);
        }

    }


// Form a filename

        filename = "";
        stringstream ssfn;
        ssfn << filenumber << ".jpg";
        filename = ssfn.str();
        filenumber++;

        imwrite(filename, gray);

        Point pt1(faces[ic].x, faces[ic].y); // Display detected faces on main window
        Point pt2((faces[ic].x + faces[ic].height), (faces[ic].y + faces[ic].width));
        rectangle(frame, pt1, pt2, Scalar(0, 255, 0), 2, 8, 0);

    /* Crop the original image to the defined ROI */

    cv::Mat crop = frame(roi_b);
    cv::imshow("crop", crop);

        cv::waitKey(0);

   // cv::imwrite("noises_cropped.png", crop);
        //-- Show what you got
    //    imshow( window_name, frame );

        return 0;
    } else if (mode==2) {
        //-- 2. Read the video stream
        VideoCapture capture;
        capture.open(-1);
        if ( ! capture.isOpened() ) { printf("--(!)Error opening video capture\n"); return -1; }
        while ( capture.read(frame) )
        {
            if( frame.empty() )
            {
                printf(" --(!) No captured frame -- Break!");
                break;
            }
            //-- 3. Apply the classifier to the frame
            detectAndDisplay( frame, "circle" );
            //-- Show what you got
            imshow( window_name, frame );
            char c = (char)waitKey(10);
            if( c == 27 ) { break; } // escape
        }
    }
    return 0;
}

