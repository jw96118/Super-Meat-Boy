#pragma once

// FMOD: ����Ƽ, �𸮾�� ���� ��� �������� �η� ���̴� ���� ���� ����.
// ���忡 ���õ� �������̽��� ����.
#include "fmod.h"
#pragma comment(lib, "fmodex_vc.lib")

#include <io.h>

class CSoundMgr
{
	DECLARE_SINGLETON(CSoundMgr)

public:
	
private:
	CSoundMgr();
	~CSoundMgr();

public:
	void Initialize();
	void UpdateSound();
	void PlaySound(const wstring& wstrSoundKey, SOUNDMGR::CHANNEL_ID eID);
	void PlayBGM(const wstring& wstrSoundKey);
	void StopSound(SOUNDMGR::CHANNEL_ID eID);
	void StopAll();
	void SetVolume(SOUNDMGR::CHANNEL_ID eID, float fVol); // ������ ������ �ּ� 0.f ~ �ִ� 1.f����.
	void Release();

private:
	void LoadSoundFile();

private:
	// FMOD_SOUND: ���� ���Ͽ� ���� ������ ���� ����ü.
	map<wstring, FMOD_SOUND*>	m_MapSound; 

	// FMOD_CHANNEL: ���带 ����ϰ� �����ϴ� ����. ex) ���� ���� ��.
	FMOD_CHANNEL*	m_pChannelArr[SOUNDMGR::MAX_CHANNEL];

	// FMOD_SYSTEM: FMOD_SOUND�� FMOD_CHANNEL�� �Ѱ� �����ϴ� ��ü.
	FMOD_SYSTEM*	m_pSystem;
};

