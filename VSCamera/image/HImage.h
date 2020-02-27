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

        //加载图片的矩阵//
        bool LoadMat(std::string name, std::string image);
        //使用opencv自带的缩放功能//
        bool Resize(double x_scale, double y_scale);
        //自己实现缩放功能//
        bool MResize(double x_scale, double y_scale);
        //自定义剪切图片//
        bool MCut(int x1, int y1, int x2, int y2);
        //显示矩阵//
        bool Show();
    };

} // namespace image