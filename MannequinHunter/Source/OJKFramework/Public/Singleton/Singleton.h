// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#pragma region Define Singleton

//Single tone with no constructor destructor
#define DECLARE_SINGLETON(ClassName) \
\
public:\
static ClassName* GetInstance() \
{ \
	static ClassName* instance = nullptr; \
	if (instance == nullptr) \
	{ \
		instance = new ClassName(); \
		atexit(Destroy); \
	} \
	return instance; \
} \
\
private: \
\
static void Destroy() \
{ \
	ClassName* instance = GetInstance(); \
	delete instance; \
	instance = nullptr; \
} \
\

// Single tone with constructor destructor
#define DECLARE_SINGLETON_CONSTRUCTOR(ClassName) \
DECLARE_SINGLETON(ClassName)\
\
ClassName() {}\
~ClassName() {}\
\


#pragma endregion


///**
// * 
// */
//template<typename T>
//class OJKFRAMEWORK_API FSingleton
//{
//public:
//
//	static T* GetInstance()
//	{
//		if (instance == nullptr)
//		{
//			instance = new T;
//			atexit(Destroy);
//		}
//
//		return instance;
//	}
//
//
//protected:
//	static void Destroy()
//	{
//		delete instance;
//		instance = nullptr;
//	}
//
//protected:
//	static T* instance;
//
//protected:
//	FSingleton() {}
//	virtual ~FSingleton() {}
//
//};
//
