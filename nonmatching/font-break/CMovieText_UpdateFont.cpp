struct V4 { float x, y, z, w; };
struct CMovieText {
    char pad0[0x14];
    unsigned char rgba[4];
    char pad18[8];
    V4 add;
    V4 mul;
    V4 addBase;
    V4 mulBase;
};

extern "C" void CMovieText_UpdateFont(CMovieText *self)
{
    float scaled = self->mulBase.w * 0.007874016f;
    float red = self->addBase.x + (float)self->rgba[0];
    float green = self->addBase.y + (float)self->rgba[1];
    float blue = self->addBase.z + (float)self->rgba[2];
    self->add.x = red < 255.0f ? red : 255.0f;
    self->add.y = green < 255.0f ? green : 255.0f;
    self->add.z = blue < 255.0f ? blue : 255.0f;
    self->add.w = self->addBase.w;
    self->mul.x = self->mulBase.x;
    self->mul.y = self->mulBase.y;
    self->mul.z = self->mulBase.z;
    float alpha = scaled * (float)self->rgba[3];
    float result;
    if (alpha < 0.0f) result = 0.0f;
    else {
        result = alpha;
        if (1.0f < result) result = 1.0f;
    }
    self->mul.w = result;
}
