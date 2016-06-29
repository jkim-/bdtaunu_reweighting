# directory configuration
# -----------------------

BINARIES = 

# objects to package into the shared library
OBJECTS = BXlnuKin.o BVlnuKin.o ff_reweight_utils.o McDecayGraph.o \
          McDecayGraphSummary.o McDecayGraphCrawler.o DecayMode.o BToDlnuMode.o \
          BToDlnuAnalyzer.o BSemiLepDict.o \
          ISGW2PseudoscalarFF.o CLNPseudoscalarFF.o \
          ISGW2VectorFF.o CLNVectorFF.o \
          gauss_legendre.o BPlnuDecayRate.o BVlnuDecayRate.o \
          BDss0FF.o BDss0lnuDecayRate.o \
          BD1primeFF.o BD1primelnuDecayRate.o \
          BD1FF.o BD1lnuDecayRate.o \
          BD2FF.o BD2lnuDecayRate.o

LIBNAME = libff_reweight.so

# external dependencies
# ---------------------

FF_REWEIGHT_ROOT = /Users/dchao/workspace/bdtaunu_reweighting
INCDIR = $(FF_REWEIGHT_ROOT)/include
LIBDIR = $(FF_REWEIGHT_ROOT)/lib
UTILS_INCDIR = $(FF_REWEIGHT_ROOT)/utils
UTILS_LIBDIR = $(FF_REWEIGHT_ROOT)/utils

CLHEP_INCDIR = /usr/local/include
CLHEP_LIBDIR = /usr/local/lib

BOOST_ROOT = /usr/local/boost_1_56_0
BOOST_INCDIR = $(BOOST_ROOT)
BOOST_LIBDIR = $(BOOST_ROOT)/stage/lib
BOOST_LIBS = -lboost_program_options -lboost_regex

LIBPQ_ROOT = /usr/local/pgsql
LIBPQ_INCDIR = $(LIBPQ_ROOT)/include
LIBPQ_LIBDIR = $(LIBPQ_ROOT)/lib

INCFLAGS += -I$(INCDIR) -I$(UTILS_INCDIR) -I$(CLHEP_INCDIR) \
						-I$(BOOST_INCDIR) -I$(LIBPQ_INCDIR)
LDFLAGS += -L $(UTILS_LIBDIR) -L $(CLHEP_LIBDIR) \
          -L$(BOOST_LIBDIR) -L$(LIBPQ_LIBDIR) \
          -Wl,-rpath,$(UTILS_LIBDIR) -lff_reweight_utils \
          -Wl,-rpath,$(CLHEP_LIBDIR) -lCLHEP-2.3.3.1 \
          -Wl,-rpath,$(BOOST_LIBDIR) -lboost_program_options \
          -Wl,-rpath,$(LIBPQ_LIBDIR) -lpq

# link flags for binary executables
EXELDFLAGS = -L$(LIBDIR) -L $(UTILS_LIBDIR) -L $(CLHEP_LIBDIR) \
							-L$(BOOST_LIBDIR) -L$(LIBPQ_LIBDIR) \
							-Wl,-rpath,$(LIBDIR) -lff_reweight \
							-Wl,-rpath,$(UTILS_LIBDIR) -lff_reweight_utils \
							-Wl,-rpath,$(CLHEP_LIBDIR) -lCLHEP-2.3.3.1 \
							-Wl,-rpath,$(BOOST_LIBDIR) -lboost_program_options \
							-Wl,-rpath,$(LIBPQ_LIBDIR) -lpq

# build rules
# -----------

CXX := g++
CXXFLAGS = -Wall -fPIC -pedantic -pthread -std=c++11 -O2 \
					 -Wno-unused-local-typedef -Wno-redeclared-class-member

SRCS = $(wildcard src/*.cc)
BUILDDIR = build

DEPDIR = .d
$(shell mkdir -p $(DEPDIR) > /dev/null)
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td
POSTCOMPILE = @mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d

all : $(BINARIES) lib

test% : $(BUILDDIR)/test%.o lib
	$(CXX) $(EXELDFLAGS) $< -o $@

lib : $(addprefix $(BUILDDIR)/, $(OBJECTS))
	if [ "$(shell uname)" = "Darwin" ]; then \
    SHARED_LIB_FLAG="-dynamiclib -Wl,-install_name,@rpath/$(LIBNAME)"; \
  else \
    SHARED_LIB_FLAG="-shared -Wl,-soname,$(LIBNAME)"; \
  fi; \
	$(CXX) $(LDFLAGS) $${SHARED_LIB_FLAG} $^ -o $(addprefix $(LIBDIR)/, $(LIBNAME))

$(BUILDDIR)/%.o : src/%.cc
$(BUILDDIR)/%.o : src/%.cc $(DEPDIR)/%.d
	$(CXX) $(DEPFLAGS) $(CXXFLAGS) $(INCFLAGS) -c $< -o $@
	$(POSTCOMPILE)

$(DEPDIR)/%.d: ;

.PRECIOUS: $(DEPDIR)/%.d

-include $(patsubst %,$(DEPDIR)/%.d,$(notdir $(basename $(SRCS))))

clean : 
	@rm -f *~ $(BINARIES) $(LIBDIR)/* $(BUILDDIR)/*

cleanall : clean
	@rm -f $(DEPDIR)/*
