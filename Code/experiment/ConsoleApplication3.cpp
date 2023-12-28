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