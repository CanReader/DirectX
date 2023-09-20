Texture2D ColorMap : register(t0);
SamplerState colorSampler : register(s0);

cbuffer cbMVPObject
{
    float4x4 WVP;
};  

struct VertexInput
{
    float4 pos : POSITION;
    float2 tex : TEXCOORD;
};

struct PixelInput
{
    float4 pos : SV_POSITION;
    float2 tex : TEXCOORD;
};

PixelInput VS(VertexInput inp, float2 texCoord : TEXCOORD)
{
    inp.pos.w = 1.0f;

    PixelInput Output;
    Output.pos = mul(inp.pos,WVP);
    Output.tex = texCoord;


    return Output;
}


float4 PS(PixelInput inp) : SV_TARGET
{
    return ColorMap.Sample(colorSampler, inp.tex);
}


