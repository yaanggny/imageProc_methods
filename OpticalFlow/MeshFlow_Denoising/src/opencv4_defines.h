#ifndef __OPENCV4_DEFINES_H
#define __OPENCV4_DEFINES_H

#include <opencv2/core/version.hpp>

#if CV_VERSION_MAJOR > 3

#define CV_AA cv::LINE_AA
#define CV_CAP_PROP_FPS cv::CAP_PROP_FPS
#define CV_RGB2GRAY cv::COLOR_RGB2GRAY
#define CV_BGR2GRAY cv::COLOR_BGR2GRAY
#define CV_TERMCRIT_ITER cv::TermCriteria::MAX_ITER
#define CV_TERMCRIT_EPS cv::TermCriteria::EPS
#define cvTermCriteria cv::TermCriteria
#define CV_LMEDS cv::LMEDS
#define CV_FOURCC cv::VideoWriter::fourcc
#endif


#endif /* __OPENCV4_DEFINES_H */
