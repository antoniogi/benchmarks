AUTOMAKE_OPTIONS = subdir-objects

openshmemdir = $(pkglibexecdir)/openshmem

openshmem_PROGRAMS = osu_oshm_get osu_oshm_put osu_oshm_put_mr \
					 osu_oshm_atomics osu_oshm_barrier osu_oshm_broadcast \
					 osu_oshm_collect osu_oshm_fcollect osu_oshm_reduce \
					 osu_oshm_get_nb osu_oshm_put_nb osu_oshm_put_overlap \
					 osu_oshm_get_mr_nb osu_oshm_put_mr_nb 

AM_CFLAGS = -I../util

UTILITIES = ../util/osu_util.c osu_util.h

osu_oshm_get_SOURCES = osu_oshm_get.c $(UTILITIES)
osu_oshm_put_SOURCES = osu_oshm_put.c $(UTILITIES)
osu_oshm_put_mr_SOURCES = osu_oshm_put_mr.c $(UTILITIES)
osu_oshm_atomics_SOURCES = osu_oshm_atomics.c $(UTILITIES)
osu_oshm_barrier_SOURCES = osu_oshm_barrier.c $(UTILITIES)
osu_oshm_broadcast_SOURCES = osu_oshm_broadcast.c $(UTILITIES)
osu_oshm_collect_SOURCES = osu_oshm_collect.c $(UTILITIES)
osu_oshm_fcollect_SOURCES = osu_oshm_fcollect.c $(UTILITIES)
osu_oshm_reduce_SOURCES = osu_oshm_reduce.c $(UTILITIES)
osu_oshm_get_nb_SOURCES = osu_oshm_get_nb.c $(UTILITIES)
osu_oshm_put_nb_SOURCES = osu_oshm_put_nb.c $(UTILITIES)
osu_oshm_put_overlap_SOURCES = osu_oshm_put_overlap.c $(UTILITIES)
osu_oshm_get_mr_nb_SOURCES = osu_oshm_get_mr_nb.c $(UTILITIES)
osu_oshm_put_mr_nb_SOURCES = osu_oshm_put_mr_nb.c $(UTILITIES)
