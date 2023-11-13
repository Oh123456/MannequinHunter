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
	/// CombatComponent ���� Ȯ��
	/// <param name="MeshComp">Ȯ���� ������Ʈ</param>
	/// </summary>
	static bool IsCombatComponentValid(UPrimitiveComponent* MeshComp);
	/// <summary>
	/// CombatComponent ���� Ȯ��, UCombatComponent ��ȯ
	/// </summary>
	/// <param name="MeshComp">Ȯ���� ������Ʈ</param>
	/// <param name="ownerCombatComponent"> ��ȯ ���� CombatComponent</param>
	static bool IsCombatComponentValid(UPrimitiveComponent* MeshComp, OUT class UCombatComponent** ownerCombatComponent);
	/// <summary>
	/// CombatComponent ���� Ȯ��, ABaseActionCharacter �迭 Ŭ���� ��ȯ ,UCombatComponent ��ȯ
	/// </summary>
	/// <param name="MeshComp">Ȯ���� ������Ʈ</param>
	/// <param name="ownerCharacter"> ��ȯ ���� ABaseActionCharacter �迭 </param>
	/// <param name="ownerCombatComponent"> ��ȯ ���� CombatComponent</param>
	/// <returns></returns>
	static bool IsCombatComponentValid(UPrimitiveComponent* MeshComp, OUT class ABaseActionCharacter** ownerCharacter, OUT class UCharacterCombatComponent** ownerCombatComponent);

};
