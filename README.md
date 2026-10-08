# ElecBackScat

**Electron energy and number backscatter coefficients from cylindrical targets**,
validated against the calorimetric measurements of Lockwood, Miller & Halbleib
(SAND80-1968 UC-34a). Authors: paolo.dondero@cern.ch, Anton.Lechner@cern.ch.

[![CI Pipeline](https://github.com/G4Med-test/ElecBackScat/actions/workflows/ci.yml/badge.svg)](https://github.com/G4Med-test/ElecBackScat/actions/workflows/ci.yml)

---

## 🔬 What this test does

A mono-energetic electron beam hits a cylindrical target (material, length and
radius set via `/detector/material`, `/detector/length`, `/detector/radius`) at
a given incidence angle (`/beam/angle`). For every primary that re-crosses the
entrance boundary, the fraction of its energy and the fraction of incident
electrons backscattered out of the target are scored. A macro scans a fixed set
of beam energies (1.033 down to 0.032 MeV, one `/run/beamOn` per energy), and
`UserRunAction` appends one summary line per energy to `res.dat`.

Physics lists compared (`PhysicsList::AddPhysicsList`): `standardGS`
(Goudsmit-Saunderson), `standardSS` (single Coulomb scattering),
`emstandard_opt0` and `emstandard_opt3`, plus `emstandard_opt1/opt2/opt4`,
`standardSSM`, `standardWVI`, `empenelope`, `emlivermore` and `emlowenergy`,
also supported by `PhysicsList` but with no macro here.

## 🛠️ Fill in the repository (from the template)

| Path | What it contains |
| --- | --- |
| `main.cc`, `src/`, `include/` | The Geant4 application, imported unchanged from `geant-validation-tests/src/ElecBackScat` (it already used the standard single-macro-argument invocation). |
| `macro/unit.mac` | One-event smoke test (Aluminium, `standardGS`, 1.033 MeV, 0°). |
| `macro/<Material>/*.mac` | The original per-material, per-angle, per-physics-list macros (Aluminium, Beryllium, Carbon, Molybdenum, Tantalum, Titanium, Uranium), each with its unexpanded `/testem/phys/addPhysics PHYSLIST` template leftover removed. |
| `validation/config.json` | The 0° `emstandard_opt0` run of all seven materials; the other angles and physics lists are available in `macro/` but not run automatically. |
| `validation/parser.py` | Reads `res.dat` and exports the energy and number backscatter coefficients vs. beam energy. |

See [`validation/README.md`](validation/README.md) for the parser's provenance
and exact behaviour.

## 🚀 How to run the container

```bash
apptainer build --build-arg PROJECT_NAME=ElecBackScat ElecBackScat.sif Apptainer.def
apptainer run ElecBackScat.sif macro/Aluminium/00deg_emstandardOpt0.mac
```

No Geant4 datasets are needed for this test, but the shared container still
mounts `/g4data` as usual.

See the top-level [template README](https://github.com/G4Med-test/template#readme)
for the full local workflow (pulling the CI-built container and running
`ci-workflows/validation/export.py`).

## 📦 Container on GHCR

[![Container on GHCR](https://img.shields.io/badge/Container-GHCR-blue?logo=github)](https://github.com/orgs/G4Med-test/packages?repo_name=ElecBackScat)

```bash
apptainer pull oras://ghcr.io/g4med-test/elecbackscat:<tag>
```
> Replace `<tag>` with the desired release tag or commit hash.

## ✅ GitHub Actions workflow

Defined in the shared [`ci-workflows`](https://github.com/G4Med-test/ci-workflows)
repository and invoked from [`.github/workflows/ci.yml`](.github/workflows/ci.yml).
