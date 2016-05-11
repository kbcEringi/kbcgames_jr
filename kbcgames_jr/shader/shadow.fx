/*
 *	�e���e�N�X�`���ɍ����Ă��t���邽�߂̃V�F�[�_�[
 */

float4x4 g_worldMatrix;			//���[���h�s��B
float4x4 g_viewMatrix : register(c0);			//�r���[�s��B
float4x4 g_projectionMatrix;	//�v���W�F�N�V�����s��B

struct VS_INPUT{
	float4	pos		: POSITION;
	float4	color	: COLOR0;
	float2	uv		: TEXCOORD0;
};

struct VS_OUTPUT{
	float4	pos		: POSITION;
	float4	color	: COLOR0;
	float2	uv		: TEXCOORD0;
};

VS_OUTPUT VSShadow(VS_INPUT In)
{
	VS_OUTPUT Out = (VS_OUTPUT)0;
	float4 pos = mul(In.pos, g_worldMatrix);		//���f���̃��[�J����Ԃ��烏�[���h��Ԃɕϊ��B
		pos = mul(pos, g_viewMatrix);			//���[���h��Ԃ���r���[��Ԃɕϊ��B
	//pos = mul(pos, g_projectionMatrix);	//�r���[��Ԃ���ˉe��Ԃɕϊ��B
	Out.pos = pos;
	Out.uv = In.uv;
	Out.color = In.color;
	return Out;
}
/*!
*@brief	�s�N�Z���V�F�[�_�[�B
*/
float4 PSShadow(VS_OUTPUT In) : COLOR
{
	return float4(0.5f, 0.5f, 0.5f, 1.0f);
}

technique SkinModel
{
	pass p0
	{
		VertexShader = compile vs_2_0 VSShadow();
		PixelShader = compile ps_2_0 PSShadow();
	}
};