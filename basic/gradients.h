#ifndef __GRADIENTS_H
#define __GRADIENTS_H

#include <opencv2/core.hpp>

void sobel(const cv::Mat& src, cv::Mat& dst, int dx, int dy, int ksize, double scale=1.0, double delta=0, int borderType=4);
void spatialGradient(const cv::Mat& src, cv::Mat& dx, cv::Mat& dy, int ksize, int borderType);

#endif /* __GRADIENTS_H */
