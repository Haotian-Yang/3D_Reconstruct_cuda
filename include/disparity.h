#ifndef DISPARITY_H
#define DISPARITY_H

#include <common.h>
#include <rectify.h>

using namespace cv;

class Disparity{
public:
    cv::Mat disparity;
private:
    int P1;
    int P2;
    int preFilterCap;
    int SADWindowSize;
    int speckleWindowSize;
    int speckleRange;
    int maxDisparityofImg; // image.size / max = max pixel difference of disparity

#if WLS_FILTER
    int wls_lambda;
    float wls_sigma;
#endif

private:
    void callSGBM(cv::Mat& left, cv::Mat& right, cv::Mat& disp);
public:

#if WLS_FILTER
    Disparity():P1(8),P2(32),SADWindowSize(9),
        speckleRange(2),speckleWindowSize(1600),maxDisparityofImg(10),
        wls_lambda(1000),wls_sigma(1.5){}

    void setLambda(int lambda);
    void setSigma(float sigma);
#else
    Disparity():P1(8),P2(32),SADWindowSize(9),
        speckleRange(2),speckleWindowSize(1600),maxDisparityofImg(10){}
#endif


#if GPU_ON
    bool computeDisparity_cuda(Rectify recity); // TODO first
#else
    bool computeDisparity(Rectify rectify);
#endif

    void setP1(int P1);
    void setP2(int P2);
    void setPreFilterCap(int PFcap);
    void setSADWindowSize(int sad_size);
    void setSpeckleWindowSize(int speckle_size);
    void setSpeckleRange(int speckle_range);
    void setmaxDisparityofImg(int maxDisparityRatio);

    int getP1();
    int getP2();
};



#endif
