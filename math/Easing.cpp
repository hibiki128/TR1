#include "Easing.h"
#include"cmath"
#include "numbers"

float easeLinear(float t) {
	return t;
}

float easeInSine(float t) {
	return 1 - std::cosf((t * std::numbers::pi_v<float>) / 2);
}
float easeOutSine(float t) {
	return std::sinf((t * std::numbers::pi_v<float>) / 2);
}
float easeInOutSine(float t) {
	return -(std::cosf(std::numbers::pi_v<float> * t) - 1) / 2;
}
float easeInQuad(float t) {
	return t * t;
}
float easeOutQuad(float t) {
	return 1 - (1 - t) * (1 - t);
}
float easeInOutQuad(float t) {
	return t < 0.5 ? 2 * t * t : 1 - std::powf(-2 * t + 2, 2) / 2;
}
float easeInCubic(float t) {
	return t * t * t;
}
float easeOutCubic(float t) {
	return 1 - std::powf(1 - t, 3);
}
float easeInOutCubic(float t) {
	return t < 0.5 ? 4 * t * t * t : 1 - std::powf(-2 * t + 2, 3) / 2;
}
float easeInQuart(float t) {
	return t * t * t * t;
}
float easeOutQuart(float t) {
	return 1 - std::powf(1 - t, 4);
}
float easeInOutQuart(float t) {
	return t < 0.5 ? 8 * t * t * t * t : 1 - std::powf(-2 * t + 2, 4) / 2;
}
float easeInQuint(float t) {
	return t * t * t * t * t;
}
float easeOutQuint(float t) {
	return 1 - std::powf(1 - t, 5);
}
float easeInOutQuint(float t) {
	return t < 0.5 ? 16 * t * t * t * t * t : 1 - std::powf(-2 * t + 2, 5) / 2;
}
float easeInEtpo(float t) {
	return t == 0 ? 0 : std::powf(2, 10 * t - 10);
}
float easeOutEtpo(float t) {
	return t == 1 ? 1 : 1 - std::powf(2, -10 * t);
}
float easeInOutEtpo(float t) {
	return t == 0
		? 0
		: t == 1
		? 1
		: t < 0.5 ? std::powf(2, 20 * t - 10) / 2
		: (2 - std::powf(2, -20 * t + 10)) / 2;
}
float easeInCirc(float t) {
	return 1 - std::sqrtf(1 - std::powf(t, 2));
}
float easeOutCirc(float t) {
	return  std::sqrtf(1 - std::powf(t - 1, 2));
}
float easeInOutCirc(float t) {
	return t < 0.5
		? (1 - std::sqrtf(1 - std::powf(2 * t, 2))) / 2
		: (std::sqrtf(1 - std::powf(-2 * t + 2, 2)) + 1) / 2;
}
float easeInBack(float t) {
	const float c1 = 1.70158f;
	const float c3 = c1 + 1;

	return c3 * t * t * t - c1 * t * t;
}
float easeOutBack(float t) {
	const float c1 = 1.70158f;
	const float c3 = c1 + 1;

	return 1 + c3 * std::powf(t - 1, 3) + c1 * std::powf(t - 1, 2);
}
float easeInOutBack(float t) {
	const float  c1 = 1.70158f;
	const float  c2 = c1 * 1.525f;

	return t < 0.5
		? (std::powf(2 * t, 2) * ((c2 + 1) * 2 * t - c2)) / 2
		: (std::powf(2 * t - 2, 2) * ((c2 + 1) * (t * 2 - 2) + c2) + 2) / 2;
}
float easeInElastic(float t) {
	const float  c4 = (2 * std::numbers::pi_v<float>) / 3;

	return t == 0
		? 0
		: t == 1
		? 1
		: -std::powf(2, 10 * t - 10) * std::sinf((t * 10 - 10.75f) * c4);
}
float easeOutElastic(float t) {
	const float  c4 = (2 * std::numbers::pi_v<float>) / 3;

	return t == 0
		? 0
		: t == 1
		? 1
		: std::powf(2, -10 * t) * std::sinf((t * 10 - 0.75f) * c4) + 1;
}
float easeInOutElastic(float t) {
	const float  c5 = (2 * std::numbers::pi_v<float>) / 4.5f;

	return t == 0
		? 0
		: t == 1
		? 1
		: t < 0.5
		? -(std::powf(2, 20 * t - 10) * std::sinf((20 * t - 11.125f) * c5)) / 2
		: (std::powf(2, -20 * t + 10) * std::sinf((20 * t - 11.125f) * c5)) / 2 + 1;
}
float easeOutBounce(float t) {
	const float  n1 = 7.5625f;
	const float  d1 = 2.75f;

	if (t < 1 / d1) {
		return n1 * t * t;
	}
	else if (t < 2 / d1) {
		return n1 * (t -= 1.5f / d1) * t + 0.75f;
	}
	else if (t < 2.5 / d1) {
		return n1 * (t -= 2.25f / d1) * t + 0.9375f;
	}
	else {
		return n1 * (t -= 2.625f / d1) * t + 0.984375f;
	}
}
float easeInBounce(float t) {
	return 1 - easeOutBounce(1 - t);
}
float easeInOutBounce(float t) {
	return t < 0.5
		? (1 - easeOutBounce(1 - 2 * t)) / 2
		: (1 + easeOutBounce(2 * t - 1)) / 2;
}
void Easeing(easename EaseName, Vector2& PlayerPos, const Vector2& StartPos, const Vector2& EndPos, float& t) {
	switch (EaseName) {
	 case Linear:
        PlayerPos = StartPos + (EndPos - StartPos) * easeLinear(t);
        break;
	case InSine:
		PlayerPos = StartPos + (EndPos - StartPos) * easeInSine(t);
		break;
	case OutSine:
		PlayerPos = StartPos + (EndPos - StartPos) * easeOutSine(t);
		break;
	case InOutSine:
		PlayerPos = StartPos + (EndPos - StartPos) * easeInOutSine(t);
		break;
	case InQuad:
		PlayerPos = StartPos + (EndPos - StartPos) * easeInQuad(t);
		break;
	case OutQuad:
		PlayerPos = StartPos + (EndPos - StartPos) * easeOutQuad(t);
		break;
	case InOutQuad:
		PlayerPos = StartPos + (EndPos - StartPos) * easeInOutQuad(t);
		break;
	case InCubic:
		PlayerPos = StartPos + (EndPos - StartPos) * easeInCubic(t);
		break;
	case OutCubic:
		PlayerPos = StartPos + (EndPos - StartPos) * easeOutCubic(t);
		break;
	case InOutCubic:
		PlayerPos = StartPos + (EndPos - StartPos) * easeInOutCubic(t);
		break;
	case InQuart:
		PlayerPos = StartPos + (EndPos - StartPos) * easeInQuart(t);
		break;
	case OutQuart:
		PlayerPos = StartPos + (EndPos - StartPos) * easeOutQuart(t);
		break;
	case InOutQuart:
		PlayerPos = StartPos + (EndPos - StartPos) * easeInOutQuart(t);
		break;
	case InQuint:
		PlayerPos = StartPos + (EndPos - StartPos) * easeInQuint(t);
		break;
	case OutQuint:
		PlayerPos = StartPos + (EndPos - StartPos) * easeOutQuint(t);
		break;
	case InOutQuint:
		PlayerPos = StartPos + (EndPos - StartPos) * easeInOutQuint(t);
		break;
	case InEtpo:
		PlayerPos = StartPos + (EndPos - StartPos) * easeInEtpo(t);
		break;
	case OutEtpo:
		PlayerPos = StartPos + (EndPos - StartPos) * easeOutEtpo(t);
		break;
	case InOutEtpo:
		PlayerPos = StartPos + (EndPos - StartPos) * easeInOutEtpo(t);
		break;
	case InCirc:
		PlayerPos = StartPos + (EndPos - StartPos) * easeInCirc(t);
		break;
	case OutCirc:
		PlayerPos = StartPos + (EndPos - StartPos) * easeOutCirc(t);
		break;
	case InOutCirc:
		PlayerPos = StartPos + (EndPos - StartPos) * easeInOutCirc(t);
		break;
	case InBack:
		PlayerPos = StartPos + (EndPos - StartPos) * easeInBack(t);
		break;
	case OutBack:
		PlayerPos = StartPos + (EndPos - StartPos) * easeOutBack(t);
		break;
	case InOutBack:
		PlayerPos = StartPos + (EndPos - StartPos) * easeInOutBack(t);
		break;
	case InElastic:
		PlayerPos = StartPos + (EndPos - StartPos) * easeInElastic(t);
		break;
	case OutElastic:
		PlayerPos = StartPos + (EndPos - StartPos) * easeOutElastic(t);
		break;
	case InOutElastic:
		PlayerPos = StartPos + (EndPos - StartPos) * easeInOutElastic(t);
		break;
	case InBounce:
		PlayerPos = StartPos + (EndPos - StartPos) * easeInBounce(t);
		break;
	case OutBounce:
		PlayerPos = StartPos + (EndPos - StartPos) * easeOutBounce(t);
		break;
	case InOutBounce:
		PlayerPos = StartPos + (EndPos - StartPos) * easeInOutBounce(t);
		break;
	}
}
