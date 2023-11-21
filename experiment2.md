# 一、基本知识
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

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	// define window properties
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("simple");
	// diaplay callback
	glutDisplayFunc(mydisplay);

	// set OpenGL state
	init();

	// enter event loop
	glutMainLoop();
}
```
- glutInit:allows application to get command line arguments and initializes system
- gluInitDisplayMode:requests properties for the window (the rendering context)
  - RGB color
  - Single buffering
  - Properties logically ORed together
- glutWindowSize:in pixels
- glutWindowPosition:from top-left corner of display
- glutCreateWindow:create window with title “simple”
- glutDisplayFunc:display callback
- glutMainLoop:enter infinite event loop

### 基本图形
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

### 定义基本图形
```C++
// primType determines how vertices are combined
glBegin(primType);
glEnd();
```
```C++
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

---
# 遇到的问题
