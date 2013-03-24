//
// AngleUtils.h
// hifi
//
// Created by Tobias Schwinger on 3/23/13.
// Copyright (c) 2013 High Fidelity, Inc. All rights reserved.
//

#ifndef __hifi__AngleUtils__
#define __hifi__AngleUtils__

#include <math.h>

struct Degrees
{
    static float pi()       { return 180.0f; }
    static float twice_pi() { return 360.0f; }
    static float half_pi()  { return 90.0f; }
};

struct Radians
{
    static float pi()       { return 3.141592653589793f; }
    static float twice_pi() { return 6.283185307179586f; }
    static float half_pi()  { return 1.5707963267948966; }
};

struct Rotations
{
    static float pi()       { return 0.5f; }
    static float twice_pi() { return 1.0f; }
    static float half_pi()  { return 0.25f; }
};

/**
 * Clamps an angle to the range of [-180; 180) degrees.
 */
template< class Unit >
float angleSignedNormal(float a)
{
    float result = remainder(a, Unit::twice_pi());
    if (result == Unit::pi())
        result = -Unit::pi();
    return result;
}

/**
 * Clamps an angle to the range of [0; 360) degrees.
 */
template< class Unit >
float angleUnsignedNormal(float a)
{
    return angleSignedNormal<Unit>(a - Unit::pi()) + Unit::pi();
}


/** 
 * Clamps a polar direction so that azimuth is in the range of [0; 360)
 * degrees and altitude is in the range of [-90; 90] degrees.
 *
 * The so normalized angle still contains ambiguity due to gimbal lock:
 * Both poles can be reached from any azimuthal direction.
 */
template< class Unit >
void angleHorizontalPolar(float& azimuth, float& altitude)
{
    altitude = angleSignedNormal<Unit>(altitude);
    if (altitude > Unit::half_pi())
    {
        altitude = Unit::pi() - altitude;
        azimuth = -azimuth;
    }
    else if (altitude < -Unit::half_pi())
    {
        altitude = -Unit::pi() - altitude;
        azimuth = -azimuth;
    }
    azimuth = angleUnsignedNormal<Unit>(azimuth);
}

#endif

