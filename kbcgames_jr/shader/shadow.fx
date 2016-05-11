/*
 *	影をテクスチャに黒く焼き付けるためのシェーダー
 */

float4x4 g_worldMatrix;			//ワールド行列。
float4x4 g_viewMatrix : register(c0);			//ビュー行列。
float4x4 g_projectionMatrix;	//プロジェクション行列。

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
	float4 pos = mul(In.pos, g_worldMatrix);		//モデルのローカル空間からワールド空間に変換。
		pos = mul(pos, g_viewMatrix);			//ワールド空間からビュー空間に変換。
	//pos = mul(pos, g_projectionMatrix);	//ビュー空間から射影空間に変換。
	Out.pos = pos;
	Out.uv = In.uv;
	Out.color = In.color;
	return Out;
}
/*!
*@brief	ピクセルシェーダー。
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