// PublicMatrix.h: interface for the PublicMatrix class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include <osg/Matrix>
#include <osg/Vec3d>
//#include "ViperExport.h"
#include <osgSim/DOFTransform>

#ifdef PUBLIC_MATRIX_EXPORTS
#define PUBLIC_MATRIX_API __declspec(dllexport)
#else
#define PUBLIC_MATRIX_API __declspec(dllimport)
#endif


/**	this class was written in order to implement value() function */
class  PUBLIC_MATRIX_API PublicMatrix : public osg::Matrix
{
public:
	PublicMatrix();

	PublicMatrix(const osg::Matrixd& mat);

	/**
		@return matrix variable at (x,y)
	*/
	inline value_type value(int x, int y) const	{ return _mat[x][y]; }

	/**
		if the matrix is a rotation matrix, this will return HPR angles in radians
		@return HPR angles in radians 
	*/
	osg::Vec3d calcHPR () const;

	/**
		if the matrix is a rotation matrix, this will return HPR angles in degrees
		@return HPR angles in degrees 
	*/
	osg::Vec3d calcHPRDeg () const;

/*
	/ * fast calculation of hpr rotation matrix * /
	inline void calcHPR (value_type angle_x, value_type angle_y, value_type angle_z)
	{
		// TODO :: This should be implemented
	}*/



	/** Rotates camera by -90 degrees
		@param imat camera matrix to rotate
		@return imat camera rotated matrix */ 
	static osg::Matrixd RotateWorldToCamera(const osg::Matrixd& imat);

	/** Rotates camera by 90 degrees
		@param imat camera matrix to rotate
		@return imat camera rotated matrix */
	static osg::Matrixd RotateCameraToWorld(const osg::Matrixd& imat);

	/** Converts hpr (RADIANS) to object matrix
		@param hpr vector (RADIANS) to convert
		@return mat object matrix */
	static osg::Matrixd ObjectHPRtoMAT(const osg::Vec3d& hpr);

	/** Converts hpr (DEGREES) to object matrix
		@param hpr vector (DEGREES) to convert
		@return mat object matrix */
	static osg::Matrixd ObjectHPRtoMAT_Deg(const osg::Vec3d& hpr);

	/** Converts hpr (RADIANS) to object matrix according 
	* to a certain multiply order.
	* @param multOrder - multiply order
	* @param hpr - vector (RADIANS) to convert
	* @return mat - object matrix 
	*/
	static osg::Matrixd ObjectToMAT(osgSim::DOFTransform::MultOrder multOrder, const osg::Vec3d& hpr);

	/** Converts hpr (DEGREES) to object matrix according 
	* to a certain multiply order.o
	* @param multOrder - multiply order
	* @param hpr - vector (DEGREES) to convert
	* @return mat - object matrix 
	*/
	static osg::Matrixd ObjectToMAT_Deg(osgSim::DOFTransform::MultOrder multOrder, const osg::Vec3d& hpr);

	/** Converts object matrix to hpr (RADIANS)
		@param mat object matrix to convert
		@return hpr vector (RADIANS) */
	static osg::Vec3d ObjectMATtoHPR(const osg::Matrixd& mat);

	/** Converts object matrix to hpr (DEGREES)
		@param mat object matrix to convert
		@return hpr vector (DEGREES) */
	static osg::Vec3d ObjectMATtoHPR_Deg(const osg::Matrixd& mat);

	/** Converts camera matrix to hpr (RADIANS)
		@param imat camera matrix to convert
		@return hpr vector (RADIANS) */
	static osg::Vec3d CameraMATtoHPR(const osg::Matrixd& imat);

	/** Converts camera matrix to hpr (DEGREES)
	    @param imat camera matrix to convert
		@return hpr vector (DEGREES) */
	static osg::Vec3d CameraMATtoHPR_Deg(const osg::Matrixd& imat);

	/** Calculates direction vector from hpr (RADIANS)
		@param hpr (RADIANS)
		@return direction vector */
	static osg::Vec3d CalculateHPRtoDirection(const osg::Vec3d& hpr);

	/** Calculates direction vector from hpr (DEGREES)
		@param hpr (DEGREES)
		@return direction vector */
	static osg::Vec3d CalculateHPRtoDirection_Deg(const osg::Vec3d& hpr);

	/** Calculates direction vector to hp (RADIANS)
		@param direction vector
		@return hpr (RADIANS) */
	static osg::Vec2d CalculateDirectionToHP(const osg::Vec3d& direction);

	/** Calculates direction vector to hp (DEGREES)
		@param direction vector
		@return hpr (DEGREES) */
	static osg::Vec2d CalculateDirectionToHP_Deg(const osg::Vec3d& direction);

	/** Calculates angle (RADIANS) between two directions
		@param directionSource source direction
		@param directionDestination destination direction
		@return angle (RADIANS) */
	static double CalculateAngleBetweenDirections(const osg::Vec3d& directionSource,
												  const osg::Vec3d& directionDestination);

	/** Calculates angle (DEGREES) between two directions
		@param directionSource source direction
		@param directionDestination destination direction
		@return angle (DEGREES) */
	static double CalculateAngleBetweenDirections_Deg(const osg::Vec3d& directionSource,
													  const osg::Vec3d& directionDestination);

	/** Calculates line X height intersection point
		@param xyz line xyz
		@param hpr (RADIANS) line hpr
		@param height height
		@output xyzOut intersection point
		@return is intersection occured */
	static bool CalculateLineHeightIntersection(const osg::Vec3d& xyz,
												const osg::Vec3d& hpr,
												double height,
												osg::Vec3d& xyzOut);

	/** Calculates line X height intersection point
		@param xyz line xyz
		@param hpr (DEGREES) line hpr
		@param height height
		@output xyzOut intersection point
		@return is intersection occured */
	static bool CalculateLineHeightIntersection_Deg(const osg::Vec3d& xyz,
													const osg::Vec3d& hpr,
													double height,
													osg::Vec3d& xyzOut);

	/** Moves in axis by xyzOffset
		@param xyzSource source xyz
		@param hprAxis axis hpr (RADIANS)
		@param xyzOffset offset xyz
		@return xyz */
	static osg::Vec3d AxisMove(const osg::Vec3d& xyzSource,
											 const osg::Vec3d& hprAxis,
											 const osg::Vec3d& xyzOffset);

	/** Moves in axis by xyzOffset
		@param xyzSource source xyz
		@param hprAxis axis hpr (DEGREES)
		@param xyzOffset offset xyz
		@return xyz */
	static osg::Vec3d AxisMove_Deg(const osg::Vec3d& xyzSource,
												 const osg::Vec3d& hprAxis,
												 const osg::Vec3d& xyzOffset);

	/** Rotates in self axis by hprOffset
		@param hprSource source hpr (RADIANS)
		@param hprOffset offset hpr (RADIANS)
		@return hpr (RADIANS) */
	static osg::Vec3d SelfAxisRotate(const osg::Vec3d& hprSource, const osg::Vec3d& hprOffset);

	/** Rotates in self axis by hprOffset
		@param hprSource source hpr (DEGREES)
		@param hprOffset offset hpr (DEGREES)
		@return hpr (DEGREES) */
	static osg::Vec3d SelfAxisRotate_Deg(const osg::Vec3d& hprSource, const osg::Vec3d& hprOffset);

	/** Rotates around point by hprOffset
		@param xyzSource source xyz
		@param hprSource source hpr (RADIANS)
		@param xyzPoint point xyz
		@param hprOffset offset hpr (RADIANS)
		@output xyzOut xyz
		@return hpr (RADIANS) */
	static osg::Vec3d RotateAroundPoint(const osg::Vec3d& xyzSource,
													  const osg::Vec3d& hprSource,
													  const osg::Vec3d& xyzPoint,
													  const osg::Vec3d& hprOffset,
													  osg::Vec3d& xyzOut);

	/** Rotates around point by hprOffset
		@param xyzSource source xyz
		@param hprSource source hpr (DEGREES)
		@param xyzPoint point xyz
		@param hprOffset offset hpr (DEGREES)
		@output xyzOut xyz
		@return hpr (DEGREES) */
	static osg::Vec3d RotateAroundPoint_Deg(const osg::Vec3d& xyzSource,
														  const osg::Vec3d& hprSource,
														  const osg::Vec3d& xyzPoint,
														  const osg::Vec3d& hprOffset,
														  osg::Vec3d& xyzOut);

	/** Calculates absolute hpr (RADIANS) from source hpr (RADIANS) + offset hpr (RADIANS)
		@param hprSource source hpr (RADIANS)
		@param hprOffset offset hpr (RADIANS)
		@return hpr vector (RADIANS) */
	static osg::Vec3d RotateFreeByOffset(const osg::Vec3d& hprSource, const osg::Vec3d& hprOffset);

	/** Calculates absolute hpr (DEGREES) from source hpr (DEGREES) + offset hpr (DEGREES)
		@param hprSource source hpr (DEGREES)
		@param hprOffset offset hpr (DEGREES)
		@return hpr vector (DEGREES) */
	static osg::Vec3d RotateFreeByOffset_Deg(const osg::Vec3d& hprSource, const osg::Vec3d& hprOffset);

	/** Calculates offset hpr (RADIANS) from source hpr (RADIANS) + destination hpr (RADIANS)
		@param hprSource source hpr (RADIANS)
		@param hprDestination destination hpr (RADIANS)
		@return hpr vector (RADIANS) */
	static osg::Vec3d CalculateRotateFreeOffset(const osg::Vec3d& hprSource, const osg::Vec3d& hprDestination);

	/** Calculates offset hpr (DEGREES) from source hpr (DEGREES) + destination hpr (DEGREES)
		@param hprSource source hpr (DEGREES)
		@param hprDestination destination hpr (DEGREES)
		@return hpr vector (DEGREES) */
	static osg::Vec3d CalculateRotateFreeOffset_Deg(const osg::Vec3d& hprSource, const osg::Vec3d& hprDestination);

	/** Cuts the offset hpr (RADIANS) to lookat by gimbals
		@param xyzLookat lookat xyz
		@param xyzSource source xyz
		@param hprSource source hpr (RADIANS)
		@param headingOffsetMinMax heading (RADIANS) gimbals
		@param pitchOffsetMinMax pitch (RADIANS) gimbals
		@output hprOffsetOut offset hpr (RADIANS)
		@return is offset cut */
	static bool CutLookatByGimbals(const osg::Vec3d& xyzLookat,
								   const osg::Vec3d& xyzSource, const osg::Vec3d& hprSource,
								   const osg::Vec2d& headingOffsetMinMax, const osg::Vec2d& pitchOffsetMinMax,
								   osg::Vec3d& hprOffsetOut);

	/** Cuts the offset hpr (DEGREES) to lookat by gimbals
		@param xyzLookat lookat xyz
		@param xyzSource source xyz
		@param hprSource source hpr (DEGREES)
		@param headingOffsetMinMax heading (DEGREES) gimbals
		@param pitchOffsetMinMax pitch (DEGREES) gimbals
		@output hprOffsetOut offset hp (DEGREES)
		@return is offset cut */
	static bool CutLookatByGimbals_Deg(const osg::Vec3d& xyzLookat,
									   const osg::Vec3d& xyzSource, const osg::Vec3d& hprSource,
									   const osg::Vec2d& headingOffsetMinMax, const osg::Vec2d& pitchOffsetMinMax,
									   osg::Vec3d& hprOffsetOut);

	/** Cuts the offset hpr (RADIANS) by gimbals
	@param hprOffset offset hpr (RADIANS)
	@param headingOffsetMinMax heading (RADIANS) gimbals
	@param pitchOffsetMinMax pitch (RADIANS) gimbals
	@output hprOffsetOut offset hpr (RADIANS)
	@return is offset cut */
	static bool CutOffsetByGimbals(const osg::Vec3d& hprOffset,
								   const osg::Vec2d& headingOffsetMinMax, const osg::Vec2d& pitchOffsetMinMax,
								   osg::Vec3d& hprOffsetOut);

	/** Cuts the offset hpr (DEGREES) by gimbals
	@param hprOffset offset hpr (DEGREES)
	@param headingOffsetMinMax heading (DEGREES) gimbals
	@param pitchOffsetMinMax pitch (DEGREES) gimbals
	@output hprOffsetOut offset hp (DEGREES)
	@return is offset cut */
	static bool CutOffsetByGimbals_Deg(const osg::Vec3d& hprOffset,
									   const osg::Vec2d& headingOffsetMinMax, const osg::Vec2d& pitchOffsetMinMax,
									   osg::Vec3d& hprOffsetOut);

	/** Calculate offset hpr (RADIANS) from lookat xyz
		@param xyzLookat lookat xyz
		@param xyzSource source xyz
		@param hprSource source hpr (RADIANS)
		@return offset hpr (RADIANS) */
	static osg::Vec3d CalculateLookatToOffset(const osg::Vec3d& xyzLookat,
											  const osg::Vec3d& xyzSource,
											  const osg::Vec3d& hprSource);

	/** Calculate offset hpr (DEGREES) from lookat xyz
		@param xyzLookat lookat xyz
		@param xyzSource source xyz
		@param hprSource source hpr (DEGREES)
		@return offset hpr (DEGREES) */
	static osg::Vec3d CalculateLookatToOffset_Deg(const osg::Vec3d& xyzLookat,
												  const osg::Vec3d& xyzSource,
												  const osg::Vec3d& hprSource);

	/** Rotates offset hpr (RADIANS) from offset hpr (RADIANS) to lookat xyz by speed
		@param xyzLookat lookat xyz
		@param xyzSource source xyz
		@param hprSource source hpr (RADIANS)
		@param hprOffset offset hpr (RADIANS)
		@param dt delta time
		@param anglePerSec angle per sec (RADIANS)
		@return offset hpr (RADIANS) */
	static osg::Vec3d RotateFromOffsetToLookatBySpeed(const osg::Vec3d& xyzLookat,
													  const osg::Vec3d& xyzSource,
													  const osg::Vec3d& hprSource,
													  const osg::Vec3d& hprOffset,
													  double dt, double anglePerSec);

	/** Rotates offset hpr (DEGREES) from offset hpr (DEGREES) to lookat xyz by speed
		@param xyzLookat lookat xyz
		@param xyzSource source xyz
		@param hprSource source hpr (DEGREES)
		@param hprOffset offset hpr (DEGREES)
		@param dt delta time
		@param anglePerSec angle per sec (DEGREES)
		@return offset hpr (DEGREES) */
	static osg::Vec3d RotateFromOffsetToLookatBySpeed_Deg(const osg::Vec3d& xyzLookat,
														  const osg::Vec3d& xyzSource,
														  const osg::Vec3d& hprSource,
														  const osg::Vec3d& hprOffset,
														  double dt, double anglePerSec);

	/** Rotates offset hpr (RADIANS) from prev lookat xyz to lookat xyz by speed
		@param xyzLookatSource source lookat xyz
		@param xyzLookatDestination destination lookat xyz
		@param xyzSource source xyz
		@param hprSource source hpr (RADIANS)
		@param dt delta time
		@param anglePerSec angle per sec (RADIANS)
		@return lookat xyz */
	static osg::Vec3d RotateFromLookatToLookatBySpeed(const osg::Vec3d& xyzLookatSource,
													  const osg::Vec3d& xyzLookatDestination,
													  const osg::Vec3d& xyzSource,
													  const osg::Vec3d& hprSource,
													  double dt, double anglePerSec);

	/** Rotates offset hpr (DEGREES) from prev lookat xyz to lookat xyz by speed
		@param xyzLookatSource source lookat xyz
		@param xyzLookatDestination destination lookat xyz
		@param xyzSource source xyz
		@param hprSource source hpr (DEGREES)
		@param dt delta time
		@param anglePerSec angle per sec (DEGREES)
		@return offset hpr (DEGREES) */
	static osg::Vec3d RotateFromLookatToLookatBySpeed_Deg(const osg::Vec3d& xyzLookatSource,
														  const osg::Vec3d& xyzLookatDestination,
														  const osg::Vec3d& xyzSource,
														  const osg::Vec3d& hprSource,
														  double dt, double anglePerSec);
};
