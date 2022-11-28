# MIPS-pipeline-processor-simulator

## 22-2 Computer Architecture Project
### 20191555 김규민
### 20191599 박준서

## Description
MIPS and/or/add/sub/slt/lw/sw/beq/j 9가지 instruction을 수행하는 5단계 pipeline processor를 cycle 단위로 시각화 하여 보여준다. 

![pipelinePerformance](https://user-images.githubusercontent.com/54925443/204225452-eba3f83d-cdb6-4bf6-a20f-cb27dd9c0060.png)

single cycle 방식에서는 하나의 instruction의 수행을 끝낸 후 다음 cycle을 실행하지만 pipeline 방식에서는 IF, ID, EX, MEM, WB 5단계로 나누어 동시에 다른 instruction을 다루기 때문에 실행시간을 단축할 수 있다.
"pipelineMap" //워터마크 추가

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

## Usage
