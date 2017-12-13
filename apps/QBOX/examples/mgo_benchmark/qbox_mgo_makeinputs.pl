#! /usr/bin/perl -w
#
# generate input files for large bcc magnesium oxide systems for Qbox HPC benchmarking 
#
# written by Erik Draeger, LLNL, 4/12/2013

if ($#ARGV < 1) {
   print "syntax:  qbox_mgo_makeinputs [number of atoms] [number of MPI tasks]\n";
  exit;
}

# if you're using the open source version from http://eslab.ucdavis.edu/software/qbox/ set this to one.
# if you're using the qb@LL version, set this to zero.
$useDavisVersion = 0;   


$nAtoms = $ARGV[0];
$nTasks = $ARGV[1];

# print coordinates to .sys file
$species1 = "magnesium";
$atomtype1 = "Mg";
$pseudo1 = "Mg.xml";
$species2 = "oxygen";
$atomtype2 = "O";
$pseudo2 = "O.xml";
$a0 = 7.7;

$nx = 2;
$ny = 2;
if ($nAtoms >= 512)
{
   $nx = 4;
   $ny = 4;
}
$nz = int $nAtoms/(8*$nx*$ny);

if ($nz < 1) { $nz = 1; }

$nFinal = 8*$nx*$ny*$nz;

print "Using natoms = $nFinal\n";

$ax = $a0*$nx;
$ay = $a0*$ny;
$az = $a0*$nz;

$sysfile = join '',"mgo.N",$nFinal,".sys";
open SYS, ">$sysfile";
print SYS "set cell $ax 0.0 0.0 0.0 $ay 0.0 0.0 0.0 $az\n";
print SYS "species $species1 $pseudo1\n";
print SYS "species $species2 $pseudo2\n";

# print magnesium atom positions
$atomcnt = 1;
for ($i=0; $i<$nx; $i++) { 
  for ($j=0; $j<$ny; $j++) { 
    for ($k=0; $k<$nz; $k++) { 

      $x = 0.0 + $i*$a0;
      $y = 0.0 + $j*$a0;
      $z = 0.0 + $k*$a0;
      printf SYS "atom $atomtype1$atomcnt $species1 %11.7f %11.7f %11.7f\n",$x,$y,$z;
      $atomcnt++;

      $x = 0.5*$a0 + $i*$a0;
      $y = 0.5*$a0 + $j*$a0;
      $z = 0.0 + $k*$a0;
      printf SYS "atom $atomtype1$atomcnt $species1 %11.7f %11.7f %11.7f\n",$x,$y,$z;
      $atomcnt++;

      $x = 0.5*$a0 + $i*$a0;
      $y = 0.0 + $j*$a0;
      $z = 0.5*$a0 + $k*$a0;
      printf SYS "atom $atomtype1$atomcnt $species1 %11.7f %11.7f %11.7f\n",$x,$y,$z;
      $atomcnt++;

      $x = 0.0 + $i*$a0;
      $y = 0.5*$a0 + $j*$a0;
      $z = 0.5*$a0 + $k*$a0;
      printf SYS "atom $atomtype1$atomcnt $species1 %11.7f %11.7f %11.7f\n",$x,$y,$z;
      $atomcnt++;

    }
  }
}
# print oxygen atom positions
$atomcnt = 1;
for ($i=0; $i<$nx; $i++) { 
  for ($j=0; $j<$ny; $j++) { 
    for ($k=0; $k<$nz; $k++) { 

      $x = 0.5*$a0 + $i*$a0;
      $y = 0.5*$a0 + $j*$a0;
      $z = 0.5*$a0 + $k*$a0;
      printf SYS "atom $atomtype2$atomcnt $species2 %11.7f %11.7f %11.7f\n",$x,$y,$z;
      $atomcnt++;

      $x = 0.0 + $i*$a0;
      $y = 0.0 + $j*$a0;
      $z = 0.5*$a0 + $k*$a0;
      printf SYS "atom $atomtype2$atomcnt $species2 %11.7f %11.7f %11.7f\n",$x,$y,$z;
      $atomcnt++;

      $x = 0.0 + $i*$a0;
      $y = 0.5*$a0 + $j*$a0;
      $z = 0.0 + $k*$a0;
      printf SYS "atom $atomtype2$atomcnt $species2 %11.7f %11.7f %11.7f\n",$x,$y,$z;
      $atomcnt++;

      $x = 0.5*$a0 + $i*$a0;
      $y = 0.0 + $j*$a0;
      $z = 0.0 + $k*$a0;
      printf SYS "atom $atomtype2$atomcnt $species2 %11.7f %11.7f %11.7f\n",$x,$y,$z;
      $atomcnt++;

    }
  }
}
close SYS;

# print input file

$nrowmax = 1024;
if ($nTasks < 128) { $nrowmax = $nTasks; }
elsif ($nTasks <= 4096) { $nrowmax = $nTasks / 4; }
elsif ($nTasks >= 65536) { $nrowmax = 2048; }

$ecut = 65;                     # plane wave basis size, defined by ecut in Rydbergs


$inputfile = join '',"mgo.N",$nFinal,".i";
open IN, ">$inputfile";

print IN "set nrowmax $nrowmax\n";
print IN "$sysfile\n";
print IN "\n";
print IN "set xc LDA\n";
print IN "set ecut $ecut\n";
print IN "set wf_dyn PSDA\n";
print IN "set ecutprec 8.0\n";
print IN "\n";
if ($useDavisVersion == 1)
{
   print IN "kpoint del 0 0 0\n";
   print IN "kpoint add 0.0000001 0 0 1.0\n";
}
else
{
   print IN "kpoint 0.0000001 0 0 1.0\n";
}
print IN "\n";
print IN "randomize_wf\n";
print IN "run 0 5\n";
print IN "\n";
print IN "quit\n";
close IN;

