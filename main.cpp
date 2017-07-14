
//Exemplo 2.9

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <fstream>

IplImage* doCanny(
    IplImage* in,
    double    lowThresh,
    double    highThresh,
    double    aperture)
{
    if (in->nChannels != 1)
        return(0); // Canny only handles gray scale images
    IplImage* out = cvCreateImage(
        cvGetSize( in ),
        in->depth, //IPL_DEPTH_8U,
        1);
    cvCanny( in, out, lowThresh, highThresh, aperture );
    return( out );
};


int main( int argc, char** argv ) {

    cvNamedWindow( "Normal", CV_WINDOW_AUTOSIZE );
    cvNamedWindow( "Canny", CV_WINDOW_AUTOSIZE );

    CvCapture* capture;
    if( argc == 1 ) {
        capture = cvCreateCameraCapture( 0 );
    } else {
        capture = cvCreateFileCapture( argv[1] );
    }
    //assert( capture != NULL );
    if( capture == NULL ) {
	if( argc == 1 )
		printf( "Nao pude abrir stream de video\n" );
	else
		printf( "Nao pude abrir arquivo de video\n" );
	exit( 1 );
    }

    /*double fps = cvGetCaptureProperty (
				       capture,
				       CV_CAP_PROP_FPS
				       );
    printf("fps=%d\n",(int)fps);
    */
    CvSize size = cvSize(
			 (int)cvGetCaptureProperty( capture, CV_CAP_PROP_FRAME_WIDTH),
			 (int)cvGetCaptureProperty( capture, CV_CAP_PROP_FRAME_HEIGHT)
			 );
    printf( "frame (w, h) = (%d, %d)\n", size. width, size. height );

    IplImage* frame;
    IplImage* frame_gry;
    IplImage* frame_cny;
    while( 1 ) {
        frame = cvQueryFrame( capture );
        frame_gry = cvCreateImage( cvSize( frame->width,frame->height ), frame->depth, 1);
        cvCvtColor(frame, frame_gry ,CV_BGR2GRAY);
        frame_cny = doCanny( frame_gry, 50, 100, 3 );
        if( !frame ) break;
        cvShowImage("Normal", frame );
        //cvShowImage( "Canny", frame_cny );
        char c = cvWaitKey(10);
        if( c == 27 ) break;
    }
    while( 1 ) {
        frame = cvQueryFrame( capture );
        frame_gry = cvCreateImage( cvSize( frame->width,frame->height ), frame->depth, 1);
        cvCvtColor(frame, frame_gry ,CV_BGR2GRAY);
        frame_cny = doCanny( frame_gry, 50, 100, 3 );
        if( !frame ) break;
        cvShowImage("Normal", frame );
        cvShowImage( "Canny", frame_cny );
        char c = cvWaitKey(10);
        if( c == 27 ) break;
    }
    cvReleaseImage(&frame_gry);
    cvReleaseImage(&frame_cny);
    cvReleaseCapture( &capture );
    cvDestroyWindow( "Normal" );
    cvDestroyWindow( "Canny" );
}
