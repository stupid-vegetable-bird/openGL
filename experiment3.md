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
- void myreshape(GLint w, GLint h)`

# 二、实验内容
编写交互程序，要求：  
1. 显示基本线段、三角形、四边形、多边形等图形
2. 用户可以通过按键来控制绘制的图形类型和颜色。如：t绘制三角形，r图形改为红色
3. 使用键盘控制图形的位置
4. 用户可以通过点击鼠标左右键来调整图形的类型和颜色

# 三、实验过程

---
# 遇到的问题
