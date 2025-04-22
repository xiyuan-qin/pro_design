#include<iostream>
#include<vector>
#include<string>

using namespace std;

/**
 * 离散方法存储时的数据结构为 X Y R G B
 * 其中 X Y 表示与上一帧相比，像素发生改变的二维坐标
 * 每个坐标各占 12 比特，R G B 表示当前像素的颜色，占 24 比特（每个颜色通道占 8 比特）。
 * 对于原本的密集型存储而言，数据量只需要考虑颜色的占用，其大小为：图像的像素数量 ×24 比特。
 * 
 * 输入格式
 * 输入的第一行，两个数 h,w，分别为帧的长与宽。
 * 接下来输入 2×h 行，表示两帧的图像。
 * 对于一张图而言，有 h 行，每行 3×w 个空格隔开的整数
 * 每相邻的 3 个数字表示一个像素的 R G B 颜色，其数值为 0 - 255
 * 第 i 个数隶属于当前行的第 ⌊(i−1)/3⌋+1 个像素的颜色描述。
 */

class Pixel {
public:
    //int x, y;// 坐标，每个12比特
    int r, g, b;// 颜色，每个8比特

    Pixel(int r, int g, int b) : r(r), g(g), b(b) {}
    Pixel() : r(0), g(0), b(0) {}
};

int main(){
    int height, width;
    cin >> height >> width;

    vector<vector<Pixel>> frame1(height, vector<Pixel>(width));
    vector<vector<Pixel>> frame2(height, vector<Pixel>(width));
    vector<vector<bool>> changed(height, vector<bool>(width, false));

    // 读取第一帧
    for(int i = 0 ; i < height ; i++){
        int r, g, b;
        for(int j = 0 ; j < width ; j++){
            cin >> r >> g >> b;
            frame1[i][j] = Pixel(r, g, b);
        }
    }
    // 读取第二帧
    for(int i = 0 ; i < height ; i++){
        int r, g, b;
        for(int j = 0 ; j < width ; j++){
            cin >> r >> g >> b;
            frame2[i][j] = Pixel(r, g, b);
        }
    }

    // 比较两帧
    for(int i = 0 ; i < height ; i++){
        for(int j = 0 ; j < width ; j++){
            if( frame1[i][j].r != frame2[i][j].r || 
                frame1[i][j].g != frame2[i][j].g || 
                frame1[i][j].b != frame2[i][j].b){
                changed[i][j] = true;
            }
        }
    }

    int original_size = height * width * 24; // 原始图像大小
    int compressed_size = 0; // 压缩后图像大小
    for(int i = 0 ; i < height ; i++){
        for(int j = 0 ; j < width ; j++){
            if(changed[i][j]){
                compressed_size += 24 + 24; // 坐标 + 颜色
            }
        }
    }

    cout << original_size - compressed_size << endl;
    return 0;
}