// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/ActionPlayerController.h"

void AActionPlayerController::ExecuteInputBuffer()
{
	if (IsInputBuffer())
	{
		inputBufferAction.Execute();
		inputBufferAction.Unbind();
	}
}
