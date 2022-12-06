# MIPS-pipeline-processor-simulator

## 22-2 Computer Architecture Project
### 20191555 김규민
### 20191599 박준서

## How to install

#### Ubuntu 18.04 +
```
sudo apt-get update
sudo apt-get install build-essential qtcreator qt5-default make


git clone https://github.com/QueueMin/MIPS-pipeline-processor-simulator.git
cd MIPS-pipeline-processor-simulator/GUI/MIPSSimulator/MIPSSimulator/

qmake
make

./MIPSSimulator
```
거의 유사한 맥락으로 Windows와 MAC OS에서도 설치 가능하다.

이외에도 자신의 운영체제에 맞는 [Qt creator](https://www.qt.io/ko-kr/product/development-tools)를 설치한 뒤 Qt creator에서 `./MIPS-pipeline-processor-simulator/GUI/MIPSSimulator/MIPSSimulator/MIPSSimulator.pro`를 프로젝트로서 연 후, `Qt 5.15` 이상 버전으로 빌드하는 방법이 존재한다.

![image](https://user-images.githubusercontent.com/55120768/205352810-52ae4a44-4f50-41fc-94eb-de1aa34a37f4.png)
![image](https://user-images.githubusercontent.com/55120768/205352959-80f1e735-85d8-4cad-9a45-b8e350da4b53.png)




## Description
MIPS and/or/add/sub/slt/lw/sw/beq/j 9가지 instruction을 수행하는 5단계 pipeline processor를 cycle 단위로 시각화 하여 보여준다. 
![image](https://user-images.githubusercontent.com/55120768/205290221-9d9ded75-8d47-4a5a-8c32-1f06304aadce.png)


single cycle 방식에서는 하나의 instruction의 수행을 끝낸 후 다음 cycle을 실행하지만 pipeline 방식에서는 IF, ID, EX, MEM, WB 5단계로 나누어 동시에 다른 instruction을 다루기 때문에 실행시간을 단축할 수 있다.

![pipelinePerformance](https://user-images.githubusercontent.com/54925443/204225452-eba3f83d-cdb6-4bf6-a20f-cb27dd9c0060.png)

## Hazard
single cycle 방식은 instruction이 순차적으로 진행되지만 pipeline 방식은 이전 instruction이 끝나기 전에 다음 instruction이 fatch되기 때문에 데이터 처리 과정에서 hazard가 발생한다.

### Data Hazard
![DataHazard](https://user-images.githubusercontent.com/54925443/204225772-ad19a38a-b712-42a5-a147-e2021676506a.png)

전후 instruction이 의존관계에 있을 때 발생하는 hazard로 Forwarding Unit을 통해 이전 instruction에서 처리 된 값을 가져와 사용한다.

### Structure Hazard
![StructureHazard](https://user-images.githubusercontent.com/54925443/204225805-338b3629-4698-42af-93b1-147451097bcf.png)

pipeline 구조에서 발생하는 hazard로 lw instruction에서 Rd값을 사용하는 instruction이 뒤따르는 경우 forwarding으로 hazard를 해결할 수 없다. 따라서 Hazard Detection Unit에서 hazard 유무를 판별해 bubble을 배치한다.

### Control Hazard
bubble의 갯수를 줄이기 위해 branch instruction이 계산되기 전에 다음 명령어를 fatch하는것에서 생기는 hazard이다. 본 프로젝트에서는 as not taken 방식을 선택했다. 즉 branch instruction 이 있는 Program Counter값의 다음 instruction을 fatch 한다. 이 상황에서 branch된다면 IFFlush로 fatch되는 값을 0으로 바꿔준다.

------
## How code works
회로상에서 일어나는 모든 동작들은 코드의 `Simulator` 객체에서 이루어지게 된다. `Simulator`는 pipelined circuit의 구조를 최대한 본따, `MemoryManager`,`ForwardUnit`, `HazardDetectionUnit`, `ControlUnit`와 같이 입력에 따른 제어신호를 알맞게 반환하는 객체들을 내장하고 있다. `Simulator`는 `IF`, `ID`, `EX`, `MEM`, `WB`의 method를 가지며 해당 method들은 앞서 서술한 객체들과 pipeline register의 역할을 하는 `IFID`, `IDEX`, `EXMEM`, `MEMWB` 객체와 상호작용하며 실행되고, 그 결과는 다시 pipeline register객체에 저장되거나, $0~$31 레지스터에 write back되거나, `MemoryManager` 객체에 전달되어 Memory 영역에 저장된다. 
program counter와 $0~$31번 레지스터에 들어가는 데이터는 `Simulator` 객체의 필드에 저장된다. 이외에 `Jump`, `PCsrc`, `IF Flush` signal들 또한 `Simultor`객체의 필드에 저장된다.


 GUI는 `Qt5`기반으로 제작되었으며, [QTSpim](https://spimsimulator.sourceforge.net/)의 큰 구조를 벤치마킹 하였다. `Simulator` 객체에 접근하여 데이터를 가져와 화면에 표시한다. 회로의 동작에 직접적인 영향을 미치는 요소들은 `QGraphicSceneView`에 회로도를 표시하고, `Simulator`객체의 요소에 대응하는 component의 옆 혹은 위에 해당 값을 표시한다.
 Encode되어 저장된 instruction들, PC와 $0~$31 레지스터가 가지는 값, 현재 Memory 영역에 저장된 0이 아닌 값은 각각 해당하는 Tab에 table의 형태로 확인할 수 있게 하였다.


## Usage
* ![image](https://user-images.githubusercontent.com/55120768/205359735-a4da0887-6974-4922-9039-e0b4e64566ab.png) File load button: 버튼을 누르면 파일을 선택할 수 있는 dialog가 나오고, 해당 dialog를 통해 `{filename}.s`형태로 저장된 파일을 열면 해당 파일의 내용을 바탕으로 instruction들이 시뮬레이터에 저장된다.
* ![image](https://user-images.githubusercontent.com/55120768/205360416-650399f9-85f2-437f-8dbb-b941ac656bb8.png) Run single cycle button: 버튼을 누르면 현재 시뮬레이터에 저장된 값들을 바탕으로 시뮬레이터를 한 사이클 작동한다. 

* ![image](https://user-images.githubusercontent.com/55120768/205361415-73010205-6975-443c-87e1-bd11d4474db5.png) Display Settings: Register 탭에서 보여주는 값들과 Memory 탭에서 보여주는 값들을 각각 2진수, 10진수, 16진수로 변환하여 표시할 수 있도록 설정한다.

![image](https://user-images.githubusercontent.com/55120768/205845809-954f796b-0a75-41ad-95d1-bb2c1bc2c470.png)    
* Instructions, Register, Memory Tab:
선택한 탭의 정보를 표시한다. `Instrtuction Tab`은 각 Instruction이 할당된 PC와 encode된 code를 16진수로 표시한다. `Register Tab`은 현재 사이클이 시작할 때의 PC와 $0~$31번 레지스터에 들어가는 데이터가 표시된다. 이때, 이전 사이클과 비교해서 변화가 생긴 PC 혹은 register 값의 경우 붉은 색으로 highlight된다. `Memory Tab`은 데이터 필드에 저장된, 0이 아닌 데이터가 저장된 주소와 해당 값을 표시한다. 이때 .data directive나 특정 instruction을 통해 특정한 주소에 0을 저장하더라도 Tab에 표시되지 않는다.


