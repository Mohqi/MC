# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

# compile CXX with /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++
CXX_FLAGS = -W -Wall -pedantic -Wno-non-virtual-dtor -Wno-long-long -Wwrite-strings -Wpointer-arith -Woverloaded-virtual -Wno-variadic-macros -Wshadow -pipe -Qunused-arguments -DGL_SILENCE_DEPRECATION -stdlib=libc++ -std=c++11  -O3 -DNDEBUG -fno-trapping-math -ftree-vectorize -fno-math-errno -O3 -DNDEBUG -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk   -fPIC -std=gnu++11

CXX_DEFINES = -DG4INTY_USE_QT -DG4LIB_BUILD_DLL -DG4UI_USE_QT -DG4UI_USE_TCSH -DG4VIS_USE_OPENGL -DG4VIS_USE_OPENGLQT -DQT_CORE_LIB -DQT_GUI_LIB -DQT_NO_DEBUG -DQT_OPENGL_LIB -DQT_PRINTSUPPORT_LIB -DQT_WIDGETS_LIB

CXX_INCLUDES = -I/Users/arichert/lib/root/root-6.18.04_build/include -I/Users/arichert/Desktop/Projet/MC/Microbeam/source/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/analysis/g4tools/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/analysis/accumulables/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/analysis/csv/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/analysis/factory/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/analysis/hntools/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/analysis/management/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/analysis/root/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/analysis/xml/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/digits_hits/detector/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/digits_hits/digits/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/digits_hits/hits/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/digits_hits/scorer/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/digits_hits/utils/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/error_propagation/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/event/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/externals/clhep/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/externals/zlib/include -isystem /Users/arichert/lib/geant4/geant4_build/source/geometry/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/geometry/biasing/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/geometry/divisions/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/geometry/magneticfield/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/geometry/management/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/geometry/navigation/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/geometry/solids/Boolean/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/geometry/solids/CSG/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/geometry/solids/specific/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/geometry/volumes/include -isystem /Users/arichert/lib/geant4/geant4_build/source/global/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/global/HEPGeometry/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/global/HEPNumerics/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/global/HEPRandom/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/global/management/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/graphics_reps/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/intercoms/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/interfaces/GAG/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/interfaces/basic/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/interfaces/common/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/materials/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/parameterisations/gflash/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/particles/adjoint/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/particles/bosons/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/particles/hadrons/barions/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/particles/hadrons/ions/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/particles/hadrons/mesons/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/particles/leptons/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/particles/management/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/particles/shortlived/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/particles/utils/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/persistency/ascii/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/persistency/mctruth/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/physics_lists/builders/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/physics_lists/constructors/decay/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/physics_lists/constructors/electromagnetic/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/physics_lists/constructors/factory/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/physics_lists/constructors/gamma_lepto_nuclear/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/physics_lists/constructors/hadron_elastic/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/physics_lists/constructors/hadron_inelastic/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/physics_lists/constructors/ions/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/physics_lists/constructors/limiters/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/physics_lists/constructors/stopping/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/physics_lists/lists/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/physics_lists/util/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/processes/biasing/management/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/processes/biasing/generic/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/processes/biasing/importance/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/processes/cuts/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/processes/decay/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/processes/electromagnetic/adjoint/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/processes/electromagnetic/dna/processes/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/processes/electromagnetic/dna/models/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/processes/electromagnetic/dna/utils/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/processes/electromagnetic/dna/management/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/processes/electromagnetic/dna/molecules/management/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/processes/electromagnetic/dna/molecules/types/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/processes/electromagnetic/highenergy/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/processes/electromagnetic/lowenergy/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/processes/electromagnetic/muons/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/processes/electromagnetic/pii/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/processes/electromagnetic/polarisation/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/processes/electromagnetic/standard/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/processes/electromagnetic/utils/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/processes/electromagnetic/xrays/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/processes/hadronic/cross_sections/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/processes/hadronic/management/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/processes/hadronic/models/abla/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/processes/hadronic/models/abrasion/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/processes/hadronic/models/binary_cascade/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/processes/hadronic/models/cascade/cascade/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/processes/hadronic/models/coherent_elastic/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/processes/hadronic/models/de_excitation/ablation/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/processes/hadronic/models/de_excitation/evaporation/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/processes/hadronic/models/de_excitation/fermi_breakup/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/processes/hadronic/models/de_excitation/fission/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/processes/hadronic/models/de_excitation/gem_evaporation/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/processes/hadronic/models/de_excitation/handler/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/processes/hadronic/models/de_excitation/management/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/processes/hadronic/models/de_excitation/multifragmentation/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/processes/hadronic/models/de_excitation/photon_evaporation/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/processes/hadronic/models/de_excitation/util/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/processes/hadronic/models/em_dissociation/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/processes/hadronic/models/fission/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/processes/hadronic/models/im_r_matrix/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/processes/hadronic/models/inclxx/utils/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/processes/hadronic/models/inclxx/incl_physics/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/processes/hadronic/models/inclxx/interface/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/processes/hadronic/models/gamma_nuclear/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/processes/hadronic/models/lend/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/processes/hadronic/models/lepto_nuclear/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/processes/hadronic/models/management/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/processes/hadronic/models/particle_hp/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/processes/hadronic/models/parton_string/diffraction/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/processes/hadronic/models/parton_string/hadronization/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/processes/hadronic/models/parton_string/management/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/processes/hadronic/models/parton_string/qgsm/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/processes/hadronic/models/pre_equilibrium/exciton_model/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/processes/hadronic/models/qmd/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/processes/hadronic/models/quasi_elastic/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/processes/hadronic/models/radioactive_decay/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/processes/hadronic/models/rpg/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/processes/hadronic/models/theo_high_energy/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/processes/hadronic/models/util/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/processes/hadronic/processes/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/processes/hadronic/stopping/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/processes/hadronic/util/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/processes/management/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/processes/optical/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/processes/solidstate/phonon/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/processes/solidstate/channeling/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/processes/parameterisation/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/processes/scoring/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/processes/transportation/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/readout/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/run/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/track/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/tracking/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/visualization/FukuiRenderer/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/visualization/HepRep/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/visualization/RayTracer/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/visualization/Tree/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/visualization/VRML/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/visualization/XXX/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/visualization/externals/gl2ps/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/visualization/gMocren/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/visualization/management/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/visualization/modeling/include -isystem /Users/arichert/lib/geant4/geant4.10.06.p01/source/visualization/OpenGL/include -isystem /Users/arichert/lib/geant4/geant4_build/source/externals/zlib -iframework /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk/System/Library/Frameworks -iframework /Users/arichert/lib/qtlib/QT/5.14.1/clang_64/lib -isystem /Users/arichert/lib/qtlib/QT/5.14.1/clang_64/lib/QtGui.framework/Headers -isystem /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk/System/Library/Frameworks/OpenGL.framework/Headers -isystem /Users/arichert/lib/qtlib/QT/5.14.1/clang_64/lib/QtCore.framework/Headers -isystem /Users/arichert/lib/qtlib/QT/5.14.1/clang_64/./mkspecs/macx-clang -isystem /Users/arichert/lib/qtlib/QT/5.14.1/clang_64/lib/QtWidgets.framework/Headers -isystem /Users/arichert/lib/qtlib/QT/5.14.1/clang_64/lib/QtPrintSupport.framework/Headers -isystem /Users/arichert/lib/qtlib/QT/5.14.1/clang_64/lib/QtOpenGL.framework/Headers 

