#include "hcpch.h"

#include "Cube.h"

Hercules::Cube::Cube()
{
	//float vertices[] = {  ///texture
 //    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
 //    0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
 //    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
 //    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
 //   -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
 //   -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

 //   -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
 //    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
 //    0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
 //    0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
 //   -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
 //   -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

 //   -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
 //   -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
 //   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
 //   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
 //   -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
 //   -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

 //    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
 //    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
 //    0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
 //    0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
 //    0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
 //    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

 //   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
 //    0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
 //    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
 //    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
 //   -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
 //   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

 //   -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
 //    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
 //    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
 //    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
 //   -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
 //   -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	//};

	////Binds automatically
	//VertexBuffer vb(sizeof(vertices), vertices);

	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
	//glEnableVertexAttribArray(0);

	//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);

	//unsigned int indices[] = { 0, 1, 3,
	//						  1, 2, 3 };

	//IndexBuffer ib(sizeof(indices), indices);

	////vertexPath = "Assets/Shaders/Vertex.shader";
	////fragmentPath = "Assets/Shaders/Fragment.shader";

	////shader = new Shader(vertexPath, fragmentPath);

	///*shader->Bind();*/
	////TODO: change this to shader->UseColor for readability
	////shader->SetBool("UseColor", false);

    glEnable(GL_DEPTH_TEST);
}

Hercules::Cube::~Cube()
{
}

void Hercules::Cube::Draw(Texture texture, glm::vec3 pos, glm::vec3 scale, glm::vec3 rotation,
    glm::vec3 color)
{
    float vertices[] = {  ///texture
     -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
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

    IndexBuffer ib(sizeof(indices), indices);

    Shader shader("Assets/Shaders/Vertex.shader", 
        "Assets/Shaders/Fragment.shader");

    shader.Bind();
    //shader.SetTexture(0);
    shader.SetColor(color.x, color.y, color.z, 1.0f);

    glm::mat4 model = glm::mat4(1.0f);
    //glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(40.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    shader.SetMat4("model", model);

    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, pos);
    unsigned int viewLoc = glGetUniformLocation(shader.GetId(), "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);

    //scale
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), 1920.0f / 1080.0f, 0.1f, 100.0f);
    shader.SetMat4("projection", projection);

    //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Hercules::Cube::Update()
{
    
}

//void Hercules::Cube::Translate(float x, float y, float z)
//{
//    glm::mat4 view = glm::mat4(1.0f);
//
//    view = glm::translate(view, glm::vec3(x, y, z));
//
//    unsigned int viewLoc = glGetUniformLocation(shader->GetId(), "view");
//    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
//}

//void Hercules::Cube::Rotate()
//{
//    glm::mat4 model = glm::mat4(1.0f);
//    model = glm::rotate(model, glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
//    model = glm::rotate(model, glm::radians(40.0f), glm::vec3(0.0f, 1.0f, 0.0f));
//    shader->SetMat4("model", model);
//}
//
//void Hercules::Cube::SetTexture(const char* path, bool type)
//{
//    if (type == HC_IMG_PNG)
//    {
//        Texture texture(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, GL_LINEAR, GL_LINEAR,
//            path, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE, 0);
//
//        shader->SetTexture(0);
//    }
//    else
//    {
//        Texture texture(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, GL_LINEAR, GL_LINEAR,
//            path, GL_RGB, GL_RGB, GL_UNSIGNED_BYTE, 0);
//
//        shader->SetTexture(0);
//    }
//}
//
//void Hercules::Cube::SetColor(float r, float g, float b, float a)
//{
//    shader->SetColor(r, g, b, a);
//}
