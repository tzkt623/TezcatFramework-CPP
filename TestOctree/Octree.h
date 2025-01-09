#pragma once
#include "OctreeNode.h"
#include "OctreeAgent.h"

class Octree : public OctreeNode
{
    /*
    * 0层:1(8^0)
    * 1层:8(8^1)
    * 2层:8*8(8^2)
    * 3层:8*8*8(8^3)
    * 4层:8*8*8*8(8^4)
    * N层:8^n
    * 总计:8^0+...+8^n
    */

public:
    void update();

    void setBoundingBox(OctVector3 min, OctVector3 max)
    {
        mBoundingBox.reset(min, max);
    }

    void collectBoundingBox(const BoundingBox& other)
    {
        mBoundingBox.collect(other);
    }

private:


public:
    static void calcuBoundingBox(BoundingBox& parentBox, std::array<BoundingBox, 8>& outBox)
    {
        OctVector3 dimensions = parentBox.getDimensions();
        OctVector3 center = parentBox.min + (dimensions * 0.5f);

        /*
        *    /---------------/|
        *   /       /       / |
        *  /	   /	   /  |
        * /		  /	      /	  |
        * |-------|-------|	 /|
        * |	N2	  |	N1    |	/ |
        * |		  |		  |/  |
        * |-------|-------|   /
        * |	N3	  |	N4	  |  /
        * |		  |		  | /
        * |-------|-------|/
        *
        * front
        *
        */

        //front 4
        outBox[0].reset(center, parentBox.max);

        outBox[1].reset(OctVector3(parentBox.min.x, center.y, center.z)
            , OctVector3(center.x, parentBox.max.y, parentBox.max.z));

        outBox[2].reset(OctVector3(parentBox.min.x, parentBox.min.y, center.z)
            , OctVector3(center.x, center.y, parentBox.max.z));

        outBox[3].reset(OctVector3(center.x, parentBox.min.y, center.z)
            , OctVector3(parentBox.max.x, center.y, parentBox.max.z));

        //back 4
        outBox[4].reset(OctVector3(center.x, center.y, parentBox.min.z)
            , OctVector3(parentBox.max.x, parentBox.max.y, center.z));

        outBox[5].reset(OctVector3(parentBox.min.x, center.y, parentBox.min.z)
            , OctVector3(center.x, parentBox.max.y, center.z));

        outBox[6].reset(parentBox.min, center);

        outBox[7].reset(OctVector3(center.x, parentBox.min.y, parentBox.min.z)
            , OctVector3(parentBox.max.x, center.y, center.z));
    }

};

