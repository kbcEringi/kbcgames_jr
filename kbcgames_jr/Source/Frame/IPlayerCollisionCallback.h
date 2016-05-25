#pragma once

class IPlayerCollisionCallback{
private:
	bool isHitGround;
	bool isHitWall;
public:
	virtual bool OnHitGroundTrigger(const btCollisionObject*){ return false; }
	virtual void OnHitGroundLeave(const btCollisionObject*){}
	virtual void OnHitGround(const btCollisionObject*){}
	virtual void OnHitWall(const btCollisionObject*){}
	void SetHitGround(bool hit)
	{
		isHitGround = hit;
	}
	void SetHitWall(bool hit)
	{
		isHitWall = hit;
	}
	bool IsHitGround()
	{
		return isHitGround;
	}
	bool IsHitWall()
	{
		return isHitWall;
	}
};