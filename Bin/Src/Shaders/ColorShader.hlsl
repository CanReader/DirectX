cbuffer MatrixBuffer : register(b0)
{
    matrix World;
    matrix View;
    matrix Projection;
};

cbuffer LightBuffer : register(b1)
{
    float4 diffuse;
    float3 direction;
    float padding;
};

struct VertexInput
{
    float4 pos : POSITION;
    float2 tex : TEXCOORD0;
    float3 normal : NORMAL;
};

struct PixelInput
{
    float4 pos : SV_POSITION;
    float2 tex : TEXCOORD0;
    float3 normal : NORMAL;
};

PixelInput VS(VertexInput inp)
{
    PixelInput Output;

    inp.pos.w = 1.0f;

    Output.pos = mul(inp.pos, World);
    Output.pos = mul(Output.pos, View);
    Output.pos = mul(Output.pos, Projection);

    Output.normal = normalize(mul(inp.normal, (float3x3) World));

    Output.tex = inp.tex;

    return Output;
}

float4 PS(PixelInput inp) : SV_TARGET
{
    return float4(0.3,0.2,0.6,0);
}
