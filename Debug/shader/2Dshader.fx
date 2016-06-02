/*
 *2D描画shader
 */
texture g_diffuseTexture;		//ディフューズテクスチャ。
sampler g_diffuseTextureSampler =
sampler_state
{
	Texture = <g_diffuseTexture>;
	AddressU = Wrap;
	AddressV = Wrap;
};

float4x4 matWorld;

struct VS_IN
{
	float4 pos		: POSITION;
	float4 color	: COLOR0;
	float2 uv		: TEXCOORD0;
};

struct VS_OUT
{
	float4 pos		: POSITION;
	float4 color	: COLOR0;
	float2 uv		: TEXCOORD0;
};

VS_OUT vs_main(VS_IN In)
{
	VS_OUT Out = (VS_OUT)0;


	Out.pos = mul(In.pos, matWorld);

	Out.color = In.color;
	Out.uv = In.uv;

	return Out;
}

float4 ps_main(VS_OUT In) : COLOR0
{
	return tex2D(g_diffuseTextureSampler, In.uv) * In.color;
}

technique Tech
{
	pass p0
	{
		VertexShader = compile vs_2_0 vs_main();
		PixelShader = compile ps_2_0 ps_main();
	}
};