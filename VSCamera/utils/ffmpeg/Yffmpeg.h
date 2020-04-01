#pragma once

#include <string>

extern "C"
{
#include "include/libavcodec/avcodec.h"
#include "include/libavformat/avformat.h"
#include "include/libswscale/swscale.h"
}

#define INBUF_SIZE 4096

class Yffmpeg
{
public:
	~Yffmpeg();

	AVFormatContext* _formatCtx;


	bool Init(std::string file);

private:
	void decode(AVCodecContext* dec_ctx, AVFrame* frame, AVPacket* pkt,
		const char* filename);

};

