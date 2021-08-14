#include "stdafx.h"
#include "SpriteMgr.h"
#include "Sprite.h"

IMPLEMENT_SINGLETON(CSpriteMgr)

CSpriteMgr::CSpriteMgr()
{
}
CSpriteMgr::~CSpriteMgr()
{
	Release();
}

const LPDIRECT3DTEXTURE9 CSpriteMgr::GetTexInfo(const wstring & wstrObjectKey) const
{

	auto iter_find = m_mapTexture.find(wstrObjectKey);

	if (m_mapTexture.end() == iter_find)
		return nullptr;

	return iter_find->second->GetTex();
}

const LPD3DXSPRITE CSpriteMgr::GetSprite(const wstring & wstrObjectKey) const
{
	auto iter_find = m_mapTexture.find(wstrObjectKey);

	if (m_mapTexture.end() == iter_find)
		return nullptr;

	return iter_find->second->GetSprite();
}

const CSprite * CSpriteMgr::GetSpriteInfo(const wstring & wstrObjectKey)
{
	auto iter_find = m_mapTexture.find(wstrObjectKey);

	if (m_mapTexture.end() == iter_find)
		return nullptr;
	return iter_find->second;
}

HRESULT CSpriteMgr::LoadTexture(LPDIRECT3DDEVICE9 pGrahicDev,const wstring & wstrFilePath, const wstring & wstrObjectKey, float x, float y)
{
	CSprite* pTexture = nullptr;

	auto iter_find = m_mapTexture.find(wstrObjectKey);

	if (m_mapTexture.end() == iter_find)
	{
		pTexture = CSprite::CreateS(wstrFilePath, pGrahicDev ,x ,y);
	}

	NULL_CHECK_RETURN(pTexture, E_FAIL);
	m_mapTexture.insert(make_pair(wstrObjectKey, pTexture));
	
	return S_OK;
}

void CSpriteMgr::Release()
{
	for (auto& MyPair : m_mapTexture)
		SafeDelete(MyPair.second);

	m_mapTexture.clear();
}
