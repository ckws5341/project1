// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(project_Taesung, Log, All);

#define Tasung_ErrorLog(Verbosity) UE_LOG(project_Taesung, Verbosity, TEXT("%s"), (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))

#define CHECK(Expr, ...) {if(!(Expr)) {UE_LOG(project_Taesung, Error, TEXT("ASSERTION : %s"), TEXT("'"#Expr"'")); return __VA_ARGS__; } }
