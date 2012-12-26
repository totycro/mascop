SRCDIR = src
OBJDIR = obj

GPP = ccache g++


STARTUP_SOURCE = $(SRCDIR)/main.cpp

CPP_SOURCES = \
	$(SRCDIR)/aircraftlanding.cpp \
	$(SRCDIR)/instance.cpp

DEBUG = 1

CXXFLAGS = -Wall -Wno-non-virtual-dtor -pipe
LDFLAGS =  -lgecodesearch -lgecodeint -lgecodekernel -lgecodesupport -lgecodegist

ifeq ($(DEBUG), 1)
  CXXFLAGS += -g -p -O0
else
  CXXFLAGS += -O3
endif

OBJ_FILES = $(addprefix $(OBJDIR)/, $(patsubst %.cpp,%.o, \
  $(patsubst src/%, %, $(CPP_SOURCES) ) ) )
STARTUP_OBJ = $(addprefix $(OBJDIR)/, $(patsubst %.cpp,%.o, \
  $(patsubst src/%, %,$(STARTUP_SOURCE) ) ) )

all: prog

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(SRCDIR)/%.h
	@echo
	@echo "compiling $<"
	$(GPP) $(CPPFLAGS) $(CXXFLAGS) -o $@ -c $< 

# for startup (no header file available)
$(OBJDIR)/main.o: $(SRCDIR)/main.cpp
	@echo 
	@echo "compiling $<"
	$(GPP) $(CPPFLAGS) $(CXXFLAGS) -o $@ -c $< 

prog: $(OBJ_FILES) $(STARTUP_OBJ)
	@echo 
	@echo "linking ..."
	@echo
	$(GPP) $(CPPFLAGS) $(CXXFLAGS) -o prog $(OBJ_FILES) $(STARTUP_OBJ) $(LDFLAGS)



depend:
	makedepend $(STARTUP_SOURCE) $(CPP_SOURCES)

clean:
	rm -f obj/*.o prog

# DO NOT DELETE

src/main.o: src/aircraftlanding.h src/instance.h /usr/include/gecode/int.hh
src/main.o: /usr/include/gecode/kernel.hh /usr/include/gecode/support.hh
src/main.o: /usr/include/gecode/support/config.hpp
src/main.o: /usr/include/gecode/support/auto-link.hpp
src/main.o: /usr/include/gecode/support/macros.hpp
src/main.o: /usr/include/gecode/support/exception.hpp
src/main.o: /usr/include/gecode/support/cast.hpp
src/main.o: /usr/include/gecode/support/heap.hpp
src/main.o: /usr/include/gecode/support/marked-pointer.hpp
src/main.o: /usr/include/gecode/support/int-type.hpp
src/main.o: /usr/include/gecode/support/bitset-base.hpp
src/main.o: /usr/include/gecode/support/bitset.hpp
src/main.o: /usr/include/gecode/support/block-allocator.hpp
src/main.o: /usr/include/gecode/support/dynamic-array.hpp
src/main.o: /usr/include/gecode/support/dynamic-queue.hpp
src/main.o: /usr/include/gecode/support/dynamic-stack.hpp
src/main.o: /usr/include/gecode/support/random.hpp
src/main.o: /usr/include/gecode/support/sort.hpp
src/main.o: /usr/include/gecode/support/static-stack.hpp
src/main.o: /usr/include/gecode/support/thread.hpp /usr/include/pthread.h
src/main.o: /usr/include/features.h /usr/include/stdc-predef.h
src/main.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
src/main.o: /usr/include/gnu/stubs.h /usr/include/endian.h
src/main.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
src/main.o: /usr/include/bits/byteswap-16.h /usr/include/sched.h
src/main.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
src/main.o: /usr/include/time.h /usr/include/bits/sched.h
src/main.o: /usr/include/bits/pthreadtypes.h /usr/include/bits/setjmp.h
src/main.o: /usr/include/gecode/support/thread/pthreads.hpp
src/main.o: /usr/include/unistd.h /usr/include/bits/posix_opt.h
src/main.o: /usr/include/bits/environments.h /usr/include/bits/confname.h
src/main.o: /usr/include/getopt.h /usr/include/ctype.h /usr/include/xlocale.h
src/main.o: /usr/include/gecode/support/thread/none.hpp
src/main.o: /usr/include/gecode/support/thread/thread.hpp
src/main.o: /usr/include/gecode/support/timer.hpp /usr/include/sys/time.h
src/main.o: /usr/include/bits/time.h /usr/include/sys/select.h
src/main.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
src/main.o: /usr/include/gecode/kernel/exception.hpp
src/main.o: /usr/include/gecode/kernel/memory-config.hpp
src/main.o: /usr/include/gecode/kernel/memory-manager.hpp
src/main.o: /usr/include/gecode/kernel/macros.hpp
src/main.o: /usr/include/gecode/kernel/archive.hpp
src/main.o: /usr/include/gecode/kernel/global-prop-info.hpp
src/main.o: /usr/include/gecode/kernel/core.hpp
src/main.o: /usr/include/gecode/kernel/var-type.hpp
src/main.o: /usr/include/gecode/kernel/modevent.hpp
src/main.o: /usr/include/gecode/kernel/range-list.hpp
src/main.o: /usr/include/gecode/kernel/region.hpp
src/main.o: /usr/include/gecode/kernel/var.hpp
src/main.o: /usr/include/gecode/kernel/view.hpp
src/main.o: /usr/include/gecode/kernel/array.hpp
src/main.o: /usr/include/gecode/kernel/shared-array.hpp
src/main.o: /usr/include/gecode/kernel/propagator.hpp
src/main.o: /usr/include/gecode/kernel/advisor.hpp
src/main.o: /usr/include/gecode/kernel/branch.hpp
src/main.o: /usr/include/gecode/kernel/brancher.hpp
src/main.o: /usr/include/gecode/kernel/brancher-view.hpp
src/main.o: /usr/include/gecode/kernel/brancher-tiebreak.hpp
src/main.o: /usr/include/gecode/kernel/brancher-val.hpp
src/main.o: /usr/include/gecode/kernel/var-imp.hpp
src/main.o: /usr/include/gecode/kernel/allocators.hpp
src/main.o: /usr/include/gecode/iter.hh
src/main.o: /usr/include/gecode/iter/ranges-operations.hpp
src/main.o: /usr/include/gecode/iter/ranges-minmax.hpp
src/main.o: /usr/include/gecode/iter/ranges-list.hpp
src/main.o: /usr/include/gecode/iter/ranges-append.hpp
src/main.o: /usr/include/gecode/iter/ranges-array.hpp
src/main.o: /usr/include/gecode/iter/ranges-cache.hpp
src/main.o: /usr/include/gecode/iter/ranges-compl.hpp
src/main.o: /usr/include/gecode/iter/ranges-diff.hpp
src/main.o: /usr/include/gecode/iter/ranges-empty.hpp
src/main.o: /usr/include/gecode/iter/ranges-inter.hpp
src/main.o: /usr/include/gecode/iter/ranges-map.hpp
src/main.o: /usr/include/gecode/iter/ranges-minus.hpp
src/main.o: /usr/include/gecode/iter/ranges-negative.hpp
src/main.o: /usr/include/gecode/iter/ranges-offset.hpp
src/main.o: /usr/include/gecode/iter/ranges-positive.hpp
src/main.o: /usr/include/gecode/iter/ranges-scale.hpp
src/main.o: /usr/include/gecode/iter/ranges-singleton.hpp
src/main.o: /usr/include/gecode/iter/ranges-union.hpp
src/main.o: /usr/include/gecode/iter/ranges-values.hpp
src/main.o: /usr/include/gecode/iter/ranges-add.hpp
src/main.o: /usr/include/gecode/iter/ranges-singleton-append.hpp
src/main.o: /usr/include/gecode/iter/ranges-rangelist.hpp
src/main.o: /usr/include/gecode/iter/values-array.hpp
src/main.o: /usr/include/gecode/iter/values-bitset.hpp
src/main.o: /usr/include/gecode/iter/values-list.hpp
src/main.o: /usr/include/gecode/iter/values-inter.hpp
src/main.o: /usr/include/gecode/iter/values-map.hpp
src/main.o: /usr/include/gecode/iter/values-minus.hpp
src/main.o: /usr/include/gecode/iter/values-negative.hpp
src/main.o: /usr/include/gecode/iter/values-offset.hpp
src/main.o: /usr/include/gecode/iter/values-positive.hpp
src/main.o: /usr/include/gecode/iter/values-ranges.hpp
src/main.o: /usr/include/gecode/iter/values-singleton.hpp
src/main.o: /usr/include/gecode/iter/values-union.hpp
src/main.o: /usr/include/gecode/iter/values-unique.hpp
src/main.o: /usr/include/gecode/iter/ranges-size.hpp
src/main.o: /usr/include/gecode/int/exception.hpp
src/main.o: /usr/include/gecode/int/limits.hpp
src/main.o: /usr/include/gecode/int/int-set-1.hpp
src/main.o: /usr/include/gecode/int/var-imp.hpp
src/main.o: /usr/include/gecode/int/var-imp/delta.hpp
src/main.o: /usr/include/gecode/int/var-imp/int.hpp
src/main.o: /usr/include/gecode/int/var-imp/bool.hpp
src/main.o: /usr/include/gecode/int/view.hpp
src/main.o: /usr/include/gecode/int/view/iter.hpp
src/main.o: /usr/include/gecode/int/var/int.hpp
src/main.o: /usr/include/gecode/int/var/bool.hpp
src/main.o: /usr/include/gecode/int/view/int.hpp
src/main.o: /usr/include/gecode/int/view/constint.hpp
src/main.o: /usr/include/gecode/int/view/zero.hpp
src/main.o: /usr/include/gecode/int/view/minus.hpp
src/main.o: /usr/include/gecode/int/view/offset.hpp
src/main.o: /usr/include/gecode/int/view/scale.hpp
src/main.o: /usr/include/gecode/int/view/cached.hpp
src/main.o: /usr/include/gecode/int/view/bool.hpp
src/main.o: /usr/include/gecode/int/view/neg-bool.hpp
src/main.o: /usr/include/gecode/int/view/print.hpp
src/main.o: /usr/include/gecode/int/var/print.hpp
src/main.o: /usr/include/gecode/int/view/rel-test.hpp
src/main.o: /usr/include/gecode/int/view/bool-test.hpp
src/main.o: /usr/include/gecode/int/propagator.hpp
src/main.o: /usr/include/gecode/int/array-traits.hpp
src/main.o: /usr/include/gecode/int/int-set-2.hpp
src/main.o: /usr/include/gecode/int/array.hpp
src/main.o: /usr/include/gecode/int/extensional/dfa.hpp
src/main.o: /usr/include/gecode/int/extensional/tuple-set.hpp
src/main.o: /usr/include/gecode/minimodel.hh /usr/include/gecode/set.hh
src/main.o: /usr/include/gecode/set/exception.hpp
src/main.o: /usr/include/gecode/set/limits.hpp
src/main.o: /usr/include/gecode/set/var-imp.hpp
src/main.o: /usr/include/gecode/set/var-imp/delta.hpp
src/main.o: /usr/include/gecode/set/var-imp/integerset.hpp
src/main.o: /usr/include/gecode/set/var-imp/iter.hpp
src/main.o: /usr/include/gecode/set/var-imp/set.hpp
src/main.o: /usr/include/gecode/set/view.hpp
src/main.o: /usr/include/gecode/set/var/set.hpp
src/main.o: /usr/include/gecode/set/view/set.hpp
src/main.o: /usr/include/gecode/set/view/const.hpp
src/main.o: /usr/include/gecode/set/view/singleton.hpp
src/main.o: /usr/include/gecode/set/view/complement.hpp
src/main.o: /usr/include/gecode/set/view/cached.hpp
src/main.o: /usr/include/gecode/set/view/print.hpp
src/main.o: /usr/include/gecode/set/var/print.hpp
src/main.o: /usr/include/gecode/set/array-traits.hpp
src/main.o: /usr/include/gecode/set/array.hpp
src/main.o: /usr/include/gecode/int/linear.hh
src/main.o: /usr/include/gecode/int/linear/int-bin.hpp
src/main.o: /usr/include/gecode/int/linear/int-ter.hpp
src/main.o: /usr/include/gecode/int/linear/int-nary.hpp
src/main.o: /usr/include/gecode/int/linear/int-noview.hpp
src/main.o: /usr/include/gecode/int/linear/int-dom.hpp
src/main.o: /usr/include/gecode/int/linear/bool-int.hpp
src/main.o: /usr/include/gecode/int/bool.hh
src/main.o: /usr/include/gecode/int/bool/base.hpp
src/main.o: /usr/include/gecode/int/bool/eq.hpp
src/main.o: /usr/include/gecode/int/bool/lq.hpp
src/main.o: /usr/include/gecode/int/bool/or.hpp
src/main.o: /usr/include/gecode/int/bool/eqv.hpp
src/main.o: /usr/include/gecode/int/bool/clause.hpp
src/main.o: /usr/include/gecode/int/linear/bool-view.hpp
src/main.o: /usr/include/gecode/int/linear/bool-scale.hpp
src/main.o: /usr/include/gecode/int/linear/post.hpp
src/main.o: /usr/include/gecode/minimodel/exception.hpp
src/main.o: /usr/include/gecode/minimodel/lin-expr.hpp
src/main.o: /usr/include/gecode/minimodel/lin-rel.hpp
src/main.o: /usr/include/gecode/minimodel/bool-expr.hpp
src/main.o: /usr/include/gecode/minimodel/set-expr.hpp
src/main.o: /usr/include/gecode/minimodel/set-rel.hpp
src/main.o: /usr/include/gecode/minimodel/matrix.hpp
src/main.o: /usr/include/gecode/minimodel/optimize.hpp
src/main.o: /usr/include/gecode/search.hh
src/main.o: /usr/include/gecode/search/statistics.hpp
src/main.o: /usr/include/gecode/search/stop.hpp
src/main.o: /usr/include/gecode/search/options.hpp
src/main.o: /usr/include/gecode/search/dfs.hpp
src/main.o: /usr/include/gecode/search/bab.hpp
src/main.o: /usr/include/gecode/search/restart.hpp
src/aircraftlanding.o: src/aircraftlanding.h src/instance.h
src/aircraftlanding.o: /usr/include/gecode/int.hh
src/aircraftlanding.o: /usr/include/gecode/kernel.hh
src/aircraftlanding.o: /usr/include/gecode/support.hh
src/aircraftlanding.o: /usr/include/gecode/support/config.hpp
src/aircraftlanding.o: /usr/include/gecode/support/auto-link.hpp
src/aircraftlanding.o: /usr/include/gecode/support/macros.hpp
src/aircraftlanding.o: /usr/include/gecode/support/exception.hpp
src/aircraftlanding.o: /usr/include/gecode/support/cast.hpp
src/aircraftlanding.o: /usr/include/gecode/support/heap.hpp
src/aircraftlanding.o: /usr/include/gecode/support/marked-pointer.hpp
src/aircraftlanding.o: /usr/include/gecode/support/int-type.hpp
src/aircraftlanding.o: /usr/include/gecode/support/bitset-base.hpp
src/aircraftlanding.o: /usr/include/gecode/support/bitset.hpp
src/aircraftlanding.o: /usr/include/gecode/support/block-allocator.hpp
src/aircraftlanding.o: /usr/include/gecode/support/dynamic-array.hpp
src/aircraftlanding.o: /usr/include/gecode/support/dynamic-queue.hpp
src/aircraftlanding.o: /usr/include/gecode/support/dynamic-stack.hpp
src/aircraftlanding.o: /usr/include/gecode/support/random.hpp
src/aircraftlanding.o: /usr/include/gecode/support/sort.hpp
src/aircraftlanding.o: /usr/include/gecode/support/static-stack.hpp
src/aircraftlanding.o: /usr/include/gecode/support/thread.hpp
src/aircraftlanding.o: /usr/include/pthread.h /usr/include/features.h
src/aircraftlanding.o: /usr/include/stdc-predef.h /usr/include/sys/cdefs.h
src/aircraftlanding.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
src/aircraftlanding.o: /usr/include/endian.h /usr/include/bits/endian.h
src/aircraftlanding.o: /usr/include/bits/byteswap.h
src/aircraftlanding.o: /usr/include/bits/byteswap-16.h /usr/include/sched.h
src/aircraftlanding.o: /usr/include/bits/types.h
src/aircraftlanding.o: /usr/include/bits/typesizes.h /usr/include/time.h
src/aircraftlanding.o: /usr/include/bits/sched.h
src/aircraftlanding.o: /usr/include/bits/pthreadtypes.h
src/aircraftlanding.o: /usr/include/bits/setjmp.h
src/aircraftlanding.o: /usr/include/gecode/support/thread/pthreads.hpp
src/aircraftlanding.o: /usr/include/unistd.h /usr/include/bits/posix_opt.h
src/aircraftlanding.o: /usr/include/bits/environments.h
src/aircraftlanding.o: /usr/include/bits/confname.h /usr/include/getopt.h
src/aircraftlanding.o: /usr/include/ctype.h /usr/include/xlocale.h
src/aircraftlanding.o: /usr/include/gecode/support/thread/none.hpp
src/aircraftlanding.o: /usr/include/gecode/support/thread/thread.hpp
src/aircraftlanding.o: /usr/include/gecode/support/timer.hpp
src/aircraftlanding.o: /usr/include/sys/time.h /usr/include/bits/time.h
src/aircraftlanding.o: /usr/include/sys/select.h /usr/include/bits/select.h
src/aircraftlanding.o: /usr/include/bits/sigset.h
src/aircraftlanding.o: /usr/include/gecode/kernel/exception.hpp
src/aircraftlanding.o: /usr/include/gecode/kernel/memory-config.hpp
src/aircraftlanding.o: /usr/include/gecode/kernel/memory-manager.hpp
src/aircraftlanding.o: /usr/include/gecode/kernel/macros.hpp
src/aircraftlanding.o: /usr/include/gecode/kernel/archive.hpp
src/aircraftlanding.o: /usr/include/gecode/kernel/global-prop-info.hpp
src/aircraftlanding.o: /usr/include/gecode/kernel/core.hpp
src/aircraftlanding.o: /usr/include/gecode/kernel/var-type.hpp
src/aircraftlanding.o: /usr/include/gecode/kernel/modevent.hpp
src/aircraftlanding.o: /usr/include/gecode/kernel/range-list.hpp
src/aircraftlanding.o: /usr/include/gecode/kernel/region.hpp
src/aircraftlanding.o: /usr/include/gecode/kernel/var.hpp
src/aircraftlanding.o: /usr/include/gecode/kernel/view.hpp
src/aircraftlanding.o: /usr/include/gecode/kernel/array.hpp
src/aircraftlanding.o: /usr/include/gecode/kernel/shared-array.hpp
src/aircraftlanding.o: /usr/include/gecode/kernel/propagator.hpp
src/aircraftlanding.o: /usr/include/gecode/kernel/advisor.hpp
src/aircraftlanding.o: /usr/include/gecode/kernel/branch.hpp
src/aircraftlanding.o: /usr/include/gecode/kernel/brancher.hpp
src/aircraftlanding.o: /usr/include/gecode/kernel/brancher-view.hpp
src/aircraftlanding.o: /usr/include/gecode/kernel/brancher-tiebreak.hpp
src/aircraftlanding.o: /usr/include/gecode/kernel/brancher-val.hpp
src/aircraftlanding.o: /usr/include/gecode/kernel/var-imp.hpp
src/aircraftlanding.o: /usr/include/gecode/kernel/allocators.hpp
src/aircraftlanding.o: /usr/include/gecode/iter.hh
src/aircraftlanding.o: /usr/include/gecode/iter/ranges-operations.hpp
src/aircraftlanding.o: /usr/include/gecode/iter/ranges-minmax.hpp
src/aircraftlanding.o: /usr/include/gecode/iter/ranges-list.hpp
src/aircraftlanding.o: /usr/include/gecode/iter/ranges-append.hpp
src/aircraftlanding.o: /usr/include/gecode/iter/ranges-array.hpp
src/aircraftlanding.o: /usr/include/gecode/iter/ranges-cache.hpp
src/aircraftlanding.o: /usr/include/gecode/iter/ranges-compl.hpp
src/aircraftlanding.o: /usr/include/gecode/iter/ranges-diff.hpp
src/aircraftlanding.o: /usr/include/gecode/iter/ranges-empty.hpp
src/aircraftlanding.o: /usr/include/gecode/iter/ranges-inter.hpp
src/aircraftlanding.o: /usr/include/gecode/iter/ranges-map.hpp
src/aircraftlanding.o: /usr/include/gecode/iter/ranges-minus.hpp
src/aircraftlanding.o: /usr/include/gecode/iter/ranges-negative.hpp
src/aircraftlanding.o: /usr/include/gecode/iter/ranges-offset.hpp
src/aircraftlanding.o: /usr/include/gecode/iter/ranges-positive.hpp
src/aircraftlanding.o: /usr/include/gecode/iter/ranges-scale.hpp
src/aircraftlanding.o: /usr/include/gecode/iter/ranges-singleton.hpp
src/aircraftlanding.o: /usr/include/gecode/iter/ranges-union.hpp
src/aircraftlanding.o: /usr/include/gecode/iter/ranges-values.hpp
src/aircraftlanding.o: /usr/include/gecode/iter/ranges-add.hpp
src/aircraftlanding.o: /usr/include/gecode/iter/ranges-singleton-append.hpp
src/aircraftlanding.o: /usr/include/gecode/iter/ranges-rangelist.hpp
src/aircraftlanding.o: /usr/include/gecode/iter/values-array.hpp
src/aircraftlanding.o: /usr/include/gecode/iter/values-bitset.hpp
src/aircraftlanding.o: /usr/include/gecode/iter/values-list.hpp
src/aircraftlanding.o: /usr/include/gecode/iter/values-inter.hpp
src/aircraftlanding.o: /usr/include/gecode/iter/values-map.hpp
src/aircraftlanding.o: /usr/include/gecode/iter/values-minus.hpp
src/aircraftlanding.o: /usr/include/gecode/iter/values-negative.hpp
src/aircraftlanding.o: /usr/include/gecode/iter/values-offset.hpp
src/aircraftlanding.o: /usr/include/gecode/iter/values-positive.hpp
src/aircraftlanding.o: /usr/include/gecode/iter/values-ranges.hpp
src/aircraftlanding.o: /usr/include/gecode/iter/values-singleton.hpp
src/aircraftlanding.o: /usr/include/gecode/iter/values-union.hpp
src/aircraftlanding.o: /usr/include/gecode/iter/values-unique.hpp
src/aircraftlanding.o: /usr/include/gecode/iter/ranges-size.hpp
src/aircraftlanding.o: /usr/include/gecode/int/exception.hpp
src/aircraftlanding.o: /usr/include/gecode/int/limits.hpp
src/aircraftlanding.o: /usr/include/gecode/int/int-set-1.hpp
src/aircraftlanding.o: /usr/include/gecode/int/var-imp.hpp
src/aircraftlanding.o: /usr/include/gecode/int/var-imp/delta.hpp
src/aircraftlanding.o: /usr/include/gecode/int/var-imp/int.hpp
src/aircraftlanding.o: /usr/include/gecode/int/var-imp/bool.hpp
src/aircraftlanding.o: /usr/include/gecode/int/view.hpp
src/aircraftlanding.o: /usr/include/gecode/int/view/iter.hpp
src/aircraftlanding.o: /usr/include/gecode/int/var/int.hpp
src/aircraftlanding.o: /usr/include/gecode/int/var/bool.hpp
src/aircraftlanding.o: /usr/include/gecode/int/view/int.hpp
src/aircraftlanding.o: /usr/include/gecode/int/view/constint.hpp
src/aircraftlanding.o: /usr/include/gecode/int/view/zero.hpp
src/aircraftlanding.o: /usr/include/gecode/int/view/minus.hpp
src/aircraftlanding.o: /usr/include/gecode/int/view/offset.hpp
src/aircraftlanding.o: /usr/include/gecode/int/view/scale.hpp
src/aircraftlanding.o: /usr/include/gecode/int/view/cached.hpp
src/aircraftlanding.o: /usr/include/gecode/int/view/bool.hpp
src/aircraftlanding.o: /usr/include/gecode/int/view/neg-bool.hpp
src/aircraftlanding.o: /usr/include/gecode/int/view/print.hpp
src/aircraftlanding.o: /usr/include/gecode/int/var/print.hpp
src/aircraftlanding.o: /usr/include/gecode/int/view/rel-test.hpp
src/aircraftlanding.o: /usr/include/gecode/int/view/bool-test.hpp
src/aircraftlanding.o: /usr/include/gecode/int/propagator.hpp
src/aircraftlanding.o: /usr/include/gecode/int/array-traits.hpp
src/aircraftlanding.o: /usr/include/gecode/int/int-set-2.hpp
src/aircraftlanding.o: /usr/include/gecode/int/array.hpp
src/aircraftlanding.o: /usr/include/gecode/int/extensional/dfa.hpp
src/aircraftlanding.o: /usr/include/gecode/int/extensional/tuple-set.hpp
src/aircraftlanding.o: /usr/include/gecode/minimodel.hh
src/aircraftlanding.o: /usr/include/gecode/set.hh
src/aircraftlanding.o: /usr/include/gecode/set/exception.hpp
src/aircraftlanding.o: /usr/include/gecode/set/limits.hpp
src/aircraftlanding.o: /usr/include/gecode/set/var-imp.hpp
src/aircraftlanding.o: /usr/include/gecode/set/var-imp/delta.hpp
src/aircraftlanding.o: /usr/include/gecode/set/var-imp/integerset.hpp
src/aircraftlanding.o: /usr/include/gecode/set/var-imp/iter.hpp
src/aircraftlanding.o: /usr/include/gecode/set/var-imp/set.hpp
src/aircraftlanding.o: /usr/include/gecode/set/view.hpp
src/aircraftlanding.o: /usr/include/gecode/set/var/set.hpp
src/aircraftlanding.o: /usr/include/gecode/set/view/set.hpp
src/aircraftlanding.o: /usr/include/gecode/set/view/const.hpp
src/aircraftlanding.o: /usr/include/gecode/set/view/singleton.hpp
src/aircraftlanding.o: /usr/include/gecode/set/view/complement.hpp
src/aircraftlanding.o: /usr/include/gecode/set/view/cached.hpp
src/aircraftlanding.o: /usr/include/gecode/set/view/print.hpp
src/aircraftlanding.o: /usr/include/gecode/set/var/print.hpp
src/aircraftlanding.o: /usr/include/gecode/set/array-traits.hpp
src/aircraftlanding.o: /usr/include/gecode/set/array.hpp
src/aircraftlanding.o: /usr/include/gecode/int/linear.hh
src/aircraftlanding.o: /usr/include/gecode/int/linear/int-bin.hpp
src/aircraftlanding.o: /usr/include/gecode/int/linear/int-ter.hpp
src/aircraftlanding.o: /usr/include/gecode/int/linear/int-nary.hpp
src/aircraftlanding.o: /usr/include/gecode/int/linear/int-noview.hpp
src/aircraftlanding.o: /usr/include/gecode/int/linear/int-dom.hpp
src/aircraftlanding.o: /usr/include/gecode/int/linear/bool-int.hpp
src/aircraftlanding.o: /usr/include/gecode/int/bool.hh
src/aircraftlanding.o: /usr/include/gecode/int/bool/base.hpp
src/aircraftlanding.o: /usr/include/gecode/int/bool/eq.hpp
src/aircraftlanding.o: /usr/include/gecode/int/bool/lq.hpp
src/aircraftlanding.o: /usr/include/gecode/int/bool/or.hpp
src/aircraftlanding.o: /usr/include/gecode/int/bool/eqv.hpp
src/aircraftlanding.o: /usr/include/gecode/int/bool/clause.hpp
src/aircraftlanding.o: /usr/include/gecode/int/linear/bool-view.hpp
src/aircraftlanding.o: /usr/include/gecode/int/linear/bool-scale.hpp
src/aircraftlanding.o: /usr/include/gecode/int/linear/post.hpp
src/aircraftlanding.o: /usr/include/gecode/minimodel/exception.hpp
src/aircraftlanding.o: /usr/include/gecode/minimodel/lin-expr.hpp
src/aircraftlanding.o: /usr/include/gecode/minimodel/lin-rel.hpp
src/aircraftlanding.o: /usr/include/gecode/minimodel/bool-expr.hpp
src/aircraftlanding.o: /usr/include/gecode/minimodel/set-expr.hpp
src/aircraftlanding.o: /usr/include/gecode/minimodel/set-rel.hpp
src/aircraftlanding.o: /usr/include/gecode/minimodel/matrix.hpp
src/aircraftlanding.o: /usr/include/gecode/minimodel/optimize.hpp
src/aircraftlanding.o: /usr/include/gecode/search.hh
src/aircraftlanding.o: /usr/include/gecode/search/statistics.hpp
src/aircraftlanding.o: /usr/include/gecode/search/stop.hpp
src/aircraftlanding.o: /usr/include/gecode/search/options.hpp
src/aircraftlanding.o: /usr/include/gecode/search/dfs.hpp
src/aircraftlanding.o: /usr/include/gecode/search/bab.hpp
src/aircraftlanding.o: /usr/include/gecode/search/restart.hpp
src/aircraftlanding.o: /usr/include/gecode/gist.hh
src/aircraftlanding.o: /usr/include/gecode/gist/gist.hpp
src/instance.o: src/instance.h
