#include "Yffmpeg.h"

#include "utils/log/easylogging++.h"

Yffmpeg::~Yffmpeg()
{
	LOG(INFO) << "释放Yffmpeg";

	avformat_close_input(&_formatCtx);
}

bool Yffmpeg::Init(std::string file)
{
	//注册所有的formats和codecs
	//av_register_all();

	//打开视频文件
	if (avformat_open_input(&_formatCtx, file.c_str(), NULL, NULL)<0)
	{
		LOG(ERROR) << "无法打开输入";
		return false;
	}

	if (avformat_find_stream_info(_formatCtx, NULL) < 0)
	{
		LOG(ERROR) << "无法找到流信息";
		return false;
	}

	// 打印输入输出格式的详细信息
	av_dump_format(_formatCtx, 0, file.c_str(), 0);


	
	
	return true;
}
