/*!
 * @brief	スキンモデルシェーダー。(4ボーンスキニング)
 */

//スキン行列。
#define MAX_MATRICES  26
float4x3    g_mWorldMatrixArray[MAX_MATRICES] : WORLDMATRIXARRAY;//アニメーション用
float4x4    g_mViewProj : VIEWPROJECTION;
float		g_numBone;			//骨の数。
bool shadowflg;

float4x4 g_mRotation;

bool hureneruflg;
float4x4 g_viewMatrixRotInv;	////カメラの回転行列の逆行列。

float4x4 g_worldMatrix;
float4x4 g_lvpMatrix;	//プロジェクション行列。
float3 vEyePos;//カメラの位置

#define DIFFUSE_LIGHT_NUM 6
float4 g_diffuseLightDirection[DIFFUSE_LIGHT_NUM];
float4 g_diffuseLightColor[DIFFUSE_LIGHT_NUM];
float4 g_ambientLight;

float2		g_farNear;	//遠平面と近平面。xに遠平面、yに近平面。


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

texture g_normalMap;		//法線マップ
sampler g_normalMapSampler =
sampler_state
{
	Texture = <g_normalMap>;
	MipFilter = NONE;
	MinFilter = NONE;
	MagFilter = NONE;
	AddressU = Wrap;
	AddressV = Wrap;
};
bool Normalflg;

bool isLuminance;
float g_luminance;

/*!
 * @brief	入力頂点
 */
struct VS_INPUT
{
    float4  Pos             : POSITION;
    float4  BlendWeights    : BLENDWEIGHT;
    float4  BlendIndices    : BLENDINDICES;
    float3  Normal          : NORMAL;
    float3  uv            : TEXCOORD0;
	float3	tangentNormal	: TANGENT;		//接ベクトル

};

/*!
 * @brief	出力頂点。
 */
struct VS_OUTPUT
{
	float4  Pos     : POSITION;
    float2  uv    : TEXCOORD0;
	float4  specColor : TEXCOORD1;
	float4 shadowpos : TEXCOORD2;
	float3	normal	: TEXCOORD3;
	float3	tangentNormal	: TEXCOORD4;		//接ベクトル

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
	Normal = mul(In.Normal, g_mRotation);
}

float4 CalcLight(float3 normal)
{
	float4 lig = 0.0f;
	{
		for (int i = 0; i < DIFFUSE_LIGHT_NUM; i++)
		{
			lig.xyz += max(0.0f, dot(normal.xyz, -g_diffuseLightDirection[i].xyz)) * g_diffuseLightColor[i].xyz;
		}
		//lig += g_ambientLight;
	}
	return lig;
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

	Out.shadowpos = mul(float4(Pos.xyz, 1.0f), g_lvpMatrix);
	Out.Pos = mul(float4(Pos.xyz, 1.0f), g_mViewProj);
	Out.uv = In.uv;
	Out.normal = Normal;
	Out.tangentNormal = mul(In.tangentNormal, g_mRotation);
	return Out;
}
/*!
* @brief	アルファに埋め込む輝度を計算。
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
/*!
 * @brief	ピクセルシェーダー。
 */
float4 PSMain(VS_OUTPUT In) : COLOR
{
	float3 normal = In.normal;
	if (Normalflg)
	{
		normal = tex2D(g_normalMapSampler, In.uv);
		float4x4 tangentSpaceMatrix;
		float3 biNormal = normalize(cross(In.tangentNormal, In.normal));
		tangentSpaceMatrix[0] = float4(In.tangentNormal, 0.0f);
		tangentSpaceMatrix[1] = float4(biNormal, 0.0f);
		tangentSpaceMatrix[2] = float4(In.normal, 0.0f);
		tangentSpaceMatrix[3] = float4(0.0f, 0.0f, 0.0f, 1.0f);
		normal = (normal * 2.0f) - 1.0f;
		normal = tangentSpaceMatrix[0] * normal.x + tangentSpaceMatrix[1] * normal.y + tangentSpaceMatrix[2] * normal.z;
	}

	float4 lig = CalcLight(normal);
	float4 diff = tex2D(g_diffuseTextureSampler, In.uv);



	if (shadowflg)
	{
		float4 pos = In.shadowpos;
		float2 uv = float2(0.5f, -0.5f) * pos.xy / pos.w + float2(0.5f, 0.5f);
		float shadow_val = 1.0f;
		if (uv.x <= 1.0f && uv.y <= 1.0f && uv.x >= 0.0f && uv.y >= 0.0f ){
			if (dot(In.normal, float3(0, 1, 0)) >= 0.4f)
			{
				shadow_val = tex2D(g_ShadowTextureSampler, uv).r;
			}
		}
		float depth = (pos.z - g_farNear.y) / (g_farNear.x - g_farNear.y);
		if (depth > shadow_val){
			//影になっている。
			lig = 0.0f;
		}
	}
	lig += g_ambientLight;
	float4 color = diff*lig;



	float t = 0.0f;
	if (hureneruflg)
	{
		float3 normalInCamera = mul(In.normal, g_viewMatrixRotInv);
		t = 1.0f - abs(dot(normalInCamera, float3(0.0f, 0.0f, 1.0f)));
		t = pow(t, 1.5f);
	}
	color.xyz += t;
	//アルファに輝度を埋め込む
	if (isLuminance){
		color.a *= CalcLuminance(color.xyz);
	}
	
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
