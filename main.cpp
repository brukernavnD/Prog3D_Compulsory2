#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>
#include <cmath>
#include <math.h>
#include <vector>

#include "Camera.h"
#include "House.h"
#include "NPC.h"
#include "Pickup.h"
#include "PlayerCharacter.h"
#include "Shaders.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/gtx/rotate_vector.inl"
#include "glm/gtx/string_cast.hpp"

// callback functions
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window, float InDeltaTime);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);

// Window dimensions
float resolutions[2] = { 800, 800 };

// camera (from https://learnopengl.com/Getting-started/Camera)
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

// mouse movement (from https://learnopengl.com/Getting-started/Camera)
double LastX = resolutions[0] / 2.0f;
double LastY = resolutions[1] / 2.0f;
bool IsFirstMouse = true;

//stores the current scene
int ScenePicker = 0;

//vector to store the vertices
std::vector<float> Vertices = {};

//add the floor vertices to the house vertices
House NewHouse = House(glm::vec3(0.0f, 0.0f, -10.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(2.0f, 2.0f, 2.0f), Vertices);

//create the npc
NPC NewNPC = NPC(Vertices, glm::vec3(-8.0f, 0.5f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f));

//scale variable for the pickup placement in the world
glm::vec3 PickupsScale = glm::vec3(5.5, 1, 5.5);

//vector to store the 8 pickups
std::vector<Pickup> Pickups = {
    Pickup(Vertices, NewHouse.Position),
    Pickup(Vertices, NewHouse.Position + glm::vec3(2 * PickupsScale.x, 0.5 * PickupsScale.y, 2 * PickupsScale.z)),
    Pickup(Vertices, NewHouse.Position + glm::vec3(-2 * PickupsScale.x, 0.5 * PickupsScale.y, 2 * PickupsScale.z)),
    Pickup(Vertices, NewHouse.Position + glm::vec3(1 * PickupsScale.x, 0.5 * PickupsScale.y, 0 * PickupsScale.z)),
    Pickup(Vertices, NewHouse.Position + glm::vec3(-1 * PickupsScale.x, 0.5 * PickupsScale.y, 0 * PickupsScale.z)),
    Pickup(Vertices, NewHouse.Position + glm::vec3(1 * PickupsScale.x, 0.5 * PickupsScale.y, 1 * PickupsScale.z)),
    Pickup(Vertices, NewHouse.Position + glm::vec3(-1 * PickupsScale.x, 0.5 * PickupsScale.y, -1 * PickupsScale.z)),
    Pickup(Vertices, NewHouse.Position + glm::vec3(1 * PickupsScale.x, 0.5 * PickupsScale.y, -1 * PickupsScale.z)),
    Pickup(Vertices, NewHouse.Position + glm::vec3(-1 * PickupsScale.x, 0.5 * PickupsScale.y, 1 * PickupsScale.z))
};

//the starting position of the player character
const glm::vec3 PlayerStartPos = glm::vec3(NewHouse.Position.x, 0.5, NewHouse.Position.z + NewHouse.SideWallWidth * NewHouse.Size.z / 2 - 1);

//create the player character (position right behind the door)
PlayerCharacter Player = PlayerCharacter(Vertices, PlayerStartPos, glm::vec3(0.5, 2, 0.5), glm::vec3(0, 0, 0.5));

constexpr float HouseSizeMultiplier = 3.0f;

//the first camera position for the house scene
glm::vec3 HouseSceneCameraPosition1 = glm::vec3(NewHouse.Position.x + NewHouse.Size.x * HouseSizeMultiplier * NewHouse.FrontBackWallWidth / 2.5, Player.Position.y, NewHouse.Position.z + NewHouse.Size.z * HouseSizeMultiplier * NewHouse.SideWallWidth / 3);

//the second camera position for the house scene
glm::vec3 HouseSceneCameraPosition2 = glm::vec3(NewHouse.Position.x - NewHouse.Size.x * HouseSizeMultiplier * NewHouse.FrontBackWallWidth / 2.5, Player.Position.y, NewHouse.Position.z + NewHouse.Size.z * HouseSizeMultiplier * NewHouse.SideWallWidth / 3);

//function to be called when the which scene we're on changes
void SceneChange(int NewScene)
{
    //check if the old scene was the outside scene
    if (ScenePicker == 0)
    {
        //print the enter house message
    	std::cout << "You have entered the house!" << std::endl;

        //increase the size of the house
        NewHouse.Size = glm::vec3(NewHouse.Size.x * HouseSizeMultiplier, NewHouse.Size.y * HouseSizeMultiplier, NewHouse.Size.z * HouseSizeMultiplier);

        //set the pickup positions so that they maintain their relative positions to the house
        for (Pickup& Pickup : Pickups)
        {
            //check if the distance from the house is greater than 0
            if (distance(Pickup.Position, NewHouse.Position) > 0)
            {
	            //set the pickup position to the new pickup position
				Pickup.Position = (NewHouse.Position - Pickup.Position) * HouseSizeMultiplier;
			}
		}

        //set the npc position so that it maintains its relative position to the house
        if (distance(NewNPC.Position, NewHouse.Position) > 0)
        {
	        //set the npc position to the new npc position
			NewNPC.Position = (NewHouse.Position - NewNPC.Position) * HouseSizeMultiplier;

            //set the original position to the new original position
            NewNPC.OriginalPosition = (NewHouse.Position - NewNPC.OriginalPosition) * HouseSizeMultiplier;
		}

        //set the camera position to be at the house scene camera position
        camera.Position = HouseSceneCameraPosition1;

	    //call process mouse movement with no mouse movement to update the camera vectors
	    camera.ProcessMouseMovement(0, 0);
	}
    //check if the old scene was the house scene
    else if (ScenePicker == 1)
    {
        //print the exit house message
		std::cout << "You have exited the house!" << std::endl;

        //decrease the size of the house
		NewHouse.Size = glm::vec3(NewHouse.Size.x / HouseSizeMultiplier, NewHouse.Size.y / HouseSizeMultiplier, NewHouse.Size.z / HouseSizeMultiplier);

        //set the pickup positions so that they maintain their relative positions to the house
        for (Pickup& Pickup : Pickups)
        {
            //check if the distance from the house is greater than 0
            if (distance(Pickup.Position, NewHouse.Position) > 0)
            {
	            //set the pickup position to the new pickup position
				Pickup.Position = (NewHouse.Position - Pickup.Position) / HouseSizeMultiplier + NewHouse.Position / glm::vec3(2, 2, 2);
			}
		}

        //set the npc position so that it maintains its relative position to the house
        if (distance(NewNPC.Position, NewHouse.Position) > 0)
        {
	        //set the npc position to the new npc position
			NewNPC.Position = (NewHouse.Position - NewNPC.Position) / HouseSizeMultiplier;

            //set the original position to the new original position
            NewNPC.OriginalPosition = (NewHouse.Position - NewNPC.OriginalPosition) / HouseSizeMultiplier;
		}

        //reset the position of the player character
        Player.Position = PlayerStartPos;

        //set the camera position to be at 0,0,0
        camera.Position = glm::vec3(0,0,0);

        //set the camera to face away from the door
        camera.Yaw = 180;

        //process the mouse movement to update the camera vectors
        camera.ProcessMouseMovement(0, 0);
    }

    //update the scene picker
    ScenePicker = NewScene;
}

//function to check for collision between 2 objects (using aa-bb collision detection)
bool CheckCollision(const glm::vec3 Object1Position, const glm::vec3 Object1Size, const glm::vec3 Object2Position, const glm::vec3 Object2Size)
{
	//check if the objects are colliding
	if (Object1Position.x < Object2Position.x + Object2Size.x &&
        Object1Position.x + Object1Size.x > Object2Position.x &&
        Object1Position.y < Object2Position.y + Object2Size.y &&
        Object1Position.y + Object1Size.y > Object2Position.y &&
        Object1Position.z < Object2Position.z + Object2Size.z &&
        Object1Position.z + Object1Size.z > Object2Position.z)
	{
		//return true if the objects are colliding
		return true;
	}

	//return false if the objects are not colliding
	return false;
}

//function to do all the individual collision checks for a scene
void CheckCollisions()
{
    //the hitbox size
    constexpr glm::vec3 HitboxSize = glm::vec3(0.5f, INFINITY, 0.5f);

    //the object to use as the hitbox for the player
    glm::vec3 PlayerHitboxPos = camera.Position;

    //check if we're on the inside scene
    if (ScenePicker == 1)
    {
	    PlayerHitboxPos = Player.Position;
    }

	//check if the player is colliding with any of the pick-ups
    for (Pickup& Pickup : Pickups)
    {
	    //check if the player is colliding with the pick-up
		if (Pickup.IsActive && CheckCollision(PlayerHitboxPos, HitboxSize, Pickup.Position, HitboxSize))
		{
			//set the pick-up to inactive
			Pickup.IsActive = false;
		}
    }

    //check for collision between the and the player
    if (NewHouse.CheckDoorCollision && CheckCollision(PlayerHitboxPos, HitboxSize, glm::vec3(NewHouse.Position.x, 0, NewHouse.Position.z + NewHouse.SideWallWidth * NewHouse.Size.z / 2), glm::vec3(HitboxSize.x * NewHouse.Size.x, INFINITY, HitboxSize.z * NewHouse.Size.z)))
    {
    	//change the scene
    	SceneChange(!ScenePicker);
    }
}

//update function
void Update(float DeltaTime)
{
    //check for collisions
    CheckCollisions();

	//update the npc
	NewNPC.Update(DeltaTime);
}

//render function
void Render(const unsigned int& InShaderProgram, const std::string& ModelKey, std::vector<float>& InVertices)
{
	//draw the house
	NewHouse.Render(InShaderProgram, ModelKey, InVertices);

	//draw the pick-ups
	for (Pickup& Pickup : Pickups)
	{
		Pickup.Render(InShaderProgram, ModelKey, InVertices);
	}

	//render the npc
	NewNPC.Render(InShaderProgram, ModelKey, InVertices);

    //render the player character
    Player.Render(InShaderProgram, ModelKey, InVertices);
}

//setup function
void GLFWSetup()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

//function to create a glfw window
GLFWwindow* CreateWindow()
{
    //create the window
	GLFWwindow* Window = glfwCreateWindow(resolutions[0], resolutions[1], "Compulsory 1", NULL, NULL);

    //set the window to the current context
	glfwMakeContextCurrent(Window);

    //set the on resize callback
	glfwSetFramebufferSizeCallback(Window, framebuffer_size_callback);
    glfwSetCursorPosCallback(Window, mouse_callback);
    glfwSetScrollCallback(Window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    return Window;
}

int main()
{
	// timing (from https://learnopengl.com/Getting-started/Camera)
	float deltaTime;	// time between current frame and last frame
	float lastFrame = 0.0f;

    //setup glfw
    GLFWSetup();

    //glfw window creation
    GLFWwindow* Window = CreateWindow();

    //glad: load all OpenGL function pointers
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    //create the shader program
    const unsigned int ShaderProgram = Shaders::CreateShader();

    //enable depth testing
    glEnable(GL_DEPTH_TEST);

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(float), Vertices.data(), GL_STATIC_DRAW);

    //position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), static_cast<void*>(nullptr));
    glEnableVertexAttribArray(0);

    //colour attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, true, 6 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);

    //storage variables for the uniform names
    const std::string name1 = "projection";
    const std::string name2 = "view";
    const std::string name3 = "model";

    // render loop
    while (!glfwWindowShouldClose(Window))
    {
        // per-frame time logic (from https://learnopengl.com/Getting-started/Camera)
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
		processInput(Window, deltaTime);

        //draw the background
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        //clear the colour buffer
		glClear(GL_COLOR_BUFFER_BIT);

        //clear the depth buffer
        glClear(GL_DEPTH_BUFFER_BIT);

        glUseProgram(ShaderProgram);
        glBindVertexArray(VAO);

        //(modified)from https://learnopengl.com/Getting-started/Camera
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), resolutions[0] / resolutions[1], 0.1f, 100.0f);
        glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, name1.c_str()), 1, false, &projection[0][0]);

        // camera/view transformation
        glm::mat4 View = camera.GetViewMatrix();
        glUniformMatrix4fv(glGetUniformLocation(ShaderProgram,name2.c_str()), 1, false, &View[0][0]);

    	//model matrix
        glm::mat4 model = glm::mat4(1.0f);

        //set the model matrix uniform
        glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, name3.c_str()), 1, false, &model[0][0]);

        //do the update for this frame
        Update(deltaTime);

        //do the rendering for this frame
        Render(ShaderProgram, name3, Vertices);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(Window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(ShaderProgram);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow* window, float InDeltaTime)
{
    //check if the escape key is pressed
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

    //check if we're on the outside scene
    if (ScenePicker == 0)
	{
        //process the input for the camera
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			camera.ProcessKeyboard(FORWARD, InDeltaTime);
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			camera.ProcessKeyboard(BACKWARD, InDeltaTime);
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			camera.ProcessKeyboard(LEFT, InDeltaTime);
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			camera.ProcessKeyboard(RIGHT, InDeltaTime);
		}

        //process the input for the npc path picking function
        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
        {
	        //set the npc to pick a new path
			NewNPC.SwitchPath(&NewNPC.Paths[0]);
        }
        if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
        {
            //set the npc to pick a new path
			NewNPC.SwitchPath(&NewNPC.Paths[1]);
		}

        //prevent y movement to make the camera move like a character
        camera.Position.y = Player.OriginalPosition.y;
	}
    //check if we're on the house scene
	else if (ScenePicker == 1)
	{
	    //process the input for the player
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			Player.ProcessInput(camera, FORWARD, InDeltaTime);
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			Player.ProcessInput(camera, BACKWARD, InDeltaTime);
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			Player.ProcessInput(camera, LEFT, InDeltaTime);
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			Player.ProcessInput(camera, RIGHT, InDeltaTime);
		}

        //process input for the camera position change
	    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
	    {
	        //update the camera position to the second house scene camera position
            camera.Position = HouseSceneCameraPosition1;

            //set the camera to face away from the door
            camera.Yaw = 0;
		}
        if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
        {
	        //update the camera position to the second house scene camera position
			camera.Position = HouseSceneCameraPosition2;

			//set the camera to face towards the door
			camera.Yaw = 180;
		}

        //process the mouse movement to update the camera vectors
		camera.ProcessMouseMovement(0, 0);

        //prevent y movement to make the camera move like a character
        Player.Position.y = Player.OriginalPosition.y;
	}
}

//called whenever the window is resized
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
    std::cout << " windows resized with " << width << " Height " << height << std::endl;
}

// glfw: whenever the mouse moves, this callback is called (from https://learnopengl.com/Getting-started/Camera)
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	const double Xpos = xposIn;
    const double Ypos = yposIn;

    if (IsFirstMouse)
    {
        LastX = Xpos;
        LastY = Ypos;
        IsFirstMouse = false;
    }

    const double Xoffset = Xpos - LastX;
    const double Yoffset = LastY - Ypos; // reversed since y-coordinates go from bottom to top

    LastX = Xpos;
    LastY = Ypos;

    camera.ProcessMouseMovement(Xoffset, Yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called (from https://learnopengl.com/Getting-started/Camera)
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}