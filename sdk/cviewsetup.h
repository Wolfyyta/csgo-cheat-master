#pragma once
#include "cvector.h"

class CViewSetup
{
public:
	int			x;
	int			unscaledX;
	int			y;
	int			unscaledY;
	int			width;
	int			unscaledWidth;
	int			height;
	int			unscaledHeight;
	bool		ortho;
	float		orthoLeft;
	float		orthoTop;
	float		orthoRight;
	float		orthoBottom;
	std::byte	pad0[0x7C];
	float		fov;
	float		viewModelFOV;
	CVector		origin;
	CVector		view;
	float		nearZ;
	float		farZ;
	float		nearViewmodelZ;
	float		farViewmodelZ;
	float		aspectRatio;
	float		nearBlurDepth;
	float		nearFocusDepth;
	float		farFocusDepth;
	float		farBlurDepth;
	float		nearBlurRadius;
	float		farBlurRadius;
	float		doFQuality;
	int			motionBlurMode;
	float		shutterTime;
	CVector		shutterOpenPosition;
	CVector		shutterOpenAngles;
	CVector		shutterClosePosition;
	CVector		shutterCloseAngles;
	float		offCenterTop;
	float		offCenterBottom;
	float		offCenterLeft;
	float		offCenterRight;
	bool		offCenter : 1;
	bool		renderToSubrectOfLargerScreen : 1;
	bool		bloomAndToneMapping : 1;
	bool		depthOfField : 1;
	bool		HDRTarget : 1;
	bool		drawWorldNormal : 1;
	bool		cullFontFaces : 1;
	bool		cacheFullSceneState : 1;
	bool		CSMView : 1;
};