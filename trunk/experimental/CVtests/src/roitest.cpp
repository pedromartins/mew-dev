
/**
* Mew OpenCV experiment for using ROI
*
* @author Hok Shun Poon
*/

#include <stdio.h>

#include <cv.h>
#include <highgui.h>
#include <math.h>


/*
 * Global variables
 */
IplImage * image;


/**
 * Main program
 * Finds contours from webcam.
 * @param argc
 * @param argv
 * @return
 */
int main (int argc, char ** argv) {
	// Open the plant file.
	IplImage * before = cvLoadImage("res/plant.jpg");
	IplImage * after = cvCloneImage(before);

	if (before == NULL){
		return 1;
	}

	int x = 40;
	int y = 40;
	int width = 200;
	int height = 100;

	cvSetImageROI(after,cvRect(x,y,width,height));
	cvAddS(after,cvScalarAll(150),after);
	cvResetImageROI(after);

	cvNamedWindow("Before");
	cvNamedWindow("After");

	cvShowImage("Before",before);
	cvShowImage("After",after);

	cvWaitKey(0);

	cvDestroyAllWindows();

	return 0;

}

