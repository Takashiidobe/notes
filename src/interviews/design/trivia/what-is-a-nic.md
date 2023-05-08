# What is a NIC?

A Network Interface Card (NIC) implements the Physical layer (L1) and part of the data link layer (L2).

It processes packets to and from the CPU, by turning packets -> bits through PCIe on Egress, and bits -> Packets over PCIe.

| Part    | End Host    |
|---------|-------------|
| CPU     | Application |
| CPU     | Transport   |
| CPU     | Network     |
| CPU/NIC | Data Link   |
| NIC     | Physical    |

However, CPUs haven't gotten faster at processing packets (Linux can process about 1M pps), but links are around 400 Gbps now, and they're lagging behind NICs speed.

## Smart NICs

Smart NICs eschew that with a Programmable Domain-Specific Hardware Processor on the NIC.

Currently, they are generally

1. Field Programmable Gate Arrays (FPGAs)
2. Multi-core Systems on chip (SoCs)

FPGAs have small configurable logic and memory boards, which can be assembled to meet a certain workload. This requires a bit of a different model of programming than other popular software programming.

SoCs have a small computer on a chip, which has small processing cores and a memory hierarchy, and moreso resembles a computer.

|                        | FPGAs                           | Multi-Core SoCs                |
|------------------------|---------------------------------|--------------------------------|
| Hardware Architecture  | Reconfigurable                  | Fixed                          |
| Programming Model      | Verilog                         | C-like                         |
| Performance            | Higher throughput lower latency | Lower throughput higer latency |
