Info<< "Reading field p\n" << endl;
volScalarField p
(
    IOobject
    (
        "p",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);


Info<< "Reading field U\n" << endl;
volVectorField U
(
    IOobject
    (
        "U",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);


volScalarField magtTau
(
    IOobject
    (
        "magtTau",
        runTime.timeName(),
        mesh,
        IOobject::READ_IF_PRESENT,
        IOobject::AUTO_WRITE
    ),
	mesh,
	//dimensionedScalar("magtTau", dimensionSet(0,1,-2,0,0,0,0), 0.0) // Dummy initialization values
	// kin. visk * shear rate
	dimensionedScalar("magtTau", dimensionSet(0,2,-2,0,0,0,0), 0.0) // Dummy initialization values
);


#include "createPhi.H"


singlePhaseTransportModel fluid(U, phi);


label pRefCell = 0;
scalar pRefValue = 0.0;
setRefCell(p, mesh.solutionDict().subDict("PISO"), pRefCell, pRefValue);
mesh.setFluxRequired(p.name());
