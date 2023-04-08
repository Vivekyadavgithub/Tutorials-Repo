#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 1800;
const unsigned int SCR_HEIGHT = 1400;

const char* vertexShaderSource = "#version 460 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec2 texcoord;\n"
"out vec2 tex;"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"   tex = texcoord;\n"
"}\0";
const char* fragmentShaderSource = "#version 460 core\n"
"out vec4 FragColor;\n"
"in vec2 tex;"
"uniform sampler2D ourTexture;"
"void main()\n"
"{\n"
"   FragColor = texture(ourTexture, tex);\n"
"}\0";

enum class shaderType {
    None,
    VERTEX_SHADER,
    FRAGMENT_SHADER
};

enum class bufferType {
    VERTEX_BUFFER,
    INDEX_BUFFER
};
void debug(unsigned int& shader, shaderType type = shaderType::None) {
    int success;
    char infoLog[512];
    if (type == shaderType::None)
        glGetShaderiv(shader, GL_LINK_STATUS, &success);
    else
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        if (type == shaderType::None)
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        else
            std::cout << "ERROR::SHADER::" << ((type == shaderType::VERTEX_SHADER) ? "VERTEX_SHADER" : "FRAGMENT_SHADER")
            << "::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

unsigned int compileShader(shaderType type, const char* shaderSource)
{
    unsigned int shader;
    if (type == shaderType::VERTEX_SHADER)
        shader = glCreateShader(GL_VERTEX_SHADER);
    else if (type == shaderType::FRAGMENT_SHADER)
        shader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(shader, 1, &shaderSource, NULL);
    glCompileShader(shader);

    debug(shader, type);

    return shader;
}

unsigned int linkShader() {
    unsigned int shaderProgram = glCreateProgram();

    unsigned int vertexShader = compileShader(shaderType::VERTEX_SHADER, vertexShaderSource);
    unsigned int fragmentShader = compileShader(shaderType::FRAGMENT_SHADER, fragmentShaderSource);

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    debug(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

void createBuffer(std::vector<float>& data, unsigned int& bo, bufferType type) {
    glGenBuffers(1, &bo);

    if (type == bufferType::VERTEX_BUFFER) {
        glBindBuffer(GL_ARRAY_BUFFER, bo);
        glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);
    }
    else {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);
    }
}

void unbindTexture() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void bindTexture(unsigned int& texture) {
    glBindTexture(GL_TEXTURE_2D, texture);
}

unsigned int setTexture(std::string path) {
    int width, height, nrChannels;
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

    unsigned int texture;
    glGenTextures(1, &texture);
    bindTexture(texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    return texture;
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    
    unsigned int wallTexture = setTexture("C:/project/Tuts/Opengl/assets/wall.jpg");
    unsigned int shaderProgram = linkShader();

    std::vector<float>vertices{
         -0.5f, -0.5f, 0.0f, 0.5f, 0.0f,
          0.5f, -0.5f, 0.0f, 0.0f, 0.5f,
          0.0f,  0.5f, 0.0f, 1.0f, 0.0f
    };
 
    std::vector<unsigned int> indices{
        0, 1, 3,
        1, 2, 3 
    };

    unsigned int VBO, VAO;


    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);
    createBuffer(vertices, VBO, bufferType::VERTEX_BUFFER);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);


    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO); 
        glDrawArrays(GL_TRIANGLES, 0, 6);
        //glDrawElement(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}