---
title: "Detecting Silent Errors In The Wild Combining Two Novel Approaches To Quickly Detect Silent Data Corruptions At Scale"
pdf_url: "[[detecting-silent-errors-in-the-wild-combining-two-novel-approaches-to-quickly-detect-silent-data-corruptions-at-scale.pdf]]"
---
This paper by Meta discusses detecting Silent Data corruptions in production to catch faulty CPUs and other parts.

## Silent Errors

- Silent errors don't trigger machine checks, ECC errors, or log at all, but instead quietly produce wrong answers.
- Meta observes these at scale, with an empirical rate of around 1 in 1000 devices, compared to the traditional 1 in 1000000.
- These faults can propagate across services and cause data loss or other weird behavior.

## Testing

The paper notes the testing funnel:

1. Design & Verification
2. Post-silicon validation
3. Manufacturer testing
4. Integrator testing (at rack-level)
5. Infrastructure intake/burn-in (running workloads before prod)
6. Infrastructure fleet testing (testing devices after deployment, while in fleet)

## SDC problems

Detection is hard because of:

1. Some operations fail for only specific bit patterns.
2. Electrical variations: changes in voltage, frequency, current, can trigger or hide faults
3. Environment: temperature, humidity, hotspots can expose defects
4. Silicon aging: devices degrade over time.

So, continuous testing in prod is the only way to explore this state space.

## How Meta tests

1. Out of production testing (Fleetscanner)
	- Runs a suite of tests when machines are **drained**, i.e. not in the fleet, for upgrades or repair.
	- This is an extensive set of tests while the server is idle.
	- The test suite is incrementally added to based on failures meta sees.
2. In-production testing (Ripple)
	- Tests are colocated with normal workloads and run in bursts (~ms scale).
	- Test sequences are meant to be **performance-aware** so as not to degrade workloads
	- The footprint of these tests is observed to be less than a certain threshold, with A/B shadow testing to make sure there's little impact.
	- This testing is always on, with more testing that occurs during times of less work.

## Results

For Fleetscanner, which is more extensive:

- **93%** of all SDC-affected machines are found.
- **23%** of all detectable SDCs are only seen by Fleetscanner.
With the con that it takes 6 months to reach full fleet coverage.

For Ripple, which is always on:

- Detects **70%** of SDC faults, within 15 days. 
- **7%** unique coverage, faults that only show up when tests are interleaved with workloads.

## Discussion

- Silent data corruption is a big deal
- You can't catch all errors before sending out to your fleet.
- Out of production and in-production testing can detect most SDCs.