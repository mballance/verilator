# Distributed Multi-Node Simulation Framework  Research & Naming Analysis

## 1. Problem Statement

Design a simulation framework enabling multi-core, multi-node simulation sessions
that mix hardware models (abstract to RTL) with software emulation (e.g. QEMU) and
real/emulated hardware. Nodes communicate via message-oriented FIFOs. A single
lead/primary node orchestrates the distributed session. Same-machine IPC uses shared
memory + sockets; cross-machine IPC uses sockets.

---

## 2. Landscape of Similar Solutions

### 2.1 Switchboard (Zero ASIC)  *Closest match*

- **What:** Open-source framework for modular, distributed simulation of large
  hardware systems (ASICs, chiplets, FPGAs, software models).
- **Communication:** Single-producer / single-consumer (SPSC) shared-memory FIFO
  queues with ~100 ns latency. TCP bridging for multi-host. Packet-based (416-bit
  packets with destination, control flags, payload).
- **Topology:** Arbitrary; each block is an independent process connected via SB
  ports. Protocol adapters for AXI, UMI, GPIO, etc.
- **Scale:** Demonstrated million-core simulations.
- **Differentiation from your design:** Switchboard is focused on hardware block
  composition (RTL/FPGA/SW models). It does *not* natively integrate full-system
  software emulators like QEMU, nor does it have the concept of a lead/primary node
  orchestrating a heterogeneous HW+SW session.
- **Links:** [GitHub](https://github.com/zeroasiccorp/switchboard),
  [Paper](https://arxiv.org/pdf/2407.20537)

### 2.2 FireSim (UC Berkeley)

- **What:** FPGA-accelerated, cycle-accurate simulation of scale-out systems
  (datacenter-scale). Up to 1024 quad-core nodes.
- **Communication:** FPGA-to-FPGA links; network simulation with parameterized
  bandwidth/latency/topology. Cloud-native (AWS EC2 F1).
- **Differentiation:** Tightly coupled to FPGAs and the Chipyard/Rocket Chip
  ecosystem. Not designed for mixing abstract models or QEMU-based SW emulation
  with RTL. Very different scope (datacenter architecture research).
- **Links:** [fires.im](https://fires.im/),
  [GitHub](https://github.com/firesim/firesim)

### 2.3 Xilinx/AMD libsystemctlm-soc + Remote-Port

- **What:** SystemC/TLM-2.0 co-simulation framework. Connects QEMU instances to
  SystemC/TLM models and RTL (via Verilator) using a "remote-port" protocol over
  Unix sockets.
- **Communication:** Unix sockets between QEMU and SystemC. Supports multiple QEMU
  instances talking to a single SystemC simulation.
- **Differentiation:** Focused on Xilinx/AMD SoC platforms (Zynq, Versal).
  Single-host, tightly coupled to Xilinx tooling. No concept of distributed
  multi-machine sessions or a lead-node orchestrator.
- **Links:** [GitHub](https://github.com/Xilinx/libsystemctlm-soc)

### 2.4 SonicSim (UC Berkeley)

- **What:** Socket-based hardware co-simulation where distinct models (CPU, GPU)
  communicate via standard sockets with FIFO semantics.
- **Communication:** Inter-process and network sockets, point-to-point and
  server-client topologies.
- **Differentiation:** Research-stage; focused on heterogeneous HW model
  composition, not full SW emulation integration.
- **Links:** [Paper (PDF)](https://www2.eecs.berkeley.edu/Pubs/TechRpts/2024/EECS-2024-61.pdf)

### 2.5 MuchiSim (Princeton)

- **What:** Parallel simulator for design exploration of multi-chiplet manycore
  systems (up to 1M processing units).
- **Communication:** Message-passing models, parallelized execution.
- **Differentiation:** High-level cycle-accurate modeling only  no RTL, no QEMU,
  no SW emulation. Pure architecture exploration.
- **Links:** [GitHub](https://github.com/PrincetonUniversity/muchiSim)

### 2.6 Aldec Riviera-PRO + QEMU

- **What:** Commercial HW/SW co-verification. QEMU runs software; Riviera-PRO runs
  RTL/SystemC. Connected via AXI BFM bridge.
- **Differentiation:** Proprietary, single-host, vendor-locked workflow.

### 2.7 QEMU-CAS (CARRV 2023)

- **What:** Full-system cycle-accurate simulation based on QEMU for RISC-V.
- **Differentiation:** Single-node, single-purpose (cycle-accurate SW simulation
  on one core). No distributed or multi-node capability.

### Summary Comparison Table

| Framework              | Distributed | QEMU | RTL  | Shared Mem | Sockets | Lead Node | Mixed HW/SW |
|------------------------|:-----------:|:----:|:----:|:----------:|:-------:|:---------:|:-----------:|
| **Your design**        |           |    |    |          |       |         |           |
| Switchboard            |           |    |    |          |       |         | Partial     |
| FireSim                |           |    |    |          |       |         |           |
| libsystemctlm-soc     | Partial     |    |    |          |       |         |           |
| SonicSim               |           |    |    | Indirect   |       |         | Partial     |
| MuchiSim               |           |    |    |          |       |         |           |
| Aldec QEMU Co-Sim      |           |    |    |          |       |         |           |

**Key takeaway:** No existing open-source framework combines *all* of: distributed
multi-machine execution, QEMU SW emulation, RTL simulation, shared-memory + socket
IPC, and a lead-node orchestrator. Your design fills a genuine gap  closest to
Switchboard in communication architecture but broader in scope (SW emulation, lead
node, heterogeneous session management).

---

## 3. Name Suggestions  Round 1

### Candidate 1: **nsim** (Node Simulation)
Your initial preference.

### Candidate 2: **meshsim** (Mesh Simulation)
Evokes the interconnected, multi-node mesh topology of the system.

### Candidate 3: **distsim** (Distributed Simulation)
Directly describes the core architectural property.

### Candidate 4: **simforge**
Abstract/brandable name suggesting the "forging" (assembly) of simulation components.

---

## 4. Round 1  Critical Name Comparison

### 4.1 nsim  Node Simulation

| Aspect       | Assessment |
|-------------|-----------|
| **Pros**    | Short, memorable, easy to type. "Node" maps directly to the architecture. Clean CLI feel (`nsim run`, `nsim launch`). |
| **Cons**    | **Namespace collision:** Synopsys ships a commercial product called "nSIM"  the ARC processor instruction-set simulator. This is a well-known tool in the embedded/EDA industry and appears in Zephyr RTOS docs, Synopsys product pages, and academic papers. Multiple smaller open-source projects also use "nsim" on GitHub (network simulator, payment simulator, HP-41CV microcode simulator). The name is generic  "node simulation" could mean anything (network sim, Node.js sim, etc.). |
| **Risk**    | **HIGH**  Direct naming conflict with Synopsys nSIM in the same EDA/hardware simulation domain. Likely to cause confusion in searches, documentation references, and professional conversations. |

### 4.2 meshsim  Mesh Simulation

| Aspect       | Assessment |
|-------------|-----------|
| **Pros**    | Evocative of interconnected topology. Reasonably unique  no major conflicts in the EDA/simulation space. Slightly more descriptive than "nsim." |
| **Cons**    | "Mesh" implies a specific topology (mesh network), which may not always match the actual connection topology (could be star, tree, etc.). Some academic mesh-generation tools use similar names. Longer to type than nsim. |
| **Risk**    | LOW  no significant conflicts in the target domain. |

### 4.3 distsim  Distributed Simulation

| Aspect       | Assessment |
|-------------|-----------|
| **Pros**    | Immediately communicates the distributed nature. Professional and self-documenting. No major namespace conflicts. |
| **Cons**    | Generic and dry  sounds academic rather than like a tool you'd reach for. "distsim" has been used as a variable/function name in various codebases. Doesn't hint at the HW/SW co-simulation or multi-fidelity aspects. |
| **Risk**    | LOW  no significant conflicts, but also not distinctive. |

### 4.4 simforge

| Aspect       | Assessment |
|-------------|-----------|
| **Pros**    | Unique, brandable, and memorable. No namespace conflicts in EDA/simulation. Suggests assembly/construction of something powerful. Works well for a CLI tool and as a project identity. Easy to search for. |
| **Cons**    | Abstract  doesn't self-document what the tool does. Someone seeing "simforge" for the first time won't know it's about distributed HW/SW simulation. Slightly longer. |
| **Risk**    | VERY LOW  highly distinctive, no conflicts found. |

---

## 5. Name Suggestions  Round 2 (System-Oriented)

Given the framework's deeper ambitions  coordinating resource sharing between
simulation nodes (memory page checkout, shared state management, etc.)  a
"system"-rooted name better captures the scope. The framework isn't just simulating
nodes in isolation; it's orchestrating a *system* of cooperating simulators that
share resources. This shifts the framing from "distributed execution" to "system
co-simulation with managed resources."

### Candidate 5: **ssim** (System Simulation)

### Candidate 6: **syssim** (System Simulation  unambiguous spelling)

### Candidate 7: **sysfab** (System Fabric)

---

## 6. Round 2  Research & Critical Analysis

### 6.1 ssim  System Simulation

**Namespace research:**
- **SSIM is overwhelmingly associated with "Structural Similarity Index Measure"**
   the de facto standard image/video quality metric (scikit-image, MATLAB, PyTorch,
  OpenCV). Searching "ssim" on GitHub returns hundreds of SSIM-metric repositories.
  Academic papers, Stack Overflow, and documentation universally use "SSIM" for this
  metric.
- No significant *simulator* projects named "ssim" were found outside the image
  quality domain.
- The collision is cross-domain (image processing vs. EDA/simulation), but it is
  *massive* in volume  "ssim" is one of the most recognized acronyms in all of
  computer science.

| Aspect       | Assessment |
|-------------|-----------|
| **Pros**    | Extremely short (4 chars). "System simulation" is precisely what the tool does. Clean CLI feel (`ssim launch`, `ssim status`). Intuitive to anyone in the HW/EDA space. |
| **Cons**    | **Severe search pollution.** "SSIM" returns millions of results about the Structural Similarity Index. Even with context qualifiers ("ssim simulator", "ssim hardware"), image-quality results will dominate for years. Documentation links, README badges, and package registry names will be buried. This is arguably worse than the nsim/Synopsys collision because SSIM is *universally* known, not just within EDA. |
| **Risk**    | **VERY HIGH**  Cross-domain but overwhelming namespace collision. The acronym is essentially "taken" by image processing. |

### 6.2 syssim  System Simulation (expanded)

**Namespace research:**
- **SYSSIM** exists as a power-electronics simulator on GitHub (mhx-gh/SYSSIM)
  small, low-activity project.
- **SYSSIM** appears in a 1980s academic paper as a real-time control system
  simulation tool (ScienceDirect).
- **Airbus_SysSim** on GitHub models a primary flight control computer.
- **SimSys** (reversed word order) is used by Mississippi State University for CFD
  tools, and by the UK Met Office for deployment scripts.
- None of these are in the EDA/hardware co-simulation domain, and all are low-
  profile projects.

| Aspect       | Assessment |
|-------------|-----------|
| **Pros**    | Self-documenting  "system simulation" is immediately clear. Short enough to type comfortably (6 chars). Avoids the SSIM image-metric collision by being distinct. No conflicts in the EDA/hardware simulation space. The extra two characters over "ssim" buy enormous search clarity. Works well as CLI (`syssim run`, `syssim node add`). The "sys" prefix naturally extends to sub-commands and concepts (sysnode, sysfabric, etc.). |
| **Cons**    | Minor collisions with low-profile projects in unrelated domains (power electronics, flight control). "syssim" is somewhat generic  doesn't convey the distributed, multi-fidelity, or resource-sharing aspects. Could be confused with generic "system simulation" as a category rather than a specific tool. |
| **Risk**    | **LOW**  No significant conflicts in the target domain. The existing uses are small, dormant, and in completely different fields. |

### 6.3 sysfab  System Fabric

**Namespace research:**
- **sysfab** on GitHub is a personal account (SysFAB64) with a handful of unrelated
  hobby repositories (video game modding, Linux config). No simulation tools.
- **SimFab** is a flight/racing cockpit hardware brand (simfab.eu)  physical
  products, not software.
- No software projects, libraries, or tools named "sysfab" were found in EDA,
  simulation, or systems engineering.

| Aspect       | Assessment |
|-------------|-----------|
| **Pros**    | **Unique and descriptive of the architecture.** "Fabric" is the right metaphor  it evokes the interconnect/communication layer that weaves simulation nodes together, manages shared resources (memory pages, state), and provides the substrate for coordinated execution. Well-understood in hardware/systems contexts (switch fabric, interconnect fabric). Short (6 chars). No namespace conflicts anywhere. Brandable  sounds professional and purposeful. Naturally extends: "sysfab node", "sysfab fabric", "sysfab page-checkout". |
| **Cons**    | "Fabric" might initially suggest networking infrastructure rather than simulation. Someone unfamiliar might think it's a deployment/orchestration tool (like Fabric, the Python SSH library  though that's lowercase "fabric" or "fab"). Requires a subtitle to fully communicate the simulation aspect. |
| **Risk**    | **VERY LOW**  Essentially no conflicts. The GitHub account is irrelevant, and SimFab is hardware in a different domain. |

---

## 7. Combined Ranking (All 7 Candidates)

| Rank | Name         | Score | Rationale |
|:----:|-------------|:-----:|-----------|
| 1    | **sysfab**   | 9.5/10 | Best overall. "System Fabric" precisely describes the interconnect + resource-sharing architecture. Zero namespace conflicts. Brandable, professional, and short. The "fabric" metaphor resonates with the HW/EDA audience. Subtitle: "Distributed System Simulation Fabric." |
| 2    | **syssim**   | 8.5/10 | Strong runner-up. Self-documenting ("system simulation"), low conflict risk, comfortable to type. Falls slightly behind sysfab because it's more generic and doesn't hint at the resource-sharing/fabric aspects. But it's the safest "says what it does" choice. |
| 3    | **simforge** | 8/10  | Still excellent for brandability and uniqueness. Slightly less descriptive of the system/fabric architecture than sysfab or syssim. |
| 4    | **meshsim**  | 6.5/10 | Decent but implies a fixed mesh topology. |
| 5    | **distsim**  | 6/10  | Safe but forgettable. |
| 6    | **nsim**     | 4/10  | Synopsys ARC nSIM collision in same domain. |
| 7    | **ssim**     | 2/10  | Catastrophic collision with SSIM (Structural Similarity Index)  one of the most widely used acronyms in CS/ML/image processing. Unusable. |

---

## 8. Recommendation

*(See updated recommendation in Section 10 below.)*

---

## 9. Name Suggestions  Round 3 (Network/Graph/Mesh + System)

Feedback: `sysfab` doesn't roll off the tongue. Preference for names evoking
network, graph, mesh, or interconnection  something that captures the connected
topology of the simulation system.

### Candidates Considered and Eliminated

| Name       | Why eliminated |
|------------|---------------|
| **simgrid** | **Blocked.** SimGrid is a major, 20+ year old LGPL framework from INRIA for simulating distributed systems. Thousands of citations, active development, Wikipedia page. Direct collision in exactly the same space. |
| **sysgraph** | Taken. SiliconHoller/sysgraph on GitHub (infrastructure modeling tool). Also Sophuwu300/sysgraph (terminal graph visualizer). The name reads more like a monitoring/visualization tool than a simulation engine. |
| **syscloud** | Misleading  implies cloud computing infrastructure (AWS, GCP). Would confuse the audience. |

### New Candidates

### Candidate 8: **sysmesh**

"System Mesh"  the interconnected mesh of simulation nodes forming a coherent
system. Evokes service-mesh concepts (Istio, Linkerd) which are about managed
inter-process communication  exactly what this framework provides for simulation.

### Candidate 9: **sysnet**

"System Network"  the network of simulation nodes. Short, punchy, emphasizes the
connected/networked nature of the distributed system.

### Candidate 10: **sysloom**

"System Loom"  a loom weaves threads together into fabric. The framework weaves
simulation nodes (threads) into a coherent system. Evocative, metaphorical, and
unique. Bonus: "loom" has connotations of something appearing/emerging ("looming
into view"), which fits a system that materializes a virtual hardware/software
environment.

---

## 10. Round 3  Research & Critical Analysis

### 10.1 sysmesh  System Mesh

**Namespace research:**
- No software projects named "sysmesh" found on GitHub or elsewhere.
- No conflicts in EDA, simulation, networking, or any other domain.
- "Service mesh" is a well-known concept in cloud-native infrastructure (Istio,
  Linkerd, Consul Connect)  this association is a *positive*, as it primes the
  audience to think "managed inter-process communication infrastructure."

| Aspect       | Assessment |
|-------------|-----------|
| **Pros**    | **Zero conflicts.** Self-documenting  "system mesh" immediately conveys interconnected simulation nodes. The service-mesh association is helpful, not harmful: your framework *is* essentially a simulation service mesh (managed communication, routing, resource sharing between processes). Rolls off the tongue well. Short (7 chars). Clean CLI: `sysmesh launch`, `sysmesh node add`, `sysmesh status`. Natural extension vocabulary: mesh nodes, mesh links, mesh topology. |
| **Cons**    | "Mesh" implies a specific topology (full/partial mesh), which may not always describe the actual connection pattern (could be star, ring, tree). Minor concern  "service mesh" is strongly associated with Kubernetes/cloud-native, which could slightly mislead people unfamiliar with the project. |
| **Risk**    | **VERY LOW**  No conflicts whatsoever. |

### 10.2 sysnet  System Network

**Namespace research:**
- No simulation tools named "sysnet" found.
- "SysNet" appears as the name of a few academic research labs (e.g., Microsoft
  Research SysNet group, various university labs). These are *groups*, not software
  tools, so no direct conflict.
- Some minor IT/networking company names use "Sysnet" but none in
  simulation/EDA.

| Aspect       | Assessment |
|-------------|-----------|
| **Pros**    | Very short (6 chars). Intuitive  "system network" is immediately clear. Good CLI feel (`sysnet run`, `sysnet connect`). The "net" suffix clearly conveys the connected, networked nature. |
| **Cons**    | Sounds like a generic networking tool or sysadmin utility. A new user might expect it to be about network administration/monitoring rather than HW/SW simulation. The word "network" is so overloaded in computing that it doesn't strongly signal *simulation*. Several research labs use "SysNet" as their group name, which adds mild search noise. |
| **Risk**    | **LOW**  No tool conflicts, but mild ambiguity about what it does. |

### 10.3 sysloom  System Loom

**Namespace research:**
- No software projects, tools, or libraries named "sysloom" found anywhere.
- No GitHub repositories, no academic papers, no commercial products.
- "Loom" as a standalone project name is used by a few things (Loom video
  recording, Java Project Loom for virtual threads) but "sysloom" is completely
  clear.

| Aspect       | Assessment |
|-------------|-----------|
| **Pros**    | **Completely unique**  zero hits anywhere. Evocative and memorable: a loom weaves individual threads into a unified fabric, exactly as this framework weaves simulation nodes into a coherent system. The metaphor is rich and extends naturally: threads (FIFO connections), warps (node groups), weaving (orchestration), fabric (the running system). Rolls off the tongue better than sysfab. Distinctive enough to be immediately searchable. Short (7 chars). |
| **Cons**    | Abstract  requires a moment's explanation for someone encountering it cold (same issue as simforge, but the metaphor is stronger and more internally consistent). "Loom" might evoke textile manufacturing rather than technology for some audiences. Less immediately self-documenting than sysmesh or syssim. |
| **Risk**    | **VERY LOW**  Essentially zero conflicts anywhere. |

### Quick note on sysnode

**sysnode** was mentioned as an option. Research shows no conflicts, but it has
a weakness: "node" is the most generic term possible in distributed systems. It
doesn't convey the *interconnection* aspect you want. It names a component rather
than the system. `sysmesh`, `sysnet`, and `sysloom` all emphasize the *connections
between* nodes, which is the actual value of the framework.

---

## 11. Final Combined Ranking (All 10 Candidates)

| Rank | Name         | Score  | Rationale |
|:----:|-------------|:------:|-----------|
| 1    | **sysmesh**  | 9.5/10 | Best overall. "System mesh" is self-documenting, rolls off the tongue, zero conflicts, and the service-mesh association is a positive signal (managed inter-process communication). Natural vocabulary for sub-commands and concepts. |
| 2    | **sysloom**  | 9/10   | Most distinctive and memorable. Rich, consistent metaphor. Zero conflicts. Slightly behind sysmesh only because it requires a beat of explanation  but it *rewards* that explanation with a "that's perfect" moment. |
| 3    | **syssim**   | 8.5/10 | Best "says what it does" name. No conflicts. Falls behind the network/graph-oriented names because it doesn't convey the interconnection/topology aspect. |
| 4    | **simforge** | 8/10   | Brandable and unique but doesn't lean into the system/network framing you prefer. |
| 5    | **sysnet**   | 7.5/10 | Clean and short, but sounds like a networking tool rather than a simulation framework. "Net" is too overloaded. |
| 6    | **sysfab**   | 7/10   | Right concept (fabric) but doesn't roll off the tongue (per your feedback). |
| 7    | **meshsim**  | 6.5/10 | Decent but word order feels backwards  describes a "mesh simulator" rather than a "system mesh." |
| 8    | **distsim**  | 6/10   | Safe, forgettable. |
| 9    | **nsim**     | 4/10   | Synopsys nSIM collision. |
| 10   | **ssim**     | 2/10   | SSIM image-metric collision. Unusable. |

---

## 12. Recommendation

### Top pick: **sysmesh**

`sysmesh` hits the sweet spot:
- **Self-documenting:** "system mesh" immediately tells you it's about
  interconnected system components.
- **Correct metaphor:** A mesh is a network of interconnected nodes  exactly
  what the framework creates. The service-mesh analogy (Istio, Linkerd) primes
  people to think "managed communication layer between processes."
- **Resource sharing fits naturally:** Memory page checkout, shared state, and
  coordinated resources are all services the mesh provides to its nodes.
- **Clean CLI:** `sysmesh launch`, `sysmesh node add`, `sysmesh status`,
  `sysmesh connect`.
- **Zero conflicts.** Easy to search, easy to register, easy to remember.

### Runner-up: **sysloom**

If you want something more *distinctive* and are willing to trade a small amount
of self-documentation for memorability, `sysloom` is exceptional. The weaving
metaphor is internally consistent and surprisingly deep:
- Threads = FIFO connections
- Warp = node groups / machine boundaries
- Weave = orchestration / the act of connecting nodes
- Fabric = the running distributed system

Either choice will serve the project well for years.
