#include "gradients.h"

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        printf("Usage: %s <srcImage>\n", argv[0]);
        return -1;
    }

    Mat src = cv::imread(argv[1], IMREAD_GRAYSCALE);
    Mat dstRef, dst;
    cv::Sobel(src, dstRef, -1, 1, 0, 1);
    sobel(src, dst, 1, 0, 1);

    Mat dstRef3, dst3;
    cv::Sobel(src, dstRef3, -1, 1, 0, 3);
    sobel(src, dst3, 1, 0, 3);

    return 0;
}
