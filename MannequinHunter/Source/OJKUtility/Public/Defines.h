#pragma once


#define CONSTRUCTOR_HELPERS_FOBJECTFINDER(findeclass, outValue, path) static ConstructorHelpers::FObjectFinder<findeclass> outValue(path);
#define CONSTRUCTOR_HELPERS_FCLASSFINDER(findeclass, outValue, path)  static ConstructorHelpers::FClassFinder<findeclass> outValue(path);