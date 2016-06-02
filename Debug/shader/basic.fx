/*!
 *@brief	簡単なテクスチャ貼り付けシェーダー。
 */


float4x4 g_worldMatrix;			//ワールド行列。
float4x4 g_viewMatrix : register(c0);			//ビュー行列。
float4x4 g_projectionMatrix;	//プロジェクション行列。
float4x4 g_lvpMatrix;	//プロジェクション行列。

#define DIFFUSE_LIGHT_NUM 6
float4 g_diffuseLightDirection[DIFFUSE_LIGHT_NUM];
float4 g_diffuseLightColor[DIFFUSE_LIGHT_NUM];
float4 g_ambientLight;

float3 vEyePos;//カメラの位置

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

texture g_ShadowTexture;		//ディフューズテクスチャ。
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
*@brief	頂点シェーダー。
*/
//通常
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
	//座標変換
	float4 pos;
	pos = mul(In.pos, g_worldMatrix);		//モデルのローカル空間からワールド空間に変換。
	Out.shadowpos = mul(pos, g_lvpMatrix);
	pos = mul(pos, g_viewMatrix);			//ワールド空間からビュー空間に変換。
	pos = mul(pos, g_projectionMatrix);	//ビュー空間から射影空間に変換。
	Out.pos = pos;
	Out.uv = In.uv;
	
	return Out;
}
/*!
	*@brief	ピクセルシェーダー。
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

	float3 eye = normalize(vEyePos.xyz - In.pos);//オブジェクトからのカメラの目線
		float3 N = In.normal.xyz;
		float3 R = -eye + 2.0f*dot(N, eye)*N;//反射ベクトル

		float4 lig = 0.0f;
		float4 spec = 0.0f;
	for (int i = 0; i < DIFFUSE_LIGHT_NUM; i++)
{
		lig.xyz += max(0.0, dot(N, -g_diffuseLightDirection[i].xyz)) * g_diffuseLightColor[i].xyz;
		lig.xyz += pow(max(0.0f, dot(-g_diffuseLightDirection[i].xyz, R)), 10) * g_diffuseLightColor[i].w;	//10=鏡面反射指数
	}
	lig += g_ambientLight;//環境光プラス
	Out.color = lig;

	//座標変換
	float4 pos;
	pos = mul(In.pos, g_worldMatrix);		//モデルのローカル空間からワールド空間に変換。
	pos = mul(pos, g_viewMatrix);			//ワールド空間からビュー空間に変換。
	pos = mul(pos, g_projectionMatrix);	//ビュー空間から射影空間に変換。
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