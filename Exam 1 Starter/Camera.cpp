#include "Camera.h"

Camera::Camera()
{
	speed = 10;
	FoV = 0.25*PI;
	aspectRatio = 480.0f/640.0f;
	nearClippingPlane = 1.0f;
	farClippingPlane = 1000.0f;
	up = Vector3(0.0f, 1.0f, 0.0f);
	//position = Vector3(25.0f,25.0f,25.0f);
	position = Vector3(-10,0,0);
	lookAt = Vector3(0.0f, 0.0f, 0.0f);
	refDirection = Vector3(1,0,0);
	yaw = 0;
	roll = 0;
	pitch = 0;
	rightDownLastFrame = false;
	leftDownLastFrame = false;
}

Camera::~Camera()
{
	//nothing to deallocate
}

void Camera::init(Vector3 position, Vector3 direction, Vector3 _lookAt)
{
}

void Camera::setPerspective()
{
	D3DXMatrixPerspectiveFovLH(&mProj, FoV, aspectRatio, nearClippingPlane,farClippingPlane); 
}
void Camera::update(float dt, Input *input)
{
	bool yawUpdate = false;
	float deltaYaw = 0;
	float _speed = 100;


	Vector3 direction = Vector3(0,0,0);
	Matrix yawR;
	Matrix pitchR;
	Matrix rollR;
	
	Identity(&yawR);
	Identity(&pitchR);
	Identity(&rollR);
	
	//if (input->getMouseRawX() > 0 && input->getMouseLButton())
	if (!rightDownLastFrame && input->wasKeyPressed(VK_RIGHT))// isKeyDown(VK_RIGHT))
	{
		deltaYaw += _speed*dt;
		yaw += deltaYaw;
		yawUpdate = true;
		rightDownLastFrame = true;
		_RPT1(0,"yaw inc %f", deltaYaw);
		_RPT1(0, "Yaw %f \n", yaw);

	}
	if (!leftDownLastFrame && input->wasKeyPressed(VK_LEFT))//   isKeyDown(VK_LEFT))
		//if (input->getMouseRawX() < 0 && input->getMouseLButton())
	{
		yawUpdate = true;
		deltaYaw -= _speed*dt;
		yaw+= deltaYaw;
		leftDownLastFrame = true;
		_RPT1(0,"yaw dec %f ", deltaYaw);
		_RPT1(0, "Yaw %f \n", yaw);
	}
	if (!input->wasKeyPressed(VK_RIGHT))
		rightDownLastFrame = false;
	if (!input->wasKeyPressed(VK_LEFT))
		leftDownLastFrame = false;
	
	pitch = speed * input->getMouseRawY();
	input->clearKeyPress(VK_RIGHT);
	input->clearKeyPress(VK_LEFT);

	if (yaw > 90)
		yaw -= 90;
	else if (yaw < -90)
		yaw+= 90;

	RotateY(&yawR, ToRadian(yaw));
	//_RPT1(0,"yaw: %f\n", yaw);
	if(input->isKeyDown('A'))
		direction.z = 1;
	if(input->isKeyDown('D'))
		direction.z = -1;
	if(input->isKeyDown('S'))
		direction.x = -1;
	if(input->isKeyDown('W'))
		direction.x = 1;
	if(input->isKeyDown('P'))
		direction.y = 1;
	if(input->isKeyDown('O'))
		direction.y = -1;
	//update position
	//input->clearAll();
	D3DXVec3Normalize(&direction, &direction);
	direction = direction*_speed*.1*dt;
	Transform(&direction, &direction, &yawR);
	position += direction;
	if (yawUpdate)
	{
	Vector3 transformedRef = refDirection;
	Transform(&transformedRef, &transformedRef, &yawR);
	D3DXVec3Normalize(&transformedRef, &transformedRef);
    lookAt = transformedRef;
	_RPT1(0,"lookAt x %f ", lookAt.x);
	_RPT1(0,"lookAt z %f\n",lookAt.z);
	yawUpdate = false;
	}
	else
		lookAt += direction;
	D3DXMatrixLookAtLH(&mView, &position, &lookAt, &up);
}
