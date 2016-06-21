/*
 *	�e���e�N�X�`���ɍ����Ă��t���邽�߂̃V�F�[�_�[
 */

float4x4 g_worldMatrix;			//���[���h�s��B
float4x4 g_viewprojMatrix;			//�r���[�s��B

#define MAX_MATRICES  26
float4x3    g_mWorldMatrixArray[MAX_MATRICES] : WORLDMATRIXARRAY;//�A�j���[�V�����p
float		g_numBone;			//���̐��B

float2		g_farNear;	//�����ʂƋߕ��ʁBx�ɉ����ʁAy�ɋߕ��ʁB

struct VS_INPUT{
	float4	pos		: POSITION;
	float4  BlendWeights    : BLENDWEIGHT;
	float4  BlendIndices    : BLENDINDICES;
};

struct VS_OUTPUT{
	float4	pos		: POSITION;
	float4 depth	: TEXCOORD;
};

void CalcWorldMatrixFromSkinMatrix(VS_INPUT In, out float3 Pos)
{
	Pos = 0.0f;
	//�u�����h����{�[���̃C���f�b�N�X�B
	int4 IndexVector = D3DCOLORtoUBYTE4(In.BlendIndices);

		//�u�����h���[�g�B
		float BlendWeightsArray[4] = (float[4])In.BlendWeights;
	int   IndexArray[4] = (int[4])IndexVector;
	float LastWeight = 0.0f;

	for (int iBone = 0; iBone < g_numBone - 1; iBone++)
	{
		LastWeight = LastWeight + BlendWeightsArray[iBone];

		Pos += mul(In.pos, g_mWorldMatrixArray[IndexArray[iBone]]) * BlendWeightsArray[iBone];
	}
	LastWeight = 1.0f - LastWeight;

	Pos += (mul(In.pos, g_mWorldMatrixArray[IndexArray[g_numBone - 1]]) * LastWeight);

}

void CalcWorldMatrix(VS_INPUT In, out float3 Pos)
{
	Pos = 0.0f;
	Pos = mul(In.pos, g_worldMatrix);
}

VS_OUTPUT VSShadow(VS_INPUT In, uniform bool hasSkin)
{
	VS_OUTPUT Out = (VS_OUTPUT)0;
	float3 Pos = 0.0f;
	if (hasSkin){
		CalcWorldMatrixFromSkinMatrix(In, Pos);
	}
	else{
		CalcWorldMatrix(In, Pos);
	}
	Out.pos = mul(float4(Pos.xyz, 1.0f), g_viewprojMatrix);			//���[���h��Ԃ���r���[��Ԃɕϊ��B
	Out.depth = Out.pos;
	return Out;
}
/*!
*@brief	�s�N�Z���V�F�[�_�[�B
*/
float4 PSShadow(VS_OUTPUT In) : COLOR
{
	float z = (In.depth.z - g_farNear.y) / (g_farNear.x - g_farNear.y);
	return float4(z, z, z, z);
}

technique SkinModel
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSShadow(true);
		PixelShader = compile ps_3_0 PSShadow();
	}
	pass p1
	{
		VertexShader = compile vs_3_0 VSShadow(false);
		PixelShader = compile ps_3_0 PSShadow();
	}
};