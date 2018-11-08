#include "ComponentCamera.h"



ComponentCamera::ComponentCamera()
{
	MyType = CAMERA;
	camerafrustum.type = math::FrustumType::PerspectiveFrustum;

	camerafrustum.pos = { -10.0f,5.0f,-9.0f };
	camerafrustum.front = { 0.0f,0.0f,-1.0f };
	camerafrustum.up = { 0.0f,1.0f,0.0f };

	camerafrustum.nearPlaneDistance = 0.1f;
	camerafrustum.farPlaneDistance = 1000.0f;

	camerafrustum.verticalFov = DEGTORAD * 90.0f;
	SetAspectRatio(16.0f / 9.0f);

	cameraboundingbox = AABB({ 0.0f,0.0f,0.0f }, { 0.0f,0.0f,0.0f });

}


ComponentCamera::~ComponentCamera()
{
}

void ComponentCamera::SetAspectRatio(float _aspectratio)
{
	if (_aspectratio <= 0) {
		CONSOLELOG("Can't set aspect ratio to 0 or negative value");
	}
	camerafrustum.horizontalFov = 2.f * atanf(tanf(camerafrustum.verticalFov*0.5f)*_aspectratio);
}

void ComponentCamera::DrawCameraBoundingBox()
{
	glLineWidth(1.5f);
	glColor3f(1, 0.5f, 1);

	glBegin(GL_LINES);

	{
		glVertex3f(cameraboundingbox.CornerPoint(0).x, cameraboundingbox.CornerPoint(0).y, cameraboundingbox.CornerPoint(0).z);
		glVertex3f(cameraboundingbox.CornerPoint(1).x, cameraboundingbox.CornerPoint(1).y, cameraboundingbox.CornerPoint(1).z);

		glVertex3f(cameraboundingbox.CornerPoint(0).x, cameraboundingbox.CornerPoint(0).y, cameraboundingbox.CornerPoint(0).z);
		glVertex3f(cameraboundingbox.CornerPoint(2).x, cameraboundingbox.CornerPoint(2).y, cameraboundingbox.CornerPoint(2).z);

		glVertex3f(cameraboundingbox.CornerPoint(0).x, cameraboundingbox.CornerPoint(0).y, cameraboundingbox.CornerPoint(0).z);
		glVertex3f(cameraboundingbox.CornerPoint(4).x, cameraboundingbox.CornerPoint(4).y, cameraboundingbox.CornerPoint(4).z);

		glVertex3f(cameraboundingbox.CornerPoint(3).x, cameraboundingbox.CornerPoint(3).y, cameraboundingbox.CornerPoint(3).z);
		glVertex3f(cameraboundingbox.CornerPoint(1).x, cameraboundingbox.CornerPoint(1).y, cameraboundingbox.CornerPoint(1).z);

		glVertex3f(cameraboundingbox.CornerPoint(3).x, cameraboundingbox.CornerPoint(3).y, cameraboundingbox.CornerPoint(3).z);
		glVertex3f(cameraboundingbox.CornerPoint(2).x, cameraboundingbox.CornerPoint(2).y, cameraboundingbox.CornerPoint(2).z);

		glVertex3f(cameraboundingbox.CornerPoint(3).x, cameraboundingbox.CornerPoint(3).y, cameraboundingbox.CornerPoint(3).z);
		glVertex3f(cameraboundingbox.CornerPoint(7).x, cameraboundingbox.CornerPoint(7).y, cameraboundingbox.CornerPoint(7).z);

		glVertex3f(cameraboundingbox.CornerPoint(6).x, cameraboundingbox.CornerPoint(6).y, cameraboundingbox.CornerPoint(6).z);
		glVertex3f(cameraboundingbox.CornerPoint(2).x, cameraboundingbox.CornerPoint(2).y, cameraboundingbox.CornerPoint(2).z);

		glVertex3f(cameraboundingbox.CornerPoint(6).x, cameraboundingbox.CornerPoint(6).y, cameraboundingbox.CornerPoint(6).z);
		glVertex3f(cameraboundingbox.CornerPoint(4).x, cameraboundingbox.CornerPoint(4).y, cameraboundingbox.CornerPoint(4).z);

		glVertex3f(cameraboundingbox.CornerPoint(6).x, cameraboundingbox.CornerPoint(6).y, cameraboundingbox.CornerPoint(6).z);
		glVertex3f(cameraboundingbox.CornerPoint(7).x, cameraboundingbox.CornerPoint(7).y, cameraboundingbox.CornerPoint(7).z);

		glVertex3f(cameraboundingbox.CornerPoint(5).x, cameraboundingbox.CornerPoint(5).y, cameraboundingbox.CornerPoint(5).z);
		glVertex3f(cameraboundingbox.CornerPoint(1).x, cameraboundingbox.CornerPoint(1).y, cameraboundingbox.CornerPoint(1).z);

		glVertex3f(cameraboundingbox.CornerPoint(5).x, cameraboundingbox.CornerPoint(5).y, cameraboundingbox.CornerPoint(5).z);
		glVertex3f(cameraboundingbox.CornerPoint(4).x, cameraboundingbox.CornerPoint(4).y, cameraboundingbox.CornerPoint(4).z);

		glVertex3f(cameraboundingbox.CornerPoint(5).x, cameraboundingbox.CornerPoint(5).y, cameraboundingbox.CornerPoint(5).z);
		glVertex3f(cameraboundingbox.CornerPoint(7).x, cameraboundingbox.CornerPoint(7).y, cameraboundingbox.CornerPoint(7).z);
	}

	glEnd();

	glColor3f(1, 1, 1);
	glLineWidth(1.0f);

}

float ComponentCamera::GetNearPlaneDist() const
{
	return camerafrustum.nearPlaneDistance;
}

float ComponentCamera::GetFarPlaneDist() const
{
	return camerafrustum.farPlaneDistance;
}

float ComponentCamera::GetFOV() const
{
	return camerafrustum.verticalFov * RADTODEG;
}
