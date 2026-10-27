# Portal JSON parser

Adapted from `geant-config-generator/tests/geant4/ElecBackScat/parser.py` at
commit `0bf42953c9c98ac6ecccf077e7c7fe2c4ceb7307`, with queue discovery replaced
by the shared ci-workflows exporter.

Each macro is a fixed energy scan (one `/run/beamOn` per energy, 1.033 down to
0.032 MeV) at one material, incidence angle and physics list.
`UserRunAction::EndOfRunAction` appends one line per run to `res.dat`:
`<material> <energy MeV> <angle deg> <energy albedo> <energy albedo error>
<number albedo> <number albedo error>` (the energy and number backscatter
coefficients, i.e. the fraction of the incident electron's energy, and the
fraction of incident electrons, reflected back out of the target).
`metadata()` derives the physics list, material, angle and the expected energy
scan from the macro; `parse()` reads `res.dat` and checks its energies and
angle against the macro before exporting two charts (energy and number
coefficient vs. beam energy, with the angle as a parameter), exactly as the
original parser did.

`config.json` selects the straight-on (0°) `emstandard_opt0` run for each of the
seven materials this test ships reference data for (Aluminium, Beryllium,
Carbon, Molybdenum, Tantalum, Titanium, Uranium — spelled as in the original
directory names). `macro/<Material>/` also holds the same scan at 15°, 30°,
45°, 60°, 75° (83.5° for Beryllium) and with `standardGS`, `standardSS` and
`emstandard_opt3`, for manual or Padova runs; they are not run automatically.
Experimental reference data (Lockwood, Miller & Halbleib, SAND80-1968 UC-34a)
is in `geant-validation-tests/src/ElecBackScat/data`, not copied into this
repository.

Each of the 172 copied macros had the original `/testem/phys/addPhysics
PHYSLIST` line removed: an unexpanded template placeholder left over in every
committed macro (immediately followed by the real, concrete
`/testem/phys/addPhysics <model>` line), harmless at run time but incompatible
with `metadata()`'s one-value-per-command reading of the macro.

The pipeline uploads `validation-json/results.json` (an array of plot objects)
and `plots/*.json` (the original one-object-per-file format), plus raw artifacts.
See [ci-workflows](https://github.com/G4Med-test/ci-workflows) for local CLI usage.
