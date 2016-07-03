# directory configuration
# -----------------------

BINARIES = ff_reweight

# objects to package into the shared library
OBJECTS = McDecayGraph.o McDecayModeCurator.o \
					BToDlnuMode.o BToDslnuMode.o BToDsslnuMode.o \
					BSemiLepDict.o \
					CLNReweighter.o LLSWReweighter.o \
					FormFactorAnalyzer.o

# external dependencies
# ---------------------

FF_REWEIGHT_ROOT = /home/dchao/workspace/bdtaunu_reweighting
UTILS_INCDIR = $(FF_REWEIGHT_ROOT)/utils
UTILS_LIBDIR = $(FF_REWEIGHT_ROOT)/utils
XSLPHYSICS_INCDIR = $(FF_REWEIGHT_ROOT)/xslphysics
XSLPHYSICS_LIBDIR = $(FF_REWEIGHT_ROOT)/xslphysics

CLHEP_ROOT = /usr/local/CLHEP_2.3.3.1
CLHEP_INCDIR = $(CLHEP_ROOT)/include
CLHEP_LIBDIR = $(CLHEP_ROOT)/lib

BOOST_ROOT = /usr/local/boost_1_59_0
BOOST_INCDIR = $(BOOST_ROOT)
BOOST_LIBDIR = $(BOOST_ROOT)/stage/lib
BOOST_LIBS = -lboost_program_options -lboost_regex

LIBPQ_ROOT = /usr/pgsql-9.4
LIBPQ_INCDIR = $(LIBPQ_ROOT)/include
LIBPQ_LIBDIR = $(LIBPQ_ROOT)/lib

INCFLAGS += -I$(UTILS_INCDIR) -I$(XSLPHYSICS_INCDIR) -I$(CLHEP_INCDIR) \
						-I$(BOOST_INCDIR) -I$(LIBPQ_INCDIR)
LDFLAGS += -L$(UTILS_LIBDIR) -L$(XSLPHYSICS_LIBDIR) -L$(CLHEP_LIBDIR) \
          -L$(BOOST_LIBDIR) -L$(LIBPQ_LIBDIR) \
          -Wl,-rpath,$(UTILS_LIBDIR) -lreweight_utils \
          -Wl,-rpath,$(XSLPHYSICS_LIBDIR) -lxslphysics \
          -Wl,-rpath,$(CLHEP_LIBDIR) -lCLHEP-2.3.3.1 \
          -Wl,-rpath,$(BOOST_LIBDIR) -lboost_program_options \
          -Wl,-rpath,$(LIBPQ_LIBDIR) -lpq

# build rules
# -----------

CXX := g++
CXXFLAGS = -Wall -fPIC -pedantic -pthread -std=c++11 -O2 \
					 -Wno-unused-local-typedef -Wno-redeclared-class-member

SRCS = $(wildcard *.cc)
BUILDDIR = build

DEPDIR = .d
$(shell mkdir -p $(DEPDIR) > /dev/null)
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td
POSTCOMPILE = @mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d

all : $(BINARIES)

ff_reweight : $(addprefix $(BUILDDIR)/, ff_reweight.o $(OBJECTS))
	$(CXX) $(LDFLAGS) $^ -o $@

test% : $(addprefix $(BUILDDIR)/, test%.o $(OBJECTS))
	$(CXX) $(LDFLAGS) $^ -o $@

$(BUILDDIR)/%.o : %.cc
$(BUILDDIR)/%.o : %.cc $(DEPDIR)/%.d
	$(CXX) $(DEPFLAGS) $(CXXFLAGS) $(INCFLAGS) -c $< -o $@
	$(POSTCOMPILE)

$(DEPDIR)/%.d: ;

.PRECIOUS: $(DEPDIR)/%.d

-include $(patsubst %,$(DEPDIR)/%.d,$(notdir $(basename $(SRCS))))

clean : 
	@rm -f *~ $(BINARIES) $(BUILDDIR)/* *.csv

cleanall : clean
	@rm -f $(DEPDIR)/*
