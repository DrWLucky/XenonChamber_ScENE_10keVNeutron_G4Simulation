    
//#include "DetectorConstruction.hh" 
//#include "SCENE_TwoPhasePrototype_CoincidentGeometry.hh"
#include "UCLA_XenonChamber_Geometry.hh"
#include "BeamTestSensitiveDetector.hh"
#include "PeripherySensitiveDetector.hh"

#include "G4Polyhedra.hh"
#include "G4Polycone.hh"

#include "G4Tubs.hh"
#include "G4Transform3D.hh"
#include "G4RotationMatrix.hh"
#include "G4Box.hh"
#include "G4Colour.hh"
#include "G4LogicalVolume.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"     
#include "G4PVParameterised.hh"
#include "G4PVPlacement.hh"
#include "G4RunManager.hh"
#include "G4Tubs.hh"
#include "G4SubtractionSolid.hh"
#include "G4UnionSolid.hh"
#include "G4VisAttributes.hh"

#include "G4SDManager.hh"
#include "stdlib.h"
#include "string.h"
#include <cmath>




DetectorConstruction::DetectorConstruction()
  :fpWorldLogical(0)
  ,fpWorldPhysical(0)
{}

DetectorConstruction::~DetectorConstruction() {}



G4VPhysicalVolume*DetectorConstruction::Construct()
{
  // Material Definition
  DefineMaterials();  

  // Geometry Definition
  SetupGeometry();   

  // Return world volume
  return fpWorldPhysical;  
}







void DetectorConstruction::DefineMaterials()
{
  G4String symbol;             
  G4double a, z, density;     
  G4int ncomponents;
  G4double fractionmass;
  
    //================================== elements ===================================
  new G4Material(     "Silicon",    z=14., a=28.0855*g/mole,  density=2.330*g/cm3);
  new G4Material(        "Iron",    z=26., a=55.845*g/mole,   density=7.87*g/cm3);
  new G4Material(    "Titanium",    z=22., a=47.90*g/mole,    density=4.540*g/cm3);  
  new G4Material( "LiquidArgon",    z=18,  a=39.948*g/mole,   density=1.43*g/cm3);
  new G4Material(    "GasArgon",    z=18,  a=39.948*g/mole,   density=1.449e-3*g/cm3);
  new G4Material(      "Copper",    z=29,  a=63.546*g/mole,   density=8.94*g/cm3);
  new G4Material(   "Aluminium",    z=13,  a=26.98*g/mole,    density=2.70*g/cm3);
  new G4Material(    "Tungsten",    z=74,  a=183.85*g/mole,   density=19.25*g/cm3);
  
    
	G4Element *H  = new G4Element("Hydrogen",   "H",  1.,  1.0079*g/mole);
	G4Element *C  = new G4Element("Carbon",     "C",  6.,  12.011*g/mole);
	G4Element *N  = new G4Element("Nitrogen",   "N",  7.,  14.007*g/mole);
	G4Element *O  = new G4Element("Oxygen",     "O",  8.,  15.999*g/mole);
	G4Element *F  = new G4Element("Fluorine",   "F",  9.,  18.998*g/mole);
	G4Element *Si = new G4Element("Silicon",    "Si", 14., 28.086*g/mole);
	G4Element *Cr = new G4Element("Chromium",   "Cr", 24., 51.996*g/mole);
	G4Element *Mn = new G4Element("Manganese",  "Mn", 25., 54.938*g/mole);
	G4Element *Fe = new G4Element("Iron",       "Fe", 26., 55.85*g/mole);   //-- density 7.874*g/cm3 --
	G4Element *Ni = new G4Element("Nickel",     "Ni", 28., 58.693*g/mole);  //-- density 8.9*g/cm3 --
    G4Element *Mo = new G4Element("Molybdenum", "Mo", 42., 95.96*g/mole);   //-- density 10.28*g/cm3 --

    G4Element *Xe = new G4Element("Xenon",     "Xe", 54., 131.293*g/mole);

    //G4Element *Al = new G4Element("Aluminium", "Al", 13., 26.982*g/mole);
    //G4Element *Cu = new G4Element("Copper",    "Cu", 29., 63.546*g/mole);
	//G4Element *Pb = new G4Element("Lead",      "Pb", 82., 207.2*g/mole);
	//G4Element *Gd = new G4Element("Gadolinium","Gd", 64., 157.25*g/mole);

    
    // xenon
    G4Material* LXe = new G4Material("LiquidXenon", 2.90*g/cm3, 1, kStateLiquid);
    LXe->AddElement(Xe, 1);
    
    G4Material* GXe = new G4Material("GasXenon", 13.5*mg/cm3, 1, kStateGas); //--- 178.*kelvin, 1.4*bar ---
    GXe->AddElement(Xe, 1);
    
    
// PTFE
    G4Material* Teflon = new G4Material("Teflon", 2.2*g/cm3, 2, kStateSolid);
	Teflon->AddElement(C, 0.240183);
	Teflon->AddElement(F, 0.759817);
    
// polyethylene 
    G4Material* polyethylene = new G4Material("polyethylene", 0.94*g/cm3, 2, kStateSolid);
    polyethylene->AddElement(C, 1);
    polyethylene->AddElement(H, 2);
    

    
    
    //  quartz
    G4Material* quartz = new G4Material("quartz", 2.201*g/cm3, 2, kStateSolid);
    quartz->AddElement(Si, 1);
    quartz->AddElement(O, 2);
    
    
    // Stainless Steel
    G4Material *SS304LSteel = new G4Material("SS304LSteel", 8.00*g/cm3, 5, kStateSolid);
	SS304LSteel->AddElement(Fe, 0.65);
	SS304LSteel->AddElement(Cr, 0.20);
	SS304LSteel->AddElement(Ni, 0.12);
	SS304LSteel->AddElement(Mn, 0.02);
	SS304LSteel->AddElement(Si, 0.01);


    /*
    // False Stainless Steel
    G4Material *SS_Pole = new G4Material("SS_Pole", 0.80*g/cm3, 5, kStateSolid);
	SS_Pole->AddElement(Fe, 0.65);
	SS_Pole->AddElement(Cr, 0.20);
	SS_Pole->AddElement(Ni, 0.12);
	SS_Pole->AddElement(Mn, 0.02);
	SS_Pole->AddElement(Si, 0.01);
    
    
    // paraffin
    G4Material* paraffin = new G4Material("paraffin", 0.9*g/cm3, 2, kStateSolid);
    paraffin->AddElement(C, 1);
    paraffin->AddElement(H, 2);
    
    */
    
    
    // 316L Steel
    G4Material *SS316LSteel = new G4Material("SS316LSteel", 7000/12.7/51.6/5.5*g/cm3, 5, kStateSolid);      //-- Heat Exchanger 127W x 516H x 55D-----
	SS316LSteel->AddElement(Fe, 0.67);
	SS316LSteel->AddElement(Cr, 0.17);
	SS316LSteel->AddElement(Ni, 0.12);
	SS316LSteel->AddElement(Mn, 0.02);
	SS316LSteel->AddElement(Mo, 0.02);
    
    
    
// special Kovar (Co free material), the 3" PMT Shell Material, based on assumption of 8.35*g/cm3 and two components Fe and Ni only
// -- x+y=1--
// -- 7.874*x + 8.9*y = 8.35 --
    
    G4Material *Kovar = new G4Material("Kovar",8.35*g/cm3, 2, kStateSolid);
    Kovar->AddElement(Ni, 0.464);
    Kovar->AddElement(Fe, 0.536);
 
    
  //EJ301 (the liquid scintillator for neutron detector)
    G4Material* EJ301 = new G4Material("EJ301", density=0.874*g/cm3, 2, kStateLiquid);
    EJ301->AddElement(H, 0.548);
    EJ301->AddElement(C, 0.452);
    
  // Air
  G4Material* Air = new G4Material("Air", density= 1.290*mg/cm3, ncomponents=2);
  Air->AddElement(N, fractionmass=0.7);
  Air->AddElement(O, fractionmass=0.3);
  
  // Define vacuum
  G4Material* Vacuum = new G4Material("Vacuum", density= 1.e-6*g/cm3, ncomponents=1, kStateGas, STP_Temperature, 2.e-7*bar);
  Vacuum->AddMaterial(Air, fractionmass=1.);
  
  // Dump material information
  //G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}








void DetectorConstruction::SetupGeometry()
{
  
    
         //G4Material* air = G4Material::GetMaterial("Air");
         G4Material* LXe = G4Material::GetMaterial("LiquidXenon");
         G4Material* GXe = G4Material::GetMaterial("GasXenon");
         G4Material*  Al = G4Material::GetMaterial("Aluminium");
      G4Material* quartz = G4Material::GetMaterial("quartz");
       G4Material* EJ301 = G4Material::GetMaterial("EJ301");
        G4Material* PTFE = G4Material::GetMaterial("Teflon");
       G4Material* steel = G4Material::GetMaterial("SS304LSteel");
  //G4Material* pole_steel = G4Material::GetMaterial("SS_Pole");
      G4Material* vacuum = G4Material::GetMaterial("Vacuum");
G4Material* polyethylene = G4Material::GetMaterial("polyethylene");
      G4Material* copper = G4Material::GetMaterial("Copper");
       G4Material* Kovar = G4Material::GetMaterial("Kovar");
      //G4Material* SS316L = G4Material::GetMaterial("SS316LSteel");  
    //G4Material* Tungsten = G4Material::GetMaterial("Tungsten");
    //G4Material* paraffin = G4Material::GetMaterial("paraffin");

   
    
    /*  //--- Cylindral world volume-----
    G4double world_Radius = 3*m;
    G4double world_halfHeight = 1.5*m;

 G4Tubs* worldSolid = new G4Tubs("World_Solid", 0*m, world_Radius, world_halfHeight, 0*deg, 360*deg);
     fpWorldLogical = new G4LogicalVolume(worldSolid, air, "World_Logical");
    fpWorldPhysical = new G4PVPlacement(0, G4ThreeVector(), fpWorldLogical, "World_Physical", 0, false, 0);
    */
    
    
    
    G4double world_halfLength = 2*m;
    
    G4Box* worldSolid = new G4Box("World_Solid", world_halfLength, world_halfLength, world_halfLength);
       fpWorldLogical = new G4LogicalVolume(worldSolid, vacuum, "World_Logical");
      fpWorldPhysical = new G4PVPlacement(0, G4ThreeVector(), fpWorldLogical, "World_Physical", 0, false, 0);

    
    
    //---------------------------------------------
    /*
     
     */
    //---------------------------------------------
    
    
    
    
    // the Aluminum Frame Color 
    //G4VisAttributes* Al_Color = new G4VisAttributes(G4Colour::Black());
    G4VisAttributes* Al_Color = new G4VisAttributes(G4Colour(0.4, 0.4, 0.4, 0.));
    Al_Color->SetForceSolid(true);
    
    
    // Color for EJs
    //G4VisAttributes* EJColor = new G4VisAttributes(G4Colour(0.1,0.8,0.1,0.1));
    //EJColor->SetForceSolid(false);
    //EJColor->SetForceWireframe(false);
    
    
    /*
     
     August 23rd 2013
     
     SSDewar center is referred to the center of inner SS volume (24" height volume without considering the CF600 flange).
     
     The 3-inch PMT is based on the geometry from ScENE
     
     
     
    The TPC center is an variable that's able to move in zAxis, The Center is assumed to be in the center of SSDewar
     
    in TPC, the center is the center of Active LXe.
     
    Total active region: 0.35" (Xenon Gas) + 3" (Xenon Liquid). But the gas pocket length is able to vary. 
        
    5.mm is currently used.
     
     */

    
    
    
    
    
    
    //------------------ Cryofab SS Dewar and 6" flange --------------------


    //--- SS Dewar ---
    const G4double      SSDewar_OuterWall_OuterRadius =  4.6/2*25.4*mm;     //-- 4.6" OD---
    const G4double      SSDewar_OuterWall_Thickness   =   0.05*25.4*mm;     //-- 0.05"---
    const G4double      SSDewar_OuterWall_TotHeight   =     27*25.4*mm;     //-- 30" height---
    
    const G4double      SSDewar_InnerWall_InnerRadius = 3.93/2*25.4*mm;     //-- 4.6" OD---
    const G4double      SSDewar_InnerWall_Thickness   =   0.02*25.4*mm;     //-- 0.05"---
    const G4double      SSDewar_InnerWall_InnerDepth  =     24*25.4*mm;     //-- 30" height---
    
    
    const G4double      SSDewar_Center_xPos = 0.*mm;
    const G4double      SSDewar_Center_yPos = 0.*mm;
    const G4double      SSDewar_Center_zPos = 0.*mm;

        
    
  ///*  
    //---CF600 Flange---
    const G4double      CF600Flange_OuterRadius = 5.97/2*25.4*mm; //-- 6" OD --
    const G4double      CF600Flange_TotHeight   = 0.78*25.4*mm;     //-- 0.78" thick --
    //------------------
    
    G4Tubs *SSInnerDewar = new G4Tubs("SSInnerDewar", SSDewar_InnerWall_InnerRadius, SSDewar_InnerWall_InnerRadius+SSDewar_InnerWall_Thickness, SSDewar_InnerWall_InnerDepth/2, 0.*deg, 360*deg);
    G4Tubs *SSOuterDewar = new G4Tubs("SSOuterDewar", SSDewar_OuterWall_OuterRadius-SSDewar_OuterWall_Thickness, SSDewar_OuterWall_OuterRadius, SSDewar_OuterWall_TotHeight/2, 0.*deg, 360*deg);

    G4Tubs *SSInnerDewar_BtmPlate = new G4Tubs("SSInnerDewar_BtmPlate", 0.*mm, SSDewar_InnerWall_InnerRadius+SSDewar_InnerWall_Thickness, SSDewar_InnerWall_Thickness/2, 0.*deg, 360*deg);
    G4Tubs *SSOuterDewar_BtmPlate = new G4Tubs("SSOuterDewar_BtmPlate", 0.*mm, SSDewar_OuterWall_OuterRadius, SSDewar_OuterWall_Thickness/2, 0.*deg, 360*deg);

    
    
    G4Tubs  *SSDewar_CF600FlangeRing = new G4Tubs("SSDewar_CF600FlangeRing", SSDewar_InnerWall_InnerRadius, CF600Flange_OuterRadius, CF600Flange_TotHeight/2, 0.*deg, 360*deg);
    G4Tubs  *SSDewar_CF600Flange = new G4Tubs("SSDewar_CF600Flange",  0.*mm, CF600Flange_OuterRadius,  CF600Flange_TotHeight/2, 0.*deg, 360*deg);


    
    G4LogicalVolume  *SSInnerDewar_Logical            = new G4LogicalVolume(SSInnerDewar,            steel, "SSInnerDewar_Logical");
    G4LogicalVolume  *SSOuterDewar_Logical            = new G4LogicalVolume(SSOuterDewar,            steel, "SSOuterDewar_Logical");
    G4LogicalVolume  *SSInnerDewar_BtmPlate_Logical   = new G4LogicalVolume(SSInnerDewar_BtmPlate,   steel, "SSInnerDewar_BtmPlate_Logical");
    G4LogicalVolume  *SSOuterDewar_BtmPlate_Logical   = new G4LogicalVolume(SSOuterDewar_BtmPlate,   steel, "SSOuterDewar_BtmPlate_Logical");
    G4LogicalVolume  *SSDewar_CF600FlangeRing_Logical = new G4LogicalVolume(SSDewar_CF600FlangeRing, steel, "SSDewar_CF600FlangeRing_Logical");
    G4LogicalVolume  *SSDewar_CF600Flange_Logical     = new G4LogicalVolume(SSDewar_CF600Flange,     steel, "SSDewar_CF600Flange_Logical");

    
    ///*
    new G4PVPlacement(0, G4ThreeVector(SSDewar_Center_xPos, SSDewar_Center_yPos, SSDewar_Center_zPos), SSInnerDewar_Logical, "SSInnerDewar_Physical", fpWorldLogical, true, 1, true);
    new G4PVPlacement(0, G4ThreeVector(SSDewar_Center_xPos, SSDewar_Center_yPos, SSDewar_Center_zPos-SSDewar_InnerWall_InnerDepth/2-SSDewar_InnerWall_Thickness/2), SSInnerDewar_BtmPlate_Logical, "SSInnerDewar_BtmPlate_Physical", fpWorldLogical, true, 1, true);

    new G4PVPlacement(0, G4ThreeVector(SSDewar_Center_xPos, SSDewar_Center_yPos, SSDewar_Center_zPos+SSDewar_InnerWall_InnerDepth/2-SSDewar_OuterWall_TotHeight/2), SSOuterDewar_Logical, "SSOuterDewar_Physical", fpWorldLogical, true, 1, true);
    new G4PVPlacement(0, G4ThreeVector(SSDewar_Center_xPos, SSDewar_Center_yPos, SSDewar_Center_zPos+SSDewar_InnerWall_InnerDepth/2-SSDewar_OuterWall_TotHeight-SSDewar_OuterWall_Thickness/2), SSOuterDewar_BtmPlate_Logical, "SSOuterDewar_BtmPlate_Physical", fpWorldLogical, true, 1, true);

    
    new G4PVPlacement(0, G4ThreeVector(SSDewar_Center_xPos, SSDewar_Center_yPos, SSDewar_Center_zPos+SSDewar_InnerWall_InnerDepth/2+CF600Flange_TotHeight/2), SSDewar_CF600FlangeRing_Logical, "SSDewar_CF600FlangeRing_Physical", fpWorldLogical, true, 1, true);
    new G4PVPlacement(0, G4ThreeVector(SSDewar_Center_xPos, SSDewar_Center_yPos, SSDewar_Center_zPos+SSDewar_InnerWall_InnerDepth/2+CF600Flange_TotHeight*1.5), SSDewar_CF600Flange_Logical, "SSDewar_CF600Flange_Physical", fpWorldLogical, true, 1, true);

    
    G4VisAttributes* SS_Color = new G4VisAttributes(G4Colour(0.2, 0.2, 0.2, 1.0));
    SS_Color->SetForceSolid(false);
    
               SSInnerDewar_Logical->SetVisAttributes(SS_Color);
               SSOuterDewar_Logical->SetVisAttributes(SS_Color);
      SSInnerDewar_BtmPlate_Logical->SetVisAttributes(SS_Color);
      SSOuterDewar_BtmPlate_Logical->SetVisAttributes(SS_Color);
    SSDewar_CF600FlangeRing_Logical->SetVisAttributes(SS_Color);
        SSDewar_CF600Flange_Logical->SetVisAttributes(SS_Color);
    
    //--------------------------------------------------------
   //*/
    
       
    
    
    
    
    
    
    
 ///*
    //-------------------------------------- TPC PTFE Parts  ------------------------------------
    
    
    const G4double TPC_OuterRadius           = 3.9/2*25.4*mm;     //--- Diameter 3.9" ---
    const G4double TPC_InnerRadius           = 3.0/2*25.4*mm;     //--- Diameter 3.0" ---
    
    const G4double TPC_TopPart_TotHeight     = 0.25*25.4*mm;      //--- 0.8"  total height,  ---
    
    const G4double TPC_FieldCage_OuterRadius = (3.5-2*0.04)/2*25.4*mm;    //--- Diameter 3.5" with the extrusion for copper ring(0.04")  ---
    const G4double TPC_FieldCage_TotHeight   = 3.35*25.4*mm;              //--- 3" (drift field) + 35" (extraction + electro-luminiscence field) ---
    
    const G4double PTFE_Sleeve_InnerRadius           = 3.5/2*25.4*mm;     //--- Diameter 3.5" with the extrusion for copper ring(0.04")  ---
    const G4double PTFE_Sleeve_PMTWindow_InnerRadius = 2.492/2*25.4*mm;  
    const G4double PTFE_Sleeve_PMTBody_InnerRadius   = 3.112/2*25.4*mm;  

    const G4double PTFE_Sleeve_TotLength             = (3.35+0.74+0.08+0.3)*25.4*mm;
    
    const G4double  TPC_Center_zAxis = 0.*mm; //--- the center of Active LXe (1.5" above the cathode mesh) ----
    
    
    
    G4Tubs                 *PTFE_FieldCage  = new G4Tubs("PTFE_FieldCage",   TPC_InnerRadius,  TPC_FieldCage_OuterRadius,  TPC_FieldCage_TotHeight/2, 0.*deg, 360*deg);

    G4LogicalVolume* PTFE_FieldCage_Logical = new G4LogicalVolume(PTFE_FieldCage,	 PTFE,  "PTFE_FieldCage_Logical");

    new G4PVPlacement(0, G4ThreeVector(0, 0, (TPC_FieldCage_TotHeight/2-1.5*25.4*mm)), PTFE_FieldCage_Logical, "PTFE_FieldCage_Physical",  fpWorldLogical,  true,  1,  true);

    

       
    G4Tubs             *PTFE_TopPMT_Part  = new G4Tubs("PTFE_TopPMT_Part",   0.*mm,  TPC_OuterRadius,  TPC_TopPart_TotHeight/2, 0.*deg, 360*deg);

    G4Box                      *PMT_Hole  = new G4Box("PMT_Hole", 0.87/2*25.4*mm,  0.87/2*25.4*mm,  1*25.4*mm);

    
    const G4double TopPMT_FullSpacing = (0.19+0.87)*25.4*mm;
    
    G4SubtractionSolid* PTFE_TopPMT_temp1 = new G4SubtractionSolid("PTFE_TopPMT_temp1", PTFE_TopPMT_Part, PMT_Hole, 0, G4ThreeVector(0.,0.,0.) );

    G4SubtractionSolid* PTFE_TopPMT_temp2 = new G4SubtractionSolid("PTFE_TopPMT_temp2", PTFE_TopPMT_temp1, PMT_Hole, 0, G4ThreeVector(TopPMT_FullSpacing, 0., 0.) );

    G4SubtractionSolid* PTFE_TopPMT_temp3 = new G4SubtractionSolid("PTFE_TopPMT_temp3", PTFE_TopPMT_temp2, PMT_Hole, 0, G4ThreeVector(-TopPMT_FullSpacing, 0., 0.) );

    G4SubtractionSolid* PTFE_TopPMT_temp4 = new G4SubtractionSolid("PTFE_TopPMT_temp4", PTFE_TopPMT_temp3, PMT_Hole, 0, G4ThreeVector(-TopPMT_FullSpacing/2, -TopPMT_FullSpacing/2, 0.) );

    G4SubtractionSolid* PTFE_TopPMT_temp5 = new G4SubtractionSolid("PTFE_TopPMT_temp5", PTFE_TopPMT_temp4, PMT_Hole, 0, G4ThreeVector(TopPMT_FullSpacing, TopPMT_FullSpacing, 0.) );
    
    G4SubtractionSolid* PTFE_TopPMT_temp6 = new G4SubtractionSolid("PTFE_TopPMT_temp6", PTFE_TopPMT_temp5, PMT_Hole, 0, G4ThreeVector(-TopPMT_FullSpacing, TopPMT_FullSpacing, 0.) );
    
    G4SubtractionSolid* PTFE_TopPMT_Holder = new G4SubtractionSolid("PTFE_TopPMT_Holder", PTFE_TopPMT_temp6, PMT_Hole, 0, G4ThreeVector(TopPMT_FullSpacing, -TopPMT_FullSpacing, 0.) );
    
    G4LogicalVolume* PTFE_TopPMT_Holder_Logical = new G4LogicalVolume(PTFE_TopPMT_Holder,	 PTFE,  "PTFE_TopPMT_Holder_Logical");

    
    new G4PVPlacement(0, G4ThreeVector(0, 0, (TPC_Center_zAxis+(1.5+0.35)*25.4*mm+TPC_TopPart_TotHeight/2)), PTFE_TopPMT_Holder_Logical, "PTFE_TopPMT_Holder_Physical",  fpWorldLogical,  true,  1,  true);

    
   

    
    
    const G4int     PTFE_Sleeve_zPlaneNbr = 7;

    const G4double  PTFE_Sleeve_zPlane[PTFE_Sleeve_zPlaneNbr] = {0.*mm, -(3.35*25.4)*mm, -(3.35*25.4)*mm, -(3.35+0.74)*25.4*mm, -(3.35+0.74+0.08)*25.4*mm, -(3.35+0.74+0.08)*25.4*mm, -PTFE_Sleeve_TotLength};

    const G4double  PTFE_Sleeve_rInner[PTFE_Sleeve_zPlaneNbr] = {PTFE_Sleeve_InnerRadius, PTFE_Sleeve_InnerRadius, TPC_InnerRadius, PTFE_Sleeve_PMTWindow_InnerRadius, PTFE_Sleeve_PMTWindow_InnerRadius, PTFE_Sleeve_PMTBody_InnerRadius, PTFE_Sleeve_PMTBody_InnerRadius};
    
    const G4double  PTFE_Sleeve_rOuter[PTFE_Sleeve_zPlaneNbr] = {TPC_OuterRadius, TPC_OuterRadius, TPC_OuterRadius, TPC_OuterRadius, TPC_OuterRadius, TPC_OuterRadius, TPC_OuterRadius};
    

    G4Polycone              *PTFE_Sleeve = new G4Polycone("PTFE_Sleeve", 0.*deg, 360.0*deg, PTFE_Sleeve_zPlaneNbr, PTFE_Sleeve_zPlane, PTFE_Sleeve_rInner, PTFE_Sleeve_rOuter);
    
    G4LogicalVolume* PTFE_Sleeve_Logical = new G4LogicalVolume(PTFE_Sleeve,	 PTFE,  "PTFE_Sleeve_Logical");

    new G4PVPlacement(0, G4ThreeVector(0, 0, (TPC_Center_zAxis+(1.5+0.35)*25.4*mm)), PTFE_Sleeve_Logical, "PTFE_Sleeve_Physical",  fpWorldLogical,  true,  1,  true);

    
    
    //-------------------------------------------------------------------------------------------------
    
    
    
    
    
    //----------------------  3-inch PMT  ---------------------
    
    
    const G4double  PMT_TotLength   = 123.063*mm;
    
    const G4int     PMTzPlaneNbr = 8;
    const G4double  PMTShellThickness = 0.5*mm;
    
    
    const G4double  PMTzPlane[PMTzPlaneNbr]              = {0.*mm, -17.4115*mm, -35.041*mm, -39.9343*mm, -116.*mm, -116.078*mm, -116.713*mm, -PMT_TotLength};
    const G4double  PMTrInner[PMTzPlaneNbr]              = {36.576*mm, 36.576*mm, 28.0201*mm, 25.146*mm, 25.146*mm, 0.*mm, 0.*mm, 25.126*mm};
    const G4double  PMTrOuter[PMTzPlaneNbr]              = {36.576*mm+PMTShellThickness, 36.576*mm+PMTShellThickness, 28.0201*mm+PMTShellThickness, 25.146*mm+PMTShellThickness, 25.146*mm+PMTShellThickness, 25.146*mm+PMTShellThickness, 25.146*mm+PMTShellThickness, 25.146*mm+PMTShellThickness};
    
    const G4double  SubtrVolume_PMTzPlane[PMTzPlaneNbr]  = {0.*mm, -17.4115*mm, -35.041*mm, -39.9343*mm, -116.*mm, -116.078*mm, -116.713*mm, -PMT_TotLength};
    const G4double  SubtrVolume_PMTrInner[PMTzPlaneNbr]  = {0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm};
    const G4double  SubtrVolume_PMTrOuter[PMTzPlaneNbr]  = {36.576*mm+PMTShellThickness, 36.576*mm+PMTShellThickness, 28.0201*mm+PMTShellThickness, 25.146*mm+PMTShellThickness, 25.146*mm+PMTShellThickness, 25.146*mm+PMTShellThickness, 25.146*mm+PMTShellThickness, 25.146*mm+PMTShellThickness};

    
    
    const G4double  PMT_QuartzWindow_Radius = 35.576*mm;
    const G4double  PMT_QuartzWindow_TotLength = 3.4*mm;
    
    const G4double  BtmPMT_zOffset  =  TPC_Center_zAxis-(1.5+0.74+0.08)*25.4*mm-PMT_QuartzWindow_TotLength; //--- original z-axis position is at 0*mm ----
    
    
    
    G4Polycone              *Btm_PMT_Shell = new G4Polycone("Btm_PMT_Shell", 0.*deg, 360.0*deg, PMTzPlaneNbr, PMTzPlane, PMTrInner, PMTrOuter);
    
    G4Polycone              *BtmPMT_SubtrVolume = new G4Polycone("BtmPMT_SubtrVolume", 0.*deg, 360.0*deg, PMTzPlaneNbr, SubtrVolume_PMTzPlane, SubtrVolume_PMTrInner, SubtrVolume_PMTrOuter);
    
    
    G4LogicalVolume* Btm_PMT_Shell_Logical = new G4LogicalVolume(Btm_PMT_Shell,	 Kovar,  "Btm_PMT_Shell_Logical");
    
    
    new G4PVPlacement(0, G4ThreeVector(0, 0, BtmPMT_zOffset), Btm_PMT_Shell_Logical, "Btm_PMT_Shell_Physical",  fpWorldLogical,  true,  1,  true);
    
    
    G4Tubs  *Btm_PMT_QuartzWindow = new G4Tubs("Btm_PMT_QuartzWindow", 0.*mm, PMT_QuartzWindow_Radius, PMT_QuartzWindow_TotLength/2, 0.*deg, 360*deg);
    
    G4LogicalVolume *Btm_PMT_QuartzWindow_Logical = new G4LogicalVolume(Btm_PMT_QuartzWindow, quartz, "Btm_PMT_QuartzWindow_Logical");
    
    
    
    G4VisAttributes*   PMT_Body_Attributes = new G4VisAttributes(G4Colour::Cyan());
      PMT_Body_Attributes->SetForceSolid(true);
    G4VisAttributes* PMT_Window_Attributes = new G4VisAttributes(G4Colour::Green());
    PMT_Window_Attributes->SetForceSolid(true);
    
    Btm_PMT_QuartzWindow_Logical->SetVisAttributes(PMT_Window_Attributes);
           Btm_PMT_Shell_Logical->SetVisAttributes(PMT_Body_Attributes);
    
    
    
    new G4PVPlacement(0, G4ThreeVector(0,0, PMT_QuartzWindow_TotLength/2+BtmPMT_zOffset), Btm_PMT_QuartzWindow_Logical, "Btm_PMT_QuartzWindow_Physical", fpWorldLogical, true, 1,  true);
    
    
    //--------------------------------------------------------
    //*/
    
    
    
    
      
    
    
    
    
    ///*
    //--------------------- Volume to Subtract from Dead LXe --------------------------
    
    const G4int     TPC_SubtrVolume_zPlaneNbr = 7;
    
    const G4double  TPC_SubtrVolume_zPlane[TPC_SubtrVolume_zPlaneNbr] = {0.*mm, -(TPC_TopPart_TotHeight+TPC_FieldCage_TotHeight), -(TPC_TopPart_TotHeight+TPC_FieldCage_TotHeight), -(TPC_TopPart_TotHeight+TPC_FieldCage_TotHeight)-0.74*25.4*mm, -(TPC_TopPart_TotHeight+TPC_FieldCage_TotHeight)-(0.74+0.08)*25.4*mm, -(TPC_TopPart_TotHeight+TPC_FieldCage_TotHeight)-(0.74+0.08)*25.4*mm, -(TPC_TopPart_TotHeight+TPC_FieldCage_TotHeight)-(0.74+0.08+0.3)*25.4*mm,};
    
    const G4double  TPC_SubtrVolume_rInner[TPC_SubtrVolume_zPlaneNbr] = {0.*mm, 0.*mm, TPC_InnerRadius, PTFE_Sleeve_PMTWindow_InnerRadius, PTFE_Sleeve_PMTWindow_InnerRadius, PTFE_Sleeve_PMTBody_InnerRadius, PTFE_Sleeve_PMTBody_InnerRadius};
    
    const G4double  TPC_SubtrVolume_rOuter[TPC_SubtrVolume_zPlaneNbr] = {TPC_OuterRadius, TPC_OuterRadius, TPC_OuterRadius, TPC_OuterRadius, TPC_OuterRadius, TPC_OuterRadius, TPC_OuterRadius};
    
    
    G4Polycone     *TPC_SubtrVolume = new G4Polycone("TPC_SubtrVolume", 0.*deg, 360.0*deg, TPC_SubtrVolume_zPlaneNbr, TPC_SubtrVolume_zPlane, TPC_SubtrVolume_rInner, TPC_SubtrVolume_rOuter);
    
    
    G4VSolid*  Tot_SubtrVolume_temp = new G4UnionSolid("Tot_SubtrVolume_temp", TPC_SubtrVolume, Btm_PMT_QuartzWindow,  0, G4ThreeVector(0., 0., -(TPC_TopPart_TotHeight+TPC_FieldCage_TotHeight)-(0.74+0.08)*25.4*mm-PMT_QuartzWindow_TotLength/2));  

    G4VSolid*  Tot_SubtrVolume = new G4UnionSolid("Tot_SubtrVolume", Tot_SubtrVolume_temp, BtmPMT_SubtrVolume,  0, G4ThreeVector(0., 0., -(TPC_TopPart_TotHeight+TPC_FieldCage_TotHeight)-(0.74+0.08)*25.4*mm-PMT_QuartzWindow_TotLength));  

    
      //------------------------------------------------------------------------------------
    
    
    // PTFE Parts: Grey
    G4VisAttributes* PTFE_Attributes = new G4VisAttributes(G4Colour::Grey());
    PTFE_Attributes->SetForceSolid(true);
   PTFE_TopPMT_Holder_Logical->SetVisAttributes(PTFE_Attributes);
          PTFE_Sleeve_Logical->SetVisAttributes(PTFE_Attributes);
       PTFE_FieldCage_Logical->SetVisAttributes(PTFE_Attributes);
    


    
    
    
    
    //---------------------------- Copper Rings (23 in total)--------------------------------
    
    const G4double TPC_CopperRing_Thickness   = 0.01*25.4;    
    const G4double TPC_CopperRing_InnerRadius = TPC_FieldCage_OuterRadius;     
    const G4double TPC_CopperRing_OuterRadius = TPC_FieldCage_OuterRadius+TPC_CopperRing_Thickness;     
    
    const G4double TPC_CopperRing_TotHeight   = 0.1*25.4*mm; 
    
    
    G4Tubs     *TPC_CopperRing  = new G4Tubs("TPC_CopperRing",  TPC_CopperRing_InnerRadius,  TPC_CopperRing_OuterRadius,  TPC_CopperRing_TotHeight/2, 0.*deg, 360*deg);
    
    G4LogicalVolume* TPC_CopperRing_Logical = new G4LogicalVolume(TPC_CopperRing,	 copper,  "TPC_CopperRing_Logical");
    
    
    
    G4double InitialPosition = TPC_Center_zAxis+(0.35+1.5)*25.4*mm-1.5*TPC_CopperRing_TotHeight;
    G4double CopperRing_Distance = (0.1+0.04)*25.4*mm;
    
    for(int i=0; i<23; i++)
    {
        char *VolumeName = new char[30];
        sprintf(VolumeName, "FieldCage_Physical_%i", i);
        
        G4double Distance = InitialPosition-i*CopperRing_Distance;
        
        new G4PVPlacement(0, G4ThreeVector(0,0,Distance), TPC_CopperRing_Logical, VolumeName, fpWorldLogical,  true,  1,  true);
    }
    
    // Copper Ring: Yellow
    G4VisAttributes* CopperRing_Attributes = new G4VisAttributes(G4Colour::Yellow());
     CopperRing_Attributes->SetForceSolid(true);
    TPC_CopperRing_Logical->SetVisAttributes(CopperRing_Attributes);
       
    
    //----------------------------------------------------------------------------------------
    

    
    
        
    
    
    //----------------------------------------------------------------------------------------
    
    
    G4double Xenon_GasPocket_TotLength = 5*mm;
    
    
    //---------------Active LXe and GXe ------------
    
    G4Tubs  *ActiveLXe = new G4Tubs("ActiveLXe",    0.*mm,  TPC_InnerRadius,  (TPC_FieldCage_TotHeight-Xenon_GasPocket_TotLength)/2, 0.*deg, 360*deg);
    G4Tubs  *ActiveGXe = new G4Tubs("ActiveGXe",    0.*mm,  TPC_InnerRadius,   Xenon_GasPocket_TotLength/2,                          0.*deg, 360*deg);
    
    G4LogicalVolume *ActiveLXe_Logical = new G4LogicalVolume(ActiveLXe, LXe, "ActiveLXe_Logical");
    G4LogicalVolume *ActiveGXe_Logical = new G4LogicalVolume(ActiveGXe, GXe, "ActiveGXe_Logical");
    
    ActiveGXe_Logical->SetVisAttributes(G4Colour::Green());
    ActiveLXe_Logical->SetVisAttributes(G4Colour::Blue());
    
    G4double  ActiveLXe_Center_zAxis = TPC_Center_zAxis + (TPC_FieldCage_TotHeight-Xenon_GasPocket_TotLength)/2 - 1.5*25.4*mm;
    G4double  ActiveGXe_Center_zAxis = TPC_Center_zAxis + ActiveLXe_Center_zAxis + TPC_FieldCage_TotHeight/2 ;

    
    new G4PVPlacement(0, G4ThreeVector(0., 0., ActiveLXe_Center_zAxis),  ActiveLXe_Logical, "ActiveLXe_Physical", fpWorldLogical, true, 1, true);
    new G4PVPlacement(0, G4ThreeVector(0., 0., ActiveGXe_Center_zAxis),  ActiveGXe_Logical, "ActiveGXe_Physical", fpWorldLogical, true, 1, true);
    
    G4VisAttributes* ActiveXe_Attributes = new G4VisAttributes(G4Colour::Red());
    ActiveXe_Attributes->SetForceSolid(true);
    ActiveLXe_Logical->SetVisAttributes(ActiveXe_Attributes);
    ActiveGXe_Logical->SetVisAttributes(ActiveXe_Attributes);

    
    
     //---------------Dead LXe and GXe --------------
     
     G4double  Dewar_LXe_TotLength = TPC_Center_zAxis - SSDewar_Center_zPos + SSDewar_InnerWall_InnerDepth/2 + (TPC_FieldCage_TotHeight-Xenon_GasPocket_TotLength)/2;
     G4double  Dewar_GXe_TotLength = SSDewar_InnerWall_InnerDepth - Dewar_LXe_TotLength;
     
     
     G4Tubs             *LXe_Volume  = new G4Tubs("LAr_Volume",       0.*mm,  SSDewar_InnerWall_InnerRadius,   Dewar_LXe_TotLength/2, 0.*deg, 360*deg);
     G4Tubs             *GXe_Volume  = new G4Tubs("GXe_Volume",       0.*mm,  SSDewar_InnerWall_InnerRadius,   Dewar_GXe_TotLength/2, 0.*deg, 360*deg);
     
    
    
    G4double  DeadLXe_Center_zAxis = ActiveLXe_Center_zAxis + (TPC_FieldCage_TotHeight-Xenon_GasPocket_TotLength)/2 - Dewar_LXe_TotLength/2;
    G4double  DeadGXe_Center_zAxis = ActiveGXe_Center_zAxis - Xenon_GasPocket_TotLength/2 + Dewar_GXe_TotLength/2 ;

    
    //------ the reference point of the Tot_SubtrVolume is at zAxis = 0.mm in the coordinate of other part (LXe_Volume and GXe_Volume) -------
    
    G4SubtractionSolid* DeadLXe_Volume = new G4SubtractionSolid("DeadLXe_Volume", LXe_Volume, Tot_SubtrVolume, 0, G4ThreeVector(0., 0., Dewar_LXe_TotLength/2+TPC_TopPart_TotHeight+Xenon_GasPocket_TotLength) );

    G4SubtractionSolid* DeadGXe_Volume = new G4SubtractionSolid("DeadGXe_Volume", GXe_Volume, Tot_SubtrVolume, 0, G4ThreeVector(0., 0., -Dewar_GXe_TotLength/2+TPC_TopPart_TotHeight+Xenon_GasPocket_TotLength) );

    
    G4LogicalVolume* DeadLXe_Logical = new G4LogicalVolume(DeadLXe_Volume, LXe,  "DeadLXe_Logical");
    G4LogicalVolume* DeadGXe_Logical = new G4LogicalVolume(DeadGXe_Volume, GXe,  "DeadGXe_Logical");


    
    
    
    //----------------------  1-inch PMT  ---------------------
    
    const G4double  TopPMT_CaseWidth        = 25.4*mm;
    const G4double  TopPMT_WindowWidth      = 25.0*mm;
    const G4double  TopPMT_WindowThickness  =  1.5*mm;
    const G4double  TopPMT_CaseHeight       = 27.0*mm;
    const G4double  TopPMT_CaseThickness    =  0.5*mm;
    
    G4Box *TopPMT_Window   = new G4Box("TopPMT_Window",   TopPMT_WindowWidth/2, TopPMT_WindowWidth/2, TopPMT_WindowThickness/2);
    G4Box *TopPMT_CaseBody = new G4Box("TopPMT_CaseBody", TopPMT_CaseWidth/2,   TopPMT_CaseWidth/2, TopPMT_CaseHeight/2);
    G4Box *TopPMT_Interior = new G4Box("TopPMT_Interior", (TopPMT_CaseWidth/2-TopPMT_CaseThickness), (TopPMT_CaseWidth/2-TopPMT_CaseThickness), (TopPMT_CaseHeight-TopPMT_CaseThickness)/2);
    
    
    G4LogicalVolume* TopPMT_CaseBody_Logical = new G4LogicalVolume(TopPMT_CaseBody,       Al,  "TopPMT_CaseBody_Logical");
    G4LogicalVolume* TopPMT_Interior_Logical = new G4LogicalVolume(TopPMT_Interior,   vacuum,  "TopPMT_Interior_Logical");
    G4LogicalVolume* TopPMT_Window_Logical   = new G4LogicalVolume(TopPMT_Window,     quartz,  "TopPMT_Window_Logical");
    
    TopPMT_Interior_Logical->SetVisAttributes(G4Colour::White());
      TopPMT_Window_Logical->SetVisAttributes(PMT_Window_Attributes);
    TopPMT_CaseBody_Logical->SetVisAttributes(PMT_Body_Attributes);
    

    
    
    G4double TopPMT_CaseBody_zAxis_inGXe = -Dewar_GXe_TotLength/2+Xenon_GasPocket_TotLength+TPC_TopPart_TotHeight+TopPMT_WindowThickness+TopPMT_CaseHeight/2;
    G4double TopPMT_Window_zAxis_inGXe   = -Dewar_GXe_TotLength/2+Xenon_GasPocket_TotLength+TPC_TopPart_TotHeight+TopPMT_WindowThickness/2;

    
    new G4PVPlacement(0, G4ThreeVector(0, 0, -TopPMT_CaseThickness/2), TopPMT_Interior_Logical, "TopPMT_Interior_Physical", TopPMT_CaseBody_Logical, true, 1,  true);
    
    new G4PVPlacement(0, G4ThreeVector(0, 0, TopPMT_CaseBody_zAxis_inGXe), TopPMT_CaseBody_Logical, "BTopPMT_CaseBody_Physical_1",   DeadGXe_Logical, true, 1,  true);
    new G4PVPlacement(0, G4ThreeVector(0, 0, TopPMT_Window_zAxis_inGXe),     TopPMT_Window_Logical,    "TopPMT_Window_Physical_1",   DeadGXe_Logical, true, 1,  true);
    
    new G4PVPlacement(0, G4ThreeVector(-TopPMT_FullSpacing, 0, TopPMT_CaseBody_zAxis_inGXe), TopPMT_CaseBody_Logical, "BTopPMT_CaseBody_Physical_2",   DeadGXe_Logical, true, 1,  true);
    new G4PVPlacement(0, G4ThreeVector(-TopPMT_FullSpacing, 0, TopPMT_Window_zAxis_inGXe),     TopPMT_Window_Logical,    "TopPMT_Window_Physical_2",   DeadGXe_Logical, true, 1,  true);

    new G4PVPlacement(0, G4ThreeVector(TopPMT_FullSpacing, 0, TopPMT_CaseBody_zAxis_inGXe), TopPMT_CaseBody_Logical, "BTopPMT_CaseBody_Physical_3",   DeadGXe_Logical, true, 1,  true);
    new G4PVPlacement(0, G4ThreeVector(TopPMT_FullSpacing, 0, TopPMT_Window_zAxis_inGXe),     TopPMT_Window_Logical,    "TopPMT_Window_Physical_3",   DeadGXe_Logical, true, 1,  true);

    new G4PVPlacement(0, G4ThreeVector(-TopPMT_FullSpacing/2, TopPMT_FullSpacing, TopPMT_CaseBody_zAxis_inGXe), TopPMT_CaseBody_Logical, "BTopPMT_CaseBody_Physical_4",   DeadGXe_Logical, true, 1,  true);
    new G4PVPlacement(0, G4ThreeVector(-TopPMT_FullSpacing/2, TopPMT_FullSpacing, TopPMT_Window_zAxis_inGXe),     TopPMT_Window_Logical,    "TopPMT_Window_Physical_4",   DeadGXe_Logical, true, 1,  true);
    
    new G4PVPlacement(0, G4ThreeVector(TopPMT_FullSpacing/2, TopPMT_FullSpacing, TopPMT_CaseBody_zAxis_inGXe), TopPMT_CaseBody_Logical, "BTopPMT_CaseBody_Physical_5",   DeadGXe_Logical, true, 1,  true);
    new G4PVPlacement(0, G4ThreeVector(TopPMT_FullSpacing/2, TopPMT_FullSpacing, TopPMT_Window_zAxis_inGXe),     TopPMT_Window_Logical,    "TopPMT_Window_Physical_5",   DeadGXe_Logical, true, 1,  true);
    
    new G4PVPlacement(0, G4ThreeVector(-TopPMT_FullSpacing/2, -TopPMT_FullSpacing, TopPMT_CaseBody_zAxis_inGXe), TopPMT_CaseBody_Logical, "BTopPMT_CaseBody_Physical_6",   DeadGXe_Logical, true, 1,  true);
    new G4PVPlacement(0, G4ThreeVector(-TopPMT_FullSpacing/2, -TopPMT_FullSpacing, TopPMT_Window_zAxis_inGXe),     TopPMT_Window_Logical,    "TopPMT_Window_Physical_6",   DeadGXe_Logical, true, 1,  true);
    
    new G4PVPlacement(0, G4ThreeVector(TopPMT_FullSpacing/2, -TopPMT_FullSpacing, TopPMT_CaseBody_zAxis_inGXe), TopPMT_CaseBody_Logical, "BTopPMT_CaseBody_Physical_7",   DeadGXe_Logical, true, 1,  true);
    new G4PVPlacement(0, G4ThreeVector(TopPMT_FullSpacing/2, -TopPMT_FullSpacing, TopPMT_Window_zAxis_inGXe),     TopPMT_Window_Logical,    "TopPMT_Window_Physical_7",   DeadGXe_Logical, true, 1,  true);
    
    //---------------------------------------------------------
    

    
    
    
    
    new G4PVPlacement(0, G4ThreeVector(0, 0, DeadLXe_Center_zAxis), DeadLXe_Logical, "DeadLXe_Physical",  fpWorldLogical,  true,  1,  true);
    new G4PVPlacement(0, G4ThreeVector(0, 0, DeadGXe_Center_zAxis), DeadGXe_Logical, "DeadGXe_Physical",  fpWorldLogical,  true,  1,  true);
    
    
    
    
    G4VisAttributes* DeadLXe_Attributes = new G4VisAttributes(G4Colour::Blue());

    G4VisAttributes* DeadGXe_Attributes = new G4VisAttributes(G4Colour(0.12, 0.58, 1.0, 1.0));
    DeadGXe_Attributes->SetForceSolid(false);

    DeadLXe_Attributes->SetForceSolid(false);
    DeadLXe_Attributes->SetForceSolid(false);

    DeadLXe_Logical->SetVisAttributes(DeadLXe_Attributes);
    DeadGXe_Logical->SetVisAttributes(DeadGXe_Attributes);
    
    //-----------------------------------------------------------------------------

    
    
    
    

    
        
    //--------------------------------- Collimator and EJs --------------------------------------------------------------   
     
    
    
    //--- For PE Collimator 22cm x OD-22cm  ID-2.54cm 
    const G4double     Polythene_Cylinder_Inner_Radius = 2.54/2*cm;
    const G4double     Polythene_Cylinder_Outer_Radius = 11*cm;
    const G4double     Polythene_Cylinder_Half_Length  = 11*cm;
    
    //---- Distance between LiF and TPC center 60 cm -----
    const G4double     Polythene_Cylinder_xAxis_Distance = -60*cm + Polythene_Cylinder_Half_Length + 3*cm;
    const G4double     Polythene_Cylinder_zAxis_offset = TPC_Center_zAxis;
    
    
    //--- for 5"DIA x 5" Chamber of Scintillator, neutron detector ---  
    const G4double            EJ301_Radius = 5/2*25.4*mm;     
    const G4double        EJ301_halfHeight = 5/2*25.4*mm;
    
    //const double                       sqrt3 = 1.732;
    const G4double       Distance_EJ301_Away = 60*cm;
    //const G4double             EJ301_Spacing = 7.5*cm;
    //const G4double             EJ301_zOffset = -ActiveLAr_Volume_Height/2-TPC_zAxis_Offset;
    
    
    
    //----PE Collimator ---------
    
    G4Tubs* Collimator_tube = new G4Tubs("Collimator_tube", Polythene_Cylinder_Inner_Radius,  Polythene_Cylinder_Outer_Radius,  Polythene_Cylinder_Half_Length,  0.*deg,  360.*deg);
    
    G4LogicalVolume*  Collimator_tube_Logical = new G4LogicalVolume(Collimator_tube, polyethylene, "Collimator_tube_Logical");
    
    Collimator_tube_Logical->SetVisAttributes(PTFE_Attributes);

    
    G4RotationMatrix R_collimator;
    G4ThreeVector    T_collimator;
    
    R_collimator.rotateY(90.0*deg);
    T_collimator.setX(Polythene_Cylinder_xAxis_Distance);
    T_collimator.setY(0);
    T_collimator.setZ(Polythene_Cylinder_zAxis_offset);
    
    new G4PVPlacement(G4Transform3D(R_collimator, T_collimator),  Collimator_tube_Logical, "Collimator_tube_Physical", fpWorldLogical, false, 0);
    
    
    
    
    //-----------EJ301, neutron detector-----
    
    double      RotationAngle = 45.;
    double            PiValue = 3.1415926;
    
    
    G4Tubs*                        EJ301_tube = new G4Tubs("EJ301_tube", 0.*cm, EJ301_Radius, EJ301_halfHeight, 0.*deg, 360.*deg);
    
    G4LogicalVolume*       EJ301_tube_Logical = new G4LogicalVolume(EJ301_tube, EJ301, "EJ301_tube_Logical");
    
    EJ301_tube_Logical->SetVisAttributes(G4Colour::Red());
    
    G4RotationMatrix R_EJ301_1, R_EJ301_2;
    G4ThreeVector    T_EJ301_1, T_EJ301_2;
    
    
    
    R_EJ301_1.rotateX(90.0*deg);
    R_EJ301_1.rotateZ((90+RotationAngle)*deg);
   
    R_EJ301_2.rotateX(90.0*deg);
    R_EJ301_2.rotateZ((-90-RotationAngle)*deg);

    
    T_EJ301_1.setX(Distance_EJ301_Away*std::cos(RotationAngle/180.*PiValue));
    T_EJ301_2.setX(Distance_EJ301_Away*std::cos(RotationAngle/180.*PiValue));
   
    T_EJ301_1.setY(Distance_EJ301_Away*std::sin(RotationAngle/180.*PiValue));
    T_EJ301_2.setY(-Distance_EJ301_Away*std::sin(RotationAngle/180.*PiValue));
   
    T_EJ301_1.setZ(TPC_Center_zAxis);
    T_EJ301_2.setZ(TPC_Center_zAxis);
  
    
    new G4PVPlacement(G4Transform3D(R_EJ301_1, T_EJ301_1),  EJ301_tube_Logical, "EJ301_1", fpWorldLogical, true, 1, true);
    new G4PVPlacement(G4Transform3D(R_EJ301_2, T_EJ301_2),  EJ301_tube_Logical, "EJ301_2", fpWorldLogical, true, 1, true);
       
    
    

    
   
    
    //===============================================

	// Invisible world volume.
	fpWorldLogical->SetVisAttributes(G4VisAttributes::Invisible);
	
	
	//G4VisAttributes*  PMT_Attributes = new G4VisAttributes(G4Colour::Blue());  
	//PMT_Attributes->SetForceSolid(true);
    
    //===============================================
    
    // Create the TPC & EJs sensitive detector
    G4VSensitiveDetector* monitor = new BeamTestSensitiveDetector("Detector"); 
    
    // Create Periphery Volumes sensitive detector
    G4VSensitiveDetector* PeripheryDetector = new PeripherySensitiveDetector("PeripheryDetector"); 

    
    // Register detector with manager
    G4SDManager::GetSDMpointer()->AddNewDetector(monitor);
    G4SDManager::GetSDMpointer()->AddNewDetector(PeripheryDetector);
    


     ActiveGXe_Logical->SetSensitiveDetector(monitor);
     ActiveLXe_Logical->SetSensitiveDetector(monitor);
    EJ301_tube_Logical->SetSensitiveDetector(monitor);
    

    
    //---------------External Parts------------------
    
    
              SSInnerDewar_Logical->SetSensitiveDetector(PeripheryDetector);
              SSOuterDewar_Logical->SetSensitiveDetector(PeripheryDetector);
     SSInnerDewar_BtmPlate_Logical->SetSensitiveDetector(PeripheryDetector);
     SSOuterDewar_BtmPlate_Logical->SetSensitiveDetector(PeripheryDetector);
   SSDewar_CF600FlangeRing_Logical->SetSensitiveDetector(PeripheryDetector);
       SSDewar_CF600Flange_Logical->SetSensitiveDetector(PeripheryDetector);
    
    
        PTFE_FieldCage_Logical->SetSensitiveDetector(PeripheryDetector);
    PTFE_TopPMT_Holder_Logical->SetSensitiveDetector(PeripheryDetector);
           PTFE_Sleeve_Logical->SetSensitiveDetector(PeripheryDetector);
        TPC_CopperRing_Logical->SetSensitiveDetector(PeripheryDetector);
                   
         Btm_PMT_Shell_Logical->SetSensitiveDetector(PeripheryDetector);
  Btm_PMT_QuartzWindow_Logical->SetSensitiveDetector(PeripheryDetector);
         TopPMT_Window_Logical->SetSensitiveDetector(PeripheryDetector);
       TopPMT_CaseBody_Logical->SetSensitiveDetector(PeripheryDetector);
    
               DeadLXe_Logical->SetSensitiveDetector(PeripheryDetector);
               DeadGXe_Logical->SetSensitiveDetector(PeripheryDetector);
       Collimator_tube_Logical->SetSensitiveDetector(PeripheryDetector);
    
    

    
    //===============================================
 //*/
    
    
  /*
  ////////////////////////////////////////////////////////////////////////
  // Visualisation attributes
 
  // Invisible world volume.
  fpWorldLogical->SetVisAttributes(G4VisAttributes::Invisible);

  // HandsOn4: Calorimeter attributes 
  // Invisible calorimeter mother volume
  //calorimeterLogical->SetVisAttributes(G4VisAttributes::Invisible);
 
  // Calorimeter cells - green with transparency
  G4VisAttributes* calorimeterAttributes =
     new G4VisAttributes(G4Colour(0.0, 1.0, 0.0, 0.1));
  calorimeterAttributes->SetForceSolid(true);
  //cellLogical->SetVisAttributes(calorimeterAttributes);
 cellLogical->SetVisAttributes(G4VisAttributes::Invisible);

  // Target Volume - light blue
  G4VisAttributes* targetAttributes = new G4VisAttributes(G4Colour(0.0,0.5,0.5,1.0));
  targetAttributes->SetForceSolid(true);
  //targetLogical->SetVisAttributes(targetAttributes);
 targetLogical->SetVisAttributes(G4VisAttributes::Invisible);


  // Evacuation chamber  - magenta
  G4VisAttributes* evacChamberAttributes = new G4VisAttributes(G4Colour::Magenta());
  evacChamberAttributes->SetForceSolid(true);
  //evacChamberLogical->SetVisAttributes(evacChamberAttributes);
 evacChamberLogical->SetVisAttributes(G4VisAttributes::Invisible);

  // Silicon Monitor  - cyan
  G4VisAttributes* siliconMonitorAttributes = new G4VisAttributes(G4Colour::Cyan());
  siliconMonitorAttributes->SetForceSolid(true);
  //siliconMonitorLogical->SetVisAttributes(siliconMonitorAttributes);
siliconMonitorLogical->SetVisAttributes(G4VisAttributes::Invisible);



  // Beam Pipe Vacuum - yellow
  G4VisAttributes* beamPipeAttributes = new G4VisAttributes(G4Colour::Yellow());
  beamPipeAttributes->SetForceSolid(true);
  //beamPipeLogical->SetVisAttributes(beamPipeAttributes);
  beamPipeLogical->SetVisAttributes(G4VisAttributes::Invisible);  
*/  
 

}
