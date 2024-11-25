#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <chrono>
#include <thread>
#include "headers/camera.h"
#include "headers/linker.h"

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
        window = glfwCreateWindow(height, width, "GLFW", monitor, NULL);
        if(!window) {
            fprintf(stderr, "Nie udalo sie stworzyc okna z GLFW\n");
            glfwTerminate();
            exit(EXIT_FAILURE);
        }
        glfwMakeContextCurrent(window); // od okna

        // glew
        GLenum err = glewInit();
        if(err != GLEW_OK) {
            fprintf(stderr, "Nie udalo sie zainicjalizowac GLEW: %s\n", glewGetErrorString(err));
            glfwTerminate();
            exit(EXIT_FAILURE);
        }
        
        // glfw funckje
        glfwSetKeyCallback(window, processInput); // klawiatura
        glfwSetMouseButtonCallback(window, processMouseInput); // myszka
        glfwSwapInterval(1); // vsync
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // brak kursora

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
        // petla
        while(!glfwWindowShouldClose(window)) {
            // fps start
            auto start = std::chrono::high_resolution_clock::now();

            glfwPollEvents();

            double time = glfwGetTime();
            float deltaTime = static_cast<float>(time - lastTime); 
            lastTime = time;

            float angle = (float)time * 50.0f; // szybkosc rotacji

            movement(deltaTime); // wsad
            cameraMovement(); // obrot kamery

            // render
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glm::mat4 view = camera.GetViewMatrix(); 
            glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);

            glMatrixMode(GL_PROJECTION); 
            glLoadIdentity(); 
            glLoadMatrixf(glm::value_ptr(projection)); 

            glMatrixMode(GL_MODELVIEW); 
            glLoadIdentity(); 
            glLoadMatrixf(glm::value_ptr(view));

            glPushMatrix();
            glRotatef(angle, 0.0f, 1.0f, 0.0f); // rotacja na y

            glBegin(GL_TRIANGLES);
                glColor3f(1.0f,0.0f,0.0f); // czerwony
                glVertex3f(0.0f, 0.5f, 0.0f); //Gora trojkata (Przod)
                glColor3f(0.0f,1.0f,0.0f); // zielony
                glVertex3f(-0.5f,-0.5f, 0.5f); // lewa strona trojkata (Przod)
                glColor3f(0.0f,0.0f,1.0f); // niebieski
                glVertex3f(0.5f,-0.5f, 0.5f); // prawa strona trojkata (Przod)
                glColor3f(1.0f,0.0f,0.0f); // czerwony
                glVertex3f(0.0f, 0.5f, 0.0f); //Gora trojkata (prawo)
                glColor3f(0.0f,0.0f,1.0f); // niebieski
                glVertex3f(0.5f,-0.5f, 0.5f); // lewa strona trojkata (prawo)
                glColor3f(0.0f,1.0f,0.0f); // zielony
                glVertex3f(0.5f,-0.5f, -0.5f); // prawa strona trojkata (prawo)
                glColor3f(1.0f,0.0f,0.0f); // czerwony
                glVertex3f(0.0f, 0.5f, 0.0f); //Gora trojkata (tyl)
                glColor3f(0.0f,1.0f,0.0f); // zielony
                glVertex3f(0.5f,-0.5f, -0.5f); // lewa strona trojkata (tyl)
                glColor3f(0.0f,0.0f,1.0f); // niebieski
                glVertex3f(-0.5f,-0.5f, -0.5f); // prawa strona trojkata (tyl)
                glColor3f(1.0f,0.0f,0.0f); // czerwony
                glVertex3f(0.0f, 0.5f, 0.0f); //Gora trojkata (lewo)
                glColor3f(0.0f,0.0f,1.0f); // niebieski
                glVertex3f(-0.5f,-0.5f,-0.5f); // lewa strona trojkata (lewo)
                glColor3f(0.0f,1.0f,0.0f); // zielony
                glVertex3f(-0.5f,-0.5f, 0.5f); // prawa strona trojkata (lewo)
            glEnd();
            glPopMatrix();

            // podloga
            glBegin(GL_QUADS);
                glColor3f(0.4f,0.104f,0.221f); // rozowy taki ciemny dziwny
                glVertex3f(-10.0f,-1.0f,-10.f); //lewy dolny
                glVertex3f(-10.0f,-1.0f,10.0f); // lewy gorny
                glVertex3f(10.0f,-1.0f,10.0f); // prawy gorny
                glVertex3f(10.0f,-1.0f,-10.0f); // prawy dolny
            glEnd();


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
