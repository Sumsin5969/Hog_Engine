---

## 🛠 주요 컴포넌트

### **Engine**
- `HERun(...)` : 엔진 실행 루프 시작
- `HEUpdate()` : 매 프레임 업데이트
- `HESetNextGameState(...)` : 다음 게임 상태 설정
- `HEShutDown()` : 엔진 종료

### **WindowManager**
- SDL 윈도우 생성 (`Init`)
- 윈도우 핸들 반환 (`GetCurrentWindow`)
- 윈도우 제거 (`Destroy`)

### **RenderManager**
- OpenGL 렌더링 초기화 (`Init`)
- 배경색 초기화 (`ClearBackground`)
- 텍스처 로드 (`LoadTexture`)
- 화면 렌더링 (`Draw`, `SwapWindow`)
- 리소스 해제 (`Destroy`)

### **StateManager**
- `GameState` 인터페이스를 기반으로 상태 관리
- 현재 상태와 다음 상태를 보관하며 전환 처리

### **ObjectManager**
- `Actor*` 기반으로 게임 오브젝트 등록 및 관리

### **InputManager**
- SDL 이벤트 기반 입력 처리
- `QuitRequested()`로 종료 요청 여부 확인

---

## 🚀 사용 예시

```cpp
#include "Engine.h"

class MainMenuState : public GameState {
public:
    void Load() override { /* 리소스 로드 */ }
    void Init() override { /* 초기화 */ }
    void Update() override { /* 로직 처리 */ }
    void Destroy() override { /* 리소스 해제 */ }
};

int main() {
    HERun("My Game", 1280, 720, 60, 1, std::make_unique<MainMenuState>());
    return 0;
}