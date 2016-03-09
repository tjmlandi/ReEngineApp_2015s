#include "MyPrimitive.h"
MyPrimitive::MyPrimitive() { }
MyPrimitive::MyPrimitive(const MyPrimitive& other) { }
MyPrimitive& MyPrimitive::operator=(const MyPrimitive& other) { return *this; }
MyPrimitive::~MyPrimitive(void) { super::Release(); }
void MyPrimitive::CompileObject(vector3 a_v3Color)
{
	m_uVertexCount = static_cast<int> (m_lVertexPos.size());
	for (uint i = 0; i < m_uVertexCount; i++)
	{
		AddVertexColor(a_v3Color);
	}
	
	CompleteTriangleInfo(true);
	CompileOpenGL3X();

}
//C--D
//|\ |
//| \|
//A--B
//This will make the triang A->B->C and then the triang C->B->D
void MyPrimitive::AddQuad(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft, vector3 a_vTopRight)
{
	AddVertexPosition(a_vBottomLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopLeft);

	AddVertexPosition(a_vTopLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopRight);
}
void MyPrimitive::GeneratePlane(float a_fSize, vector3 a_v3Color)
{
	if (a_fSize < 0.01f)
		a_fSize = 0.01f;

	Release();
	Init();

	float fValue = 0.5f * a_fSize;

	vector3 pointA(-fValue, -fValue, 0.0f); //0
	vector3 pointB(fValue, -fValue, 0.0f); //1
	vector3 pointC(fValue, fValue, 0.0f); //2
	vector3 pointD(-fValue, fValue, 0.0f); //3

	vector3 pointE(fValue, -fValue, -0.001f); //1
	vector3 pointF(-fValue, -fValue, -0.001f); //0
	vector3 pointG(fValue, fValue, -0.001f); //2
	vector3 pointH(-fValue, fValue, -0.001f); //3

											  //F
	AddQuad(pointA, pointB, pointD, pointC);
	//Double sided
	AddQuad(pointE, pointF, pointG, pointH);

	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateCube(float a_fSize, vector3 a_v3Color)
{
	if (a_fSize < 0.01f)
		a_fSize = 0.01f;

	Release();
	Init();

	float fValue = 0.5f * a_fSize;
	//3--2
	//|  |
	//0--1
	vector3 point0(-fValue, -fValue, fValue); //0
	vector3 point1(fValue, -fValue, fValue); //1
	vector3 point2(fValue, fValue, fValue); //2
	vector3 point3(-fValue, fValue, fValue); //3

	vector3 point4(-fValue, -fValue, -fValue); //4
	vector3 point5(fValue, -fValue, -fValue); //5
	vector3 point6(fValue, fValue, -fValue); //6
	vector3 point7(-fValue, fValue, -fValue); //7

											  //F
	AddQuad(point0, point1, point3, point2);

	//B
	AddQuad(point5, point4, point6, point7);

	//L
	AddQuad(point4, point0, point7, point3);

	//R
	AddQuad(point1, point5, point2, point6);

	//U
	AddQuad(point3, point2, point7, point6);

	//D
	AddQuad(point4, point5, point0, point1);

	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateCone(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	//Your code starts here
	float fValue = 0.5f;
	//3--2
	//|  |
	//0--1
	/*
	vector3 point0(-fValue, -fValue, fValue); //0
	vector3 point1(fValue, -fValue, fValue); //1
	vector3 point2(fValue, fValue, fValue); //2
	vector3 point3(-fValue, fValue, fValue); //3

	AddQuad(point0, point1, point3, point2);
	*/

	for (int i = 0; i < a_nSubdivisions; ++i)
	{
		vector3 point0(0, a_fHeight / 2, 0);

		vector3 point4(a_fRadius*cos((i * 2 * PI) / a_nSubdivisions), -a_fHeight / 2, a_fRadius*sin((i * 2 * PI) / a_nSubdivisions));
		vector3 point5(a_fRadius*cos(((i + 1) * 2 * PI) / a_nSubdivisions), -a_fHeight / 2, a_fRadius*sin(((i + 1) * 2 * PI) / a_nSubdivisions));
		vector3 point6(0, -a_fHeight / 2, 0);
		vector3 point7(a_fRadius*cos((i * 2 * PI) / a_nSubdivisions), -a_fHeight / 2, a_fRadius*sin((i * 2 * PI) / a_nSubdivisions));

		AddQuad(point7, point6, point5, point4);

		AddQuad(point4, point5, point0, point4);
	}


	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateCylinder(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	//Your code starts here
	float fValue = 0.5f;
	//3--2
	//|  |
	//0--1
	/*
	vector3 point0(-fValue, -fValue, fValue); //0
	vector3 point1(fValue, -fValue, fValue); //1
	vector3 point2(fValue, fValue, fValue); //2
	vector3 point3(-fValue, fValue, fValue); //3

	AddQuad(point0, point1, point3, point2);
	*/

	for (int i = 0; i < a_nSubdivisions; ++i)
	{
		vector3 point0(a_fRadius*cos((i * 2 * PI) / a_nSubdivisions), a_fHeight / 2, a_fRadius*sin((i * 2 * PI) / a_nSubdivisions));
		vector3 point1(a_fRadius*cos(((i + 1) * 2 * PI) / a_nSubdivisions), a_fHeight / 2, a_fRadius*sin(((i + 1) * 2 * PI) / a_nSubdivisions));
		vector3 point2(0, a_fHeight / 2, 0);
		vector3 point3(a_fRadius*cos((i * 2 * PI) / a_nSubdivisions), a_fHeight / 2, a_fRadius*sin((i * 2 * PI) / a_nSubdivisions));

		AddQuad(point3, point2, point1, point0);

		vector3 point4(a_fRadius*cos((i * 2 * PI) / a_nSubdivisions), -a_fHeight / 2, a_fRadius*sin((i * 2 * PI) / a_nSubdivisions));
		vector3 point5(a_fRadius*cos(((i + 1) * 2 * PI) / a_nSubdivisions), -a_fHeight / 2, a_fRadius*sin(((i + 1) * 2 * PI) / a_nSubdivisions));
		vector3 point6(0, -a_fHeight / 2, 0);
		vector3 point7(a_fRadius*cos((i * 2 * PI) / a_nSubdivisions), -a_fHeight / 2, a_fRadius*sin((i * 2 * PI) / a_nSubdivisions));

		AddQuad(point7, point6, point5, point4);

		AddQuad(point5, point4, point1, point0);
	}


	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateTube(float a_fOuterRadius, float a_fInnerRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	//Your code starts here
	float fValue = 0.5f;
	//3--2
	//|  |
	//0--1
	/*
	vector3 point0(-fValue, -fValue, fValue); //0
	vector3 point1(fValue, -fValue, fValue); //1
	vector3 point2(fValue, fValue, fValue); //2
	vector3 point3(-fValue, fValue, fValue); //3

	AddQuad(point0, point1, point3, point2);
	*/

	for (int i = 0; i < a_nSubdivisions; ++i)
	{
		vector3 point0(a_fOuterRadius*cos((i * 2 * PI) / a_nSubdivisions), a_fHeight / 2, a_fOuterRadius*sin((i * 2 * PI) / a_nSubdivisions));
		vector3 point1(a_fOuterRadius*cos(((i + 1) * 2 * PI) / a_nSubdivisions), a_fHeight / 2, a_fOuterRadius*sin(((i + 1) * 2 * PI) / a_nSubdivisions));
		vector3 point2(a_fInnerRadius*cos((i * 2 * PI) / a_nSubdivisions), a_fHeight / 2, a_fInnerRadius*sin((i * 2 * PI) / a_nSubdivisions));
		vector3 point3(a_fInnerRadius*cos(((i + 1) * 2 * PI) / a_nSubdivisions), a_fHeight / 2, a_fInnerRadius*sin(((i + 1) * 2 * PI) / a_nSubdivisions));

		AddQuad(point3, point1, point2, point0);

		vector3 point4(a_fOuterRadius*cos((i * 2 * PI) / a_nSubdivisions), -a_fHeight / 2, a_fOuterRadius*sin((i * 2 * PI) / a_nSubdivisions));
		vector3 point5(a_fOuterRadius*cos(((i + 1) * 2 * PI) / a_nSubdivisions), -a_fHeight / 2, a_fOuterRadius*sin(((i + 1) * 2 * PI) / a_nSubdivisions));
		vector3 point6(a_fInnerRadius*cos((i * 2 * PI) / a_nSubdivisions), -a_fHeight / 2, a_fInnerRadius*sin((i * 2 * PI) / a_nSubdivisions));
		vector3 point7(a_fInnerRadius*cos(((i + 1) * 2 * PI) / a_nSubdivisions), -a_fHeight / 2, a_fInnerRadius*sin(((i + 1) * 2 * PI) / a_nSubdivisions));

		AddQuad(point4, point5, point6, point7);

		AddQuad(point5, point4, point1, point0);
		AddQuad(point6, point7, point2, point3);
	}


	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateTorus(float a_fOuterRadius, float a_fInnerRadius, int a_nSubdivisionsA, int a_nSubdivisionsB, vector3 a_v3Color)
{
	if (a_fOuterRadius <= a_fInnerRadius + 0.1f)
		return;

	if (a_nSubdivisionsA < 3)
		a_nSubdivisionsA = 3;
	if (a_nSubdivisionsA > 25)
		a_nSubdivisionsA = 25;

	if (a_nSubdivisionsB < 3)
		a_nSubdivisionsB = 3;
	if (a_nSubdivisionsB > 25)
		a_nSubdivisionsB = 25;

	Release();
	Init();

	//Your code starts here
	float fValue = 0.5f;
	//3--2
	//|  |
	//0--1
	vector3 point0(-fValue, -fValue, fValue); //0
	vector3 point1(fValue, -fValue, fValue); //1
	vector3 point2(fValue, fValue, fValue); //2
	vector3 point3(-fValue, fValue, fValue); //3

	AddQuad(point0, point1, point3, point2);

	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateSphere(float a_fRadius, int a_nSubdivisions, vector3 a_v3Color)
{
	//Sets minimum and maximum of subdivisions
	if (a_nSubdivisions < 1)
	{
		GenerateCube(a_fRadius * 2, a_v3Color);
		return;
	}
	if (a_nSubdivisions > 20)
		a_nSubdivisions = 20;

	Release();
	Init();

	//Your code starts here
	/*
	float fValue = 0.5f;
	//3--2
	//|  |
	//0--1
	vector3 point0(-fValue, -fValue, fValue); //0
	vector3 point1(fValue, -fValue, fValue); //1
	vector3 point2(fValue, fValue, fValue); //2
	vector3 point3(-fValue, fValue, fValue); //3

	AddQuad(point0, point1, point3, point2);
	*/

	for (int i = 0; i < a_nSubdivisions; ++i)
	{
		for (int j = 0; j < a_nSubdivisions; ++j)
		{
			vector3 point0(sin((j*PI) / a_nSubdivisions)*a_fRadius*cos((i * 2 * PI) / a_nSubdivisions), a_fRadius * cos((j*PI)/ a_nSubdivisions), sin((j*PI) / a_nSubdivisions)*a_fRadius*sin((i * 2 * PI) / a_nSubdivisions));
			vector3 point1(sin((j*PI) / a_nSubdivisions)*a_fRadius*cos(((i + 1)* 2 * PI) / a_nSubdivisions), a_fRadius * cos((j*PI) / a_nSubdivisions), sin((j*PI) / a_nSubdivisions)*a_fRadius*sin(((i + 1) * 2 * PI) / a_nSubdivisions));
			vector3 point2(sin(((j + 1)*PI) / a_nSubdivisions)*a_fRadius*cos((i * 2 * PI) / a_nSubdivisions), a_fRadius * cos(((j + 1)*PI) / a_nSubdivisions), sin(((j + 1)*PI) / a_nSubdivisions)*a_fRadius*sin((i * 2 * PI) / a_nSubdivisions));
			vector3 point3(sin(((j + 1)*PI) / a_nSubdivisions)*a_fRadius*cos(((i + 1) * 2 * PI) / a_nSubdivisions), a_fRadius * cos(((j + 1)*PI) / a_nSubdivisions), sin(((j + 1)*PI) / a_nSubdivisions)*a_fRadius*sin(((i + 1) * 2 * PI) / a_nSubdivisions));

			AddQuad(point0, point1, point2, point3);
		}
	}

	//Your code ends here
	CompileObject(a_v3Color);
}