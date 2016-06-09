/*!
 * @brief	スキンモデルシェーダー。(4ボーンスキニング)
 */

//スキン行列。
#define MAX_MATRICES  26
float4x3    g_mWorldMatrixArray[MAX_MATRICES] : WORLDMATRIXARRAY;//アニメーション用
float4x4    g_mViewProj : VIEWPROJECTION;
float		g_numBone;			//骨の数。
bool shadowflg;

bool hureneruflg;
float4x4 g_viewMatrixRotInv;	////カメラの回転行列の逆行列。

float4x4 g_worldMatrix;
float4x4 g_lvpMatrix;	//プロジェクション行列。
float3 vEyePos;//カメラの位置

#define DIFFUSE_LIGHT_NUM 6
float4 g_diffuseLightDirection[DIFFUSE_LIGHT_NUM];
float4 g_diffuseLightColor[DIFFUSE_LIGHT_NUM];
float4 g_ambientLight;

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
texture g_ShadowTexture;		//シャドウテクスチャ。
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
 * @brief	入力頂点
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
 * @brief	出力頂点。
 */
struct VS_OUTPUT
{
	float4  Pos     : POSITION;
	float4	color	: COLOR0;
    float2  Tex0    : TEXCOORD0;
	float4  specColor : TEXCOORD1;
	float4 shadowpos : TEXCOORD2;
	float3	normal	: TEXCOORD3;
};

void CalcWorldMatrixFromSkinMatrix(VS_INPUT In, out float3 Pos, out float3 Normal)
{
	Pos = 0.0f;
	Normal = 0.0f;

	//ブレンドするボーンのインデックス。
	int4 IndexVector = D3DCOLORtoUBYTE4(In.BlendIndices);

	//ブレンドレート。
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
	Normal = normalize(Normal);
}

void CalcWorldMatrix(VS_INPUT In, out float3 Pos, out float3 Normal)
{
	Pos = 0.0f;
	Normal = 0.0f;
	Pos = mul(In.Pos, g_worldMatrix);
	Normal = mul(In.Normal, g_worldMatrix);
}

VS_OUTPUT VSMain( VS_INPUT In, uniform bool hasSkin )
{
	VS_OUTPUT Out = (VS_OUTPUT)0;
	float3 Pos = 0.0f;
	float3 Normal= 0.0f;
	if (hasSkin){
		CalcWorldMatrixFromSkinMatrix(In, Pos, Normal);
	}
	else{
		CalcWorldMatrix(In, Pos, Normal);
	}

	float4 color;
	float4 lig = 0.0f;
	{
		for (int i = 0; i < DIFFUSE_LIGHT_NUM; i++)
		{
			lig.xyz += max(0.0f, dot(Normal.xyz, -g_diffuseLightDirection[i].xyz)) * g_diffuseLightColor[i].xyz;
		}
		lig += g_ambientLight;
	}
	color = lig;

	Out.color = color;
	Out.shadowpos = mul(float4(Pos, 1.0f), g_lvpMatrix);
	Out.Pos = mul(float4(Pos.xyz, 1.0f), g_mViewProj);
	Out.Tex0 = In.Tex0;
	Out.normal = Normal;
	return Out;
}
/*!
 * @brief	ピクセルシェーダー。
 */
float4 PSMain( VS_OUTPUT In ) : COLOR
{
	float4 pos = In.shadowpos;
	float2 uv = float2(0.5f, -0.5f) * pos.xy / pos.w + float2(0.5f, 0.5f);
	
	float4 color;
	color = tex2D(g_diffuseTextureSampler, In.Tex0);
	if (shadowflg)
	{
		if (uv.x < 1.0f && uv.y < 1.0f){
			if (dot(In.normal, float3(0, 1, 0)) >= 0.2f)
			{
				color *= tex2D(g_ShadowTextureSampler, uv);
			}
		}
	}
	float t = 0.0f;;
	if (hureneruflg)
	{
		float3 normalInCamera = mul(In.normal, g_viewMatrixRotInv);
		t = 1.0f - abs(dot(normalInCamera, float3(0.0f, 0.0f, 1.0f)));
		t = pow(t, 1.5f);
	}
	color *= In.color;
	color.xyz += t;
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
