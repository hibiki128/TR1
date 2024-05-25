#pragma once
#include"Vector2.h"
float easeLinear(float t);
float easeInSine(float t);
float easeOutSine(float t);
float easeInOutSine(float t);
float easeInQuad(float t);
float easeOutQuad(float t);
float easeInOutQuad(float t);
float easeInCubic(float t);
float easeOutCubic(float t);
float easeInOutCubic(float t);
float easeInQuart(float t);
float easeOutQuart(float t);
float easeInOutQuart(float t);
float easeInQuint(float t);
float easeOutQuint(float t);
float easeInOutQuint(float t);
float easeInEtpo(float t);
float easeOutEtpo(float t);
float easeInOutEtpo(float t);
float easeInCirc(float t);
float easeOutCirc(float t);
float easeInOutCirc(float t);
float easeInBack(float t);
float easeOutBack(float t);
float easeInOutBack(float t);
float easeInElastic(float t);
float easeOutElastic(float t);
float easeInOutElastic(float t);
float easeOutBounce(float t);
float easeInBounce(float t);
float easeInOutBounce(float t);
enum easename {
	Linear,
	InSine,
	OutSine,
	InOutSine,
	InQuad,
	OutQuad,
	InOutQuad,
	InCubic,
	OutCubic,
	InOutCubic,
	InQuart,
	OutQuart,
	InOutQuart,
	InQuint,
	OutQuint,
	InOutQuint,
	InEtpo,
	OutEtpo,
	InOutEtpo,
	InCirc,
	OutCirc,
	InOutCirc,
	InBack,
	OutBack,
	InOutBack,
	InElastic,
	OutElastic,
	InOutElastic,
	InBounce,
	OutBounce,
	InOutBounce,
};

void Easeing(easename EaseName,  Vector2& PlayerPos, const Vector2& StartPos, const Vector2& EndPos, float& t);