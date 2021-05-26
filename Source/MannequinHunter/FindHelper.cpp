// Fill out your copyright notice in the Description page of Project Settings.

#include "FindHelper.h"
#include "Kismet/KismetStringLibrary.h"

FindHelper::FindHelper()
{
}

FindHelper::~FindHelper()
{
}

AssetsPathData FindHelper::AssetsPathSplit_Object(FString string)
{
	AssetsPathData ret;
	// 에셋을 형태
	FString type;
	// 자르고난 나머지
	FString remainder;
	string.Split(L"'", &type, &remainder);
	ret.type = L"U" + type;

	// 버려지는 문자열
	FString abandon;
	// 에셋의 위치
	FString path;
	remainder.Split(L".", &path, &abandon);
	ret.path = path;

	return ret;
}

AssetsPathData FindHelper::AssetsPathSplit_Class(FString string)
{
	AssetsPathData ret;
	// 에셋을 형태
	FString type;
	// 자르고난 나머지
	FString remainder;
	string.Split(L"'", &type, &remainder);
	ret.type = L"U" + type;

	// 버려지는 문자열
	FString abandon;
	// 에셋의 위치
	FString path;
	remainder.Split(L"'", &path, &abandon);
	ret.path = path + L"_C";

	return ret;
}
