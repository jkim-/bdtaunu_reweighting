BINARIES = sideband_reweight

OBJECTS = 

SRCS = $(wildcard *.cc *.cpp)

SYMLINKS = grid_search

CUDA_ROOT = /usr/local/cuda-7.5
CUDA_LIBS = $(CUDA_ROOT)/lib64

BOOST_ROOT = /usr/local/boost_1_59_0
BOOST_INCDIR = $(BOOST_ROOT)
BOOST_LIBDIR = $(BOOST_ROOT)/stage/lib

LIBPQ_ROOT = /usr/pgsql-9.4
LIBPQ_INCDIR = $(LIBPQ_ROOT)/include
LIBPQ_LIBDIR = $(LIBPQ_ROOT)/lib

BBRCITKDE_ROOT = /home/dchao/workspace/bbrcit_kde

BDTAUNU_REWEIGHT_ROOT = /home/dchao/workspace/bdtaunu_reweighting
UTILS_INCDIR = $(BDTAUNU_REWEIGHT_ROOT)
UTILS_LIBDIR = $(BDTAUNU_REWEIGHT_ROOT)/utils

INCFLAGS = -I$(BBRCITKDE_ROOT)/include -I$(BOOST_INCDIR) \
					 -I$(LIBPQ_INCDIR) -I$(UTILS_INCDIR)
LDFLAGS = -L$(CUDA_LIBS) -lcudart \
          -L$(BOOST_LIBDIR) \
          -L$(LIBPQ_LIBDIR) \
					-L$(UTILS_LIBDIR) -lreweight_utils \
					-Wl,-rpath,$(BOOST_LIBDIR) -lboost_program_options \
          -Wl,-rpath,$(LIBPQ_LIBDIR) -lpq \
					-Wl,-rpath,$(UTILS_LIBDIR)


BUILDDIR = build

CXX := g++
CXXFLAGS = -Wall -Werror -pedantic -pthread -std=c++11 -O2

DEPDIR = .d
$(shell mkdir -p $(DEPDIR) > /dev/null)
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td
POSTCOMPILE = @mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d

NVCC := nvcc -ccbin=$(CXX)
NVCCFLAGS = -std=c++11 -O2 -arch=sm_35 -x cu
NVCCMAKEDEP = @$(NVCC) -M -MT $@ $(NVCCFLAGS) $(INCFLAGS) $< -o\
							$(patsubst $(BUILDDIR)/%.o, $(DEPDIR)/%.d, $@)


all : $(BINARIES) $(SYMLINKS)

grid_search :
	ln -s $(BBRCITKDE_ROOT)/grid_search/grid_search grid_search

sideband_reweight : $(addprefix $(BUILDDIR)/, sideband_reweight.o $(OBJECTS))
	$(CXX) $^ $(LDFLAGS) -o $@

test% : $(addprefix $(BUILDDIR)/, test%.o $(OBJECTS))
	$(CXX) $^ $(LDFLAGS) -o $@

$(BUILDDIR)/%.o : %.cpp
$(BUILDDIR)/%.o : %.cpp $(DEPDIR)/%.d
	$(CXX) $(DEPFLAGS) $(CXXFLAGS) $(INCFLAGS) -c $< -o $@
	$(POSTCOMPILE)

$(BUILDDIR)/%.o : %.cc
$(BUILDDIR)/%.o : %.cc $(DEPDIR)/%.d
	$(NVCCMAKEDEP)
	$(NVCC) $(NVCCFLAGS) $(INCFLAGS) -c $< -o $@

$(DEPDIR)/%.d: ;

.PRECIOUS: $(DEPDIR)/%.d

-include $(patsubst %,$(DEPDIR)/%.d,$(basename $(SRCS)))

clean : 
	@rm -f *~ $(BINARIES) $(BUILDDIR)/* $(SYMLINKS)

cleanall : clean
	@rm -f $(DEPDIR)/* *.csv
