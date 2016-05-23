/*!
 * @brief	�X�L�����f���V�F�[�_�[�B(4�{�[���X�L�j���O)
 */

//�X�L���s��B
#define MAX_MATRICES  26
float4x3    g_mWorldMatrixArray[MAX_MATRICES] : WORLDMATRIXARRAY;//�A�j���[�V�����p
float4x4    g_mViewProj : VIEWPROJECTION;
float		g_numBone;			//���̐��B

float4x4 g_worldMatrix;
float4x4 g_lvpMatrix;	//�v���W�F�N�V�����s��B
float3 vEyePos;//�J�����̈ʒu

#define DIFFUSE_LIGHT_NUM 6
float4 g_diffuseLightDirection[DIFFUSE_LIGHT_NUM];
float4 g_diffuseLightColor[DIFFUSE_LIGHT_NUM];
float4 g_ambientLight;

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
texture g_ShadowTexture;		//�V���h�E�e�N�X�`���B
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

/*!
 * @brief	���͒��_
 */
struct VS_INPUT
{
    float4  Pos             : POSITION;
    float4  BlendWeights    : BLENDWEIGHT;
    float4  BlendIndices    : BLENDINDICES;
    float3  Normal          : NORMAL;
	float4	color	: COLOR0;
    float3  Tex0            : TEXCOORD0;
};

/*!
 * @brief	�o�͒��_�B
 */
struct VS_OUTPUT
{
	float4  Pos     : POSITION;
	float4	color	: COLOR0;
    float2  Tex0    : TEXCOORD0;
	float4  specColor : TEXCOORD1;
	float4 shadowpos : TEXCOORD2;
};

void CalcWorldMatrixFromSkinMatrix(VS_INPUT In, out float3 Pos, out float3 Normal)
{
	Pos = 0.0f;
	Normal = 0.0f;

	//�u�����h����{�[���̃C���f�b�N�X�B
	int4 IndexVector = D3DCOLORtoUBYTE4(In.BlendIndices);

	//�u�����h���[�g�B
	float BlendWeightsArray[4] = (float[4])In.BlendWeights;
	int   IndexArray[4] = (int[4])IndexVector;
	float LastWeight = 0.0f;
	
	for (int iBone = 0; iBone < g_numBone - 1; iBone++)
	{
		LastWeight = LastWeight + BlendWeightsArray[iBone];

		Pos += mul(In.Pos, g_mWorldMatrixArray[IndexArray[iBone]]) * BlendWeightsArray[iBone];
		Normal += mul(In.Normal, g_mWorldMatrixArray[IndexArray[iBone]]) * BlendWeightsArray[iBone];
	}
	LastWeight = 1.0f - LastWeight;

	Pos += (mul(In.Pos, g_mWorldMatrixArray[IndexArray[g_numBone - 1]]) * LastWeight);
	Normal += (mul(In.Normal, g_mWorldMatrixArray[IndexArray[g_numBone - 1]]) * LastWeight);

}

void CalcWorldMatrix(VS_INPUT In, out float3 Pos, out float3 Normal)
{
	Pos = 0.0f;
	Normal = 0.0f;
	Pos = mul(In.Pos, g_worldMatrix);
}

VS_OUTPUT VSMain( VS_INPUT In, uniform bool hasSkin )
{
	VS_OUTPUT Out = (VS_OUTPUT)0;
	float3 Pos = 0.0f;
	float3 Normal= 0.0f;
	//CalcWorldMatrixFromSkinMatrix(In, Pos, Normal);
	float3 N = normalize(mul(Normal, (float3x3)g_worldMatrix));
	float4 lig = 0.0f;
	{
		for (int i = 0; i < DIFFUSE_LIGHT_NUM; i++)
		{
			lig.xyz += max(0.0f, dot(N, -g_diffuseLightDirection[i].xyz)) * g_diffuseLightColor[i].xyz;
		}
		lig += g_ambientLight;
	}
	Out.color = lig;
	if (hasSkin){
		CalcWorldMatrixFromSkinMatrix(In, Pos, Normal);
	}
	else{
		CalcWorldMatrix(In, Pos, Normal);
	}
	Out.shadowpos = mul(Pos, g_lvpMatrix);
	Out.Pos = mul(float4(Pos.xyz, 1.0f), g_mViewProj);
	Out.Tex0 = In.Tex0;
	return Out;
}
/*!
 * @brief	�s�N�Z���V�F�[�_�[�B
 */
float4 PSMain( VS_OUTPUT In ) : COLOR
{
	float4 pos = In.shadowpos;
	//float2 uv = float2(0.5f, -0.5f) * pos.xy / pos.w + float2(0.5f, 0.5f);
	float4 color = tex2D(g_diffuseTextureSampler, In.Tex0);
	//color *= tex2D(g_ShadowTextureSampler, uv);
	return color;
}


technique SkinModel
{
    pass p0
    {
        VertexShader = compile vs_3_0 VSMain(true);
		PixelShader = compile ps_3_0 PSMain();
    }
	pass p1
	{
		VertexShader = compile vs_3_0 VSMain(false);
		PixelShader = compile ps_3_0 PSMain();
	}
}