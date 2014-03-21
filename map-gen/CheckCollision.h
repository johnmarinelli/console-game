#ifndef CHECK_COLLISION_H
#define CHECK_COLLISION_H

bool checkCollision(const Rectangle& a, const Rectangle& b)
{
    int aLeft = a.mX;
    int aTop = a.mY;
    int aRight = aLeft + a.mWidth;
    int aBottom = aTop + a.mHeight;

    int bLeft = b.mX;
    int bTop = b.mY;
    int bRight = bLeft + b.mWidth;
    int bBottom = bTop + b.mHeight;

    if (aLeft >= bRight) return false;
    if (aRight <= bLeft) return false;
    if (aBottom <= bTop) return false;
    if (aTop >= bBottom) return false;

    return true;
}

#endif
