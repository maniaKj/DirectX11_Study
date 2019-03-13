struct VS_INPUT
{
    float3 inPos : POSITION;
    //float3 inColor : COLOR;
    float2 inTexCoord : TEXCOORD;
};

struct VS_OUTPUT
{
	float4 outPosition : SV_POSITION;
    //float3 outColor : COLOR;
    float2 outTexCoord : TEXCOORD;
};

VS_OUTPUT main(VS_INPUT input)
{
    VS_OUTPUT output;
    output.outPosition = float4(input.inPos, 1.0f);
    //output.outColor = input.inColor;
    output.outTexCoord = input.inTexCoord;
    return output;
}