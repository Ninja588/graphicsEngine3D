#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <chrono>
#include <thread>

class Engine {
public:
    Engine(int height, int width, bool fullscreen, int fpsLimit) : 
    height(height), width(width), fullscreen(fullscreen), fpsLimit(fpsLimit) {
        // glfw
        if(!glfwInit()) {
            fprintf(stderr, "Nie udalo sie zainicjalizowac GLFW\n");
        }
        // errory glfw
        glfwSetErrorCallback(error_callback);

        // okno
        GLFWmonitor* monitor = fullscreen ? glfwGetPrimaryMonitor() : NULL;
        window = glfwCreateWindow(height, width, "GLFW", monitor, NULL);
        if(!window) {
            fprintf(stderr, "Nie udalo sie stworzyc okna z GLFW\n");
            glfwTerminate();
        }
        glfwMakeContextCurrent(window); // od okna

        // glew
        GLenum err = glewInit();
        if(err != GLEW_OK) {
            fprintf(stderr, "Nie udalo sie zainicjalizowac GLEW: %s\n", glewGetErrorString(err));
            glfwTerminate();
            return;
        }
        
        // glfw funckje
        glfwSetKeyCallback(window, processInput); // klawiatura
        glfwSetMouseButtonCallback(window, processMouseInput); // myszka
        glfwSwapInterval(1); // vsync

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // tlo

        printf("Wersja openGL: %s\n", glGetString(GL_VERSION));
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

            // render
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            double time = glfwGetTime();
            float angle = (float)time * 50.0f; // szybkosc rotacji

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
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
        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, GLFW_TRUE);
        if(glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) glClearColor(0.8f, 0.3f, 0.3f, 1.0f);
        if(glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    }

    static void processMouseInput(GLFWwindow* window, int button, int action, int mods) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT)) printf("x: %lf, y: %lf\n",xpos, ypos);
    }

    // zmienne
    GLFWwindow* window;
    int width;
    int height;
    int fpsLimit;
    bool fullscreen;
};

int main() {
    Engine engine(800, 600, false, 165);
    engine.start();

    return 0;
}
