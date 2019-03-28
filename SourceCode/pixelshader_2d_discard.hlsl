struct PS_INPUT
{
    float4 inPosition : SV_POSITION;
    float2 inTexCoord : TEXCOORD;
};

Texture2D objTexture : TEXTURE : register(t0);
SamplerState objSamplerState : SAMPLER : register(s0);

float4 main(PS_INPUT input) : SV_Target
{
    float4 sampleColor = objTexture.Sample(objSamplerState, input.inTexCoord);
    if (sampleColor.a < 0.25) //알파값이 일정 값 이하면 그 픽셀은 버린다.
        discard;
    return float4(0, 1, 0, 0);
}