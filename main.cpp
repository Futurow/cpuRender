#include "graphics.h"

int main()
{
    initgraph(640, 480);   // 初始化，显示一个窗口
    circle(320, 240, 120); // 画圆
    getch();               // 等待输入
    closegraph();          // 关闭图形界面
    return 0;
}