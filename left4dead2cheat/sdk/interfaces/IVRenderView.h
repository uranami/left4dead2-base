#pragma once

class IVRenderView
{
public:

    void set_color_modulation(float r, float g, float b)
    {
        float color[3] = { r, g, b };
        return callvtable< void(__thiscall*)(IVRenderView*, float[]) >(this, 7)(this, color);
    }

};
