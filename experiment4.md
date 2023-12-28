# 一、基本知识
### 1. Specifying  Transformations：指定转换
- 指定矩阵
  - `glLoadMatrix`
  - `glMultMatrix`
- 指定操作
  - `glRotate`
  - `glOrtho`

### 2. Matrix Operations：矩阵操作
- `glMatrixMODE(GL_MODELVIEW or GL_PROJECTION)`：指定当前矩阵
- `glLoadIdentity()`：其他矩阵

### 3. Modeling Transformations：建模转换
- `glTranslate{fd}(x, y, z)`：移动物体
- `glRotate{fd}(angle, x, y, z)`：围绕任意轴旋转对象
  - angle以度为单位
- `glScale{fd}(x, y, z)`：放大（拉伸或缩小）或镜像物体
- \[`glMultMatrix();`\]

### 4. Viewing Transformations：查看变换
- `glTranslate()`
  - 例：`glTraslatef(0.0, 0.0, -5.0);`
- `glRotate()`
- `gluLookAt(eyex, eyey, eyz, aimx, aimy, aimz, upx, upy, upz)`
  - up矢量确定唯一的方向

### 5. Projection Transformation：投影转换
- 透视投影
  - `glFrustum(left, right, bottom, top, zNear, zFar)`
    - (left, bottom, -near),(right, top, -near)
  - `gluPerspective(fovy, aspect, zNear, zFar)`
- 正投影平行投影
  - `glOrtho(left, right, bottom, top, zNear, zFar)`
    - `gluOrtho2D(left, right, bottom, top)`
    - 在Z值接近零时调用`glOrtho`
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
     gluPerspective( 65.0, (GLfloat) w/h, 
                     1.0, 100.0 );
     glMatrixMode( GL_MODELVIEW );
     glLoadIdentity();
     glTranslatef( 0.0, 0.0, -5.0 );
  }
  ```

### 7. Viewport Transformation：视口变换
- `glViewport(x, y, width, height)`
  - (x，y)：指定视口的左下角
  - (width, height)：视口矩形的大小
    - 通常与窗口大小相同
    - 视口长宽比应与投影变换相同，否则生成的图像可能会失真
   
### 8. Matrix Stacks：矩阵堆栈
- `glPushMatrix();`
  - 复制当前矩阵，并将副本添加到堆栈顶部
  - 意思是 "记住你所在的位置"
- `glPopMatrix();`
  - 丢弃堆栈顶部的矩阵
  - 意思是 "回到你所在的位置"
 
### 9. Modelview & Projection Matrix Stack：模型视图和投影矩阵堆栈
- `glMatrixMode(GL_MODELVIEW);`
  - 用于构建分层模型
- `glMatrixMode(GL_PROJECTION);`
  - 无组合投影
  - 只能深入两层
  - 例如，用于显示文本
```C++
glMatrixMode(GL_PROJECTION);
glPushMatrix();          /*save the current projection*/ 
glLoadIdentity();     
glOrtho(...);               /*set up for displaying help*/
display_the_help(); 
glPopMatrix();
```

# 二、实验内容

# 三、实验过程

---
# 遇到的问题
