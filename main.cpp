//#include <GL/glew.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <chrono>
#include <thread>
#include "headers/camera.h"
#include "headers/renderableObject.h"
#include "headers/triangle3D.h"
#include "headers/textureLoader.h"
#include "headers/cube.h"
#include "headers/linker.h"
#include "headers/shader.h"

class Engine {
public:
    Engine(int height, int width, bool fullscreen, int fpsLimit) : 
    height(height), width(width), fullscreen(fullscreen), fpsLimit(fpsLimit), camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f) {
        // glfw
        if(!glfwInit()) {
            fprintf(stderr, "Nie udalo sie zainicjalizowac GLFW\n");
            exit(EXIT_FAILURE);
        }
        // errory glfw
        glfwSetErrorCallback(error_callback);

        // okno
        GLFWmonitor* monitor = fullscreen ? glfwGetPrimaryMonitor() : NULL;
        window = glfwCreateWindow(height, width, "GLFW", NULL, NULL);
        if(!window) {
            fprintf(stderr, "Nie udalo sie stworzyc okna z GLFW\n");
            glfwTerminate();
            exit(EXIT_FAILURE);
        }
        if(fullscreen) {
            const GLFWvidmode* mode = glfwGetVideoMode(monitor);
            glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
            height = mode->height;
            width = mode->width;
        }
        glfwMakeContextCurrent(window); // od okna

        // glew
        // GLenum err = glewInit();
        // if(err != GLEW_OK) {
        //     fprintf(stderr, "Nie udalo sie zainicjalizowac GLEW: %s\n", glewGetErrorString(err));
        //     glfwTerminate();
        //     exit(EXIT_FAILURE);
        // }

        if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            exit(EXIT_FAILURE);
        }
        

        // glfw funckje
        glfwSetKeyCallback(window, processInput); // klawiatura
        glfwSetMouseButtonCallback(window, processMouseInput); // myszka
        glfwSwapInterval(1); // vsync
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // brak kursora
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // bufor

        glfwSetWindowSize(window, height, width);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // tlo

        glfwSetWindowUserPointer(window, this);

        //printf("Wersja openGL: %s\n", glGetString(GL_VERSION));
    }

    ~Engine() { 
        glfwDestroyWindow(window); 
        glfwTerminate(); 
    }

    void start() {
        const double frameTime = 1.0 / fpsLimit;
        double lastTime = 0.0;


        const std::vector<float> surfaceVertex = {
            -10.0f,-1.0f,-10.f,
            -10.0f,-1.0f,10.0f,
            10.0f,-1.0f,10.0f,
            10.0f,-1.0f,-10.0f
        };
        std::vector colorS = {
            //0.4f,0.104f,0.221f
            1.0f,1.0f,1.0f
        };
        const std::vector<float> texS = {
            0.0,0.0,
            0.0,1.0,
            1.0,1.0,
            1.0,0.0
        };


        std::vector<float> linesVertices = { 
            0.0f, 0.0f, 0.0f, 
            1.0f, 0.0f, 0.0f 
        };
        std::vector<float> linesColors = { 
            1.0f, 0.0f, 0.0f, 
            0.0f, 1.0f, 0.0f 
        };
        RenderableObject lines(linesVertices, linesColors, {0.0, 0.0}, GL_LINES, glm::vec3(2.0f,0.0f,0.0f));


        std::vector<float> pointsVertices = { 
            0.0f, 0.0f, 0.0f, 
            1.0f, 1.0f, 1.0f 
        };
        std::vector<float> pointsColors = { 
            1.0f, 0.0f, 0.0f, 
            0.0f, 1.0f, 0.0f
        };
        RenderableObject points(pointsVertices, pointsColors, {0.0, 0.0}, GL_POINTS, glm::vec3(-2.0f,0.0f,0.0f));


        std::vector<float> lineStripVertices = { 
            0.0f, 0.0f, 0.0f, 
            1.0f, 0.0f, 0.0f, 
            1.0f, 1.0f, 0.0f 
        };
        std::vector<float> lineStripColors = { 
            1.0f, 0.0f, 0.0f, 
            0.0f, 1.0f, 0.0f, 
            0.0f, 0.0f, 1.0f 
        };
        RenderableObject lineStrip(lineStripVertices, lineStripColors, {0.0,0.0}, GL_LINE_STRIP, glm::vec3(-1.5f,0.0f,0.0f));


        std::vector<float> triangleVertices = {
            0.0f, 0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f
        };
        std::vector<float> triangleColors = {
            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f
        };
        RenderableObject triangle(triangleVertices, triangleColors, {0.0, 0.0, 0.5, 1.0, 1.0, 0.0}, GL_TRIANGLES, glm::vec3(-3.0f,0.0f,0.0f));


        std::vector<float> triangleStripVertices = {
            0.0f, 0.5f, 0.0f,
            -0.5f, -0.5f, 0.5f,
            0.5f, -0.5f, 0.5f,
            0.0f, -0.5f, -0.5f
        };
        std::vector<float> triangleStripColors = {
            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f,
            1.0f, 1.0f, 0.0f
        };
        RenderableObject triangleStrip(triangleStripVertices, triangleStripColors, {0.0, 0.0, 0.5, 1.0, 1.0, 0.0}, GL_TRIANGLE_STRIP, glm::vec3(0.0f,1.0f,0.0f));


        RenderableObject* triangle3D = new Triangle3D(glm::vec3(0.0f,0.0f,0.0f));
        RenderableObject surface(surfaceVertex, colorS, texS, GL_QUADS);

        GLuint textureID = TextureLoader::loadTexture("wall.jpg"); // tekstura

        Cube cube(glm::vec3(0.0f, 1.0f, -5.0f));

        std::vector<float> colorVertex = {
            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 
            0.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, 1.0f, 0.0f, 
            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 
            1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, 1.0f, 0.0f
        };
        //triangle3D->setColor(colorVertex);

        Shader shader("texture.vs","texture.fs");

        // petla
        while(!glfwWindowShouldClose(window)) {
            // fps start
            auto start = std::chrono::high_resolution_clock::now();

            glfwPollEvents();

            double time = glfwGetTime();
            float deltaTime = static_cast<float>(time - lastTime);
            lastTime = time;

            movement(deltaTime); // wsad
            cameraMovement(); // obrot kamery

            // render
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glm::mat4 view = camera.GetViewMatrix();
            glm::mat4 projection = glm::perspective(glm::radians(60.0f), (float)width / (float)height, 0.1f, 100.0f);

            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glLoadMatrixf(glm::value_ptr(projection));

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            glLoadMatrixf(glm::value_ptr(view));

            // trojkat
            triangle3D->updateRotation(deltaTime);
            triangle3D->draw(view, projection, textureID,shader);
            //triangle3D->translate(glm::vec3(1.0,2.0,1.0));
            //triangle3D->scale(glm::vec3(5.0));

            //szescian
            //cube.updateRotation(deltaTime);
            //cube.draw(view, projection, textureID);
            //cube.scale(glm::vec3(10));
            //cube.translate(glm::vec3(5.0,5.0,5.0));
            
            // podloga
            surface.draw(view, projection, textureID,shader);

            //prymitwyy
            // lines.draw(view, projection, textureID,shader);
            // lineStrip.draw(view, projection, textureID,shader);
            // points.draw(view, projection, textureID,shader);
            // triangle.draw(view, projection, textureID,shader);
            // triangleStrip.draw(view, projection, textureID,shader);
            
            glfwSwapBuffers(window);

            // fps end
            auto end = std::chrono::high_resolution_clock::now(); 
            std::chrono::duration<double> elapsed = end - start; 
            if(elapsed.count() < frameTime) { 
                std::this_thread::sleep_for(std::chrono::duration<double>(frameTime - elapsed.count())); 
            }
        }
    }

private:
    static void error_callback(int error, const char* description) {
        fprintf(stderr, "Error: %s\n", description);
    }

    static void processInput(GLFWwindow *window, int key, int scancode, int action, int mods) {
        // Engine* engine = static_cast<Engine*>(glfwGetWindowUserPointer(window)); 
        // if(action == GLFW_PRESS || action == GLFW_REPEAT) { 
        //     engine->camera.ProcessKeyboard(key, 0.1f);
        // }
        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, GLFW_TRUE);
        if(glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) glClearColor(0.8f, 0.3f, 0.3f, 1.0f);
        if(glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        if(glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) glfwSetWindowSize(window, 1920, 1080);
        if(glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) glfwSetWindowSize(window, 800, 600);
    }

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }

    static void processMouseInput(GLFWwindow* window, int button, int action, int mods) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT)) printf("x: %lf, y: %lf\n",xpos, ypos);
    }

    void movement(float deltaTime) { 
        if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) camera.ProcessKeyboard(GLFW_KEY_W, deltaTime); 
        if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) camera.ProcessKeyboard(GLFW_KEY_S, deltaTime); 
        if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) camera.ProcessKeyboard(GLFW_KEY_A, deltaTime); 
        if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) camera.ProcessKeyboard(GLFW_KEY_D, deltaTime); 
    }

    void cameraMovement() {
        Engine* engine = static_cast<Engine*>(glfwGetWindowUserPointer(window));
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        if(engine->firstMouse) {
            engine->lastX = xpos;
            engine->lastY = ypos;
            engine->firstMouse = false;
        }

        float xoffset = xpos - engine->lastX; 
        float yoffset = engine->lastY - ypos;

        engine->lastX = xpos; 
        engine->lastY = ypos;

        engine->camera.ProcessMouseMovement(xoffset, yoffset);
    }

    // zmienne
    GLFWwindow* window;
    GLFWwindow* window2;
    int width;
    int height;
    int fpsLimit;
    bool fullscreen;
    double lastTime = 0.0;
    bool firstMouse = true; 
    float lastX = width / 2.0f; 
    float lastY = height / 2.0f;
    Camera camera;
};

int main() {
    Engine engine(800, 600, false, 165);
    engine.start();

    return 0;
}
