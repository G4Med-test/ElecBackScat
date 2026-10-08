#!/usr/bin/env python

# ElecBackScat portal parser: metadata() reads the macro, parse() the per-run
# lines appended to res.dat by UserRunAction::EndOfRunAction. One macro holds a
# fixed energy scan (one /run/beamOn per energy) at one material/angle/physics
# list; each line is one point of the scan.
import math
import os

from geantval import energy_mev, getJSON, one_command

MODELS = {"emstandard_opt0", "emstandard_opt1", "emstandard_opt2", "emstandard_opt3",
          "emstandard_opt4", "standardSS", "standardSSM", "standardWVI", "standardGS",
          "empenelope", "emlivermore", "emlowenergy"}


def extract_runs(filename, expected_points):
    rows = []
    with open(filename) as myfile:
        for line in myfile:
            fields = line.split()
            if len(fields) != 7:
                raise ValueError("Expected 7 columns in res.dat: " + line)
            _material, energy, angle, en_alb, en_alb_err, num_alb, num_alb_err = fields
            rows.append((float(energy), float(angle), float(en_alb), float(en_alb_err),
                        float(num_alb), float(num_alb_err)))
    if len(rows) != expected_points:
        raise ValueError("res.dat has %d runs, expected %d" % (len(rows), expected_points))
    return rows


def parse(job):
    filepath = os.path.join(job["path"], "res.dat")
    rows = extract_runs(filepath, job["EXPECTED_POINTS"])
    energies = [r[0] for r in rows]
    if any(not math.isclose(e, expected, rel_tol=1e-6) for e, expected in zip(energies, job["ENERGIES"])):
        raise ValueError("res.dat energies do not match the macro")
    if any(not math.isclose(r[1], job["ANGLE"], abs_tol=1e-6) for r in rows):
        raise ValueError("res.dat angle does not match the macro")

    params = [{"names": "angle", "values": job["ANGLE"]}]

    yield getJSON(job, "chart",
                 mctool_name="GEANT4",
                 mctool_model=job["MODEL"],
                 observableName="Backscattered energy coefficient",
                 targetName=job["MATERIAL"],
                 beamParticle="e-",
                 beamEnergies=energies,
                 parameters=params,
                 secondaryParticle="None",
                 title="Backscattered energy coefficient",
                 xAxisName="E, MeV",
                 yAxisName="Backscattered energy coefficient",
                 xValues=energies,
                 yValues=[r[2] for r in rows],
                 yStatErrorsPlus=[r[3] for r in rows],
                 yStatErrorsMinus=[r[3] for r in rows])

    yield getJSON(job, "chart",
                 mctool_name="GEANT4",
                 mctool_model=job["MODEL"],
                 observableName="Backscattered electron number coefficient",
                 targetName=job["MATERIAL"],
                 beamParticle="e-",
                 beamEnergies=energies,
                 parameters=params,
                 secondaryParticle="None",
                 title="Backscattered electron number coefficient",
                 xAxisName="E, MeV",
                 yAxisName="Backscattered electron number coefficient",
                 xValues=energies,
                 yValues=[r[4] for r in rows],
                 yStatErrorsPlus=[r[5] for r in rows],
                 yStatErrorsMinus=[r[5] for r in rows])


def metadata(commands):
    model = one_command(commands, "/testem/phys/addPhysics")
    if model not in MODELS:
        raise ValueError("Unsupported physics list for this validation: " + model)

    angle_value, angle_unit = one_command(commands, "/beam/angle").split()
    if angle_unit != "deg":
        raise ValueError("Expected /beam/angle in deg, got " + angle_unit)

    energies = []
    energy = None
    for command, value in commands:
        if command == "/beam/energy":
            energy = energy_mev(value)
        if command == "/run/beamOn":
            if energy is None or int(value) <= 0:
                raise ValueError("Each beamOn needs an explicit energy and positive event count")
            energies.append(energy)
    if not energies:
        raise ValueError("No energy scan in macro")

    return {"TEST": "ElecBackScat",
            "MODEL": model,
            "MATERIAL": one_command(commands, "/detector/material").removeprefix("G4_"),
            "ANGLE": float(angle_value),
            "EXPECTED_POINTS": len(energies), "ENERGIES": energies}
