#include "Yffmpeg.h"

#include "utils/log/easylogging++.h"

Yffmpeg::~Yffmpeg()
{
	LOG(INFO) << "�ͷ�Yffmpeg";

	avformat_close_input(&_formatCtx);
}

bool Yffmpeg::Init(std::string file)
{
	//ע�����е�formats��codecs
	//av_register_all();

	//����Ƶ�ļ�
	if (avformat_open_input(&_formatCtx, file.c_str(), NULL, NULL)<0)
	{
		LOG(ERROR) << "�޷�������";
		return false;
	}

	if (avformat_find_stream_info(_formatCtx, NULL) < 0)
	{
		LOG(ERROR) << "�޷��ҵ�����Ϣ";
		return false;
	}

	// ��ӡ���������ʽ����ϸ��Ϣ
	av_dump_format(_formatCtx, 0, file.c_str(), 0);


	
	
	return true;
}
