#pragma once

#include <string>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>

namespace image
{
    class HImage
    {
    private:
        std::string _name;
        std::string _image;
        cv::Mat _mat;

    public:
        HImage();
        ~HImage();

        //����ͼƬ�ľ���//
        bool LoadMat(std::string name, std::string image);
        //ʹ��opencv�Դ������Ź���//
        bool Resize(double x_scale, double y_scale);
        //�Լ�ʵ�����Ź���//
        bool MResize(double x_scale, double y_scale);
        //�Զ������ͼƬ//
        bool MCut(int x1, int y1, int x2, int y2);
        //��ʾ����//
        bool Show();
    };

} // namespace image