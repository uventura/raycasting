// compile: g++ main.cpp -o main -lGL -lglfw
// execute: ./main

#include <stdio.h>
#include <GLFW/glfw3.h>

#define WIDTH 600
#define HEIGHT 400

#define xpos(x) (2.0f/(float)WIDTH)*(float)x-1.0
#define ypos(y) (2.0f/(float)HEIGHT)*(float)y-1.0

void setPoint(float x, float y)
{
    // How much pixels a block requires
    const int xpixel = 16;
    const int ypixel = 16;

    for(float i = xpixel*x; i < xpixel*(x+1); ++i)
    {
        glBegin(GL_POINTS);
        for(float j = ypixel*y; j < ypixel*(y+1); ++j)
            glVertex2f(xpos(i), ypos(j));
        glEnd();
    }    
}

// SCENARIO
const int rows = 8;
const int cols = 8;

char scenario[2+rows][2+cols]=
{
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000",
    "00000000"
};

int main()
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    const int width  = 600;
    const int height = 400;
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.2f, 0.0f, 0.2f, 1.0f);

        glColor3f(1.0f, 1.0f, 0.0f);
        setPoint(1,1);
        glColor3f(1.0f,0.5f,1.0f);
        setPoint(0,0);
        setPoint(2,2);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}