#pragma once
#include "..\Frame\Input.h"
#include"..\Frame\DXCommon.h"
#include"..\Frame\C3DObject.h"
#include "..\Frame\Rigidbody.h"
#include"..\Frame\CRandom.h"
#include"..\Frame\Ccamera.h"
#include "..\Frame\particle\CParticleEmitter.h"

class CAudio;

class CAlwaysWind : public C3DObject
{
public:
	CAlwaysWind();
	~CAlwaysWind();
	void Initialize()override;
	void Update();
	void Draw(D3DXMATRIX, D3DXMATRIX);
	D3DXVECTOR3 GetPosition()
	{
		return m_data.position;
	}
	void SetObjectData(ObjectData obj){
		C3DObject::SetObjectData(obj);
		m_aabbMax += obj.position;
		m_aabbMin += obj.position;
	}

private:
	CRandom random;
	D3DXMATRIX m_rotationMatrix;
	D3DXVECTOR3 m_force;
	D3DXVECTOR3 m_aabbMin;
	D3DXVECTOR3 m_aabbMax;
	float SpeedPower;				//‰Á‘¬‚ð‰Á‚¦‚é‘¬“x
	CParticleEmitter emi;

	CAudio* m_pAudio;
	bool AudioFlag;
};

