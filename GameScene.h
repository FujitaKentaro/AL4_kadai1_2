#pragma once

#include "DirectXCommon.h"
#include <DirectXMath.h>
#include "Input.h"
#include "Object3d.h"
#include "SpriteCommon.h"
#include "Sprite.h"
#include "Model.h"
#include "Audio.h"
#include <string>

#include "Matrix4.h"


/// <summary>
/// �Q�[���V�[��
/// </summary>
class GameScene
{
private: // �G�C���A�X
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

private: // �ÓI�����o�ϐ�
	static const int debugTextTexNumber = 0;

public: // �����o�֐�

	/// <summary>
	/// �R���X�g�N���^
	/// </summary>
	GameScene();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~GameScene();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize(DirectXCommon* dxCommon, Input* input);

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

private: // �����o�ϐ�
	DirectXCommon* dxCommon = nullptr;
	Input* input = nullptr;
	SpriteCommon* spriteCommon = nullptr;
	Audio* audio = nullptr;
	

	/// <summary>
	/// �Q�[���V�[���p
	/// </summary>
	Sprite* title = new Sprite();
	XMFLOAT2 position = title->GetPosition();

	Sprite* end = new Sprite();
	XMFLOAT2 position1 = end->GetPosition();

	Sprite* clear = new Sprite();
	XMFLOAT2 position2 = clear->GetPosition();

	int ischackFlag = 0;

	Object3d* enemy[4];
	Object3d* player = nullptr;
	Object3d* skydome = nullptr;
	Model* model = nullptr;
	Model* model2 = nullptr;
	Model* skyMD = nullptr;


	int soundCheckFlag = 0;

	GameScene* gamescene = nullptr;
	

	int scene=0;
	int score =0;

};

