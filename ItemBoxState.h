#ifndef ITEMBOX_STATE_H
#define ITEMBOX_STATE_H

#include <Arduino.h>

// =============================================
// 아이템박스 FSM 상태 정의
// =============================================
enum class ItemBoxState {
  BOOT,            // 초기 부팅 (setup 중)
  SETTING,         // 세팅 모드 (박스 열림, 흰색)
  READY,           // 준비 완료 (박스 닫힘, 빨간색)
  ACTIVATE,        // 활성화 (외부 태그 대기, 노란색)
  PUZZLE,          // 엔코더 퍼즐 진행 (파란색)
  QUIZ_COMPLETE,   // 퍼즐 완료 (외부 태그 대기)
  OPEN,            // 아이템 가져가기 대기 (내부 태그)
  USED,            // 아이템 수거됨 (빨간색)
  CLOSE,           // 강제 닫기
  REPAIRED_ALL,    // 전체 수리 완료
  PLAYER_WIN,      // 플레이어 승리
  PLAYER_LOSE,     // 플레이어 패배
};

// 현재 FSM 상태 (전역)
extern ItemBoxState currentState;

// 상태 이름 반환 (디버깅/QC용)
inline const char* getStateName(ItemBoxState state) {
  switch (state) {
    case ItemBoxState::BOOT:          return "BOOT";
    case ItemBoxState::SETTING:       return "SETTING";
    case ItemBoxState::READY:         return "READY";
    case ItemBoxState::ACTIVATE:      return "ACTIVATE";
    case ItemBoxState::PUZZLE:        return "PUZZLE";
    case ItemBoxState::QUIZ_COMPLETE: return "QUIZ_COMPLETE";
    case ItemBoxState::OPEN:          return "OPEN";
    case ItemBoxState::USED:          return "USED";
    case ItemBoxState::CLOSE:         return "CLOSE";
    case ItemBoxState::REPAIRED_ALL:  return "REPAIRED_ALL";
    case ItemBoxState::PLAYER_WIN:    return "PLAYER_WIN";
    case ItemBoxState::PLAYER_LOSE:   return "PLAYER_LOSE";
    default:                          return "UNKNOWN";
  }
}

// 상태 전이 함수 — 로깅 + 상태 업데이트
inline bool transitionTo(ItemBoxState newState) {
  if (currentState == newState) return false;  // 같은 상태면 무시
  
  Serial.print("[FSM] ");
  Serial.print(getStateName(currentState));
  Serial.print(" -> ");
  Serial.println(getStateName(newState));
  
  currentState = newState;
  return true;
}

#endif // ITEMBOX_STATE_H
