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
- 特殊按键的响应函数是`glutSpecialFunc`
  - 实现函数的格式是`void SpecialKey(GLint key,GLint x,GLint y)；`
  
	```C++
	#include"freeglut.h"
  
	GLfloat xOffset=0.0f,yOffset=0.0f;
	 
	void myDisplay() {
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);	
		glColor3f(0,1,0);

		glViewport(xOffset,yOffset,400,400);
		glRectf(160,160,240,240);
	 
		glutSwapBuffers();
	}
	 
	void Init() {	
		glClearColor(1,1,1,1);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0,400,0,400);
	}
	 
	void SpecialKey(GLint key,GLint x,GLint y) {
		if(key==GLUT_KEY_UP) {
			yOffset+=10;
		}	
		if(key==GLUT_KEY_LEFT) {
			xOffset-=10;
		}
		if(key==GLUT_KEY_DOWN) {
			yOffset-=10;
		}
		if(key==GLUT_KEY_RIGHT) {
			xOffset+=10;
		}
		myDisplay();
	}
	 
	int main(int argc, char *argv[]) {      
		glutInit(&argc, argv);   //初始化GLUT  
		glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);    
		glutInitWindowPosition(500, 200);      
		glutInitWindowSize(400, 400);      
		glutCreateWindow("OpenGL");   
		Init();   
		glutDisplayFunc(&myDisplay);   //回调函数   
		glutSpecialFunc(&SpecialKey);
		glutMainLoop();         
	}   
	```
  
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
### 1. 完整代码
```C++
#include<stdio.h>
#include<gl/glut.h>
#include<math.h>


void init();
void mydisplay();
void mykeyboard(unsigned char key, int x, int y);
void mymouse(int button, int state, int x, int y);
void myreshape(GLint w, GLint h);

struct MyColor {
	float R;
	float G;
	float B;
};

struct MyColor mycolor;
int graph, color;


void init() {
	glClearColor(0.0, 0.0, 0.0, 1.0);

	graph = 1;
	color = 1;
	mycolor.R = 1.0;
	mycolor.G = 0.0;
	mycolor.B = 0.0;
}

// 显示基本线段、三角形、四边形、多边形等图形
void mydisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(mycolor.R, mycolor.G, mycolor.B);

	// 三角形
	if (graph == 1) {
		glBegin(GL_TRIANGLES);
		glVertex2f(-0.5, -0.5);
		glVertex2f(0.5, -0.5);
		glVertex2f(0.0, 0.5);
		glEnd();
		printf("三角形");
	}
	// 四边形
	else if (graph == 2) {
		glBegin(GL_QUADS);
		glVertex2f(-0.5, -0.5);
		glVertex2f(-0.5, 0.5);
		glVertex2f(0.5, 0.5);
		glVertex2f(0.5, -0.5);
		glEnd();
		printf("四边形");
	}
	// 圆形
	else if (graph == 3) {
		int n = 360;  //圆绘制次数
		float PI = 3.1415926f;
		float R = 0.8f;  //半径
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f(0.0, 0.0);  //添加圆心
		for (int i = 0; i <= n; i++) {
			glVertex2f(R * sin(2 * PI * i / n), R * cos(2 * PI * i / n));   //定义顶点
		}
		glEnd();
		printf("圆形");
	}

	// 红色
	if (color == 1) {
		mycolor.R = 1.0;
		mycolor.G = 0.0;
		mycolor.B = 0.0;
		printf("红色\n");
	} 
	// 绿色
	else if (color == 2) {
		mycolor.R = 0.0;
		mycolor.G = 1.0;
		mycolor.B = 0.0;
		printf("绿色\n");
	} 
	// 蓝色
	else if (color == 3) {
		mycolor.R = 0.0;
		mycolor.G = 0.0;
		mycolor.B = 1.0;
		printf("蓝色\n");
	}

	// 刷新绘图命令队列
	glFlush();
}

// 使用键盘控制图形的位置
// 用户可以通过按键来控制绘制的图形类型和颜色
// 如：t绘制三角形，r图形改为红色
void mykeyboard(unsigned char key, int x,int y) {
	switch (key) {
	// T/t绘制三角形
	case 'T': case 't':
		graph = 1;
		printf("T/t\n");
		break;
	// Q/q绘制四边形
	case 'Q': case 'q':
		graph = 2;
		printf("Q/q\n");
		break;
	// C/c绘制圆形
	case 'C': case 'c':
		graph = 3;
		printf("C/c\n");
		break;
	// R/r改为红色
	case 'R': case 'r':
		color = 1;
		printf("R/r\n");
		break;
	// G/g改为绿色
	case 'G': case 'g':
		color = 2;
		printf("G/g\n");
		break;
	// B/b改为蓝色
	case 'B': case 'b':
		color = 3;
		printf("B/b\n");
		break;
	}

	mydisplay();
}

// 用户可以通过点击鼠标左右键来调整图形的类型和颜色
void mymouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		printf("左键\n");
		if (graph == 3) {
			graph = 1;
		}else{
			graph += 1;
		}
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		printf("右键\n");
		if (color == 3) {
			color = 1;
		}
		else {
			color += 1;
		}
	}

	mydisplay();
}


// 保持长宽比率不变
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


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(500, 150);
	glutCreateWindow("experiment3");

	// 初始化
	init();
	// 显示函数
	glutDisplayFunc(mydisplay);
	// 键盘函数
	glutKeyboardFunc(mykeyboard);
	// 鼠标函数
	glutMouseFunc(mymouse);
	// 窗口函数
	glutReshapeFunc(myreshape);

	// 进入事件循环
	glutMainLoop();
}
```

### 2. 运行说明
#### 2.1 鼠标事件
- 单击左键，图形按照【三角形 -> 四边形 -> 圆形】的顺序依次变化呈现
- 单击右键，颜色按照【红色 -> 绿色 -> 蓝色】的顺序依次变化呈现
#### 2.2 键盘事件
- 按'T'或't'键，图形变为三角形
- 按'Q'或'q'键，图形变为四边形
- 按'C'或'c'键，图形变为圆形
- 按'R'或'r'键，颜色变为红色
- 按'G'或'g'键，颜色变为绿色
- 按'B'或'b'键，颜色变为蓝色

---
# 遇到的问题
### 1. 能运行，界面全为白色
- 原因：没有刷新绘图命令队列
- 解决方法：`mydisplay()`函数最后加上`glFlush();`

### 2. 鼠标/键盘事件无响应
- 原因：改变后没有绘图
- 解决方法：在`mykeyboard()`和`mymouse()`函数最后都加上`mydisplay();`
