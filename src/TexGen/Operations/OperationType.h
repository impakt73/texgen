#pragma once

enum eOperationType
{
	kOperationType_Undefined = 0,
	kOperationType_Clear,
	kOperationType_Noise,
	kOperationType_RadialGradient,
	kOperationType_AddBlend,
	kOperationType_MultiplyBlend,
	kOperationType_HorizontalGradient,
	kOperationType_VerticalGradient
};