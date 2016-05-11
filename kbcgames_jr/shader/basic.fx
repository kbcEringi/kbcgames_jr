/*!
 *@brief	�ȒP�ȃe�N�X�`���\��t���V�F�[�_�[�B
 */


float4x4 g_worldMatrix;			//���[���h�s��B
float4x4 g_viewMatrix : register(c0);			//�r���[�s��B
float4x4 g_projectionMatrix;	//�v���W�F�N�V�����s��B
float4x4 g_lvpMatrix;	//�v���W�F�N�V�����s��B

#define DIFFUSE_LIGHT_NUM 6
float4 g_diffuseLightDirection[DIFFUSE_LIGHT_NUM];
float4 g_diffuseLightColor[DIFFUSE_LIGHT_NUM];
float4 g_ambientLight;

float3 vEyePos;//�J�����̈ʒu

texture g_diffuseTexture;		//�f�B�t���[�Y�e�N�X�`���B
sampler g_diffuseTextureSampler = 
sampler_state
{
	Texture = <g_diffuseTexture>;
    MipFilter = NONE;
    MinFilter = NONE;
    MagFilter = NONE;
    AddressU = Wrap;
	AddressV = Wrap;
};

texture g_ShadowTexture;		//�f�B�t���[�Y�e�N�X�`���B
sampler g_ShadowTextureSampler =
sampler_state
{
	Texture = <g_ShadowTexture>;
	MipFilter = NONE;
	MinFilter = NONE;
	MagFilter = NONE;
	AddressU = Clamp;
	AddressV = Clamp;
};

struct VS_INPUT{
	float4	pos		: POSITION;
	float4	color	: COLOR0;
	float2	uv		: TEXCOORD0;
	float3	normal	: NORMAL;
};

struct VS_OUTPUT{
	float4	pos		: POSITION;
	float4	color	: COLOR0;
	float2	uv		: TEXCOORD0;
	float4  specColor : TEXCOORD1;
	float4 shadowpos : TEXCOORD2;
};

/*!
*@brief	���_�V�F�[�_�[�B
*/
//�ʏ�
VS_OUTPUT VSMain(VS_INPUT In)
{
	VS_OUTPUT Out = (VS_OUTPUT)0;

	float3 N = normalize(mul(In.normal, (float3x3)g_worldMatrix));
		float4 lig = 0.0f;
	{
		for (int i = 0; i < DIFFUSE_LIGHT_NUM; i++)
		{
			lig.xyz += max(0.0f, dot(N, -g_diffuseLightDirection[i].xyz)) * g_diffuseLightColor[i].xyz;
		}
		lig += g_ambientLight;
	}
	Out.color = lig;
	//���W�ϊ�
	float4 pos;
	pos = mul(In.pos, g_worldMatrix);		//���f���̃��[�J����Ԃ��烏�[���h��Ԃɕϊ��B
	Out.shadowpos = mul(pos, g_lvpMatrix);
	pos = mul(pos, g_viewMatrix);			//���[���h��Ԃ���r���[��Ԃɕϊ��B
	pos = mul(pos, g_projectionMatrix);	//�r���[��Ԃ���ˉe��Ԃɕϊ��B
	Out.pos = pos;
	Out.uv = In.uv;
	
	return Out;
}
/*!
	*@brief	�s�N�Z���V�F�[�_�[�B
	*/
float4 PSMain(VS_OUTPUT In) : COLOR
{
	float4 pos = In.shadowpos;
	float2 uv = float2(0.5f, -0.5f) * pos.xy / pos.w + float2(0.5f, 0.5f);
	float4 color = tex2D(g_diffuseTextureSampler, In.uv);
	//color *= tex2D(g_ShadowTextureSampler, uv);
	return color;
}

VS_OUTPUT VSSpecular(VS_INPUT In)
{
	VS_OUTPUT Out = (VS_OUTPUT)0;

	float3 eye = normalize(vEyePos.xyz - In.pos);//�I�u�W�F�N�g����̃J�����̖ڐ�
		float3 N = In.normal.xyz;
		float3 R = -eye + 2.0f*dot(N, eye)*N;//���˃x�N�g��

		float4 lig = 0.0f;
		float4 spec = 0.0f;
	for (int i = 0; i < DIFFUSE_LIGHT_NUM; i++)
{
		lig.xyz += max(0.0, dot(N, -g_diffuseLightDirection[i].xyz)) * g_diffuseLightColor[i].xyz;
		lig.xyz += pow(max(0.0f, dot(-g_diffuseLightDirection[i].xyz, R)), 10) * g_diffuseLightColor[i].w;	//10=���ʔ��ˎw��
	}
	lig += g_ambientLight;//�����v���X
	Out.color = lig;

	//���W�ϊ�
	float4 pos;
	pos = mul(In.pos, g_worldMatrix);		//���f���̃��[�J����Ԃ��烏�[���h��Ԃɕϊ��B
	pos = mul(pos, g_viewMatrix);			//���[���h��Ԃ���r���[��Ԃɕϊ��B
	pos = mul(pos, g_projectionMatrix);	//�r���[��Ԃ���ˉe��Ԃɕϊ��B
	Out.pos = pos;
	Out.uv = In.uv;
	return Out;
}

float4 PSSpecular(VS_OUTPUT In) : COLOR
{
	return /*tex2D(g_diffuseTextureSampler, In.uv) */ In.color;
}

technique SkinModel
{
	pass p0
	{
		VertexShader 	= compile vs_2_0 VSMain();
		PixelShader 	= compile ps_2_0 PSMain();
	}
	pass p1
	{
		VertexShader = compile vs_2_0 VSSpecular();
		PixelShader = compile ps_2_0 PSSpecular();
	}
	
}