# 一、编程环境
- Visual Studio，Broland C++，Dev-C++
- 安装GLUT工具包
  - http://www.opengl.org/resources/libraries/glut/glutdlls37beta.zip
- 配置环境
  - https://blog.csdn.net/weixin_41962350/article/details/109345558
# 二、测试
- 创建一个控制台应用
- 输入以下代码做测试
```C++
#include <Windows.h>
#include <GL/glut.h>
void mydisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON);
	glVertex2f(-0.5, -0.5);
	glVertex2f(-0.5, 0.5);
	glVertex2f(0.5, 0.5);
	glVertex2f(0.5, -0.5);
	glEnd(); glFlush();
}
int main(int argc, char** argv) {
	glutCreateWindow("simple");
	glutDisplayFunc(mydisplay);
	glutMainLoop();
}
```
---
# 遇到的问题
### 1. 无法打开文件glut32.lib
- 【**最终解决方案**】把活动解决方案平台改为x86（在本地Windows调试器运行按钮的左边）
- 若上述【**最终解决方案**】不成功可以参考以下内容寻求解决方法（大概率会遇到问题2）
  - https://blog.csdn.net/weixin_41962350/article/details/109345558  
  - 在项目-VC++目录-库目录中添加包含glut32.lib文件的文件夹，例`D:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.34.31933\lib\x64;$(LibraryPath)`  
### 2. 库计算机类型“x86”与目标计算机类型“x64”冲突
- https://blog.csdn.net/Vikanill/article/details/89321539  
- 安装freeglut
