// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the SIXDOF_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// SIXDOF_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.

#ifdef SIXDOF_EXPORTS
#define SIXDOF_API __declspec(dllexport)
#else
#define SIXDOF_API __declspec(dllimport)
#endif
#include "Util.h"


	typedef SIXDOF_API double Motors[4];
	typedef SIXDOF_API Vector3 V3;
	typedef SIXDOF_API Control RcControl;

	SIXDOF_API int SixDofInit(int numberOfQuad, double HomeLat, double HomeLong, double HomeAlt, double initialYaw, double minDistance, double maxDistance);
	SIXDOF_API void SixDofLoggerOn(bool on);
	SIXDOF_API void SixDofSetMotorsError(int key, double percent);
	SIXDOF_API void SixDofInputData(int key, Motors m);
	SIXDOF_API void SixDofInputRcData(int key, RcControl rc);
	SIXDOF_API void SixDofSetBaseRPM(int key, int base);
	SIXDOF_API void SixDofStep(double milliseconds);//equivalent to fixed time
	SIXDOF_API V3 SixDofOutputData(int key, Angle& angle, V3& velocity);
	SIXDOF_API double SixDofGetVersion();

	//-----------many-----------------------------------------------
	SIXDOF_API void SixDofSetQuadsNumber(int numberOfQuad);
	SIXDOF_API void SixDofSetInitialPos(int key, double HomeLat, double HomeLong, double HomeAlt, double initialYaw);

