#ifndef _CAMERA_H                // Prevent multiple definitions if this 
#define _CAMERA_H 

#include "constants.h"
#include "C:\Users\wpb\Documents\Comp 446 Code\PartII\Common\d3dUtil.h"
#include "C:\Users\wpb\Documents\Comp 446 Code\PartII\Common\d3dApp.h"
#include <d3dx9math.h>
#include "input.h"

class Camera
{
public:
	Camera();
	~Camera();
	void init(Vector3 position, Vector3 direction, Vector3 _lookAt);
	Matrix getViewMatrix() {return mView;}
	Matrix getProjectionMatrix() {return mProj;}
	void update(float dt, Input *input);
	void setPosition(Vector3 pos) {position = pos;}
	Vector3 getPosition() {return position;}
	void setDirection(Vector3 dir) {direction = dir;}
	Vector3 getDirection() {return direction;}
	float getSpeed () {return speed;}
	void setSpeed(float s) {speed = s;}
	float getFoV() {return FoV;}
	void setFoV(float fov){FoV = fov;}
	void setPerspective();
private:
	Matrix mView;
	Matrix mProj;
	Vector3 position;
	Vector3 direction;
	float speed;
	float aspectRatio;
	float FoV;
	float nearClippingPlane;
	float farClippingPlane;
	Vector3 lookAt;
	Vector3 up;
	Vector3 right;
	Vector3 refDirection; //default to looking down the xz plane
	float yaw;
	float pitch;
	float roll;
	bool leftDownLastFrame;
	bool rightDownLastFrame;
};
#endif