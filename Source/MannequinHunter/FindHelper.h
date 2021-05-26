// Fill out your copyright notice in the Description page of Project Settings.
// 언리얼 엔진4 에셋을 찾는것을 도와주는 클레스


#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMesh.h"
#include "UObject/ConstructorHelpers.h"

struct AssetsPathData
{
	FString type;
	FString path;
};

#pragma region FindObject

// static ConstructorHelpers::FObjectFinder<type> name(path);
#define ObjectFinder(name,type,path) \
	static ConstructorHelpers::FObjectFinder<##type> ##name(path);
// static ConstructorHelpers::FObjectFinder<type> name(TEXT(path));
#define ObjectFinderT(name,type,path) \
	ObjectFinder(name,type,TEXT(path));
// name 변수명
// type Asset ClassType
// _path FString 문자열
#define FINDOBJECT(name,type,_path)\
	AssetsPathData data_##name = FindHelper::AssetsPathSplit_Object(_path);\
	wchar_t* path_##name = &data_##name.path[0];\
	ObjectFinder(name,type,path_##name)\
// _type Asset ClassType
//	Object_ptr 받을 변수의 주소값
// __path FString 문자열
// 못찾을시 nullptr ;
#define FindObject(_type ,Object_ptr, __path) \
{\
	FINDOBJECT(ASSETS, _type, __path)\
	if (ASSETS.Succeeded())\
		Object_ptr = ASSETS.Object;\
	else \
		Object_ptr = nullptr;\
}

#pragma endregion


#pragma region FindClass

// static ConstructorHelpers::FObjectFinder<type> name(path);
#define ClassFinder(name,type,path) \
	static ConstructorHelpers::FClassFinder<##type> ##name(path);
// static ConstructorHelpers::FObjectFinder<type> name(TEXT(path));
#define ClassFinderT(name,type,path) \
	ClassFinder(name,type,TEXT(path));
// name 변수명
// type Asset ClassType
// _path FString 문자열
#define FINDCLASS(name,type,_path)\
	AssetsPathData data_##name = FindHelper::AssetsPathSplit_Class(_path);\
	wchar_t* path_##name = &data_##name.path[0];\
	ClassFinder(name,type,path_##name)\
// _type Asset ClassType
//	Object_ptr 받을 변수의 주소값
// __path FString 문자열
// 못찾을시 nullptr ;
#define FindClass(_type ,Object_ptr, __path) \
{\
	FINDCLASS(ASSETS, _type, __path)\
	if (ASSETS.Succeeded())\
		Object_ptr = ASSETS.Class;\
	else \
		Object_ptr = nullptr;\
}

#pragma endregion



class MANNEQUINHUNTER_API FindHelper
{
public:
	FindHelper();
	~FindHelper();

	static AssetsPathData AssetsPathSplit_Object(FString string);

	static AssetsPathData AssetsPathSplit_Class(FString string);


	template<typename T>
	static void AssetsFindObejct(T** object_ptr, FString path)
	{
		FindObject(T, *object_ptr, path);
	}

	template<typename UserClass , typename T >
	static void AssetsFindClass(T* object_ptr, FString path)
	{
		FindClass(UserClass, *object_ptr, path);
	}
};
