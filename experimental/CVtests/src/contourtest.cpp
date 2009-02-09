
/**
 * Mew OpenCV experiment for finding contours.
 *
 * @author Pedro Martins
 */

#include <stdio.h>

#include <cv.h>
#include <highgui.h>
#include <math.h>


/*
 * Global variables
 */
IplImage * i;
IplImage* src;
int thresh;
CvMemStorage * storage;
CvSeq* contours;
CvCapture * cap;
int inited = 0;


/**
 * Retrieves a pixel from an IplImage. Very slow. See <INSERT NAME HERE> for
 * a more efficient way of accessing the Image data.
 * @param image
 * @param x
 * @param y
 * @param cIdx
 * @return
 */
uchar getPixel(IplImage * image, int x, int y, int cIdx) {
  return ((uchar*)(image->imageData + image->widthStep*y))[x*image->nChannels + cIdx];
}

/**
 * Sets the values of a particular pixel in image pic.
 * @param pic	The IplImage.
 * @param x
 * @param y
 * @param r
 * @param g
 * @param b
 */
void setpixel(IplImage * pic, unsigned long x, unsigned long y, short r, short g,
	      short b){
  // http://www710.univ-lyon1.fr/~bouakaz/OpenCV-0.9.5/docs/faq.htm
  CvPoint pt = {x,y};
  uchar* temp_ptr = &((uchar*)(pic->imageData + pic->widthStep*pt.y))[x*3];
  temp_ptr[0] = b;
  temp_ptr[1] = g;
  temp_ptr[2] = r;
}

/**
 * Event handler for updates to the trackbar.
 * @param pos
 */
void on_trackbar(int pos)
{
  IplImage* src1 = cvQueryFrame( cap );
  IplImage* src2 = cvQueryFrame( cap );

  // Create the image for blurring.
  src = cvCreateImage( cvGetSize(src1), IPL_DEPTH_8U, 3);
  cvSmooth( src1, src, CV_GAUSSIAN, 0, 0, 10, 10 );

  IplImage* dst = cvCreateImage( cvGetSize(src), IPL_DEPTH_8U, 3 );
  IplImage* dst2 = cvCreateImage( cvGetSize(src), IPL_DEPTH_8U, 1 );
  IplImage* contoured = cvCreateImage( cvGetSize(src), IPL_DEPTH_8U, 3 );
  IplImage* backup = cvCreateImage( cvGetSize(src) , IPL_DEPTH_8U, 3 );

  // change the threshold.
  cvThreshold(src, dst, thresh, 255, CV_THRESH_BINARY);
  cvSetImageCOI(dst, 1);
  cvCopy(dst, dst2, 0);
  //cvCopy(dst, backup, 0);

  int nContours = cvFindContours( dst2, storage, &contours, sizeof(CvContour),
				  CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, cvPoint(0,0) );
  //contours = cvApproxPoly( contours, sizeof(CvContour), storage, CV_POLY_APPROX_DP, 3, 1 );
  cvDrawContours( contoured, contours, CV_RGB(255,0,0),
		  CV_RGB(0,255,0), 1, 1, 8, cvPoint(0,0));
  printf("Value: %i\n", nContours);

  cvShowImage( "Camera", src );
  cvWaitKey(10);
  cvFlip( contoured, backup, 1);
  cvShowImage( "Image", backup );
  cvReleaseImage( &dst );
  cvReleaseImage( &dst2 );
  cvReleaseImage( &contoured );
}


/**
 * Main program
 * Finds contours from webcam.
 * @param argc
 * @param argv
 * @return
 */
int main (int argc, char ** argv) {

  cap = cvCreateCameraCapture( CV_CAP_ANY );
  storage = cvCreateMemStorage(0);
  contours = 0;

  /*
  const char* filename = argc >= 2 ? argv[1] : "test2.jpg";
  src = cvLoadImage( filename ); */

  cvNamedWindow( "Image", 1 );
  cvNamedWindow( "Camera", 1 );
  cvCreateTrackbar( "Threshold", "Image", &thresh, 255, on_trackbar );
  while(1) {
    on_trackbar(0);
    cvWaitKey(10);
  }

  cvWaitKey(0);

  cvReleaseCapture(&cap);

  return 0;

}

