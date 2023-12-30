# 一、基本知识
### （一）启用光照
```C++
// 启用和禁用光照
glEnable(GL_LIGHTING);
glDisable(GL_LIGHTING);
```

- `glEnable(GL_LIGHTING)`
- 如果启用光照，`glColor()`命令无效
- 可单独启用各光源：`glEnable(GL_LIGHTi)`, i=0,1,...,7

### （二）法向量
- `glNormal*();`
- `glNormal3d(x, y, z);`
- `glNormal3dv(p);`

- 变换会影响其长度
- 通常需要法向量为单位向量
- `glEnable(GL_NORMALIZE)`

### （三）光照模型的参数
- `glLightModel{if}[v](参数, 值)`

```C++
// 全局环境光
GLfloat ambient[] = { 0.2, 0.2, 0.2, 1.0 };
glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);

// 把无限远的观察点改为局部观察点
glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

// 设置双面光照，使物体的背面接受的光照准确
glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

// 镜面辅助颜色
// 执行纹理贴图时才有用，可使效果逼真，其原理是：把镜面光从主颜色中抽离出来，在纹理贴图后，再把镜面光加进去
glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);
// 恢复到默认值可以调用
glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SINGLE_COLOR);

// 启用和禁用光照
glEnable(GL_LIGHTING);
glDisable(GL_LIGHTING);
```

| 参数名 | 默认值 | 含义 |
| ------ | ----- | ----- |
| GL_LIGHT_MODEL_AMBIENT | (0.2,0.2,0.2,1.0) | 整个场景中的环境光强 |
| GL_LIGHT_MODE_LOCAL_VIEWER | 0.0或GL_FALSE | 镜面反射角度是如何计算的 |
| GL_LIGHT_MODEL_TWO_SIDED | 0.0或GL_FALSE | 指定了单面还是双面光照 |
| GL_LIGHT_MODEL_COLOR_CONTROL | GL_SINGLE_COLOR | 镜面光是否与漫反射的环境光分开计算 |

### （四）定义点光源
```C++
GLfloat light0_pos[] = {1.0, 2.0, 3.0, 1.0};
GLfloat ambient0[] = {1.0, 0.0, 0.0, 1.0};
GLfloat diffuse0[] = {1.0, 0.0, 0.0, 1.0};
GLfloat specular0[] = {1.0, 0.0, 0.0, 1.0};

glEnable(GL_LIGHTING);
glEnable(GL_LIGHT0);
glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
glLightfv(GL_LIGHT0, GL_AMBIENT, ambient0);
glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
glLightfv(GL_LIGHT0, GL_SPECULAR, specular0);
```

- `glLightfv(light，pname，params)`
  - `light`：灯的标识符。可能的灯的数量取决于实现，但至少支持八个灯。它们由形式`GL_LIGHTi`的符号名称标识，其中i是一个值：0到GL_MAX_LIGHTS-1
  - `pname`：光的光源参数
  - `params`：指定将光源光的参数`pname`设置为的值

| 参数名 | 默认值 | 含义 |
| ------ | ----- | ----- |
| GL_POSITION | (0, 0, 1, 0) | 指定光在同质对象坐标中的**位置** |
| GL_AMBIENT | (0.0, 0.0, 0.0, 1.0)  | 指定光线的**环境**RGBA强度 |
| GL_DIFFUSE | 除光零以外的所有光的默认漫射强度为(0.0, 0.0, 0.0, 1.0)。<br>光零的默认漫射强度为(1.0, 1.0, 1.0, 1.0) | 指定光线的**漫射**RGBA强度 |
| GL_SPECULAR | 除光零以外的所有光的默认反射强度为(0.0, 0.0, 0.0, 1.0)。<br>光零的默认反射强度为(1.0, 1.0, 1.0, 1.0) | 指定光的**反射**RGBA强度 |
| GL_SPOT_DIRECTION | (0, 0, 1) | 参数以同质对象坐标指定光的方向 |
| GL_SPOT_CUTOFF | 180 | 指定光源的最大传播角度，仅接受范围\[0， 90]和特殊值180的值 |
| GL_SPOT_EXPONENT | 0 | 指定光的强度分布，仅接受\[0， 128]范围内的值 |

- 光源是几何对象，它的位置或方向受模型视图矩阵的影响
#### 位置
- 对于`GL_POSITION`，其位置数组(x，y，z，w)定义了光源在空间中的位置
- 采用齐次坐标形式
- 若w=1.0，指定的是一个空间位置。表示光源处于空间中(x，y，z)处，这时的光源称为定点光源
- 若w=0.0，指定的是一个平行光源，所给定的是入射光方向。表示光源位于无穷远处，此时光源称为定向光源，其所有光线几乎是相互平等的，如太阳。其光线方向由点（x，y，z）指向(0,0,0)

#### 环境光强
- 对于`GL_AMBIENT`，(R，G，B，A)表示光源中含有红、绿、蓝三种光线的成分以及透明度值，一般情况下为(1,1,1,1)

#### 漫射光强
- 通过对漫射光成分的设置，可以产生一个点光源
- 对于`GL_DIFFUSE`，(R，G，B，A)表示漫射光的颜色成分。可以根据不同需要指定不同的颜色，一般情况下为(1,1,1,1)

#### 反射光强
- 通过对镜面光成分的设置，可以产生一个平行光源
- 对于`GL_SPECULAR`，(R，G，B，A)表示漫射光的颜色成分。可以根据不同需要指定不同的颜色

#### 全局环境光
  - `GLfloat global_ambient[]={0.2,0,0,1};`
  - `glLightModelfv(GL_LIGHT_MODEL_AMBIENT,global_ambient);`

#### 距离项，衰减
- 光强反比于距离的因子 a+bd+cd2
- 默认值：a=1.0, b=c=0.0
- 环境光， 散射光，镜面光的强度都会衰减；发射光，全局环境光没有衰减
- 改变方法
  - `glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 2.0);`
  - `glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 1.0);`
  - `glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0);`

#### 聚光灯
- `glLightfv()`
  - 方向：`GL_SPOT_DIRECTION`
  - 角度范围：`GL_SPOT_CUTOFF`
  - 衰减指数：`GL_SPOT_EXPONENT`
![image](https://github.com/stupid-vegetable-bird/openGL/assets/97822083/a13d0dad-46a2-44d1-b190-1978534402ca)

### （五）材质属性
```C++
GLfloat ambient[]={0.2,0.2,0.2,1.0};
GLfloat diffuse[]={1.0,0.8,0.0,1.0};
GLfloat specular[]={1.0,1.0,1.0,1.0};
GLint shine = 100;

glMaterialfv(GL_FRONT,GL_AMBIENT,ambient);
glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuse);
glMaterialfv(GL_FRONT,GL_SPECULAR,specular);
glMateriali(GL_FRONT,GL_SHININESS,shine);
```

- `glMaterial{if}[v]()`
- 与简单光照模型中的各项匹配

#### 前面与后面
- 默认状态下只是对物体的前面进行明暗处理
- 如果设置了两面光照，每一面都可以具有自己的属性
  - `glMaterialf()`
  - `GL_FRONT`, `GL_BACK`, `GL_FRONT_AND_BACK`指定

#### 发射项
- 模拟光源
- 该项的颜色不受任何其他光源或变换的影响

- `GLfloat emission[]={0.0,0.3,0.3,1.0);`
- `glMaterialfv(GL_FRONT,GL_EMISSION,emission);`

### （六）多边形的明暗处理
- 对每个顶点进行明暗处理的计算
- 默认状态下，多边形内部的颜色是顶点颜色的线性插值
- `glShadeModel(GL_SMOOTH);`
- 设置`glShadeModel(GL_FLAT);`第一个顶点的颜色确定整个多边形的颜色

### （七）GLUT模型绘制函数
> 本次实验用到的是 **实心茶壶`void glutSolidTeapot(GLdouble size);`** 

```C++
void glutWireSphere(GLdouble radius, GLint slices, GLint stacks);   // 线框球
void glutSolidSphere(GLdouble radius, GLint slices, GLint stacks);  // 实心球

void glutWireCube(GLdouble size);   // 线框立方体
void glutSolidCube(GLdouble size);  // 实心立方体

void glutWireTorus(GLdouble innerRadius, GLdouble outerRadius, GLint nsides, GLint rings);    // 线框圆环
void glutSolidTorus(GLdouble innerRadius, GLdouble outerRadius, GLint nsides, GLint rings);   // 实心圆环

void glutWireIcosahedron(void);    // 线框20面体
void glutSolidIcosahedron(void);   // 实心20面体

void glutWireOctahedron(void);    // 线框8面体 
void glutSolidOctahedron(void);   // 实心8面体

void glutWireTetrahedron(void);     // 线框4面体
void glutSolidTetrahedron(void);    // 实心4面体

void glutWireDodecahedron(GLdouble radius);    // 线框12面体
void glutSolidDodecahedron(GLdouble radius);   // 实心12面体

void glutWireCone(GLdouble radius, GLdouble height, GLint slices, GLint stacks);    // 线框圆锥体
void glutSolidCone(GLdouble radius, GLdouble height, GLint slices, GLint stacks);   // 实心圆锥体

void glutWireTeapot(GLdouble size);    // 线框茶壶
void glutSolidTeapot(GLdouble size);   // 实心茶壶
```

- radius表示球体的半径
- slices表示球体围绕z轴分割的数目
- stacks表示球体沿着z轴分割的数目。

绘制中心在模型坐标原点,半径为radius的球体,球体围绕z轴分割slices次,球体沿着z轴分割stacks次

# 二、实验内容
1. 场景中有三个光源，物体为茶壶或其它。
2. 自行设定光源和物体材质的基本属性。
3. 用可通过键盘或鼠标改变光源的位置和类型。

[参考代码](Code/example/light.c)，如下：
```C++
#include <GL/glut.h>
#include <stdlib.h>

/* Initialize material property, light source, lighting model, and depth buffer. */
void init(void)  {
   GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat mat_shininess[] = { 50.0 };
   GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };

   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_SMOOTH);

   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
   glLightfv(GL_LIGHT0, GL_POSITION, light_position);

   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_DEPTH_TEST);
}

void display(void) {
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glutSolidSphere (1.0, 20, 16);
   glFlush ();
}

void reshape (int w, int h) {
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity();
   if (w <= h)
      glOrtho (-1.5, 1.5, -1.5*(GLfloat)h/(GLfloat)w,
         1.5*(GLfloat)h/(GLfloat)w, -10.0, 10.0);
   else
      glOrtho (-1.5*(GLfloat)w/(GLfloat)h,
         1.5*(GLfloat)w/(GLfloat)h, -1.5, 1.5, -10.0, 10.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

/* ARGSUSED1 */
void keyboard(unsigned char key, int x, int y) {
   switch (key) {
      case 27:
         exit(0);
         break;
   }
}

int main(int argc, char** argv) {
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize (500, 500); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}
```

# 三、实验过程

```C++
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
```

---
# 遇到的问题
### 1. GL_POSITION的x，y，z的方向情况    
  ![image](https://github.com/stupid-vegetable-bird/openGL/assets/97822083/d814e9a8-dfbf-4b3a-a2a3-60c952c84de2)

### 2. 某个光源无颜色
- 除了调整光源属性，还要调整材质属性
