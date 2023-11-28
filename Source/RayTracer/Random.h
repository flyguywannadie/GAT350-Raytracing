#pragma once


void seedRandom(unsigned int seed)
{
    srand(seed);
}

float random01()
{
    return rand() / (float)RAND_MAX;
}

float random(float min, float max)
{
    if (min > max) std::swap(min, max);
    return min + (max - min) * random01();
}