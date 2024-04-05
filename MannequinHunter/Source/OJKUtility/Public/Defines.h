#pragma once


#define CONSTRUCTOR_HELPERS_FOBJECTFINDER(findeclass, outValue, path) static ConstructorHelpers::FObjectFinder<findeclass> outValue(path);
#define CONSTRUCTOR_HELPERS_FCLASSFINDER(findeclass, outValue, path)  static ConstructorHelpers::FClassFinder<findeclass> outValue(path);



#define INPUT_ACTION(inputActionName) \
UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input) \
UInputAction* inputActionName; \

#define TMAP_CUSTEM_KEY (ClassName) \
uint32 GetTypeHash(const ClassName& key) \
{ \
	uint32 Hash = FCrc::MemCrc32(&key, sizeof(ClassName)); \
	return Hash; \
} \
 \
inline bool operator == (const ClassName& key, const ClassName& key2) \
{ \
	return key.Equals(key2); \
} \


#define ALLOW_PRIVATE_ACCESS AllowPrivateAccess = "true"
#define TEXT_NONE TEXT("None")


#define EXECUTE_INTERFACE_RET_VAL(InterfaceClass,uClass, FunctionName, retValue , ...) \
if (uClass->ImplementsInterface(U##InterfaceClass::StaticClass()))\
{\
	I##InterfaceClass* castInterface = Cast<I##InterfaceClass>(uClass->GetDefaultObject()); \
	retValue = castInterface->FunctionName(__VA_ARGS__);\
}\

#define EXECUTE_INTERFACE(InterfaceClass,uClass, FunctionName, ...) \
if (uClass->ImplementsInterface(U##InterfaceClass::StaticClass()))\
{\
	I##InterfaceClass* castInterface = Cast<I##InterfaceClass>(uClass->GetDefaultObject()); \
	castInterface->FunctionName(__VA_ARGS__);\
}\

