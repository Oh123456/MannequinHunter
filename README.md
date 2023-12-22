# MannequinHunter
UE Game Portfolio <br/>
개인 포트 폴리오 레퍼지토리이다. <br/>
장르 액션 <br/>
작업 환경 PC, 노트북 <br/>
References Game : 마비노기 영웅전, FromSoftware의 소울 시리즈 게임 <br/>

# 본 프로젝트 코딩 표준

- 클래스 함수,변수 위치

```
class
{
   GENERATED_BODY

   static, const

   class struct enum

   constructor, destructor

   member function

   UFUNCTION

   virtual, override

   member variable

   UPROPERTY
}
```
- 접근 지정자
  - public, protected, private 순서로 작성한다.
- 변수명은 소문자로 시작한다.
  - 예외 사항 대문자로 표기된 축약어는 대문자 그대로 사용한다 
- 함수명은 대문자로 시작한다.
- 클래스, 구조체, enum, 네이밍은 언리얼 엔진 코딩 표준을 따른다.

# HFSM 사용한 플레이어 구현

- 액션 게임의 플레이어의 행동을 구현하기에는 FSM이 적합하다고 생각했으나. 상태가 많아저 복잡해질거 같아서 HFSM을 사용하였다.

HFSM 구상도 <br/>
   ![HFSM drawio](https://github.com/Oh123456/MannequinHunter/assets/57939880/b5f943dc-8804-43a9-97c3-22c9322e67a9)
