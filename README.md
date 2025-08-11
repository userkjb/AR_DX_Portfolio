# AR_DX_Portfolio

## 1. 프로젝트 개요 (Project Overview)

이 프로젝트는 C++와 DirectX 11을 기반으로 제작된 3D 렌더링 및 게임 엔진 포트폴리오입니다. Actor-Component 시스템, 렌더링 파이프라인, 리소스 관리, ImGui를 이용한 에디터 UI 등 게임 엔진의 핵심적인 기능들을 직접 구현한 프로젝트입니다.

## 2. 주요 기술 스택 (Technology Stack)

*   **언어 (Language):** C++
*   **그래픽스 API (Graphics API):** DirectX 11
*   **UI 라이브러리 (UI Library):** ImGui
*   **빌드 시스템 (Build System):** Visual Studio 2022

## 3. 빌드 및 실행 방법 (Build & Run Instructions)

1.  **필수 설치 프로그램:**
    *   Visual Studio 2022 (C++ 데스크톱 개발 워크로드 포함)
    *   Windows 11 SDK
2.  **빌드 절차:**
    *   `DirectXK/DirectXK.sln` 파일을 Visual Studio 2022로 엽니다.
    *   솔루션 탐색기에서 'DirectXK' 프로젝트를 시작 프로젝트로 설정합니다.
    *   `빌드(Build)` 메뉴에서 `솔루션 빌드(Build Solution)`를 선택하여 프로젝트를 컴파일합니다.
    *   빌드가 성공하면 `Ctrl + F5` 또는 `디버그(Debug)` 메뉴의 `디버깅하지 않고 시작(Start Without Debugging)`을 선택하여 프로그램을 실행합니다.

## 4. 프로젝트 구조 (Project Structure)

*   **`DirectXK/`**: 프로젝트의 메인 솔루션(`.sln`) 파일과 핵심 소스 코드 폴더들이 위치합니다.
    *   **`App/`**: 프로그램의 시작점(`Main.cpp`)과 애플리케이션 레벨의 로직이 포함됩니다.
    *   **`EngineBase/`**: 엔진의 가장 기본적인 데이터 타입, 수학 관련 클래스, 헬퍼 함수 등이 포함됩니다.
    *   **`EngineCore/`**: 렌더링, 액터, 컴포넌트, 카메라, 충돌 처리, 리소스 관리 등 엔진의 핵심 기능이 구현된 클래스들이 위치합니다.
    *   **`EnginePlatform/`**: Windows API와 관련된 창 생성, 메시지 루프 등 플랫폼 종속적인 코드가 포함됩니다.
    *   **`EngineShader/`**: HLSL로 작성된 버텍스 셰이더, 픽셀 셰이더 등의 셰이더 파일들이 위치합니다.
*   **`ThirdPartyProject/`**: ImGui 등 외부 라이브러리 소스 코드가 위치합니다.

## 5. 핵심 클래스 및 기능 (Core Classes & Features)

*   **`EngineGraphicDevice`**: DirectX 11 디바이스 및 컨텍스트를 래핑하여, 리소스 생성 및 렌더링 명령을 관리하는 핵심 클래스입니다.
*   **`Renderer`**: 렌더링 파이프라인을 관리하며, `Mesh`, `Material`, `Shader` 등을 사용하여 화면에 오브젝트를 그리는 역할을 담당합니다.
*   **`Actor` / `ActorComponent`**: 게임 월드의 모든 오브젝트는 `Actor`이며, 기능은 `ActorComponent` 단위로 분리되어 붙여지는 구조입니다. (예: `TransformComponent`, `CameraComponent`)
*   **`Level` / `GameMode`**: 게임의 월드(레벨)와 규칙을 정의하며, `Actor`들을 관리합니다.
*   **`EngineShader` / `EngineMaterial`**: HLSL 셰이더 코드를 로드하고 관리하며, 렌더링에 사용될 재질(텍스처, 셰이더 설정 등)을 정의합니다.
*   **`EngineEditorGUI`**: ImGui를 사용하여 개발 및 디버깅을 위한 다양한 에디터 창(오브젝트 정보, 렌더링 옵션 등)을 제공합니다.
