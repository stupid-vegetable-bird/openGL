#include<stdio.h>
#include<gl/glut.h>
#include<math.h>


void init();
void mydisplay();
void mykeyboard(unsigned char key, int x, int y);
void mymouse(int button, int state, int x, int y);
void myreshape(GLint w, GLint h);


int light = 3;
double pos_x = 0.1, pos_y = 0.1, pos_z = 0.1;


// 场景中有三个光源
// 自行设定光源和物体材质的基本属性
void init() {
	glClearColor(0.0, 0.0, 0.0, 1.0);


	// set light点光源
	glEnable(GL_LIGHTING);
	// 全开
	if (light == 3) {
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
		glEnable(GL_LIGHT2);
	}
	// 开light0
	else if (light == 0) {
		glEnable(GL_LIGHT0);
		glDisable(GL_LIGHT1);
		glDisable(GL_LIGHT2);
	}
	// 开light1
	else if (light == 1) {
		glDisable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
		glDisable(GL_LIGHT2);
	}
	// 开light2
	else if (light == 2) {
		glDisable(GL_LIGHT0);
		glDisable(GL_LIGHT1);
		glEnable(GL_LIGHT2);
	}
	
	// set position位置
	// set light0
	GLfloat light0_pos[] = {1.0 + pos_x, 0.5 + pos_y, -0.3 + pos_z, 0.0};
	// set light1
	GLfloat light1_pos[] = { 0.2 + pos_x, 1.0 + pos_y, -0.4 + pos_z, 0.0 };
	// set light2
	GLfloat light2_pos[] = { 0.1 + pos_x, 0.1 + pos_y, -1.0 + pos_z, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);
	glLightfv(GL_LIGHT2, GL_POSITION, light2_pos);

	// set ambient环境光
	// set light0
	GLfloat ambient0[] = { 1.0, 1.0, 1.0, 1.0 };
	// set light1
	GLfloat ambient1[] = { 0.5, 0.5, 0.5, 1.0 };
	// set light2
	GLfloat ambient2[] = { 0.0, 0.0, 0.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient0);
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient1);
	glLightfv(GL_LIGHT2, GL_AMBIENT, ambient2);

	// set diffuse漫射
	// set light0
	GLfloat diffuse0[] = { 1.0, 0.0, 0.0, 1.0 };
	// set light1
	GLfloat diffuse1[] = { 0.0, 1.0, 0.0, 1.0 };
	// set light2
	GLfloat diffuse2[] = { 0.0, 0.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse1);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse2);

	// set specula反射
	// set light0
	GLfloat specula0[] = { 1.0, 0.0, 0.0, 1.0 };
	// set light1
	GLfloat specula1[] = { 0.0, 1.0, 0.0, 1.0 };
	// set light2
	GLfloat specula2[] = { 0.0, 0.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_SPECULAR, specula0);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specula1);
	glLightfv(GL_LIGHT2, GL_SPECULAR, specula2);


	// set material材质属性
	GLfloat ambient[] = { 0.2,0.2,0.2,1.0 };
	GLfloat diffuse[] = { 1.0,0.8,1.0,1.0 };
	GLfloat specular[] = { 1.0,1.0,1.0,1.0 };
	GLint shine = 50;

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMateriali(GL_FRONT, GL_SHININESS, shine);


	// 明暗处理
	glShadeModel(GL_SMOOTH);

}


// 物体为茶壶
void mydisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// 画茶壶
	glutSolidTeapot(1.0);

	// 刷新绘图命令队列
	glFlush();
}


// 通过键盘改变光源的位置
void myspecialkey(int key, int x, int y) {
	if (key == GLUT_KEY_UP) {
		pos_y += 0.05;
	}
	else if (key == GLUT_KEY_DOWN) {
		pos_y -= 0.05;
	}
	else if (key == GLUT_KEY_RIGHT) {
		pos_x += 0.05;
	}
	else if (key == GLUT_KEY_LEFT) {
		pos_x -= 0.05;
	}

	mydisplay();
	init();
}


// 通过鼠标改变光源的类型
void mymouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (light == 3) {
			light = 0;
			pos_x = 0.1, pos_y = 0.1, pos_z = 0.1;
		}
		else {
			light += 1;
			pos_x = 0.1, pos_y = 0.1, pos_z = 0.1;
		}
		// printf("左键\n");
	}

	mydisplay();
	init();
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
	glutCreateWindow("experiment5");
	printf("操作说明：\n1、单击鼠标左键改变光源类型\n2、按动键盘上下左右方向键改变光源位置\n");

	// 初始化
	init();
	// 显示函数
	glutDisplayFunc(mydisplay);
	// 特殊键盘函数
	glutSpecialFunc(myspecialkey);
	// 鼠标函数
	glutMouseFunc(mymouse);
	// 窗口函数
	glutReshapeFunc(myreshape);

	// 进入事件循环
	glutMainLoop();
}