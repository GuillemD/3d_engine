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

void ComponentCamera::DrawCameraFrustum()
{
	float3 corners[8];
	camerafrustum.GetCornerPoints(corners);

	glLineWidth(2.0f);
	//glColor3f(color.x, color.y, color.z);

	glBegin(GL_LINES);

	glVertex3f(corners[0].x, corners[0].y, corners[0].z);
	glVertex3f(corners[1].x, corners[1].y, corners[1].z);

	glVertex3f(corners[0].x, corners[0].y, corners[0].z);
	glVertex3f(corners[2].x, corners[2].y, corners[2].z);

	glVertex3f(corners[0].x, corners[0].y, corners[0].z);
	glVertex3f(corners[4].x, corners[4].y, corners[4].z);

	glVertex3f(corners[1].x, corners[1].y, corners[1].z);
	glVertex3f(corners[3].x, corners[3].y, corners[3].z);

	glVertex3f(corners[1].x, corners[1].y, corners[1].z);
	glVertex3f(corners[5].x, corners[5].y, corners[5].z);

	glVertex3f(corners[2].x, corners[2].y, corners[2].z);
	glVertex3f(corners[3].x, corners[3].y, corners[3].z);

	glVertex3f(corners[2].x, corners[2].y, corners[2].z);
	glVertex3f(corners[6].x, corners[6].y, corners[6].z);

	glVertex3f(corners[3].x, corners[3].y, corners[3].z);
	glVertex3f(corners[7].x, corners[7].y, corners[7].z);

	glVertex3f(corners[4].x, corners[4].y, corners[4].z);
	glVertex3f(corners[5].x, corners[5].y, corners[5].z);

	glVertex3f(corners[4].x, corners[4].y, corners[4].z);
	glVertex3f(corners[6].x, corners[6].y, corners[6].z);

	glVertex3f(corners[5].x, corners[5].y, corners[5].z);
	glVertex3f(corners[7].x, corners[7].y, corners[7].z);

	glVertex3f(corners[6].x, corners[6].y, corners[6].z);
	glVertex3f(corners[7].x, corners[7].y, corners[7].z);

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

float ComponentCamera::GetAspectRatio() const
{
	return camerafrustum.AspectRatio();
}

void ComponentCamera::SetNearPlaneDist(float _dist)
{
	camerafrustum.nearPlaneDistance = _dist;

}

void ComponentCamera::SetFarPlaneDist(float _dist)
{
	camerafrustum.farPlaneDistance = _dist;

}

void ComponentCamera::SetFOV(float _fov)
{
	camerafrustum.verticalFov = _fov;
}


//Preguntar al Ric
void ComponentCamera::Look(const float3 & _position)
{
	float3 dir = _position - camerafrustum.pos;

	float3x3 m = float3x3::LookAt(camerafrustum.front, dir.Normalized(), camerafrustum.up, float3::unitY);

	camerafrustum.front = m.MulDir(camerafrustum.front).Normalized();
	camerafrustum.up = m.MulDir(camerafrustum.up).Normalized();
}

float * ComponentCamera::GetOpenGLViewMatrix()
{
	float4x4 ret;
	ret = camerafrustum.ViewMatrix();
	ret.Transpose();

	return (float *) ret.v;
}

float * ComponentCamera::GetOpenGLProjectionMatrix()
{
	float4x4 ret;
	ret = camerafrustum.ProjectionMatrix();
	ret.Transpose();

	return (float *)ret.v;
}

void ComponentCamera::AttachToGo(GameObject* _go)
{
	my_go = _go;
}
