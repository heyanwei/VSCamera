#pragma once

#include <string>

extern "C"
{
#include "include/libavcodec/avcodec.h"
#include "include/libavformat/avformat.h"
#include "include/libswscale/swscale.h"
}

class Yffmpeg
{
public:
	~Yffmpeg();

	AVFormatContext* _formatCtx;


	bool Init(std::string file);


};

