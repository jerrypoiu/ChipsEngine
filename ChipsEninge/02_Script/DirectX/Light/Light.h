#ifndef DIRECTX_LIGHT_LIGHT_H
#define DIRECTX_LIGHT_LIGHT_H

struct DirectionalLight
{
	DirectionalLight() { ZeroMemory(this, sizeof(this)); }

	XMFLOAT4 Ambient;
	XMFLOAT4 Diffuse;
	XMFLOAT4 Specular;
	XMFLOAT3 Direction;
	float Pad; 
};

struct PointLight
{
	PointLight() { ZeroMemory(this, sizeof(this)); }

	XMFLOAT4 Ambient;
	XMFLOAT4 Diffuse;
	XMFLOAT4 Specular;

	XMFLOAT3 Position;
	float Range;

	XMFLOAT3 Att;
	float Pad;
};

struct SpotLight
{
	SpotLight() { ZeroMemory(this, sizeof(this)); }

	XMFLOAT4 Ambient;
	XMFLOAT4 Diffuse;
	XMFLOAT4 Specular;

	XMFLOAT3 Position;
	float Range;

	XMFLOAT3 Direction;
	float Spot;

	XMFLOAT3 Att;
	float Pad; 
};

struct Material
{
	Material() { ZeroMemory(this, sizeof(this)); }

	XMFLOAT4 Ambient;
	XMFLOAT4 Diffuse;
	XMFLOAT4 Specular;
	XMFLOAT4 Reflect;
};

#endif //DIRECTX_LIGHT_LIGHT_H