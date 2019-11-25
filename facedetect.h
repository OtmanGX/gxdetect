#ifndef FACEDETECT_H_INCLUDED
#define FACEDETECT_H_INCLUDED
using namespace std;
using namespace cv;

String face_cascade_name = "haarcascades/haarcascade_frontalface_alt.xml";
CascadeClassifier face_cascade;

std::vector<Rect> detectAndDisplay(Mat frame,String shape="rect")
{
    std::vector<Rect> faces;
    Mat frame_gray;
    cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );
    //-- Detect faces
    face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(30, 30) );
    for ( size_t i = 0; i < faces.size(); i++ )
    {
        if (shape.compare("circle")==0) {
            Point center( faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2 );
            ellipse( frame, center, Size( faces[i].width/2, faces[i].height/2 ), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );
        } else if (shape.compare("rect")==0) {
            Point pt1(faces[i].x, faces[i].y); // Display detected faces on main window - livestream from camera
            Point pt2((faces[i].x + faces[i].height), (faces[i].y + faces[i].width));
            rectangle(frame, pt1, pt2, Scalar(0, 255, 0), 2, 8, 0);
        }
        Mat faceROI = frame_gray( faces[i] );
    }
    return faces;
}


#endif // FACEDETECT_H_INCLUDED
