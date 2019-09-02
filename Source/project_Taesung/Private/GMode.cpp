// Fill out your copyright notice in the Description page of Project Settings.

#include "GMode.h"
#include "UserCharacter.h"
#include "PCtrller.h"
AGMode::AGMode()
{
	PlayerControllerClass = APCtrller::StaticClass();
	DefaultPawnClass = AUserCharacter::StaticClass();
}



