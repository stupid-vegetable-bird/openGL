# Transform 基本知识
### 1. Specifying  Transformations：指定转换
- 指定矩阵
  - `glLoadMatrix`
  - `glMultMatrix`
- 指定操作
  - `glRotate`
  - `glOrtho`


### 2. Matrix Operations：矩阵操作
```C++
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
```

- `glMatrixMODE(GL_MODELVIEW or GL_PROJECTION)`：指定当前矩阵
  - 函数原型：`void glMatrixMode(GLenum mode)`
  - 与`glLoadIdentity()`一同使用
  - `mode`指定哪一个矩阵堆栈是下一个矩阵操作的目标，可选值:
    - `GL_MODELVIEW`：对模型视图矩阵堆栈应用随后的矩阵操作。
      - 需要**绘制出对象**或要**对所绘制对象进行几何变换**时，将变换矩阵设置成模型视图模式
      - 执行此命令后，输出自己的物体图形
    - `GL_PROJECTION`：对投影矩阵堆栈应用随后的矩阵操作。
      - 需要对绘制的对象**设置某种投影方式**时，将变换矩阵设置成投影模式
      - 执行此命令后，为场景增加透视
    - `GL_TEXTURE`：对纹理矩阵堆栈应用随后的矩阵操作。
      - 在**进行纹理映射**时，将变换矩阵设置成纹理模式
      - 执行此命令后，为图形增加纹理贴图
- `glLoadIdentity()`：重置当前指定的矩阵为单位矩阵


### 3. Modeling Transformations：模型变换（移动模型）
```C++
glTranslatef(50, 0, -5.0);     //移动，参数含义(x轴位移,y轴位移,z轴位移)
glRotatef(135, 0, 0, 1);    //旋转，参数含义(旋转量,x轴,y轴,z轴)
glScalef(0.5, 0.5, 0.5);    //缩放，参数含义(x轴倍数,y轴倍数,z轴倍数)
```

- `glTranslate{fd}(x, y, z)`：坐标平移函数
  - `void glTranslatef(GLfloat x,GLfloat y,GLfloat z);`
  - `void glTranslated(GLdouble x,Gldouble y, Gldouble z);`
    - 沿X轴正方向平移x个单位(x是有符号数)
    - 沿Y轴正方向平移y个单位(y是有符号数)
    - 沿Z轴正方向平移z个单位(z是有符号数)
  
- `glRotate{fd}(angle, x, y, z)`：坐标旋转函数
  - angle以度为单位
  - `void glRotatef(GLfloat angle, GLfloat x,Glfloat y, Glfloat z);`
  - `void glRotated(GLdouble angle, GLdouble x,Gldouble y, Gldouble z);`
    - angle制定旋转角度，单位为度，旋转方向为逆时针
    - x,y,z指定向量的x,y,z坐标

- `glScale{fd}(x, y, z)`：坐标缩放函数
  - `void glScalef(GLfloat x,Glfloat y, Glfloat z);`
  - `void glScaled(GLdouble x,Gldouble y, Gldouble z);`
    - x,y,z表示各个方向的缩放比例


### 4. Viewing Transformations：视点变换（三脚架的位置和方向）
```C++
#include "stdafx.h"
#include <GL/glut.h>
#include <stdlib.h>

void init(void) {
    glClearColor (0.0, 0.0, 0.0, 0.0); //背景黑色
}

void display(void) {
    glClear (GL_COLOR_BUFFER_BIT);
    glColor3f (1.0, 1.0, 1.0); //画笔白色

    glLoadIdentity();  //加载单位矩阵

    gluLookAt(0.0,0.0,5.0,  0.0,0.0,0.0,  0.0,1.0,0.0);
    glutWireTeapot(2);
    glutSwapBuffers();
}

void reshape (int w, int h) {
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow (argv[0]);

    init ();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
```

- `glTranslate()`：坐标平移函数
- `glRotate()`：坐标旋转函数
- `gluLookAt(eyex, eyey, eyz, aimx, aimy, aimz, upx, upy, upz)`
  - up矢量确定唯一的方向
  - 该函数定义一个视图矩阵，并与当前矩阵相乘
    - 第一组eyex, eyey,eyez：相机在世界坐标的位置
    - 第二组aimx, aimy, aimz：相机镜头对准的物体在世界坐标的位置
    - 第三组upx,upy,upz：相机向上的方向在世界坐标中的方向
  - 把相机想象成为脑袋：
    - 第一组数据：脑袋的位置
    - 第二组数据：眼睛看的物体的位置
    - 第三组数据：头顶朝向的方向（例歪着头看同一个物体）
  - 本地坐标系-->世界坐标系-->眼坐标系-->裁剪坐标系
  - `gluLookAt()`一般用于从世界坐标系到眼坐标系的转换，但是由于OpenGL里面模型视图矩阵直接将本地坐标系转换为眼坐标系，所以gluLookAt()应该被用来设置模型视图矩阵
  - `gluLookAt()`的调用应该在场景绘制初`glLoadIdentity()`函数调用之后，在所有的`glTranslate*()`、`glRotate*()`、`glScale*()`函数调用之前调用，且只调用一次
    ```C++
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(...);
    
    // 这里最好先调用glPushMatrix()
    // 下面就可以任意调用glTranslate*()，glRotate*()，glScale*()等函数了，注意如果再次调用了glLoadIdentity(),则需要重新调用gluLookAt()
    // 即，如果让gluLookAt()函数调用达到想要的效果的话，gluLookAt()设置的矩阵一定是模型视图矩阵所乘的第一个矩阵，且最多乘一次
    ```


### 5. Projection Transformation：投影变换（相机的镜头）
- 透视投影
  - `void glFrustum(GLdouble left, GLdouble Right, GLdouble bottom, GLdouble top, GLdouble near, GLdouble far);`
    - 该函数的参数只定义近裁剪平面的左下角点和右上角点的三维空间坐标，即(left, bottom, -near)和(right, top, -near)
    - left，right：指定左边和右边垂直切面的坐标
    - bottom，top：指定下边和上边水平切面的坐标
    - near，far：指定近端和远端深度切面的距离，必须大于0
      ![image](https://github.com/stupid-vegetable-bird/openGL/assets/97822083/dc322e4e-a96e-4d19-93a9-0692d2911384)

  - `void gluPerspective (GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar)`
    - fovy表示视野在Y-Z平面的角度，角度值，范围是\[0.0, 180.0\]
      - 如果Fovy的值等于0，则什么也看不到
      - Fovy值在0-180的范围内，值越小，视野范围越狭小，物体越近；值越大，视野范围越宽阔，物体越远
      - 如果Fovy的值无限接近180，则什么也看不到
      - Fovy值在180-360的范围内，渲染的图像反转了过来（不是镜像），相当于你和你看到的东西一起倒了过来（脑补一下你眼前的东西跟你一起头朝地，脚朝上）
    - aspect表示裁剪面的宽w高h比，影响到视野的截面有多大
    - zNear和zFar表示近远裁剪面到视点(沿Z负轴)的距离，必须大于0
    ![image](https://github.com/stupid-vegetable-bird/openGL/assets/97822083/38db1722-1c2a-4366-abe8-4d3cf1e4dd35)

- 正投影平行投影
  - `void glOrtho(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble near, GLdouble far) `
    - `gluOrtho2D(left, right, bottom, top)`
    - 在Z值接近零时调用`glOrtho`
    ![image](https://github.com/stupid-vegetable-bird/openGL/assets/97822083/a3721301-9179-42b3-92e4-09be39b390c9)

- 投影变换经典使用（正投影）
  ```C++
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  glOrtho( left, right, bottom, top, zNear, zFar );
  ```


### 6. Common Transformation Usage：常见转换用法
- 通常在调整窗口大小时调用
- 作为`glutReshapeFunc(resize)`的回调进行注册
- `resize()`：Perspective & LookAt
  ```C++
  void resize( int w, int h ) {
     glViewport( 0, 0, (GLsizei) w, (GLsizei) h );
     glMatrixMode( GL_PROJECTION );
     glLoadIdentity();
     gluPerspective( 65.0, (GLfloat) w / h, 1.0, 100.0 );
     glMatrixMode( GL_MODELVIEW );
     glLoadIdentity();
     gluLookAt( 0.0, 0.0, 5.0,
                0.0, 0.0, 0.0,
                0.0, 1.0, 0.0 );
  }
  ```
  
  效果与之前的 LookAt() 相同
  ```C++
  void resize( int w, int h ) {
     glViewport( 0, 0, (GLsizei) w, (GLsizei) h );
     glMatrixMode( GL_PROJECTION );
     glLoadIdentity();
     gluPerspective( 65.0, (GLfloat) w/h, 1.0, 100.0 );
     glMatrixMode( GL_MODELVIEW );
     glLoadIdentity();
     glTranslatef( 0.0, 0.0, -5.0 );
  }
  ```


### 7. Viewport Transformation：视口变换（照片大小）
```C++
#include "stdafx.h"
#include <math.h>
#define GLUT_DISABLE_ATEXIT_HACK
#include "gl/glut.h"
 
void myDisplay() {
 glClear(GL_COLOR_BUFFER_BIT);
 glColor3f(1.0, 0.0, 0.0);
 //画分割线，分成四个视区  
 glViewport(0, 0, 400, 400);
 glBegin(GL_LINES);
 glVertex2f(-1.0, 0);
 glVertex2f(1.0, 0);
 glVertex2f(0.0, -1.0);
 glVertex2f(0.0, 1.0);
 glEnd();
 
 //定义在左下角的区域  
 glColor3f(0.0, 1.0, 0.0);
 glViewport(0, 0, 200, 200);
 glBegin(GL_POLYGON);
 glVertex2f(-0.5, -0.5);
 glVertex2f(-0.5, 0.5);
 glVertex2f(0.5, 0.5);
 glVertex2f(0.5, -0.5);
 glEnd();
 
 //定义在右上角的区域  
 glColor3f(0.0, 0.0, 1.0);
 glViewport(200, 200, 200, 200);//注意，后面这两个参数是高度和宽度，而不是坐标  
 glBegin(GL_POLYGON);
 glVertex2f(-0.5, -0.5);
 glVertex2f(-0.5, 0.5);
 glVertex2f(0.5, 0.5);
 glVertex2f(0.5, -0.5);
 glEnd();
 
 //定义在左上角的区域  
 glColor3f(1.0, 0.0, 0.0);
 glViewport(0, 200, 200, 200);  
 glBegin(GL_POLYGON);
 glVertex2f(-0.5, -0.5);
 glVertex2f(-0.5, 0.5);
 glVertex2f(0.5, 0.5);
 glVertex2f(0.5, -0.5);
 glEnd();
 
 //定义在右下角  
 glColor3f(1.0, 1.0, 1.0);
 glViewport(200, 0, 200, 200);
 glBegin(GL_POLYGON);
 glVertex2f(-0.5, -0.5);
 glVertex2f(-0.5, 0.5);
 glVertex2f(0.5, 0.5);
 glVertex2f(0.5, -0.5);
 glEnd();
 glFlush();
 }
 
int main(int argc, char *argv[]) {
 glutInit(&argc, argv);
 glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
 glutInitWindowPosition(100, 100);
 glutInitWindowSize(400, 400);
 glutCreateWindow("第一个OpenGL程序");
 glutDisplayFunc(&myDisplay);
 glutMainLoop();
 return 0;
}
```

- `glViewport(GLint x,GLint y,GLsizei width,GLsizei height)`
  - (x，y)：指定视口的左下角
  - (width, height)：视口矩形的大小
    - 通常与窗口大小相同
    - 视口长宽比应与投影变换相同，否则生成的图像可能会失真

   
### 8. Matrix Stacks：矩阵堆栈
```C++
glLoadIdentity();
glTranslatef(1,0,0);  //向右移动(1,0,0)
glPushMatrix();       //保存当前位置
glTranslatef(0,1,0);  //现在是(1,1,0)了
glPopMatrix();        //这样，现在又回到(1,0,0)了
```

- `glPushMatrix();`
  - 复制当前矩阵，并将副本添加到堆栈顶部
  - 意思是 "记住你所在的位置"
- `glPopMatrix();`
  - 丢弃堆栈顶部的矩阵
  - 意思是 "回到你所在的位置"

 
### 9. Modelview & Projection Matrix Stack：模型视图和投影矩阵堆栈
```C++
glMatrixMode(GL_PROJECTION);
glPushMatrix();          /*save the current projection*/ 
glLoadIdentity();
glOrtho(...);               /*set up for displaying help*/
display_the_help(); 
glPopMatrix();
```

- `glMatrixMode(GL_MODELVIEW);`
  - 用于构建分层模型
- `glMatrixMode(GL_PROJECTION);`
  - 无组合投影
  - 只能深入两层
  - 例如，用于显示文本
