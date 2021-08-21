#include <stdio.h>
#include <GLFW/glfw3.h>

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
        //glPointSize(2.0/(float)cols);
        //glPointSize(width/rows);

        glPointSize(8.0f);
        glBegin(GL_POINTS);
        for(int i=0;i<8;++i)
        {
            glColor3f(1.0f, 1.0f-0.1f*i, 0.1*i);
            glVertex2f(-0.5f+0.1*(i+1),(2.0/(float)width)*i);
        }
        glEnd();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}