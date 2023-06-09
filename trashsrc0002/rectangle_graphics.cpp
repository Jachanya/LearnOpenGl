#include "rectangle_graphics.hpp"

namespace jachan
{
    RectangleGraphicsComponent::RectangleGraphicsComponent()
    : shader{"shadersProgram/shader.vs", "shadersProgram/shader.fs"}
    {
        createContext();
    }

    RectangleGraphicsComponent::RectangleGraphicsComponent(const char* vertexPath, const char* fragmentPath)
    : shader{vertexPath, fragmentPath}
    {
        createContext();
    }

    RectangleGraphicsComponent::~RectangleGraphicsComponent(){
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }

    void RectangleGraphicsComponent::createContext(){
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(0));
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, 0); 
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); 
        glBindVertexArray(0);
    }
    
    void RectangleGraphicsComponent::update(Entity &entity){
        shader.use();
        glBindVertexArray(VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); 

        glm::mat4 transform = glm::mat4(1.0f);
        float colorAmount = static_cast<float>(sin(glfwGetTime()));
        // transform = glm::translate(transform, glm::vec3(position[0], position[1], position[2]));
        //transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f)); 
        // transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        // transform = glm::scale(transform, glm::vec3(15, 15, 15)); 

        // const float radius = 10.0f;

        // float baseAngle = 1.5f * 3.142f;
        // float halfAngleRange = 0.25f * 3.142f;
        float camZ = static_cast<float>(cos(glfwGetTime()));
        float camY = static_cast<float>(sin(glfwGetTime()));
        // float angle = halfAngleRange * c + baseAngle;

        // float camY =  static_cast<float>(sin(angle));
        // float camX =  static_cast<float>(cos(angle));
        // transform = glm::translate(transform, glm::vec3(camX, camY, 0.0));

        // transform = glm::rotate(transform, glm::radians(camY*depth*60.0f), glm::vec3(0.0f, 0.0f, 1.0f));

        glm::mat4 view = glm::mat4(1.0f);
        view = glm::lookAt(glm::vec3(0.0, 0.0, 10.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0)); 
        // view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        view = glm::rotate(view, glm::radians(camY * 90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        view = glm::rotate(view, glm::radians(camY * 180.0f), glm::vec3(1.0f, 0.0f, 0.0f));

        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
        
        // get their uniform location and set matrix (using glm::value_ptr)

        shader.setGlUniformMatrix4fv("projection", glm::value_ptr(projection));
        shader.setGlUniformMatrix4fv("view", glm::value_ptr(view));
        shader.setGlUniformMatrix4fv("transform", glm::value_ptr(transform));

        unsigned int colorRectLoc = glGetUniformLocation(shader.ID, "rectColor");
        glUniform3f(colorRectLoc, 0.3, colorAmount, camY);
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
};