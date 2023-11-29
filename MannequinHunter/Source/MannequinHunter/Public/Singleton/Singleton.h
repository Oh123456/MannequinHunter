// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
template<typename T>
class MANNEQUINHUNTER_API FSingleton
{
public:

	static T* GetInstance();

protected:
	static void Destroy();

protected:
	static T* instance;

protected:
	FSingleton() {}
	virtual ~FSingleton() {}

};


template<typename T>
T* FSingleton<T>::instance = nullptr;

template<typename T>
T* FSingleton<T>::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new T;
		atexit(Destroy);
	}

	return instance;
}

template<typename T>
void FSingleton<T>::Destroy()
{
	delete instance;
	instance = nullptr;
}