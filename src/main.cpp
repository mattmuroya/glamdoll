#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "cube.h"

#include "camera.h"
#include "shader.h"
#include "vao.h"
#include "vbo.h"

// -----------------------------------------------------------------------------
// GLOBALS
// -----------------------------------------------------------------------------

const int INIT_WINDOW_SIZE = 600;

float fov = 70.0f;
float aspect = 1.0f;
float nearPlane = 1.0f;
float farPlane = 1000.0;

float xRot = 0.0f, yRot = 0.0f;
float xMouse = 0.0f, yMouse = 0.0f;

// -----------------------------------------------------------------------------
// FUNCTION PROTOTYPES
// -----------------------------------------------------------------------------

void framebuffer_size_callback(GLFWwindow*, int, int);
void window_pos_callback(GLFWwindow*, int, int);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

void resizeViewport(GLFWwindow*, int, int);
void processInput(GLFWwindow*);

// -----------------------------------------------------------------------------
// MAIN FUNCTION
// -----------------------------------------------------------------------------

int main()
{
    // -------------------------------------------------------------------------
    // Initialize GLFW window
    // -------------------------------------------------------------------------

    glfwInit();

    // Specify OpenGL version 3.3, core-profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // Create window object and verify it loaded correctly
    GLFWwindow* window = glfwCreateWindow(INIT_WINDOW_SIZE, INIT_WINDOW_SIZE, "glamdoll", NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // -------------------------------------------------------------------------
    // Set callback functions
    // -------------------------------------------------------------------------

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetWindowPosCallback(window, window_pos_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // -------------------------------------------------------------------------
    // Load and verify GLAD (OpenGL function pointers)
    // -------------------------------------------------------------------------

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // -------------------------------------------------------------------------
    // Set OpenGL global state
    // -------------------------------------------------------------------------

    glEnable(GL_DEPTH_TEST);

    // -------------------------------------------------------------------------
    // Initialize shaders
    // -------------------------------------------------------------------------

    Shader shader;
    shader.create("shader.vert", "shader.frag");

    // -------------------------------------------------------------------------
    // Initialize vertex buffer and array objects
    // -------------------------------------------------------------------------

    VertexBufferObject vertexVbo, colorVbo, normalVbo;
    VertexArrayObject vao;

    vertexVbo.upload(sizeof(vertices), vertices);
    colorVbo.upload(sizeof(colors), colors);
    normalVbo.upload(sizeof(normals), normals);

    vao.add(vertexVbo, 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (void*)0);
    vao.add(colorVbo, 1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (void*)0);
    vao.add(normalVbo, 2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (void*)0);

    // -------------------------------------------------------------------------
    // Initialize camera
    // -------------------------------------------------------------------------

    Camera camera;

    camera.setPosition(0.0f, 0.0f, 5.0f);
    camera.setTarget(0.0f, 0.0f, 0.0f);
    camera.setUp(0.0f, 1.0f, 0.0f);

    // -------------------------------------------------------------------------
    // Render loop
    // -------------------------------------------------------------------------

    while (!glfwWindowShouldClose(window))
    {
        // MacOS fullscreen bug workaround (https://github.com/glfw/glfw/issues/2251)
        // Entering fullscreen doesn't trigger framebuffer or position callback
#ifdef __APPLE__
        window_pos_callback(window, 0, 0);
#endif

        // Get inputs
        processInput(window);

        // Clear color buffer
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Set state
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Activate shader
        shader.use();

        // Bind array
        vao.bind();

        // ===== Model =====

        // Identity matrix
        glm::mat4 modelMatrix = glm::mat4(1.0f);

        // Scale
        // modelMatrix = glm::scale(modelMatrix, glm::vec3(Scale, Scale, Scale));

        // Rotate
        // modelMatrix = glm::rotate(modelMatrix, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f)); // Auto rotate
        modelMatrix = glm::rotate(modelMatrix, (float)glm::radians(xRot), glm::vec3(1.0f, 0.0f, 0.0f)); // Rotate around x-axis
        modelMatrix = glm::rotate(modelMatrix, (float)glm::radians(yRot), glm::vec3(0.0f, 1.0f, 0.0f)); // Rotate around y-axis

        // Translate
        // modelMatrix = glm::translate(modelMatrix, glm::vec3(-GRID_SIZE / (float)2, 0, -GRID_SIZE / (float)2));

        // Set model matrix
        shader.setMat4("uModelMatrix", modelMatrix);

        // ===== Normal =====

        glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(modelMatrix)));

        // Set normal matrix
        shader.setMat3("uNormalMatrix", normalMatrix);

        // ===== Set camera =====

        // TODO: Use globals to track and set camera position/target

        // Set view matrix
        shader.setMat4("uViewMatrix", camera.getViewMatrix());

        // ===== Projection =====

        glm::mat4 projectionMatrix = glm::perspective(glm::radians(fov), aspect, nearPlane, farPlane);

        // Set projection matrix
        shader.setMat4("uProjectionMatrix", projectionMatrix);

        // ===== Set uniforms =====
        shader.setFloat("uKa", 0.8f);
        shader.setFloat("uKd", 0.2f);
        shader.setFloat("uKs", 0.2f);
        shader.setFloat("uSh", 1.0f);

        // ===== Render =====

        glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices)); // Use state

        // Swap buffers
        glfwSwapBuffers(window);

        // Poll IO
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

// -----------------------------------------------------------------------------
// CALLBACK / INPUT PROCESSING FUNCTIONS
// -----------------------------------------------------------------------------

// Adjust viewport on framebuffer resize
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    resizeViewport(window, width, height);
}

void window_pos_callback(GLFWwindow* window, int xpos, int ypos)
{
    int fbWidth, fbHeight;
    glfwGetFramebufferSize(window, &fbWidth, &fbHeight);

    resizeViewport(window, fbWidth, fbHeight);
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        int dx = (float)xpos - xMouse;
        int dy = (float)ypos - yMouse;

        xRot += dy; // Vertical mouse movement -> rotation around x-axis
        yRot += dx; // Horizontal mouse movement -> rotation around y-axis
    }

    xMouse = (float)xpos;
    yMouse = (float)ypos;
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    fov -= (float)yoffset;

    if (fov < 0) fov = 0;
    if (fov > 170) fov = 170;
}

void resizeViewport(GLFWwindow* window, int fbWidth, int fbHeight)
{
    int minDimension = fbWidth < fbHeight ? fbWidth : fbHeight;

    int originX = (fbWidth - minDimension) / 2;
    int originY = (fbHeight - minDimension) / 2;

    glViewport(originX, originY, minDimension, minDimension);
}

// Process keyboard input
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}
