BINARIES = test7
OBJECTS = XSLKin.o ff_reweight_defs.o ff_reweight_utils.o McDecayGraph.o \
					McDecayGraphSummary.o McDecayGraphCrawler.o DecayMode.o BToDlnuMode.o

FF_REWEIGHT_ROOT = /Users/dchao/mctest/ff_reweight
UTILS_ROOT = $(FF_REWEIGHT_ROOT)/utils

CLHEP_ROOT = /usr/local/include
CLHEP_LIBS = /usr/local/lib

BOOST_ROOT = /usr/local/boost_1_56_0
BOOST_LIBS = $(BOOST_ROOT)/stage/lib

LIBPQ_ROOT = /usr/local/pgsql
LIBPQ_INCS = $(LIBPQ_ROOT)/include
LIBPQ_LIBS = $(LIBPQ_ROOT)/lib

INCFLAGS = -I$(UTILS_ROOT) -I$(CLHEP_ROOT) -I$(BOOST_ROOT) -I$(LIBPQ_INCS)
LDFLAGS = -L $(UTILS_ROOT) -L $(CLHEP_LIBS) \
					-L$(BOOST_LIBS) -L$(LIBPQ_LIBS) \
					-Wl,-rpath,$(UTILS_ROOT) -lff_reweight_utils \
					-Wl,-rpath,$(CLHEP_LIBS) -lCLHEP-2.3.3.1 \
					-Wl,-rpath,$(BOOST_LIBS) -lboost_program_options \
					-Wl,-rpath,$(LIBPQ_LIBS) -lpq

CXX := g++
CXXFLAGS = -Wall -fPIC -pthread -std=c++11 -DNDEBUG -O2 -Wno-unused-local-typedef -Wno-redeclared-class-member

SRCS = $(wildcard *.cc)
BUILDDIR = build

DEPDIR = .d
$(shell mkdir -p $(DEPDIR) > /dev/null)
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td
POSTCOMPILE = @mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d

all : $(BINARIES)

test% : $(addprefix $(BUILDDIR)/, test%.o $(OBJECTS))
	$(CXX) $(LDFLAGS) $^ -o $@
	
$(BUILDDIR)/%.o : %.cc
$(BUILDDIR)/%.o : %.cc $(DEPDIR)/%.d
	$(CXX) $(DEPFLAGS) $(CXXFLAGS) $(INCFLAGS) -c $< -o $@
	$(POSTCOMPILE)

$(DEPDIR)/%.d: ;

.PRECIOUS: $(DEPDIR)/%.d

-include $(patsubst %,$(DEPDIR)/%.d,$(basename $(SRCS)))

clean : 
	@rm -f *~ $(BINARIES) $(BUILDDIR)/* *.pdf *.gif *.png *.gv *.ps *.csv

cleanall : clean
	@rm -f $(DEPDIR)/*
