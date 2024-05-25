#include "Player.h"
#include "Novice.h"
#include "math/Easing.h"

void Player::Initialize(const Vector2& position) {
    position_ = position;
    prePosition_ = position;  // 初期化時に前の位置も現在の位置に設定
}

void Player::Update(Vector2Int& mousePosition,Vector2& point) {
    if (Novice::IsTriggerMouse(1)) {
        prePosition_ = position_;
        point = { static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y) };
        moveTimer_ = kMoveTime;
    }

    if (moveTimer_ > 0.0f) {
        float t = 1.0f - (moveTimer_ / kMoveTime);
        Easeing(easename::Linear, position_, prePosition_, point, t);  // イージング関数で位置を更新
        moveTimer_ -= 1.0f / 60.0f;
    }
}

void Player::Draw() {
    Novice::DrawBox(static_cast<int>(position_.x), static_cast<int>(position_.y), kWidth, kHeight, 0.0f, GREEN, kFillModeSolid);
}