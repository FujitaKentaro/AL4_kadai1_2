#include "GameScene.h"
#include <cassert>
#include <random>

using namespace DirectX;

//�����������u
std::random_device seed_gen;
std::mt19937_64 engine(seed_gen());
std::uniform_real_distribution<float>dist(-20.0f, 20.0f);


GameScene::GameScene() {}

GameScene::~GameScene() {
	//3D�I�u�W�F�N�g���
	for (int i = 0; i < _countof(enemy); i++) {
		delete enemy[i];
	}
	delete player;

	//3D���f�����
	delete model;
	delete model2;

	//�I�[�f�B�I���
	audio->Finalize();
	delete audio;

}

void GameScene::Initialize(DirectXCommon* dxCommon, Input* input) {
	// nullptr�`�F�b�N
	assert(dxCommon);
	assert(input);

	this->dxCommon = dxCommon;
	this->input = input;



	//�X�v���C�g���ʕ����̏�����
	spriteCommon = new SpriteCommon;
	spriteCommon->Initialize(dxCommon);

	//�X�v���C�g�̏�����
	{
		title->Initialize(spriteCommon);
		position.x = 0.0f;
		position.y = 0.0f;
		title->SetPozition(position);
		title->SetSize(XMFLOAT2{ 1280.0f,720.0f });

		end->Initialize(spriteCommon);
		end->SetPozition(position);
		end->SetSize(XMFLOAT2{ 1280.0f,720.0f });

		clear->Initialize(spriteCommon);
		clear->SetPozition(position);
		clear->SetSize(XMFLOAT2{ 1280.0f,720.0f });
	}
	//�X�v���C�g�̉摜�w��
	{
		spriteCommon->LoadTexture(0, "title.png");
		title->SetTextureIndex(0);
		spriteCommon->LoadTexture(1, "end.png");
		end->SetTextureIndex(1);
		spriteCommon->LoadTexture(2, "info.png");
		clear->SetTextureIndex(2);
	}
	// OBJ���烂�f���f�[�^��ǂݍ���
	{
		model = Model::LoadFromOBJ("ene");
		model2 = Model::LoadFromOBJ("body");
		skyMD = Model::LoadFromOBJ("skydome");
	}
	//3D�I�u�W�F�N�g����
	{
		for (int i = 0; i < _countof(enemy); i++) {
			enemy[i] = Object3d::Create();
		}
		player = Object3d::Create();
		skydome = Object3d::Create();
	}
	// �e�q�ݒ�
	{
		//player->SetParent(ene);
	}
	// �I�u�W�F�N�g�Ƀ��f����R�Â���
	{
		for (int i = 0; i < _countof(enemy); i++) {
			enemy[i]->SetModel(model);
		}

		player->SetModel(model2);
		skydome->SetModel(skyMD);
	}

	Vector3 z;
	z = { dist(engine),0,dist(engine) };
	//3D�I�u�W�F�N�g�̈ʒu���w��
	{
		for (int i = 0; i < _countof(enemy); i++) {
			enemy[i]->SetPosition(z);
		}
		player->SetPosition(Vector3{ 0,0,-25 });
		skydome->SetScale(Vector3{ 1000, 1000, 1000 });
	}


	audio = new Audio();
	audio->Initialize();

	audio->LoadWave("0303PM.wav");
	audio->LoadWave("GOGO.wav");
	audio->LoadWave("kyuin.wav");

}


void GameScene::Update() {
	skydome->Update();

	switch (scene)
	{

	case 0:

		if (input->TriggerKey(DIK_SPACE)) {
			scene = 1;
			ischackFlag = 0;
			player->SetPosition(Vector3{ 0,0,-25 });
			score = 0;
			Vector3 z;

			for (int i = 0; i < _countof(enemy); i++) {
				z = { dist(engine),0,dist(engine) };
				enemy[i]->SetPosition(z);
				enemy[i]->flag = 0;
			}
		}

		break;
	case 1:
		if (input->TriggerKey(DIK_SPACE)) {
			scene = 2;
		}
		break;

	case 3:

		if (input->TriggerKey(DIK_SPACE)) {
			scene = 0;
		}

		break;
	case 2:

		// �I�u�W�F�N�g�ړ�
		if (input->PushKey(DIK_UP) || input->PushKey(DIK_DOWN) || input->PushKey(DIK_RIGHT) || input->PushKey(DIK_LEFT))
		{
			// ���݂̍��W���擾
			Vector3 pos = player->GetPosition();

			// �ړ���̍��W���v�Z
			if (input->PushKey(DIK_UP)) { pos.z += 0.5f; }
			else if (input->PushKey(DIK_DOWN)) { pos.z += -0.5f; }
			if (input->PushKey(DIK_RIGHT)) { pos.x += 0.5f; }
			else if (input->PushKey(DIK_LEFT)) { pos.x += -0.5f; }

			if (pos.x < -30) {
				pos.x = -30;
			}
			if (pos.x > 30) {
				pos.x = 30;
			}
			if (pos.z > 30) {
				pos.z = 30;
			}
			if (pos.z < -30) {
				pos.z = -30;
			}
			// ���W�̕ύX�𔽉f

			player->SetPosition(pos);
		}
		for (int i = 0; i < _countof(enemy); i++) {
			enemy[i]->Update();
		}

		player->Update();



		if (input->TriggerKey(DIK_R)) {
			//�����Đ�
			audio->PlayWave("kyuin.wav");
		}
		ischackFlag = 0;
		//�����蔻��
		Vector3 a = player->GetPosition();
		for (int i = 0; i < _countof(enemy); i++) {
			if (enemy[i]->flag == 0) {
				Vector3 b = enemy[i]->GetPosition();
				float xyz = std::pow(a.x - b.x, 2.0f) + std::pow(a.y - b.y, 2.0f) + std::pow(a.z - b.z, 2.0f);
				float lenR = std::pow(2.0f + 1.0f, 2.0f);
				if (xyz <= lenR) {
					ischackFlag = 1;
					if (ischackFlag == 1) {
						score++;
						enemy[i]->flag = 1;
						//�����Đ�
						audio->PlayWave("GOGO.wav");

					}

				}
			}
		}
		ischackFlag = 0;
		if (score >= 4) {
			scene = 3;
		}

		break;
	}
	//�����Đ�
	if (soundCheckFlag == 0) {
		//�����Đ�
		audio->PlayWave("0303PM.wav");
		soundCheckFlag = 1;
	}

}

void GameScene::Draw() {


	//3D�I�u�W�F�N�g�`��O����
	Object3d::PreDraw(dxCommon->GetCommandList());
	/// <summary>
	/// ������3D�I�u�W�F�N�g�̕`�揈����ǉ��ł���
	/// <summary>

	//3D�I�u�W�F�N�g�̕`��
	for (int i = 0; i < _countof(enemy); i++) {
		if (enemy[i]->flag == 0) {
			enemy[i]->Draw();
		}		
	}

	player->Draw();
	skydome->Draw();


	//3D�I�u�W�F�N�g�`��㏈��
	Object3d::PostDraw();
	switch (scene)
	{
	case 0:
		title->Draw();
		break;

	case 1:
		clear->Draw();
		break;

	case 2:

		break;
	case 3:
		end->Draw();

		break;
	}
}