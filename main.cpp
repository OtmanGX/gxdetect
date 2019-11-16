#include "opencv2/objdetect.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "facedetect.h"
#include <iostream>
#include <stdio.h>
using namespace std;
using namespace cv;
//void detectAndDisplay(Mat frame, String shape="circle");

String window_name = "Capture - Face detection";
int main( void )
{
    //-- 1. Load the cascades
    if( !face_cascade.load( face_cascade_name ) ){
        printf("--(!)Error loading face cascade\n");
        return -1;
    };
    Mat frame;

    int mode=2; // 1-> Local image file Source ; 2-> Camera source
    if (mode==1) {
        // Read the image file
        Mat frame = imread("lena.tif");
        detectAndDisplay( frame, "rect" );
        //-- Show what you got
        imshow( window_name, frame );
        char c = (char)waitKey(0);
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

