// compile: g++ main.cpp -o main -lGL -lglfw
// execute: ./main

#include <stdio.h>
#include <math.h>
#include <GLFW/glfw3.h>

#define WIDTH 600
#define HEIGHT 400

#define xpos(x) (2.0f/(float)WIDTH)*(float)(x)-1.0
#define ypos(y) (-2.0f/(float)HEIGHT)*(float)(y)+1.0

#define radians(deg) (float)(M_PI*deg/180.0)

void setBlock(float x, float y, const int xsize, const int ysize)
{
    // How much pixels a block requires
    glBegin(GL_POINTS);
    for(float i = xsize*x; i < xsize*(x+1); ++i)
        for(float j = ysize*y; j < ysize*(y+1); ++j)
            glVertex2f(xpos(i), ypos(j)); 
    glEnd();
}

void setRay(float x, float y, float xsize, float ysize, float radius, float rayAngle)
{
    // rayAngle and relativeAngle are in degrees.
    // relativeAngle is relative to ray.

    float dx = radius*cos(radians(fabs(rayAngle)));
    float dy = radius*sin(radians(fabs(rayAngle)));

    glBegin(GL_LINES);
        glVertex2f(xpos(xsize*x+xsize/2+dx), ypos(ysize*y+ysize/2+dy));
        glVertex2f(xpos(xsize*x+xsize/2.0), ypos(ysize*y+ysize/2.0));
    glEnd();
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

// PLAYER
float xPlayer = 10;
float yPlayer = 10;

// VIEW
float viewAngle = 45;
float fov = 30; 
float numRays = 10;

// MOVEMENT
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(key == GLFW_KEY_D && action != GLFW_PRESS)
        xPlayer += 1.5;
    if(key == GLFW_KEY_A && action != GLFW_PRESS)
        xPlayer -= 1.5;
    if(key == GLFW_KEY_S && action != GLFW_PRESS)
        yPlayer += 1.5;
    if(key == GLFW_KEY_W && action != GLFW_PRESS)
        yPlayer -= 1.5;
    if(key == GLFW_KEY_R && action != GLFW_PRESS)
        viewAngle = (viewAngle+3)>360?0:viewAngle+3;
}

// EXECUTION
int main()
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(WIDTH, HEIGHT, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);

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
                glColor3f(sin(j+i), cos(i), cos(j+i));
                if(scenario[j][i]=='1')
                    setBlock(i,j,20,20);
            }
        }

        glColor3f(1.0f, 1.0f, 0.0f);
        setBlock(xPlayer,yPlayer,10,10);

        glColor3f(1.0f, 0.0f, 0.0f);
        setRay(xPlayer, yPlayer, 10, 10, 100, viewAngle);
        /*
        setRay(xPlayer, yPlayer, 10, 10, 50, viewAngle, -fov/2);
        setRay(xPlayer, yPlayer, 10, 10, 50, viewAngle, fov/2);*/

        glColor3f(1.0f, 0.5f, 1.0f);
        float step = fov/(numRays);
        float subray = step;
        for(float i=0;i<numRays/2;++i)
        {
            setRay(xPlayer, yPlayer, 10, 10, 100, viewAngle+subray);
            setRay(xPlayer, yPlayer, 10, 10, 100, viewAngle-subray);
            subray+=step;
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}