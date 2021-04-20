#include "gradients.h"

#include <opencv2/imgproc.hpp>

#include <cassert>

using OutputMat = cv::Mat;

using namespace cv;

static void getSobelKernels(OutputMat& kx, OutputMat& ky,
    int dx, int dy, int _ksize, bool normalize, int ktype)
{
    int i, j, ksizeX = _ksize, ksizeY = _ksize;
    if (ksizeX == 1 && dx > 0)
        ksizeX = 3;
    if (ksizeY == 1 && dy > 0)
        ksizeY = 3;

    //CV_Assert(ktype == CV_32F || ktype == CV_64F);
    kx = OutputMat(ksizeX, 1, CV_32FC1);  // ktype = 32F, 64F
    ky = OutputMat(ksizeX, 1, CV_32FC1);

    if (_ksize % 2 == 0 || _ksize > 31)
    {
        printf("The kernel size must be odd and not larger than 31\n");
        return;
    }
    std::vector<int> kerI(std::max(ksizeX, ksizeY) + 1);

    assert(dx >= 0 && dy >= 0 && dx + dy > 0);

    for (int k = 0; k < 2; k++)
    {
        Mat* kernel = k == 0 ? &kx : &ky;
        int order = k == 0 ? dx : dy;
        int ksize = k == 0 ? ksizeX : ksizeY;

        assert(ksize > order);

        if (ksize == 1)
            kerI[0] = 1;
        else if (ksize == 3)
        {
            if (order == 0)
                kerI[0] = 1, kerI[1] = 2, kerI[2] = 1;
            else if (order == 1)
                kerI[0] = -1, kerI[1] = 0, kerI[2] = 1;
            else
                kerI[0] = 1, kerI[1] = -2, kerI[2] = 1;
        }
        
        // TODO: support ksize > 3
        assert(ksize <= 3);

        Mat temp(kernel->rows, kernel->cols, CV_32S, &kerI[0]);
        double scale = !normalize ? 1. : 1. / (1 << (ksize - order - 1));
        temp.convertTo(*kernel, ktype, scale);
    }
}

static void getSobelKernels(int kerx[3], int ky[3],
    int dx, int dy, int ksize, int ktype)
{
    if (ksize > 3)
        ksize = 3;
    if (dx == 1 && dy == 0)
    {
        kerx[0] = 1;
        kerx[1] = 0;
        kerx[2] = -1;
    }
    else if (dx == 0 && dy == 1)
    {
        kerx[0] = 1;
        kerx[1] = 0;
        kerx[2] = -1;
    }
}

void sobel(const cv::Mat& src, cv::Mat& dst, int dx, int dy, int ksize, double scale, double delta, int borderType)
{
    int stype = src.type(), sdepth = CV_MAT_DEPTH(stype), cn = CV_MAT_CN(stype);
    int ddepth = sdepth;
    int dtype = CV_MAKE_TYPE(ddepth, cn);
    dst = OutputMat(src.size(), dtype);

    int ktype = std::max(CV_32F, std::max(ddepth, sdepth));

    Mat kx, ky;
    getSobelKernels(kx, ky, dx, dy, ksize, false, ktype);
    if (scale != 1)
    {
        // usually the smoothing part is the slowest to compute,
        // so try to scale it instead of the faster differentiating part
        if (dx == 0)
            kx *= scale;
        else
            ky *= scale;
    }

    float kerx[3];
    float kery[3];
    for (int i = 0; i < 3; i++)
    {
        kerx[i] = *kx.ptr<float>(i, 0);
        printf("%.2f ", kerx[i]);
    }
    printf("\n");

    for (int i = 0; i < 3; i++)
    {
        kery[i] = *ky.ptr<float>(i, 0);
        printf("%.2f ", kery[i]);
    }
    printf("\n");

    int z = 0;
    int bw = 1;  // border width
    int kerLen = 2 * bw;

    int imW = src.cols;
    int imH = src.rows;

    Mat imbd;
    cv::copyMakeBorder(src, imbd, bw, bw, bw, bw, 4);

    //sepFilter2D(src, dst, ddepth, kx, ky, Point(-1, -1), delta, borderType);
    int imWb = imW + kerLen;
    int imHb = imH + kerLen;
    Mat imfx(imHb, imW, CV_32FC1, cv::Scalar(0));
    for (int y = 0; y < imHb; y++)
    {
        float* pr = (float*)imfx.data + y * imW;
        for (int x = 0; x < imW; x++)
        {
            float s = 0.0;
            for (int i = 0; i < kerLen; i++)
            {
                s += imbd.data[y * imWb + x + i] * kerx[i];
            }
            pr[x] = s;
        }
    }

    // filter y component
    //dst = Mat(imH, imW, CV_8UC1, cv::Scalar(0));
    for (int x = 0; x < imW; x++)
    {
        for (int y = 0; y < imH; y++)
        {
            uchar* pr = (uchar*)dst.data + y * imW;
            float s = 0.0;
            for (int i = 0; i < kerLen; i++)
            {
                s += *((float*)imfx.data + (y + i) * imW + x) * kery[i];
            }
            pr[x] = uchar(MAX(MIN(fabs(s + 0.5f), 255), 0));
        }
    }

    sepFilter2D(src, dst, ddepth, kx, ky, Point(-1, -1), delta, borderType);
}

void spatialGradient(const cv::Mat& src, cv::Mat& dx, cv::Mat& dy, int ksize, int borderType)
{

}