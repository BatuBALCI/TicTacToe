#include "Mesh.h"
Mesh::Mesh() 
{
	VAO = 0;
	VBO = 0;
	IBO = 0;
	indexCount = 0;
    vertexCount = 0;
    dimension = 0;
    type =  GL_TRIANGLES;
}

void Mesh::CreateMesh(std::vector<float> vertices, std::vector<float> indices, int type)
{
	indexCount = indices.size();
    vertexCount = vertices.size();
    this->type = type;


    //Copy all the values from vector to an float array pointer.
    verts = new float[vertices.size()];
    std::copy(vertices.begin(), vertices.end(), verts);

    //Copy all the values from vector to an unsigned int array pointer.
    inds = new unsigned int[indices.size()];
    std::copy(indices.begin(), indices.end(), inds);

    Utility::calcAvarageNormals(inds, indexCount, verts, vertexCount, 8, 5);

    // Create VAO
    // first index is the size of VAO, second index is the ID of th VAO.
    glGenVertexArrays(1, &VAO);
    // Bind Vertex array objects with the id.
    glBindVertexArray(VAO);
        // Create VBO
        // first index is the size of IBO, second index is the ID of th IBO.
        glGenBuffers(1, &IBO);
        // Bind Index buffer objects with the id.
        // First input is where this buffer will be bound and the second input is which IBO object will be bound.
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
        // Bind data to the buffer
        // First input is the buffer array that we ewant to bind, the second input is the size of the data,
        // third input is the actual data. Fourth input decides whether we draw object statically or dynamically in other words 
        // that we want to change the data of the draw or not. during process.
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(inds[0]) * indices.size(), inds, GL_STATIC_DRAW);



        // Create VBO
        // first index is the size of VBO, second index is the ID of th VBO.
        glGenBuffers(1, &VBO);
        // Bind Vertex buffer objects with the id.
        // First input is where this buffer will be bound and the second input is which VBO object will be bound.
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        // Bind data to the buffer
        // First input is the buffer array that we ewant to bind, the second input is the size of the data,
        // third input is the actual data. Fourth input decides whether we draw object statically or dynamically in other words 
        // that we want to change the data of the draw or not. during process.
        glBufferData(GL_ARRAY_BUFFER, sizeof(verts[0])* vertices.size(), verts, GL_STATIC_DRAW);


            // Create attribute pointer.
            // First input decide where this input will be pointing(0 for positions, 1 for texture coordinates, etc....), the second input is the size that the pointer will pass,
            // the third input is how much space will pointer pass for each pass, the fourth input is if you want to normalize the values or not
            // the fifth input is after reading every cycle for vertex how much space do you want to skip (For example vertices data may have hold
            // information about colour and other thing and user may want to skip this additional info to not read while reading location, in our 
            // example it is 5 because we also have the texture coordinate data in the vertex array.), the sixth input is the offset for the pointer to find where the data start.)
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(verts[0]) * 8, 0);
            // Enable vertex attribute pointer
            // Input is the sam with the first input of glVertexAttribPointer function.
            // This one enables vertex pointer for the poisiton
            glEnableVertexAttribArray(0);

            // pointer for texture coordinates
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(verts[0]) * 8, (void*)(sizeof(verts[0]) * 3));
            // This one enables vertex pointer for the texture coordnates.
            glEnableVertexAttribArray(1);

            // pointer for normals
            glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(verts[0]) * 8, (void*)(sizeof(verts[0]) * 5));
            // This one enables vertex pointer for the normals.
            glEnableVertexAttribArray(2);

        // Unbind VAO, IBO and VBO, this unbind order is important
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Mesh::RenderMesh()
{
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    // this functions draws the arrays.
    // First input is the type of the primitive, second input is specify where the vertex pointer starts, 
    // third one is the count of the vertices inside the primitive.
    //glDrawArrays(type, 0, vertexCount);

    // this functions draws the elelments.
    // First input is the type of the primitive, second input is the count of the indices, 
    // third one is the format of those indices
    glDrawElements(type, indexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::ClearMesh()
{
    if (IBO != 0)
    {
        // Delete created buffers.
        glDeleteBuffers(1, &VBO);
        IBO = 0;
    }

    if (VBO != 0)
    {
        // Delete created buffers.
        glDeleteBuffers(1, &VBO);
        VAO = 0;
    }

    if (VAO != 0)
    {
        // Delete created buffers.
        glDeleteVertexArrays(1, &VAO);
        VAO = 0;
    }

    delete[] inds;
    delete[] verts;
    indexCount = 0;
    vertexCount = 0;
    type = 0;
}

std::vector<float> Mesh::ReadFloatsFromFile(const char* fileLocation)
{
    std::ifstream fileStream(fileLocation, std::ios::in);
    std::vector<float> nums;

    if (!fileStream.is_open()) {
        printf("failed to read %s! File doesn't exist.", fileLocation);
        return nums;
    }
    
    for (std::string line; std::getline(fileStream, line); )   //read stream line by line
    {
        while (line.size()>0)
        {
            nums.push_back(std::stof(line.substr(0, line.find_first_of(" "))));
            line.erase(line.begin(), line.begin()+line.find_first_of(" ")+1);
        }
    }
    return nums;
}

Mesh::~Mesh()
{
    ClearMesh();
}
