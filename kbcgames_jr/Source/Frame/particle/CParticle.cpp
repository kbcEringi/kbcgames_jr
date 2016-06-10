#include"CParticle.h"

#include"..\GraphicsDevice.h"
#include"CParticleEmitter.h"

CParticle::CParticle()
{
	isDead = false;
	applyForce = D3DXVECTOR3(0, 0, 0);
	timer = 0;
}

CParticle::~CParticle()
{

}

void CParticle::Init(CRandom& random, Ccamera& camera, const SParicleEmitParameter& param, const D3DXVECTOR3 emitPosition)
{
	scale = D3DXVECTOR3(param.w, param.h, 1);
	D3DXMatrixScaling(&matscale, scale.x, scale.y, scale.z);
	this->camera = &camera;
	this->random = &random;
	life = param.life;
	velocity = param.initVelocity;
	//初速度に乱数を加える。
	velocity.x += (((float)random.GetRandDouble() - 0.5f) * 2.0f) * param.initVelocityVelocityRandomMargin.x;
	velocity.y += (((float)random.GetRandDouble() - 0.5f) * 2.0f) * param.initVelocityVelocityRandomMargin.y;
	velocity.z += (((float)random.GetRandDouble() - 0.5f) * 2.0f) * param.initVelocityVelocityRandomMargin.z;
	position = emitPosition;
	position.x += (((float)random.GetRandDouble() - 0.5f) * 2.0f) * param.initPositionRandomMargin.x;
	position.y += (((float)random.GetRandDouble() - 0.5f) * 2.0f) * param.initPositionRandomMargin.y;
	position.z += (((float)random.GetRandDouble() - 0.5f) * 2.0f) * param.initPositionRandomMargin.z;
	addVelocityRandomMargih = param.addVelocityRandomMargih;
	gravity = param.gravity;
	isFade = param.isFade;
	state = eStateRun;
	initAlpha = param.initAlpha;
	alpha = initAlpha;
	fadeTIme = param.fadeTime;
	isBillboard = param.isBillboard;
	brightness = param.brightness;
	alphaBlendMode = param.alphaBlendMode;
	rotateZ = PI * 2.0f * (float)random.GetRandDouble();
	
}
void CParticle::Update()
{
	D3DXMatrixIdentity(&m_matWorld);

	float deltaTime = 1.0f / 60.0f;
	D3DXVECTOR3 addGrafity = gravity;
	addGrafity *= deltaTime;
	velocity += addGrafity;
	D3DXVECTOR3 force = applyForce;
	force.x += (((float)random->GetRandDouble() - 0.5f) * 2.0f) * addVelocityRandomMargih.x;
	force.y += (((float)random->GetRandDouble() - 0.5f) * 2.0f) * addVelocityRandomMargih.y;
	force.z += (((float)random->GetRandDouble() - 0.5f) * 2.0f) * addVelocityRandomMargih.z;
	force *= deltaTime;
	velocity += force;
	D3DXVECTOR3 addPos = velocity;
	addPos *= deltaTime;
	applyForce = D3DXVECTOR3(0,0,0);

	position += addPos;
	D3DXMATRIX mTrans;
	D3DXMatrixIdentity(&mTrans);
	mTrans.m[0][0] = 1.0f;
	mTrans.m[1][1] = 1.0f;
	mTrans.m[2][2] = 1.0f;
	mTrans.m[3][3] = 1.0f;

	mTrans.m[3][0] = position.x;
	mTrans.m[3][1] = position.y;
	mTrans.m[3][2] = position.z;

	rotateZ += 0.005;

	if (isBillboard) {
		//ビルボード
		D3DXMATRIX rot = camera->GetRotationMatrix();
		D3DXQUATERNION qRot;
		float s;
		s = sin(rotateZ);
		qRot.x = rot.m[2][0] * s;
		qRot.y = rot.m[2][1] * s;
		qRot.z = rot.m[2][2] * s;
		qRot.w = cos(rotateZ);

		D3DXMATRIX rota;
		D3DXMatrixRotationQuaternion(&rota, &qRot);
		D3DXMatrixMultiply(&rot, &rot, &rota);

		/*D3DXMatrixMultiply(&m_matWorld, &m_matWorld, &matscale);
		D3DXMatrixMultiply(&m_matWorld, &m_matWorld, &rot);
		D3DXMatrixMultiply(&m_matWorld, &m_matWorld, &mTrans);*/

		m_matWorld *= matscale * rot * mTrans;
	}
	else {
		mWorld = matscale *  mTrans;
	}
	timer += deltaTime;
	switch (state) {
	case eStateRun:
		if (timer >= life) {
			if (isFade) {
				state = eStateFadeOut;
				timer = 0.0f;
			}
			else {
				state = eStateDead;
			}
		}
		break;
	case eStateFadeOut: {
		float t = timer / fadeTIme;
		timer += deltaTime;
		alpha = initAlpha + (-initAlpha)*t;
		if (alpha <= 0.0f) {
			alpha = 0.0f;
			state = eStateDead;	//死亡。
		}
	}break;
	case eStateDead:
		isDead = true;
		break;
	}
}

void CParticle::Draw(DWORD m_NumMaterials,
	ID3DXMesh* m_pMesh,
	IDirect3DTexture9* m_pTextures,
	ID3DXEffect* m_pEffect)
{

	D3DXMATRIX m;
	D3DXMatrixIdentity(&m);
	D3DXMatrixMultiply(&m, &m_matWorld, &camera->GetViewMatrix());
	D3DXMatrixMultiply(&m, &m, &camera->GetProjectionMatrix());
	(*graphicsDevice()).SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	switch (alphaBlendMode) {
	case 0:
		(*graphicsDevice()).SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		(*graphicsDevice()).SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		m_pEffect->SetTechnique("ColorTexPrimTrans");
		break;
	case 1:
		(*graphicsDevice()).SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
		(*graphicsDevice()).SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		m_pEffect->SetTechnique("ColorTexPrimAdd");
		break;
	}

	m_pEffect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
	m_pEffect->BeginPass(0);
	(*graphicsDevice()).SetRenderState(D3DRS_ZENABLE, FALSE);

	m_pEffect->SetValue("g_mWVP", &m, sizeof(D3DXMATRIX));
	m_pEffect->SetValue("g_alpha", &alpha, sizeof(alpha));
	m_pEffect->SetValue("g_brightness", &brightness, sizeof(brightness));
	m_pEffect->SetTexture("g_texture", m_pTextures);
	m_pEffect->CommitChanges();
	for (int i = 0; i < m_NumMaterials; i++)
	{
		m_pMesh->DrawSubset(i);
	}

	m_pEffect->EndPass();
	m_pEffect->End();
	(*graphicsDevice()).SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	(*graphicsDevice()).SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	(*graphicsDevice()).SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
	(*graphicsDevice()).SetRenderState(D3DRS_ZENABLE, TRUE);
}