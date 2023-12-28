# 一、基本知识
### （一）回调函数callback function
- 用户定义用来处理特定事件的函数
  - `glutMainLoop();`
    - Window: resize
    - Mouse: click one or more buttons
    - Motion: move mouse
    - Keyboard: press or release a key
    - Idle: nonevent

### （二）鼠标
```C++
void OnMyMouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		/*自定义*/
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		/*自定义*/
	}


	mydisplay();
}

int main(int argc, char** argv) {
	/*配置*/

	// set OpenGL state
	init();
	// display callback
	glutDisplayFunc(mydisplay);
	// 主函数增加注册鼠标事件函数
	glutMouseFunc(OnMyMouse);

	/*配置*/
}
```
- `glutMouseFunc(mymouse)`
- `void mymouse(GLint button, GLint state, GLint x, GLint y)`
  - `button`的值可能是
    - `GLUT_LEFT_BUTTON`
    - `GLUT_MIDDLE_BUTTON`
    - `GLUT_RIGHT_BUTTON`
  - `state`表示相应按钮的状态
    - `GL_UP`
    - `GL_DOWN`
  - x, y表示在窗口中的位置

#### 位置
- 屏幕坐标以像素为基本单位，原点在左上角
- OpenGL坐标系原点在左下角

#### 鼠标运动函数
- `glutMotionFunc((void*)func(int x, int y));`
- `glutPassiveMotionFunc((void*)func(int x, int y));`

- Active motion是指鼠标移动并且有一个鼠标键被按下
- Passive motion是指当鼠标移动时，并没有鼠标键按下

### （三）键盘
```C++
void OnMyKey(unsigned char key, int x, int y) {
	// 写法一
	switch (key) {
	case 'w':
		/*处理*/
		break;
	case 'm':
		/*处理*/
		break;
	}

	// 写法二
	if (key == 'Q' | key == 'q') exit(0);


	mydisplay();
}

int main(int argc, char** argv) {
	/*配置*/

	// set OpenGL state
	init();
	// display callback
	glutDisplayFunc(mydisplay);
	// 主函数增加注册键盘事件函数
	glutKeyboardFunc(OnMyKey);

	/*配置*/
}
```
- `glutKeyboardFunc(mykey)`
- `void mykey(Glubyte key, GLint x, GLint y)`
  - `key`返回键盘上被按下键的ASCII码和鼠标位置
  - 【注意】在GLUT中不把释放键作为一个事件
  - x, y表示鼠标坐标

#### 键盘相关函数
- GLUT在glut.h中定义了特殊按键：
  - 功能键1：GLUT_KEY_F1
  - 向上方向键：GLUT_KEY_UP
  - `if (key == GLUT_KEY_F1) ...`
- `glutGetModifiers(...)`探测是否按下了
  - `GLUT_ACTIVE_SHIFT`
  - `GLUT_aCTIVE_CTRL`
  - `GLUT_ACTIVE_ALT`

### （四）窗口形状的改变
内容大小变化、长宽比例变化、跟着窗口变化

#### 窗口改变的回调函数
```C++
/*保持长宽比率不变*/
void myreshape(GLint w, GLint h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h) {
		gluOrtho2D(-2.0, 2.0, -2.0 * (GLfloat)h / (GLfloat)w, 2.0 * (GLfloat)h / (GLfloat)w);
	}
	else {
		gluOrtho2D(-2.0 * (GLfloat)w / (GLfloat)h, 2.0 * (GLfloat)w / (GLfloat)h, -2.0, 2.0);
	}
	glMatrixMode(GL_MODELVIEW);
}
```
- `glutReshapeFunc(myreshape)`
- `void myreshape(GLint w, GLint h)`

# 二、实验内容
编写交互程序，要求：  
1. 显示基本线段、三角形、四边形、多边形等图形
2. 用户可以通过按键来控制绘制的图形类型和颜色。如：t绘制三角形，r图形改为红色
3. 使用键盘控制图形的位置
4. 用户可以通过点击鼠标左右键来调整图形的类型和颜色

[参考代码](Code/example/test03.cpp)，如下：
```C++
// test00.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <GL/glut.h>

void myDisplay();
void myKeyboard(unsigned char key, int x, int y);
void myReshape(GLint w, GLint h);


struct mycolor {
	float R; float G; float B;
};

struct mycolor MyColor;


int main(int argc, char** argv) {
	MyColor.R = 1.0; MyColor.G = 1.0; MyColor.B = 1.0;

	glutCreateWindow("ÊµÑé2");

	glutDisplayFunc(myDisplay);
	glutKeyboardFunc(&myKeyboard);
	glutReshapeFunc(&myReshape);

	glutMainLoop();
}


void myDisplay() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(MyColor.R, MyColor.G, MyColor.B);

	glBegin(GL_POLYGON);
	glVertex2f(-0.5, -0.5);
	glVertex2f(-0.5, 0.5);
	glVertex2f(0.5, 0.5);
	glVertex2f(0.5, -0.5);
	glEnd();

	glFlush();
}


void myKeyboard(unsigned char key, int x, int y) {
	switch (key) {
	case'R':
	case 'r':
		MyColor.R = 1.0;
		MyColor.G = 0.0;
		MyColor.B = 0.0;
		break;

	case'G':
	case 'g':
		MyColor.R = 0.0;
		MyColor.G = 1.0;
		MyColor.B = 0.0;
		break;

	case'B':
	case 'b':
		MyColor.R = 0.0;
		MyColor.G = 0.0;
		MyColor.B = 1.0;
		break;
	case'Q':
	case 'q':
		exit(0);
	}

	myDisplay();
}


void myReshape(GLint w, GLint h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		gluOrtho2D(-2.0, 2.0, -2.0 * (GLfloat)h / (GLfloat)w,
			2.0 * (GLfloat)h / (GLfloat)w);
	else gluOrtho2D(-2.0 * (GLfloat)w / (GLfloat)h,
		2.0 * (GLfloat)w / (GLfloat)h, -2.0, 2.0);
	glMatrixMode(GL_MODELVIEW);
}
```

# 三、实验过程

---
# 遇到的问题
### 1. 能运行，界面全为白色
- 原因：没有刷新绘图命令队列
- 解决方法：`mydisplay()`函数最后加上`glFlush();`

### 2. 鼠标/键盘事件无响应
- 原因：改变后没有绘图
- 解决方法：在`mykeyboard()`和`mymouse()`函数最后都加上`mydisplay();`
