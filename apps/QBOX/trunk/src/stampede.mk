#-------------------------------------------------------------------------------
#
#  zeus-x86_64_intel.mk
#
#-------------------------------------------------------------------------------
# $Id: linux_x86_64_intel.mk,v 1.1 2010/01/22 00:35:01 draeger1 Exp $
#
 PLT=LINUX_X86_64
#-------------------------------------------------------------------------------
 XERCESCDIR=/work/02658/agomez/tools/hpctoolkit/xerces
 XERCESCLIBDIR=$(XERCESCDIR)/lib
 XERCESLIB=$(XERCESCLIBDIR)/libxerces-c.a
 FFTWDIR=$(TACC_FFTW2_DIR)
 FFTWINC=$(TACC_FFTW2_INC)
 FFTWLIB=$(TACC_FFTW2_LIB)
 BLASDIR=$(MKLROOT)/lib
 SCALAPACK_DIR = /opt/apps/intel13/mvapich2_1_9/petsc/3.5/sandybridge/lib/
 SCALAPACKLIB  = $(SCALAPACK_DIR)/libscalapack.a

 CXX=mpicxx
 CC=mpicc
 LD=$(CXX)

 #DFLAGS += -DUSE_FFTW -DUSE_CSTDIO_LFS -D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64 -DXML -DUSE_XERCES -DXERCESC_3
 DFLAGS += -DUSE_CSTDIO_LFS -D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64 -DXML -DUSE_XERCES -DXERCESC_3
# DFLAGS += -DPRINTALL -DUSE_FFTW -DUSE_CSTDIO_LFS -D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64 -DXML -DUSE_XERCES

 INCLUDE = -I$(FFTWINC) -I$(XERCESCDIR)/include

 CXXFLAGS= -g -O3 -openmp -xW -DUSE_MPI -DSCALAPACK -DADD_ -D$(PLT) $(INCLUDE) $(DFLAGS)
 CFLAGS= -g -O3 -openmp -xW -DUSE_MPI -DSCALAPACK -DADD_ -D$(PLT) $(INCLUDE) $(DFLAGS)

 LIBPATH = -L$(FFTWLIB) -L$(BLASDIR) -L$(XERCESCLIBDIR) -L/usr/lib64/
 LIBS =  $(SCALAPACKLIB) $(FFTWLIB)/libdfftw_mpi.a -openmp -lmkl_core -lmkl_intel_thread -lmkl_intel_lp64 -lifcore -lxerces-c# -luuid

 LDFLAGS = $(LIBPATH) $(LIBS) -Wl,-rpath,$(MKLROOT)/lib

#-------------------------------------------------------------------------------
