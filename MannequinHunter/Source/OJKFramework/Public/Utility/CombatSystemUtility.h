// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class OJKFRAMEWORK_API FCombatSystemUtility
{
public:
	/// <summary>
	/// CombatComponent 유무 확인
	/// <param name="MeshComp">확인할 컴포넌트</param>
	/// </summary>
	static bool IsCombatComponentValid(UPrimitiveComponent* MeshComp);
	/// <summary>
	/// CombatComponent 유무 확인, UCombatComponent 반환
	/// </summary>
	/// <param name="MeshComp">확인할 컴포넌트</param>
	/// <param name="ownerCombatComponent"> 반환 받을 CombatComponent</param>
	static bool IsCombatComponentValid(UPrimitiveComponent* MeshComp, OUT class UCombatComponent** ownerCombatComponent);
	/// <summary>
	/// CombatComponent 유무 확인, ABaseActionCharacter 계열 클래스 반환 ,UCombatComponent 반환
	/// </summary>
	/// <param name="MeshComp">확인할 컴포넌트</param>
	/// <param name="ownerCharacter"> 반환 받을 ABaseActionCharacter 계열 </param>
	/// <param name="ownerCombatComponent"> 반환 받을 CombatComponent</param>
	/// <returns></returns>
	static bool IsCombatComponentValid(UPrimitiveComponent* MeshComp, OUT class ABaseActionCharacter** ownerCharacter, OUT class UCharacterCombatComponent** ownerCombatComponent);

};
