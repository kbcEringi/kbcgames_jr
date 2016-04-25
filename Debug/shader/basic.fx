/*!
 *@brief	簡単なテクスチャ貼り付けシェーダー。
 */


float4x4 g_worldMatrix;			//ワールド行列。
float4x4 g_viewMatrix;			//ビュー行列。
float4x4 g_projectionMatrix;	//プロジェクション行列。

float3 vLightDir;

float4 I_a = { 0.3f, 0.3f, 0.3f, 0.0f };
float4 I_b = { 0.7f, 0.7f, 0.7f, 0.0f };

float4 K_a = { 1.0f, 1.0f, 1.0f, 1.0f };
float4 K_b = { 1.0f, 1.0f, 1.0f, 1.0f };


texture g_diffuseTexture;		//ディフューズテクスチャ。
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

};

/*!
 *@brief	頂点シェーダー。
 */
VS_OUTPUT VSMain(VS_INPUT In)
{
	VS_OUTPUT Out = (VS_OUTPUT)0;

	float3 L = -vLightDir;
		float3 N = normalize(mul(In.normal, (float3x3)g_worldMatrix));
		Out.color = I_a * K_a + I_b * K_b * max(0, dot(N, L));

	//座標変換
	float4 pos;
	pos = mul(In.pos, g_worldMatrix);		//モデルのローカル空間からワールド空間に変換。
	pos = mul(pos, g_viewMatrix);			//ワールド空間からビュー空間に変換。
	pos = mul(pos, g_projectionMatrix);	//ビュー空間から射影空間に変換。
	Out.pos = pos;
	Out.uv = In.uv;
	return Out;
}
/*!
 *@brief	ピクセルシェーダー。
 */
float4 PSMain( VS_OUTPUT In ) : COLOR
{
	return tex2D(g_diffuseTextureSampler, In.uv)*In.color;
}

technique SkinModel
{
	pass p0
	{
		VertexShader 	= compile vs_2_0 VSMain();
		PixelShader 	= compile ps_2_0 PSMain();
	}
}