#include"CParticleEmitter.h"
#include"CParticle.h"
#include"..\GraphicsDevice.h"

void CParticleEmitter::Init(CRandom& random, Ccamera& camera, const SParicleEmitParameter& param, const D3DXVECTOR3& emitPosition)
{
	this->random = &random;
	this->camera = &camera;
	this->param = param;
	this->emitPosition = emitPosition;
	timer = 0.0f;

	{
		D3DXLoadMeshFromX(
			"XFile\\itapori.x",
			D3DXMESH_MANAGED,
			graphicsDevice(),
			NULL,
			&m_pMaterials,
			NULL,
			&m_NumMaterials,
			&m_pMesh
			);
		D3DXCreateTextureFromFileA(graphicsDevice(), param.texturePath, &m_pTextures);

		LPD3DXBUFFER  compileErrorBuffer = NULL;
		HRESULT hr = NULL;
		hr = D3DXCreateEffectFromFile(
			graphicsDevice(),
			"shader\\particle.fx",
			NULL,
			NULL,
			D3DXSHADER_DEBUG,
			NULL,
			&m_pEffect,
			&compileErrorBuffer
			);
		if (FAILED(hr)) {
			MessageBox(NULL, (char*)(compileErrorBuffer->GetBufferPointer()), "error", MB_OK);
			abort();
		}
	}
}
void CParticleEmitter::Update()
{
	if (timer >= param.intervalTime) {
		//�p�[�e�B�N���𐶐��B
		CParticle* p = new CParticle;
		p->Init(*random, *camera, param, emitPosition);
		timer = 0.0f;
		particleList.push_back(p);
	}
	timer += 1.0f / 60.0f;
	std::list<CParticle*>::iterator p = particleList.begin();
	while (p != particleList.end()){
		if ((*p)->GetDead()) {
			p = particleList.erase(p);
		}
		else {
			p++;
		}
	}
	p = particleList.begin();
	while (p != particleList.end()){
		(*p++)->Update();
	}
}
/*!
*@brief	�p�[�e�B�N���ɗ͂�������B
*@param[in]	applyForce		���������Ɏg�p���闐�������@�B
*/
void CParticleEmitter::ApplyForce(const D3DXVECTOR3& applyForce)
{
	for (auto p : particleList) {
		p->ApplyForce(applyForce);
	}
}
void CParticleEmitter::Render()
{
	std::list<CParticle*>::iterator p = particleList.begin();
	while (p != particleList.end()){
		(*p++)->Draw(m_NumMaterials, m_pMesh, m_pTextures,m_pEffect);
	}
}

