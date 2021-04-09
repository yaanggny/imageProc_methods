#include <opencv2/ximgproc.hpp>

#include <opencv2/imgproc.hpp>

#include <opencv2/highgui.hpp>

#ifndef VK_ESCAPE
#define VK_ESCAPE 0x1B
#endif // VK_ESCAPE

using namespace cv;
using namespace std;

void smoothDemo(const Mat& img)
{
	string wname = "DTSmooth";
	namedWindow(wname, WINDOW_NORMAL);

	int sc = 500;
	int ss = 10;
	int iteration = 2;

	createTrackbar("sigmaColor", wname, &sc, 1000);
	createTrackbar("sigmaSpace", wname, &ss, 50);
	int mode = 0;
	createTrackbar("RF/NC/IC", wname, &mode, 2);
	int color = 0;
	createTrackbar("color", wname, &color, 1);

	int key = 0;
	while (key != 'q' && key != VK_ESCAPE)
	{
		float scf = sc * 0.1f;
		Mat dst;
		Mat src;

		if (color == 0)
		{
			if(img.channels() > 1)
				cvtColor(img, src, COLOR_BGR2GRAY);
		}
		else
		{
			src = img;
		}

		int64 startTime = getTickCount();
		if (mode == 0)
		{
			ximgproc::dtFilter(src, src, dst, sc, ss, ximgproc::DTF_RF);
		}
		else if (mode == 1)
		{
			ximgproc::dtFilter(src, src, dst, sc, ss, ximgproc::DTF_NC);
		}
		else if (mode == 2)
		{
			ximgproc::dtFilter(src, src, dst, sc, ss, ximgproc::DTF_IC);
		}

		double time = (getTickCount() - startTime) / (getTickFrequency());
		printf("DTfilter: %f ms\n", time*1000.0);

		imshow(wname, dst);
		key = waitKey(10);
	}

	destroyWindow(wname);
}

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		printf("Usage: %s <img> <guide> <output>\n");
		return -1;
	}

	std::string imgFile(argv[1]);
	//std::string guideFile(argv[2]);

	Mat im = imread(imgFile);
	Mat guide = im;

	Mat dst;
	//ximgproc::dtFilter(guide, im, dst, 500, 5, 0);
	int imH = im.rows;
	int imW = im.cols;

	int imoW = 1024;

	cv::resize(im, im, cv::Size(imoW, imoW*imH / imW), 0, INTER_CUBIC);

	smoothDemo(im);

	return 0;
}
