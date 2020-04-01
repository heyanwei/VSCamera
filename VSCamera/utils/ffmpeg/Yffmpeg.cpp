#include "Yffmpeg.h"

#include "utils/log/easylogging++.h"

Yffmpeg::~Yffmpeg()
{
	LOG(INFO) << "�ͷ�Yffmpeg";

	avformat_close_input(&_formatCtx);
}

bool Yffmpeg::Init(std::string file)
{
	AVPacket* pkt = av_packet_alloc();
	if (!pkt)
	{
		LOG(ERROR) << "�޷�����av��";
		return false;
	}

	// ���ҽ�����
	AVCodec *codec = avcodec_find_decoder(AV_CODEC_ID_MPEG1VIDEO);
	if (!codec) 
	{
		LOG(ERROR) << "�Ҳ���������";
		return false;
	}

	// ��ʽ��������
	AVCodecParserContext* parser = av_parser_init(codec->id);
	if (!parser)
	{
		LOG(ERROR) << "��ʽ��������ʧ��";
		return false;
	}

	AVCodecContext *c = avcodec_alloc_context3(codec);
	if (!c)
	{
		LOG(ERROR) << "��������ʧ��";
		return false;
	}

	if (avcodec_open2(c, codec, NULL) < 0)
	{
		LOG(ERROR) << "��������ʧ��";
		return false;
	}

	FILE* f;
	errno_t err= fopen_s(&f, file.c_str(),"rb");
	if (err != 0)
	{
		LOG(ERROR) << "�ļ���ʧ��";
		return false;
	}

	AVFrame* frame = av_frame_alloc();
	if (!frame) 
	{
		LOG(ERROR) << "����֡ʧ��";
		return false;
	}

	uint8_t inbuf[INBUF_SIZE + AV_INPUT_BUFFER_PADDING_SIZE];
	uint8_t* data;
	size_t data_size;	
	int ret;	

	while (!feof(f))
	{
		data_size = fread(inbuf, 1, INBUF_SIZE, f);
		if (!data_size)
		{
			break;
		}
		data = inbuf;
		while (data_size > 0)
		{
			ret = av_parser_parse2(parser, c, &pkt->data, &pkt->size,
				data, data_size, AV_NOPTS_VALUE, AV_NOPTS_VALUE, 0);
			if (ret < 0)
			{
				LOG(ERROR) << "ת��ʧ��";
				return false;
			}
			data += ret;
			data_size -= ret;

			if (pkt->size)
			{
				decode(c, frame, pkt, "a.avi");
			}
		}
		decode(c, frame, NULL, "a.avi");
	}
	
	return true;
}
