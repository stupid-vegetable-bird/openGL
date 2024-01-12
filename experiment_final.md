# 一、实验内容
【官方版本实验内容描述】
- 综合运用学习过的OpenGL中的几何变换、光照计算和纹理映射等技术设计并编程实现一个对室内虚拟场景进行交互式漫游的三维图形程序 
- 要求提交：可执行程序及相关数据，源代码，软件使用说明书和相关软件工程文档

<br>

【解读版本实验内容描述】
1. 做一个教室或宿舍。
2. 要求用转换视角，光影，纹理，键盘和鼠标交互等之前实验用的学的内容。
3. 要求写设计说明书（软件操作说明书）
4. 要求写代码主要函数介绍书（实验报告）

# 二、实验过程
[stb_image库下载](Code/experiment/stb_image.h)
```C++
#include <stdio.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

GLfloat rotationX = 0.0;
GLfloat rotationY = 0.0;
GLfloat rotationZ = 0.0;
GLuint texture_floor, texture_desk, texture_blackboard;
bool is_show = true;

void loadTexture(const char* filename, GLuint* textureID) {
    int width, height, channels;
    stbi_set_flip_vertically_on_load(true); // 翻转图片
    unsigned char* image = stbi_load(filename, &width, &height, &channels, 0);
    if (image) {
        glGenTextures(1, textureID);
        glBindTexture(GL_TEXTURE_2D, *textureID);
        if (channels == 3) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        }
        else if (channels == 4) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
        }
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        stbi_image_free(image);
    }
}

void init() {
    glEnable(GL_TEXTURE_2D);
    loadTexture("floor.bmp", &texture_floor);
    loadTexture("desk.bmp", &texture_desk);
    loadTexture("blackboard.bmp", &texture_blackboard);

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glShadeModel(GL_SMOOTH);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat light_position[] = { 0.0, 15.0, -20.0, 1.0 };
    GLfloat light_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
    GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat specula[] = { 1.0, 1.0, 1.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specula);

    GLfloat mat_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat mat_diffuse[] = { 0.1, 0.5, 0.8, 1.0 };
    GLfloat mat_specular[] = { 0.8, 1.0, 1.0,1.0 };
    GLint shine = 50;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMateriali(GL_FRONT, GL_SHININESS, shine);

    // 开启更新深度缓冲区
    glEnable(GL_DEPTH_TEST);
}

// draw blackboard,wall,floor,ceiling
void draw_scene() {
    // Draw the blackboard
    glBindTexture(GL_TEXTURE_2D, texture_blackboard);
    glPushMatrix();
    glTranslatef(0.0, 0.0, -4.95);
    glScalef(2.0, 1.0, 0.1);
    glutSolidCube(1.0);
    glPopMatrix();

    if (is_show) {
        // Draw the front wall
        glBindTexture(GL_TEXTURE_2D, texture_floor);
        glPushMatrix();
        glTranslatef(0.0, 0.0, -5.0);
        glScalef(2.5, 1.0, 0.01);
        glutSolidCube(4.0);
        glPopMatrix();
    
        // Draw the left wall
        glPushMatrix();
        glTranslatef(-5.0, 0.0, 0.0);
        glScalef(0.01, 1.0, 2.5);
        glutSolidCube(4.0);
        glPopMatrix();

        // Draw the right wall
        glPushMatrix();
        glTranslatef(5.0, 0.0, 0.0);
        glScalef(0.01, 1.0, 2.5);
        glutSolidCube(4.0);
        glPopMatrix();

        // Draw the ceiling
        glBindTexture(GL_TEXTURE_2D, texture_floor);
        glPushMatrix();
        glTranslatef(0.0, 2.0, 0.0);
        glScalef(2.5, 0.03, 2.5);
        glutSolidCube(4.0);
        glPopMatrix();
    }

    // Draw the floor
    glPushMatrix();
    glTranslatef(0.0, -2.0, 0.0);
    glScalef(2.5, 0.03, 2.5);
    glutSolidCube(4.0);
    glPopMatrix();
}

// draw teacher desk
void draw_teacher_desk() {
    glBindTexture(GL_TEXTURE_2D, texture_desk);
    // table_up
    glPushMatrix();
    glTranslatef(0.0, -1.0, -3.9);
    glScalef(1.3, 0.05, 0.5);
    glutSolidCube(1.5);
    glPopMatrix();
    // table_down
    glPushMatrix();
    glTranslatef(0.0, -1.2, -3.9);
    glScalef(1.3, 0.05, 0.5);
    glutSolidCube(1.5);
    glPopMatrix();
    // table_front
    glPushMatrix();
    glTranslatef(0.0, -1.5, -3.55);
    glScalef(1.3, 0.7, 0.05);
    glutSolidCube(1.5);
    glPopMatrix();
    // table_side
    glPushMatrix();
    glTranslatef(0.95, -1.1, -3.9);
    glScalef(0.05, 0.15, 0.5);
    glutSolidCube(1.5);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-1.05, -1.1, -3.9);
    glScalef(0.05, 0.15, 0.5);
    glutSolidCube(1.5);
    glPopMatrix();
}

// draw table,chair
void draw_table_desk(GLint x, GLint z) {
    glBindTexture(GL_TEXTURE_2D, texture_desk);
    // table_up
    glPushMatrix();
    glTranslatef(3.0 - 3 * x, -1.0, -1.9 + 2.3 * z);
    glScalef(1.3, 0.05, 0.5);
    glutSolidCube(1.5);
    glPopMatrix();
    // table_down
    glPushMatrix();
    glTranslatef(3.0 - 3 * x, -1.2, -1.9 + 2.3 * z);
    glScalef(1.3, 0.05, 0.5);
    glutSolidCube(1.5);
    glPopMatrix();
    // table_front
    glPushMatrix();
    glTranslatef(3.0 - 3 * x, -1.5, -2.3 + 2.3 * z);
    glScalef(1.3, 0.7, 0.05);
    glutSolidCube(1.5);
    glPopMatrix();
    // table_side
    glPushMatrix();
    glTranslatef(3.0 - 3 * x, -1.1, -1.9 + 2.3 * z);
    glScalef(0.05, 0.15, 0.5);
    glutSolidCube(1.5);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(3.95 - 3 * x, -1.1, -1.9 + 2.3 * z);
    glScalef(0.05, 0.15, 0.5);
    glutSolidCube(1.5);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(2.05 - 3 * x, -1.1, -1.9 + 2.3 * z);
    glScalef(0.05, 0.15, 0.5);
    glutSolidCube(1.5);
    glPopMatrix();

    // Draw the chair
    // draw the front
    glPushMatrix();
    glTranslatef(3.5 - 3 * x, -1.7, -1.45 + 2.3 * z);
    glScalef(0.4, 0.3, 0.05);
    glutSolidCube(1.5);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(2.5 - 3 * x, -1.7, -1.45 + 2.3 * z);
    glScalef(0.4, 0.3, 0.05);
    glutSolidCube(1.5);
    glPopMatrix();
    // draw the back
    glPushMatrix();
    glTranslatef(3.5 - 3 * x, -1.5, -1.1 + 2.3 * z);
    glScalef(0.4, 0.6, 0.05);
    glutSolidCube(1.5);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(2.5 - 3 * x, -1.5, -1.1 + 2.3 * z);
    glScalef(0.4, 0.6, 0.05);
    glutSolidCube(1.5);
    glPopMatrix();
    // draw the up
    glPushMatrix();
    glTranslatef(3.5 - 3 * x, -1.5, -1.3 + 2.3 * z);
    glScalef(0.35, 0.05, 0.25);
    glutSolidCube(1.5);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(2.5 - 3 * x, -1.5, -1.3 + 2.3 * z);
    glScalef(0.35, 0.05, 0.25);
    glutSolidCube(1.5);
    glPopMatrix();
}

void mydisplay(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -10.0);
    glRotatef(rotationX, 1.0, 0.0, 0.0);
    glRotatef(rotationY, 0.0, 1.0, 0.0);
    glRotatef(rotationZ, 0.0, 0.0, 1.0);

    // Draw the classroom here
    draw_scene();

    // Draw the teacher's desk
    draw_teacher_desk();

    // Draw the table
    for (GLint x = 0; x < 3; x++) {
        for (GLint z = 0; z < 3; z++) {
            draw_table_desk(x, z);
        }
    }

    glFlush();
    glutSwapBuffers();
}

void myspecialkey(int key, int x, int y) {
    if (key == GLUT_KEY_UP) {
        rotationX += 5.0;
    }
    else if (key == GLUT_KEY_DOWN) {
        rotationX -= 5.0;
    }
    else if (key == GLUT_KEY_LEFT) {
        rotationY += 5.0;
    }
    else if (key == GLUT_KEY_RIGHT) {
        rotationY -= 5.0;
    }
    else if (key == GLUT_KEY_F1) {
        rotationZ += 5.0;
    }
    else if (key == GLUT_KEY_F2) {
        rotationZ -= 5.0;
    }
    else if (key == GLUT_KEY_F5) {
        rotationX = 0.0;
        rotationY = 0.0;
        rotationZ = 0.0;
    }

    glutPostRedisplay();
}

void mymouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (is_show) {
            is_show = false;
        }
        else {
            is_show = true;
        }
    }
    mydisplay();
}

void myreshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90, (GLfloat)w / (GLfloat)h, 0.5, 20);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Classroom");
    printf("操作说明：\n\
1、单击鼠标左键显示/隐藏墙和天花板\n\
2、按动键盘上下左右方向键和F1、F2键进行投影变化\n\
3、按F5键刷新还原");

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

    return 0;
}
```

---
# 遇到的问题
