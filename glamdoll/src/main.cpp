#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader.cpp"

// -----------------------------------------------------------------------------
// GLOBALS
// -----------------------------------------------------------------------------

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

// -----------------------------------------------------------------------------
// FUNCTION PROTOTYPES
// -----------------------------------------------------------------------------

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
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "glamdoll", NULL, NULL);

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

    glfwSetFramebufferSizeCallback(window, resizeViewport);

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

    Shader shader("shader.vert", "shader.frag");

    // -------------------------------------------------------------------------
    // Initialize vertex buffer and array objects
    // -------------------------------------------------------------------------

    float vertices[] = {
        // Front face
        -1.0f, -1.0f,  1.0f,  // Bottom-left
        1.0f, -1.0f,  1.0f,   // Bottom-right
        1.0f,  1.0f,  1.0f,   // Top-right
        -1.0f, -1.0f,  1.0f,  // Bottom-left
        1.0f,  1.0f,  1.0f,   // Top-right
        -1.0f,  1.0f,  1.0f,  // Top-left

        // Back face
        -1.0f, -1.0f, -1.0f,  // Bottom-left
        -1.0f,  1.0f, -1.0f,  // Top-left
        1.0f,  1.0f, -1.0f,   // Top-right
        -1.0f, -1.0f, -1.0f,  // Bottom-left
        1.0f,  1.0f, -1.0f,   // Top-right
        1.0f, -1.0f, -1.0f,   // Bottom-right

        // Left face
        -1.0f, -1.0f, -1.0f,  // Bottom-left
        -1.0f, -1.0f,  1.0f,  // Bottom-right
        -1.0f,  1.0f,  1.0f,  // Top-right
        -1.0f, -1.0f, -1.0f,  // Bottom-left
        -1.0f,  1.0f,  1.0f,  // Top-right
        -1.0f,  1.0f, -1.0f,  // Top-left

        // Right face
        1.0f, -1.0f, -1.0f,  // Bottom-left
        1.0f,  1.0f, -1.0f,  // Top-left
        1.0f,  1.0f,  1.0f,  // Top-right
        1.0f, -1.0f, -1.0f,  // Bottom-left
        1.0f,  1.0f,  1.0f,  // Top-right
        1.0f, -1.0f,  1.0f,  // Bottom-right

        // Top face
        -1.0f,  1.0f, -1.0f,  // Bottom-left
        -1.0f,  1.0f,  1.0f,  // Bottom-right
        1.0f,  1.0f,  1.0f,   // Top-right
        -1.0f,  1.0f, -1.0f,  // Bottom-left
        1.0f,  1.0f,  1.0f,   // Top-right
        1.0f,  1.0f, -1.0f,   // Top-left

        // Bottom face
        -1.0f, -1.0f, -1.0f,  // Bottom-left
        1.0f, -1.0f, -1.0f,   // Bottom-right
        1.0f, -1.0f,  1.0f,   // Top-right
        -1.0f, -1.0f, -1.0f,  // Bottom-left
        1.0f, -1.0f,  1.0f,   // Top-right
        -1.0f, -1.0f,  1.0f   // Top-left
    };

    float colors[] = {
        // Front face
        0.0f,  0.0f,  1.0f,
        0.0f,  0.0f,  1.0f,
        0.0f,  0.0f,  1.0f,
        0.0f,  0.0f,  1.0f,
        0.0f,  0.0f,  1.0f,
        0.0f,  0.0f,  1.0f,

        // Back face
        0.0f,  0.0f,  1.0f,
        0.0f,  0.0f,  1.0f,
        0.0f,  0.0f,  1.0f,
        0.0f,  0.0f,  1.0f,
        0.0f,  0.0f,  1.0f,
        0.0f,  0.0f,  1.0f,

        // Left face
        1.0f,  0.0f,  0.0f,
        1.0f,  0.0f,  0.0f,
        1.0f,  0.0f,  0.0f,
        1.0f,  0.0f,  0.0f,
        1.0f,  0.0f,  0.0f,
        1.0f,  0.0f,  0.0f,

        // Right face
        1.0f,  0.0f,  0.0f,
        1.0f,  0.0f,  0.0f,
        1.0f,  0.0f,  0.0f,
        1.0f,  0.0f,  0.0f,
        1.0f,  0.0f,  0.0f,
        1.0f,  0.0f,  0.0f,

        // Top face
        0.0f,  1.0f,  0.0f,
        0.0f,  1.0f,  0.0f,
        0.0f,  1.0f,  0.0f,
        0.0f,  1.0f,  0.0f,
        0.0f,  1.0f,  0.0f,
        0.0f,  1.0f,  0.0f,

        // Bottom face
        0.0f,  1.0f,  0.0f,
        0.0f,  1.0f,  0.0f,
        0.0f,  1.0f,  0.0f,
        0.0f,  1.0f,  0.0f,
        0.0f,  1.0f,  0.0f,
        0.0f,  1.0f,  0.0f,
    };

    float normals[] = {
        // Front face
        0.0f,  0.0f,  1.0f,
        0.0f,  0.0f,  1.0f,
        0.0f,  0.0f,  1.0f,
        0.0f,  0.0f,  1.0f,
        0.0f,  0.0f,  1.0f,
        0.0f,  0.0f,  1.0f,

        // Back face
        0.0f,  0.0f, -1.0f,
        0.0f,  0.0f, -1.0f,
        0.0f,  0.0f, -1.0f,
        0.0f,  0.0f, -1.0f,
        0.0f,  0.0f, -1.0f,
        0.0f,  0.0f, -1.0f,

        // Left face
        -1.0f,  0.0f,  0.0f,
        -1.0f,  0.0f,  0.0f,
        -1.0f,  0.0f,  0.0f,
        -1.0f,  0.0f,  0.0f,
        -1.0f,  0.0f,  0.0f,
        -1.0f,  0.0f,  0.0f,

        // Right face
        1.0f,  0.0f,  0.0f,
        1.0f,  0.0f,  0.0f,
        1.0f,  0.0f,  0.0f,
        1.0f,  0.0f,  0.0f,
        1.0f,  0.0f,  0.0f,
        1.0f,  0.0f,  0.0f,

        // Top face
        0.0f,  1.0f,  0.0f,
        0.0f,  1.0f,  0.0f,
        0.0f,  1.0f,  0.0f,
        0.0f,  1.0f,  0.0f,
        0.0f,  1.0f,  0.0f,
        0.0f,  1.0f,  0.0f,

        // Bottom face
        0.0f, -1.0f,  0.0f,
        0.0f, -1.0f,  0.0f,
        0.0f, -1.0f,  0.0f,
        0.0f, -1.0f,  0.0f,
        0.0f, -1.0f,  0.0f,
        0.0f, -1.0f,  0.0f
    };

    unsigned int VAO, vertexBuffer, colorBuffer, normalBuffer;

    // Create and bind vertex array object
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Create, bind, and populate vertex buffer objects
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(
        0,                 // Attrib position 0 (for shader `in` variable)
        3,                 // Number of array elements per attribute (e.g. three components for each vertex)
        GL_FLOAT,          // Component type
        GL_FALSE,          // Whether to normalize
        3 * sizeof(float), // Stride (distance between starting bytes of consecutive attributes)
        (void*)0 // Offset of first attribute in buffer
    );
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        3 * sizeof(float),
        (void*)0
    );
    glEnableVertexAttribArray(1);

    glGenBuffers(1, &normalBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(normals), normals, GL_STATIC_DRAW);
    glVertexAttribPointer(
        2,
        3,
        GL_FLOAT,
        GL_FALSE,
        3 * sizeof(float),
        (void*)0
    );
    glEnableVertexAttribArray(2);

    // Unbind vertex array object
    glBindVertexArray(0);

    // -------------------------------------------------------------------------
    // Render loop
    // -------------------------------------------------------------------------
    while (!glfwWindowShouldClose(window))
    {
        // Get inputs
        processInput(window);

        // Clear color buffer
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Set state
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Activate shader
        shader.use();

        // Bind array
        glBindVertexArray(VAO);

        // ===== Model =====

        // Identity matrix
        glm::mat4 modelMatrix = glm::mat4(1.f);

        // Scale, Rotate, Translate
        modelMatrix = glm::rotate(modelMatrix, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));

        // Set model matrix
        shader.setMat4("uModelMatrix", modelMatrix);

        // ===== Normal =====

        glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(modelMatrix)));

        // Set normal matrix
        shader.setMat3("uNormalMatrix", normalMatrix);

        // ===== Set camera =====

        glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 5.0f); // Camera position
        glm::vec3 cameraDir = glm::vec3(0.0f, 0.0f, 0.0f); // Target position
        glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f); // Up vector

        glm::mat4 viewMatrix = glm::lookAt(cameraPos, cameraDir, cameraUp);

        // Set view matrix
        shader.setMat4("uViewMatrix", viewMatrix);

        // ===== Projection =====

        int fbWidth, fbHeight;
        glfwGetFramebufferSize(window, &fbWidth, &fbHeight);

        float aspectRatio = (float)fbWidth / (float)fbHeight;

        glm::mat4 projectionMatrix = glm::perspective(glm::radians(70.f), aspectRatio, 0.1f, 1000.f);

        // Set projection matrix
        shader.setMat4("uProjectionMatrix", projectionMatrix);

        // ===== Set uniforms =====
        shader.setFloat("uKa", 0.2f);
        shader.setFloat("uKd", 0.8f);
        shader.setFloat("uKs", 0.4f);
        shader.setFloat("uSh", 0.9f);

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
void resizeViewport(GLFWwindow* window, int width, int height)
{
    int newWidth = width;
    int newHeight = height;

    std::cout << newWidth << ", " << newHeight << std::endl;

    glViewport(0, 0, newWidth, newHeight);
}

// Process keyboard input
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}
