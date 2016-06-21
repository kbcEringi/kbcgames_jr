/*
 *2D�`��shader
 */
texture g_diffuseTexture;		//�f�B�t���[�Y�e�N�X�`���B
sampler g_diffuseTextureSampler =
sampler_state
{
	Texture = <g_diffuseTexture>;
	AddressU = Wrap;
	AddressV = Wrap;
};

float4x4 matWorld;

bool isLuminance;
float g_luminance;



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

/*!
* @brief	�A���t�@�ɖ��ߍ��ދP�x���v�Z�B
*/
float CalcLuminance(float3 color)
{
	float luminance = dot(color, float3(0.2125f, 0.7154f, 0.0721f)) + g_luminance;
	if (luminance > 1.0f){
		luminance = 1.0f / luminance;
	}
	else{
		luminance = 1.0f;
	}
	return luminance;
}

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
	float4 color = tex2D(g_diffuseTextureSampler, In.uv) * In.color;
	//�A���t�@�ɋP�x�𖄂ߍ���
	if (isLuminance){
		color.a *= CalcLuminance(color.xyz);
	}
	return color;
}

technique Tech
{
	pass p0
	{
		VertexShader = compile vs_2_0 vs_main();
		PixelShader = compile ps_2_0 ps_main();
	}
};