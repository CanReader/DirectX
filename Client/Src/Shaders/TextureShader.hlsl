Texture2D ColorMap : register(t0);
SamplerState colorSampler : register(s0);

cbuffer MatrixBuffer : register(b0)
{
    matrix World;
    matrix View;
    matrix Projection;
};

cbuffer DirectionalLightBuffer : register(b1)
{
    float3 DLB_direction;
    float DLB_padding;
    float4 DLB_ambient;
    float4 DLB_diffuse;
};

cbuffer PointLightBuffer : register(b2)
{
    float3 PLB_direction;
    float padding1;
    float4 PLB_ambient;
    float4 PLB_diffuse;
    float3 PLB_position;
    float padding2;
    float3 PLB_att;
    float padding3;
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
    float3 dir = -DLB_direction;

    float4 color = Texture * DLB_ambient;
    color += saturate(dot(dir, normal) * DLB_diffuse * Texture);

    return color;
}

float4 CalculatePoint(float4 Texture, float3 normal)
{
    return Texture;
}

float4 PS(PixelInput inp) : SV_TARGET
{
    float4 color;

    color = CalculateDirectional(ColorMap.Sample(colorSampler, inp.tex), inp.normal);

    //color = CalculatePoint(ColorMap.Sample(colorSampler, inp.tex), inp.normal);

    return color;

}


