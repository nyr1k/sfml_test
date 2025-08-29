#include <iostream>
#include <math.h>
#include <glad/gl.h>
#include <SFML/Window.hpp>
#include <filesystem>
#include "shader.h"

const float gradientRate = 0.01f;
int first = 3, second = 10, third = 17;

void gradientTriangleVerticeOne(float *vertices);
void gradientTriangleVerticeTwo(float *vertices);
void gradientTriangleVerticeThree(float *vertices);

int main()
{
    // create the window
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antiAliasingLevel = 4;
    settings.majorVersion = 3;
    settings.minorVersion = 3;

    sf::Window window(sf::VideoMode({800, 600}), "OpenGL", sf::Style::Default, sf::State::Windowed, settings);
    window.setVerticalSyncEnabled(true);

    // activate the window
    if (!window.setActive(true)) {
        std::cerr << "failed to activate opengl context" << std::endl;
        return -1;
    }

    // load resources, initialize the OpenGL states, ..
    // set up GLAD
    if(!gladLoadGL((GLADloadfunc)sf::Context::getFunction)){
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    };

    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    glViewport(0, 0, 800, 600);

    // triangle 
    float vertices[] =  {
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 
        0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };

    unsigned int VBO, VAO; 
    glGenBuffers(1, &VBO); 
    glGenVertexArrays(1, &VAO);
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    auto base = std::filesystem::current_path().parent_path()/"src";
    Shader ourShader((base/"shader.vs").c_str(), (base/"shader.fs").c_str());
    
    // run the main loop
    bool running = true;
    float red = 1.0f, green = 1.0f, blue = 1.0f; 
    sf::Clock time;
    while (running)
    {
        // handle events
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                // end the program
                running = false;
            }
            else if (const auto* resized = event->getIf<sf::Event::Resized>())
            {
                // adjust the viewport when the window is resized
                glViewport(0, 0, resized->size.x, resized->size.y);
            }
        }
        // clear color
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        
        // clear the buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // draw...
        ourShader.use();
        ourShader.setFloat("time", sin(time.getElapsedTime().asSeconds()));

        gradientTriangleVerticeOne(vertices);
        gradientTriangleVerticeTwo(vertices);
        gradientTriangleVerticeThree(vertices);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        // end the current frame (internally swaps the front and back buffers)
        window.display();
    }
    window.close();
    
    return 0;
}

void gradientTriangleVerticeOne(float *vertices) {
    if(first == 5 && vertices[first] <= 0.0f) {
        vertices[first] = 0.0f;
        first = 3;
    } else if (vertices[first] <= 0.0f) {
        vertices[first] = 0.0f;
        first++;
    } 
    if(vertices[first] > 0.0f && first != 5) {
        vertices[first] -= gradientRate;
        vertices[first+1] += gradientRate;
    } else if (vertices[first] > 0.0f && first == 5) {
        vertices[first] -= gradientRate;
        vertices[first-2] += gradientRate;
    }
}

void gradientTriangleVerticeTwo(float *vertices) {
    if(second == 11 && vertices[second] <= 0.0f) {
        vertices[second] = 0.0f;
        second = 9;
    } else if (vertices[second] <= 0.0f) {
        vertices[second] = 0.0f;
        second++;
    } 
    if(vertices[second] > 0.0f && second != 11) {
        vertices[second] -= gradientRate;
        vertices[second+1] += gradientRate;
    } else if (vertices[second] > 0.0f && second == 11) {
        vertices[second] -= gradientRate;
        vertices[second-2] += gradientRate;
    }
}

void gradientTriangleVerticeThree(float *vertices) {
    if(third == 17 && vertices[third] <= 0.0f) {
        vertices[third] = 0.0f;
        third = 15;
    } else if (vertices[third] <= 0.0f) {
        vertices[third] = 0.0f;
        third++;
    } 
    if(vertices[third] > 0.0f && third != 17) {
        vertices[third] -= gradientRate;
        vertices[third+1] += gradientRate;
    } else if (vertices[third] > 0.0f && third == 17) {
        vertices[third] -= gradientRate;
        vertices[third-2] += gradientRate;
    }
}