# 🎨 3D 그래픽스 & 셰이더 프로젝트

OpenGL과 GLSL을 활용해 3D 객체를 실시간으로 렌더링하고, 조명 및 셰이딩 효과를 구현한 그래픽스 프로젝트입니다.

---

## 📌 프로젝트 개요

이 프로젝트는 3D 그래픽스 렌더링 파이프라인의 기초 개념을 직접 구현하며 학습하기 위해 진행되었습니다.  
카메라와 객체 변환, 조명, 셰이더 프로그래밍 등 실시간 그래픽스의 핵심 요소들을 직접 다뤘습니다.

---

## 🔹 구현 기능

### ✅ 1. Model / View / Projection 행렬 계산
- 3D 객체를 월드 좌표계에 배치하고 카메라 시점으로 변환  
- 최종적으로 화면 공간에 투영되도록 MVP 행렬 직접 구성 및 적용

### ✅ 2. Phong 조명 모델 구현
- Ambient / Diffuse / Specular 조명을 계산하여 현실감 있는 조명 효과 적용  
- 광원 방향과 물체 표면의 상호작용을 수학적으로 계산해 반사광 구현

### ✅ 3. GLSL 기반 셰이더 작성
- Vertex / Fragment Shader를 직접 작성하여 그래픽스 파이프라인 제어  
- 조명, 텍스처, 색상 등을 실시간으로 조절 가능

---

## 🛠 사용 기술

- **언어**: C++  
- **그래픽스 API**: OpenGL  
- **셰이더 언어**: GLSL  
- **활용 수학**: 행렬 변환, 벡터 내적/외적, 반사 벡터 계산 등

---

## 🎯 주요 학습 내용

- 그래픽스 렌더링 파이프라인의 작동 원리  
- 실시간 조명 모델의 구현 방식  
- GPU 셰이더 프로그래밍의 기본 구조  
- 수학적 모델링을 통한 3D 공간 표현

---

## 🖼️ 결과물
<img width="323" height="169" alt="image" src="https://github.com/user-attachments/assets/b17ce34d-891c-4ad4-b377-331b848da67c" />
<img width="323" height="169" alt="image" src="https://github.com/user-attachments/assets/9837fef7-6405-4e0a-9053-30d97d02777a" />
<img width="323" height="169" alt="image" src="https://github.com/user-attachments/assets/69f8f9de-f683-4b6e-b9b2-a9ec15d4587a" />

