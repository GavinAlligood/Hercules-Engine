#include "hcpch.h"

#include "Test.h"

Hercules::Test::Test()
{
    glGenVertexArrays(2, &m_VertexArray);
    glBindVertexArray(m_VertexArray);

    shader = new Shader("Assets/Shaders/Vertex.shader",
        "Assets/Shaders/Fragment.shader");

    float vertices[] = {  ///texture
     -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  -0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  -0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  -0.5f, -0.5f,  -1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  -0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    //Binds automatically
     VertexBuffer vb(sizeof(vertices), vertices);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    unsigned int indices[] = { 0, 1, 3,
                              1, 2, 3 };

    IndexBuffer(sizeof(indices), indices);

    glEnable(GL_DEPTH_TEST);
}

Hercules::Test::~Test()
{
    delete shader;
}

void Hercules::Test::Draw(Texture& texture, glm::vec3 pos,
    glm::vec3 scale, glm::vec3 rotation, glm::vec4 color,

    glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp)
{
    glBindVertexArray(m_VertexArray);
    shader->Bind();
    //shader.SetTexture(0);
    shader->SetColor(color.x, color.y, color.z, color.w);
    shader->SetBool("mode", true);

    glm::mat4 model = glm::mat4(1.0f);
    //glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, pos);
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, scale);

    shader->SetMat4("model", model);

    glm::mat4 view;
    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

    shader->SetMat4("view", view);

    //i dont think this needs to be done every frame
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), 1920.0f / 1080.0f, 0.1f, 100.0f);
    shader->SetMat4("projection", projection);

    //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}