# 一、基本知识
> 可运行的示例代码
```C++
#include<GL/glut.h>
void init() {
	// black clear color, opaque window
	glClearColor(0.0, 0.0, 0.0, 1.0);
	
	// fill/draw with white
	glColor3f(1.0, 1.0, 1.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// viewing volume
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
}

void display(){
	// 清空颜色缓冲区和深度缓冲区
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// 绘图
	glutSolidSphere (1.0, 20, 16);
   
	// 刷新绘图命令队列
	glFlush ();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	// define window properties
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("simple");

	// set OpenGL state
	init();
	// diaplay callback
	glutDisplayFunc(mydisplay);

	// enter event loop
	glutMainLoop();
}
```
- `glutInit`: allows application to get command line arguments and initializes system
- `gluInitDisplayMode`: requests properties for the window (the rendering context)
  - RGB color
  - Single buffering
  - Properties logically ORed together
- `glutWindowSize`: in pixels
- `glutWindowPosition`: from top-left corner of display
- `glutCreateWindow`: create window with title “simple”
- `init`: 初始化OpenGL的状态，例如设置清空颜色、投影矩阵等
  - `glClearColor`: 设置清空颜色
  - `glMatrixMode`: 设置矩阵类型
    - `glMatrixMode(GL_PROJECTION)`: 设置当前操作为投影矩阵
    - `glMatrixMode(GL_MODELVIEW)`: 设置当前操作为模型视图矩阵
  - `glLoadIdentity`: 将当前矩阵重置为单位矩阵，通常与 `glMatrixMode(GL_PROJECTION)` 或 `glMatrixMode(GL_MODELVIEW)` 配合使用
    - 使用 `glMatrixMode` 指定了要进行操作的矩阵类型后，调用该函数将该矩阵重置为单位矩阵
    - 清除之前对该矩阵的所有变换，将其重置为初始状态，从而开始一个新的矩阵变换序列
  - `glOrtho`: 设置正交投影
    - 定义了一个平行投影，使得渲染的对象在观察时不会产生透视变形
    - 参数包括左边界、右边界、底部边界、顶部边界、近裁剪面和远裁剪面
- `glutDisplayFunc`: display callback
  - `mydisplay`: 绘制OpenGL场景
    - `glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)`: 清空颜色缓冲区和深度缓冲区
    - `glFlush`: 刷新绘图命令队列，并等待命令执行完成，不等待图形硬件将结果显示到屏幕上
- `glutMainLoop`: enter infinite event loop

### （一）基本图形
- GL_POINTS
- GL_LINES
- GL_LINE_STRIP
- GL_LINE_LOOP
- GL_POLYGON
- GL_TRIANGLE
- GL_TRIANGLE_STRIP
- GL_TRIANGLE_FAN
- GL_QUADS
- GL_QUAD_STRIP

### （二）定义基本图形
```C++
// primType determines how vertices are combined
glBegin(primType);
glEnd();
```
```C++
// 属于mydisplay
void drawRhombus(GLfloat color[]) {
	glBegin(GL_QUADS);
	glColor3fv(color);
	glVertex2f(0.0, 0.0);
	glVertex2f(1.0, 0.0);
	glVertex2f(1.0, 1.0);
	glVertex2f(0.5, 1.0);
	glEnd();
}
```

#### OpenGL Command Formats
`glVertex3fv(v)`
- 3:Number of components
  - 2-(x,y)
  - 3-(x,y,z)
  - 4-(x,y,z,w)
- f:Data Type
  - b-byte
  - ub-unsigned byte
  - s-short
  - us-unsigned short
  - i-int
  - ui-unsigned int
  - f-float
  - d-double
- v:Vector
  - omit 'v' for scalar form
  - glVertex2f(x,y);

# 二、实验内容
在一个窗口内：  
1. 画一个三角形，三个顶点设置三个不同的颜色，其余部分的颜色由系统自动填充
2. 画一个纯色的圆形

# 三、实验过程
1. 写出架构
```C++
#include<GL/glut.h>
void init();
void mydisplay();

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	// define window properties
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("simple");

	// set OpenGL state
	init();
	// diaplay callback
	glutDisplayFunc(mydisplay);

	// enter event loop
	glutMainLoop();
}
```
2. 根据题目要求对函数进行补充
```C++
void init() {
	// black clear color, opaque window
	glClearColor(0.0, 0.0, 0.0, 1.0);

	// fill/draw with white
	glColor3f(1.0, 1.0, 1.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}
```

```C++
void mydisplay() {
	// 清空颜色缓冲区和深度缓冲区
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// 三角形，三个顶点设置三个不同的颜色，其余部分的颜色由系统自动填充
	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 0.0, 0.0);  //设定顶点颜色
	glVertex2f(-0.5, -0.5);
	glColor3f(0.0, 0.0, 1.0);  //设定顶点颜色
	glVertex2f(0.5, -0.5);
	glColor3f(0.0, 1.0, 0.0);  //设定顶点颜色
	glVertex2f(0.0, 0.5);
	glEnd();

	// 刷新绘图命令队列
	glFlush();
}
```

```C++
'''
添加头文件#include<math.h>
'''
void mydisplay() {
	// 清空颜色缓冲区和深度缓冲区
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// 纯色的圆形
	int n = 360;  //圆绘制次数
	float PI = 3.1415926f;
	float R = 0.8f;  //半径
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.1, 0.2, 0.3);  //设定颜色
	glVertex2f(0.0, 0.0);  //添加圆心
	for (int i = 0; i <= n; i++) {
		glVertex2f(R * sin(2 * PI * i / n), R * cos(2 * PI * i / n));   //定义顶点
	}
	glEnd();

	// 刷新绘图命令队列
	glFlush();
}
```

3. 完整代码
> 三角形和圆不可同时绘制，根据需要选用其中一个
```C++
#include<GL/glut.h>
#include<math.h>
void init() {
	// black clear color, opaque window
	glClearColor(0.0, 0.0, 0.0, 1.0);

	// fill/draw with white
	glColor3f(1.0, 1.0, 1.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}
void mydisplay() {
	// 清空颜色缓冲区和深度缓冲区
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// 三角形，三个顶点设置三个不同的颜色，其余部分的颜色由系统自动填充
	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 0.0, 0.0);  //设定顶点颜色
	glVertex2f(-0.5, -0.5);
	glColor3f(0.0, 0.0, 1.0);  //设定顶点颜色
	glVertex2f(0.5, -0.5);
	glColor3f(0.0, 1.0, 0.0);  //设定顶点颜色
	glVertex2f(0.0, 0.5);
	glEnd();

	//// 纯色的圆形
	//int n = 360;  //圆绘制次数
	//float PI = 3.1415926f;
	//float R = 0.8f;  //半径
	//glBegin(GL_TRIANGLE_FAN);
	//glColor3f(0.1, 0.2, 0.3);  //设定颜色
	//glVertex2f(0.0, 0.0);  //添加圆心
	//for (int i = 0; i <= n; i++) {
	//	glVertex2f(R * sin(2 * PI * i / n), R * cos(2 * PI * i / n));   //定义顶点
	//}
	//glEnd();

	// 刷新绘图命令队列
	glFlush();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	// define window properties
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(500, 150);
	glutCreateWindow("simple");

	// set OpenGL state
	init();
	// diaplay callback
	glutDisplayFunc(mydisplay);

	// enter event loop
	glutMainLoop();
}
```

---
# 遇到的问题
### 1. 如何绘制圆
- 首先确定绘制的类型
- 采用循环的方式重复画
```C++
'''
画无填充的圆（只有线）
原因：类型为GL_LINE_LOOP
'''
int n = 360;  //圆绘制次数
float PI = 3.1415926f;
float R = 0.8f;  //半径

glBegin(GL_LINE_LOOP);
glColor3f(0.1, 0.2, 0.3);  //设定颜色
for (int i = 0; i <= n; i++) {
	glVertex2f(R*sin(2 * PI*i / n), R*cos(2 * PI*i / n));   //定义顶点
}
glEnd();
```

```C++
'''
画填充的圆
修改方式：类型为GL_TRIANGLE_FAN，并添加圆心
【可能出现的】问题：圆不完整
原因：重复次数为360
'''
int n = 360;  //圆绘制次数
float PI = 3.1415926f;
float R = 0.8f;  //半径

glBegin(GL_TRIANGLE_FAN);
glColor3f(0.1, 0.2, 0.3);  //设定颜色
glVertex2f(0.0, 0.0);  //添加圆心
for (int i = 0; i <= n; i++) {
	glVertex2f(R*sin(2 * PI*i / n), R*cos(2 * PI*i / n));   //定义顶点
}
glEnd();
```

```C++
'''
画完整的填充的圆
修改方式：重复次数为361
'''
int n = 361;  //圆绘制次数
float PI = 3.1415926f;
float R = 0.8f;  //半径

glBegin(GL_TRIANGLE_FAN);
glColor3f(0.1, 0.2, 0.3);  //设定颜色
glVertex2f(0.0, 0.0);  //添加圆心
for (int i = 0; i <= n; i++) {
	glVertex2f(R*sin(2 * PI * i / n), R*cos(2 * PI * i / n));   //定义顶点
}
glEnd();
```
