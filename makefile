gpp = g++-6
prom = annulus
deps = $(shell find ./src -name "*.hpp")
src = $(shell find ./src -name "*.cpp" ! -name "generator.cpp")
objdir = ./bin/
setting = -w -std=c++14 -O2
$(shell mkdir $(objdir))
obj = $(src:%.cpp=%.o) 

$(prom): $(obj)
	$(gpp) -o $(objdir)$(prom) $(addprefix $(objdir), $(notdir $(obj))) $(setting)
	@echo ""
	@bin/$(prom)
	@python3 ./src/draw.py

%.o: %.cpp $(deps)
	$(gpp) -c $< -o $(addprefix $(objdir), $(notdir $@)) $(setting)

gen: src/generator.cpp $(obj)
	$(gpp) -o $(objdir)generator src/generator.cpp bin/utils.o $(setting)
	@echo ""
	@bin/generator

clean:
	rm -rf $(objdir)*
