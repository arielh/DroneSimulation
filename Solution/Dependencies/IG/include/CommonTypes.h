#pragma once
#define CCD_SENSOR_MASK		1
#define GRAY_SENSOR_MASK	2
#define IR_SENSOR_MASK		4
enum CAMERA_SENSOR
{
	RGB = 0,
	IR = 1,
	GRAY = 2
};
typedef struct
{
	double left;
	double right;
	double bottom;
	double top;
}Ortho2D_params;
typedef enum
{
	Proj_3D = 0,
	Proj_Ortho_2D = 1,
	Proj_Hud_2D = 2
}Projection;
typedef struct{
	CAMERA_SENSOR sensor;
	double fovX;  //degree
	double fovY;	//degree
	double nearPlane;	//meters
	double farPlane;	//meters
	int windowOriginX; //pixels
	int windowOriginY; //pixels
	int width;	//pixels
	int height;	//pixels
	bool OffScreen;
	bool borders;
	int multisample;
	Projection perspective;
	Ortho2D_params proj;
	bool readBack;
}CameraProps;