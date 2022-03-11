Texture2D ColorMap : register(t0);
SamplerState colorSampler : register(s0);

cbuffer MatrixBuffer : register(b0)
{
    matrix World;
    matrix View;
    matrix Projection;
};
/*
cbuffer DirectionalLightBuffer : register(b1)
{
    float3 DLB_direction;
    float DLB_padding;
    float4 DLB_ambient;
    float4 DLB_diffuse;
};*/

cbuffer PointLightBuffer : register(b1)
{
    float4 PLB_ambient;
    float4 PLB_diffuse;
    float3 PLB_position;
    float PLB_range;
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
    float4 WorldPos : WORLD_POSITION;
};

PixelInput VS(VertexInput inp)
{
    PixelInput Output;

    Output.WorldPos = mul(inp.pos, World);

    inp.pos.w = 1.0f;
    Output.pos = mul(inp.pos, World);
    Output.pos = mul(Output.pos,View);
    Output.pos = mul(Output.pos,Projection);

    Output.normal = normalize(mul(inp.normal, (float3x3)World));

    Output.tex = inp.tex;

    return Output;
}
/*
float4 CalculateDirectional(float4 Texture, float3 normal)
{
    float3 dir = -DLB_direction;

    float4 color = Texture * DLB_ambient;
    color += saturate(dot(dir, normal) * DLB_diffuse * Texture);
    
    return color;
}
*/
float4 CalculatePoint(float4 Texture, float3 normal, float4 WorldLoc)
{
    float4 color = float4(0,0,0,0);
    float4 TotalAmbient = Texture * float4(0.1,0.1,0.1,1);

    float3 LightToPixel = PLB_position - float3(WorldLoc.x, WorldLoc.y, WorldLoc.z);

    float d = length(LightToPixel);
    
    LightToPixel /= d;

    if (d > PLB_range)
        return TotalAmbient;

    float LightAmount = dot(LightToPixel, normal);

    if(LightAmount > 0.0f)
    {
        color += LightAmount * PLB_diffuse * Texture;

        color /= PLB_att[0] + (PLB_att[1] * d) + (PLB_att[2]*d*d);
    }

    color = saturate(color + TotalAmbient);

    return color;
}

float4 PS(PixelInput inp) : SV_TARGET
{
    float4 color;

    //color = CalculateDirectional(ColorMap.Sample(colorSampler, inp.tex), inp.normal);

    color = CalculatePoint(ColorMap.Sample(colorSampler, inp.tex), inp.normal,inp.WorldPos);

    return color;

}


