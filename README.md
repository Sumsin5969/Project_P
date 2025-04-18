
# Project_P 개발 마일스톤 플랜 & 게임 문서

## Development Plan

| 마일스톤 | 주차 | 기간 | 목표 | 주요 작업 | 비고 |
|----------|------|-------|-------|------------|------|
| 개발 | 1주차 | 04-10 ~ 04-18 | 캐릭터 조작 <br> zoom in&out <br> 대쉬 기능<br> 카메라 움직임 구현 <br> 타이머  | - 대쉬 기능<br> - 카메라 움직임 구현<br>- 임시 도형 그리기<br>- 키 입력 받기<br>- 충돌 체크 |  |
| 개발 | 2주차 | 04-19 ~ 04-25 | 탄막 구현 <br> 보스 구현 |  - 탄막 궤적<br>- 적 AI<br>- 이미지 삽입- 레벨 디자인 |  |
| 개발 | 3주차 | 04-26 ~ 05-02 | UI, UX<br> 이펙트<br> 사운드<br> 이미지 교체 |  |  |
| 폴리싱 | 4주차 | 05-03 ~ 05-09 | 밸런싱 | - 구상중 |  |
| 빌드 안정화 | 5주차 | 05-10 ~ 05-15 | 최종 디버깅 & 밸런스 조정 | - 구상중 |  |

---

## Daily Report 링크

> https://docs.google.com/spreadsheets/d/1qCBNRiYkRlbFA0GK-Sijq355_IKXwG7KapppzgWhN-8/edit?usp=sharing

---

## 게임 한 줄 소개

**캐릭터를 조작하여 적이 쏘는 미사일 및 장애물을 피해 정해진 시간동안 생존하는 게임입니다.**

---

## 게임 목표 / 승리 조건

- 1스테이지에서 피격당할 시 패배
- **7스테이지에서 30초를 버티면 승리**

---

## 주요 게임 오브젝트

- 플레이어 캐릭터 (속도, 대쉬, 크기, 충돌 체크)
- 장애물 (충돌 체크)
- 적 유닛 (미사일 발사, 이동)
- 보스 (미사일 발사, 이동)

---

## 게임 UI/UX 구성

- 플레이어 정보: **대쉬 가능 여부(쿨타임)**
- 위험 정보: **적 유닛 공격 예고(레이저 등)**
- 일시정지 메뉴: **버튼 구현(재개, 설정, 종료)**

---

## 게임 흐름

> 게임 시작 → 적 및 공격 회피 → 30초 생존 → 줌 아웃 → 적 추가 등장 → 캐릭터 피격 → 줌 인 → 적 감소

---

## 플레이어 행동 / 선택 / 영향

- 생존 > 줌 아웃 > 오브젝트 및 적 추가
- 피격 > 줌 인 > 오브젝트 및 적 감소

---

## 04/18 기준 구현된 내용 정리

- 캐릭터 이동
- 캐릭터 대쉬
- 상하좌우 벽 렌더링
- 줌 Level 1의 벽 충돌 감지
- 탄막패턴 1종
- 적 공격패턴 1종
- 타이머

--- 

## 조작법

- 이동: 방향키
- 대쉬: Shift