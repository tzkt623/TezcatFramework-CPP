#pragma once

#include "OctreeConfig.h"

struct BoundingBox
{
    BoundingBox()
    {

    }

    BoundingBox(const OctVector3& min, const OctVector3& max)
        : min(min)
        , max(max)
    {}

    void reset(const OctVector3& min, const OctVector3& max)
    {
        this->min = min;
        this->max = max;
    }

    bool contains(const BoundingBox& other)
    {
        if ((min.x <= other.min.x && min.y <= other.min.y && min.z <= other.min.z)
            && (max.x >= other.max.x && max.y >= other.max.y && max.z >= other.max.z))
        {
            return true;
        }

        return false;
    }

    bool impact(const BoundingBox& other)
    {
        if (min.x > other.max.x || min.y > other.max.y || min.z > other.max.z
            || max.x < other.min.x || max.y < other.min.y || max.z < other.min.z)
        {
            return false;
        }

        return true;
    }

    void translate(const OctVector3& offset)
    {
        this->min += offset;
        this->max += offset;
    }

    void setPosition(OctVector3& position)
    {
        auto d = this->getDimensions() * 0.5f;
        this->min = position - d;
        this->max = position + d;
    }

    void collect(const BoundingBox& other)
    {
        if (min.x >= other.min.x)
        {
            min.x = other.min.x;
        }

        if (min.y >= other.min.y)
        {
            min.y = other.min.y;
        }

        if (min.z >= other.min.z)
        {
            min.z = other.min.z;
        }

        if (max.x <= other.max.x)
        {
            max.x = other.max.x;
        }

        if (max.y <= other.max.y)
        {
            max.y = other.max.y;
        }

        if (max.z <= other.max.z)
        {
            max.z = other.max.z;
        }
    }

    OctVector3 getDimensions()
    {
        return max - min;
    }

    OctVector3 getPosition()
    {
        return (this->min + this->max) * 0.5;
    }


    OctVector3 max;
    OctVector3 min;

};

