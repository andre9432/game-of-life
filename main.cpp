#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <shader/shaders.h>
#include <glm/glm.hpp>

#include <iostream>
#include <sstream>

namespace WINDOW
{
    int WIDTH{ 600 }, HEIGHT{ 600 };
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    if (height < width)
	    glViewport((width - height) / 2, 0, height, height);

    else
        glViewport(0, (height - width) / 2, width, width);

    WINDOW::WIDTH = width;
    WINDOW::HEIGHT = height;
}

int main(void)
{
    /* Initialize the library */
    if (!glfwInit())
    {
        std::cerr << "Error initializing GLFW\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow(WINDOW::WIDTH, WINDOW::HEIGHT, "Hello World", NULL, NULL);
    if (!window)
    {
        std::cerr << "Error creating window\n";
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glfwSwapInterval(1);

    float vertices[] = {
        -1.f, -1.f,
         1.f, -1.f,
        -1.f,  1.f,

         1.f, -1.f,
         1.f,  1.f,
        -1.f,  1.f
    };

    GLuint VAO, VBO;
    glCreateVertexArrays(1, &VAO);
    glCreateBuffers(1, &VBO);

    glNamedBufferData(VBO, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexArrayAttrib(VAO, 0);
    glVertexArrayAttribBinding(VAO, 0, 0);
    glVertexArrayAttribFormat(VAO, 0, 2, GL_FLOAT, GL_FALSE, 0);

    glVertexArrayVertexBuffer(VAO, 0, VBO, 0, 2 * sizeof(float));

    // SHADER STORAGE BUFFER OBJECT
    GLuint ssbo1, ssbo2;
    void* ptr1;
    float* ptrfloat;

    glCreateBuffers(1, &ssbo2);

    glNamedBufferStorage(ssbo2, sizeof(float) * 4 * 10'000, NULL, GL_MAP_WRITE_BIT);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, ssbo2);

    
    // ----------------

    glCreateBuffers(1, &ssbo1);

    glNamedBufferStorage(ssbo1, sizeof(float) * 4 * 10'000, NULL, GL_MAP_WRITE_BIT);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, ssbo1);

    // Second SSBO

    // ------------------------------------------

    Shader shader1{"./shaders/ssbo1"};
    Shader shader2{"./shaders/ssbo2"};

    double elapsedTime;
    double deltaTime;
    double lastTime{ 0.0 };

    bool frameStep{ false };
    double lastStepTime{ 0.0 };
    bool pausedgame{false};

    glBindVertexArray(VAO);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Measure speed */
        elapsedTime = glfwGetTime();
        deltaTime = elapsedTime - lastTime;
        lastTime = elapsedTime;

        /* Input */
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        //std::cout << -std::abs(WINDOW::WIDTH - WINDOW::HEIGHT) / 2 + 100 * (int)xpos / std::min(WINDOW::WIDTH, WINDOW::HEIGHT) << ' ' << -std::abs(WINDOW::WIDTH - WINDOW::HEIGHT) / 2 + 100 * (std::min(WINDOW::WIDTH, WINDOW::HEIGHT) - (int)ypos) / std::min(WINDOW::WIDTH, WINDOW::HEIGHT) << '\n';

        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
        {
            glm::ivec2 gameMousePos;
            if (WINDOW::WIDTH < WINDOW::HEIGHT)
                gameMousePos = glm::ivec2(100 * (int)xpos / WINDOW::WIDTH, 100 * (WINDOW::HEIGHT - (int)ypos - (WINDOW::HEIGHT - WINDOW::WIDTH) / 2) / WINDOW::WIDTH);
            else
                gameMousePos = glm::ivec2(100 * ((int)xpos - (WINDOW::WIDTH - WINDOW::HEIGHT) / 2) / WINDOW::HEIGHT, 100 * (WINDOW::HEIGHT - (int)ypos) / WINDOW::HEIGHT);

            // FILL THE BUFFER POINTER
            ptr1 = glMapNamedBufferRange(ssbo1, 0, sizeof(float) * 4 * 10'000, GL_MAP_WRITE_BIT);
            if (ptr1 == NULL)
                std::cerr << "Failed to get buffer pointer\n";

            ptrfloat = (float*)ptr1;
            *(ptrfloat + 4 * (gameMousePos.x + gameMousePos.y * 100)) = 1.f;

            // UNMAP BUFFER AND SEND DATA TO BE READ BY OPENGL
            glUnmapNamedBuffer(ssbo1);
            // INVALIDATE THE BUFFER FOR ASYNCHRONISATION
            //glInvalidateBufferData(ssbo2);
        }
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        {
            if (!pausedgame)
                pausedgame = true;
            else
                pausedgame = false;
        }
        

        /* Game mechanics */

        /* Render here */
        if (elapsedTime - lastStepTime > 0.01)
        {
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            if (!(!frameStep && !pausedgame))
            {
                shader1.use();
                //glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
                glDrawArrays(GL_TRIANGLES, 0, 6);
                frameStep = false;
            }
            if (!frameStep && !pausedgame)
            {
                shader2.use();
                glDrawArrays(GL_TRIANGLES, 0, 6);
                //glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
                frameStep = true;
            }

            

            lastStepTime = elapsedTime;
            glfwSwapBuffers(window);
        }

        /* Swap front and back buffers */

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}