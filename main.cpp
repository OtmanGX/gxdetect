#include "opencv2/objdetect.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "facedetect.h"
#include "crop.h"
#include <iostream>
#include <stdio.h>

#define IMG_REP "imgs"


using namespace std;
String window_name = "Capture - Face detection";
int mode=1; // 1-> Local image file Source ; 2-> Camera source

int main( void )
{

    //-- 1. Load the cascades
    if( !face_cascade.load( face_cascade_name ) ){
        printf("--(!)Error loading face cascade\n");
        return -1;
    };
    Mat frame;

    if (mode==1) {
        // Read the image file
        ostringstream filename;
        filename << IMG_REP << "/lena.tif" ;
        Mat frame = imread(filename.str());
        if( frame.empty() )
            {
                printf(" --(!) Error while loading the image -- Break!");
                exit(1);
            }

    std::vector<Rect> faces = detectFaces( Mat(frame).clone(), "rect" );


    int filenumber; // Number of file to be saved
    filenumber++;
    cropAndSave(frame, faces, "lena");
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
            detectFaces( frame, "circle" );

            //-- Show what you got
            imshow( window_name, frame );
            char c = (char)waitKey(10);
            if( c == 27 ) { break; } // escape
        }
    }
    return 0;
}


