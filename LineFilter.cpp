//
// Created by yht on 04/10/15.
//

#include "LineFilter.h"

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;

LineFilter::LineFilter(const cv::Mat &depthMatrix, const cv::Mat &imageMatrix)
:PointCloudBuilder(depthMatrix, imageMatrix)
{

}

void LineFilter::buildPointCloud() {
    Mat dst,cdst;
    Canny(imageMat, dst, 50, 200, 3);
	cvtColor(depthMat,cdst, COLOR_GRAY2BGR);

    vector<Vec4i> lines;
    HoughLinesP(dst, lines, 1, CV_PI/180, 50, 50, 10 );
    for( size_t i = 0; i < lines.size(); i++ )
    {
        Vec4i l = lines[i];
        line( cdst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,0), 5, CV_AA);
    }
	cvtColor(cdst,depthMat, COLOR_RGB2GRAY);
	PointCloudBuilder::buildPointCloud();
}
