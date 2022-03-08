Texture2D ColorMap : register(t0);
SamplerState colorSampler : register(s0);

cbuffer MatrixBuffer : register(b0)
{
    matrix World;
    matrix View;
    matrix Projection;
};

cbuffer LightBuffer : register(b1)
{
    float3 direction;
    float padding;
    float4 ambient;
    float4 diffuse;
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

    Output.pos = mul(inp.pos,World);
    Output.pos = mul(Output.pos,View);
    Output.pos = mul(Output.pos,Projection);

    Output.normal = normalize(mul(inp.normal, (float3x3)World));

    Output.tex = inp.tex;

    return Output;
}

float4 CalculateDirectional(float4 Texture, float3 normal)
{
    float3 dir = -direction;

    float4 color = Texture * ambient;
    color += saturate(dot(dir, normal) * diffuse * Texture);

    return color;
}

float4 PS(PixelInput inp) : SV_TARGET
{
    float4 color;

    color = CalculateDirectional(ColorMap.Sample(colorSampler, inp.tex), inp.normal);

    return color;

}


