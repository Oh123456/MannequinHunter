#pragma once

#include "CoreMinimal.h"


#define UE_LOG_WARNING(CategoryName, Format, ...) UE_LOG(CategoryName, Warning ,Format, ##__VA_ARGS__)
#define UE_LOG_ERROR(CategoryName, Format, ...) UE_LOG(CategoryName, Error ,Format, ##__VA_ARGS__)


#define LOG_BOOL(b) b ? TEXT("Ture") : TEXT("False")
#define LOG_BOOL_CUSTOM(b, strue, sfalse) b ? #strue : #sfalse
