#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("SLERP - YOUR USER NAME GOES HERE"); // Window Name

	//Setting the color to black
	m_v4ClearColor = vector4(0.0f);
}

void AppClass::InitVariables(void)
{
	//Setting the position in which the camera is looking and its interest point
	m_pCameraMngr->SetPositionTargetAndView(vector3(12.12f, 28.52f, 11.34f), ZERO_V3, REAXISY);

	//Setting the color to black
	m_v4ClearColor = vector4(0.0f);

	//Loading the models
	m_pMeshMngr->LoadModel("Planets\\00_Sun.obj", "Sun");
	m_pMeshMngr->LoadModel("Planets\\03_Earth.obj", "Earth");
	m_pMeshMngr->LoadModel("Planets\\03A_Moon.obj", "Moon");

	//Setting the days duration
	m_fDay = 1.0f;
}

void AppClass::Update(void)
{
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();

	//First person camera movement
	if (m_bFPC == true)
		CameraRotation();

	//Getting the time between calls
	double fCallTime = m_pSystem->LapClock();
	//Counting the cumulative time
	static double fRunTime = 0.0f;
	fRunTime += fCallTime;

	//Earth Orbit
	double fEarthHalfOrbTime = 182.5f * m_fDay; //Earths orbit around the sun lasts 365 days / half the time for 2 stops
	float fEarthHalfRevTime = 0.5f * m_fDay; // Move for Half a day
	float fMoonHalfOrbTime = 14.0f * m_fDay; //Moon's orbit is 28 earth days, so half the time for half a route

	//Setting the matrices

	glm::quat first = glm::quat(vector3(0.0f, 0.0f, 0.0f));
	glm::quat second = glm::quat(vector3(0.0f, PI, 0.0f));

	float earthOrbPercentage = fmod(fRunTime, fEarthHalfOrbTime * 2) / fEarthHalfOrbTime;

	glm::quat rotation = glm::mix(first, second, earthOrbPercentage);
	matrix4 earthPos = IDENTITY_M4 * glm::mat4_cast(rotation);

	earthPos = glm::translate(earthPos, vector3(11.0f, 0.0f, 0.0f));
	earthPos = glm::scale(earthPos, vector3(0.524f, 0.524f, 0.524f));

	matrix4 moonPos = matrix4(earthPos);
	
	glm::quat moonOrbFirst = glm::quat(vector3(0.0f, 0.0f, 0.0f));
	glm::quat moonOrbSecond = glm::quat(vector3(0.0f, PI, 0.0f));

	float moonOrbPercentage = fmod(fRunTime, fMoonHalfOrbTime * 2) / fMoonHalfOrbTime;

	glm::quat mOrbit = glm::mix(moonOrbFirst, moonOrbSecond, moonOrbPercentage);
	moonPos *= glm::mat4_cast(mOrbit);

	moonOrbPercentage = fmod(fRunTime, fEarthHalfOrbTime * 2) / fEarthHalfOrbTime;

	mOrbit = glm::mix(moonOrbSecond, moonOrbFirst, moonOrbPercentage);
	moonPos *= glm::mat4_cast(mOrbit);



	moonPos = glm::translate(moonPos, vector3(2.0f, 0.0f, 0.0f));

	glm::quat mRevFirst = glm::quat(vector3(0.0f, 0.0f, 0.0f));
	glm::quat mRevSecond = glm::quat(vector3(0.0f, PI, 0.0f));
	float moonRevPercentage = fmod(fRunTime / 365, fMoonHalfOrbTime * 2) / fMoonHalfOrbTime;
	glm::quat mRevolution = glm::mix(mRevFirst, mRevSecond, moonRevPercentage);

	moonPos *= glm::mat4_cast(mRevolution);

	moonPos = glm::scale(moonPos, vector3(0.27f, 0.27f, 0.27f));

	glm::quat eRevFirst = glm::quat(vector3(0.0f, 0.0f, 0.0f));
	glm::quat eRevSecond = glm::quat(vector3(0.0f, PI, 0.0f));
	float earthRevPercentage = fmod(fRunTime, fEarthHalfRevTime * 2) / fEarthHalfRevTime;
	glm::quat eRevolution = glm::mix(eRevFirst, eRevSecond, earthRevPercentage);

	earthPos *= glm::mat4_cast(eRevolution);





	m_pMeshMngr->SetModelMatrix(glm::scale(IDENTITY_M4, vector3(5.936f, 5.936f, 5.936f)), "Sun");
	m_pMeshMngr->SetModelMatrix(earthPos, "Earth");
	m_pMeshMngr->SetModelMatrix(moonPos, "Moon");

	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	int nEarthOrbits = fRunTime / (fEarthHalfOrbTime * 2);
	int nEarthRevolutions = fRunTime / (fEarthHalfRevTime * 2);
	int nMoonOrbits = fRunTime / (fMoonHalfOrbTime * 2);

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();

	//Print info on the screen
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	
	m_pMeshMngr->Print("Time:");
	m_pMeshMngr->PrintLine(std::to_string(fRunTime));

	m_pMeshMngr->Print("Day:");
	m_pMeshMngr->PrintLine(std::to_string(m_fDay));

	m_pMeshMngr->Print("E_Orbits:");
	m_pMeshMngr->PrintLine(std::to_string(nEarthOrbits));

	m_pMeshMngr->Print("E_Revolutions:");
	m_pMeshMngr->PrintLine(std::to_string(nEarthRevolutions));

	m_pMeshMngr->Print("M_Orbits:");
	m_pMeshMngr->PrintLine(std::to_string(nMoonOrbits));

	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();

	//Render the grid based on the camera's mode:
	switch (m_pCameraMngr->GetCameraMode())
	{
	default:
		break;
	case CAMERAMODE::CAMROTHOX:
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::YZ, RERED * 0.75f); //renders the YZ grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOY:
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XZ, REGREEN * 0.75f); //renders the XZ grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOZ:
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XY, REBLUE * 0.75f); //renders the XY grid with a 100% scale
		break;
	}
	
	m_pMeshMngr->Render(); //renders the render list

	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	super::Release(); //release the memory of the inherited fields
}