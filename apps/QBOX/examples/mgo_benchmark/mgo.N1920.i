set nrowmax 1024
mgo.N1920.sys

set xc LDA
set ecut 65
set wf_dyn PSDA
set ecutprec 8.0

kpoint 0.0000001 0 0 1.0

randomize_wf
run 0 5

quit
