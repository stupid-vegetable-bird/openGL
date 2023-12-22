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