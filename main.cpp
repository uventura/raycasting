// compile: g++ main.cpp -o main -lGL -lglfw
// execute: ./main

#include <stdio.h>
#include <math.h>
#include <GLFW/glfw3.h>

#define WIDTH 600
#define HEIGHT 400

#define xpos(x) (2.0f/(float)WIDTH)*(float)x-1.0
#define ypos(y) (-2.0f/(float)HEIGHT)*(float)y+1.0

void setBlock(float x, float y)
{
    // How much pixels a block requires
    const int xpixel = 20;
    const int ypixel = 20;

    for(float i = xpixel*x; i < xpixel*(x+1); ++i)
    {
        glBegin(GL_POINTS);
        for(float j = ypixel*y; j < ypixel*(y+1); ++j)
            glVertex2f(xpos(i), ypos(j));
        glEnd();
    }    
}

// SCENARIO
const int rows = 16;
const int cols = 16;

char scenario[2+rows][2+cols]=
{
    "1111111111111111",
    "1000000000000001",
    "1000000000000001",
    "1000000000000001",
    "1000000000000001",
    "1000001111111111",
    "1000001000000001",
    "1000001000000001",
    "1000001100000001",
    "1000001111000001",
    "1001100001000001",
    "1000100001000001",
    "1000111111000001",
    "1000000000000001",
    "1000000000000001",
    "1111111111111111"
};

int main()
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    const int width  = 600;
    const int height = 400;

    window = glfwCreateWindow(WIDTH, HEIGHT, "Hello World", NULL, NULL);
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
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.2f, 0.0f, 0.2f, 1.0f);

        // Plot the map
        for(int i = 0; i < rows;++i)
        {
            for(int j=0; j<cols;++j)
            {
                glColor3f(sin(i), cos(i), i*0.1f);
                if(scenario[j][i]=='1')
                    setBlock(i,j);
            }
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}