#include <opencv2/opencv.hpp>
#include "MotionDenoiser.h"



int main(const int argc, const char* argv[])
{
	if (argc < 2)
	{
		printf("Usage: %s <videoFile> [<outVideoFile>]\n", argv[0]);
		return -1;
	}

	std::string videoFile(argv[1]);
	std::string outVideoFile = videoFile + "_out.avi";
	if (argc > 2)
		outVideoFile = std::string(argv[2]);

	MotionDenoiser denoiser(videoFile.c_str());
	denoiser.Execute();
	denoiser.SaveResult(outVideoFile.c_str());

	return 0;
}