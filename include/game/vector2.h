//
// Created by mac on 5/22/24.
//

#ifndef PAC_PLUS_VECTOR2_H
#define PAC_PLUS_VECTOR2_H

template <typename T>
class Vector2 {
   public:
    Vector2() = default;

    Vector2(T tX, T tY) : X(tX), Y(tY) {};

    template <typename U>
    explicit Vector2(const Vector2<U>& vector)
        : X(static_cast<T>(vector.X)), Y(static_cast<T>(vector.Y)) {}

    T X;
    T Y;
};

#endif  // PAC_PLUS_VECTOR2_H
