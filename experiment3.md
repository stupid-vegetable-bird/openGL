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
- `glutMouseFunc(mymouse)`
- `void mymouse(GLint button, GLint state, GLint x, GLint y)`

#### 位置
- 屏幕坐标以像素为基本单位，原点在左上角
- OpenGL坐标系原点在左下角

#### 鼠标运动函数
- `glutMotionFunc((void*)func(int x, int y));`
- `glutPassiveMotionFunc((void*)func(int x, int y));`

### （三）键盘
- `glutKeyboardFunc(mykey)`
- `void mykey(Glubyte key, GLint x, GLint y)`

#### 键盘相关函数

### （四）窗口形状的改变
内容大小变化、长宽比例变化、跟着窗口变化

# 二、实验内容
编写交互程序，要求：  
1. 显示基本线段、三角形、四边形、多边形等图形
2. 用户可以通过按键来控制绘制的图形类型和颜色。如：t绘制三角形，r图形改为红色
3. 使用键盘控制图形的位置
4. 用户可以通过点击鼠标左右键来调整图形的类型和颜色
